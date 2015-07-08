#include "StdAfx.h"
#include "String.h"
#include "string"


struct String::Srep{
	char *s;//到元素的指针
	int sz;//字符串的长度
	int n;//对角引用的次数
	Srep(int nsz, const char* p)
	{
		n = 1;
		sz = nsz;
		s = new char[sz + 1];
		strcpy_s(s,sz+1,p);
	}
	~Srep()
	{
		delete[] s;
	}
	Srep* get_own_copy()//复制自己
	{
		if (n == 1)return this;
		n--;
		return new Srep(sz, s);
	}
	void assign(int nsz, const char* p){//重新赋值
		if (sz != nsz){
			delete[] s;
			sz = nsz;
			s = new char[sz + 1];
		}
		strcpy_s(s, sz + 1, p);
	}
private://防止复制与赋值
	Srep(const Srep&);
	Srep& operator=(const Srep&);
};

//拷贝构造
String::String(const String& x)
{
	x.rep->n++;
	rep = x.rep;
}

//带有参数的构造函数,默认参数s=""
String::String(const char* s)
{
	rep = new Srep(strlen(s), s);
}

String::~String()
{
	if (--rep->n == 0)delete rep;
}

//赋值运算符重载
String& String::operator=(const String& x)
{
	x.rep->n++;
	if (--rep->n == 0)delete rep;//若无对象指向这块字符串区，则删除
	rep = x.rep;
	return *this;
}

//赋值运算符重载
String& String::operator=(const char* s)
{
	if (rep->n == 1)
	{
		rep->assign(strlen(s), s);//若当前计数为1，则将字符串区域重新赋值，这样可以减少一些内存的重新分配
	}
	else
	{
		rep->n--;
		rep = new Srep(strlen(s), s);//重新构造字符串区域
	}	
	return *this;
}

//测试序号i是否越界，若越界抛出异常
void String::check(int i) const{
	if (i < 0 || rep->sz < i)throw Range();
}

//读某个字符
char String::read(int i)const
{
	return rep->s[i];
}

//写某个字符
void String::write(int i, char c)
{
	rep = rep->get_own_copy(); rep->s[i] = c;
}

//[]运算符重载，非const
String::Cref String::operator[](int i)
{
	check(i);
	return Cref(*this,i);
} 

//[]运算符重载，const
char String::operator[](int i) const
{
	check(i);
	return rep->s[i];
}

//获取字符串大小
int String::size()const
{
	return rep->sz;
}

String String::substr(size_t spos)//子串，从spos处到未尾
{
	return String(this->rep->s + spos);
}

String String::substr(size_t spos, size_t len)//子串，从spos处开始，长度为len
{
	String ret = *this;
	ret.rep->n--;
	ret.rep = new Srep(len, "");
	memcpy_s(ret.rep->s, len, rep->s + spos,len);
	ret.rep->s[len] = 0;
	return ret;
}

//+=运算符重载
String& String::operator+=(const String& x){
	char* cs = new char[rep->sz + x.rep->sz + 1];
	strcpy_s(cs, rep->sz + 1, rep->s);
	strcat(cs, x.rep->s);
	rep = rep->get_own_copy();
	rep->sz += x.rep->sz;
	delete rep->s;
	rep->s = cs;
	return *this;
}
//+=运算符重载
String& String::operator+=(const char* s){
	char* cs = new char[rep->sz + strlen(s) + 1];
	strcpy_s(cs, rep->sz + 1, rep->s);
	strcat(cs, s);
	rep = rep->get_own_copy();
	rep->sz += strlen(s);
	delete rep->s;
	rep->s = cs;
	return *this;
}

//<<运算符重载
std::ostream& operator<<(std::ostream& out, const String& x){
	out << x.rep->s;
	return out;
}
//>>运算符重载
std::istream& operator>>(std::istream& in, String& x){
	x.rep = x.rep->get_own_copy();
	char ins[100];//最大字符是为100,这是一个缺陷
	in >> ins;
	x.rep->assign(strlen(ins), ins);
	return in;
}

//==运算符重载
bool operator==(const String& x, const String& y){
	return strcmp(x.rep->s, y.rep->s) == 0;
}

//==运算符重载
bool operator==(const String& x, const char* y){
	return strcmp(x.rep->s, y) == 0;
}

//！=运算符重载
bool operator!=(const String& x, const String& y){
	return strcmp(x.rep->s, y.rep->s) != 0;
}

//！=运算符重载
bool operator!=(const String& x, const char* y){
	return strcmp(x.rep->s, y) != 0;
}

//<运算符重载
bool operator<(const String& x, const String& y){
	return strcmp(x.rep->s, y.rep->s)<0;
}

bool operator<(const String& x, const char* y)
{
	return strcmp(x.rep->s, y)<0;
}

//>运算符重载
bool operator>(const String& x, const String& y){
	return strcmp(x.rep->s, y.rep->s)>0;
}

bool operator>(const String& x, const char* y)
{
	return strcmp(x.rep->s, y)>0;
}

//+运算符重载
String operator+(const String& x, const String& y){
	String ret = x;
	ret += y;
	return ret;
}
//+运算符重载
String operator+(const String& x, const char* s){
	String ret = x;
	ret += s;
	return ret;
}