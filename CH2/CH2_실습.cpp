#include <iostream>
#include <cstring>
#define AUTOMATIC_ERROR_CHECK false
using namespace std;

struct Person {
    char   name[20];
    int    id;
    double weight;
    bool   married;
    char   address[50];
};

void print(Person* p) {
    cout << p->name << " " << p->id << " " << p->weight << " " << p->married << " :" << p->address << ":";
}

void println(Person* p) {
    print(p);
    cout << endl;
}

void input(Person* p) {
    cin >> p->name >> p->id >> p->weight >> p->married;
    if (!cin) return;
    cin.getline(p->address, sizeof(p->address), ':');
    cin.getline(p->address, sizeof(p->address), ':');
}

bool isSame(const Person* p, const char* pname, int pid) {
    return (strcmp(p->name, pname) == 0 && p->id == pid);
}

void whatAreYouDoing(Person* p) {
    cout << p->name << " is taking a rest." << endl;
}

void init(Person* p, const char *pname, int pid, double pweight, bool pmarried, const char *paddress) {
    strcpy(p->name, pname);
    p->id = pid;
    p->weight = pweight;
    p->married = pmarried;
    strcpy(p->address, paddress);
    cout << "init("; print(p); cout << ")" << endl;
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
        input(p);
        if (checkDataFormatError(&cin)) return false;
        if (echo_input) println(p);
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

Person p = { "Hong", 1, 61.1, true, "Seoul Jongno-gu Nam-ro 123" };

void printlnTest() {
    Person p1 = {};
    println(&p1);
    Person p2 = { "LeeSoonShin", 0, 70.1, true, "Gangnam Seoul" };
    println(&p2);
    Person p3{ "Hong,gildong", 1, 60.2, false, "Jongno-gu, Busan" };
    println(&p3);
    println(&p);
}

void initTest() {
    Person u1;
    init(&u1, "u1", 10, 60.0, false, "Jongno-gu, Seoul");
    Person u2;
    init(&u2, "u2", p.id, p.weight, p.married, p.address);
    println(&p);
}

void getter() {
    cout << "name:" << p.name << ", id:" << p.id << ", weight:" << p.weight << ", married:" << p.married << ", address:" << p.address << endl;
}

void setter() {
    Person u;
    strcpy(u.name, "u");
    u.id = p.id;
    u.weight = p.weight;
    u.married = p.married;
    strcpy(u.address, p.address);
    println(&u);
}

void isSameTest() {
    println(&p);
    Person u = { "Hong", 1 };
    cout << "p.isSame(): " << isSame(&p, u.name, u.id) << endl;
}

void whatAreYouDoingTest() {
    whatAreYouDoing(&p);
}

void noBoolAlphaOutput() {
    printlnTest();
    initTest();
    getter();
    setter();
    isSameTest();
    whatAreYouDoingTest();
}

void boolAlphaOutput() {
    cout << boolalpha;
    noBoolAlphaOutput();
    cout << noboolalpha;
}

void noBoolAlphaInputPerson() {
    if (UI::inputPerson(&p))
        println(&p);
}

void boolAlphaInputPerson() {
    cout << boolalpha;
    cin >> boolalpha;
    if (UI::inputPerson(&p))
        println(&p);
    cin >> noboolalpha;
    cout << noboolalpha;
}

void dataTypeSize() {
    cout << "bool   size: " << sizeof(bool)   << endl;
    cout << "char   size: " << sizeof(char)   << endl;
    cout << "short  size: " << sizeof(short)  << endl;
    cout << "int    size: " << sizeof(int)    << endl;
    cout << "long   size: " << sizeof(long)   << endl;
    cout << "float  size: " << sizeof(float)  << endl;
    cout << "double size: " << sizeof(double) << endl;
    cout << "int*   size: " << sizeof(int*)   << endl;
}

void run() {
    int menuCount = 12; // 상수 정의
    // 화면에 보여 줄 메뉴
    string menuStr =
    "+++++++++++++++++++++ Person Structure Test Menu +++++++++++++++++++++\n"
    "+ 0.Exit 1.printlnTest 2.initTest 3.getter 4.setter 5.isSameTest     +\n"
    "+ 6.whatAreYouDoingTest 7.NoBoolAlphaOutput 8.BoolAlphaOutput        +\n"
    "+ 9.NoBoolAlphaInputPerson 10.BoolAlphaInputPerson 11.DataTypeSize() +\n"
    "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    while (true) {
        int menuItem = UI::selectMenu(menuStr, menuCount);
        if (menuItem == 0) break;

        switch(menuItem) {
        case 1: printlnTest();            break;
        case 2: initTest();               break;
        case 3: getter();                 break;
        case 4: setter();                 break;
        case 5: isSameTest();             break;
        case 6: whatAreYouDoingTest();    break;
        case 7: noBoolAlphaOutput();      break;
        case 8:   boolAlphaOutput();      break;
        case 9: noBoolAlphaInputPerson(); break;
        case 10:  boolAlphaInputPerson(); break;
        case 11: dataTypeSize();          break;
        }
    }
    cout << "Good bye!!" << endl;
}

#if AUTOMATIC_ERROR_CHECK
#include "check_error.h"
#endif

int main() {
    #if AUTOMATIC_ERROR_CHECK
        evaluate(true);
    #else
        run();
    #endif
}