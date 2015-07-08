#include "stdafx.h"
#include "iostream"
#include "String"

int _tmain(int argc, _TCHAR* argv[])
{
	String mys;
	mys = "123456";
	mys[2]='c';
	String mys1 = mys;
	String mys2 = mys;
	mys2[3] = 'm';
	String b = mys.substr(1);
	String c = mys.substr(1, 4);
	std::cout << mys1 << ":" << mys1.size() << std::endl
		<< mys2 << ":" << mys2.size() << std::endl
		<< b << ":" << b.size() << std::endl
		<< c << ":" << c.size() << std::endl;
	system("pause");
	return 0;
}