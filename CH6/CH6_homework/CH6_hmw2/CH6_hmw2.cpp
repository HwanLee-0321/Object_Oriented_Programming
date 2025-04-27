#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#define AUTOMATIC_ERROR_CHECK false
using namespace std;

// *********************************************************
// Persson class
// *********************************************************
class Person
{
    string     name;           // 이름
    int        id;             // Identifier
    double     weight;         // 체중
    bool       married;        // 결혼여부
    char*      address;        // 주소
    string     rawInput;       // 입력값
    string     passwd;         // 비밀번호
    char*      memo_c_str;     // 메모

protected:
    void inputMembers       (istream& in);
    void printMembers(ostream& out) const;
    void copyAddress        (const char* address);
    void copyMemo           (const char* c_str);
public:
    // 생성자
    Person(const string name = "", int id = 0, double weight = 0.0,
        bool married = false, const char* address = nullptr)
     : name(name), id(id), weight(weight), married(married),
       address(nullptr), memo_c_str(nullptr)
    {
        copyAddress(address);
        cout << "Person::Person(...):"; println();
    }
    Person(const Person& p);
    Person& assign(const Person& p);
    ~Person() { cout << "Person::~Person():"; println(); }

    // setter 함수
    void set(const string& name, int pid, double weight, bool married, const char* addr);
    void setName(const string& name)       { this->name = name; }
    void set(int pid)                      { id = pid; }
    void set(double pweight)               { weight = pweight; }
    void set(bool pmarried)                { married = pmarried; }
    void setAddress(const char* address); 
    void setPasswd(const string& pw)       { passwd = pw; }
    void setMemo(const char* c_str)        { copyMemo(c_str); }

    // getter 함수
    const string& getName()   const { return name; }
    const string& getPasswd() const { return passwd; }
    int         getId()       const { return id; }
    double      getWeight()   const { return weight; }
    bool        getMarried()  const { return married; }
    const char* getAddress()        { return address; }
    const char* getMemo()           { return memo_c_str; }
    

    // 기능 함수
    void input(istream& in)         { inputMembers(in); }
    void print(ostream& out) const;
    void println() const;
    void whatAreYouDoing();
    bool isSame(const string& name, int pid);
};
// *********************************************************
// Persson class end point
// *********************************************************

// *********************************************************
// Persson member func start point
// *********************************************************

void Person::printMembers(ostream& out) const {
    out << name << " " << id << " " << weight << " "
          << (married ? "true" : "false") << " :"
          << (address ? address : "") << ":";
}

// Person 클래스 바깥 정의부
void Person::print(ostream& out) const {
    printMembers(out);
}

void Person::println() const {
    print(cout);
    cout << endl;
}

Person& Person::assign(const Person& p) {
    if (this == &p) return *this; // 자기 자신 대입 방지

    // 기본 타입 및 string은 = 연산자로 깊은 복사
    name    = p.name;
    passwd  = p.passwd;
    id      = p.id;
    weight  = p.weight;
    married = p.married;

    setAddress(p.address);
    setMemo(p.memo_c_str);

    return *this;
}

void Person::setAddress(const char* address) {
    copyAddress(address);
}

void Person::copyAddress(const char* addr) {
    delete[] address;  // ✅ 기존 주소 삭제
    if (addr == nullptr) {
        address = nullptr;
        return;
    }
    address = new char[strlen(addr) + 1];
    strcpy(address, addr);
}

void Person::copyMemo(const char* c_str) {
    delete[] memo_c_str;  // ✅ 기존 메모 삭제
    if (c_str == nullptr) {
        memo_c_str = nullptr;
        return;
    }
    memo_c_str = new char[strlen(c_str) + 1];
    strcpy(memo_c_str, c_str);
}

void Person::whatAreYouDoing() {
    cout << name << " is taking a rest." << endl;
}

bool Person::isSame(const string& name, int pid) {
    return (this->name == name && this->id == pid);
}

void Person::set(const string& name, int pid, double weight, bool married, const char* addr) {
    setName(name);
    set(pid);
    set(weight);
    set(married);
    setAddress(addr);
}

Person::Person(const Person& p)
    : name(p.name), id{p.id}, weight{p.weight}, married{p.married}, address(nullptr), memo_c_str(nullptr) {
    copyAddress(p.address);
    copyMemo(p.memo_c_str);
    cout << "Person::Person(const Person&):"; println();
}

void Person::inputMembers(istream& in) {
    string line;
    string t_name;
    string t_married_str;
    char colon;
    int t_id;
    double t_weight;
    bool t_married;

    getline(in, line);
    rawInput = line; // 그대로 저장 (출력용)
    istringstream iss(line);
    string addrPart;
    if (!(iss >> t_name >> t_id >> t_weight >> t_married_str >> colon) || colon != ':') {
        in.setstate(ios::failbit);
        return;
    }
    if (t_married_str == "true")
        t_married = true;
    else if (t_married_str == "false")
        t_married = false;
    else {
        in.setstate(ios::failbit);
        return;
    }
    getline(iss, addrPart, ':');
    const int MAX_ADDRESS_LEN = 100;
    if (addrPart.length() >= MAX_ADDRESS_LEN)
        addrPart = addrPart.substr(0, MAX_ADDRESS_LEN - 1);
    set(t_name, t_id, t_weight, t_married, addrPart.c_str());
}
// *********************************************************
// Persson member func end point
// *********************************************************

//*****************************************************************************
// VectorPerson class
//*****************************************************************************/
class VectorPerson
{
    static const int DEFAULT_SIZE = 10; // pVector의 디폴트 배열 원소 개수

    Person **pVector; // Person *pVector[]; Person에 대한 포인터들의 배열, 배열에 저장될 값이 Person *이다.
    int count;        // pVector 배열에 현재 삽입된 객체 포인터의 개수
    int allocSize;    // 할당 받의 pVector의 총 배열 원소의 개수

    void extend_capacity();

public:
    VectorPerson(int capacity = DEFAULT_SIZE): count(0), allocSize(capacity) {
        cout << "VectorPerson::VectorPerson(" << allocSize << ")" << endl;
        pVector = new Person*[allocSize]; // Person* 들의 배열을 위한 동적 메모리 할당
    }
    ~VectorPerson();

    Person* at(int index) const { 
    if (index < 0 || index >= count) 
        return nullptr;
        
    return pVector[index];
    }

    int     capacity()    const { return allocSize; }
    int     size()        const { return count; }
    bool    empty()       const { return count == 0; }
    void    clear()             { count = 0; }
    void    push_back(Person* p);
    void    erase(int index);
    void    insert(int index, Person* p);
};
//*****************************************************************************
// VectorPerson class end point
//*****************************************************************************

//*****************************************************************************
// VectorPerson objects
//*****************************************************************************

void VectorPerson::erase(int index) {
    // 경계 체크
    if (index < 0 || index >= count) return;

    // 원소 이동
    for (int i = index; i < count - 1; ++i) {
        pVector[i] = pVector[i + 1];
    }

    // 마지막 원소는 그대로 두고, count만 감소
    --count;
}

void VectorPerson::insert(int index, Person* p) {  
    if (count >= allocSize) {
        extend_capacity();
    }
    for (int i = count; i > index; --i) { // ✅ 올바른 방향
        pVector[i] = pVector[i-1];
    }
    pVector[index] = p;
    ++count;
}


