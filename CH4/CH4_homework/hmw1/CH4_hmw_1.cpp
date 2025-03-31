#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#define AUTOMATIC_ERROR_CHECK true
using namespace std;

class Person
{
    string name;            // 이름
    int    id;              // Identifier
    double weight;          // 체중
    bool   married;         // 결혼여부
    char   address[40];     // 주소
    string rawInput;

protected:
    void inputMembers(istream* in);
    void printMembers(ostream* out);

public:
    Person();
    Person(const string name);
    Person(const string name, int id, double weight, bool married, const char *address);
    ~Person();

    void set(const string name, int pid, double pweight, bool pmarried, const char *paddress);
    void setName(const string name)       { this->name = name; }
    void setId(int pid)                   { id = pid; }
    void setWeight(double pweight)        { weight = pweight; }
    void setMarried(bool pmarried)        { married = pmarried; }
    void setAddress(const char* paddress) { strcpy(address, paddress); }

    string      getName()    { return name; }
    int         getId()      { return id; }
    double      getWeight()  { return weight; }  // 구현 시
    bool        getMarried() { return married; }  // 리턴 값들을
    const char* getAddress() { return address; } // 수정하시오.

    void input(istream* pin)  { inputMembers(pin); } // ch3_2에서 추가
    void print(ostream* pout) { printMembers(pout); }
    void println()            { print(&cout); cout << endl; }
    void whatAreYouDoing();                          // ch3_2에서 추가
    bool isSame(const string name, int pid);         // ch3_2에서 추가
};

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

    // 1. 이름, id, 몸무게, 결혼 여부, ':' 구분까지
    if (!(iss >> t_name >> t_id >> t_weight >> t_married_str >> colon) || colon != ':') {
        pin->setstate(ios::failbit);
        return;
    }

    // 2. 결혼 여부 bool 처리
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

void Person::whatAreYouDoing() {
    cout << name << " is taking a rest." << endl;
}

bool Person::isSame(const string name, int pid) {
    return (this->name == name && this->id == pid);
}


Person::Person(): name{}, id{}, weight{}, married{}, address{} {
    // 위 함수 서두(:와 함수 본체 사이)에서 각 멤버를 초기화하는데 이는 함수 진입하기 전에
    // 각 멤버의 값을 초기화하는 것이다. {}는 각 데이타 타입별로 디폴트 값으로 초기화하라는 의미임.
    // 즉, name[]={'\0'}="", id=0, weight=0.0, married=false, address[]={'\0'}=""
    cout << "Person::Person():"; println();
}

Person::Person(const string name) : id(0), weight(0.0), married(false), address{} {
    setName(name);
    cout << "Person::Person(\"" << name << "\"):"; println();
}

Person::Person(const string name, int id, double weight, bool married, const char *address)
    : name(name), id{id}, weight{weight}, married{married} {
    setAddress(address);  // 여전히 문자열 처리 및 복사가 필요한 경우
    cout << "Person::Person(...):"; println();
}

Person::~Person() {
    cout << "Person::~Person():"; println();
}

void Person::printMembers(ostream* pout) {
    *pout << name << " " << id << " " << weight << " "
          << (married ? "true" : "false") << " :"
          << address << ":";
}

namespace UI {

bool echo_input = false;
string line, emptyLine;

// 입력에서 정수 대신 일반 문자가 입력되었는지 체크하고 에러 발생시 에러 메시지 출력
bool checkInputError(istream* pin, const string msg) {
    if (!(*pin)) { // 에러가 발생했다면
        cout << msg;  // 에러 메시지를 출력
        pin->clear(); // 에러 발생 상태정보를 리셋함; 그래야 다음 문장에서 읽을 수 있음
        getline(*pin, emptyLine); // 에러가 발생한 행 전체를 읽어 데이터를 버림
        return true;
    }
    return false;
}


// 정수나 실수를 입력해야 하는 곳에 일반 문자열을 입력한 경우의 에러 체크
bool checkDataFormatError(istream* pin) {
    return checkInputError(pin, "Input-data format MISMATCHED\n");
}

// 한 사람의 정보 즉, 각 멤버 데이터를 순서적으로 입력 받아 p에 저장하고
// 입력 중 입력 데이터에 오류가 있는지 확인하고 오류가 있을 시 에러 메시지를 출력한다.
bool inputPerson(Person* p) {
    cout << "input person information:" << endl;
    p->input(&cin);
    if (echo_input) p->println(); // 자동체크에서 사용됨
    return true;
}

// 하나의 정수를 입력 받음; 정수가 아닌 아닌 문자열 입력시 에러 메시지 출력 후 재입력 받음
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

// 하나의 양의 정수를 입력 받음; 음수 입력시 에러 메시지 출력 후 재입력 받음
int getPositiveInt(const string msg) {
    int value;
    while ((value = getInt(msg)) < 0)
        cout << "Input a positive INTEGER." << endl;
    return value;
}

// 0~(size-1)사이의 선택된 메뉴 항목 또는 리스트의 항목의 인덱스 값을 리턴함
// 존재하지 않는 메뉴항목을 선택한 경우 에러 출력
int getIndex(const string msg, int size) {
    while (true) {
        int index = getPositiveInt(msg);
        if (0 <= index  && index < size) return index;
        cout << index << ": OUT of selection range(0 ~ "
             << size-1 << ")" << endl;
    }
}

// 사용자에게 메뉴를 보여주고 사용자가 선택한 메뉴항목의 인덱스를 리턴함
int selectMenu(const string menuStr, int menuItemCount) {
    cout << endl << menuStr;
    return getIndex("Menu item number? ", menuItemCount);
}

} // namespace UI

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
};

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
    func_t func_arr[] = {
        nullptr, &CurrentUser::display, &CurrentUser::getter, &CurrentUser::setter,
        &CurrentUser::set, &CurrentUser::whatAreYouDoing,
        &CurrentUser::isSame, &CurrentUser::inputPerson,
    };
    int menuCount = sizeof(func_arr) / sizeof(func_arr[0]); // func_arr[] 배열의 길이
    string menuStr =
        "+++++++++++++++++++++ Current User Menu ++++++++++++++++++++++++\n"
        "+ 0.Logout 1.Display 2.Getter 3.Setter 4.Set 5.WhatAreYouDoing +\n"
        "+ 6.IsSame 7.InputPerson                                       +\n"
        "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    while (true) {
        int menuItem = UI::selectMenu(menuStr, menuCount);
        if (menuItem == 0) return;
        (this->*func_arr[menuItem])();
    }
}
// ch3_2: CurrentUser class

