#pragma once
#include <iostream>
#include <vector>
// #ifdef TEST_EXPORT
#define TEST __declspec(dllexport) 
//  

extern "C" {
	int Add(int a[]);
}

// class Test {
// 	public:
// 		Test() {};
// 		~Test() {};
// };