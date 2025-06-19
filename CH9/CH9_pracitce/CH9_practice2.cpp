#include <iostream>
#include <string>

using namespace std;

/******************************************************************************
 * UI 클래스 선언 및 구현
 *******************************************************************************/
class UI {
public:
    static void println(string msg);
    static void print(string msg);
    static int printGetInt(string msg);
    static int getMainMenu();
    static void getWidthHeight(int& width, int& height);
};

void UI::println(string msg) {
    cout << msg << endl;
}

void UI::print(string msg) {
    cout << msg;
}

int UI::printGetInt(string msg) {
    print(msg);
    int value;
    cin >> value;
    return value;
}

int UI::getMainMenu() {
    return printGetInt("종료:0, 모두보기:1, 자동삽입:2, 모두이동:3, 모두삭제:4 >> ");
}

void UI::getWidthHeight(int& width, int& height) {
    cout << "X축과 Y축으로 이동할 양은(정수 두개 입력)? >> ";
    cin >> width >> height;
}

/******************************************************************************
 * Point 클래스 선언 및 구현
 *******************************************************************************/
class Point {
    int x;
    int y;
public:
    Point(int x = 0, int y = 0);
    void move(int width, int height);
    string toString();
};

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

void Point::move(int width, int height) {
    this->x += width;
    this->y += height;
}

string Point::toString() {
    return "(" + to_string(x) + "," + to_string(y) + ")";
}

/******************************************************************************
 * Shape 클래스 선언
 *******************************************************************************/
class Shape {
    Shape* next;
protected:
    virtual void draw() = 0;
public:
    Shape() { next = nullptr; }
    virtual ~Shape() {}
    void paint() { draw(); }
    Shape* add(Shape* p) { this->next = p; return p; }
    Shape* getNext() { return next; }
    virtual void move(int width, int height) = 0;
};

/******************************************************************************
 * Line 클래스 선언 및 구현
 *******************************************************************************/
class Line : public Shape {
    Point p1;
    Point p2;
protected:
    void draw() override;
public:
    Line(const Point& p1, const Point& p2);
    void move(int width, int height) override;
};

Line::Line(const Point& p1, const Point& p2) {
    this->p1 = p1;
    this->p2 = p2;
}

void Line::draw() {
    UI::println("Line " + p1.toString() + " " + p2.toString());
}

void Line::move(int width, int height) {
    p1.move(width, height);
    p2.move(width, height);
}

/******************************************************************************
 * Rect 클래스 선언 및 구현
 *******************************************************************************/
class Rect : public Shape {
    Point p1;
    Point p2;
protected:
    void draw() override;
public:
    Rect(const Point& p1, const Point& p2);
    void move(int width, int height) override;
};

Rect::Rect(const Point& p1, const Point& p2) {
    this->p1 = p1;
    this->p2 = p2;
}

void Rect::draw() {
    UI::println("Rectangle " + p1.toString() + " " + p2.toString());
}

void Rect::move(int width, int height) {
    p1.move(width, height);
    p2.move(width, height);
}

/******************************************************************************
 * Circle 클래스 선언 및 구현
 *******************************************************************************/
class Circle : public Shape {
    Point center;
    int radius;
protected:
    void draw() override;
public:
    Circle(int radius, const Point& center);
    void move(int width, int height) override;
};

Circle::Circle(int radius, const Point& center) {
    this->radius = radius;
    this->center = center;
}

void Circle::draw() {
    UI::println("Circle " + to_string(radius) + " " + center.toString());
}

void Circle::move(int width, int height) {
    center.move(width, height);
}

/******************************************************************************
 * Factory 클래스 선언 및 구현
 *******************************************************************************/
class Rand {
    int low, max, cur;
public:
    Rand(int low, int high) {
        this->low = low, this->max = high - low + 1, this->cur = (high - low + 1) / 2;
    }
    int operator() () { cur = (cur + 1) % max; return low + cur; }
};

class Factory {
public:
    enum { LINE = 0, CIRCLE = 1, RECT = 2 };
    static Shape* create(int shapeType);
    static Shape* create();
    static int getSize();
};

static Rand randShapeType(Factory::LINE, Factory::RECT);
static Rand randXY(0, 99);
static Rand randRadius(5, 20);
static Rand randSize(5, 10);

static Point newPoint() { return Point(randXY(), randXY()); }

Shape* Factory::create(int shapeType) {
    switch (shapeType) {
    case LINE:
        return new Line(newPoint(), newPoint());
    case CIRCLE:
        return new Circle(randRadius(), newPoint());
    case RECT:
        return new Rect(newPoint(), newPoint());
    }
    return nullptr;
}

Shape* Factory::create() {
    return create(randShapeType());
}

int Factory::getSize() {
    return randSize();
}

/******************************************************************************
 * GraphicEditor 클래스 선언 및 구현
 *******************************************************************************/
class GraphicEditor {
    enum { EXIT = 0, ALL_PAINT = 1, AUTO_INSERT = 2, ALL_MOVE = 3, ALL_REMOVE = 4 };
    Shape* pStart;
    Shape* pLast;

    void add(Shape* p);
    bool empty();
    void removeAllShapes();
protected:
    void autoInsert();
    void allRemove();
    void allPaint();
    void allMove();
public:
    GraphicEditor();
    ~GraphicEditor();
    void run();
};

GraphicEditor::GraphicEditor() {
    pStart = pLast = nullptr;
}

void GraphicEditor::removeAllShapes() {
    for (Shape* p = pStart, *q; p != nullptr; p = q) {
        q = p->getNext();
        delete p;
    }
    pStart = pLast = nullptr;
}

GraphicEditor::~GraphicEditor() {
    removeAllShapes();
}

void GraphicEditor::add(Shape* p) {
    if (pStart == nullptr) {
        pStart = pLast = p;
        return;
    }
    else {
        pLast = pLast->add(p);
    }
}

bool GraphicEditor::empty() {
    if (pStart == nullptr) {
        UI::println("그려진 도형이 없습니다.");
        return true;
    }
    return false;
}

void GraphicEditor::allPaint() {
    if (empty()) return;
    Shape* p = pStart;
    for (int i = 0; p != nullptr; ++i, p = p->getNext()) {
        UI::print("[" + to_string(i) + "]: ");
        p->paint();
    }
}

void GraphicEditor::autoInsert() {
    int size = Factory::getSize();
    for (int i = 0; i < size; i++) {
        add(Factory::create());
    }
    allPaint();
}

void GraphicEditor::allMove() {
    if (empty()) return;
    int width, height;
    UI::getWidthHeight(width, height);
    for (Shape* p = pStart; p != nullptr; p = p->getNext()) {
        p->move(width, height);
    }
    allPaint();
}

void GraphicEditor::allRemove() {
    if (empty()) return;
    removeAllShapes();
}

void GraphicEditor::run() {
    UI::println("그래픽 에디터입니다.");
    while (true) {
        int menu = UI::getMainMenu();
        switch (menu) {
        case ALL_PAINT:
            allPaint();
            break;
        case AUTO_INSERT:
            autoInsert();
            break;
        case ALL_MOVE:
            allMove();
            break;
        case ALL_REMOVE:
            allRemove();
            break;
        case EXIT:
            return;
        default:
            UI::println("명령 선택 오류");
        }
    }
}

/******************************************************************************
 * main() 함수
 ******************************************************************************/
int main() {
    GraphicEditor g;
    g.run();
}