VectorPerson::~VectorPerson() {
    delete[] pVector;  // 배열만 삭제 (각 Person 객체는 PersonManager에서 처리)
    cout << "VectorPerson::~VectorPerson(): pVector deleted" << endl;
}

void VectorPerson::push_back(Person* p) {
    if (count >= allocSize) {
        extend_capacity();
    }
    pVector[count++] = p;
}

void VectorPerson::extend_capacity() {
    int newAllocSize = allocSize * 2;
    Person** newVector = new Person*[newAllocSize];

    for (int i = 0; i < count; ++i) {
        newVector[i] = pVector[i];
    }

    delete[] pVector;

    pVector = newVector;
    allocSize = newAllocSize;

    cout << "VectorPerson: capacity extended to " << allocSize << endl;
}
//*****************************************************************************
// VectorPerson objects end point
//*****************************************************************************

//*****************************************************************************
// class UI start point
//*****************************************************************************
class UI {
private:
    static string line, emptyLine;

public:
    // static variable
    static bool echo_input;

    static string&          getEmptyLine()          { return emptyLine; }
    static const string&    getNext                 (const string& msg);
    static const string&    getNextLine             (const string& msg);
    static bool             checkInputError         (istream* pin, const string& msg);
    static int              getInt                  (const string& msg);
    static int              getIndex                (const string& msg, int size);
    static int              selectMenu              (const string& menuStr, int menuItemCount);

    static bool inputPerson(Person& p) {
        cout << "input person information:" << endl;
    
        p.setAddress(NULL);
    
        p.input(cin);
        if (!cin) {
            checkInputError(&cin, "Input-data format MISMATCHED\n");
            return false;
        }
        if (echo_input) p.println();
        return true;
    }
    
    static int getPositiveInt(const string& msg) {
        int value;
        while ((value = getInt(msg)) < 0)
            cout << "Input a positive INTEGER." << endl;
        return value;
    }
};
//*****************************************************************************
// class UI end point
//*****************************************************************************

// static variable init
bool UI::echo_input = false;
string UI::line, UI::emptyLine;

//*****************************************************************************
// class UI Member func start point
//*****************************************************************************

const string& UI::getNext(const string& msg) {
    cout << msg;
    cin >> line;
    if (echo_input) cout << line << endl;
    getline(cin, emptyLine);
    return line;
}

const string& UI::getNextLine(const string& msg) {
    cout << msg;
    getline(cin, line);
    if ((line.size() > 0) && (line.back() == '\r'))
        line.pop_back();
    if (echo_input) cout << line << endl;
    return line;
}

bool UI::checkInputError(istream* pin, const string& msg) {
    if (!(*pin)) {
        cout << msg;
        pin->clear();
        getline(*pin, emptyLine);
        return true;
    }
    return false;
}

int UI::getIndex(const string& msg, int size) {
    while (true) {
        int index = getPositiveInt(msg);
        if (0 <= index && index < size) return index;
        cout << index << ": OUT of selection range(0 ~ " << size - 1 << ")" << endl;
    }
}

int UI::getInt(const string& msg) {
    for (int value;;) {
        cout << msg;
        cin >> value;
        if (UI::echo_input) cout << value << endl;
        if (UI::checkInputError(&cin, "Input an INTEGER.\n"))
            continue;

        string dummy;
        getline(cin, dummy);
        return value;
    }
}
//*****************************************************************************
// class UI Member func end point
//*****************************************************************************

//*****************************************************************************
// public func start point
//*****************************************************************************
bool checkDataFormatError(istream& in) {
    return UI::checkInputError(&in, "Input-data format MISMATCHED\n");
}

bool inputPersonFromUser(Person* p) {
    cout << "input person information:" << endl;
    p->setAddress(nullptr);
    p->input(cin);
    if (UI::echo_input) p->println();
    return true;
}


int getPositiveInt(const string msg) {
    int value;
    while ((value = UI::getInt(msg)) < 0)
        cout << "Input a positive INTEGER." << endl;
    return value;
}

int getIndex(const string msg, int size) {
    while (true) {
        int index = getPositiveInt(msg);
        if (0 <= index  && index < size) return index;
        cout << index << ": OUT of selection range(0 ~ "
            << size-1 << ")" << endl;
    }
}
int selectMenu(const string menuStr, int menuItemCount) {
    cout << endl << menuStr;
    return getIndex("Menu item number? ", menuItemCount);
}
//*****************************************************************************
// public func end point
//*****************************************************************************

//*****************************************************************************
// string and Memo class
//*****************************************************************************
class Memo {
    string mStr; // 메모 문자열 저장

    size_t find_last_line();
    bool find_line(int line, size_t& start, size_t& len);

public:
    Memo(const char* c_str = nullptr) : mStr(c_str ? c_str : "") {}

    void displayMemo();
    void findString();
    void compareWord();
    void dispByLine();
    void deleteLine();
    void replaceLine();
    void scrollUp();
    void scrollDown();
    void inputMemo();
    void run();

    const char*  c_str() const { return mStr.c_str(); }
    void         c_str(const char* c_str) { mStr = (c_str ? c_str : ""); }

    string&     getNext(size_t& pos, string& word);
    string&     get_next_line(size_t& pos, string& line);
};


// 아래 R"( 와 )"는 그 사이에 있는 모든 문자를 하나의 문자열로 취급하라는 의미이다.
// 따라서 행과 행 사이에 있는 줄바꾸기 \n 문자도 문자열에 그대로 포함된다.
// 이런 방식을 사용하지 않으면 여러 행에 걸친 문자열을 만들려면 복잡해진다.
const char* memoData = R"(The Last of the Mohicans
James Fenimore Cooper
Author's Introduction
It is believed that the scene of this tale, and most of the information
necessary to understand its allusions, are rendered sufficiently 
obvious to the reader in the text itself, or in the accompanying notes.
Still there is so much obscurity in the Indian traditions, and so much
confusion in the Indian names, as to render some explanation useful.
Few men exhibit greater diversity, or, if we may so express it, 
greater antithesis of character, 
than the native warrior of North America.
)";

//*****************************************************************************
// string and Memo class end point
//*****************************************************************************

//*****************************************************************************
// string and Memo member func start point
//*****************************************************************************
bool Memo::find_line(int line_num, size_t& start, size_t& len) {
    start = 0;
    for (int i = 0; i < line_num; ++i) {
        start = mStr.find('\n', start);
        if (start == std::string::npos) return false;
        ++start;
    }
    size_t end = mStr.find('\n', start);
    len = (end == std::string::npos) ? mStr.size() - start : end - start + 1;
    return true;
}

size_t Memo::find_last_line() {
    for (size_t start = 0, pos = 0; true; start = pos) {
        pos = mStr.find('\n', start);
        if (pos == string::npos || ++pos >= mStr.size()) {
            return start;
        }
    }
}

void Memo::displayMemo() { // Menu item 1
    cout << "------- Memo -------" << endl;
    cout << mStr;
    if (mStr.length() > 0 && mStr[mStr.length()-1] != '\n')
        cout << endl; // 메모 끝에 줄바꾸기 문자가 없을 경우 출력
    cout << "--------------------" << endl;
}

