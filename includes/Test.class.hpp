#pragma once

// #ifdef TEST_EXPORT
#define TEST __declspec(dllexport) 
//  

extern "C" {
	int Add(int a, int b);
}

// class Test {
// 	public:
// 		Test() {};
// 		~Test() {};
// };