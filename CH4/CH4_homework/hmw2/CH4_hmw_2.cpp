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
    string name;            // 이름
    int    id;              // Identifier
    double weight;          // 체중
    bool   married;         // 결혼여부
    char   address[40];     // 주소
    string rawInput;
    string passwd;
protected:
    void inputMembers(istream* in);
    void printMembers(ostream* out);
    public:
    // 문제 3-1, 3-2, 3-3 위임 생성자: 선언부에서 직접 타겟 생성자 호출
    Person() : Person("", 0, 0.0, false, "") { }  // 문제 3-1
    Person(const string name) : Person(name, 0, 0.0, false, "") { }  // 문제 3-2

    // 타겟 생성자
    Person(const string name, int id, double weight, bool married, const char *address)
        : name(name), id{id}, weight{weight}, married{married} {
        setAddress(address);
        cout << "Person::Person(...):"; println();
    }

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
//*****************************************************************************/

//*****************************************************************************
// VectorPerson objects 
//*****************************************************************************/
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
// Namespace
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
public:
    CurrentUser(Person* pUser): pUser(pUser) { }  // user(u)는 this->user = u 와 동일한 기능
    void display();
    void setter();
    void getter();
    void set();
    void whatAreYouDoing();
    void isSame();
    void inputPerson();
    void run();
    void changePasswd();
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
        &CU::isSame, &CU::inputPerson, &CU::changePasswd
    };
    int menuCount = sizeof(func_arr) / sizeof(func_arr[0]);
    string menuStr =
        "+++++++++++++++++++++ Current User Menu ++++++++++++++++++++++++\n"
        "+ 0.Logout 1.Display 2.Getter 3.Setter 4.Set 5.WhatAreYouDoing +\n"
        "+ 6.IsSame 7.InputPerson 8.ChangePasswd(4_2)                   +\n"
        "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    while (true) {
        int menuItem = UI::selectMenu(menuStr, menuCount);
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

    for (int i = 0; i < len; ++i) {
        Person* s = array[i];
        Person* copy = new Person(
            s->getName(),
            s->getId(),
            s->getWeight(),
            s->getMarried(),
            s->getAddress()
        );
        persons.push_back(copy);
    }

    display();
}

PersonManager::~PersonManager() {
    deleteElemets();
    display();
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
        "= 0.Exit 1.Display 2.Append 3.Clear 4.Login(CurrentUser, ch4_2) =\n"
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
// MainMenu class 
//******************************************************************************
class MainMenu{
public:
    void run() {
        int menuCount = 3; // 상수 정의
        string menuStr =
"******************************* Main Menu *********************************\n"
"* 0.Exit 1.PersonManager(ch3_2, 4)                                        *\n"
"* 2.Class:Object(ch3_1)                                                   *\n"
"***************************************************************************\n";
        while (true) { 
            int menuItem = UI::selectMenu(menuStr, menuCount);
            if (menuItem == 0) break;
            switch(menuItem) {
            case 1: MultiManager().run();             break;
            case 2: ClassAndObject().run();           break;
            }
        }
        cout << "Good bye!!" << endl;
    }
}; 
//******************************************************************************
// MultiManager class end point
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