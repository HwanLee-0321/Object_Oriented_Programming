#include <iostream> //공백지우고 활용
#include <vector> //공백지우고 활용
#include <algorithm> //공백지우고 활용
#define MAX_SIZE  5
using namespace std;


int main() {

    vector<string> strVec;

    // 문자열 입력 받기
    cout << "문자열을 최대 " << MAX_SIZE << "개 입력하세요:" << endl;
    for (int i = 0; i < MAX_SIZE; ++i) {
        string str;
        cout << "문자열 " << i + 1 << ": ";
        cin >> str;
        strVec.push_back(str); // vector에 삽입
    }

    // string 자료형의 문자열 길이를 구하는 함수는 .length() 이다.
    cout << "각 문자열의 길이:" << endl;
    for_each(strVec.begin(), strVec.end(), [](const string& str) {
        cout << str << "의 길이: " << str.length() << endl;
    });
    return 0;
}