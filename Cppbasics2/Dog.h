#pragma once
#include <iostream>
#include <math.h>
using namespace std;

class Dog
{
public:
	char name[100];
	int age;
	int weight;
public:
	void setweight(int a) {
		weight = a;
		cout << "Hello..." << sin(30) << endl;
	}
	int getweight();
};

