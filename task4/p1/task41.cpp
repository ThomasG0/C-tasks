#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <functional>
#include <sstream>
#include <memory>
using namespace std;
		
class Any
{
	class Basic
	{
	public:
		virtual const std::type_info& getinf() const = 0;
		virtual ~Basic(){}
	};
	template<typename T>
		class Owner: public Basic
		{
			T value;
		public:
			Owner(const T& value):
				value(value)
			{}
			const std::type_info& getinf() const;
			T getvalue() const;
		};
	std::unique_ptr<Basic> elem;
public:
	template<class T>
		Any(const T& value):
			elem(new Owner<T>(value))
		{}
	template<class S>
		S get() const;
};

template<class T>
	const std::type_info& Any::Owner<T>::getinf() const
{
	return typeid(this->value);
}

template<class T>
	T Any::Owner<T>::getvalue() const
{
	return this->value;
}

template<class S>
	S Any::get() const
{
	if(this->elem->getinf() != typeid(S))
	{
	  	throw std::invalid_argument("Catastrophe! Error: an incorrect \
									template parameter argument was \
									passed to the method \"get\" of \
									the class \"Any\".");
	}
	else
	{
		return static_cast<Owner<S>*>(this->elem.get())->getvalue();
	}
}

int main(void)
{
	Any a(5);
	std::cout<<a.get<int>()<<std::endl;
	return 0;
}
