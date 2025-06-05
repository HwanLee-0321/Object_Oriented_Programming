#include <iostream>
#include <cstring> // For strcpy, strlen
#include <string>
#include <sstream> // For istringstream
#include <iomanip> // For boolalpha
#include <limits>  // Required for std::numeric_limits

#define AUTOMATIC_ERROR_CHECK false
using namespace std;

/*
 *
 * + Person을 상속 받는 Student, Worker 클래스 추가
 * + MultiManager: 배열 데이타 추가, 멤버 함수 추가 (Note: MultiManager changes are mostly from ch7_3, this problem focuses on Student/Worker/Inheritance)
 * + Inheritance 클래스 추가
 * + VectorPerson의 메모리 확장 관련 출력문들 주석처리
 */

// Forward Declarations
class Person;
class Student;
class Worker;
class UI;
class MainMenu;
class Memo;

// *********************************************************
// Person class
// *********************************************************
class Person
{
    string      name;
    int         id;
    double      weight;
    bool        married;
    char* address;
    string      rawInput;
    string      passwd;
    char* memo_c_str;

protected:
    void inputMembers        (istream& in);
    void printMembers(ostream& out) const;
    void copyAddress         (const char* address_val);
    void copyMemo            (const char* c_str_val);
public:
    // 생성자
    Person(const string name_p = "", int id_p = 0, double weight_p = 0.0,
           bool married_p = false, const char* address_p = nullptr)
      : name(name_p), id(id_p), weight(weight_p), married(married_p),
        address(nullptr), memo_c_str(nullptr)
    {
        copyAddress(address_p);
        // 코드 추가 5.2
        cout << "Person::Person(...):"; printMembers(cout); cout << endl;
    }
    Person(const Person& p);
    virtual ~Person() {
        // 코드 추가 5.2
        cout << "Person::~Person():"; printMembers(cout); cout << endl;
        delete[] address;
        address = nullptr;
        delete[] memo_c_str;
        memo_c_str = nullptr;
    }

    // setter 함수
    void set(const string& name_val, int pid_val, double weight_val, bool married_val, const char* addr_val);
    void setName(const string& name_val)       { this->name = name_val; }
    void set(int pid_val)                      { id = pid_val; }
    void set(double pweight_val)               { weight = pweight_val; }
    void set(bool pmarried_val)                { married = pmarried_val; }
    void setAddress(const char* address_val);
    void setPasswd(const string& pw_val)       { passwd = pw_val; }
    void setMemo(const char* c_str_val)        { copyMemo(c_str_val); }

    // getter 함수
    const string& getName()   const { return name; }
    const string& getPasswd() const { return passwd; }
    int           getId()       const { return id; }
    double        getWeight()   const { return weight; }
    bool          getMarried()  const { return married; }
    const char* getAddress()  const { return address; }
    const char* getMemo()           { return memo_c_str; }


    // 기능 함수
    virtual void input(istream& in)       { inputMembers(in); }
    virtual void print(ostream& out) const;
    void println() const;
    virtual void whatAreYouDoing();
    bool isSame(const string& name_val, int pid_val);
    Person& operator++();
    Person operator++(int);
    virtual Person* clone() {
        return new Person(*this);
    }

    Person& operator=(const Person& p) {
        if (this == &p) return *this;
        name    = p.name;
        passwd  = p.passwd;
        id      = p.id;
        weight  = p.weight;
        married = p.married;
        setAddress(p.address);
        setMemo(p.memo_c_str);
        return *this;
    }

    Person& operator<<(const std::string& name_val);
    Person& operator<<(const char* name_val);
    Person& operator<<(int id_val);

    Person& operator>>(std::string& name_val);
    Person& operator>>(int& id_val);
    Person& operator>>(char* name_val);

    operator string() const { return name; }
    operator int() const    { return id; }

    bool operator==(const Person& other) const {
        return name == other.name && id == other.id;
    }
};
// *********************************************************
// Person class end point
// *********************************************************

// *********************************************************
// Person member func start point
// *********************************************************
Person& Person::operator<<(const std::string& name_val) {
    this->name = name_val;
    return *this;
}

Person& Person::operator<<(const char* name_val) {
    this->name = name_val;
    return *this;
}

Person& Person::operator<<(int id_val) {
    this->id = id_val;
    return *this;
}

Person& Person::operator>>(std::string& name_val) {
    name_val = this->name;
    return *this;
}

Person& Person::operator>>(int& id_val) {
    id_val = this->id;
    return *this;
}

Person& Person::operator>>(char* name_val) {
    if (name_val != nullptr) {
        strcpy(name_val, this->name.c_str());
    }
    return *this;
}

Person operator+(double lhs, const Person& rhs) {
    Person temp(rhs);
    temp.set(lhs + temp.getWeight());
    return temp;
}

Person operator+(const Person& lhs, double rhs) {
    Person temp(lhs);
    temp.set(temp.getWeight() + rhs);
    return temp;
}

Person operator+(double lhs, Person&& rhs) {
    rhs.set(lhs + rhs.getWeight());
    return std::move(rhs);
}

Person operator+(Person&& lhs, double rhs) {
    lhs.set(lhs.getWeight() + rhs);
    return std::move(lhs);
}

Person operator+(const Person& lhs, const Person& rhs) {
    Person temp(lhs);
    temp.set(temp.getWeight() + rhs.getWeight());
    return temp;
}

Person operator+(Person&& lhs, const Person& rhs) {
    lhs.set(lhs.getWeight() + rhs.getWeight());
    return std::move(lhs);
}

Person operator+(const Person& lhs, Person&& rhs) {
    rhs.set(lhs.getWeight() + rhs.getWeight());
    return std::move(rhs);
}

Person operator+(Person&& lhs, Person&& rhs) {
    lhs.set(lhs.getWeight() + rhs.getWeight());
    return std::move(lhs);
}

Person& Person::operator++() {
    weight += 1.0;
    return *this;
}

Person Person::operator++(int) {
    Person temp = *this;
    weight += 1.0;
    return temp;
}

void Person::printMembers(ostream& out) const {
    out << name << " " << id << " " << weight << " "
        << (married ? "true" : "false") << " :"
        << (address ? address : "") << ":";
}

void Person::print(ostream& out) const {
    printMembers(out);
}

void Person::println() const {
    print(cout);
    cout << endl;
}

void Person::setAddress(const char* address_val) {
    copyAddress(address_val);
}

void Person::copyAddress(const char* addr_val) {
    delete[] address;
    if (addr_val == nullptr || strlen(addr_val) == 0) {
        address = new char[1];
        address[0] = '\0';
        return;
    }
    address = new char[strlen(addr_val) + 1];
    strcpy(address, addr_val);
}

void Person::copyMemo(const char* c_str_val) {
    delete[] memo_c_str;
    if (c_str_val == nullptr) {
        memo_c_str = nullptr;
        return;
    }
    memo_c_str = new char[strlen(c_str_val) + 1];
    strcpy(memo_c_str, c_str_val);
}

void Person::whatAreYouDoing() {
    cout << name << " is taking a rest." << endl;
}

bool Person::isSame(const string& name_val, int pid_val) {
    return (this->name == name_val && this->id == pid_val);
}

void Person::set(const string& name_val, int pid_val, double weight_val, bool married_val, const char* addr_val) {
    setName(name_val);
    set(pid_val);
    set(weight_val);
    set(married_val);
    setAddress(addr_val);
}

Person::Person(const Person& p)
    : name(p.name), id(p.id), weight(p.weight), married(p.married),
      address(nullptr), memo_c_str(nullptr) {
    copyAddress(p.address);
    copyMemo(p.memo_c_str);
    cout << "Person::Person(const Person& p):"; printMembers(cout); cout << endl;
}

void Person::inputMembers(istream& in_stream) {
    string line_buf;
    string t_name;
    string t_married_str;
    char colon_char;
    int t_id;
    double t_weight;
    bool t_married_val;

    getline(in_stream, line_buf);

    if (!in_stream && line_buf.empty()){
        // This case means getline failed and read nothing, potentially due to previous error or EOF.
        // if (!in_stream.eof()) { // If not EOF, it's a more serious error.
             in_stream.clear(); // Clear error flags like failbit or badbit.
             in_stream.setstate(ios::failbit); // Explicitly set failbit.
        // } else {
        //     // It was EOF and an empty line, which might be a valid end of input.
        //     // The caller should check in_stream.eof() if this distinction is important.
        //     in_stream.clear(); // Clear eof for now.
        // }
         return;
    }

    // If getline hit EOF but still read some characters (or an empty line before EOF),
    // clear the eof state so that istringstream can parse the content of line_buf.
    if (in_stream.eof()) {
        in_stream.clear();
    }

    rawInput = line_buf;
    istringstream iss(line_buf);
    string addrPart;

    if (!(iss >> t_name >> t_id >> t_weight >> t_married_str >> colon_char) || colon_char != ':') {
        if (!line_buf.empty() || (iss.fail() && !iss.eof()) ) {
             // If line_buf was not empty (meaning getline read something) but parsing failed,
             // or if iss itself failed for reasons other than EOF on the iss,
             // then propagate error to the original stream.
            in_stream.setstate(ios::failbit);
        }
        return;
    }

    if (t_married_str == "true")
        t_married_val = true;
    else if (t_married_str == "false")
        t_married_val = false;
    else {
        in_stream.setstate(ios::failbit);
        return;
    }

    getline(iss >> std::ws, addrPart, ':');

    const int MAX_ADDRESS_LEN = 100;
    if (addrPart.length() >= MAX_ADDRESS_LEN)
        addrPart = addrPart.substr(0, MAX_ADDRESS_LEN - 1);

    this->setName(t_name);
    this->set(t_id);
    this->set(t_weight);
    this->set(t_married_val);
    this->setAddress(addrPart.c_str());

    if (iss.fail() && !iss.eof()) {
        in_stream.setstate(ios::failbit);
    }
}
// *********************************************************
// Person member func end point
// *********************************************************

// 코드 추가 2
/******************************************************************************
 * ch8_1: Student class
 ******************************************************************************/
