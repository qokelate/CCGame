#include <windows.h>
#include <stdio.h>

class Base
{
public:
	Base(){ printf("ptr=%p, �޲ι���Base()\n", this); };
	Base(const unsigned long size){  printf("ptr=%p, �вι���Base(unsigned long size = %lu)\n", this, size); };
	~Base(){ printf("ptr=%p, ����~Base()\n", this); };
};

class Child : public Base
{
public:
//	Child(){ Child(1);  printf("ptr=%p, �޲ι���Child()\n", this); };
	Child(const unsigned long size){  printf("ptr=%p, �вι���Child(unsigned long size = %lu)\n", this, size); };
	~Child(){  printf("ptr=%p, ����~Child()\n", this); };
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