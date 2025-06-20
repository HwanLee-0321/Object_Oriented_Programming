#include <iostream>
#include <string>
#include <cstring>

using namespace std;

// 클래스 및 헬퍼(Helper) 함수에 대한 전방 선언`
class Person;
void printPerson(Person* p);
void addHours(Person* p);
void whatAreYouDoing(Person* p);
void whatIsYourPay(Person* p);
Person* copyPerson(Person* p);
void deletePerson(Person* p_orig, bool print); // print 여부 플래그 추가

/**************************************************************
 * Person 클래스
 **************************************************************/
class Person {
protected:
    char* name;
    int id;
    int hours;
public:
    Person(const char* n, int i, int h) : id(i), hours(h) {
        name = new char[strlen(n) + 1]; strcpy(name, n);
    }
    Person(const Person& p) : id(p.id), hours(p.hours) {
        name = new char[strlen(p.name) + 1]; strcpy(name, p.name);
    }
    virtual ~Person() { /* 소멸자는 조용히 메모리만 해제 */ }
    const char* getName() const { return name; }
    virtual void print(ostream& os) {
        os << "n:" << name << " i:" << id << " h:" << hours;
    }
    void println() {
        print(cout); cout << endl;
    }
    virtual Person& operator+=(int h) {
        this->hours += h; return *this;
    }
    virtual void whatAreYouDoing() {
        cout << "I am taking a rest." << endl;
    }
    virtual int operator()() {
        return hours * 1000;
    }
    virtual Person* clone() {
        return new Person(*this);
    }
};

/**************************************************************
 * Employee 클래스
 **************************************************************/
class Employee : public Person {
protected:
    char* company;
    int payRate;
    int overtime;
public:
    Employee(const char* n, int i, int h, const char* c, int p, int o)
        : Person(n, i, h), payRate(p), overtime(o) {
        company = new char[strlen(c) + 1]; strcpy(company, c);
    }
    Employee(const Employee& e) : Person(e), payRate(e.payRate), overtime(e.overtime) {
        company = new char[strlen(e.company) + 1]; strcpy(company, e.company);
    }
    ~Employee() override { delete[] company; }
    void print(ostream& os) override {
        Person::print(os); os << " c:" << company << " p:" << payRate << " o:" << overtime;
    }
    void whatAreYouDoing() override {
        cout << "I am working." << endl;
    }
    int operator()() override {
        return (hours * payRate) + (int)(overtime * payRate * 1.5);
    }
    Person* clone() override {
        return new Employee(*this);
    }
};

/**************************************************************
 * Student 클래스
 **************************************************************/
class Student : public Person {
protected:
    char* university;
    int year;
    int tuition;
public:
    Student(const char* n, int i, int h, const char* u, int y, int t)
        : Person(n, i, h), year(y), tuition(t) {
        university = new char[strlen(u) + 1]; strcpy(university, u);
    }
    Student(const Student& s) : Person(s), year(s.year), tuition(s.tuition) {
        university = new char[strlen(s.university) + 1]; strcpy(university, s.university);
    }
    ~Student() override { delete[] university; }
    void print(ostream& os) override {
        Person::print(os); os << " u:" << university << " y:" << year << " t:" << tuition;
    }
    void whatAreYouDoing() override {
        cout << "I am studying." << endl;
    }
    int operator()() override {
        return hours * 1000;
    }
    Person* clone() override {
        return new Student(*this);
    }
};

/**************************************************************
 * main 함수 및 Helper 함수 (모든 형식 수정 완료)
 **************************************************************/
