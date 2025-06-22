#include <iostream>
#include <string>
using namespace std;

// 기본 커피 머신 클래스
class BaseCoffeeMachine {
    string model; // 커피 머신 모델명
    string manufacturer; // 제조사
    int brewedCount; // 만들어진 커피의 수
    int availableWater; // 사용 가능한 물의 양

public:
    // 생성자(모델명, 제조사, 초기 물의 양을 설정)
    BaseCoffeeMachine(string model, string manufacturer, int totalWater);
protected:
    // 커피를 만드는 메서드
    bool brew(int cups = 1);
    // 각종 getter 메서드들
    string getModel() { return model; }
    string getManufacturer() { return manufacturer; }
    int getBrewedCount() { return brewedCount; }
    int getAvailableWater() { return availableWater; }
   
    void show(); // 커피 머신 상태를 출력하는 메서드
};

// 에스프레소 머신 클래스
class EspressoMachine : public BaseCoffeeMachine {
    int availableBeans; // 사용 가능한 커피 콩의 양

public:
    // 생성자
    EspressoMachine(string model, string manufacturer, int totalWater, int totalBeans);
    bool brewEspresso(int cups = 1);// 에스프레소를 만드는 메서드
    void showState();   // 에스프레소머신 상태를 출력하는 메서드
};

// 아메리카노 머신 클래스
class AmericanoMachine : public BaseCoffeeMachine {
    int availableCapsules; // 사용 가능한 캡슐의 양

public:
    // 생성자
    AmericanoMachine(string model, string manufacturer, int totalWater, int totalCapsules);
     bool brewAmericano(int cups = 1); // 아메리카노를 만드는 메서드
     void showState(); // 아메리카노 머신 상태를 출력하는 메서드
};

// 커피 머신 관리자 클래스
class CoffeeMachineManager {
    EspressoMachine* em; 
    AmericanoMachine* am; 

public:
     CoffeeMachineManager();
     ~CoffeeMachineManager();
     void operate(); // 커피 머신을 작동시키는 메서드
};

// BaseCoffeeMachine 클래스의 생성자 구현
 /*         */

// 커피를 만드는 메서드 구현
bool BaseCoffeeMachine::brew(int cups) {
 /*                  */
}

// 커피 머신 상태를 출력하는 메서드 구현
void BaseCoffeeMachine::show() {
 /*                    */
}

// EspressoMachine 클래스의 생성자 구현
EspressoMachine::EspressoMachine(string model, string manufacturer, int totalWater, int totalBeans)
 /*                    */
}

// 에스프레소를 만드는 메서드 구현
bool EspressoMachine::brewEspresso(int cups) {
 /*                       */
}

// 에스프레소 머신 상태를 출력하는 메서드 구현
void EspressoMachine::showState() {
  /*                               */
}

// AmericanoMachine 클래스의 생성자 구현
AmericanoMachine::AmericanoMachine(string model, string manufacturer, int totalWater, int totalCapsules)
  /*                           */

}

// 아메리카노를 만드는 메서드 구현
bool AmericanoMachine::brewAmericano(int cups) {
  /*                               */
}

// 아메리카노 머신 상태를 출력하는 메서드 구현
void AmericanoMachine::showState() {
   /*                   */
}

// CoffeeMachineManager 클래스의 생성자 구현
CoffeeMachineManager::CoffeeMachineManager() {
  /*                        */
}

// CoffeeMachineManager 클래스의 소멸자 구현
CoffeeMachineManager::~CoffeeMachineManager() {
 /*                              */
}

// 커피 머신을 작동시키는 메서드 구현
void CoffeeMachineManager::operate() {
 /*                            */
int main() {
    CoffeeMachineManager manager; // 커피 머신 관리자 인스턴스 생성
    manager.operate(); // 커피 머신 작동
    return 0;
}