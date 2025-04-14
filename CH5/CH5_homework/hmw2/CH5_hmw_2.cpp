#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#define AUTOMATIC_ERROR_CHECK false
using namespace std;
/*
 * CH5_hmw_2.cpp
 *
 *  Created on: 2025.04.15
 *      Author: Lee Jae Hwan
  *
 *  + MainMenu 수정
 *  + class Person의 두 멤버의 타입을 배열[]에서 포인터로 즉, char* address, char* memo_c_str로 변경
 *  + Person 클래스에 copyAddress(), copyMemo() 추가
 *  + Person 생성자, inputMembers(), printMembers(), setAddress(), setMemo() 수정
 *  + Person(const Person& p) 복사생성자 수정
 *  + Memo::set_c_str(): 매개변수 c_str==nullptr일 경우 ""로 설정
 *  + Person::printMembers(): address==nullptr일 경우 "" 출력
 *  + Person::inputMembers(): 지역변수 char address[40] 추가
 *  + Person::assign() 추가
 *  + CopyConstructor 멤버 함수에서 u = backup 대신 u.assign(backup)
 */
// *********************************************************
// Persson class
// ********************************************************* 
class Person
{
    string name;            // 이름
    int    id;              // Identifier
    double weight;          // 체중
    bool   married;         // 결혼여부
    char   address[40];     // 주소
    string rawInput;
    string passwd;
    char memo_c_str[1024];

protected:
    void inputMembers(istream* in);
    void printMembers(ostream* out);

public:
    Person() : Person("", 0, 0.0, false, "") { }
    Person(const string name) : Person(name, 0, 0.0, false, "") { }

    Person(const string name, int id, double weight, bool married, const char *address)
        : name(name), id{id}, weight{weight}, married{married} {
        setAddress(address);
        cout << "Person::Person(...):"; println();
    }

    Person(const Person& p);

    ~Person() {
        cout << "Person::~Person():"; println();
    }

    void set(const string name, int pid, double pweight, bool pmarried, const char *paddress);
    void setName(const string name)       { this->name = name; }
    void setId(int pid)                   { id = pid; }
    void setWeight(double pweight)        { weight = pweight; }
    void setMarried(bool pmarried)        { married = pmarried; }
    void setAddress(const char* paddress) { strcpy(address, paddress); }

    string      getName()    { return name; }
    int         getId()      { return id; }
    double      getWeight()  { return weight; }
    bool        getMarried() { return married; }
    const char* getAddress() { return address; }

    void input(istream* pin)  { inputMembers(pin); }
    void print(ostream* pout) { printMembers(pout); }
    void println()            { print(&cout); cout << endl; }

    void whatAreYouDoing();
    bool isSame(const string name, int pid);

    void setPasswd(const string& pw) { passwd = pw; }
    string getPasswd() const { return passwd; }

    // [문제 11 - 메모 저장 및 반환 함수]
    void setMemo(const char* c_str) { strcpy(memo_c_str, c_str); }
    const char* getMemo() { return memo_c_str; }
};
// *********************************************************
// Persson class end point
// ********************************************************* 