void Memo::run() {
    using func_t = void (Memo::*)();
    func_t func_arr[] = {
        nullptr, &Memo::displayMemo, &Memo::findString,
        &Memo::compareWord, &Memo::dispByLine, &Memo::deleteLine,
        &Memo::replaceLine, &Memo::scrollUp, &Memo::scrollDown,
        &Memo::inputMemo
    };
    int menuCount = sizeof(func_arr) / sizeof(func_arr[0]);

    string menuStr =
        "++++++++++++++++++++++ Memo Management Menu +++++++++++++++++++++\n"
        "+ 0.Exit 1.DisplayMemo 2.FindString 3.CompareWord 4.DispByLine  +\n"
        "+ 5.DeleteLine 6.RepaceLine 7.ScrollUp 8.ScrollDown 9.InputMemo +\n"
        "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    if (mStr == "") mStr = memoData;

    while (true) {
        int menuItem = selectMenu(menuStr, menuCount);
        if (menuItem == 0) return;
        (this->*func_arr[menuItem])();
    }
}

// 사용자로부터 찾을 단어를 입력받고 메모 문자열에서 해당 단어의 출현 회수를 세어서 출력한다.
// 찾을 단어가 다른 단어의 일부분일지라도 모두 카운트하라.
void Memo::findString() {
    string word = UI::getNext("Word to find? ");
    int count = 0, len = word.length();
    size_t pos = 0;

    while (true) {
        pos = mStr.find(word, pos);  // word를 pos 위치부터 탐색
        if (pos == string::npos) break;  // 더 이상 찾을 수 없음
        ++count;
        pos += len;  // 다음 위치로 이동 (중복 방지)
    }

    cout << "Found count: " << count << endl;
}

string& Memo::getNext(size_t& pos, std::string& word) {
    size_t end = pos;
    while (end < mStr.size() && isspace(mStr[end])) ++end;

    if (ispunct(mStr[end])) {
        word = mStr.substr(end, 1);
        pos = end + 1;
    } else {
        size_t start = end;
        while (end < mStr.size() && !isspace(mStr[end]) && !ispunct(mStr[end])) ++end;
        word = mStr.substr(start, end - start);
        pos = end;
    }
    return word;
}


void Memo::compareWord() {
    std::string word = UI::getNext("Word to compare? ");
    int less = 0, same = 0, larger = 0;
    for (size_t pos = 0; ; ) {
        std::string next;
        if (getNext(pos, next).empty()) break;
        if (next < word) ++less;
        else if (next == word) ++same;
        else ++larger;
    }
    std::cout << "less: " << less << "\nsame: " << same << "\nlarger: " << larger << std::endl;
}

void Memo::dispByLine() { // Menu item 4
    cout << "--- Memo by line ---" << endl;

    size_t pos = 0;
    int lineNum = 0;

    while (pos < mStr.length()) {
        size_t next = mStr.find('\n', pos);
        if (next == string::npos) {
            cout << "[" << lineNum++ << "] " << mStr.substr(pos) << endl;
            break;
        } else {
            cout << "[" << lineNum++ << "] " << mStr.substr(pos, next - pos) << endl;
            pos = next + 1;
        }
    }

    // 마지막 개행이 없었으면, 빈 줄 출력 필요 없음
    cout << "--------------------" << endl;
}

void Memo::deleteLine() {
    size_t line_num = getPositiveInt("Line number to delete? ");
    size_t start, len;
    if (!find_line(line_num, start, len)) {
        std::cout << "Out of line range" << std::endl;
        return;
    }
    mStr.erase(start, len);
    dispByLine();
}

void Memo::replaceLine() {
    size_t line_num = getPositiveInt("Line number to replace? ");
    size_t start, len;
    if (!find_line(line_num, start, len)) {
        std::cout << "Out of line range" << std::endl;
        return;
    }
    string line = UI::getNextLine("Input a line to replace:\n");
    line += '\n';
    mStr.replace(start, len, line);
    dispByLine();
}

void Memo::scrollUp() {
    size_t start, len;
    if (!find_line(0, start, len)) return dispByLine();
    string first = mStr.substr(start, len);
    mStr.erase(start, len);
    if (!mStr.empty() && mStr.back() != '\n') mStr += '\n';
    mStr += first;
    dispByLine();
}

void Memo::scrollDown() {
    if (mStr.empty()) {
        dispByLine(); // ✅ 반드시 호출하여 라벨 출력
        return;
    }

    size_t last = find_last_line();
    size_t len = mStr.size() - last;

    string lastLine = mStr.substr(last, len);
    mStr.erase(last, len);
    mStr = lastLine + mStr;

    dispByLine(); // ✅ 항상 호출
}

void Memo::inputMemo() {
    mStr.clear(); // 기존 메모 삭제

    string line;
    cout << "--- Input memo lines, and then input empty line at the end ---" << endl;

    while (true) {
        getline(cin, line);
        if (UI::echo_input) cout << line << endl;

        if (line.empty()) break; // 빈 줄이면 종료

        mStr += line + '\n'; // 줄 끝에 '\n' 붙여 추가
    }
}
//*****************************************************************************
// string and Memo class objects end point
//*****************************************************************************

//*****************************************************************************
// Factory class
// ****************************************************************************
class Factory
{
public:
    // ✅ static으로 변경
    static Person* inputPerson(istream& in) {
        Person* p = new Person();
        p->input(in);
        if (checkDataFormatError(in)) {
            delete p;
            return nullptr;
        }
        if (UI::echo_input) p->println();
        return p;
    }
};
//*****************************************************************************
// Factory class
//*****************************************************************************

//*****************************************************************************
// CurrentUser class
//*****************************************************************************
class CurrentUser
{
    Person& rUser;
    Memo memo;
public:
    CurrentUser(Person& rUser) : rUser(rUser) {
        memo.c_str(rUser.getMemo());
    }

    void display();
    void setter();
    void getter();
    void set();
    void whatAreYouDoing();
    void isSame();
    void inputPerson();
    void run();
    void changePasswd();
    void manageMemo();
    void defaultParameter();
    void staticMember();
};
//*****************************************************************************
// CurrentUser class end point
//*****************************************************************************

//*****************************************************************************
// CurrentUser class objects
//*****************************************************************************
void CurrentUser::changePasswd() {
    string newPasswd = UI::getNext("New password: ");
    rUser.setPasswd(newPasswd);
    cout << "Password changed" << endl;
}

void CurrentUser::display() { // Menu item 1
    rUser.println();
}

void CurrentUser::getter() {  // Menu item 2
    cout << "name:" << rUser.getName()
        << ", id:" << rUser.getId()
        << ", weight:" << rUser.getWeight()
        << ", married:" << (rUser.getMarried() ? "true" : "false")
        << ", address:" << rUser.getAddress() << endl;
}

void CurrentUser::set() {  // 메뉴 4번
    Person* ps = new Person("rp");  // ✅ "pp" 대신 "rp"
    ps->set(ps->getName(), 
            rUser.getId(), 
            rUser.getWeight(), 
            !rUser.getMarried(), 
            rUser.getAddress());
    cout << "rp.set():";  // ✅ "pp->set()" 대신 "rp.set()"
    ps->println();
    delete ps;
}

void CurrentUser::setter() {
    Person* ps = new Person("rp");
    ps->set(rUser.getId());
    ps->set(rUser.getWeight());
    ps->set(rUser.getMarried());
    ps->setAddress(rUser.getAddress());
    cout << "rp.setMembers():";
    ps->println();
    delete ps;
}

void CurrentUser::whatAreYouDoing() {  // Menu item 5
    rUser.whatAreYouDoing();
}

