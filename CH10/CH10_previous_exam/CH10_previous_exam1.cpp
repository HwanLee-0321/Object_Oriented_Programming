#include <iostream>
#define MAX_ARRAY_SIZE 6
using namespace std;

template <class T>
T smallest(T a[], int n) {
	T min = a[0];
	for (int i = 1; i < n; i++) {
		if (a[i] < min) {
		min = a[i];
		}
	}
	return min;
}	

int main() {
	int x[MAX_ARRAY_SIZE];
	double y[MAX_ARRAY_SIZE];

	cout << "정수 " << MAX_ARRAY_SIZE << "개를 입력하세요:";
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		cin >> x[i];
	cout << "가장 작은 정수는: " << smallest(x, MAX_ARRAY_SIZE) << endl;

	
	cout << "실수 " << MAX_ARRAY_SIZE << "개를 입력하세요:";
	
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		cin >> y[i];
	cout << "가장 작은 실수는: " << smallest(y, MAX_ARRAY_SIZE) << endl;

	return 0;
}