// *********************************************************
// Persson objects
// ********************************************************* 
void Person::whatAreYouDoing() {
    cout << name << " is taking a rest." << endl;
}
bool Person::isSame(const string name, int pid) {
    return (this->name == name && this->id == pid);
}
void Person::printMembers(ostream* pout) {
    *pout << name << " " << id << " " << weight << " "
        << (married ? "true" : "false") << " :"
        << address << ":";
}
void Person::set(const string name, int pid, double pweight, bool pmarried, const char *paddress) {
    setName(name);        // string으로 직접 설정
    setId(pid);
    setWeight(pweight);
    setMarried(pmarried);
    setAddress(paddress);
}
Person::Person(const Person& p):
    name(p.name), id{p.id}, weight{p.weight}, married{p.married}  {
    setAddress(p.address);
    setMemo(p.memo_c_str);
    cout << "Person::Person(const Person&):"; println();
}
void Person::inputMembers(istream* pin) {
    string line;
    getline(*pin, line);
    rawInput = line; // 그대로 저장 (출력용)
    istringstream iss(line);
    string t_name;
    int t_id;
    double t_weight;
    string t_married_str;
    bool t_married;
    char colon;
    string addrPart;
    if (!(iss >> t_name >> t_id >> t_weight >> t_married_str >> colon) || colon != ':') {
        pin->setstate(ios::failbit);
        return;
    }
    if (t_married_str == "true")
        t_married = true;
    else if (t_married_str == "false")
        t_married = false;
    else {
        pin->setstate(ios::failbit);
        return;
    }
    // 3. 주소 처리
    getline(iss, addrPart, ':');
    if (addrPart.length() >= sizeof(address))
        addrPart = addrPart.substr(0, sizeof(address) - 1);
    // 4. 실제 데이터 반영
    set(t_name, t_id, t_weight, t_married, addrPart.c_str());
}
// *********************************************************
// Persson objects end point
// ********************************************************* 

//*****************************************************************************
// VectorPerson class
//*****************************************************************************/
// VectorPerson는 n개의 Person * 포인터를 pVector[] 배열에 담아 관리하는 클래스이다.
// 필요에 따라 포인터를 삽입, 삭제, 추가 등을 할 수 있다.
// 삽입하는 포인터 개수가 점점 많아지면 pVector[] 배열을 위한 메모리를 자동 확장하기도 한다.
class VectorPerson
{
    static const int DEFAULT_SIZE = 10; // pVector의 디폴트 배열 원소 개수

    Person **pVector; // Person *pVector[]; Person에 대한 포인터들의 배열, 배열에 저장될 값이 Person *이다.
    int count;        // pVector 배열에 현재 삽입된 객체 포인터의 개수
    int allocSize;    // 할당 받의 pVector의 총 배열 원소의 개수

    void extend_capacity(); /* TODO 문제 [7] */

public:
    VectorPerson() : VectorPerson(DEFAULT_SIZE) { }
    VectorPerson(int capacity);
    ~VectorPerson();

    // 아래 긱 함수이름 뒤의 const는 그 함수가 클래스 멤버 변수들을 수정하지 않고 읽기만 한다는 의미임
    // pVector[index]의 포인터 값을 반환 
    Person* at(int index) const { if (index < 0 || index >= count) return nullptr;
        return pVector[index];
    }

    // 할당 받의 pVector의 총 배열 원소의 개수를 반환
    int     capacity()    const { return allocSize; }

    // pVector 배열에 현재 삽입된 객체 포인터의 개수를 0으로 설정
    void    clear()             { count = 0; }

    // 현재 삽입된 객체 포인터가 하나도 없으면 true, 있으면 false
    bool    empty()       const { return count == 0; }

    // 현재 삽입된 객체 포인터의 개수를 반환
    int     size()        const { return count; }

    // pVector 배열에 마지막 삽입된 원소 뒤에 새로운 원소 p를 삽입하고 현재 삽입된 객체 개수를 증가
    void    push_back(Person* p); /* TODO 문제 [4, 7] */
};
//*****************************************************************************
// VectorPerson class end point
//*****************************************************************************

//*****************************************************************************
// VectorPerson objects 
//*****************************************************************************
// capacity는 할당해야 할 배열 원소의 개수
VectorPerson::VectorPerson(int capacity)
    : count(0), allocSize(capacity) {
    cout << "VectorPerson::VectorPerson(" << allocSize << ")" << endl;
    pVector = new Person*[allocSize]; // Person* 들의 배열을 위한 동적 메모리 할당
}

