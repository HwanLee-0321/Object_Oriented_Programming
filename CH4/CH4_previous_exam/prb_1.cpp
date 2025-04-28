#include <iostream>
#include <string>
using namespace std;

class Room {
    string name;   // 방 사용자 이름
    int roomNO;    // 방 번호
public:
    Room(string name, int roomNO);  // 생성자
    Room();                         // 기본 생성자

    int getRoomNO();                // 방 번호 반환
    void setRoomNO(int roomNO);     // 방 번호 설정
    void changeName(string name);   // 사용자 이름 변경
    void showRoom();                // 방 정보 출력
};

// Room 클래스 생성자: 파라미터로 이름과 방 번호를 받음
Room::Room(string name, int roomNO) : name(name), roomNO(roomNO) {}

// Room 클래스 기본 생성자  완성 
// Room 클래스 기본 생성자  // "Chosun"이라는 기본 이름과 0번 방 번호로 초기화
Room::Room() : Room("Chosun", 0) {}

// Room 클래스의 사용자 이름 변경 메소드
void Room::changeName( string name) {
    this->name = name;  // 새로운 이름으로 변경
}

// Room 클래스의 방 번호 반환 메소드
int Room::getRoomNO()  {
    return this->roomNO;  // 방 번호 반환
}

// Room 클래스의 방 번호 설정 메소드
void Room::setRoomNO(int roomNO) {
    this->roomNO = roomNO;  // 새로운 방 번호로 설정
}

// Room 클래스의 방 정보 출력 메소드
void Room::showRoom()  {
    cout << "Name: " << this->name << ", Room NO: " << this->roomNO << endl;  // 방 사용자 이름과 번호 출력
}

// House 클래스 정의: 집에 관한 정보를 나타내는 클래스
class House {
private:
    int size;           // 집에 있는 방의 개수
    string houseName;   // 집 이름
    string address;     // 집 주소
    Room* roomList;     // 방 리스트
public:
    House(int size,  string houseName, string address);  // 생성자
    void showHouse() ;                                   // 집 정보 출력
    bool rentRoom( string name, int roomNO);             // 방 렌트
    ~House();  // 소멸자
};

// House 클래스 생성자: 집 이름, 주소, 그리고 방 개수를 파라미터로 받음
House::House(int size, string houseName, string address)
    : size(size), houseName(houseName), address(address) {  // 멤버 변수 초기화

    // 문제 1
    // 방 정보 저장을 위한 roomList 생성 
    // 생성된 방의 번호를 1부터 순차적으로 초기화
    // 방 번호 변경 할때는 Room 클래스의 setRoomNO() 함수 이용
    
    roomList = new Room[size];
    for (int i=0; i < size; i++){
        roomList[i].setRoomNO(i+1);
    }
}

// House 클래스 소멸자: 메모리 해제
House::~House() {
    if (roomList) {  // roomList가 nullptr이 아닌지 확인
        delete[] roomList;  // 동적 메모리 해제
    }
}


// 문제 2
// House 클래스의 방 렌트 메소드
// 입력한 방 번호가 존재하면 해당 번호의 방 사용자 이름 수정하고 true 리턴
// 입력한 방 번호가 존재하지 않으면 false 리턴
bool House::rentRoom(string name, int roomNO) {
    if (roomNO < 1 || roomNO > size) {
        return false;  // 유효하지 않은 방 번호
    }

    roomList[roomNO - 1].changeName(name);  // 방 번호는 1부터 시작, 인덱스는 0부터
    return true;  // 렌트 성공
}

// House 클래스의 집 정보 출력 메소드
void House::showHouse()  {
    cout << "House Name: " << houseName << endl;  // 집 이름 출력
    cout << "Address: " << address << endl;  // 집 주소 출력
    cout << "Room List:" << endl;  // 방 목록 출력

    for (int i = 0; i < size; ++i) {  // 모든 방 정보 출력
        roomList[i].showRoom();
    }
}

// 메인 함수: 프로그램의 시작 지점
int main() {
    int roomSize;  // 방의 개수
    string name;  // 사용자 이름
    int roomNO;  // 방 번호

    cout << "Enter the number of rooms: ";  // 방의 개수 입력 메시지
    cin >> roomSize;  // 사용자가 입력한 방 개수 가져오기

    House chosun(roomSize, "Chosun Dormitory", "Gwangju");  // House 객체 생성

    chosun.showHouse();  // 초기 집 정보 출력

    // 방 렌트
    for (int i = 0; i < roomSize; ++i) {  // 사용자가 지정한 수만큼 반복
        cout << "Enter the room user's name and room number: ";  // 사용자 이름과 방 번호 입력 메시지
        cin >> name >> roomNO;  // 입력 받기

        if (chosun.rentRoom(name, roomNO)) {  // 렌트 성공 여부 확인
            cout << "Successfully rented the room." << endl;  // 성공 메시지
        } else {
            cout << "Room number input error." << endl;  // 오류 메시지
        }
    }

    chosun.showHouse();  // 최종 집 정보 출력

    return 0;  // 메인 함수가 성공적으로 종료될 때 반환하는 값
}
