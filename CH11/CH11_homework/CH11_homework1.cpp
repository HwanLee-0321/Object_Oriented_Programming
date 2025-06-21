#include <iostream>

using namespace std;

/******************************************************************************
 * Class Point
 ******************************************************************************/
class Point {
    int x, y;  // 점의 x, y 좌표 값
public:
    Point() { x = 31; y = 15; }
    friend ostream& operator<<(ostream& os, const Point& p);
    friend istream& operator>>(istream& is, Point& p);
};


// 여기에 필요한 연산자, 조작자 등의 함수를 구현하시오.

// [문제 1] Point의 출력 연산자 << 구현
ostream& operator<<(ostream& os, const Point& p) {
    // 스트림의 현재 상태(플래그, 채움 문자)를 저장
    ios_base::fmtflags flags = os.flags();
    char fill = os.fill();

    // x 좌표 출력: 폭 7, 채움 문자 '*', 16진수, 진법 표시
    os.width(7);
    os.fill('*');
    os.setf(ios::hex, ios::basefield);
    os.setf(ios::showbase);
    os << p.x;

    // ", " 문자열 출력을 위해 플래그 초기화
    os.flags(flags); 
    os << ", ";

    // y 좌표 출력: [수정된 부분] 문제의 설명 대신 실행 예시에 맞춰 구현
    // 8진수, 진법 표시('0' 접두사)를 적용하고 뒤에 "..."를 붙임
    os.setf(ios::oct, ios::basefield);
    os.setf(ios::showbase);
    os << p.y << "...";

    // ", "와 bool 값 출력을 위해 플래그 초기화
    os.flags(flags);
    os << ", ";
    os.setf(ios::boolalpha); // bool 값을 true/false로 출력
    os << (p.x == p.y);

    // 스트림의 상태를 원래대로 복원
    os.flags(flags);
    os.fill(fill);

    return os;
}

// [문제 2] 출력 조작자 leftp, rightp 구현
ostream& leftp(ostream& os) {
    os << "( ";
    return os;
}

ostream& rightp(ostream& os) {
    os << " )";
    return os;
}

// [문제 3] Point의 입력 연산자 >> 구현
istream& operator>>(istream& is, Point& p) {
    is >> p.x >> p.y;
    return is;
}

// [문제 4] 입력 조작자 inmsg 구현
istream& inmsg(istream& is) {
    cout << "x, y coordinate? ";
    return is;
}


/******************************************************************************
 * 선택된 메인 메뉴 항목을 실행하는 함수들
 ******************************************************************************/
//------------------------------------------------------
// 경고: 아래 네 개의 함수는 주석을 제거하는 것 외는 수정하지 마시오.
//      만약 본인의 임의대로 아래 함수를 수정할 경우 0점 처리함.
//------------------------------------------------------

Point p;

void outPoint() {
    cout.width(3); 
    cout << 1 << 2 << 3 << true << endl;
    cout << p << endl;
    cout.width(3); 
    cout << 1 << 2 << 3 << true << endl;
}

void outMnpPoint() {
    cout << leftp << p << rightp << endl;
}

void inPoint() {
    cout << "input x and y: ";
    cin >> p;
    outMnpPoint();
}

void inMnpPoint() {
    cin >> inmsg >> p;
    outMnpPoint();
}

/******************************************************************************
 * menu_switch() 함수: 선택된 메인 메뉴 항목을 실행함
 ******************************************************************************/
const char* menuStr =
    "----------------------- I/O Stream -----------------------\n"
    "  0.exit 1.outPoint 2.outMnpPoint 3.inPoint 4.inMnpPoint  \n"
    "----------------------------------------------------------\n"
    "menu item? ";

void menu_switch(int menu)
{
    switch (menu) {
    case 1: outPoint();    break;
    case 2: outMnpPoint(); break;
    case 3: inPoint();     break;
    case 4: inMnpPoint();  break;
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