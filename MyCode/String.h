#pragma once
#include "iostream"

/************************************************
**********   һ����������string��
**********     ������  20150708
**********String�����reference Counting����������ƣ�ʹһ���ڴ��е�һ���ַ������Ա����String��������������Ļ�����ʱ������ֵ��1��������ֵΪ0����delete��
**********String��ʵ�����·�����size(),substr(),�Լ����ظ��������������Щ�������У���Ҫע��[]��+=�������������ƣ���Ϊ�������������ܻ�ı��������ݡ�
**********�����String���[]������ʱ������һ��Cref�����࣬����������=��char()����ת�������������Բ���ÿ����[]��ȥ�����µĿռ䣬��ֻ�е�����ֵʱ����Ҫȥ���ٿռ䡣
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
	class Cref{//����char
	private:
		String& s;
		int i;
	public:
		friend class String;
		Cref(String& ss, int ii) :s(ss), i(ii){}
		operator char() const{ return s.read(i); }
		void operator=(char c){ s.write(i, c); }
	};
	class Range{};//�����쳣

private:
	void check(int i) const;//�������i�Ƿ�Խ��
	char read(int i)const;//��ĳ���ַ�
	void write(int i, char c);//дĳ���ַ�
public:
	int size()const;//��ȡ��С 
	String substr(size_t spos = 0);//�Ӵ�����spos����δβ
	String substr(size_t spos, size_t len);//�Ӵ�����spos����ʼ������Ϊlen

	//���������
	Cref operator[](int i);//����const���ÿ��Ƕ�Ӧλ����ֵ�����
	char operator[](int i)const;//[]�����  const

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