/******************************************************************************
 * ch3_2: MultiManager class
 ******************************************************************************/

class MultiManager
{
    Person person {"p0", 0, 70.0, false, "Gwangju Nam-gu Bongseon-dong 21"};
public:
    void currentUser() {
        CurrentUser(&person).run();
    }
}; // ch3_2: MultiManager class

// Person gps("gps", 1000, 100, true, "gps adress");
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
        // static Person sps("sps", 2000, 200, false, "sps adress");
    }

    void globalStaticLocalObjects() { // Menu item 4
        global_static_local_objects_inner();
        cout << "--- global_static_local_objects_inner() returned ---" << endl;
        global_static_local_objects_inner();
        cout << "--- global_static_local_objects_inner() returned ---" << endl;
    }

public:
    // 사용자가 선택한 메뉴 항목을 실행하는 멤버 함수(func_arr[menuItem]에 등록된 함수)를 호출
    void run() {
        // ClassAndObject의 멤버 함수에 대한 포인터 타입인 새로운 데이타 타입 func_t를 정의함
        using func_t = void (ClassAndObject::*)();
        // 위 using 문은 ClassAndObject 클래스의 멤버 함수(리턴 타입이 void 이면서 매개변수가 없는)에
        // 대한 포인터 타입을 앞으로는 간단히 func_t로 사용하겠다는 의미이다.

        // ClassAndObject의 멤버 함수 포인터들의 배열
        // 나중에 호출하기 위해 멤버 함수의 이름을 미리 배열에 저장(등록)
        //     함수 이름이 곧 함수에 대한 포인터임: 즉, 함수의 첫번째 명령어의 주소를 저장함
        // 등록된 이 멤버 함수들은 나중에 run()에서 호출됨
        //     (즉, 함수 주소로 jump 해 가서 함수를 실행함)

        func_t func_arr[] = { // 메뉴항목을 실행하는 멤버 함수를 배열에 미리 저장(등록)해 둠
            nullptr, &ClassAndObject::defualConstructor, &ClassAndObject::constructor,
            &ClassAndObject::construcorDestructor, &ClassAndObject::globalStaticLocalObjects,
        };
        int menuCount = sizeof(func_arr) / sizeof(func_arr[0]);
        // func_arr[]의 원소의 개수 = 배열 전체 크기 / 한 배열 원소의 크기

        // 화면에 보여 줄 메뉴
        string menuStr =
            "+++++++++++ Person Class And Object Menu ++++++++++++\n"
            "+ 0.Exit 1.DefualConstructor 2.Constructor          +\n"
            "+ 3.ConstrucorDestructor 4.GlobalStaticLocalObjects +\n"
            "+++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

        while (true) {
            int menuItem = UI::selectMenu(menuStr, menuCount); // 메뉴 번호 입력 받음
            if (menuItem == 0) return;
            (this->*func_arr[menuItem])(); // 선택된 메뉴 항목을 실행할 멤버 함수를 호출함
            /* 위 문장은 다음을 간단히 한 것이다. 앞으로 계속 나올테니 잘 이해하기 바란다.
                func_t f = func_arr[menuItem];// 배열에 저장된 멤버 함수 포인터
               (this->*f)();                 // 멤버함수 포인터를 이용하여 해당 함수를 호출함
            */
        }
    }
}; // ch3_1: class ClassAndObject


/******************************************************************************
 * Main Menu
 ******************************************************************************/

class MainMenu{
public:
    void run() {
        int menuCount = 3; // 상수 정의
        string menuStr =
"******************************* Main Menu *********************************\n"
"* 0.Exit 1.CurrentUser(ch3_2, 4_1)                                        *\n"
"* 2.Class:Object(ch3_1)                                                   *\n"
"***************************************************************************\n";

        while (true) { 
            int menuItem = UI::selectMenu(menuStr, menuCount);
            if (menuItem == 0) break;

            switch(menuItem) {
            case 1: MultiManager().currentUser();     break;
            case 2: ClassAndObject().run();           break;
            }
        }
        cout << "Good bye!!" << endl;
    }
}; // class MainMenu


void run() {
    MainMenu().run();
    // MainMenu 타입의 이름 없는 임시객체를 생성한 후
    // 그 객체의 run() 멤버함수를 호출함; run()에서 리턴한 후에는 임시객체가 자동 소멸됨
    // 즉, 위 문장은 아래 두 문장과 동일한 기능임
    // MainMenu mm;
    // mm.run();
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