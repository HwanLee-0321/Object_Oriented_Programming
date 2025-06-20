#include <iostream>
#include <string>

using namespace std;

/******************************************************************************
 * Class Rand (난수 생성기 직접 구현)
 ******************************************************************************/
// 난수를 발생하는 클래스임.
int seed = 0;

// LCG(선형 합동 생성기) 상태를 저장할 전역 변수
// 이 변수는 프로그램 전체에서 난수 생성 상태를 유지합니다.
static unsigned int lcg_state = 0;

class Rand {
    int low, high;

public:
    // [low, high] 범위 내의 값이 발생하도록 초기화
    Rand(int l, int h) : low(l), high(h) {
        // time() 함수를 사용할 수 없으므로, 프로그램은 항상 동일한 순서의
        // 난수를 생성합니다. 사용자가 setSeed()를 호출해야 순서가 바뀝니다.
        // 이는 원래 코드의 동작과 동일합니다.
    }

    // [low, high] 범위 내의 난수 발생하는 함수 (LCG 사용)
    int operator() () {
        // LCG 파라미터 (glibc에서 사용하는 값)
        const unsigned int a = 1103515245;
        const unsigned int c = 12345;

        // 상태를 업데이트하고 다음 난수를 생성
        lcg_state = a * lcg_state + c;

        // 생성된 값을 원하는 범위로 매핑
        return (lcg_state % (unsigned int)(high - low + 1)) + low;
    }

    void setSeed() {
        cout << "seed for random number? ";
        cin >> seed;
        lcg_state = seed; // 사용자가 입력한 값으로 LCG 상태를 초기화
    }
};

// [10, 29] 범위의 난수 발생기
Rand rnd(10, 29);

/******************************************************************************
 * [문제 1] template class
 ******************************************************************************/
template <typename T>
class Store {
    T value;
public:
    Store(const T& v = T{}) { value = v; }
    T get() { return value; }
    void set(const T& v) { value = v; }
    T add(const T& v) { value += v; return value; }
};

void templateClass() {
    Store<int> is;
    int i = is.get();
    cout << "is.get()   : " << i << endl;
    is.set(3);
    cout << "is.set(3)" << endl;
    i = is.add(4);
    cout << "is.add(4)  : " << i << endl;

    Store<string> ss("S1");
    string s = ss.get();
    cout << "ss.get()   : " << s << endl;
    ss.set("S3");
    cout << "ss.set(S3)" << endl;
    s = ss.add("S4");
    cout << "ss.add(S4) : " << s << endl;
}

/******************************************************************************
 * 컨테이너 클래스 (직접 구현)
 ******************************************************************************/

//--- 동적 배열 클래스 ---
class MyVector {
    int* m_data;
    int m_size;
    int m_capacity;

    void reallocate(int new_capacity) {
        int* new_data = new int[new_capacity];
        if (m_data) {
            for (int i = 0; i < m_size; ++i) {
                new_data[i] = m_data[i];
            }
            delete[] m_data;
        }
        m_data = new_data;
        m_capacity = new_capacity;
    }

public:
    MyVector() : m_data(nullptr), m_size(0), m_capacity(0) {
        reallocate(10);
    }
    ~MyVector() {
        delete[] m_data;
    }

