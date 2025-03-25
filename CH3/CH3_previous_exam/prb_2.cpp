#include <iostream>
#include <string>
using namespace std;

class Circle {
	int radius; // 원의 반지름 값
public:
	void setRadius(int radius); // 반지름을 설정한다.
	double getArea(); // 면적을 리턴한다.
};
void Circle::setRadius(int radius) {
    this->radius = radius;
}
double Circle::getArea() {
	return 3.14*radius*radius;
}

int main() {
    int n, cnt = 0;
    cout << "원의 개수 >>";
    cin >> n;

    Circle* p = new Circle[n];

    for (int i=1;i<n+1;i++){
        int r;
        cout << "원 " << i << "의 반지름 >> ";
        cin >> r;
        p[i].setRadius(r);
    }
    for(int i=0; i<n; i++){
        if (p[i].getArea() > 100) cnt++;
    }

    cout << "면적이 100보다 큰 원은 " << cnt << "개 입니다" << endl;

	delete[] p; // 객체 배열 소멸
}