class Student : public Person {
    string department;
    double GPA;
    int    year;

protected:
    void inputMembers(istream& in_stream);
    void printMembers(ostream& out) const;

public:
    Student(const string& name_p={}, int id_p={}, double weight_p={},
            bool married_p={}, const char* address_p={},
            const string& department_p={}, double GPA_p={}, int year_p={});
    Student(const Student& s);
    ~Student();
    Person* clone() override;

    int           getYear()       const;
    double        getGPA()        const;
    const string& getDepartment() const;

    void setDepartment(const string& department_val);
    void setYear(int year_val);
    void setGPA(double GPA_val);

    void input(istream& in_stream) override;
    void print(ostream& out) const override;
    void println() { print(cout); cout << endl; }
    bool operator==(const Student& s);
    void whatAreYouDoing() override;
    void study();
    void takeClass();
};

Student::Student(const string& name_p, int id_p, double weight_p,
                 bool married_p, const char* address_p,
                 const string& department_p, double GPA_p, int year_p)
    : Person(name_p, id_p, weight_p, married_p, address_p),
      department(department_p), GPA(GPA_p), year(year_p) {
    cout << "Student::Student(...):"; printMembers(cout); cout << endl;
}

// [문제 2].1
Student::Student(const Student& s)
    : Person(s),
      department(s.department), GPA(s.GPA), year(s.year) {
    cout << "Student::Student(const Student& s):"; printMembers(cout); cout << endl;
}

Student::~Student() {
    cout << "Student::~Student():"; printMembers(cout); cout << endl;
}

void Student::printMembers(ostream& out) const {
    out << " " << department << " " << GPA << " " << year;
}

// [문제 2].2
void Student::print(ostream& out) const {
    Person::printMembers(out);
    this->printMembers(out);
}

// [문제 3]
bool Student::operator==(const Student& s) {
    return (static_cast<const Person&>(*this) == s) &&
           this->department == s.department &&
           this->year == s.year;
}

// [문제 4]
int Student::getYear() const { return year; }
double Student::getGPA() const { return GPA; }
const string& Student::getDepartment() const { return department; }

void Student::setDepartment(const string& department_val) { this->department = department_val; }
void Student::setYear(int year_val) { this->year = year_val; }
void Student::setGPA(double GPA_val) { this->GPA = GPA_val; }

// [문제 5]
void Student::whatAreYouDoing() {
    cout << "~~~~~~~~~~~~~~~~ Student::whatAreYouDoing() ~~~~~~~~~~~~~~~~\n";
    study();
    takeClass();
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void Student::study() {
    cout << getName() << " is studying as a " << year << "-year student in " << department << endl;
}
void Student::takeClass() {
    cout << getName() << " took several courses and got GPA " << GPA << endl;
}

// [문제 6]
Person* Student::clone() {
    return new Student(*this);
}

// [문제 7].2
void Student::input(istream& in_stream) {
    Person::inputMembers(in_stream);
    // Check the original stream's state. If Person::inputMembers failed (and set in_stream's failbit), return.
    // If Person::inputMembers read an empty line successfully (e.g. at EOF for interactive input),
    // in_stream might be good but subsequent read for Student parts might fail.
    if (!in_stream && !in_stream.eof()) { // If failed and not just EOF
        return;
    }
    // If Person::inputMembers successfully read a line which ALSO contained student data,
    // its internal istringstream (iss) would have the student data.
    // However, 'this->inputMembers(in_stream)' will try to read from the original 'in_stream'.
    // If 'in_stream' was 'cin', Person::inputMembers already consumed the line from 'cin'.
    // This part of the logic is problematic if all data (Person + Student) is on a single line
    // AND Person::inputMembers consumes the whole line from the passed stream.
    // For this to work as intended by the problem structure (base call then derived call on same stream),
    // Person::inputMembers should ideally only parse its part from an istringstream of the line,
    // and the public input method should manage the getline and pass the istringstream.
    // Or Person::inputMembers uses in_stream and only reads its part.

    // Assuming the problem implies Person::inputMembers leaves 'in_stream' (if it's an istringstream)
    // ready for Student specific parts.
    if (in_stream.good()){ // Only proceed if stream is still good
         this->inputMembers(in_stream);
    }
    if (in_stream.fail() && !in_stream.eof()){
        // Error during Student input
    }
}

// [문제 7].3
void Student::inputMembers(istream& in_stream) {
    in_stream >> department >> GPA >> year;
    if (!in_stream && !in_stream.eof()) {
        // Propagate error to in_stream if it's not already set by >>
        if (in_stream.good()) in_stream.setstate(ios::failbit);
    }
}

/******************************************************************************
 * ch8_1: Worker class
 ******************************************************************************/
class Worker : public Person {
    string company;
    string position;
protected:
    void inputMembers(istream& in_stream);
    void printMembers(ostream& out) const;
public:
    Worker(const string& name_p={}, int id_p={}, double weight_p={},
           bool married_p={}, const char* address_p={},
           const string& company_p={}, const string& position_p={});
    Worker(const Worker& w);
    ~Worker();
    Person* clone() override;

    const string& getCompany()  const;
    const string& getPosition() const;

    void setCompany(const string& company_val);
    void setPosition(const string& position_val);

    void input(istream& in_stream) override;
    void print(ostream& out) const override;
    void println() { print(cout); cout << endl; }
    bool operator==(const Worker& w);
    void whatAreYouDoing() override;
    void work();
    void goOnVacation();
};

// [문제 1]
Worker::Worker(const string& name_p, int id_p, double weight_p,
               bool married_p, const char* address_p,
               const string& company_p, const string& position_p)
    : Person(name_p, id_p, weight_p, married_p, address_p),
      company(company_p), position(position_p) {
    cout << "Worker::Worker(...):"; printMembers(cout); cout << endl;
}

// [문제 8].2
Worker::Worker(const Worker& w)
    : Person(w), company(w.company), position(w.position) {
    cout << "Worker::Worker(const Worker& w):"; printMembers(cout); cout << endl;
}

Worker::~Worker() {
    cout << "Worker::~Worker():"; printMembers(cout); cout << endl;
}

void Worker::printMembers(ostream& out) const {
    out << " " << company << " " << position;
}

// [문제 8].2
void Worker::print(ostream& out) const {
    Person::printMembers(out);
    this->printMembers(out);
}

// [문제 8].2
bool Worker::operator==(const Worker& w) {
    return (static_cast<const Person&>(*this) == w) &&
           this->company == w.company &&
           this->position == w.position;
}

// [문제 8].2
const string& Worker::getCompany()  const { return company; }
const string& Worker::getPosition() const { return position; }

void Worker::setCompany(const string& company_val) { this->company = company_val; }
void Worker::setPosition(const string& position_val) { this->position = position_val; }

// [문제 8].2
void Worker::whatAreYouDoing() {
    cout << "!!!!!!!!!!!!!!!! Worker::whatAreYouDoing()!!!!!!!!!!!!!!!!!\n";
    work();
    goOnVacation();
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
}

void Worker::work() {
    cout << getName() << " works in " << company << " as " << position << endl;
}
void Worker::goOnVacation() {
    cout << getName() << " is now enjoying his(her) vacation" << endl;
}

// [문제 8].2
Person* Worker::clone() {
    return new Worker(*this);
}

// [문제 8].2
void Worker::input(istream& in_stream) {
    Person::inputMembers(in_stream);
    if (in_stream.fail() && !in_stream.eof()) {
        return;
    }
    if(in_stream.good()){
        this->inputMembers(in_stream);
    }
     if (in_stream.fail() && !in_stream.eof()){
        // Error
    }
}

// [문제 8].2
void Worker::inputMembers(istream& in_stream) {
    in_stream >> company >> position;
    if (!in_stream && !in_stream.eof()) {
        if(in_stream.good()) in_stream.setstate(ios::failbit);
    }
}

//*****************************************************************************
// VectorPerson class (Retaining original structure with modifications)
//*****************************************************************************
class VectorPerson
{
    static const int DEFAULT_SIZE = 10;
    Person **pVector;
    int count;
    int allocSize;
    void extend_capacity(int capacity);
public:
    VectorPerson& operator=(const VectorPerson& vp);
    VectorPerson operator+(const VectorPerson& vp) const;
    VectorPerson& operator+=(const VectorPerson& vp);
    VectorPerson(int capacity = DEFAULT_SIZE): count(0), allocSize(capacity) { pVector = new Person*[allocSize]; }
    VectorPerson(const VectorPerson& vp)
      : count(vp.count), allocSize(vp.allocSize)
    {
        // cout << "VectorPerson::VectorPerson(const VectorPerson& vp)" << endl;
        pVector = new Person*[allocSize];
        for (int i = 0; i < count; ++i)
            pVector[i] = vp.pVector[i];
    }
    ~VectorPerson();
    Person* at(int index) const {
        if (index < 0 || index >= count) return nullptr;
        return pVector[index];
    }
    int     capacity()    const { return allocSize; }
    int     size()        const { return count; }
    bool    empty()       const { return count == 0; }
    void    clear()             { count = 0; }
    void    push_back(Person* p);
    void    erase(int index);
    void    insert(int index, Person* p);
    Person* operator[](int index) const {
        if (index < 0 || index >= count)
            return nullptr;
        return pVector[index];
    }
    bool operator!() const { return empty(); }
    operator bool() const { return !empty(); }
};

VectorPerson& VectorPerson::operator+=(const VectorPerson& vp) {
    if (count + vp.count > allocSize) {
        extend_capacity(allocSize + vp.allocSize);
    }
    for (int i = 0; i < vp.count; ++i) {
        pVector[count + i] = vp.pVector[i];
    }
    count += vp.count;
    return *this;
}

VectorPerson VectorPerson::operator+(const VectorPerson& vp) const {
    VectorPerson tmp(this->count + vp.count);
    for (int i = 0; i < this->count; ++i) {
        tmp.pVector[i] = this->pVector[i];
    }
    for (int i = 0; i < vp.count; ++i) {
        tmp.pVector[this->count + i] = vp.pVector[i];
    }
    tmp.count = this->count + vp.count;
    return tmp;
}

// 코드 추가 5.1
VectorPerson& VectorPerson::operator=(const VectorPerson& vp) {
    if (this == &vp)
        return *this;
    if (vp.count > this->allocSize) {
        // cout << "VectorPerson::operator = : capacity extended to " << vp.allocSize << endl;
        delete[] pVector;
        this->allocSize = vp.allocSize;
        if (this->allocSize < vp.count) this->allocSize = vp.count;
        pVector = new Person*[this->allocSize];
    }
    this->count = vp.count;
    for (int i = 0; i < this->count; ++i) {
        pVector[i] = vp.pVector[i];
    }
    return *this;
}

void VectorPerson::erase(int index) {
    if (index < 0 || index >= count) return;
    for (int i = index; i < count - 1; ++i) {
        pVector[i] = pVector[i + 1];
    }
    --count;
}

void VectorPerson::insert(int index, Person* p) {
    if (index < 0 || index > count) return;
    if (count >= allocSize) {
        extend_capacity(allocSize == 0 ? DEFAULT_SIZE : allocSize * 2);
    }
    for (int i = count; i > index; --i) {
        pVector[i] = pVector[i-1];
    }
    pVector[index] = p;
    ++count;
}

VectorPerson::~VectorPerson() {
    delete[] pVector;
}

void VectorPerson::push_back(Person* p) {
    if (count >= allocSize) {
        extend_capacity(allocSize == 0 ? DEFAULT_SIZE : allocSize * 2);
    }
    pVector[count++] = p;
}

// 코드 추가 5.1
void VectorPerson::extend_capacity(int capacity) {
    // cout << "VectorPerson: capacity extended to " << capacity << endl;
    int newAllocSize = (this->allocSize == 0) ? DEFAULT_SIZE : this->allocSize * 2;
    if (capacity > newAllocSize) {
        newAllocSize = capacity;
    }
    Person** newVector = new Person*[newAllocSize];
    for (int i = 0; i < count; ++i) {
        newVector[i] = pVector[i];
    }
    delete[] pVector;
    pVector = newVector;
    allocSize = newAllocSize;
}

//*****************************************************************************
// UI Class (as provided in original)
//*****************************************************************************
class UI {
private:
    static string line, emptyLine;
public:
    static bool echo_input;
    static string&           getEmptyLine()              { return emptyLine; }
    static const string&     getNext (const string& msg);
    static const string&     getNextLine (const string& msg);
    static bool              checkInputError (istream* pin, const string& msg);
    static int               getInt (const string& msg);
    static int               getIndex (const string& msg, int size);
    static int               selectMenu (const string& menuStr, int menuItemCount);
    static bool inputPerson(Person& p_ref);
    static int getPositiveInt(const string& msg);
};

bool UI::echo_input = false; string UI::line, UI::emptyLine;
const string& UI::getNext(const string& prompt_message) {
    cout << prompt_message;
    cin >> line;
    if (echo_input) {
        cout << line << endl;
    }
    getline(cin, emptyLine);
    return line;
}

const string& UI::getNextLine(const string& prompt_message) {
    cout << prompt_message;
    getline(cin, line);
    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }
    if (echo_input) {
        cout << line << endl;
    }
    return line;
}

