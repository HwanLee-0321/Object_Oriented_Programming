
#include <iostream>
#include <string>

using namespace std;

/******************************************************************************
 * Person Container
 ******************************************************************************/

class Container {
    string title;  // 컨테이너 타이틀
    int    size;   // 컨테이너에 저장된 정수 배열 arr의 크기
    int    *arr;   // size 개의 원소를 가진 배열 시작 주소
public:
    Container();
    Container(string title);
    Container(string title, int size);
    Container(const Container& c);  // 복사 생성자 선언
    ~Container();

    void setTitle(string title);
    string getTitle();
    void printIntArray();
    Container& newIntArray();
    Container& inputIntArray();
};

Container::Container() : Container("no-title") { }

Container::Container(string title) : Container(title, 0) {}

Container::Container(string title, int size) {
    this->title = title;
    this->size = size;

    if (size > 0){
        arr = new int[size];
        for (int i =0; i < size; i++){
            arr[i] = 0;
        }
    } else {
        arr = nullptr;
    }
    cout << "Container(): "; printIntArray();
}

Container::Container(const Container& c) {
    title = c.title;
    size = c.size;

    if (size > 0) {
        arr = new int[size];
        for (int i = 0; i < size; ++i) {
            arr[i] = c.arr[i];  // 원소 하나하나 복사
        }
    } else {
        arr = nullptr;
    }

    cout << "Container(Container& c): ";
    printIntArray();
}

Container::~Container() {
    cout << "~Container(): "; printIntArray();
    if (arr != nullptr)
        delete [] arr;
}

void Container::setTitle(string title) {
    this->title = title;
}

string Container::getTitle() {
    return title;
}

void Container::printIntArray() {
    cout << title << ": arr[" << size << "]: ";
    for (int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

Container& Container::newIntArray() {
    if (arr != nullptr)
        delete [] arr;
    cout << "element numbers of int array[]? ";
    cin >> size;
    arr = new int[size];
    return *this;
}

Container& Container::inputIntArray() {
    cout << "input " << size << " integers: ";
    for (int i = 0; i < size; ++i)
        cin >> arr[i];
    return *this;
}

/******************************************************************************
 * Global functions
 ******************************************************************************/
void skipEnter() {
    string s;
    getline(cin, s); // 메뉴항목 번호 뒤의 [엔터]를 제거함
}

void inputTitle(Container& c) {
    string s;
    cout << "input title: ";
    getline(cin, s);      // 사용자로부터 제목 한 줄 입력 받음
    c.setTitle(s);        // 제목 변경x
}

void refParam() {
    Container c("C", 3);
    Container b("B");
    Container a;
    Container d;
    skipEnter();
    inputTitle(d);
}


Container& changeTitle(Container& rc) {
    string s;
    cout << "title to change: ";
    getline(cin, s);
    rc.setTitle(s);
    return rc;
}

void refRet1() {
    skipEnter();
    Container c("C");
    Container& rc = changeTitle(c);
    cout << " c.getTitle(): " << c.getTitle() << endl;
    cout << "rc.getTitle(): " << rc.getTitle() << endl;

    cout << "---" << endl;

    cout << "appendTitle(c).getTitle(): " << changeTitle(c).getTitle() << endl;
    cout << "             c.getTitle(): " << c.getTitle() << endl;
    cout << "            rc.getTitle(): " << rc.getTitle() << endl;
}

void refRet2() {
    Container c("C");
    c.newIntArray().inputIntArray().printIntArray();
}

void explicitCopy() {
    Container c1("c1", 4);
    c1.inputIntArray().printIntArray();
    cout << "---" << endl;
    Container c2(c1);
    c2.setTitle("c2");
    c2.printIntArray();
    cout << "---" << endl;
    c2.inputIntArray().printIntArray();
    c1.printIntArray();
}

void callByValue(Container v) {
    cout << "callByValue" << endl;
    v.setTitle("V");
    v.inputIntArray().printIntArray();
}

Container returnValue(Container& r) {
    cout << "returnValue" << endl;
    return r;  // 자동으로 복사생성자 호출
}

void implicitCopy() {
    Container a("A", 2);
    a.inputIntArray().printIntArray();
    cout << "---" << endl;
    Container b = a; // 자동으로 복사생성자 호출
    b.setTitle("B");
    b.inputIntArray().printIntArray();
    cout << "---" << endl;
    callByValue(a); // 자동으로 복사생성자 호출
    cout << "---" << endl;
    Container c = returnValue(a);
    c.setTitle("C");
    c.inputIntArray().printIntArray();
    cout << "---" << endl;
}

string menuStr =
"****************************** Main Menu ******************************\n"
"* 0.Exit 1.refParam 2.refRet1 3.refRet2 4.explicitCopy 5.implicitCopy *\n"
"***********************************************************************\n";

int main() {
    while (true) {
        int menuItem;
        cout << endl << menuStr << "menu? ";
        cin >> menuItem;
        if (menuItem == 0)
            break;
        switch(menuItem) {
        case 1: refParam();     break;
        case 2: refRet1();      break;
        case 3: refRet2();      break;
        case 4: explicitCopy(); break;
        case 5: implicitCopy(); break;
        }
    }
    cout << "Good bye!!" << endl;
}