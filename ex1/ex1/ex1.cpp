// ex1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>


template <unsigned long N>
struct binary
{
	static unsigned const value = 
		binary<N/10>::value * 2 + N%10;
};

template <>
struct binary<0>
{
	static unsigned const value = 0;
};



int _tmain(int argc, _TCHAR* argv[])
{
//	std::cout << std::binary<101010>::value << endl;

	printf( "%d\n", binary<1101>::value );

	return 0;
}

