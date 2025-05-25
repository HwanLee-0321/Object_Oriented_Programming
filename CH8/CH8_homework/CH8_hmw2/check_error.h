/******************************************************************************
 * Program Test: Automatic Error Check
 ******************************************************************************/
#if AUTOMATIC_ERROR_CHECK

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include <cstring>

class TokenReader
{
    istream& is;
    string line;
    vector<string> tokens;
    unsigned idx;
    bool print_mode;
    bool split();

public:
    TokenReader(istream& is, bool print_mode);
    void clear();
    string& getLine();
    bool nextLine();
    string *next();
    void printRemainingLines(const string& preMsg, const string& postMsg);
};

class Evaluator
{
    bool trace;
    streambuf *cin_backup, *cout_backup;
    //ifstream ifs;
    stringstream oss;
    const string HOME_DIR = "test";

    bool fileCopy(const string& srcfn, istream& is, const string& newDir);
    void print_OX(const string& prompt, bool condition);
    bool fstream_check(const string& fn, ios& stream);
    void setOutputStream(bool set_oss);
    void test(const string& msg, void (*pf)(),
              const string& in_fn, const string& out_fn);
    bool diff(istream& user_is, istream& correct_is);
    void printTraceMessage(string& cline, string& uNext, string& cNext);
    int  getTestFileCount();
public:
    Evaluator(bool trace);
    void run();
};

void evaluate(bool trace)
{
#if AUTOMATIC_ERROR_CHECK != 2
    UI::echo_input = true;
#endif
    Evaluator rt(trace);
    rt.run();
}

/******************************************************************************
 * class Evaluator implementation
 ******************************************************************************/
Evaluator::Evaluator(bool trace):
    trace{trace}, cin_backup{cin.rdbuf()}, cout_backup{cout.rdbuf()} {
}

int Evaluator::getTestFileCount() {
    const string& pathName = HOME_DIR;
    DIR     *dp;
    if ((dp = opendir(pathName.c_str())) == nullptr) {
        cout << pathName << ": directory open error" << endl;
        return 0;
    }
    int count = 0;
    for (struct dirent *dirp; (dirp = readdir(dp)) != NULL; ) {
    	char *p = strchr(dirp->d_name, '.');
    	if (p && strcmp(p, ".in") == 0) ++count;
    }
    closedir(dp);
    return count;
}

void Evaluator::run() {
    int testFileCount = getTestFileCount();
    for (int i = 1; i <= testFileCount; ++i) {
        string itemNumStr = to_string(i);
        string test_name = "test " + itemNumStr;
        string file_name = HOME_DIR + "/test_" + itemNumStr;

        test(test_name, ::run, file_name+".in", file_name+".out");
    }
    cout << "Good bye!!" << endl;
}

