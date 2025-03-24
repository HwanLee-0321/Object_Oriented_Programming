#include <iostream>
#include <string>
using namespace std;

class Name{
    string first, last;
public:
    string get_first() { return first; }
    string get_last()  { return last; }
    void set_name(string f, string l);  // 멤버 first와 last에 각각 f와 l을 저장
};

class PersonManager{
    Name *p;
    int nofp; //Name의 수, p의 크기
public:
    PersonManager(int n);    // 생성자에서 n개의 원소를 가지는 Name 배열을 동적 메모리 할당 받은 후 p에 저장 후
                             // n개의 Name(first last)을 입력 받아 p 배열의 각 원소에 저장
    void show();             // 모든 n개의 이름의 first name과 last name을 출력 
    int serarch(string str); // str과 같은 first 또는 last 이름의 수를 반환
    ~PersonManager();        // 메모리 반환 및 "delete [] p;" 출력
};
// 위에 코드는 수정 불가

// set_name 함수 구현
void Name::set_name(string f, string l) {
    first = f;
    last = l;
}

// PersonManager 생성자 구현
PersonManager::PersonManager(int n) {
    nofp = n;
    p = new Name[n]; // n개의 Name 배열을 동적 메모리 할당

    cout << "Enter " << nofp << " first and last names." << endl;
    for (int i = 0; i < nofp; i++) {
        string f, l;
        cin >> f >> l;
        p[i].set_name(f, l); // 입력받은 이름을 각 객체에 저장
    }
}

// show 함수 구현
void PersonManager::show() {
    for (int i = 0; i < nofp; i++) {
        cout << p[i].get_first() << " " << p[i].get_last() << endl;
    }
}

// serarch 함수 구현
int PersonManager::serarch(string str) {
    int count = 0;
    for (int i = 0; i < nofp; i++) {
        if (p[i].get_first() == str || p[i].get_last() == str)
            count++;
    }
    return count;
}

// 소멸자 구현
PersonManager::~PersonManager() {
    delete[] p;
    cout << "delete [] p;" << endl;
}

// 아래 main 함수는 수정 불가
int main() {
    int n;
    cout << "Enter number of people." << endl;
    cin >> n;

    PersonManager people(n);

    people.show();

    cout << "Enter search name." << endl;
    string str;
    cin >> str;
    cout << people.serarch(str) << endl;

    return 0;
}