void CurrentUser::isSame() { // Menu item 6
    rUser.println();
    cout << "isSame(\"user\", 1): " << (rUser.isSame("user", 1) ? "true" : "false") << endl;
}

void CurrentUser::inputPerson() {
    if (inputPersonFromUser(&rUser)) {
        display();
    }
}

void CurrentUser::defaultParameter() { // Menu item 10
    Person ps1;
    Person ps2("ps2");
    Person ps3("ps3", 3);
    Person ps4("ps4", 4, 70.4);
    Person ps5("ps5", 5, 70.5, true);
    Person ps6("ps6", 6, 70.6, true, "ps6 address");

    cout << "\nMemo m1;" << endl;
    Memo m1; // 메모 생성자에게 인자를 넘겨 주지 않은 경우
    m1.displayMemo();

    cout << "\nMemo m2(rUser.getMemo())" << endl;
    Memo m2(rUser.getMemo()); // 메모 생성자에게 인자를 넘겨 준 경우
    m2.displayMemo();
}

void CurrentUser::staticMember() { // Menu item 11
	string word1;
	word1 = UI::getNext("Input a word: ");
    cout << "UI::getNext(): " << word1 << endl << endl;

    UI ui;

    string word2;
    word2 = ui.getNext("Input a word: ");
    cout << "ui.getNext() : " << word2 << endl;
}

void CurrentUser::manageMemo() { // Menu item 9
    memo.run();
    rUser.setMemo(memo.c_str());
}

void CurrentUser::run() {
    using func_t = void (CurrentUser::*)();
    using CU = CurrentUser;
    func_t func_arr[] = {
        nullptr, &CU::display, &CU::getter, &CU::setter,
        &CU::set, &CU::whatAreYouDoing,
        &CU::isSame, &CU::inputPerson, &CU::changePasswd,
        &CU::manageMemo, &CU::defaultParameter,
		&CU::staticMember
    };
    int menuCount = sizeof(func_arr) / sizeof(func_arr[0]);
    string menuStr =
        "+++++++++++++++++++++ Current User Menu ++++++++++++++++++++++++\n"
        "+ 0.Logout 1.Display 2.Getter 3.Setter 4.Set 5.WhatAreYouDoing +\n"
        "+ 6.IsSame 7.InputPerson 8.ChangePasswd(4_2) 9.ManageMemo(4_3) +\n"
    	"+ 10.DefaultParameter(6_1) 11.StaticMember(6_1)                +\n"
        "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    while (true) {
        int menuItem = selectMenu(menuStr, menuCount);
        if (menuItem == 0) return;
        (this->*func_arr[menuItem])();
    }
}
//*****************************************************************************
// CurrentUser class end point
//*****************************************************************************

//*****************************************************************************
// PersonManager class
//*****************************************************************************
class PersonManager
{
    VectorPerson persons;
    // Factory factory;

    void deleteElemets();
    void printNotice(const string preMessage, const string postMessage);
    Person* findByName(const string name);

public:
    PersonManager(Person* array[], int len); // 6장에서 default 매개변수 설정
    ~PersonManager();
    void display();
    void append();
    void clear();
    void login();
    void run();
    void insert();
    void remove();
};
//******************************************************************************
// PersonManager class end point
//******************************************************************************

//******************************************************************************
// PersonManager member func start point
//******************************************************************************


Person* PersonManager::findByName(const string name) {
    for (int i = 0; i < persons.size(); ++i) {
        if (persons.at(i)->getName() == name) {
            return persons.at(i);
        }
    }
    cout << name << ": NOT found" << endl;
    return nullptr;
}

PersonManager::PersonManager(Person* array[], int len) {
    cout << "PersonManager::PersonManager(array[], len)" << endl;

    for (int i = 0; i < len; ++i)
    {
        Person* copy = new Person(*array[i]); // 복사 생성자 사용
        persons.push_back(copy);
    }

    display();
}

PersonManager::~PersonManager() {
    deleteElemets();
}

void PersonManager::deleteElemets() {
    int n = persons.size();
    for (int i = 0; i < n; ++i) {
        delete persons.at(i);  // 동적으로 생성한 객체 해제
    }
    persons.clear();  // count 0으로 초기화
}

void PersonManager::display() { // Menu item 1
    int count = persons.size();
    cout << "display(): count " << count << endl;
    for (int i = 0; i < count; ++i) {
        cout << "[" << i << "] ";
        persons.at(i)->println();
    }
    cout << boolalpha; // 추가

    cout << "empty():" << persons.empty() << ", size():" << persons.size()
        << ", capacity():" << persons.capacity() << endl;
}

void PersonManager::printNotice(const string preMessage, const string postMessage) {
    cout << preMessage;
    cout << " [person information] ";
    cout << postMessage << endl;
}

void PersonManager::append() {  // Menu item 2
    int count = getPositiveInt("The number of persons to append? ");
    printNotice("Input " + to_string(count), ":");
    for (int i = 0; i < count; ++i) {
        Person* p = Factory::inputPerson(cin); // ✅ static 방식 호출
        if (p) persons.push_back(p);
    }
    display();
}

void PersonManager::clear() { // Menu item 3
    deleteElemets();
    display();
}

void PersonManager::login() {
    string name = UI::getNext("user name: ");
    Person* p = findByName(name);
    if (p == nullptr) return;

    string passwd = UI::getNextLine("password: ");
    if (passwd != p->getPasswd())
        cout << "WRONG password!!" << endl;
    else
        CurrentUser(*p).run();
}

void PersonManager::insert() { // Menu item 5
    int index = 0;
    if (!persons.empty()) {
        index = getPositiveInt("Index to insert in front? ");
        if (index > persons.size()) {
            cout << index << ": OUT of selection range(0 ~ " << persons.size() << ")" << endl;
            return;
        }
    }
    cout << "Input [person information] to insert:" << endl;

    Person* p = Factory::inputPerson(cin);
    if (p == nullptr) return;

    persons.insert(index, p);

    display();
}

void PersonManager::remove() {
    if (persons.empty()) {
        cout << "No entry to remove" << endl;
        return;
    }

    int index = UI::getIndex("Index to delete? ", persons.size());

    delete persons.at(index);
    persons.erase(index);

    display();
}

void PersonManager::run() {
    cout << "PersonManager::run() starts" << endl; // 여기에 위치해야 함

    using func_t = void (PersonManager::*)();
    using PM = PersonManager;
    func_t func_arr[] = {
        nullptr, 
        &PM::display, 
        &PM::append, 
        &PM::clear, 
        &PM::login,
        &PM::insert,
        &PM::remove
    };
    int menuCount = sizeof(func_arr) / sizeof(func_arr[0]);
    string menuStr =
        "====================== Person Management Menu ===================\n"
        "= 0.Exit 1.Display 2.Append 3.Clear 4.Login(CurrentUser, ch6)   =\n"
        "= 5.Insert(6_2) 6.Delete(6_2)                                   =\n"
        "=================================================================\n";

    while (true) {
        int menuItem = selectMenu(menuStr, menuCount);
        if (menuItem == 0) {
            cout << "PersonManager::run() returned" << endl;
            return;
        }
        (this->*func_arr[menuItem])();
    }
}

//******************************************************************************
// PersonManager objects end point
//******************************************************************************

//******************************************************************************
// MultiManager class
//******************************************************************************
class MultiManager {
    static const int personCount = 5;

