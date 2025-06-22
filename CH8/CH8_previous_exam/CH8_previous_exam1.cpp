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
BaseCoffeeMachine::BaseCoffeeMachine(string model, string manufacturer, int totalWater)
    : model(model), manufacturer(manufacturer), availableWater(totalWater), brewedCount(0) {
    // Initializer list를 사용하여 멤버 변수 초기화
}

// 커피를 만드는 메서드 구현 (물만 소모)
bool BaseCoffeeMachine::brew(int cups) {
    // 입출력 예시에 따라, 이 함수는 물만 소모시킴.
    // 자식 클래스에서 재료 확인 전 선행 호출됨.
    // 1컵당 1ml의 물을 소모한다고 가정.
    this->availableWater -= cups;
    return true; // 항상 true를 반환하여 자식 클래스에서 다음 로직을 진행하게 함
}

// 커피 머신 상태를 출력하는 메서드 구현
void BaseCoffeeMachine::show() {
    // 공통적인 상태 정보 출력
    cout << getModel() << " ," << getManufacturer() << " ,남은 물 " << getAvailableWater() << "ml";
}

// EspressoMachine 클래스의 생성자 구현
EspressoMachine::EspressoMachine(string model, string manufacturer, int totalWater, int totalBeans)
    : BaseCoffeeMachine(model, manufacturer, totalWater) {
    this->availableBeans = totalBeans;
}

// 에스프레소를 만드는 메서드 구현
bool EspressoMachine::brewEspresso(int cups) {
    BaseCoffeeMachine::brew(cups); // 1. 물을 먼저 소모

    int beansNeeded = cups; // 1컵당 1개의 원두 소모
    if (this->availableBeans < beansNeeded) { // 2. 원두가 충분한지 확인
        cout << "커피 콩이 부족하여 에스프레소를 만들 수 없습니다." << endl;
        return false;
    }

    this->availableBeans -= beansNeeded; // 3. 원두 소모
    cout << "에스프레소를 만들었습니다." << endl;
    return true;
}

// 에스프레소 머신 상태를 출력하는 메서드 구현
void EspressoMachine::showState() {
    BaseCoffeeMachine::show(); // 부모 클래스의 show() 호출
    cout << " ,남은 커피 콩 " << this->availableBeans << "개" << endl;
}

// AmericanoMachine 클래스의 생성자 구현
AmericanoMachine::AmericanoMachine(string model, string manufacturer, int totalWater, int totalCapsules)
    : BaseCoffeeMachine(model, manufacturer, totalWater) {
    this->availableCapsules = totalCapsules;
}

// 아메리카노를 만드는 메서드 구현
bool AmericanoMachine::brewAmericano(int cups) {
    BaseCoffeeMachine::brew(cups); // 1. 물을 먼저 소모

    int capsulesNeeded = cups; // 1컵당 1개의 캡슐 소모
    if (this->availableCapsules < capsulesNeeded) { // 2. 캡슐이 충분한지 확인
        cout << "캡슐이 부족하여 아메리카노를 만들 수 없습니다." << endl;
        return false;
    }

    this->availableCapsules -= capsulesNeeded; // 3. 캡슐 소모
    cout << "아메리카노를 만들었습니다." << endl;
    return true;
}

// 아메리카노 머신 상태를 출력하는 메서드 구현
void AmericanoMachine::showState() {
    BaseCoffeeMachine::show(); // 부모 클래스의 show() 호출
    cout << " ,남은 캡슐 " << this->availableCapsules << "개" << endl;
}

// CoffeeMachineManager 클래스의 생성자 구현
CoffeeMachineManager::CoffeeMachineManager() {
    // 입출력 예시에 나온 초기값으로 객체 동적 할당
    em = new EspressoMachine("Barista Express", "Breville", 2000, 50);
    am = new AmericanoMachine("VertuoPlus", "Nespresso", 1500, 30);
}

// CoffeeMachineManager 클래스의 소멸자 구현
CoffeeMachineManager::~CoffeeMachineManager() {
    // 동적으로 할당된 메모리 해제
    delete em;
    delete am;
}

// 커피 머신을 작동시키는 메서드 구현
void CoffeeMachineManager::operate() {
    cout << "현재 작동중인 2 대의 커피 머신은 아래와 같습니다:" << endl;
    cout << "에스프레소 머신: "; em->showState();
    cout << "아메리카노 머신: "; am->showState();
    cout << endl;

    char choiceContinue = 'y';

    while (choiceContinue == 'y' || choiceContinue == 'Y') {
        cout << "커피 머신(1:에스프레소, 2:아메리카노)과 컵 수 입력>>";
        int machineType, cups;
        cin >> machineType >> cups;

        if (machineType == 1) {
            em->brewEspresso(cups);
        }
        else if (machineType == 2) {
            am->brewAmericano(cups);
        }

        // 작업 후 머신 상태 출력
        em->showState();
        am->showState();

        cout << "계속 커피를 만드시겠습니까(y/n)>>";
        cin >> choiceContinue;
        cout << endl; // 입출력 형식에 맞게 한 줄 띄움
    }
}

int main() {
    CoffeeMachineManager manager; // 커피 머신 관리자 인스턴스 생성
    manager.operate(); // 커피 머신 작동
    return 0;
}