
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
    ~Container();

    void setTitle(string title);
    string getTitle();
    void printIntArray();
    void newIntArray();
    void inputIntArray();
};

Container::Container() { }

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

void Container::newIntArray() {
    if (arr != nullptr)
        delete [] arr;
    cout << "element numbers of int array[]? ";
    cin >> size;
    arr = new int[size];
}

void Container::inputIntArray() {
    cout << "input " << size << " integers: ";
    for (int i = 0; i < size; ++i)
        cin >> arr[i];
}

/******************************************************************************
 * Global functions
 ******************************************************************************/

void refParam() {
    Container c("C", 3);
    Container b("B");
}

void refRet1() {
}

void refRet2() {
}

void explicitCopy() {
}

void implicitCopy() {
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