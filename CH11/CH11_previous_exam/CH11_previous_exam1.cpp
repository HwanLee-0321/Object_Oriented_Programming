#include <iostream>
#include <string>
using namespace std;

// 학생 class
class Student {
public:
	string name;
	int    id;
public:
	Student(string name="", int id=0) {
		this->name = name;
		this->id = id;
	}

	/*학생 정보 받아 주는 함수 정의*/
	friend istream& operator >> (istream& ins, Student &a); // friend 선언

	/*학생 정보 출력해 주는 함수 정의 */
	friend ostream& operator << (ostream& stream, Student a); // friend 선언
};

/* 문제 1 학생 정보 받아 주는 함수 구현*/
istream& operator >> (istream& ins, Student &a){
    cout << "Input name>>";
    ins >> a.name;
    cout << "Input ID>>";
    ins >> a.id;
    return ins; // 수정: 입력 스트림 반환
}


/* 문제 2 학생 정보 출력해 주는 함수 구현 */
ostream& operator << (ostream& stream, Student a){
    // cout 대신 매개변수로 받은 stream을 사용해야 함
    stream << "[" << "name:" << a.name << ",ID:" << a.id << "]" << endl;
    return stream; // 수정: 출력 스트림 반환
}

/* 문제 3 오류 메세지 관련 조작자 구현 2개의 조작자 함수*/
ostream& message_same(ostream& os){ // 수정: ostream 참조를 인자로 받음
    os << "Same" << endl;
    return os; // 수정: ostream 참조 반환
}

ostream& message_different(ostream& os){ // 수정: ostream 참조를 인자로 받음
    os << "Different" << endl;
    return os; // 수정: ostream 참조 반환
}

int main() {
	Student StdA, StdB;
	
	// 학생 정보 받기 
	cin >> StdA;   
	cin >> StdB;

	// 학생 정보 출력
	cout << StdA;
	cout << StdB;

	if ( StdA.name == StdB.name && StdA.id == StdB.id)
		cout << message_same;
	else
		cout << message_different;
}