    // 정적 Person 배열 초기화
    Person persons[personCount] = {
        Person("p0", 10, 70.0, false, "Gwangju Nam-gu Bongseon-dong 21"),
        Person("p1", 11, 61.1, true,  "Jong-ro 1-gil, Jongno-gu, Seoul"),
        Person("p2", 12, 52.2, false, "1001, Jungang-daero, Yeonje-gu, Busan"),
        Person("p3", 13, 83.3, true,  "100 Dunsan-ro Seo-gu Daejeon"),
        Person("p4", 14, 64.4, false, "88 Gongpyeong-ro, Jung-gu, Daegu"),
    };

    // 포인터 배열로 변환
    static const int allPersonCount = personCount;
    Person* allPersons[allPersonCount] = {
        &persons[0], &persons[1], &persons[2], &persons[3], &persons[4],
    };

    // PersonManager에 포인터 배열 전달
    PersonManager personMng{ allPersons, allPersonCount };

public:
    void run() {
        personMng.run();  // 메뉴 기반 Person 관리 기능 실행
    }
};
//******************************************************************************
// MultiManager class end point
//******************************************************************************

//******************************************************************************
// ClassAndObject class
//******************************************************************************
class ClassAndObject
{
    void defualConstructor() { // Menu item 1
        Person P;
    }
    void constructor() { // Menu item 2: 지역객체의 다양한 생성자 및 소멸자 실행
        Person ps1;
        Person ps2("ps2");
        Person ps3("ps3", 3, 70.3, true, "ps3 address");
    }
    void construcor_destructor_inner_inner() {
        cout << "\n--- construcor_destructor_inner_inner() begins ---" << endl;
        Person ps3("ps3");
        cout << "\n- if begins -" << endl;
        if (true) {
            Person ps4("ps4");
        }
        cout << "- if ends -\n" << endl;
        cout << "- temporary object begins -" << endl;
        Person("temp_ps_1"); // 임시객체(이름 없는 객체) 성성 및 소멸
        cout << endl;
        Person("temp_ps_2").setName("TEMP_PS_2"); // 임시객체 생성,
                                                // setName() 호출, 임시객체 소멸
        cout << "- temporary object ends -\n" << endl;
        Person ps5("ps5");
    }
    void construcor_destructor_inner() {
        cout << "\n--- construcor_destructor_inner() begins ---" << endl;
        Person ps2("ps2");
        construcor_destructor_inner_inner();
        cout << "--- construcor_destructor_inner_inner() returned ---\n" << endl;
        Person ps6("ps6");
    }
    void construcorDestructor() { // Menu item 3
        Person ps1("ps1");
        construcor_destructor_inner();
        cout << "--- construcor_destructor_inner() returned ---\n" << endl;
    }
    void global_static_local_objects_inner() {
        cout << "\n--- global_static_local_objects_inner() begins ---" << endl;
    }

    class Init1 {
        Person p;
        int i = 0;
        int j = 0;
        double d = 0.0;
        char name[5] = "";
    public:
        void print() {
            cout << "Init1 i: " << i << ", j: " << j << ", d: " << d << ", name: " << name << endl;
        }
    };

    class Init2 {
        Person p;
        int i = 6; // 수정됨
        int j = 6; // 추가 수정
        double d = 0.0;
    public:
        void print() {
            cout << "Init2 i: " << i << ", j: " << j << ", d: " << d << endl;
        }
    };

    class Init3 {
        Person p { "p-Init3" };
        int i = 3;
        int j = 6;
        double d = 0.0;
    public:
        void print() {
            cout << "Init3 i: " << i << ", j: " << j << ", d: " << d << endl;
        }
    };

    class Init4 {
        Person p;
        int i;
        int j;
        double d;
    public:
        Init4(): p{"p-Init4-head"}, i{4}, j{6}, d{0.0} {}
        void print() {
            cout << "Init4 i: " << i << ", j: " << j << ", d: " << d << endl;
        }
    };

    class Init5 {
        Person p { "p-Init5" };
        int i;
        int j;
        double d;
    public:
        Init5(): p{"p-Init5-head"}, i{5}, j{6}, d{0.0} {}
        void print() {
            cout << "Init5 i: " << i << ", j: " << j << ", d: " << d << endl;
        }
    };

    class Init6 {
        Person p;
        int i, j;
        double d;
    public:
        // 여기서는 p.set(...) 대신 편의상 p.setName(...)을 호출했다.
        Init6() { i = j = 6; d = 0; p.setName("p-Init6-body"); p.println(); }
        void print() { 
            cout << "Init6 i: " << i << ", j: " << j << ", d: " << d << endl; 
        }
    };

    void memberInitialization() { // Menu item 5
        int i = 0, i2 = i; i = i2; // 의미 없는 문장이지만, 삭제하지 말 것
        
        // 임시객체 생성 후 print()를 호출하고 바로 소멸된다.
        Init1().print(); cout << endl;
        Init2().print(); cout << endl;
        Init3().print(); cout << endl;
        Init4().print(); cout << endl;
        Init5().print(); cout << endl;
        Init6().print();
    }
//******************************************************************************
// sub class Parameter class start point
//******************************************************************************
    class Parameter {
    public:
        // 아래 각 함수 선언에서 const가 있는 매개변수는 해당 함수에서 객체 p를 수정하지 않는다는 의미이고,
        // const가 없는 매개변수는 해당 함수에서 객체 p를 수정할 수 있다는 의미임
        // 함수 호출한 곳에서 함수의 실행 결과를 매개변수를 통해 넘겨 받아야 하는 경우는 const가 없어야 함
        void normalValue(Person p)           { cout << "normalValue(Person p)" << endl; }
        void constValue(const Person p)      { cout << "constValue(const Person p)" << endl; }
        void normalReference(Person& p)      { cout << "normalReference(Person& p)" << endl; }
        void constReference(const Person& p) { cout << "constReference(const Person& p)" << endl; }

        void printStr(string& s)             { cout << "printStr(string& s): " << s << endl; }
        void printConstStr(const string& s)  { cout << "printConstStr(const string& s): " << s << endl; }
        void printPerson(const Person& p) { // const Person p로 선언해도 동일한 결과가 나옴
            cout << "printPerson(const Person& p)" << endl;
            p.println();
            // 위 const Person& p 선언의 의미: 이 함수에서 객체 p를 수정하지 않겠다는 의미임
            // 따라서 아래의 p.setName("const-value")처럼 p의 멤버함수를 호출하면 에러로 처리함; 
            // 이유는 이 함수가 const 객체인 p의 멤버 name를 수정하기기 때문에.

            /* p.setName("const-value"); */ // 명백히 이름을 수정하는 것이므로 컴파일 에러 발생
            /* cout << p.getName() << " " << p.getId() << " " << p.getWeight() << " " <<
                    p.getMarried() << " :" << ((p.getAddress()==nullptr)?"":p.getAddress()) <<
                    ":" << endl; */

            // 주석을 풀 경우 발생하는 컴파일 에러는 매개변수가 const로 선언되었기 때문에  
            // 발생하는 것이다. 컴파일러 입장에서는 위 멤버함수들이 p의 멤버를 수정하는지 아니면 
            // 읽기만하는지 알 수 없기 때문에 컴파일 시 에러로 처리함; 
        }
    };
//******************************************************************************
// sub class Parameter class end point
//******************************************************************************    
    Parameter cp;

