// ActionFunction.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <string>



class Action {
public:
	Action() : internal() {}

	template <typename FunctionT>
	Action(FunctionT f) : internal(new Wrapper<FunctionT>(f)) {}

	void operator ()() {
		return internal->invoke();
	}
	
private:
	class SomeInterface {
	public:
		SomeInterface() {}
		virtual ~SomeInterface() {}
		virtual void invoke() = 0;

	};
	typedef std::auto_ptr<SomeInterface> f_type;

	template <typename FunctionT>
	class Wrapper : public SomeInterface {
	public:
		Wrapper(FunctionT func) : SomeInterface(), mFunction(func) {}
	
		virtual void invoke() {
			return mFunction();
		}
	private:
		FunctionT mFunction;
	};
	f_type internal;
};



void function()
{
	std::cout << 1 << std::endl;
}

struct Functor
{
	std::string String;
	void operator()()
	{
		std::cout << String << "\n";
	}
};

int main()
{
	Action action = function;
	action();//1
	action = Functor{ "qqq" };
	action();//qqq
	Action action2 = action;
	action = Functor{ "www" };
	action2();//qqq
	action();//www
	system("pause");
    return 0;
}