bool is_space(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

bool Evaluator::fileCopy(const string& srcfn, istream& is, const string& newDir) {
	string fn(srcfn);
	fn.replace(fn.find(HOME_DIR),  HOME_DIR.size(),  newDir);
	cout << "fileCopy(): " << srcfn << "\t-->    " << fn << endl;
	ofstream ofs(fn);
    if (fstream_check(fn, ofs)) return true;
	is.clear();
	is.seekg(0);
	copy((istreambuf_iterator<char>(is)), (istreambuf_iterator<char>()), (ostreambuf_iterator<char>(ofs)));
	ofs.close();
	return false;
}

void Evaluator::test(const string& msg, void (*pf)(),
                     const string& in_fn, const string& out_fn) {
    ifstream ifs(in_fn);
    if (fstream_check(in_fn, ifs)) return;
    cin.rdbuf(ifs.rdbuf());
    setOutputStream(true);
    pf();
    cin .rdbuf(cin_backup);
    cout.rdbuf(cout_backup);

#if (AUTOMATIC_ERROR_CHECK == 2)
    fileCopy( in_fn, ifs, "oj");
    fileCopy(out_fn, oss, "oj");
#elif (AUTOMATIC_ERROR_CHECK == 3)
    fileCopy(out_fn, oss, HOME_DIR);
#else
    string user_output = oss.str();
    ifstream ifs_correct(out_fn);
    if (fstream_check(out_fn, ifs_correct)) return;
    string correct_output((istreambuf_iterator<char>(ifs_correct)), (istreambuf_iterator<char>()));

    user_output.erase(remove_if(user_output.begin(), user_output.end(), is_space), user_output.end());
    correct_output.erase(remove_if(correct_output.begin(), correct_output.end(), is_space), correct_output.end());

    bool is_correct = (user_output == correct_output);
    print_OX(msg, is_correct);

    if (!is_correct && trace)
        diff(oss, ifs_correct);
    ifs_correct.close();
#endif
    ifs.close();
}

void Evaluator::setOutputStream(bool set_oss) {
    if (set_oss) {
        oss.str("");
        cout.rdbuf(oss.rdbuf());
    }
}

void Evaluator::print_OX(const string& prompt, bool condition) {
    cout << prompt << " : " << (condition ? "O" : "X") << endl;
    cout.flush();
}

bool Evaluator::fstream_check(const string& fn, ios& stream)
{
    if (!stream)
        cout << fn << ": file open error" << endl;
    return !stream;
}


void Evaluator::printTraceMessage(string& cline, string& uNext, string& cNext) {
    cout << "^--- [wrong line]" << endl;
    cout << cline << endl << "^--- [correct line]" << endl;
    cout << "User output(\"" << uNext  <<
            "\") is not equal to correct output(\"" << cNext << "\")" << endl;
    cout << "continue[y/n]? ";
    string next;
    cin >> next;
    if (next != "y" && next != "Y") {
        cout << "Good bye" << endl;
        exit(0);
    }
}

bool Evaluator::diff(istream& user_is, istream& correct_is) {
    TokenReader user(user_is, true), correct(correct_is, false);
    string *pUserNext, *pCorrectNext;
    bool err = false;
    while (true) {
        pUserNext = user.next();
        pCorrectNext = correct.next();
        if ((pUserNext == nullptr) || (pCorrectNext == nullptr))
            break;
        if (*pUserNext != *pCorrectNext) {
            err = true;
            printTraceMessage(correct.getLine(), *pUserNext, *pCorrectNext);
            user.clear();
            correct.clear();
         }
    }
    if ((pUserNext == nullptr) && (pCorrectNext == nullptr))
        return err;
    if (pUserNext != nullptr)
        user.printRemainingLines("User output", "correct answer");
    else if (pCorrectNext != nullptr)
        correct.printRemainingLines("Correct answer", "user output");
    return true;
}

/******************************************************************************
 * class TokenReader implementation
 ******************************************************************************/
bool TokenReader::split() { // true: has tokens
    tokens.clear();
    string word;
    for (auto n : line) {
        if (n != ' ' && n != '\t' && n != '\n' && n != '\r') // not white space
            word += n;
        else if (!word.empty()) { // white space
            tokens.push_back(move(word));
            word.clear();
        }
    }
    if (!word.empty()) tokens.push_back(word);
    return !tokens.empty();
}

TokenReader::TokenReader(istream& is, bool print_mode): is{is}, print_mode{print_mode} {
    idx = 0;
    is.seekg (0, is.beg);
}

void TokenReader::clear() {
    tokens.clear();
    idx = 0;
}

string& TokenReader::getLine()  { return line; }

bool TokenReader::nextLine() {
    while (getline(is, line)) {
        if (print_mode)               cout << line << endl;
        if (!line.empty() && split()) return true;
    }
    is.clear();
    return false;
}

string* TokenReader::next() {
    if (idx == tokens.size()) {
        idx = 0;
        if (!nextLine()) return nullptr;
    }
    return &(tokens[idx++]);
}

void TokenReader::printRemainingLines(const string& preMsg, const string& postMsg) {
    cout << preMsg << " has more lines than " << postMsg << " as follows." << endl;
    cout << line << endl;
    while (getline(is, line))
        cout << line << endl;
}

#endif // AUTOMATIC_ERROR_CHECK