    void push_back(int value) {
        if (m_size >= m_capacity) {
            reallocate(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        m_data[m_size++] = value;
    }

    void clear() { m_size = 0; }
    bool empty() const { return m_size == 0; }
    int size() const { return m_size; }
    int& operator[](int index) { return m_data[index]; }
    
    int* begin() { return m_data; }
    int* end() { return m_data + m_size; }
    
    void sort() {
        for (int i = 1; i < m_size; i++) {
            int key = m_data[i];
            int j = i - 1;
            while (j >= 0 && m_data[j] > key) {
                m_data[j + 1] = m_data[j];
                j = j - 1;
            }
            m_data[j + 1] = key;
        }
    }
};

//--- 이진 탐색 트리 클래스 ---
class MyMap {
private:
    struct Node {
        int key;
        string value;
        Node *left, *right;
        Node(int k, string v) : key(k), value(v), left(nullptr), right(nullptr) {}
    } *root;

    void clearRecursive(Node* node) {
        if (!node) return;
        clearRecursive(node->left);
        clearRecursive(node->right);
        delete node;
    }

    Node* insertRecursive(Node* node, int key, const string& value) {
        if (!node) return new Node(key, value);
        if (key < node->key) node->left = insertRecursive(node->left, key, value);
        else if (key > node->key) node->right = insertRecursive(node->right, key, value);
        else node->value = value;
        return node;
    }
    
    Node* findRecursive(Node* node, int key) {
        if (!node || node->key == key) return node;
        if (key < node->key) return findRecursive(node->left, key);
        else return findRecursive(node->right, key);
    }

    void printInOrderRecursive(Node* node) const {
        if (!node) return;
        printInOrderRecursive(node->left);
        cout << "(" << node->key << "," << node->value << ") ";
        printInOrderRecursive(node->right);
    }

    void keysToVectorRecursive(Node* node, MyVector& vec) const {
        if (!node) return;
        keysToVectorRecursive(node->left, vec);
        vec.push_back(node->key);
        keysToVectorRecursive(node->right, vec);
    }

public:
    MyMap() : root(nullptr) {}
    ~MyMap() { clear(); }

    void clear() { clearRecursive(root); root = nullptr; }
    bool empty() const { return root == nullptr; }

    string& operator[](int key) {
        Node* found = findRecursive(root, key);
        if (found) return found->value;
        root = insertRecursive(root, key, "");
        return findRecursive(root, key)->value;
    }
    
    Node* find(int key) { return findRecursive(root, key); }
    void printInOrder() const { printInOrderRecursive(root); }
    void keysToVector(MyVector& vec) const { keysToVectorRecursive(root, vec); }
};

MyVector iv;
MyMap mp;

void printVector(string msg = {}) {
    if (!msg.empty())
        cout << msg << endl;
    cout << "vector: ";
    for (int val : iv) {
        cout << val << " ";
    }
    cout << endl;
}

void vectorAppend() {
    // [문제 8] 아래 주석 해제
    //rnd.setSeed(); 
    if (!iv.empty()) iv.clear();
    for(int i=0; i<10; ++i) {
        iv.push_back(rnd());
    }
}

void vectorDisplay() {
    vectorAppend();
    printVector();
}

void vectorSort() {
    vectorAppend();
    printVector("before sort");
    iv.sort();
    printVector("after sort");
}

void vectorLambda() {
    vectorAppend();
    printVector("before add");
    int start = seed;

    auto lmd = [&start](int& val) {
        val += start;
    };
    start++;
    
    for (int& val : iv) {
        lmd(val);
    }
    printVector("after add");
}

void printMap(string msg = {}) {
    if (!msg.empty())
        cout << msg << endl;
    cout << "map: ";
    mp.printInOrder();
    cout << endl;
}

void vectorToMap() {
    vectorAppend();
    printVector();
    if (!mp.empty()) mp.clear();
    for (int val : iv) {
        mp[val] = "S" + to_string(val % 10);
    }
    printMap("vector => map");
}

void find_map() {
    int key = rnd();
    auto* node = mp.find(key);
    if (node) {
        cout << "(" << node->key << "," << node->value << ")" << endl;
    } else {
        cout << "key(" << key << ") not found" << endl;
    }
}

void mapFind() {
    vectorToMap();
    find_map();
    find_map();
    find_map();
}

void mapToVector() {
    vectorToMap();
    iv.clear();
    mp.keysToVector(iv);
    printVector("map => vector");
}

/******************************************************************************
 * menu_switch() 함수: 선택된 메인 메뉴 항목을 실행함
 ******************************************************************************/
string menuStr =
"------------- Template and STL ------------\n"
"  0.exit 1.template_class 2.vector 3.sort  \n"
"  4.lambda 5.map 6.find 7.mapToVector      \n"
"-------------------------------------------\n"
"menu item? ";

void menu_switch(int menu)
{
    switch (menu) {
    case 1: templateClass(); break;
    case 2: vectorDisplay(); break;
    case 3: vectorSort();    break;
    case 4: vectorLambda();  break;
    case 5: vectorToMap();   break;
    case 6: mapFind();       break;
    case 7: mapToVector();   break;
    }
    cout << endl;
}

/******************************************************************************
 * main() 함수
 ******************************************************************************/
int main()
{
    while (true) {
        int menu;
        cout << menuStr;
        cin >> menu;
        if (menu == 0) break;
        menu_switch(menu);
    }
    cout << "\nGood bye!!" << endl;
}