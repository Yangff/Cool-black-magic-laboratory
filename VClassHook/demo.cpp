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
		printf("B");
	}
	virtual int MyFunc1(){
		printf("B");
	}
	virtual int MyFunc2(){
		printf("B");
	}
};

int main(){
	Father * ch = new Child();
	Joker * jk = new Joker();
	_vtbhook<Father, Joker>(ch, jk).hook(&Father::MyFunc, &Joker::MyFunc2);
	//ch->MyFunc();
}