VectorPerson::~VectorPerson() {
    delete[] pVector;
    cout << "VectorPerson::~VectorPerson(): pVector deleted" << endl;
}
// 여기 아래에 추가
void VectorPerson::push_back(Person* p) {
    if (count >= allocSize) {
        extend_capacity(); // (문제 7에서 구현 예정)
    }
    pVector[count++] = p;
}
void VectorPerson::extend_capacity() {
    int newAllocSize = allocSize * 2;
    Person** newVector = new Person*[newAllocSize];

    // 기존 포인터 복사
    for (int i = 0; i < count; ++i) {
        newVector[i] = pVector[i];
    }

    // 기존 배열 해제
    delete[] pVector;

    // 새 배열로 교체
    pVector = newVector;
    allocSize = newAllocSize;

    cout << "VectorPerson: capacity extended to " << allocSize << endl;
}
//*****************************************************************************
// VectorPerson objects end point
//*****************************************************************************

//*****************************************************************************
// Namespace UI
//*****************************************************************************
namespace UI {
    bool echo_input = false;
    string line, emptyLine;

    string getNext(const string msg) {
        cout << msg;
        cin >> line;
        if (echo_input) cout << line << endl;
        getline(cin, emptyLine); // flush rest of line
        return line;
    }
    string getNextLine(const string msg) {
        cout << msg;
        getline(cin, line);
        if ((line.size() > 0) && (line.back() == '\r'))
            line.pop_back();
        if (echo_input) cout << line << endl;
        return line;
    }
    bool checkInputError(istream* pin, const string msg) {
    if (!(*pin)) { // 에러가 발생했다면
        cout << msg;  // 에러 메시지를 출력
        pin->clear(); // 에러 발생 상태정보를 리셋함; 그래야 다음 문장에서 읽을 수 있음
        getline(*pin, emptyLine); // 에러가 발생한 행 전체를 읽어 데이터를 버림
        return true;
    }
    return false;
}
//*****************************************************************************
// Namespace UI end point
//*****************************************************************************
bool checkDataFormatError(istream* pin) {
    return checkInputError(pin, "Input-data format MISMATCHED\n");
}
bool inputPerson(Person* p) {
    cout << "input person information:" << endl;
    p->input(&cin);
    if (echo_input) p->println(); // 자동체크에서 사용됨
    return true;
}
int getInt(const string msg) {
    for (int value; true; ) {
        cout << msg;
        cin >> value;
        if (echo_input) cout << value << endl; // 자동체크 시 출력됨
        if (checkInputError(&cin, "Input an INTEGER.\n"))
            continue;
        getline(cin, emptyLine); // skip [enter] after the number
        return value;
    }
}
int getPositiveInt(const string msg) {
    int value;
    while ((value = getInt(msg)) < 0)
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
} 
//*****************************************************************************
// Namespace UI end point
//*****************************************************************************

//*****************************************************************************
// string and Memo class
//*****************************************************************************
class Memo{
    string mStr; // 메모를 저장해 두는 문자열

    string get_next_line(size_t* ppos);
    bool find_line(int line, size_t* start, size_t* next);
    size_t find_last_line();
public:
    string getNext(size_t* ppos);  
    void displayMemo();
    
    const char *get_c_str() { return mStr.c_str(); }
    void set_c_str(const char *c_str) { mStr = c_str;}

