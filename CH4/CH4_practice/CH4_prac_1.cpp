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

// Container 클래스의 멤버 함수: findDeleteTitle()
// 설명: title에서 사용자가 입력한 특정 단어를 찾아서 모두 삭제한다.
void Container::findDeleteTitle() {
    string word;  // 삭제할 단어를 저장할 변수

    cout << "word to delete? ";
    cin >> word;  // 삭제할 단어 입력받기

    size_t pos;  // 단어가 발견된 위치를 저장하는 변수

    // 단어가 발견되지 않을 때까지 반복하여 삭제
    while ((pos = title.find(word)) != string::npos) {
        title.erase(pos, word.length()); // 찾은 위치(pos)부터 단어 길이만큼 삭제
    }

    // 삭제 후 결과(title) 출력
    cout << title << endl;
}

void Container::rightRotateTitle() {
    int len = title.length();

    for (int i = 1; i <= len; i++) {
        // 맨 뒤의 한 글자를 앞으로 옮기는 작업
        title = title[len - 1] + title.substr(0, len - 1);
        cout << title << endl;
    }
}

void Container::average(){
    double sum = 0;
    for(int i=0; i<size; i++){
        sum += arr[i];
    }
    cout << "average: " << sum/size << endl;
}

void Container::inputIntArray(){
    int i;
    cout << "input " << size << " integers: ";
    for (i = 0; i < size; i++) {
        cin >> arr[i];
    }
    cout << "arr[" << size << "]:";
    for (i = 0; i < size; i++){
        cout << " " << arr[i];
    }
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
    Container *pArr = new Container[size]; // 1) size개의 Container 객체 배열 동적 할당
    cout << "input " << size << " words: ";
    cin.ignore(); // 이전 입력에서 남은 '\n' 제거

    for(int i = 0; i < size; i++) {
        string word;
        cin >> word;                 // 2) 단어 입력
        pArr[i].setTitle(word);     // title에 저장
    }

    return pArr;
}

void printTitles(Container *pArr, int size) {
    cout << "words: ";
    for (int i = 0; i < size; i++) {
        cout << pArr[i].getTitle() << " ";
    }
    cout << endl;
}

void objectArray() {
    Container *pArr; // Container 객체 배열 시작 주소
    int size;        // Container 객체 배열 원소 개수
    cout << "element numbers of Container array[]? ";
    cin >> size;
    pArr = newObjectArray(size);
    printTitles(pArr, size);
    /* 여기서 pArr이 포인터 하는 메모리를 반납하시오. */
    delete[] pArr;
}

void inputTitle(Container* cp) {
    string s;
    cout << "input title: ";
    cin.ignore();
    getline(cin,s);
    cp -> setTitle(s);
}

void rotateTitle() {
    Container c;
    inputTitle(&c);
    cout << "c.getTitle(): " << c.getTitle() << endl;
    c.rightRotateTitle();
}

void findDelete() {
    Container c;
    inputTitle(&c);      // This AAis aAA AAtest AAtitle.
    c.findDeleteTitle();
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