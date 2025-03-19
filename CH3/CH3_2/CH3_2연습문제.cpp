// 아래에 class alu를 작성해서 
// main 함수에서 +, -, * 계산이 가능하게 하라
// 멤버 변수인 r1, r2는 unsigned int, oper은 char이다
// ------------------------------------------------
#include <iostream>
using namespace std;

class alu {
public:
    unsigned int r1, r2;
    char oper;
    
    alu() : r1(1), oper('*'), r2(3) {}
    
    unsigned int calc() {
        switch (oper) {
            case '+': return r1 + r2;
            case '-': return r1 - r2;
            case '*': return r1 * r2;
            default: return 0; // 잘못된 연산자 처리
        }
    }
};

//아래 main 함수는 수정 불가
int main() {
    alu machine; //생성자 구현하여 아래 출력 결과 1*3처럼 출력되게 각 멤버를 초기화 시킬 것
    cout << machine.r1 << machine.oper << machine.r2 << endl; // 출력 결과:1*3
    cin  >> machine.r1 >> machine.oper >> machine.r2;         // 입력 예시:7 + 7
    cout << machine.calc() << endl;                           // 출력 예시:14
    cin  >> machine.r1 >> machine.oper >> machine.r2;         // 입력 예시:25 - 8
    cout << machine.calc() << endl;                           // 출력 예시:17
    cin  >> machine.r1 >> machine.oper >> machine.r2;         // 입력 예시:9 * 25
    cout << machine.calc() << endl;                           // 출력 예시:225
}