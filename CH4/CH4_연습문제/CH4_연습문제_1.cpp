#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class Container {
    string title;  // 컨테이너 타이틀
    int    size;   // 컨테이너에 저장된 정수 배열 arr의 크기
    int    *arr;   // size 개의 원소를 가진 배열 시작 주소
public:
    Container();
    ~Container();
    void setTitle(string title);
    string getTitle();
    void newArray();
    void average();
    void rightRotateTitle();
    void findDeleteTitle();
    void newIntArray();
    void inputIntArray();
};

void Container::average(){
    int sum = 0;
    for(int i=0; i<size; i++){
        sum += arr[i];
    }
    cout << "average: " << sum << endl;
}

void Container::inputIntArray(){
    int i;
    cout << "input " << size << " integers: ";
    for (i = 1; i < size + 1; i++){ cin >> arr[i-1]; }
    cout << "arr[" << size << "]:";
    for (i = 0; i < size; i++){ cout << " " << arr[i]; }
    cout << endl;
}

void Container::newIntArray() {
    cout << "element numbers of int array[]? ";
    cin >> size;               // 사용자로부터 크기 입력
    arr = new int[size];       // int 배열 동적 할당
}


Container::Container(){
    arr = nullptr;
    size = 0;
    cout << "Container(): arr = nullptr; size = 0;" << endl;
}

Container::~Container() {
    if (arr != nullptr) {
        delete[] arr;
        cout << "~Container(): arr[" << size << "] deleted;" << endl;
    } else {
        cout << "~Container(): " << title << endl;
    }
}

void Container::setTitle(string title) {
    /* 매개변수 title 값을 멤버 변수 title에 저장한다. */
    this -> title = title;
}

string Container::getTitle() {
    return title;  /* 멤버변수 title을 반환하라. */
}

/******************************************************************************
 * Global functions
 ******************************************************************************/

void constructor() {
    Container c;
    c.setTitle("constructor-title");
    cout << "c.getTitle(): " << c.getTitle() << endl;
}

void intArray() {
    Container c;
    c.newIntArray();
    c.inputIntArray();
    c.average();
}

Container *newObjectArray(int size) {
    Container *pArr = nullptr; // Container 객체 배열 시작 주소
    /* 여기에 코드를 구현하라. */
    return pArr;
}

void printTitles(Container *pArr, int size) {
}

void objectArray() {
    Container *pArr; // Container 객체 배열 시작 주소
    int size;        // Container 객체 배열 원소 개수
    cout << "element numbers of Container array[]? ";
    cin >> size;
    pArr = newObjectArray(size);
    printTitles(pArr, size);
    /* 여기서 pArr이 포인터 하는 메모리를 반납하시오. */
}

void inputTitle(Container* cp) {
    string s;
    getline(cin, s); // 앞서 입력된 메뉴항목 번호 뒤의 [엔터]를 제거함
    /* 여기에 코드를 구현하라. */
}

void rotateTitle() {
}

void findDelete() {
}

/******************************************************************************
 * main()
 ******************************************************************************/

string menuStr =
"******************************** Main Menu *********************************\n"
"* 0.Exit 1.constructor 2.intArray 3.objectArray 4.rotateTitle 5.findDelete *\n"
"****************************************************************************\n";

int main() {
    while (true) {
        int menuItem;
        cout << endl << menuStr << "menu? ";
        cin >> menuItem;
        if (menuItem == 0)
            break;
        switch(menuItem) {
        case 1: constructor(); break;
        case 2: intArray();    break;
        case 3: objectArray(); break;
        case 4: rotateTitle(); break;
        case 5: findDelete(); break;
        }
    }
    cout << "Good bye!!" << endl;
}