#pragma once
#include "iostream"

/************************************************
**********   一个轻量级的string类
**********     王慎波  20150708
**********String类采用reference Counting技术进行设计，使一个内存中的一个字符串可以被多个String对象共享，当对象更改或销毁时，计数值减1，若计数值为0，则delete。
**********String类实现以下方法：size(),substr(),以及重载各种运算符。在这些方法当中，需要注意[]和+=两种运算符的设计，因为这两个操作可能会改变对象的内容。
**********在设计String类的[]操作符时采用了一个Cref引用类，该类重载了=和char()类型转换，这样做可以不必每次用[]都去开辟新的空间，而只有当被赋值时才需要去开辟空间。
**************************************************/

class String
{
	struct Srep;
	Srep *rep;
public:
	String(const char* s="");
	String(const String&);
	String& operator=(const char*);
	String& operator=(const String&);
	~String();

public:
	class Cref{//引用char
	private:
		String& s;
		int i;
	public:
		friend class String;
		Cref(String& ss, int ii) :s(ss), i(ii){}
		operator char() const{ return s.read(i); }
		void operator=(char c){ s.write(i, c); }
	};
	class Range{};//用于异常

private:
	void check(int i) const;//测试序号i是否越界
	char read(int i)const;//读某个字符
	void write(int i, char c);//写某个字符
public:
	int size()const;//获取大小 
	String substr(size_t spos = 0);//子串，从spos处到未尾
	String substr(size_t spos, size_t len);//子串，从spos处开始，长度为len

	//运算符重载
	Cref operator[](int i);//不带const，得考虑对应位被赋值的情况
	char operator[](int i)const;//[]运算符  const

	String& operator+=(const String&);
	String& operator+=(const char*);
	
	friend std::ostream& operator<<(std::ostream& ,const String&);
	friend std::istream& operator>>(std::istream&, String&);

	friend bool operator==(const String& x, const String& y);
	friend bool operator==(const String& x, const char* y);

	friend bool operator!=(const String& x, const String& y);
	friend bool operator!=(const String& x, const char* y);

	friend bool operator<(const String& x, const String& y);
	friend bool operator<(const String& x, const char* y);

	friend bool operator>(const String& x, const String& y);
	friend bool operator>(const String& x, const char* y);

};

std::ostream& operator<<(std::ostream&, const String&);
std::istream& operator>>(std::istream&, String&);

bool operator==(const String& x, const String& y);
bool operator==(const String& x, const char* y);

bool operator!=(const String& x, const String& y);
bool operator!=(const String& x, const char* y);

bool operator<(const String& x, const String& y);
bool operator<(const String& x, const char* y);

bool operator>(const String& x, const String& y);
bool operator>(const String& x, const char* y);

String operator+(const String&, const String&);
String operator+(const String&, const char*);

