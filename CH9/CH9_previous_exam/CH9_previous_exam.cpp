#include <iostream>
using namespace std;

// 추상 클래스 AbstractItem 정의
class AbstractItem {
public:
    // 추상 메서드로 compareTo 정의
    virtual int compareTo(AbstractItem* other) const = 0;
    // 추상 메서드로 getSize 정의
    virtual int getSize() const = 0;
    // 추상 메서드로 getName 정의
    virtual string getName() const = 0;
    // 가상 소멸자
    virtual ~AbstractItem() {}
};

// ConcretePackage 클래스는 AbstractItem 클래스를 상속
class ConcretePackage : public AbstractItem {
private:
    string name; // 패키지의 이름
    int length, width, height; // 패키지의 길이, 너비, 높이

public:
    // 생성자
    ConcretePackage(string n, int l, int w, int h) : name(n), length(l), width(w), height(h) {}

    // 패키지의 부피를 계산하여 반환하는 메서드
    

    // 패키지의 이름을 반환하는 메서드
    /*                       */

    // 다른 패키지와의 크기를 비교하는 메서드
     /*                         */

int main() {
    // 패키지 포인터 배열 선언
    AbstractItem* packages[3];

    cout << "패키지 3개 생성(이름 길이 너비 높이 입력) =>" << endl;
    for (int i = 0; i < 3; ++i) {
        string n;
        int l, w, h;
        cin >> n >> l >> w >> h; // 사용자로부터 입력 받음
        packages[i] = new ConcretePackage(n, l, w, h); // 패키지 객체 생성 및 배열에 추가
    }

    cout << "패키지 크기 비교 =>" << endl;

     string firstName = packages[0]->getName(); // 첫 번째 패키지의 이름
    for (int i = 1; i < 3; ++i) {
        /*                            */                      // 현재 패키지의 이름
        /*                             */                       // 첫 번째 패키지와 비교
        // 비교 결과에 따라 출력
       /*

        */
    }

    // 메모리 해제(동적으로 할당된 패키지 객체 삭제)
    /*

    */

    return 0;
}