    void findString();
    void compareWord();
    void dispByLine();
    void deleteLine();
    void replaceLine();
    void scrollUp();
    void scrollDown();
    void inputMemo();
    void run();
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
// string and Memo objects 
//*****************************************************************************
bool Memo::find_line(int line_num, size_t* pstart, size_t* plen) {
    size_t start = 0;
    for (int i = 0; i < line_num; ++i) {
        start = mStr.find('\n', start);
        if (start == string::npos) return false;
        ++start;
    }

    *pstart = start;
    size_t end = mStr.find('\n', start);
    if (end == string::npos)
        *plen = mStr.size() - start;
    else
        *plen = end - start + 1; // 줄바꿈 포함

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
        int menuItem = UI::selectMenu(menuStr, menuCount);
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
string Memo::getNext(size_t* ppos) {
    size_t pos = *ppos, end;

    // 공백 문자들 스킵
    while (pos < mStr.size() && isspace(mStr[pos])) ++pos;

    end = pos;

    // 구두점이면 그 하나만 단어로 처리
    if (end < mStr.size() && ispunct(mStr[end])) {
        ++end;
    } else {
        // 구두점, 공백 전까지 단어
        while (end < mStr.size() && !isspace(mStr[end]) && !ispunct(mStr[end]))
            ++end;
    }

    *ppos = end;

    // 단어 길이 0이면 빈 문자열 반환
    if (end <= pos) return "";

    return mStr.substr(pos, end - pos);
}
void Memo::compareWord() {
    string next, word = UI::getNext("Word to compare? ");
    int less = 0, same = 0, larger = 0;

    for (size_t pos = 0; ; ) {
        next = getNext(&pos);
        if (next == "") break;

        if (next < word) ++less;
        else if (next == word) ++same;
        else ++larger;
    }

    cout << "less: "   << less   << endl;
    cout << "same: "   << same   << endl;
    cout << "larger: " << larger << endl;
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
    size_t start, len;
    size_t line_num = UI::getPositiveInt("Line number to delete? ");

    if (mStr.empty() || !find_line(line_num, &start, &len) || start == mStr.size()) {
        cout << "Out of line range" << endl;
        return;
    }

    mStr.erase(start, len);
    dispByLine();
}
void Memo::replaceLine() {
    size_t start, len;
    size_t line_num = UI::getPositiveInt("Line number to replace? ");

    if (!find_line(line_num, &start, &len)) {
        cout << "Out of line range" << endl;
        return;
    }

    string line = UI::getNextLine("Input a line to replace:\n");
    line += '\n';
    mStr.replace(start, len, line);
    dispByLine();
}
void Memo::scrollUp() {
    size_t start, len;

    if (mStr.empty() || !find_line(0, &start, &len)) {
        dispByLine(); // ✅ 반드시 호출하여 라벨 출력
        return;
    }

    string firstLine = mStr.substr(start, len);
    mStr.erase(start, len);

    if (!mStr.empty() && mStr.back() != '\n') {
        mStr += '\n';
    }

    mStr += firstLine;
    dispByLine(); // ✅ 항상 호출
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
    // 동적으로 Person 객체를 할당 받은 후 키보드로부터 새로 추가하고자 하는 사람의
    // 인적정보를 읽어 들여 해당 객체에 저장한 후 그 객체의 포인터를 반환한다.
    Person* inputPerson(istream* in) {
        Person* p = new Person();
        p->input(in);  // 멤버들을 입력 받음
        if (UI::checkDataFormatError(in)) { // 정수입력할 곳에 일반 문자 입력한 경우
            delete p;         // 할당한 메모리 반납
            return nullptr;   // nullptr 반환은 에러가 발생했다는 의미임
        }
        if (UI::echo_input) p->println(); // 자동체크에서 사용됨
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
    Person* pUser;
    Memo memo;
public:
    CurrentUser(Person* pUser) : pUser(pUser) {
        memo.set_c_str(pUser->getMemo());
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
}; 
//*****************************************************************************
// CurrentUser class end point
//*****************************************************************************

//*****************************************************************************
// CurrentUser class objects
//*****************************************************************************
void CurrentUser::changePasswd() {
    string newPasswd = UI::getNext("New password: ");
    pUser->setPasswd(newPasswd);
    cout << "Password changed" << endl;
}
void CurrentUser::display() { // Menu item 1
    pUser->println();
}
void CurrentUser::getter() {  // Menu item 2
    cout << "name:" << pUser->getName()
        << ", id:" << pUser->getId()
        << ", weight:" << pUser->getWeight()
        << ", married:" << (pUser->getMarried() ? "true" : "false")
        << ", address:" << pUser->getAddress() << endl;
}
void CurrentUser::setter() {  // Menu item 3
    Person ps("pp");
    ps.setName(ps.getName());
    ps.setId(pUser->getId());
    ps.setWeight(pUser->getWeight());
    ps.setMarried(pUser->getMarried());
    ps.setAddress(pUser->getAddress());
    cout << "pp->setMembers():"; ps.println();
}
void CurrentUser::set() {  // Menu item 4
    Person ps("pp");  
    ps.set(ps.getName(),
        pUser->getId(),
        pUser->getWeight(),
        !pUser->getMarried(),
        pUser->getAddress());
    cout << "pp->set():"; ps.println();
}
void CurrentUser::whatAreYouDoing() {  // Menu item 5
    pUser->whatAreYouDoing();
}
void CurrentUser::isSame() { // Menu item 6
    pUser->println();
    cout << "isSame(\"user\", 1): " << (pUser->isSame("user", 1) ? "true" : "false") << endl;
}
void CurrentUser::inputPerson() { // Menu item 7
    if (UI::inputPerson(pUser)) // GilDong 1 70.5 true :Jongno-gu, Seoul:
        display();              // user 1 71.1 true :Gwangju Nam-ro 21:
}
void CurrentUser::run() {
    using func_t = void (CurrentUser::*)();
    using CU = CurrentUser;
    func_t func_arr[] = {
        nullptr, &CU::display, &CU::getter, &CU::setter,
        &CU::set, &CU::whatAreYouDoing,
        &CU::isSame, &CU::inputPerson, &CU::changePasswd,
        &CU::manageMemo
    };
    int menuCount = sizeof(func_arr) / sizeof(func_arr[0]);
    string menuStr =
        "+++++++++++++++++++++ Current User Menu ++++++++++++++++++++++++\n"
        "+ 0.Logout 1.Display 2.Getter 3.Setter 4.Set 5.WhatAreYouDoing +\n"
        "+ 6.IsSame 7.InputPerson 8.ChangePasswd(4_2) 9.ManageMemo(4_3) +\n"
        "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    while (true) {
        int menuItem = UI::selectMenu(menuStr, menuCount);
        if (menuItem == 0) return;
        (this->*func_arr[menuItem])();
    }
}
void CurrentUser::manageMemo() { // Menu item 9
    memo.run();
    pUser->setMemo(memo.get_c_str());
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
    Factory factory;

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
}; 
//******************************************************************************
// PersonManager class end point
//******************************************************************************

//******************************************************************************
// PersonManager objects
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
    int count = UI::getPositiveInt("The number of persons to append? ");
    printNotice("Input "+to_string(count), ":");
    for (int i = 0; i < count; ++i) {
        Person* p = factory.inputPerson(&cin);
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
        CurrentUser(p).run();
}
void PersonManager::run() {
    cout << "PersonManager::run() starts" << endl; // 여기에 위치해야 함

    using func_t = void (PersonManager::*)();
    using PM = PersonManager;
    func_t func_arr[] = {
        nullptr, &PM::display, &PM::append, &PM::clear, &PM::login,
    };
    int menuCount = sizeof(func_arr) / sizeof(func_arr[0]);
    string menuStr =
        "====================== Person Management Menu ===================\n"
        "= 0.Exit 1.Display 2.Append 3.Clear 4.Login(CurrentUser, ch4)   =\n"
        "=================================================================\n";

    while (true) {
        int menuItem = UI::selectMenu(menuStr, menuCount);
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
    void globalStaticLocalObjects() { // Menu item 4
        global_static_local_objects_inner();
        cout << "--- global_static_local_objects_inner() returned ---" << endl;
        global_static_local_objects_inner();
        cout << "--- global_static_local_objects_inner() returned ---" << endl;
    }
public:
    void run() {
        using func_t = void (ClassAndObject::*)();
        func_t func_arr[] = { // 메뉴항목을 실행하는 멤버 함수를 배열에 미리 저장(등록)해 둠
            nullptr, &ClassAndObject::defualConstructor, &ClassAndObject::constructor,
            &ClassAndObject::construcorDestructor, &ClassAndObject::globalStaticLocalObjects,
        };
        int menuCount = sizeof(func_arr) / sizeof(func_arr[0]);
        string menuStr =
            "+++++++++++ Person Class And Object Menu ++++++++++++\n"
            "+ 0.Exit 1.DefualConstructor 2.Constructor          +\n"
            "+ 3.ConstrucorDestructor 4.GlobalStaticLocalObjects +\n"
            "+++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
        while (true) {
            int menuItem = UI::selectMenu(menuStr, menuCount); // 메뉴 번호 입력 받음
            if (menuItem == 0) return;
            (this->*func_arr[menuItem])(); // 선택된 메뉴 항목을 실행할 멤버 함수를 호출함
        }
    }
}; 
//******************************************************************************
// MultiManager class end point
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

void CopyConstructor::return_reference_test() { // Menu item 6-2
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
    u = backup;
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
    u = backup;
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
void CopyConstructor::call_by_reference(Person &p) { // Menu item 5-2: call by reference
    cout << "p: "; p.println();   // p는 u의 참조이므로 u와 동일한 객체 메모리를 공유함
    cout << "u: "; u.println();
    cout << "p.set(p, 2, 80, false, Seoul)" << endl;
    p.set("p", 2, 80, false, "Seoul");
    cout << "p: "; p.println();   // p와 u은 동일한 객체 메모리를 공유하므로 항상 내용이 동일함
    cout << "u: "; u.println();
    u = backup;       // u 값을 원래 값으로 복구
    // 매개변수 p는 참조이므로 함수 리턴 시 소멸자가 호출되지 않음
}
void CopyConstructor::call_by_address(Person *p) { // Menu item 5-3: call by address
    cout << "p: "; p->println();   // p는 u 메모리를 포인터하므로 동일한 내용이 출력됨
    cout << "u: "; u.println();
    cout << "p->set(p, 2, 80, false, Seoul)" << endl;
    p->set("p", 2, 80, false, "Seoul");
    cout << "p: "; p->println();   // p는 u 메모리를 포인터하므로 항상 동일한 내용이 출력됨
    cout << "u: "; u.println();
    u = backup;       // u 값을 원래 값으로 복구
    // 매개변수 p는 포인터이므로 함수 리턴 시 소멸자가 호출되지 않음
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
    p.setId(2);
    p.setWeight(80);
    p.setMarried(false);
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
    r.setId(2);
    r.setWeight(80);
    r.setMarried(false);
    r.setAddress("Seoul");
    
    cout << "p: "; p.println();
    cout << "r: "; r.println();
    
    p.setName("p");
    p.setId(1);
    p.setWeight(70);
    p.setMarried(true);
    p.setAddress("Gwangju");
    
    cout << "p: "; p.println();
    cout << "r: "; r.println();
    
    // r은 참조이므로 객체 p와 동일한 메모리를 공유 → 항상 동일한 값 출력됨
}
void CopyConstructor::inputPerson() { // Menu item 7
    cout << "u: "; u.println();
    while (true) {
        if (!UI::inputPerson(&u)) {
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
        int menuItem = UI::selectMenu(menuStr, menuCount);
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
        int menuCount = 4; // 상수 정의
        string menuStr =
"******************************* Main Menu *********************************\n"
"* 0.Exit 1.PersonManager(ch3_2, 4)                                        *\n"
"* 2.Class:Object(ch3_1) 3.CopyConstructor(ch5_1)                          *\n"
"***************************************************************************\n";
        while (true) { 
            int menuItem = UI::selectMenu(menuStr, menuCount);
            if (menuItem == 0) break;
            switch(menuItem) {
            case 1: MultiManager().run();             break;
            case 2: ClassAndObject().run();           break;    
            case 3: CopyConstructor().run();          break;    
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