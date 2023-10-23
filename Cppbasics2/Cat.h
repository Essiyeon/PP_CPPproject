#pragma once
class Cat
{
public:
	char name[100];
	int age;
	float weight;
	int whisker;

	void setwhisker(int k);
	void giveweight(float k);
	void changename(char* k);
	float getweight();
};