    void normalParameter() {
        cout << "normalParameter()" << endl;
        cout << "Person p1(\"p1-name\")" << endl;

        // 요점: 아래 Person p1처럼 p1이 일반적인 객체일 경우 
        //      함수의 매개변수 타입에 상관없이 이 객체를 함수 인자로 넘겨 줄 수 있다.
        Person p1("p1-name");

        cp.normalValue(p1);     // 복사생성자 통해 매개변수 p에 p1을 복사해서 넘겨 줌
        cp.constValue(p1);      // 복사생성자 통해 매개변수 p에 p1을 복사해서 넘겨 줌
        cp.normalReference(p1); // 매개변수 p에 단순히 p1의 참조만 넘겨 줌
        cp.constReference(p1);  // 매개변수 p에 단순히 p1의 참조만 넘겨 줌
    }

    void constParameter() {
        cout << "constParameter()" << endl;
        cout << "const Person p2(\"const-p2-name\")" << endl;
    
        const Person p2("const-p2-name");
    
        // ❌ 아래 코드를 지워야 합니다!!!
        // normalParameter();
    
        cp.normalValue(p2); 
        cp.constValue(p2);  
        //cp.normalReference(p2); // 컴파일 에러라 주석
        cp.constReference(p2); 
    }

    void temporaryParameter() {
        cout << "temporaryParameter()" << endl;

        // 요점: 아래의 Person("Person-name")는 임시객체가 생성되며, 
        //      이 임시객체는 컴파일러에 의해 const로 취급된다.
        //      따라서 이 임시객체는 위 [문제 10]의 const p2와 동일하게 취급된다.

        cp.normalValue(Person("Person-name"));       // 불필요한 객체 복사 일어남
        cp.constValue(Person("Person-name"));        // 불필요한 객체 복사 일어남
        //cp.normalReference(Person("Person-name")); // 컴파일 에러 발생
        cp.constReference(Person("Person-name"));    // 임시 객체 참조만 넘어감

        // 결론: 일반적으로 객체는 함수의 매개변수로 value로 복사해서 넘기지 않고 객체의 참조를 넘긴다.
        //      이유는 객체의 크기가 커지면 복사 오버헤드가 발생하기 때문이다. 
        //      그런데 함수의 매개변수가 const가 아닌 일반 참조 변수로 선언된 경우 
        //      그 함수에서 이 참조변수를 통해 원본 객체를 수정할 수 있기 때문에
        //      const p2 또는 위 임시객체(const 취급)와 같은 객체들을 함수 인자로 넘길 수 없다. 
        //      따라서 [만약 함수 내에서 매개변수인 객체를 수정하지 않는다면]
        //      일반 & 매개변수로 선언하기 보다는 const &로 습관적으로 선언하는 것이 유리하다.
        //      (이렇게 선언하면 위 cp.constReference()처럼 
        //       임시객체의 참조를 함수의 매개변수로 바로 넘길 수 있다.)
    }

    void stringParameter() {
        cout << "stringParameter()" << endl;

        string s("name1"); // string s = "name1"; 과 동일

        cp.printStr(s);
        cp.printConstStr(s);
        // 아래는 임시 string 객체 생성 (임시객체는 항상 const): 컴파일 에러
        //cp.printStr(string("name")); 
        cp.printConstStr(string("name2")); // const 임시 객체 생성
        // 아래 "name"은 자동으로 임시 string("name") 객체 생성: 컴파일 에러
        //cp.printStr("name"); 
        cp.printConstStr("name3"); // const 임시 객체 생성
        // 결론: 함수의 매개변수로 "name3"처럼 문자열을 직접 넘겨 주고 싶으면
        //      함수 매개변수를 const string& 으로 선언해야 한다. string&로 선언시 에러.
        //      함수 내에서 매개변수 객체를 수정하지 않을 경우 습관적으로 항상 이렇게 선언하라.
        // 매개변수를 const string으로 선언해도 되지만 이 경우 문자열 전체가 복사되므로 비효율적임
    }

    void parameters() {
        normalParameter();
        cout << endl;
        constParameter();
        cout << endl;
        temporaryParameter();
        cout << endl;
        stringParameter();
        cout << endl;
        cp.printPerson(Person("name", 10, 77.7, true, "address"));
    }

    void globalStaticLocalObjects() { // Menu item 4
        global_static_local_objects_inner();
        cout << "--- global_static_local_objects_inner() returned ---" << endl;
        global_static_local_objects_inner();
        cout << "--- global_static_local_objects_inner() returned ---" << endl;
    }
    public:
    void run() {
        using CO = ClassAndObject;
        using func_t = void (CO::*)();

        func_t func_arr[] = {
            nullptr,
            &CO::defualConstructor,
            &CO::constructor,
            &CO::construcorDestructor,
            &CO::globalStaticLocalObjects,
            &CO::memberInitialization,
            &CO::parameters
        };

        int menuCount = sizeof(func_arr) / sizeof(func_arr[0]);

        string menuStr =
            "+++++++++++ Person Class And Object Menu ++++++++++++\n"
            "+ 0.Exit 1.DefualConstructor 2.Constructor          +\n"
            "+ 3.ConstrucorDestructor 4.GlobalStaticLocalObjects +\n"
            "+ 5.MemberInitialization 6.constParameter           +\n"
            "+++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

        while (true) {
            int menuItem = selectMenu(menuStr, menuCount);
            if (menuItem == 0) return;
            (this->*func_arr[menuItem])();
        }
    }
};
//******************************************************************************
// MultiManager class end point
//******************************************************************************

/******************************************************************************
 * ch5_2: AllocatedMember, new을 이용한 동적 메모리 할당한 멤버 취급
 ******************************************************************************/
class AllocatedMember {
    Person  u;
    Memo    memo;

    void set_print_address(Person& p, const char* address) {
        cout << "p.setAddress(" << (address ? address : "") << ")" << endl;
        p.setAddress(address);
        p.println();
        cout << endl;
    }

    void print_memo(Person& p) {
        cout << "------ " << p.getName() << " memo ------" << endl;
        const char *pmemo = p.getMemo();
        cout << (pmemo ? pmemo : "");
    
        if (pmemo && strlen(pmemo) > 0 && pmemo[strlen(pmemo) - 1] != '\n')
            cout << endl;
    
        cout << "--------------------" << endl << endl;
    }

    void set_print_memo(Person& p, const char* memo) {
        cout << "p.setMemo(memo)" << endl;
        p.setMemo(memo);
        print_memo(p);
    }

    void changeAddress() {
        Person p("p", 1, 70, true, "Gwangju");
        set_print_address(p, "short address");
        set_print_address(p, "middle length Address, Seoul");
        set_print_address(p, "long length Address Seoul Mapo-gu Korea");
        set_print_address(p, u.getAddress());
    }

    void changeMemo() {
        Person p("p", 1, 70, true, "Gwangju");
        set_print_memo(p, "short memo\n");
        set_print_memo(p, "middle long memo: The Last of the Mohicans\n");
        set_print_memo(p, u.getMemo());
    }

    void manageMemo() {
        memo.c_str(u.getMemo());
        memo.run();
        cout << "\nmemo.run() returned" << endl;
        u.setMemo(memo.c_str());
        print_memo(u);
    }

    Person call_by_value_and_return_value(Person p) {
        cout << "p.setName(p)" << endl;
        p.setName("p");
        cout << "p2: ";
        return p;
    }