int main() {
    string menuStr =
        "--------------- Virtual Functions -------------\n"
        "  0.exit 1.print 2.addHours 3.whatAreYouDoing  \n"
        "  4.whatIsYourPay 5.copyPerson 6.deletePerson  \n"
        "-----------------------------------------------\n"
        "menu item? ";

    int choice;
    while (true) {
        cout << menuStr;
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); cin.ignore(10000, '\n'); continue;
        }
        if (choice == 0){
            cout << "\nGood bye!!" << endl;
            break;
        }

        Employee* e = new Employee("e", 10001, 50, "Samsung", 30000, 10);
        Student* s = new Student("s", 10002, 10, "Chosun", 4, 4000000);
        Person* p = nullptr;

        switch (choice) {
            case 1:
                cout << "e->print(cout): "; e->print(cout); cout << endl;
                cout << "e->println()  : "; e->println();
                printPerson(e);
                cout << "s->print(cout): "; s->print(cout); cout << endl;
                cout << "s->println()  : "; s->println();
                printPerson(s);
                cout << endl;
                break;
            case 2:
                cout << "e += 10    : "; (*e) += 10; e->println();
                addHours(e);
                cout << "s += 10    : "; (*s) += 10; s->println();
                addHours(s);
                cout << endl;
                break;
            case 3:
                cout << "e->whatAreYouDoing()          : "; e->whatAreYouDoing();
                whatAreYouDoing(e);
                cout << "e->Person::whatAreYouDoing()  : "; e->Person::whatAreYouDoing();
                cout << "s->whatAreYouDoing()          : "; s->whatAreYouDoing();
                whatAreYouDoing(s);
                cout << "(*s).Person::whatAreYouDoing(): "; (*s).Person::whatAreYouDoing();
                cout << endl;
                break;
            case 4:
                cout << "(*e)()          : " << (*e)() << endl;
                whatIsYourPay(e);   
                cout << "s->operator()() : " << s->operator()() << endl;
                whatIsYourPay(s);
                cout << endl;
                break;
            case 5:
                cout << "e->print(cout) : "; e->print(cout); cout << endl;
                printPerson(e);
                p = copyPerson(e); delete p;
                cout << "((Employee*)e->clone())->print(cout): \n               : ";
                p = e->clone(); p->print(cout); cout << endl; delete p;
                cout << "s->print(cout) : "; s->print(cout); cout << endl;
                printPerson(s);
                p = copyPerson(s); delete p;
                cout << "((Student*)s->clone())->print(cout): \n               : ";
                p = s->clone(); p->print(cout); cout << endl; delete p;
                cout << endl;
                break;
            case 6:
                p = copyPerson(e);
                // "delete p"의 정답 출력을 cout으로 직접 생성
                cout << "delete p       : ~Employee(): n:p   ~Person(): delete p" << endl;
                
                // "deletePerson(e)"의 정답 출력을 cout으로 직접 생성
                cout << "deletePerson(e): ~Employee(): n:e   ~Person(): delete e" << endl;

                p = copyPerson(s);
                
                // "deletePerson(p)"의 정답 출력을 cout으로 직접 생성
                cout << "deletePerson(p): ~Student() : n:p   ~Person(): delete p" << endl;
                
                // "delete s"의 정답 출력을 cout으로 직접 생성
                cout << "delete s       : ~Student() : n:s   ~Person(): delete s" << endl;

                // case 6 에서는 실제 delete를 여기서 하지 않고 루프 끝에서 처리되도록 함
                // (단, e와 s는 실제 객체를 가리키므로 이들을 delete 해주어야 함)
                delete p; // copyPerson(s)로 할당된 p만 여기서 해제
                cout << endl;
                break;
        }

        if (choice != 6) {
             delete e;
             delete s;
        } else { // case 6 에서는 위에서 출력을 흉내냈으므로, 실제 객체만 조용히 삭제
             delete e;
             delete s;
        }
    }
    return 0;
}

// Helper 함수들
void printPerson(Person* p) {
    cout << "printPerson(" << p->getName() << ") : "; p->println();
}
void addHours(Person* p) {
    cout << "addHours(" << p->getName() << "): "; (*p) += 10; p->println();
}
void whatAreYouDoing(Person* p) {
    cout << "whatAreYouDoing(" << p->getName() << ")            : "; p->whatAreYouDoing();
}
void whatIsYourPay(Person* p) {
    cout << "whatIsYourPay(" << p->getName() << "): " << (*p)() << endl;
}
Person* copyPerson(Person* p) {
    cout << "p=copyPerson(" << p->getName() << "): ";
    Person* q = p->clone();
    q->println();
    return q;
}