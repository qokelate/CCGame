#include <windows.h>
#include <stdio.h>

class Base
{
public:
	Base(){ printf("ptr=%p, 无参构造Base()\n", this); };
	Base(const unsigned long size){  printf("ptr=%p, 有参构造Base(unsigned long size = %lu)\n", this, size); };
	~Base(){ printf("ptr=%p, 析构~Base()\n", this); };
};

class Child : public Base
{
public:
//	Child(){ Child(1);  printf("ptr=%p, 无参构造Child()\n", this); };
	Child(const unsigned long size){  printf("ptr=%p, 有参构造Child(unsigned long size = %lu)\n", this, size); };
	~Child(){  printf("ptr=%p, 析构~Child()\n", this); };
};

void hook(Base b)
{
	static Base a;
	a = b;
}

typedef struct _Box
{
	long a = 0;
}Box, *PBox;

int main()
{
	auto temp =  Child(900UL);
	//temp->Base(900);
	//delete temp;

	Box ba ;

	hook(temp);



	return 0;
}