#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main() {
    cin >> boolalpha;
    cout << boolalpha;

    string name, search_name;
    int id;
    double weight;
    bool married;
    
    cout << "Hello world!!" << endl;
        
    cout << "name? ";
    getline(cin, name);
    cout << "name: " << name << endl;
    
    cout << "id? ";
    cin >> id;
    cout << "id: " << id << endl;
    
    cout << "weight? ";
    cin >> weight;
    cout << "weight: " << weight << endl;
    
    cout << "married? ";
    cin >> married;
    cout << "married: " << married << endl;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 개행 문자 제거
    
    cout << "name to find? ";
    getline(cin, search_name);
    
    if (search_name == name) {
        cout << "name:" << name << ", id:" << id << ", weight:" << weight << ", married:" << married << endl;
    } else {
        cout << search_name << ": not found" << endl;
    }
    
    return 0;
}
