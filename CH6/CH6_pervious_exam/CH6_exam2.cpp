/*=======================소스코드====================*/
#include <iostream>
#include <string>
using namespace std;

struct Infofood {
    string food;
    int calories;
};

class CalFood {
public:
    static Infofood food[100];
    static int cnt;

    static void addFood(Infofood k){
        if (cnt < 100){
            food[cnt++] = k;
        }
    }

    static int totalCalories(){
        int sum = 0;
        for (int i = 0; i < 3; i++){
            sum += food[i].calories;
        }
        return sum;
    }

    static void printTotalCalories() {
        cout << "************* 누적된 칼로리 *************\n";
        cout << "지금 까지 먹은 음식 : ";
        for (int i = 0; i < cnt; i++) {
            cout << food[i].food << " ";
        }
        cout << endl;
        cout << "총 칼로리: " << totalCalories() << " kcal" << endl;
        cout << endl;
    }
};

// static 멤버 변수 초기화
Infofood CalFood::food[100];
int CalFood::cnt = 0;

class Person {
private:
    Infofood myFood;
public:
    void setfood(Infofood f){
        myFood = f;
        CalFood::addFood(f);
    }
};

int main() {
    Person human[3];
    int i = 0;

    while (i < 3) {
        Infofood eatfood;
        cin >> eatfood.food >> eatfood.calories;
        human[i].setfood(eatfood);
        i++;
    }
    CalFood::printTotalCalories();
}