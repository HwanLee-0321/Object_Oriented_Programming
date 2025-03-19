#include <iostream>
#include <limits>
#include <cstring>
#define AUTOMATIC_ERROR_CHECK false
using namespace std;

class Person 
{
    char   name[20];        // 이름
    int    id;              // Identifier
    double weight;          // 체중
    bool   married;         // 결혼여부
    char   address[50];     // 주소

protected:
    void printMembers(ostream* pout);

public:
    Person();
    Person(const char *name);
    Person(const char *name, int id, double weight, 
           bool married, const char *address);
    ~Person();

    void setName(const char* pname)       { strcpy(name, pname); }
    void setAddress(const char* paddress) { strcpy(address, paddress); }

    void input(istream* pin)  {
        pin->getline(name, 20, ' ');
        *pin >> id >> weight >> married;
        pin->ignore();
        pin->getline(address, 50);
    }
    void print(ostream* pout) { printMembers(pout); }
    void println()            { print(&cout); cout << endl; }
};

Person::Person(): id{0}, weight{0.0}, married{false} {
    name[0] = '\0';
    address[0] = '\0';
    cout << "Person::Person():"; println();
}

Person::Person(const char *name) : Person() {
    setName(name);
    cout << "Person::Person(\"" << name << "\"):"; println();
}

Person::Person(const char *name, int id, double weight, bool married, const char *address) :
        id{id}, weight{weight}, married{married} {
    setName(name);
    setAddress(address);
    cout << "Person::Person(...):"; println();
}

Person::~Person() {
    cout << "Person::~Person():"; println();
}

void Person::printMembers(ostream* pout) {
    *pout << name << " " << id << " " << weight << " " << married << " :" << address << ":";
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

    int selectMenu(const string menuStr, int menuItemCount) {
        cout << endl << menuStr;
        int menuItem;
        cin >> menuItem;
        return menuItem;
    }
}

class ClassAndObject
{
    void defualConstructor() { Person ps; }
    void constructor() {
        Person ps1;
        Person ps2("ps2");
        Person ps3("ps3", 3, 70.3, true, "ps3 address");
    }
    void construcorDestructor() {
        Person ps1("ps1");
        Person ps2("ps2");
    }
    void globalStaticLocalObjects() {}

public:
    void run() {
        using func_t = void (ClassAndObject::*)();
        func_t func_arr[] = { nullptr, &ClassAndObject::defualConstructor, &ClassAndObject::constructor,
                              &ClassAndObject::construcorDestructor, &ClassAndObject::globalStaticLocalObjects };
        int menuCount = sizeof(func_arr) / sizeof(func_arr[0]);
        string menuStr =
            "+++++++++++ Person Class And Object Menu ++++++++++++\n"
            "+ 0.Exit 1.DefualConstructor 2.Constructor          +\n"
            "+ 3.ConstrucorDestructor 4.GlobalStaticLocalObjects +\n"
            "+++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

        while (true) {
            int menuItem = UI::selectMenu(menuStr, menuCount);
            if (menuItem == 0) return;
            (this->*func_arr[menuItem])();
        }
    }
};

class MainMenu
{
public:
    void run() {
        int menuCount = 2;
        string menuStr =
"******************************* Main Menu *********************************\n"
"* 0.Exit 1.Class:Object(ch3_1)                                            *\n"
"***************************************************************************\n";
        while (true) {
            int menuItem = UI::selectMenu(menuStr, menuCount);
            if (menuItem == 0) break;
            if (menuItem == 1) ClassAndObject().run();
        }
        cout << "Good bye!!" << endl;
    }
};

void run() {
    MainMenu().run();
}

int main() {
    cout << boolalpha;
    cin >> boolalpha;
    run();
}
