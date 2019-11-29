#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <functional>
#include <sstream>
#include <memory>
using namespace std;

template<class...>
class are_same
{};

template<>
class are_same<>
{
public:
	bool v = true;
};

template<class A>
class are_same<A>
{
public:
	bool v = true;
};

template<class A, class B>
class are_same<A,B>
{
public:
	bool v = std::is_same<A,B>::value;
};

template<class A, class B, class C>
class are_same<A,B,C>
{
public:
	bool v = std::is_same<A,B>::value && std::is_same<B,C>::value;
};

template<class A, class B, class... Args>
class are_same<A, B, Args...>: public are_same<Args...>
{
public:
	constexpr are_same(){this->v = this->v && std::is_same<A,B>::value;}
};

template<class...Args>
constexpr bool are_same_v = are_same<Args...>().v;

int main(void)
{
		static_assert(are_same_v<int,int>, "compile assert");
	return 0;
}