    void copyConstructor() {
        cout << "u: "; u.println();
        print_memo(u);

        cout << "Person p1(u)" << endl;
        cout << "p1: ";
        Person p1(u);
        p1.setName("p1");
        p1.println();
        print_memo(p1);

        cout << "Person p2 = call_by_value_and_return_value(p1)" << endl;
        cout << "p: ";
        Person p2 = call_by_value_and_return_value(p1);
        cout << "call_by_value_and_return_value(p1) returned\n" << endl;
        cout << "p2.setName(p2)" << endl;
        p2.setName("p2");
        p2.println();
        print_memo(p2);
        cout << "copyConstructor() returns" << endl;
    }

    void nullptrMember() { // Menu Item 5
        u.println();
        print_memo(u);
        cout << "set address = memo_c_str = nullptr" << endl;
        u.setAddress(nullptr);
        u.setMemo(nullptr);
        u.println();
        print_memo(u);

        cout << "memo.c_str(u.getMemo())" << endl;
        memo.c_str(u.getMemo());
        memo.displayMemo();

        cout << endl << "u.setMemo(memo.c_str())" << endl;
        u.setMemo(memo.c_str());
        print_memo(u);
    }

    void inputPerson() { // Menu Item 6
        cout << "u: "; u.println();
        while (!inputPersonFromUser(&u)) ;  // 사용자 입력 오류 시 재입력
        cout << "u: "; u.println();
    }

public:
    AllocatedMember():
        u("u", 1, 70, true, "NAMDAEMUN-RO 123, JONGNO-GU, SEOUL, KOREA") {
        u.setMemo("It is believed that the Aborigines of the American continent");
    }

    void run() {
        using func_t = void (AllocatedMember::*)();
        func_t func_arr[] = {
            nullptr,
            &AllocatedMember::changeAddress,
            &AllocatedMember::changeMemo,
            &AllocatedMember::manageMemo,
            &AllocatedMember::copyConstructor,
            &AllocatedMember::nullptrMember,
            &AllocatedMember::inputPerson
        };

        int menuCount = sizeof(func_arr) / sizeof(func_arr[0]);
        string menuStr =
            "++++++++++++++++ Allocated Member Menu ++++++++++++++++\n"
            "+ 0.Exit 1.ChangeAddress 2.ChangeMemo 3.UsingMemoMenu +\n"
            "+ 4.CopyConstructor 5.NullptrMember 6.inputPerson     +\n"
            "+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

        while (true) {
            int menuItem = selectMenu(menuStr, menuCount);
            if (menuItem == 0) return;
            if (menuItem >= menuCount || func_arr[menuItem] == nullptr) {
                cout << menuItem << ": OUT of selection range(0 ~ " << menuCount - 1 << ")" << endl;
                continue;
            }
            (this->*func_arr[menuItem])();
        }
    }
};
//******************************************************************************
//* ch5_2: AllocatedMember, new을 이용한 동적 메모리 할당한 멤버 취급
//******************************************************************************

//******************************************************************************
// CopyConstructor class
//******************************************************************************
class CopyConstructor {
    Person u;
    Person backup;

public:
    CopyConstructor() : u("u", 1, 70, true, "Gwangju"), backup(u) { }

    Person return_temporary_object();
    Person return_member_object();
    Person return_local_object();
    Person return_value();
    Person& return_reference();
    Person* return_address();
    void inputPerson();
    void returnDataType();
    void return_address_test();
    void return_reference_test();
    void return_value_test();
    void function_argument(Person a);
    void call_by_reference(Person &p);
    void call_by_value(Person p);
    void call_by_address(Person *p);
    void explicitCopyConstructor();
    void referenceVariable();
    void function_argument();
    void implicitCopyConstructor();
    void temporaryObject();
    void functionParameterType();
    void run();                     // 메뉴 실행 함수
};
//******************************************************************************
// CopyConstructor class end point
//******************************************************************************

//******************************************************************************
// CopyConstructor member func start point
//******************************************************************************
Person CopyConstructor::return_value() {                   // return value
    return u;
}

void CopyConstructor::return_value_test() { // Menu item 6-1
    cout << "--- return_value_test() ---" << endl;
    cout << "call return_value()" << endl;
    cout << "p: ";

    Person p = return_value();

    cout << "return_value() returned" << endl;
    cout << "p: "; p.println();
    cout << "p.set(p, 2, 80, false, Seoul)" << endl;
    p.set("p", 2, 80, false, "Seoul");
    cout << "p: "; p.println();
    cout << "u: "; u.println();
}

Person& CopyConstructor::return_reference() {                  // return reference
    return u;
}

void CopyConstructor::return_reference_test() {
    cout << "--- return_reference_test() ---" << endl;
    cout << "call return_reference()" << endl;
    cout << "p: ";

    Person p = return_reference();

    cout << "return_reference() returned" << endl;
    cout << "p.set(p, 2, 80, false, Seoul)" << endl;
    p.set("p", 2, 80, false, "Seoul");
    cout << "p: "; p.println();
    cout << "u: "; u.println();
    cout << endl;

    cout << "call return_reference()" << endl;

    Person& r = return_reference();
    cout << "return_reference() returned" << endl;
    cout << "u: "; u.println();
    cout << "r.set(p, 2, 80, false, Seoul)" << endl;
    r.set("r", 2, 80, false, "Seoul");
    cout << "r: "; r.println();
    cout << "u: "; u.println();
    u.assign(backup); // 수정: 얕은 대입 제거
}

Person* CopyConstructor::return_address() {                  // return address
    return &u;
}

void CopyConstructor::return_address_test() { // Menu item 6-3
    cout << "--- return_address_test() ---" << endl;
    cout << "call return_address()" << endl;

    Person* p = return_address();

    cout << "return_address() returned" << endl;
    cout << "p: "; p->println();
    cout << "u: "; u.println();
    cout << "p.set(p, 2, 80, false, Seoul)" << endl;
    p->set("p", 2, 80, false, "Seoul");
    cout << "p: "; p->println();
    cout << "u: "; u.println();
    u.assign(backup);
}

void CopyConstructor::returnDataType() { // Menu item 6
    return_value_test();        cout << endl;
    return_reference_test();    cout << endl;
    return_address_test();
}
void CopyConstructor::functionParameterType() {
    cout << "call_by_value" << endl;
    call_by_value(u); // 복사본 전달 (복사생성자 호출)
    cout << endl;

    cout << "call_by_reference" << endl;
    call_by_reference(u); // 참조 전달
    cout << endl;

    cout << "call_by_address" << endl;
    call_by_address(&u); // 주소 전달 (포인터)
    cout << endl;
}

void CopyConstructor::call_by_reference(Person &p) {
    cout << "p: "; p.println();
    cout << "u: "; u.println();
    cout << "p.set(p, 2, 80, false, Seoul)" << endl;
    p.set("p", 2, 80, false, "Seoul");
    cout << "p: "; p.println();
    cout << "u: "; u.println();
    u.assign(backup); // 수정: 얕은 대입 제거
}

void CopyConstructor::call_by_address(Person *p) {
    cout << "p: "; p->println();
    cout << "u: "; u.println();
    cout << "p->set(p, 2, 80, false, Seoul)" << endl;
    p->set("p", 2, 80, false, "Seoul");
    cout << "p: "; p->println();
    cout << "u: "; u.println();
    u.assign(backup); // 수정: 얕은 대입 제거
}

