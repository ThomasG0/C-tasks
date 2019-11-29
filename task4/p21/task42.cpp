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
	bool value = true;
};

template<class A>
class are_same<A>
{
public:
	bool value = true;
};

template<class A, class B>
class are_same<A,B>
{
public:
	bool value = std::is_same<decay_t<A>,decay_t<B>>::value;
};

template<class A, class B, class C>
class are_same<A,B,C>
{
public:
	bool value = std::is_same<decay_t<A>,decay_t<B>>::value && std::is_same<decay_t<B>,decay_t<C>>::value;
};

template<class A, class B, class... Args>
class are_same<A, B, Args...>: public are_same<Args...>
{
public:
	constexpr are_same(){this->value = this->value && std::is_same<decay_t<A>,decay_t<B>>::value;}
};

template<class...Args>
constexpr bool are_same_v = are_same<Args...>().value;

int main(void)
{
	static_assert(are_same_v<int,int>, "compile assert");
	//static_assert(are_same_v<int, int32_t, signed int>, "compile assert");
	return 0;
}
