# MyString
一个轻量级的String类（Copy On Write)

此类String类采用reference Counting技术进行设计，使一个内存中的一个字符串可以被多个String对象共享，当对象更改或销毁时，
计数值减1，若计数值为0，则delete相应的内存。

String类实现以下方法：size(),substr(),以及重载各种运算符。在这些方法当中，需要注意[]和+=两种运算符的设计，因为这两个操
作可能会改变对象的内容。

在设计String类的[]操作符时采用了一个Cref引用类，该类重载了=和char()类型转换，如下：
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
这样当operator[]运算符被调用时，可以根据具体情况采用不同的策略：比如：String a;
当a[i]='c'时，相当于被赋值了，此时开辟新的空间去存放。
而当char m=a[i]时，就不需要开辟空间
上述这两中情况通过引用Cref类都可以满足，从而内存的开辟，提高效率。