void CopyConstructor::call_by_value( Person p ) { // Menu item 5-1: call by value: 복사생성자에 의해 복사됨
    cout << "p: "; p.println();
    cout << "u: "; u.println();
    cout << "p.set(p, 2, 80, false, Seoul)" << endl;
    p.set("p", 2, 80, false, "Seoul");
    cout << "p: "; p.println();      // p는 u과 다른 메모리를 사용하는 객체임
    cout << "u: "; u.println(); // u은 영향을 받지 않음
    // 함수 리턴 시 매개변수 p 객체의 소멸자 함수가 호출됨
}
Person CopyConstructor::return_local_object() { // Menu item 4-1
    Person pL("pL", 0, 70, true, "Gwangju Nam-gu");
    cout << "return_local_object() returns pL" << endl;
    return pL;
}
Person CopyConstructor::return_temporary_object() { // Menu item 4-2
    cout << "return_temporary_object() returns Person(pT, 0, 70, true, Gwangju Nam-gu)" << endl;
    return Person("pT", 0, 70, true, "Gwangju Nam-gu");
}
void CopyConstructor::temporaryObject() { // Menu item 4
    cout << "temporary object 1: Person(p0, 10, 70, true, Gwangju)" << endl;
    Person("p0", 10, 70, true, "Gwangju");

    cout << "\ntemporary object 2: Person(p1, 11, 60, false, Seoul).println()" << endl;
    Person("p1", 11, 60, false, "Seoul").println();

    cout << "\nreturn_member_object().println()" << endl;
    return_member_object().println();
    cout << "return_member_object() returned" << endl;

    cout << "\nreturn_local_object().println()" << endl;
    return_local_object().println();
    cout << "return_local_object() returned" << endl;

    cout << "\nPerson pL = return_local_object()" << endl;
    Person pL = return_local_object();
    cout << "return_local_object() returned" << endl;
    pL.println();

    cout << "\nreturn_temporary_object().println()" << endl;
    return_temporary_object().println();
    cout << "return_temporary_object() returned" << endl;

    cout << "\nPerson pT = return_temporary_object()" << endl;
    Person pT = return_temporary_object();
    cout << "return_temporary_object() returned" << endl;
    pT.println();
}

void CopyConstructor::implicitCopyConstructor() { // Menu item 3
    cout << "u: "; u.println();

    cout << "\nimplicit copy constructor 1: operator =" << endl;
    cout << "Person p = u" << endl;
    cout << "p: ";
    Person p = u; // 묵시적 복사생성자

    cout << "p.setName(p)" << endl;
    p.setName("p");
    cout << "p: "; p.println();

    cout << "\nimplicit copy constructor 2: function argument" << endl;
    cout << "call function_argument(u)" << endl;
    function_argument(u);
    cout << "function_argument(u) returned" << endl;

    cout << "\nimplicit copy constructor 3: return object" << endl;
    cout << "call return_member_object().println()" << endl;
    return_member_object().println();
    cout << "return_member_object() returned" << endl;
}

Person CopyConstructor::return_member_object() { // Menu item 3-2
    return u; // 묵시적으로 복사생성자 호출됨
}

void CopyConstructor::function_argument(Person a) {
    cout << "a: "; a.println();
    cout << "a.setName(a)" << endl;
    a.setName("a");
    cout << "a: "; a.println();
}

void CopyConstructor::explicitCopyConstructor() {
    cout << "u: "; u.println();

    Person p(u);
    p.setName("p");
    p.set(2);
    p.set(80);
    p.set(false);
    p.setAddress("Seoul");

    cout << "u: "; u.println();
    cout << "p: "; p.println();
    // p는 함수 종료 시 자동 소멸
}

void CopyConstructor::referenceVariable() { // Menu item 2
    cout << "p: ";
    Person p(u);  // u를 복사하여 p 생성 (복사생성자 호출)

    Person& r = p;

    cout << "p: "; p.println();
    cout << "r: "; r.println();

    r.setName("r");
    r.set(2);
    r.set(80);
    r.set(false);
    r.setAddress("Seoul");

    cout << "p: "; p.println();
    cout << "r: "; r.println();

    p.setName("p");
    p.set(1);
    p.set(70);
    p.set(true);
    p.setAddress("Gwangju");

    cout << "p: "; p.println();
    cout << "r: "; r.println();

    // r은 참조이므로 객체 p와 동일한 메모리를 공유 → 항상 동일한 값 출력됨
}

void CopyConstructor::inputPerson() {
    cout << "u: "; u.println();
    while (true) {
        if (!inputPersonFromUser(&u)) {
            cout << "Input-data format MISMATCHED" << endl;
            continue;
        }
        break;
    }
    backup.assign(u); // 수정: 얕은 대입 제거
    cout << "u: "; u.println();
}


void CopyConstructor::run() {
    using CC = CopyConstructor;
    using func_t = void (CopyConstructor::*)();
    func_t func_arr[] = {
        nullptr,
        &CC::explicitCopyConstructor,
        &CC::referenceVariable,
        &CC::implicitCopyConstructor,
        &CC::temporaryObject,
        &CC::functionParameterType,
        &CC::returnDataType,
        &CC::inputPerson
    };
    int menuCount = sizeof(func_arr) / sizeof(func_arr[0]);

    string menuStr =
    "+++++++++ Reference And Copy Constructor Menu ++++++++++\n"
    "+ 0.Exit 1.ExplicitCopyConstructor 2.ReferenceVariable +\n"
    "+ 3.ImplicitCopyConstructor 4.TemporaryObject          +\n"
    "+ 5.FunctionParameterType 6.FunctionReturnType         +\n"
    "+ 7.inputPerson                                        +\n"
    "++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    while (true) {
        int menuItem = selectMenu(menuStr, menuCount);
        if (menuItem == 0) return;
        if (menuItem >= menuCount || func_arr[menuItem] == nullptr) {
            cout << menuItem << ": OUT of selection range(0 ~ " << menuCount - 1 << ")" << endl;
            continue;
        }
        (this->*func_arr[menuItem])();
    }
}

//******************************************************************************
// CopyConstructor member func end point
//******************************************************************************

//******************************************************************************
// MainMenu class
//******************************************************************************
class MainMenu{
public:
    void run() {
        int menuCount = 5; // 상수 정의
        string menuStr =
"******************************* Main Menu *********************************\n"
"* 0.Exit 1.PersonManager(ch3_2, 4, 6)                                     *\n"
"* 2.Class:Object(ch3_1) 3.CopyConstructor(ch5_1) 4.AllocatedMember(ch5_2) *\n"
"***************************************************************************\n";
        while (true) {
            int menuItem = selectMenu(menuStr, menuCount);
            if (menuItem == 0) break;
            switch(menuItem) {
            case 1: MultiManager().run();             break;
            case 2: ClassAndObject().run();           break;
            case 3: CopyConstructor().run();          break;
            case 4: AllocatedMember().run();          break;
            }
        }
        cout << "Good bye!!" << endl;
    }
};
//******************************************************************************
// MainMenu class end point
//******************************************************************************

//******************************************************************************
// Run func
//******************************************************************************

void run() {
    MainMenu().run();
}

#if AUTOMATIC_ERROR_CHECK
#include "check_error.h"
#endif

int main() {
#if AUTOMATIC_ERROR_CHECK
    evaluate(false);   // 각 문제에 대해 단순히 O, X만 확인하고자 할 때는 false
#else
    run();
#endif
}