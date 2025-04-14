#include <iostream>
#include <string>
using namespace std;

/*=======================소=스=코=드====================*/

class Player {
private:
    string pname;
    int php;
    int pdamage;
public:
    Player(string pname, int php = 100, int pdamage = 1){
        this->pname = pname;
        this->php = php;
        this->pdamage = pdamage;
    }
    void setHp(int hp) { php = hp; }
    string getName() {return pname;}
    int getHp() {return php;}
    int getDamage() {return pdamage;}
    void getInfo();
};

void Player::getInfo() {
    cout << "-----플레이어 정보-----" << endl;
    cout << "플레이어 이름 : " << pname << endl;
    cout << "체력 : " << php << endl;
    cout << "무기 : " << pdamage << endl;
}

class Monster {
private:
    string mname;
    int mhp;
    int mdamage;
public:
    Monster(string mname, int mhp = 100, int mdamage = 1){
        this->mname = mname;
        this->mhp = mhp;
        this->mdamage = mdamage;
    }
    void setHp(int hp) { mhp = hp; }
    string getName() {return mname;}
    int getHp() {return mhp;}
    int getDamage() {return mdamage;}
    void getInfo();
};
void Monster::getInfo() {
    this->mname = mname;
    this->mhp = mhp;
    this->mdamage = mdamage;
    cout << "-----몬스터 정보-----" << endl;
    cout << "몬스터 이름 : " << mname << endl;
    cout << "체력 : " << mhp << endl;
    cout << "무기 : " << mdamage << endl;
}

// case 1
void Attack(Player& p, Monster& m) {
    cout << p.getName() << "(이)가 " << m.getName() << "을 공격했다!" << endl;

    m.setHp(m.getHp() - p.getDamage());
}

// case 2
void Attack(Monster& m, Player& p) {
    cout << m.getName() << "(이)가 " << p.getName() << "을 공격했다!" << endl;

    p.setHp(p.getHp() - m.getDamage());
}

// case 3
void Attack(Player& p1, Player& p2) {
    cout << p1.getName() << "(이)가 " << p2.getName() << "을 공격했다!" << endl;
    
    p2.setHp(p2.getHp() - p1.getDamage());
}

int main() {

    Player player_1("홍길동", 100,10);
    Player player_2("손오공", 100, 5);
    Monster monster_A("몬스터 A"), monster_B("몬스터 B", 200);

    int i;
    cin >> i;
    switch (i)
    {
    case 1: //플레이어가 몬스터 공격
        Attack(player_2, monster_A);
        player_2.getInfo();
        monster_A.getInfo();
        break;
    case 2: //몬스터가 플레이어 공격
        Attack(monster_B, player_1);
        player_1.getInfo();
        monster_B.getInfo();
        break;
    case 3: //플레이어가 플레이어 공격
        Attack(player_1, player_2);
        player_1.getInfo();
        player_2.getInfo();
        break;
    }
    return 0;
}