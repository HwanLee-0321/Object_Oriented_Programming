#include <iostream>
#include <string>
using namespace std;

/******************************************************************************
 * Class Person
 ******************************************************************************/
class Person {
    string name;    // 이름
    string address; // 주소
public:
    Person(string name = "", string address = "") { set(name, address); }

    void set(const string& name, const string& address) {
        this->name = name;
        this->address = address;
    }
    void show() const {
        cout << name << ": " << address << endl;
    }
    char operator [] (int idx) { return address[idx]; }
    bool operator ! () const;
    friend Person operator + (char c, const Person& p);
    Person& operator<<(char c);
    Person operator--(int);
};

// 여기에 필요한 연산자를 구현하시오.
bool Person::operator ! () const {
    if (this->name == "" && this->address == "") {
        return true;
    } else {
        return false;
    }
}

Person operator + (char c, const Person& p) {
    // 1. 새로운 name 문자열 생성: c + "+" + p.name
    string newName = c + string("+") + p.name;
    
    // 2. 새로운 address 문자열 생성: c + p.address
    string newAddress = c + p.address;
    
    // 3. 계산된 name과 address로 새 Person 객체를 생성하여 반환
    return Person(newName, newAddress);
}

Person& Person::operator<<(char c) {
    // 1. 이름(name) 변경: (name += "<<") += c
    (this->name += " << ") += c;  
    
    // 2. 주소(address) 변경: address += c
    this->address += c;

    // 3. 자기 자신의 참조를 반환하여 연쇄 호출 가능하게 함
    return *this;
}

Person Person::operator--(int) {
    // 1. 변경 전의 현재 객체 상태를 복사하여 보관 (반환용)
    Person temp = *this;

    // 2. 현재 객체의 name을 변경 (name + "--")
    this->name += "--";

    // 3. 현재 객체의 address가 비어있지 않으면 마지막 문자 제거
    if (!this->address.empty()) {
        this->address.pop_back(); // string의 마지막 문자를 제거하는 멤버 함수
    }

    // 4. 보관해둔 변경 전의 객체를 반환
    return temp;
}

//------------------------------------------------------
// 경고: 아래 함수들은 주석을 제거하는 것 외는 수정하지 마시오.
//      만약 본인의 임의대로 아래 함수를 수정할 경우 0점 처리함.
//------------------------------------------------------

int main()
{
    int menu;
    string name1("p1"), address1("seoul"), name2("p2"), address2("XYZ");

    while (true) {
        cout << "menu item? ";
        cin >> menu;
        if (menu == 0) break;

        Person p1(name1, address1), p2(name2, address2);
        p1.show();
        p2.show();
        cout << "+++++++++" << endl;
        if (menu == 1) {
            if (!p1) p1 = p2;
            p1.show();
            Person p3;
            if (!p3) p1 = p2;
        }
        else if (menu == 2) {
            (p2[0] + p1).show();
            (p2[0] + (p2[1] + p1)).show();
            (p2[0] + (p2[1] + (p2[2] + p1))).show();
        }
        else if (menu == 3) {
            (p1 << p2[0]).show();
            (p1 << p2[1]).show();
            (p1 << p2[2]).show();
        }
        else if (menu == 4) {
            (p1--).show();
            p1.show();
            cout << "***" << endl;
            (p1--).show();
        }
        else if (menu == 5) {
            cin.ignore();
            cout << "name? ";    getline(cin, name1);
            cout << "address? "; getline(cin, address1);
            p1.set(name1, address1);
        }
        p1.show();
        cout << endl;
    }
    cout << "\nGood bye!!" << endl;
}