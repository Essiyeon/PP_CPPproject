// Cppbasics2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "Dog.h"

int main()
{
    std::cout << "Cppbasics2\n";
    Dog dd, ee, ff;
    dd.setweight(20);
    std::cout << dd.getweight();
}