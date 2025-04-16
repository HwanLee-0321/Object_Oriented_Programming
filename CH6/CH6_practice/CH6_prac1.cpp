#include <iostream>
using namespace std;

/******************************************************************************
 * class Cal
 ******************************************************************************/

class Cal {
    int x;
    int y;
    static int count;
public:
    Cal(const int &x = 100, const int &y = 200){
    	this->x = x;
    	this->y = y;
    	count++;
    	cout << "Cal::Cal(" << x << ", " << y << ")" << endl;
    }
    ~Cal(){
    	cout << "Cal::~Cal(): x=" << x << ", " << "y=" << y << endl;
    	count--;
    }
    int add(){
    	return x+y;
    }
    int add(int x){
    	return x + y;
    }
    int add(int x, int y){
    	return x+y;
    }
    static void print_count() {
        cout << "total count: " << count << endl;
    }
};


int Cal::count = 0;
/******************************************************************************
 * Global functions
 ******************************************************************************/

void function_overload(int x, int y)
{
    Cal c1(100, 200);
    cout << "c1.add(): " << c1.add() << endl;
	cout << "c1.add(" << x << "): " << c1.add(x) << endl;
	cout << "c1.add(" << x << ", " << y << "): " << c1.add(x, y) << endl;
}

void default_parameter(int x, int y)
{
    Cal *c1 = new Cal();
    cout << "c1->add(): " << c1->add() << endl << endl;

    Cal *c2 = new Cal(x);
    cout << "c2->add(): " << c2->add() << endl << endl;

    Cal *c3 = new Cal(x, y);
    cout << "c3->add(): " << c3->add() << endl << endl;

    // Cal 객체 수 출력
    Cal::print_count(); cout << endl;

    // Cal 객체 배열 동적 생성
    Cal *cal = new Cal[5]; cout << endl;

    // 객체 수 출력
    Cal::print_count(); cout << endl;

    // 먼저 생성된 세 객체 소멸
    delete c2; 
    delete c3; 
    delete c1; cout << endl;

    // 다시 객체 수 출력
    Cal::print_count(); cout << endl;

    // Cal 배열 소멸
    delete[] cal; cout << endl;

    // 최종 객체 수 출력
    Cal::print_count();
}

void printXY(int x=0, int y=0)
{
    cout << "x, y: " << x << ", " << y << endl;
}

/* 함수호출시 넘겨 준 main()의 원본 인자 값이 수정되도록 매개변수 선언을 적절히 수정하라.*/
void inputXY(int &x, int &y)
{
    /* 여기서 "x and y? "를 출력하고
       x, y 값을 입력 받는 코드를 삽입하라. */

    cout << "x and y? "; cin >> x >> y;
    
    printXY(x, y);
}

string menuStr =
"************************* Main Menu ************************\n"
"* 0.Exit 1.function_overload 2.default_parameter 3.inputXY *\n"
"************************************************************\n";

int main() {
    int x = 10, y = 20;

    while (true) {
        int menuItem;
        cout << endl << menuStr << "menu? ";
        cin >> menuItem;
        if (menuItem == 0)
            break;
        switch(menuItem) {
        case 1: function_overload(x, y); break;
        case 2: default_parameter(x, y); break;
        case 3: inputXY(x, y);
                cout << "X, Y: " << x << ", " << y  << endl;
                printXY(x);
                printXY();
                break;
        }
    }
    cout << "Good bye!!" << endl;
}
