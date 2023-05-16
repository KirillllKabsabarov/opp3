#include<iostream>
#include"container.h"
#include<time.h>

class Test {
public:
	Test() {
		value = 0;
	}
	void setValue(int value) {
		this->value = value;
	}
	int getValue() {
		return value;
	}
protected:
	int value;
};
class Daughtertest : public Test {
public:
	Daughtertest() : Test() { value = 5; }
};
int main() {
	srand(time(0));
	Storage<Test> a;
	int count = 0;
	int itternum = 100;
	while (count < 3) {
		long double time_spent = 0;
		clock_t begin = clock();
		for (int i = 0; i < itternum; i++) {
			switch (rand() % 3) {
			case 0:
				a.deleteObject(rand() % a.getSize());
				break;
			case 1:
				a.pushObject(rand() % a.getSize(), new Daughtertest());
				break;
			case 2:
				switch (rand() % 2) {
				case 0:
					a.getObject(rand() % a.getSize())->getValue();
					break;
				case 1:
					a.getObject(rand() % a.getSize())->setValue(rand() % 100);
					break;
				}
				break;
			}
		}
		clock_t end = clock();
		time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
		printf("itterations: %i; time: %lf seconds\n", itternum, time_spent);
		count++;
		itternum *= 10;
	}

	return 0;
}