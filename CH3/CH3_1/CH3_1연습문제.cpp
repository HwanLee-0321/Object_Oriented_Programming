#include <iostream>
#include <string>

using namespace std;

class Person {
    string name;
    int id;
    double weight;
    bool married;

public:
    Person() : name("no-name"), id(0), weight(0), married(false) {
        cout << "Person::Person():";
        println();
    }
    
    Person(string _name, int _id, double _weight, bool _married) : name(_name), id(_id), weight(_weight), married(_married) {
        cout << "Person::Person(...):";
        println();
    }
    
    ~Person() {
        cout << "Person::~Person():";
        println();
    }
    
    void setName(string _name) { name = _name; }
    void setId(int _id) { id = _id; }
    void setWeight(double _weight) { weight = _weight; }
    void setMarried(bool _married) { married = _married; }
    
    string getName() { return name; }
    int getId() { return id; }
    double getWeight() { return weight; }
    bool getMarried() { return married; }
    
    void println() {
        cout << "name:" << name << ", id:" << id << ", weight:" << weight << ", married:" << boolalpha << married << endl;
    }
};

void set(string name, int id, double weight, bool married) {
    Person p1;
    p1.setName(name);
    p1.setId(id);
    p1.setWeight(weight);
    p1.setMarried(married);
    p1.println();
}

void creator() {
    cout << "creator() begin" << endl;
    Person p2("p2", 1002, 60.5, false);
    cout << "creator() return" << endl;
}

int main() {
    cin >> boolalpha;
    cout << boolalpha;

    string name = "p1";
    int id = 1001;
    double weight = 72.5;
    bool married = true;

    set(name, id, weight, married);

    cout << endl;
    creator();

    cout << endl;
    cout << "name id weight married? ";
    cin >> name >> id >> weight >> married;
    Person p3(name, id, weight, married);

    cout << "output name:" << p3.getName() << ", id:" << p3.getId() << ", weight:" << p3.getWeight() << ", married:" << p3.getMarried() << endl;

    return 0;
}
