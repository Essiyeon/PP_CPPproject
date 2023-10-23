#include "Cat.h"

void Cat::setwhisker(int k) {
	int a;
	a = whisker * 2;
	if (a > 20) a = 20;
	else a = a - 1;
	whisker = a;
}
void Cat::giveweight(float k) {
	weight = k;
}
void Cat::changename(char* k) {
	;
}
float Cat::getweight() {
	return weight;
}