// ActionFunction.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <memory>



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
	typedef std::unique_ptr<SomeInterface> f_type;

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

int main()
{
	Action action(function);
	action();
	system("pause");
    return 0;
}

