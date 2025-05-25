#include <iostream>
using namespace std;

// 정수값 value를 저장하고 있는 double linked 리스트 노드
class Node {
private:
    // 모든 멤버를 private으로 선언하여 외부에서 접근 못하게 하고,
    // BaseList에서만 Node의 모든 멤버에 접근할 수 있게 클래스 전체를 friend로 선언
    friend class BaseList;
    Node *prev;
    Node *next;
    int value;
    Node(int value) { prev = next = nullptr; this->value = value; }
    int getValue() { return value; }
    // 현재 노드 다음에 n 노드를 추가한다.
    void add(Node *n) { next = n; n->prev = this; }
    // 현재 노드를 삭제하고 이 노드의 next 노드를 리턴한다.
    Node *remove() { Node *n = next; delete this; return n; }
};

// 여러 개의 노드들을 가지고 있는 double linked 리스트
class BaseList {
private:
    Node *head;   // 리스트의 맨 처음 노드를 가리키는 포인터
    Node *tail;   // 리스트의 맨 마지막 노드를 가리키는 포인터
protected:
    int size;     // 현재 리스트 내에 있는 노드(데이터)의 개수

    BaseList() { head = tail = nullptr; size = 0; } // 생성자: 멤버 초기화
    // 소멸자: 모든 노드를 삭제함
    ~BaseList() { for (Node *n = head; n != nullptr; n = n->remove()); }

    void add_rear(int value);
    int remove_rear();
    int remove_front();
};

// 새로운 노드(value 값을 저장하고 있음)를 생성한 후 리스트의 맨 마지막에 추가
void BaseList::add_rear(int value) {
    Node *n = new Node(value);
    if (tail != nullptr) {
        tail->add(n);
        tail = n;
    } else {
        head = tail = n;
    }
    size++;
}

// 리스트의 마지막 노드를 제거한 후 그 노드에 저장된 value를 리턴
int BaseList::remove_rear() {
    if (size == 0) return -1;          // list empty error
    int val = tail->getValue();
    Node *prev = tail->prev;
    delete tail;
    size--;
    if (prev != nullptr) {
        prev->next = nullptr;
        tail = prev;
    } else {
        head = tail = nullptr;
    }
    return val;
}

// 리스트의 맨 처음 노드를 제거한 후 그 노드에 저장된 value를 리턴
int BaseList::remove_front() {
    if (size == 0) return -1;          // list empty error
    int val = head->getValue();
    Node *nextNode = head->next;
    delete head;
    size--;
    if (nextNode != nullptr) {
        nextNode->prev = nullptr;
        head = nextNode;
    } else {
        head = tail = nullptr;
    }
    return val;
}

// 큐 구현: BaseList를 상속받음
class MyQueue : public BaseList {
public:
    // 큐의 맨 끝에 노드 추가 후 value 저장
    void enqueue(int value) { add_rear(value); }
    // 큐의 맨 앞의 노드 삭제하고 노드의 value 값 리턴
    int dequeue() { return remove_front(); }
    // 저장된 데이터의 개수 리턴
    int length() { return size; }
    static void test();
};

void MyQueue::test() {
    MyQueue mQ;
    int size;
    cout << "큐에 삽입할 정수의 개수? ";
    cin >> size;
    cout << "큐에 enqueue()된 원소들 : ";
    for (int i = 0; i < size; i++) {
        mQ.enqueue(i * 100);
        cout << i * 100 << ' ';
    }
    cout << endl << "큐의 크기: " << mQ.length() << endl;
    cout << "큐에서 dequeue()된 모든 원소들 : ";
    while (mQ.length() != 0)
        cout << mQ.dequeue() << ' ';
    cout << endl << "큐의 현재 크기 : " << mQ.length() << endl;
}

// 스택 구현: BaseList를 상속받음
class MyStack : public BaseList {
public:
    // 스택의 맨 끝에 노드 추가 후 value 저장
    void push(int value) { add_rear(value); }
    // 스택의 맨 끝의 노드 삭제하고 노드의 value 값 리턴
    int pop() { return remove_rear(); }
    // 저장된 데이터의 개수 리턴
    int length() { return size; }
    static void test();
};

void MyStack::test() {
    MyStack mStack;
    int size;
    cout << "스택에 삽입할 정수의 개수? ";
    cin >> size;
    cout << "스택에 push()된 원소들 : ";
    for (int i = 0; i < size; i++) {
        mStack.push(i);
        cout << i << ' ';
    }
    cout << endl << "스택 크기: " << mStack.length() << endl;
    cout << "스택에서 pop()된 모든 원소들 : ";
    while (mStack.length() != 0)
        cout << mStack.pop() << ' ';
    cout << endl << "스택의 현재 크기 : " << mStack.length() << endl;
}

int main() {
    MyQueue::test();
    MyStack::test();
    return 0;
}
