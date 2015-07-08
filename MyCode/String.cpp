#include "StdAfx.h"
#include "String.h"
#include "string"


struct String::Srep{
	char *s;//��Ԫ�ص�ָ��
	int sz;//�ַ����ĳ���
	int n;//�Խ����õĴ���
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
	Srep* get_own_copy()//�����Լ�
	{
		if (n == 1)return this;
		n--;
		return new Srep(sz, s);
	}
	void assign(int nsz, const char* p){//���¸�ֵ
		if (sz != nsz){
			delete[] s;
			sz = nsz;
			s = new char[sz + 1];
		}
		strcpy_s(s, sz + 1, p);
	}
private://��ֹ�����븳ֵ
	Srep(const Srep&);
	Srep& operator=(const Srep&);
};

//��������
String::String(const String& x)
{
	x.rep->n++;
	rep = x.rep;
}

//���в����Ĺ��캯��,Ĭ�ϲ���s=""
String::String(const char* s)
{
	rep = new Srep(strlen(s), s);
}

String::~String()
{
	if (--rep->n == 0)delete rep;
}

//��ֵ���������
String& String::operator=(const String& x)
{
	x.rep->n++;
	if (--rep->n == 0)delete rep;//���޶���ָ������ַ���������ɾ��
	rep = x.rep;
	return *this;
}

//��ֵ���������
String& String::operator=(const char* s)
{
	if (rep->n == 1)
	{
		rep->assign(strlen(s), s);//����ǰ����Ϊ1�����ַ����������¸�ֵ���������Լ���һЩ�ڴ�����·���
	}
	else
	{
		rep->n--;
		rep = new Srep(strlen(s), s);//���¹����ַ�������
	}	
	return *this;
}

//�������i�Ƿ�Խ�磬��Խ���׳��쳣
void String::check(int i) const{
	if (i < 0 || rep->sz < i)throw Range();
}

//��ĳ���ַ�
char String::read(int i)const
{
	return rep->s[i];
}

//дĳ���ַ�
void String::write(int i, char c)
{
	rep = rep->get_own_copy(); rep->s[i] = c;
}

//[]��������أ���const
String::Cref String::operator[](int i)
{
	check(i);
	return Cref(*this,i);
} 

//[]��������أ�const
char String::operator[](int i) const
{
	check(i);
	return rep->s[i];
}

//��ȡ�ַ�����С
int String::size()const
{
	return rep->sz;
}

String String::substr(size_t spos)//�Ӵ�����spos����δβ
{
	return String(this->rep->s + spos);
}

String String::substr(size_t spos, size_t len)//�Ӵ�����spos����ʼ������Ϊlen
{
	String ret = *this;
	ret.rep->n--;
	ret.rep = new Srep(len, "");
	memcpy_s(ret.rep->s, len, rep->s + spos,len);
	ret.rep->s[len] = 0;
	return ret;
}

//+=���������
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
//+=���������
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

//<<���������
std::ostream& operator<<(std::ostream& out, const String& x){
	out << x.rep->s;
	return out;
}
//>>���������
std::istream& operator>>(std::istream& in, String& x){
	x.rep = x.rep->get_own_copy();
	char ins[100];//����ַ���Ϊ100,����һ��ȱ��
	in >> ins;
	x.rep->assign(strlen(ins), ins);
	return in;
}

//==���������
bool operator==(const String& x, const String& y){
	return strcmp(x.rep->s, y.rep->s) == 0;
}

//==���������
bool operator==(const String& x, const char* y){
	return strcmp(x.rep->s, y) == 0;
}

//��=���������
bool operator!=(const String& x, const String& y){
	return strcmp(x.rep->s, y.rep->s) != 0;
}

//��=���������
bool operator!=(const String& x, const char* y){
	return strcmp(x.rep->s, y) != 0;
}

//<���������
bool operator<(const String& x, const String& y){
	return strcmp(x.rep->s, y.rep->s)<0;
}

bool operator<(const String& x, const char* y)
{
	return strcmp(x.rep->s, y)<0;
}

//>���������
bool operator>(const String& x, const String& y){
	return strcmp(x.rep->s, y.rep->s)>0;
}

bool operator>(const String& x, const char* y)
{
	return strcmp(x.rep->s, y)>0;
}

//+���������
String operator+(const String& x, const String& y){
	String ret = x;
	ret += y;
	return ret;
}
//+���������
String operator+(const String& x, const char* s){
	String ret = x;
	ret += s;
	return ret;
}