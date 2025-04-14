#include <iostream>
#include <string>
using namespace std;

// x,y 좌표 값을 저장하는 클래스
class Point {
public:
    int x, y;
    void print() { cout << "(" << x << "," << y << ")"; }
};

// Point 객체들을 저장하는 원형 큐
class Queue {
private:
    string *pname;    // 큐의 이름
    Point  *elements; // 큐의 원소들을 저장하고 있는 배열의 메모리 주소
    int capacity;     // 동적으로 할당된 큐의 크기 (최대 원소 개수)
    int count;        // 현재 큐에 삽입된 원소의 개수
    int frontIdx;     // 큐의 맨 앞 원소의 인덱스(pop()할 원소)
    int backIdx;      // 큐의 맨 뒤 원소 그 다음의 인덱스(새로 push()할 인덱스)
public:
    Queue(const string& name, int capacity) { // 생성자
        pname = new string(name);
        elements = new Point[capacity];
        this->capacity = capacity;
        count = frontIdx = backIdx = 0;
    }
    ~Queue() {
        delete pname;
        delete [] elements;
    }
    Queue(const Queue& src) {
        pname = new string(*src.pname);
        elements = new Point[src.capacity];
        capacity = src.capacity;
        count = src.count;
        frontIdx = src.frontIdx;
        backIdx = src.backIdx;
        for (int i = 0; i < capacity; ++i)
            elements[i] = src.elements[i];
    }
    int maxSize()                    { return capacity; }
    int size()                       { return count; }
    bool empty()                     { return count == 0; }
    void setName(const string& name) { *pname = name; };
    void print() {
        cout << *pname << ": ";
        for (int i=frontIdx, cnt=0; cnt < count; ++cnt, i=(i+1)%capacity)
            elements[i].print();
        cout << endl;
    }
    bool push(const Point& item);
    Point& front();
    Point& back();
    void pop();
};

//-------------------------------------------------
// 여기에 Queue의 적절한 멤버 함수들을 구현하라.
//-------------------------------------------------

// 큐의 맨 뒤에 item을 삽입함
bool Queue::push(const Point& item) {
    if (count >= capacity) // 큐가 가득 찬 경우
        return false;
    // 문제 1: 여기에 아래의 코드를 삽입하시오.
    // item을 elements[backIdx]에 저장한 후
    elements[backIdx] = item;
    // 원형 큐이므로 backIdx = (backIdx+1) % capacity; 한 후 
    backIdx = (backIdx+1) % capacity;
    // count 증가
    count++;
    return true;
}

Point& Queue::front(){ return elements[frontIdx]; }

Point& Queue::back(){ 
    int idx = backIdx-1;
    if (idx < 0) idx = capacity-1;

    return elements[idx];
}

void Queue::pop(){
    if (capacity == 0) return;
    frontIdx = (frontIdx+1) % capacity;
    count --;
}

//-------------------------------------------------
// 아래 함수들은 문제에서 제시한 코드로 대체하시오.
//-------------------------------------------------

// 큐의 첫 원소와 마지막 원소의 위치를 서로 바꾼다.
void swap(Queue& queue) {
    queue.print();
    // queue.front()와 queue.back()의 좌표 값들의 위치를 서로 바꿈
    Point tmp = queue.front();
    queue.front() = queue.back();
    queue.back() = tmp;
    cout << "swap(queue.front(), queue.back())" << endl;
    queue.print();
}
// 큐의 일부 원소들을 출력한 후 삭제한다.
void pop(Queue& queue) {
    cout << "half pop: ";
    int count = queue.size() / 2;
    for (int i = 0; i < count; ++i) {
        queue.front().print();
        queue.pop();
    }
    cout << endl;
    queue.print();
}
// 아래 함수의 매개변수는 call by value 이다. 
void printQueue(Queue q) { // 함수 수정 금지
    q.setName("q    ");
    q.print();             // q의 좌표들을 출력;
}
// 위 함수를 call by value 로 호출한다. 
void parameter(Queue& queue) { // 함수 수정 금지
    printQueue(queue);
    queue.print();
}
// 키보드에서 좌표 값들을 읽어 큐에 삽입함
void input(Queue& queue) {
    int count;
    // 큐에 삽입할 좌표의 개수
    cout << "input count? ";
    cin >> count;
    int space = queue.maxSize() - queue.size(); // 큐의 여유 공간
    // count 값이 큐의 여유 공간보다 더 클 경우 여유공간 크기만큼 설정함
    if (count > space) count = space;
    for (int i = 0; i < count; i++) {
        Point p;
        cout <<"input " << "x, y: " ;
        cin >> p.x >> p.y; // x, y 좌표 값을 입력 받음
        queue.push(p);
    }
    queue.print();
}
//-------------------------------------------------
// 아래 코드는 수정 불가
//-------------------------------------------------
int main() {
    Point points[] = { {0,1}, {2,3}, {4,5}, {6,7}, {8,9} };
    int capacity = sizeof(points) / sizeof(points[0]);

    Queue queue("queue", capacity);
    // points[] 배열에 있는 좌표들을 큐에 삽입함
    for (int i = 0; i < queue.maxSize(); i++)
        queue.push(points[i]);
    queue.print(); // 큐의 모든 원소를 출력함

    while (true) {
        cout << endl << "menu: 0.exit 1.swap 2.pop 3.parameter 4.input >> ";
        int item;
        cin >> item;
        if (item == 0) break;
        switch (item) {
            case 1: swap(queue);      break;
            case 2: pop(queue);       break;
            case 3: parameter(queue); break;
            case 4: input(queue);     break;
        }
    }
    cout << endl << "Good bye!!" << endl;
}

//**************************************************
// 소스 코드 끝
//**************************************************