bool UI::checkInputError(istream* p_inStream, const string& error_message) {
    if (!(*p_inStream)) {
        cout << error_message;
        p_inStream->clear();
        p_inStream->ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }
    return false;
}

int UI::getInt(const string& prompt_message) {
    int value;
    while (true) {
        cout << prompt_message;
        cin >> value;
        if (echo_input) {
            cout << value << endl;
        }
        if (checkInputError(&cin, "Input an INTEGER.\n")) {
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }
}

int UI::getIndex(const string& prompt_message, int max_elements) {
    int index;
    while (true) {
        index = getInt(prompt_message);
        if (index >= 0 && index < max_elements) {
            return index;
        }
        cout << index << ": OUT of selection range(0 ~ " << (max_elements - 1) << ")" << endl;
    }
}

int UI::selectMenu(const string& menu_string, int menu_item_count) {
    cout << endl << menu_string;
    return getIndex("Menu item number? ", menu_item_count);
}

bool UI::inputPerson(Person& person_ref) {
    cout << "input person information:" << endl;
    person_ref.setAddress(nullptr);
    person_ref.input(cin);
    if (!cin) {
        checkInputError(&cin, "Input-data format MISMATCHED\n");
        return false;
    }
    if (echo_input) {
        person_ref.println();
    }
    return true;
}

int UI::getPositiveInt(const string& prompt_message) {
    int value;
    while ((value = getInt(prompt_message)) < 0) {
        cout << "Input a positive INTEGER." << endl;
    }
    return value;
}
//*****************************************************************************
// Global helper functions (as provided in original)
//*****************************************************************************
bool checkDataFormatError(istream& in_stream) {
    return UI::checkInputError(&in_stream, "Input-data format MISMATCHED\n");
}
bool inputPersonFromUser(Person* p_ptr) {
    if (!p_ptr) return false;
    cout << "input person information:" << endl;
    p_ptr->setAddress(nullptr);
    // Crucial: ensure cin is usable before Person::input (which uses getline)
    // if(std::cin.peek() == '\n') std::cin.ignore(); // More aggressive clear if needed, but UI::getInt should handle it
    p_ptr->input(cin);
    if (!cin && !cin.eof()) { // Check stream state after p_ptr->input() if not just EOF
         UI::checkInputError(&cin, "Input-data format MISMATCHED (from inputPersonFromUser)\n");
         return false;
    }
    if (UI::echo_input) p_ptr->println();
    return true;
}
int getPositiveInt(const string msg) { return UI::getPositiveInt(msg); }
int getIndex(const string msg, int size_val) { return UI::getIndex(msg, size_val); }
int selectMenu(const string menuStr, int menuItemCount) { return UI::selectMenu(menuStr, menuItemCount); }

//*****************************************************************************
// Memo Class and methods (as provided in original)
//*****************************************************************************
class Memo {
    string mStr;
    size_t find_last_line(); bool find_line(int line, size_t& start, size_t& len);
public:
    Memo(const char* c_str_p = nullptr) : mStr(c_str_p ? c_str_p : "") {}
    void displayMemo(); void findString(); void compareWord(); void dispByLine();
    void deleteLine(); void replaceLine(); void scrollUp(); void scrollDown();
    void inputMemo(); void run();
    const char* c_str() const { return mStr.c_str(); }
    void         c_str(const char* c_str_p) { mStr = (c_str_p ? c_str_p : ""); }
    string&      getNext(size_t& pos, string& word);
    string&      get_next_line(size_t& pos, string& line_ref);
    Memo operator+(const Memo& m_other) { return Memo((mStr + m_other.mStr).c_str()); }
    Memo& operator+=(const Memo& m_other) { mStr += m_other.mStr; return *this; }
};
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
bool Memo::find_line(int line_num, size_t& start_pos, size_t& length) {
    start_pos = 0;
    for (int i = 0; i < line_num; ++i) {
        start_pos = mStr.find('\n', start_pos);
        if (start_pos == string::npos) return false;
        ++start_pos;
    }
    size_t end_pos = mStr.find('\n', start_pos);
    length = (end_pos == string::npos) ? mStr.size() - start_pos : end_pos - start_pos + 1;

    if (start_pos > mStr.length()) return false;
    if (start_pos == mStr.length() && line_num > 0) { // Requested line beyond actual content
        if (mStr.empty() || mStr.back() != '\n') { // And no implicit empty line at the end
             length = 0; // Defensive: ensure length is 0 if line not found
             return false;
        }
    }
    return true;
}

size_t Memo::find_last_line() {
    if (mStr.empty()) return 0;
    size_t pos = mStr.rfind('\n');
    if (pos == string::npos) return 0;
    if (pos == mStr.length() - 1) {
        if (mStr.length() == 1) return 0;
        size_t prev_pos = mStr.rfind('\n', pos - 1);
        if (prev_pos == string::npos) return 0;
        return prev_pos + 1;
    }
    return pos + 1;
}

void Memo::displayMemo() {
    cout << "------- Memo -------" << endl;
    cout << mStr;
    if (mStr.length() > 0 && mStr.back() != '\n') {
        cout << endl;
    }
    cout << "--------------------" << endl;
}

void Memo::findString() {
    string word_to_find = UI::getNext("Word to find? ");
    int match_count = 0;
    size_t word_len = word_to_find.length();
    size_t current_pos = 0;
    if (word_len == 0) { // Avoid infinite loop if word_to_find is empty
        cout << "Found count: 0" << endl;
        return;
    }
    while ((current_pos = mStr.find(word_to_find, current_pos)) != string::npos) {
        ++match_count;
        current_pos += word_len;
    }
    cout << "Found count: " << match_count << endl;
}

string& Memo::getNext(size_t& current_scan_pos, string& word_buffer) {
    word_buffer.clear();
    size_t effective_pos = current_scan_pos;
    while (effective_pos < mStr.length() && isspace(mStr[effective_pos])) {
        effective_pos++;
    }
    if (effective_pos >= mStr.length()) {
        current_scan_pos = effective_pos;
        return word_buffer;
    }
    size_t token_start_pos = effective_pos;
    if (ispunct(mStr[effective_pos])) {
        word_buffer = mStr.substr(effective_pos, 1);
        effective_pos++;
    } else {
        while (effective_pos < mStr.length() && !isspace(mStr[effective_pos]) && !ispunct(mStr[effective_pos])) {
            effective_pos++;
        }
        word_buffer = mStr.substr(token_start_pos, effective_pos - token_start_pos);
    }
    current_scan_pos = effective_pos;
    return word_buffer;
}

void Memo::compareWord() {
    string word_to_compare = UI::getNext("Word to compare? ");
    int less_count = 0, same_count = 0, greater_count = 0;
    size_t current_pos = 0;
    string next_word;
    while (true) {
        getNext(current_pos, next_word);
        if (next_word.empty() && current_pos >= mStr.length()) {
            break;
        }
        if (next_word.empty()) { // Skip empty tokens if getNext can produce them mid-string
            continue;
        }
        if (next_word < word_to_compare) less_count++;
        else if (next_word == word_to_compare) same_count++;
        else greater_count++;
    }
    cout << "less: " << less_count << "\nsame: " << same_count << "\nlarger: " << greater_count << endl;
}

void Memo::dispByLine() {
    cout << "--- Memo by line ---" << endl;
    size_t current_pos = 0;
    int line_number = 0;
    while (current_pos < mStr.length()) {
        size_t newline_pos = mStr.find('\n', current_pos);
        cout << "[" << line_number++ << "] ";
        if (newline_pos == string::npos) {
            cout << mStr.substr(current_pos) << endl;
            break;
        } else {
            cout << mStr.substr(current_pos, newline_pos - current_pos) << endl;
            current_pos = newline_pos + 1;
        }
    }
    if (mStr.empty() || (current_pos == mStr.length() && !mStr.empty() && mStr.back() == '\n')) {
        cout << "[" << line_number << "] " << endl;
    }
    cout << "--------------------" << endl;
}

void Memo::deleteLine() {
    size_t line_to_delete = UI::getPositiveInt("Line number to delete? ");
    size_t start_offset, line_length;
    if (!find_line(line_to_delete, start_offset, line_length)) {
        cout << "Out of line range" << endl;
        return;
    }
    mStr.erase(start_offset, line_length);
    dispByLine();
}

void Memo::replaceLine() {
    size_t line_to_replace = UI::getPositiveInt("Line number to replace? ");
    size_t start_offset, line_length;
    if (!find_line(line_to_replace, start_offset, line_length)) {
        cout << "Out of line range" << endl;
        return;
    }
    string replacement_line = UI::getNextLine("Input a line to replace:\n");
    replacement_line += '\n';
    mStr.replace(start_offset, line_length, replacement_line);
    dispByLine();
}

void Memo::scrollUp() {
    size_t first_line_start, first_line_len;
    if (mStr.empty() || !find_line(0, first_line_start, first_line_len)) {
        dispByLine();
        return;
    }
    string first_line_content = mStr.substr(first_line_start, first_line_len);
    mStr.erase(first_line_start, first_line_len);
    if (!mStr.empty() && mStr.back() != '\n') {
        mStr += '\n';
    }
    mStr += first_line_content;
    dispByLine();
}

void Memo::scrollDown() {
    if (mStr.empty()) {
        dispByLine();
        return;
    }
    size_t last_line_start_pos = find_last_line();
    size_t last_line_length = mStr.size() - last_line_start_pos;
    string last_line_content = mStr.substr(last_line_start_pos, last_line_length);
    mStr.erase(last_line_start_pos, last_line_length);
    if (!last_line_content.empty() && last_line_content.back() != '\n') {
        last_line_content += '\n';
    }
    mStr = last_line_content + mStr;
    dispByLine();
}

void Memo::inputMemo() {
    mStr.clear();
    string current_line_buffer;
    cout << "--- Input memo lines, and then input empty line at the end ---" << endl;
    while (getline(cin, current_line_buffer)) {
        if (UI::echo_input) {
            cout << current_line_buffer << endl;
        }
        if (current_line_buffer.empty()) {
            break;
        }
        mStr += current_line_buffer + '\n';
    }
}

void Memo::run() {
    using func_ptr_t = void (Memo::*)();
    func_ptr_t menu_functions[] = {
        nullptr, &Memo::displayMemo, &Memo::findString, &Memo::compareWord,
        &Memo::dispByLine, &Memo::deleteLine, &Memo::replaceLine,
        &Memo::scrollUp, &Memo::scrollDown, &Memo::inputMemo
    };
    int num_menu_items = sizeof(menu_functions) / sizeof(menu_functions[0]);
    string menu_display_string =
        "++++++++++++++++++++++ Memo Management Menu +++++++++++++++++++++\n"
        "+ 0.Exit 1.DisplayMemo 2.FindString 3.CompareWord 4.DispByLine  +\n"
        "+ 5.DeleteLine 6.RepaceLine 7.ScrollUp 8.ScrollDown 9.InputMemo +\n"
        "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    if (mStr.empty()) {
        mStr = memoData;
    }
    while (true) {
        int selected_item = UI::selectMenu(menu_display_string, num_menu_items);
        if (selected_item == 0) return;
        if (selected_item > 0 && selected_item < num_menu_items && menu_functions[selected_item] != nullptr) {
             (this->*menu_functions[selected_item])();
        } else {
            cout << "Invalid menu selection." << endl; // Should be handled by UI::getIndex ideally
        }
    }
}

