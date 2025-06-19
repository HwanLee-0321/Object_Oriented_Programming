#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

/******************************************************************************
 * Person class
 ******************************************************************************/
class Person {
    string *name;  // 사람 이름
    int id;        // 고유한 ID 번호
    int hours;     // 일한 시간

public:
    Person(const string& name={}, int id=0, int hour=0);
    ~Person();
    void print(ostream& out) const;

    // 연산자 선언
    Person& operator=(const Person& rhs);
    Person operator+(int op) const; // const 추가
    int operator()() const;
    bool operator==(const Person& rhs) const;
    Person& operator++();       // 전위
    Person operator++(int);    // 후위 (추가)
    Person& operator<<(int hours_to_add);

    // friend 선언
    friend ostream& operator<<(ostream& out, const Person &p);
    friend Person& operator+=(Person& lhs, int hours_to_add);
    friend Person operator+(int hours_to_add, const Person& rhs);
};

// --- 생성자, 소멸자, print ---
Person::Person(const string& name, int id, int hours) {
    this->id = id;
    this->name = new string(name);
    this->hours = hours;
}
Person::~Person() {
    delete name;
}
void Person::print(ostream& out) const {
    out << "name(" << *name << ") ID(" << id << ") hours(" << hours << ")";
}

// --- 연산자 구현 ---
ostream& operator<<(ostream& out, const Person &p) {
    p.print(out);
    return out;
}
Person& operator+=(Person& lhs, int hours_to_add) {
    lhs.hours += hours_to_add;
    return lhs;
}
int Person::operator()() const {
    return this->hours * 8600;
}
Person& Person::operator=(const Person& rhs) {
    // [수정] 자기 대입 확인
    if (this == &rhs) {
        return *this;
    }
    *this->name = *rhs.name;
    this->id = rhs.id;
    this->hours = rhs.hours;
    return *this;
}
// [수정] const 추가
Person Person::operator+(int op) const {
    Person tmp;
    tmp = *this;
    tmp.hours += op;
    return tmp;
}
Person operator+(int hours_to_add, const Person& rhs) {
    Person tmp;
    tmp = rhs;
    tmp.hours += hours_to_add;
    return tmp;
}
bool Person::operator==(const Person& rhs) const {
    return (this->id == rhs.id) && (*this->name == *rhs.name);
}
Person& Person::operator++() { // 전위
    this->hours++;
    return *this;
}
// [추가] 후위 ++ 구현
Person Person::operator++(int) {
    Person temp;
    temp = *this;
    this->hours++;
    return temp;
}
Person& Person::operator<<(int hours_to_add) {
    *this += hours_to_add;
    return *this;
}

/******************************************************************************
 * menu_switch() 함수
 ******************************************************************************/
string menuStr =
    "---------------------- Operator ---------------------\n"
    "  0.exit  1. cout <<  2. +=  3. ()  4. =  5. +(int)  \n"
    "  6. +(int,Person)  7. ==  8. ++p  9. p++  10. p <<  \n"
    "-----------------------------------------------------\n"
    "menu item? ";

void menu_switch(int menu)
{
    Person p1("HongGD",    1, 10);
    Person p2("anonymous", 2);

    switch (menu) {
    case 1:
        cout << "p1: " << p1 << endl;
        break;
    case 2:
        cout << "p1            : " << p1 << endl;
        cout << "(p1 += 1) += 2: " << ((p1 += 1) += 2) << endl;
        cout << "p1            : " << p1 << endl;
        break;
    case 3:
        cout << "p1  : " << p1   << endl;
        cout << "p1(): " << p1() << endl;
        break;
    case 4:
        cout << "p1      : " << p1 << endl;
        cout << "p2 = p1 : " << (p2 = p1) << endl;
        cout << "p2      : " << p2 << endl;
        break;
    case 5:
        cout << "p1          : " << p1 << endl;
        cout << "p1 + 3 + 4  : " << p1 + 3 + 4 << endl;
        cout << "p1          : " << p1 << endl;
        break;
    case 6:
        cout << "p1          : " << p1 << endl;
        cout << "5 + (2 + p1): " << 5 + (2 + p1) << endl;
        cout << "p1          : " << p1 << endl;
        break;
    case 7:
        cout << boolalpha;
        cout << "p1      : " << p1 << endl;
        cout << "p2      : " << p2 << endl;
        cout << "p1 == p2: " << (p1 == p2) << endl;
        cout << "(p2 = p1) == p1: " << ((p2=p1) == p1) << endl;
        cout << "p2      : " << p2 << endl;
        break;
    case 8:
        cout << "p1  : " << p1   << endl;
        cout << "++p1: " << ++p1 << endl;
        cout << "p1  : " << p1   << endl;
        break;
    // [추가] case 9
    case 9:
        cout << "p1  : " << p1   << endl;
        cout << "p1++: " << p1++ << endl;
        cout << "p1  : " << p1   << endl;
        break;
    // [추가] case 10
    case 10:
        cout << "p1      : " << p1 << endl;
        cout << "p1 << 10: " << (p1 << 10) << endl;
        cout << "p1      : " << p1 << endl;
        break;
    }
    cout << endl;
}

/******************************************************************************
 * main() 함수
 ******************************************************************************/
int main()
{
    while (true) {
        int menu;
        cout << menuStr;
        cin >> menu;
        if (menu == 0) break;
        menu_switch(menu);
    }
    cout << "\nGood bye!!" << endl;
}