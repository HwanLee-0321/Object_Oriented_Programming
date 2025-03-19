#include <iostream>
#include <cstring>
#define AUTOMATIC_ERROR_CHECK false
using namespace std;

class Person 
{
    char   name[20];        // 이름
    int    id;              // Identifier
    double weight;          // 체중
    bool   married;         // 결혼여부
    char   address[40];     // 주소

protected:
    void printMembers(ostream* out);

public:
    Person();
    Person(const char *name);
    Person(const char *name, int id, double weight, 
           bool married, const char *address);
    ~Person();

    void setName(const char* pname)       { strcpy(name, pname); }
    void setAddress(const char* paddress) { /* TODO: [문제 2] */ }

    void input(istream* pin)  {  }
    void print(ostream* pout) { printMembers(pout); }
    void println()            { print(&cout); cout << endl; }
};

Person::Person(): name{}, id{}, weight{}, married{}, address{} {
    // 위 함수 서두(:와 함수 본체 사이)에서 각 멤버를 초기화하는데 이는 함수 진입하기 전에 
    // 각 멤버의 값을 초기화하는 것이다. {}는 각 데이타 타입별로 디폴트 값으로 초기화하라는 의미임. 
    // 즉, name[]={'\0'}="", id=0, weight=0.0, married=false, address[]={'\0'}=""
    cout << "Person::Person():"; println();
}

Person::Person(const char *name) /* : TODO [문제 2] */ {
    // TODO: [문제 2] 
    cout << "Person::Person(\"" << name << "\"):"; println();
}

Person::Person(const char *name, int id, double weight, bool married, 
               const char *address) :
        id{id}, weight{weight}, married{married} {
    // 위에서 각 멤버를 초기화하는 {}는 각 매개변수 값을 객체의 상응하는 멤버에 설정하는 것이다. 즉,
    // this->id=id, this->weight=weight, this->married=married와 동일하다.
    // 여기서 this는 해당 객체를 포인터하는 포인터 변수이며, (다음 장에서 설명될 예정임)
    // this->id는 해당 객체의 멤버 id를 지칭하며 =의 우측변수 id는 함수의 매개변수이다.
    // 값을 간단히 대입하는 것은 위처럼 하면 되지만 name[], address[]와 같은 배열 복사 함수 
    // 호출 또는 다른 함수를 호출할 때는 생성자 함수의 몸체 { } 내에서 호출해야 한다.
    
    // TODO: [문제 2] 
    cout << "Person::Person(...):"; println();
}

Person::~Person() {
    cout << "Person::~Person():"; println();
}

void Person::printMembers(ostream* pout)   {
    // TODO: [문제 1]
}

namespace UI {
    bool echo_input = false;
    string emptyLine;
    
    bool checkInputError(istream* pin, const string msg) {
        if (!(*pin)) {
            cout << msg;
            pin->clear();
            getline(*pin, emptyLine);
            return true;
        }
        return false;
    }

    bool checkDataFormatError(istream* pin) {
        return checkInputError(pin, "Input-data format MISMATCHED\n");
    }

    bool inputPerson(Person* p) {
        cout << "input person information:" << endl;
        p->input(&cin);
        if (checkDataFormatError(&cin)) return false;
        if (echo_input) p->println();
        return true;
    }

    int getInt(const string msg) {
        for (int value;;) {
            cout << msg;
            cin >> value;
            if (echo_input) cout << value << endl;
            if (checkInputError(&cin, "Input an INTEGER.\n")) continue;
            getline(cin, emptyLine);
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
            if (0 <= index && index < size) return index;
            cout << index << ": OUT of selection range(0 ~ " << size-1 << ")" << endl;
        }
    }

    int selectMenu(const string menuStr, int menuItemCount) {
        cout << endl << menuStr;
        return getIndex("Menu item number? ", menuItemCount);
    }
}

//Person gps("gps", 1000, 100, true, "gps adress");

class ClassAndObject
{
    void defualConstructor() { // Menu item 1
    }

    void constructor() { // Menu item 2: 지역객체의 다양한 생성자 및 소멸자 실행
    }

    void construcor_destructor_inner_inner() {
    }

    void construcor_destructor_inner() {
    }

    void construcorDestructor() { // Menu item 3
    }

    void global_static_local_objects_inner() {
    }

    void globalStaticLocalObjects() { // Menu item 4
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

class MainMenu
{
public:
    void run() {
        int menuCount = 2; // 상수 정의
        string menuStr =
"******************************* Main Menu *********************************\n"
"* 0.Exit 1.Class:Object(ch3_1)                                            *\n"
"***************************************************************************\n";

        while (true) {
            int menuItem = UI::selectMenu(menuStr, menuCount);
            if (menuItem == 0) break;

            switch(menuItem) {
            case 1: ClassAndObject().run();           break;
            // 위 ClassAndObject()는 임시객체(이름없는 객체)를 생성하하는 코드이고 
            // 이후 바로 해당 객체의 멤버 run()을 호출하고 run()에서 리턴된 후에는 객체 자동 소멸됨
            // 위는 다음과 같다. ClassAndObject tmp; tmp.run();
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
    cout << boolalpha;  // 11장에서 배움; bool 타입 값을 0, 1 대신 true, false로 출력하도록 설정
    cin >> boolalpha;   // bool 타입 값을 0, 1 대신 true, false로 입력 받도록 설정

#if AUTOMATIC_ERROR_CHECK
    evaluate(false);   // 각 문제에 대해 단순히 O, X만 확인하고자 할 때는 false
#else
    run();
#endif
}