string& Memo::get_next_line(size_t& current_pos, string& line_buffer) {
    line_buffer.clear();
    if (current_pos >= mStr.length()) {
        return line_buffer;
    }
    size_t newline_char_pos = mStr.find('\n', current_pos);
    if (newline_char_pos == string::npos) {
        line_buffer = mStr.substr(current_pos);
        current_pos = mStr.length();
    } else {
        line_buffer = mStr.substr(current_pos, newline_char_pos - current_pos);
        current_pos = newline_char_pos + 1;
    }
    return line_buffer;
}
//*****************************************************************************
// Factory class (as provided in original)
//*****************************************************************************
class Factory {
public:
    static Person* inputPerson(istream& in_stream) {
        Person* p = new Person();
        p->input(in_stream);
        if (!in_stream && !in_stream.eof()) {
             if (checkDataFormatError(in_stream)) {
                delete p;
                return nullptr;
             }
        } else if (!in_stream && in_stream.eof() && (p->getName().empty() && p->getId()==0)){ // More robust check for actual failed read at eof
            delete p;
            return nullptr;
        }
        if (UI::echo_input) p->println();
        return p;
    }
};

//*****************************************************************************
// CurrentUser class (as provided in original)
//*****************************************************************************
class CurrentUser {
    Person& rUser;
    Memo memo;
public:
    CurrentUser(Person& rUser_p) : rUser(rUser_p) {
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

void CurrentUser::changePasswd() {
    string newPw = UI::getNext("New password: ");
    rUser.setPasswd(newPw);
    cout << "Password changed" << endl;
}

void CurrentUser::display() {
    rUser.println();
}

void CurrentUser::getter() {
    cout << "name:" << rUser.getName()
         << ", id:" << rUser.getId()
         << ", weight:" << rUser.getWeight()
         << ", married:" << (rUser.getMarried() ? "true" : "false")
         << ", address:" << (rUser.getAddress() ? rUser.getAddress() : "") << endl;
}

void CurrentUser::set() {
    Person* ps = new Person("rp");
    ps->set(ps->getName(), rUser.getId(), rUser.getWeight(), !rUser.getMarried(), rUser.getAddress());
    cout << "rp.set():";
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

void CurrentUser::whatAreYouDoing() {
    rUser.whatAreYouDoing();
}

void CurrentUser::isSame() {
    rUser.println();
    cout << "isSame(\"user\", 1): " << boolalpha << (rUser.isSame("user", 1)) << endl;
}

void CurrentUser::inputPerson() {
    if (inputPersonFromUser(&rUser)) {
        display();
    }
}

void CurrentUser::defaultParameter() {
    Person ps1;
    Person ps2("ps2");
    Person ps3("ps3", 3);
    Person ps4("ps4", 4, 70.4);
    Person ps5("ps5", 5, 70.5, true);
    Person ps6("ps6", 6, 70.6, true, "ps6 address");

    cout << "\nMemo m1;" << endl;
    Memo m1;
    m1.displayMemo();

    cout << "\nMemo m2(rUser.getMemo())" << endl;
    Memo m2(rUser.getMemo());
    m2.displayMemo();
}

void CurrentUser::staticMember() {
    string w1;
    w1 = UI::getNext("Input a word: ");
    cout << "UI::getNext(): " << w1 << endl << endl;

    UI ui_obj;
    string w2;
    w2 = ui_obj.getNext("Input a word: ");
    cout << "ui.getNext() : " << w2 << endl;
}

void CurrentUser::manageMemo() {
    memo.run();
    rUser.setMemo(memo.c_str());
}

void CurrentUser::run() {
    using func_t = void (CurrentUser::*)();
    func_t func_arr[] = {
        nullptr,
        &CurrentUser::display,
        &CurrentUser::getter,
        &CurrentUser::setter,
        &CurrentUser::set,
        &CurrentUser::whatAreYouDoing,
        &CurrentUser::isSame,
        &CurrentUser::inputPerson,
        &CurrentUser::changePasswd,
        &CurrentUser::manageMemo,
        &CurrentUser::defaultParameter,
        &CurrentUser::staticMember
    };
    int menuCount = sizeof(func_arr) / sizeof(func_arr[0]);
    string menuStr =
        "+++++++++++++++++++++ Current User Menu ++++++++++++++++++++++++\n"
        "+ 0.Logout 1.Display 2.Getter 3.Setter 4.Set 5.WhatAreYouDoing +\n"
        "+ 6.IsSame 7.InputPerson 8.ChangePasswd(4_2) 9.ManageMemo(4_3) +\n"
        "+ 10.DefaultParameter(6_1) 11.StaticMember(6_1)                +\n"
        "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    while (true) {
        int menuItem = UI::selectMenu(menuStr, menuCount);
        if (menuItem == 0) return;
        if (menuItem > 0 && menuItem < menuCount && func_arr[menuItem] != nullptr) {
            (this->*func_arr[menuItem])();
        } else {
            // 선택지가 배열 범위를 벗어나거나 nullptr인 경우 UI::selectMenu에서 처리될 것으로 예상
            // 만약 여기까지 온다면 UI::selectMenu 로직에 문제가 있을 수 있음
            cout << "Invalid menu selection or function not available." << endl;
        }
    }
}
//*****************************************************************************
// PersonManager class (as provided in original)
//*****************************************************************************
class PersonManager {
    Person** array;
    int      arrLen;
    int      cpCount;
    VectorPerson persons;

    void deleteElements(); // 오타 수정: deleteElemets -> deleteElements
    void printNotice(const string pre_message, const string post_message);
    Person* findByName(const string name_to_find);
    void pushArray();

public:
    PersonManager(Person* initial_array[], int length);
    ~PersonManager();

    void display();
    void append();
    void clear();
    void login();
    void insert();
    void remove();
    void copyPersons();
    void reset();
    void run();
};

Person* PersonManager::findByName(const string name_to_find) {
    for (int i = 0; i < persons.size(); ++i) {
        if (persons.at(i)->getName() == name_to_find) {
            return persons.at(i);
        }
    }
    cout << name_to_find << ": NOT found" << endl;
    return nullptr;
}

PersonManager::PersonManager(Person* initial_array[], int length)
    : array(initial_array), arrLen(length), persons(), cpCount(0) {
    pushArray();
}

void PersonManager::pushArray() {
    for (int i = 0; i < arrLen; ++i) {
        if (array[i]) {
            Person* copy = array[i]->clone(); // clone() 사용
            persons.push_back(copy);
        }
    }
}

PersonManager::~PersonManager() {
    deleteElements();
}

void PersonManager::deleteElements() {
    for (int i = 0; i < persons.size(); ++i) {
        delete persons.at(i); // VectorPerson이 포인터만 관리하므로 객체 직접 삭제
    }
    persons.clear();
    cpCount = 0;
}

void PersonManager::display() {
    int current_person_count = persons.size();
    cout << "display(): count " << current_person_count << endl;
    for (int i = 0; i < current_person_count; ++i) {
        cout << "[" << i << "]";
        persons.at(i)->println();
    }
    cout << boolalpha; // 다음 bool 출력 시 true/false로 나오도록 설정
}

void PersonManager::printNotice(const string pre_message, const string post_message) {
    cout << pre_message << " [person information] " << post_message << endl;
}

void PersonManager::append() {
    int num_to_add = UI::getPositiveInt("The number of persons to append? ");
    printNotice("Input " + to_string(num_to_add), ":");
    for (int i = 0; i < num_to_add; ++i) {
        Person* new_person = Factory::inputPerson(cin);
        if (new_person) {
            persons.push_back(new_person);
        } else {
            i--; // 입력 실패 시 재시도 (루프 카운터 조정)
        }
    }
    display();
}

void PersonManager::clear() {
    deleteElements();
    display();
}

void PersonManager::login() {
    string user_name = UI::getNext("user name: ");
    Person* found_person = findByName(user_name);
    if (!found_person) return;

    string input_passwd = UI::getNextLine("password: ");
    if (input_passwd != found_person->getPasswd()) {
        cout << "WRONG password!!" << endl;
    } else {
        CurrentUser(*found_person).run();
    }
}

void PersonManager::insert() {
    int insert_idx = 0;
    if (!persons.empty()) {
        insert_idx = UI::getPositiveInt("Index to insert in front? ");
        if (insert_idx > persons.size()) { // persons.size() 위치에도 삽입 가능 (맨 뒤)
            cout << insert_idx << ": OUT of selection range(0 ~ " << persons.size() << ")" << endl;
            return;
        }
    }
    cout << "Input [person information] to insert:" << endl;
    Person* new_person = Factory::inputPerson(cin);
    if (!new_person) return;

    persons.insert(insert_idx, new_person);
    display();
}

void PersonManager::remove() {
    if (persons.empty()) {
        cout << "No entry to remove" << endl;
        return;
    }
    int remove_idx = UI::getIndex("Index to delete? ", persons.size());
    delete persons.at(remove_idx); // 먼저 객체 메모리 해제
    persons.erase(remove_idx);   // 그 다음 벡터에서 포인터 제거
    display();
}

void PersonManager::copyPersons() {
    cpCount++;
    int original_size = persons.size();
    for (int i = 0; i < original_size; ++i) {
        Person* cloned_person = persons.at(i)->clone(); // clone()을 통한 깊은 복사
        string original_name = cloned_person->getName();
        string prefix = "";
        if (!original_name.empty()) {
            for (int k = 0; k < cpCount; ++k) {
                prefix += original_name[0];
            }
        }
        cloned_person->setName(prefix + original_name);
        cloned_person->set(cloned_person->getId() + 20 * cpCount);
        cloned_person->set(cloned_person->getWeight() + cpCount);
        if (cpCount % 2 == 1) {
            cloned_person->set(!cloned_person->getMarried());
        }
        persons.push_back(cloned_person);
    }
    display();
}

void PersonManager::reset() {
    deleteElements();
    pushArray();
    display();
}

void PersonManager::run() {
    // cout << "PersonManager::run() starts" << endl; // 문제의 초기 실행 결과에는 이 출력이 없음

    using func_ptr_t = void (PersonManager::*)();
    func_ptr_t menu_functions[] = {
        nullptr,
        &PersonManager::display,
        &PersonManager::append,
        &PersonManager::clear,
        &PersonManager::login,
        &PersonManager::insert,
        &PersonManager::remove,
        &PersonManager::copyPersons,
        &PersonManager::reset,
    };
    int num_menu_items = sizeof(menu_functions) / sizeof(menu_functions[0]);
    string menu_display_string =
        "====================== Person Management Menu ===================\n"
        "= 0.Exit 1.Display 2.Append 3.Clear 4.Login(CurrentUser, ch6)  =\n"
        "= 5.Insert(6_2) 6.Delete(6_2) 7.CopyPersons(7_3) 8.Reset(7_3)   =\n"
        "=================================================================\n";

    while (true) {
        int selected_item = UI::selectMenu(menu_display_string, num_menu_items);
        if (selected_item == 0) {
            // cout << "PersonManager::run() returned" << endl; // 문제의 실행 결과에는 이 출력이 없음
            return;
        }
        if (selected_item > 0 && selected_item < num_menu_items && menu_functions[selected_item] != nullptr) {
            (this->*menu_functions[selected_item])();
        } else {
            // UI::getIndex가 범위를 보장하므로 이 경우는 거의 발생하지 않음
            cout << "Invalid menu selection in PersonManager." << endl;
        }
    }
}

//******************************************************************************
// MultiManager class (as provided in original)
//******************************************************************************
class MultiManager {
    static const int personCount = 5;
    Person persons[personCount] = {
        Person("p0", 10, 70.0, false, "Gwangju Nam-gu Bongseon-dong 21"),
        Person("p1", 11, 61.1, true,  "Jong-ro 1-gil, Jongno-gu, Seoul"),
        Person("p2", 12, 52.2, false, "1001, Jungang-daero, Yeonje-gu, Busan"),
        Person("p3", 13, 83.3, true,  "100 Dunsan-ro Seo-gu Daejeon"),
        Person("p4", 14, 64.4, false, "88 Gongpyeong-ro, Jung-gu, Daegu"),
    };
    Person* allPersons[personCount];
    PersonManager personMng;
public:
    MultiManager() : allPersons{}, personMng(allPersons, personCount) {
        for(int i=0; i < personCount; ++i) {
            allPersons[i] = &persons[i];
        }
    }
    void run() {
        personMng.run();
    }
};

//******************************************************************************
// ClassAndObject class (as provided in original, with inline definitions)
//******************************************************************************
class ClassAndObject {
    void defualConstructor() {
        Person P;
    }
    void constructor() {
        Person ps1;
        Person ps2("ps2");
        Person ps3("ps3", 3, 70.3, true, "ps3 address");
    }
    void construcor_destructor_inner_inner() {
        cout << "\n--- construcor_destructor_inner_inner() begins ---" << endl;
        Person ps3("ps3");
        if (true) {
            Person ps4("ps4");
        }
        cout << "- if ends -\n" << endl;
        cout << "- temporary object begins -" << endl;
        Person("temp_ps_1");
        cout << endl;
        Person("temp_ps_2").setName("TEMP_PS_2");
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
    void construcorDestructor() {
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
        int i = 6;
        int j = 6;
        double d = 0.0;
    public:
        void print() {
            cout << "Init2 i: " << i << ", j: " << j << ", d: " << d << endl;
        }
    };
    class Init3 {
        Person p{ "p-Init3" };
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
        Init4() :p{ "p-Init4-head" }, i{ 4 }, j{ 6 }, d{ 0.0 } {}
        void print() {
            cout << "Init4 i: " << i << ", j: " << j << ", d: " << d << endl;
        }
    };
    class Init5 {
        Person p{ "p-Init5" };
        int i;
        int j;
        double d;
    public:
        Init5() :p{ "p-Init5-head" }, i{ 5 }, j{ 6 }, d{ 0.0 } {}
        void print() {
            cout << "Init5 i: " << i << ", j: " << j << ", d: " << d << endl;
        }
    };
    class Init6 {
        Person p;
        int i, j;
        double d;
    public:
        Init6() {
            i = j = 6; d = 0.0; p.setName("p-Init6-body");
        }
        void print() {
            cout << "Init6 i: " << i << ", j: " << j << ", d: " << d << endl;
        }
    };

    void memberInitialization() {
        int i = 0, i2 = i; i = i2;
        Init1().print(); cout << endl;
        Init2().print(); cout << endl;
        Init3().print(); cout << endl;
        Init4().print(); cout << endl;
        Init5().print(); cout << endl;
        Init6().print();
    }

    class Parameter {
    public:
        void normalValue(Person p_val) { cout << "normalValue(Person p)" << endl; }
        void constValue(const Person p_val) { cout << "constValue(const Person p)" << endl; }
        void normalReference(Person& p_ref) { cout << "normalReference(Person& p)" << endl; }
        void constReference(const Person& p_ref) { cout << "constReference(const Person& p)" << endl; }
        void printStr(string& s_ref) { cout << "printStr(string& s): " << s_ref << endl; }
        void printConstStr(const string& s_ref) { cout << "printConstStr(const string& s): " << s_ref << endl; }
        void printPerson(const Person& p_ref) { cout << "printPerson(const Person& p)" << endl; p_ref.println(); }
    };
    Parameter cp;

    void normalParameter() {
        cout << "normalParameter()" << endl;
        Person p1("p1-name");
        cp.normalValue(p1);
        cp.constValue(p1);
        cp.normalReference(p1);
        cp.constReference(p1);
    }
    void constParameter() {
        cout << "constParameter()" << endl;
        const Person p2("const-p2-name");
        cp.normalValue(p2);
        cp.constValue(p2);
        cp.constReference(p2);
    }
    void temporaryParameter() {
        cout << "temporaryParameter()" << endl;
        cp.normalValue(Person("Person-name"));
        cp.constValue(Person("Person-name"));
        cp.constReference(Person("Person-name"));
    }
    void stringParameter() {
        cout << "stringParameter()" << endl;
        string s("name1");
        cp.printStr(s);
        cp.printConstStr(s);
        cp.printConstStr(string("name2"));
        cp.printConstStr("name3");
    }
    void parameters() {
        normalParameter(); cout << endl;
        constParameter(); cout << endl;
        temporaryParameter(); cout << endl;
        stringParameter(); cout << endl;
        cp.printPerson(Person("name", 10, 77.7, true, "address"));
    }
    void globalStaticLocalObjects() {
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
            "+ 5.MemberInitialization 6.constParameter         +\n"
            "+++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
        while (true) {
            int menuItem = UI::selectMenu(menuStr, menuCount);
            if (menuItem == 0) return;
            if (menuItem > 0 && menuItem < menuCount && func_arr[menuItem] != nullptr) {
                (this->*func_arr[menuItem])();
            } else {
                cout << "Invalid menu selection." << endl;
            }
        }
    }
};

//******************************************************************************
// AllocatedMember class (as provided in original)
//******************************************************************************
class AllocatedMember { Person u; Memo memo; void set_print_address(Person&p, const char*a){cout<<"p.setAddress("<<(a?a:"")<<")"<<endl;p.setAddress(a);p.println();cout<<endl;} void print_memo(Person&p){cout<<"------ "<<p.getName()<<" memo ------"<<endl;const char*pm=p.getMemo();cout<<(pm?pm:"");if(pm&&strlen(pm)>0&&pm[strlen(pm)-1]!='\n')cout<<endl;cout<<"--------------------"<<endl<<endl;} void set_print_memo(Person&p,const char*m){cout<<"p.setMemo(memo)"<<endl;p.setMemo(m);print_memo(p);} void changeAddress(){Person p_loc("p",1,70,true,"Gwangju");set_print_address(p_loc,"short address");set_print_address(p_loc,"middle length Address, Seoul");set_print_address(p_loc,"long length Address Seoul Mapo-gu Korea");set_print_address(p_loc,u.getAddress());} void changeMemo(){Person p_loc("p",1,70,true,"Gwangju");set_print_memo(p_loc,"short memo\n");set_print_memo(p_loc,"middle long memo: The Last of the Mohicans\n");set_print_memo(p_loc,u.getMemo());} void manageMemo(){memo.c_str(u.getMemo());memo.run();cout<<"\nmemo.run() returned"<<endl;u.setMemo(memo.c_str());print_memo(u);} Person call_by_value_and_return_value(Person p_val){cout<<"p.setName(p)"<<endl;p_val.setName("p");cout<<"p2: ";return p_val;} void copyConstructor(){cout<<"u: ";u.println();print_memo(u);cout<<"Person p1(u)"<<endl;cout<<"p1: ";Person p1(u);p1.setName("p1");p1.println();print_memo(p1);cout<<"Person p2 = call_by_value_and_return_value(p1)"<<endl;cout<<"p: ";Person p2=call_by_value_and_return_value(p1);cout<<"call_by_value_and_return_value(p1) returned\n"<<endl;cout<<"p2.setName(p2)"<<endl;p2.setName("p2");p2.println();print_memo(p2);cout<<"copyConstructor() returns"<<endl;} void nullptrMember(){u.println();print_memo(u);cout<<"set address = memo_c_str = nullptr"<<endl;u.setAddress(nullptr);u.setMemo(nullptr);u.println();print_memo(u);cout<<"memo.c_str(u.getMemo())"<<endl;memo.c_str(u.getMemo());memo.displayMemo();cout<<endl<<"u.setMemo(memo.c_str())"<<endl;u.setMemo(memo.c_str());print_memo(u);} void inputPerson(){cout<<"u: ";u.println();while(!inputPersonFromUser(&u));cout<<"u: ";u.println();} public: AllocatedMember():u("u",1,70,true,"NAMDAEMUN-RO 123, JONGNO-GU, SEOUL, KOREA"){u.setMemo("It is believed that the Aborigines of the American continent");} void run(){using func_t=void(AllocatedMember::*)();func_t func_arr[]={nullptr,&AllocatedMember::changeAddress,&AllocatedMember::changeMemo,&AllocatedMember::manageMemo,&AllocatedMember::copyConstructor,&AllocatedMember::nullptrMember,&AllocatedMember::inputPerson};int menuCount=sizeof(func_arr)/sizeof(func_arr[0]);string menuStr="++++++++++++++++ Allocated Member Menu ++++++++++++++++\n+ 0.Exit 1.ChangeAddress 2.ChangeMemo 3.UsingMemoMenu +\n+ 4.CopyConstructor 5.NullptrMember 6.inputPerson     +\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";while(true){int menuItem=UI::selectMenu(menuStr,menuCount);if(menuItem==0)return;if(menuItem>=menuCount||func_arr[menuItem]==nullptr){cout<<menuItem<<": OUT of selection range(0 ~ "<<menuCount-1<<")"<<endl;continue;}(this->*func_arr[menuItem])();}}};

//******************************************************************************
// VectorOperator class (as provided in original)
//******************************************************************************
class VectorOperator { Person pa[5]={Person("Hong ",0,72.1,true,nullptr),Person("Mong ",1,65.4,true,nullptr),Person("Choon",3,56.7,true,nullptr),Person("Soon ",2,87.6,true,nullptr),Person("Chung",4,67.8,true,nullptr),}; int pa_len=sizeof(pa)/sizeof(pa[0]); VectorPerson pv1,pv2; void disp_vector(const VectorPerson&pv){int count=pv.size();cout<<"count "<<count<<endl;for(int i=0;i<count;++i){cout<<"["<<i<<"] ";pv[i]->println();}cout<<endl;} public: VectorOperator(){int i;for(i=0;i<2;++i)pv1.push_back(&pa[i]);/*cout<<"pv1: ";disp_vector(pv1);*/for(;i<pa_len;++i)pv2.push_back(pa+i);/*cout<<"pv2: ";disp_vector(pv2);*/} void operatorIndex(){MultiManager().run();} void operatorNot(){cout<<boolalpha;VectorPerson pv;disp_vector(pv);if(pv)cout<<"if(pv): true\n";else cout<<"if(pv): false\n";cout<<"operator bool(): "<<(bool)pv<<endl;if(!pv)cout<<"if(!pv): true\n";else cout<<"if(!pv): false\n";cout<<"operator !(): "<<!pv<<endl;pv.push_back(pa);disp_vector(pv);cout<<"(pv? true: false) "<<(pv?true:false)<<endl;pv.push_back(new Person("Chung",2,67.8,true,nullptr));disp_vector(pv);cout<<"pv[0]: ";pv[0]->println();cout<<"delete pv[1];"<<endl;delete pv[1]; pv.erase(1); } VectorPerson call_return_value(VectorPerson pv){cout<<"pv: ";disp_vector(pv);cout<<"return pv1 "<<endl;return pv1;} void copyConstructor(){cout<<"VectorPerson pv3 = pv2"<<endl;VectorPerson pv3=pv2;cout<<"pv3: ";disp_vector(pv3);pv3.erase(0);cout<<"pv3.erase(0)"<<endl;cout<<"pv3: ";disp_vector(pv3);cout<<"pv2: ";disp_vector(pv2);cout<<"disp_vector(call_return_value(vp2))"<<endl;disp_vector(call_return_value(pv2));cout<<"pv1: ";disp_vector(pv1);} void operatorAssign(){cout<<"VectorPerson pv3 = pv2"<<endl;VectorPerson pv3=pv2;cout<<"pv3: ";disp_vector(pv3);cout<<"pv3 = pv1"<<endl;pv3=pv1;cout<<"pv3: ";disp_vector(pv3);cout<<"repeat 9 times: pv3.push_back(pa+2)"<<endl;for(int i=0;i<9;++i)pv3.push_back(pa+2);cout<<"pv3: ";disp_vector(pv3);VectorPerson pv4;cout<<"pv4 = pv3"<<endl;pv4=pv3;cout<<"pv4: ";disp_vector(pv4);} void operatorAdd(){VectorPerson pv3;cout<<"pv3 = pv1 + pv2"<<endl;pv3=pv1+pv2;cout<<"pv3: ";disp_vector(pv3);cout<<"pv3 = pv2 + pv2 + pv3"<<endl;pv3=pv2+pv2+pv3;cout<<"pv3: ";disp_vector(pv3);} void operatorAddAssign(){cout<<"VectorPerson pv4 = pv1:"<<endl;VectorPerson pv4=pv1;cout<<"pv4: ";disp_vector(pv4);cout<<"pv4 += pv2"<<endl;pv4+=pv2;cout<<"pv4: ";disp_vector(pv4);cout<<"pv4 += pv2 + pv2"<<endl;pv4+=pv2+pv2;cout<<"pv4: ";disp_vector(pv4);} void run(){using VO=VectorOperator;using func_t=void(VO::*)();func_t func_arr[]={nullptr,&VO::operatorIndex,&VO::operatorNot,&VO::copyConstructor,&VO::operatorAssign,&VO::operatorAdd,&VO::operatorAddAssign};int menuCount=sizeof(func_arr)/sizeof(func_arr[0]);string menuStr="+++++++++++++ Vector Operator Overload ++++++++++++++\n+ 0.Exit 1.operator[] 2.operator! 3.CopyConstructor +\n+ 4.operator= 5.operator+ 6.operator=+           +\n+++++++++++++++++++++++++++++++++++++++++++++++++++++\n";while(true){int menuItem=UI::selectMenu(menuStr,menuCount);if(menuItem==0)return;if(menuItem>=menuCount||func_arr[menuItem]==nullptr){cout<<menuItem<<": OUT of range"<<endl;continue;}(this->*func_arr[menuItem])();}}};

//******************************************************************************
// OperatorOverload class (as provided in original)
//******************************************************************************
class OperatorOverload { Person p; Memo m; void disp_memo(const string&n,Memo&m_ref){cout<<n<<endl;m_ref.displayMemo();cout<<endl;} void memoAdd(){Memo m1(m);Memo m2("JF Cooper\n");disp_memo("m1",m1);disp_memo("m2",m2);Memo m3=m1+m2;disp_memo("m3=m1+m2",m3);m3+=Memo("1st\n");disp_memo("m3+=",m3);m3=m3+m2+Memo("2nd\n");disp_memo("m3=m3+m2+",m3);} void personEqual(){Person p1(p),p2(p);cout<<"p1: ";p1.println();cout<<"p2: ";p2.println();cout<<"p1==p2: "<<(p1==p2)<<endl;p2.set(2);cout<<"p2: ";p2.println();cout<<"p1==p2: "<<(p1==p2)<<endl;p2.set(1);p2.setName("user");cout<<"p2: ";p2.println();cout<<"p1==p2: "<<(p1==p2)<<endl;} void personAdd(){Person p1(p);p1.setAddress("");cout<<"p1: ";p1.println();Person p2=p1+5.0;cout<<"p2: ";p2.println();cout<<"(p2+10.0).println()"<<endl;cout<<"tmp: ";(p2+10.0).println();cout<<"p2: ";p2.println();Person p3=15.0+p1;cout<<"p3: ";p3.println();cout<<"(20.0+p3).println()"<<endl;cout<<"tmp: ";(20.0+p3).println();cout<<"p3: ";p3.println();} void assignPerson(){Person p1(p);Person p2;cout<<"p: ";p.println();cout<<"p2=p"<<endl;p2=p;cout<<"p2: ";p2.println();Person p3("Hong",0,72.1,false,"Gwangju");cout<<"p3: ";p3.println();cout<<"p3=20.0+p2+30.5"<<endl;p3=20.0+p2+30.5;cout<<"p3: ";p3.println();cout<<"p==p3 : true"<<endl;} public: void currentUser(){CurrentUser(p).run();m.c_str(p.getMemo());cout<<"p: ";p.println();m.displayMemo();} void vectorOOL(){VectorOperator().run();} void print_name_id(string n,int i){cout<<"print_name_id() name:"<<n<<", id:"<<i<<endl;} void typeConversion(){Person p1(p),p2(p);p1<<"Hong"<<1;p2<<"Dong"<<2;cout<<"p1: ";p1.println();cout<<"p2: ";p2.println();int id_v=p1;string name_v=p1;cout<<"p1 name:"<<name_v<<", id:"<<id_v<<endl;p2>>id_v>>name_v;cout<<"p2 name:"<<name_v<<", id:"<<id_v<<endl;print_name_id(p1,p1);print_name_id(p2,p2);cout<<"p2 name:"<<(string)p2<<", id:"<<(int)p2<<endl;cout<<"p1+p2 name:"<<(string)p1+name_v<<", id:"<<(int)p1+id_v<<endl;} void personShift(); void personIncrement(){cout<<boolalpha;Person p1(p);p1.setAddress("");cout<<"p1: ";p1.println();cout<<"++p1: ";(++p1).println();cout<<"p1++: ";(p1++).println();cout<<"p1: ";p1.println();Person p2=p1++;cout<<"p2: ";p2.println();cout<<"p1: ";p1.println();p2=(++p1)++;cout<<"p2: ";p2.println();cout<<"p1: ";p1.println();p2=++(p1++);cout<<"p2: ";p2.println();cout<<"p1: ";p1.println();p2=++p1++;cout<<"p2: ";p2.println();cout<<"p1: ";p1.println();cout<<"(p2=2.0 + ++p1++ + 3.0)==p : "<<((p2=2.0 + ++p1++ + 3.0)==p)<<endl;cout<<"p2: ";p2.println();cout<<"p1: ";p1.println();} OperatorOverload():p("p",1,65.4,true,"Jong-ro 1-gil, Jongno-gu, Seoul"),m("The Last of the Mohicans\n"){} void run(){using func_t=void(OperatorOverload::*)(); func_t func_arr[]={nullptr,&OperatorOverload::memoAdd,&OperatorOverload::personEqual,&OperatorOverload::personAdd,&OperatorOverload::assignPerson,&OperatorOverload::personIncrement,&OperatorOverload::personShift,&OperatorOverload::typeConversion,&OperatorOverload::currentUser,&OperatorOverload::vectorOOL,};int menuCount=sizeof(func_arr)/sizeof(func_arr[0]);string menuStr="+++++++++++++++++++ Operator Overload +++++++++++++++++\n+ 0.Exit 1.MemoAdd 2.Equal 3.Add 4.Assign 5.Increment +\n+ 6.Shift 7.TypeConversion 8.CurrentUser 9.VectorOOL  +\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";while(true){int menuItem=UI::selectMenu(menuStr,menuCount);if(menuItem==0)return;if(menuItem>=menuCount||func_arr[menuItem]==nullptr){cout<<menuItem<<": OUT of selection range(0 ~ "<<menuCount-1<<")"<<endl;continue;}(this->*func_arr[menuItem])();}}};
void OperatorOverload::personShift(){Person p1(p);p1.setAddress("");cout<<"p1: ";p1.println();cout<<"p1<<\"p1\"<<11"<<endl;p1<<"p1"<<11;cout<<"p1: ";p1.println();cout<<"p1<<name<<12"<<endl;string name_loc("p1-12");p1<<name_loc<<12;cout<<"p1: ";p1.println();cout<<"p1>>name>>id>>c_name"<<endl;int id_loc;char c_name_loc[40];name_loc="";p1>>name_loc>>id_loc>>c_name_loc;cout<<"name:"<<name_loc<<", id:"<<id_loc<<", c_name:"<<c_name_loc<<endl;cout<<"(p1<<\"p\"<<1)==p : ";cout<<((p1<<"p"<<1)==p?"true":"false")<<endl;cout<<"p1: ";p1.println();cout<<"p : ";p.println();}

//******************************************************************************
// CopyConstructor class (as provided in original)
//******************************************************************************
class CopyConstructor {

    Person u;
    Person backup;

public:
    CopyConstructor() : u("u", 1, 70, true, "Gwangju"), backup(u) {}

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
    void function_argument(Person a_val);
    void call_by_reference(Person& p_ref);
    void call_by_value(Person p_val);
    void call_by_address(Person* p_ptr);
    void explicitCopyConstructor();
    void referenceVariable();
    // void function_argument(); // 중복 선언 가능성 제거 (원본 주석 반영)
    void implicitCopyConstructor();
    void temporaryObject();
    void functionParameterType();
    void run();
};

Person CopyConstructor::return_value() {
    return u;
}

void CopyConstructor::return_value_test() {
    cout << "---rt_val_test---" << endl;
    Person p_loc = return_value();
    cout << "ret_val() ret" << endl;
    cout << "p: "; p_loc.println();
    p_loc.set("p", 2, 80, false, "Seoul");
    cout << "p: "; p_loc.println();
    cout << "u: "; u.println();
}

Person& CopyConstructor::return_reference() {
    return u;
}

void CopyConstructor::return_reference_test() {
    cout << "---rt_ref_test---" << endl;
    Person p_loc = return_reference();
    cout << "ret_ref() ret" << endl;
    p_loc.set("p", 2, 80, false, "Seoul");
    cout << "p: "; p_loc.println();
    cout << "u: "; u.println();
    cout << endl;
    Person& r_loc = return_reference();
    cout << "ret_ref() ret" << endl;
    cout << "u: "; u.println();
    r_loc.set("r", 2, 80, false, "Seoul");
    cout << "r: "; r_loc.println();
    cout << "u: "; u.println();
    u = backup;
}

Person* CopyConstructor::return_address() {
    return &u;
}

void CopyConstructor::return_address_test() {
    cout << "---rt_addr_test---" << endl;
    Person* p_ptr = return_address();
    cout << "ret_addr() ret" << endl;
    cout << "p: "; p_ptr->println();
    cout << "u: "; u.println();
    p_ptr->set("p", 2, 80, false, "Seoul");
    cout << "p: "; p_ptr->println();
    cout << "u: "; u.println();
    u = backup;
}

void CopyConstructor::returnDataType() {
    return_value_test(); cout << endl;
    return_reference_test(); cout << endl;
    return_address_test();
}

void CopyConstructor::functionParameterType() {
    cout << "call_by_value" << endl;
    call_by_value(u);
    cout << endl;
    cout << "call_by_reference" << endl;
    call_by_reference(u);
    cout << endl;
    cout << "call_by_address" << endl;
    call_by_address(&u);
    cout << endl;
}

void CopyConstructor::call_by_reference(Person& p_ref) {
    cout << "p: "; p_ref.println();
    cout << "u: "; u.println();
    p_ref.set("p", 2, 80, false, "Seoul");
    cout << "p: "; p_ref.println();
    cout << "u: "; u.println();
    u = backup;
}

void CopyConstructor::call_by_address(Person* p_ptr) {
    cout << "p: "; p_ptr->println();
    cout << "u: "; u.println();
    p_ptr->set("p", 2, 80, false, "Seoul");
    cout << "p: "; p_ptr->println();
    cout << "u: "; u.println();
    u = backup;
}

void CopyConstructor::call_by_value(Person p_val) {
    cout << "p: "; p_val.println();
    cout << "u: "; u.println();
    p_val.set("p", 2, 80, false, "Seoul");
    cout << "p: "; p_val.println();
    cout << "u: "; u.println();
}

Person CopyConstructor::return_local_object() {
    Person pL("pL", 0, 70, true, "Gwangju Nam-gu");
    cout << "ret_local_obj() ret pL" << endl;
    return pL;
}

Person CopyConstructor::return_temporary_object() {
    cout << "ret_temp_obj() ret Person(...)" << endl;
    return Person("pT", 0, 70, true, "Gwangju Nam-gu");
}

void CopyConstructor::temporaryObject() {
    cout << "temp obj 1" << endl;
    Person("p0", 10, 70, true, "Gwangju");
    cout << "\ntemp obj 2" << endl;
    Person("p1", 11, 60, false, "Seoul").println();
    cout << "\nret_mem_obj().println()" << endl;
    return_member_object().println();
    cout << "ret_mem_obj() ret" << endl;
    cout << "\nret_local_obj().println()" << endl;
    return_local_object().println();
    cout << "ret_local_obj() ret" << endl;
    cout << "\nPerson pL = ret_local_obj()" << endl;
    Person pL_loc = return_local_object();
    cout << "ret_local_obj() ret" << endl;
    pL_loc.println();
    cout << "\nret_temp_obj().println()" << endl;
    return_temporary_object().println();
    cout << "ret_temp_obj() ret" << endl;
    cout << "\nPerson pT = ret_temp_obj()" << endl;
    Person pT_loc = return_temporary_object();
    cout << "ret_temp_obj() ret" << endl;
    pT_loc.println();
}

void CopyConstructor::implicitCopyConstructor() {
    cout << "u: "; u.println();
    cout << "\nimp cp_con 1" << endl;
    cout << "Person p=u" << endl;
    cout << "p: ";
    Person p_loc = u;
    cout << "p.setName(p)" << endl;
    p_loc.setName("p");
    cout << "p: "; p_loc.println();
    cout << "\nimp cp_con 2" << endl;
    cout << "call func_arg(u)" << endl;
    function_argument(u);
    cout << "func_arg(u) ret" << endl;
    cout << "\nimp cp_con 3" << endl;
    cout << "call ret_mem_obj().println()" << endl;
    return_member_object().println();
    cout << "ret_mem_obj() ret" << endl;
}

Person CopyConstructor::return_member_object() {
    return u;
}

void CopyConstructor::function_argument(Person a_val) {
    cout << "a: "; a_val.println();
    cout << "a.setName(a)" << endl;
    a_val.setName("a");
    cout << "a: "; a_val.println();
}

void CopyConstructor::explicitCopyConstructor() {
    cout << "u: "; u.println();
    Person p_loc(u);
    p_loc.setName("p");
    p_loc.set(2);
    p_loc.set(80);
    p_loc.set(false);
    p_loc.setAddress("Seoul");
    cout << "u: "; u.println();
    cout << "p: "; p_loc.println();
}

void CopyConstructor::referenceVariable() {
    cout << "p: ";
    Person p_loc(u);
    Person& r_loc = p_loc;
    cout << "p: "; p_loc.println();
    cout << "r: "; r_loc.println();
    r_loc.setName("r");
    r_loc.set(2);
    r_loc.set(80);
    r_loc.set(false);
    r_loc.setAddress("Seoul");
    cout << "p: "; p_loc.println();
    cout << "r: "; r_loc.println();
    p_loc.setName("p");
    p_loc.set(1);
    p_loc.set(70);
    p_loc.set(true);
    p_loc.setAddress("Gwangju");
    cout << "p: "; p_loc.println();
    cout << "r: "; r_loc.println();
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
    backup = u;
    cout << "u: "; u.println();
}

void CopyConstructor::run() {
    using CC = CopyConstructor;
    using func_t = void (CC::*)();
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
        "+ 3.ImplicitCopyConstructor 4.TemporaryObject         +\n"
        "+ 5.FunctionParameterType 6.FunctionReturnType        +\n"
        "+ 7.inputPerson                                         +\n"
        "++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    while (true) {
        int menuItem = UI::selectMenu(menuStr, menuCount);
        if (menuItem == 0) return;
        if (menuItem >= menuCount || func_arr[menuItem] == nullptr) {
            cout << menuItem << ": OUT of selection range(0 ~ " << menuCount - 1 << ")" << endl;
            continue;
        }
        (this->*func_arr[menuItem])();
    }
}
// 코드 추가 3
/******************************************************************************
 * ch8_1, ch8_2: Inheritance class
 ******************************************************************************/
class Inheritance
{
    Student s { "s1", 1, 65.4, true,  "Jongno-gu Seoul", "Physics", 3.8, 1 };
    Worker  w { "w1", 3, 33.3, false, "Kangnam-gu Seoul",  "Samsung", "Director" };

    void student() {
        // [문제 2] 코드 삽입
        Student s1(s);
        cout << "s1: "; s1.println();
        Student s2 = s1;
        cout << "s2: "; s2.println();

        // [문제 3] 코드 추가
        cout << "s1 == s2 : " << boolalpha << (s1 == s2) << endl;

        // [문제 4] 코드 추가
        s2.setName("s2");
        s2.set(s1.getId()+1);
        s2.set(s1.getWeight() * 1.1);
        s2.set(!s1.getMarried());
        s2.setDepartment(s1.getDepartment()+"-Electronics");
        s2.setGPA(s1.getGPA()+1.0);
        s2.setYear(s1.getYear()+1);
        cout << "s2: "; s2.println();
        cout << "s1 == s2 : " << boolalpha << (s1 == s2) << endl;

        // [문제 5] 코드 추가
        s2.whatAreYouDoing();

        // [문제 6] 코드 추가
        Student *s3 = dynamic_cast<Student*>(s1.clone());
        if (s3) {
            cout << "s3: "; s3->println();
            cout << "s1: "; s1.println();
            cout << "s3 == s1 : " << boolalpha << (*s3 == s1) << endl;
            delete s3;
        } else {
            cout << "Error: s1.clone() did not return a Student object or clone failed." << endl;
        }

        // [문제 7] 코드 추가
        cout << "input student: ";
        // Clear the input buffer robustly before calling getline-based input
        // This is crucial if the previous input was 'cin >> menu_item'
        // and UI::getInt() didn't fully consume the newline.
        cin.clear(); // Clear any error flags on cin first.
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        s2.input(cin); // This calls Person::inputMembers which uses getline

        if (UI::echo_input) { cout << "echo s2: "; s2.println(); }
        cout << "s2: "; s2.println();
        cout << "s1: "; s1.println();
        cout << "s2 == s1 : " << boolalpha << (s2 == s1) << endl;
    }

    void worker() {
        // [문제 8].1 코드 삽입
        Worker w1(w);
        cout << "w1: "; w1.println();
        Worker w2 = w1;
        cout << "w2: "; w2.println();
        cout << "w1 == w2 : " << boolalpha << (w1 == w2) << endl;

        w2.setName("w2");
        w2.set(w1.getId()+1);
        w2.set(w1.getWeight() * 1.1);
        w2.set(!w1.getMarried());
        w2.setCompany(w1.getCompany()+"-Hyundai");
        w2.setPosition(w1.getPosition()+"-Manager");
        cout << "w2: "; w2.println();
        cout << "w1 == w2 : " << boolalpha << (w1 == w2) << endl;

        w2.whatAreYouDoing();

        Worker *w3 = dynamic_cast<Worker*>(w1.clone());
        if (w3) {
            cout << "w3: "; w3->println();
            cout << "w1: "; w1.println();
            cout << "w3 == w1 : " << boolalpha << (*w3 == w1) << endl;
            delete w3;
        } else {
            cout << "Error: w1.clone() did not return a Worker object or clone failed." << endl;
        }

        cout << "input worker: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        w2.input(cin);
        if (UI::echo_input) { cout << "echo w2: "; w2.println(); }
        cout << "w2: "; w2.println();
        cout << "w1: "; w1.println();
        cout << "w2 == w1 : " << boolalpha << (w2 == w1) << endl;
    }

public:
    void run() {
        using func_t = void (Inheritance::*)();
        func_t func_arr[] = {
            nullptr, &Inheritance::student, &Inheritance::worker,
        };
        int menuCount = sizeof(func_arr) / sizeof(func_arr[0]);
        string menuStr =
            "+++++++++++++ Inheritance Menu ++++++++++++++\n"
            "+ 0.Exit 1.Student 2.Worker               +\n"
            "+++++++++++++++++++++++++++++++++++++++++++++\n";

        while (true) {
            int menuItem = UI::selectMenu(menuStr, menuCount);
            if (menuItem == 0) return;
            if (menuItem > 0 && menuItem < menuCount && func_arr[menuItem] != nullptr) {
                 (this->*func_arr[menuItem])();
            } else {
                 cout << "Invalid menu selection for Inheritance menu." << endl;
            }
        }
    }
};
// ch8_1, ch8_2: Inheritance class

//******************************************************************************
// MainMenu class
//******************************************************************************
class MainMenu{
public:
    void run() {
        // 코드 추가 4
        int menuCount = 7;
        string menuStr =
            "******************************* Main Menu *********************************\n"
            "* 0.Exit 1.PersonManager(ch3_2, 4, 6, 7_2, 8)                            *\n"
            "* 2.Class:Object(ch3_1) 3.CopyConstructor(ch5_1) 4.AllocatedMember(ch5_2) *\n"
            "* 5.OperatorOverload(ch7_1) 6.Inheritance(ch8)                           *\n"
            "***************************************************************************\n";
        while (true) {
            int menuItem = UI::selectMenu(menuStr, menuCount);
            if (menuItem == 0) break;
            switch(menuItem) {
                case 1: MultiManager().run();         break;
                case 2: ClassAndObject().run();       break;
                case 3: CopyConstructor().run();      break;
                case 4: AllocatedMember().run();      break;
                case 5: OperatorOverload().run();     break;
                case 6: Inheritance().run();          break;
                default:
                    // This case should ideally not be reached if UI::getIndex is robust.
                    // cout << "Invalid menu item selected." << endl;
                    break;
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
    // evaluate(false);
    cout << "AUTOMATIC_ERROR_CHECK is true, but evaluate() is not available." << endl;
    cout << "Running program normally." << endl;
    run();
#else
    // UI::echo_input = true; // Uncomment for debugging input
    run();
#endif
    return 0;
}