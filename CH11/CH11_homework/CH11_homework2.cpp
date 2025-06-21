#include <iostream>
#include <string>
#include <ostream> // ostream 조작자(manipulator) 정의를 위해 필요

using namespace std;

// 사용자 정의 조작자 'boxSign'의 전방 선언
ostream& boxSign(ostream& os);

/*********************************************************************
 * Class Box
 *********************************************************************/
class Box {
private:
    string label;                     // 박스 라벨
    int permitWeight, itemWeight;     // 박스 허용용량, 박스에 담은 물품의 총 용량
public:
    // 기본 생성자
    Box() {
        itemWeight = 0;
        permitWeight = 0; // 안전한 값으로 초기화
    }

    // 매개변수화된 생성자
    Box(string label, int weight) {
        this->label = label;
        permitWeight = weight;
        itemWeight = 0;
    }

    // 박스에 물품을 넣는 멤버 함수
    void putItem(int weight) {
        // 남은 허용 용량이 넣을 물품의 용량보다 크거나 같은지 확인
        if ((permitWeight - itemWeight) >= weight) {
            itemWeight += weight;
        } else {
            cout << "This box doesn't have available space." << endl;
        }
    }

    // 연산자 오버로딩 함수들을 friend로 선언하여 private 멤버에 접근 허용
    friend ostream& operator<<(ostream& os, const Box& b);
    friend istream& operator>>(istream& is, Box& b);
};


/*********************************************************************
 * 사용자 정의 조작자 및 연산자 오버로딩 구현
 *********************************************************************/

// 사용자 정의 조작자 'boxSign' 구현
ostream& boxSign(ostream& os) {
    os << "[[[[[ BOX ]]]]]" << endl;
    return os;
}

// 출력 연산자 '<<' 오버로딩 구현
ostream& operator<<(ostream& os, const Box& b) {
    os << boxSign; // boxSign 조작자 호출
    os << "Box label : " << b.label << endl;
    os << "Box available weight : " << (b.permitWeight - b.itemWeight) << endl;
    return os;
}

// 입력 연산자 '>>' 오버로딩 구현
istream& operator>>(istream& is, Box& b) {
    // 박스에 이미 물건이 담겨 있는지 (itemWeight > 0) 확인
    if (b.itemWeight > 0) {
        // 물건이 있는 경우: 라벨만 변경
        cout << "This box is not empty. You can change only label of this box" << endl;
        cout << "Box label : ";
        is >> b.label;
    } else {
        // 박스가 비어 있는 경우: 라벨과 허용용량 입력
        cout << "Box label and weight : ";
        is >> b.label >> b.permitWeight;
    }
    return is;
}

/*********************************************************************
 * Main 함수
 *********************************************************************/
int main() {
    Box box, box2("Book", 30);   //  두 개의 박스 객체 생성

    cin >> box;                  // box 객체의 label, permotWeight 입력
    cout << box;                 // box 객체의 라벨과 남은 용량 출력
    box.putItem(5);              // box 객체에 물품 용량을 추가
    cout << box;
    box.putItem(20);        // box 객체에 물품 중량 추가. 이때 남은 허용용량을 체크하고 부족하면 오류메세지 출력
    
    cout << box2;
    box2.putItem(15);
    cin >> box2;              // // 박스가 라벨과 중량을 가지고 있는 경우 This box is not empty. You .. 출력
    cout << box2;

    return 0;
}