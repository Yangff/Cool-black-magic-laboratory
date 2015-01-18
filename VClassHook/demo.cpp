#include "vchook.hpp"
#include <cstdio>

using namespace Yangff::BlackMagic::VBT;

class Father{
public:
	virtual int MyFunc() = 0;
};

class Child : public Father{
public:
	virtual int MyFunc(){
		printf("A");
	}

};

class Joker{
public:
	virtual int MyFunc(){
		puts("A");
	}
	virtual int MyFunc1(){
		puts("B");puts("C");puts("C");
	}
};

int main(){
	//Father * ch1 = new Child();
	Father * ch2 = new Child();

//	Joker * jk = new Joker();
	//_vtbhook<Father, Joker>(ch1, jk).hook(&Father::MyFunc, &Joker::MyFunc4);
	//ch1->MyFunc();
	ch2->MyFunc();
	return 0;
}
