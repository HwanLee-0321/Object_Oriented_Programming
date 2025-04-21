#include <iostream>
#include <string>

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
    cin.ignore(); // flush leftover newline
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

    cout << "name to find? ";
    cin.ignore(); // flush leftover newline again
    getline(cin, search_name);

    if (search_name == name) {
        cout << "name:" << name << ", id:" << id << ", weight:" << weight << ", married:" << married << endl;
    } else {
        cout << search_name << ": not found" << endl;
    }

    return 0;
}
