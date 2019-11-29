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
struct are_same
{};

template<class...>
struct flow
{};

template<class A, class B, class...Args>
struct flow<A, B,Args...>: public std::false_type
{};

template<class A, class... Args>
struct flow<A, A, Args...>: public are_same<A, Args...>
{};

template<>
struct are_same<>: public std::true_type
{};

template<class A>
struct are_same<A>: public std::true_type
{};

template<class A, class B, class... Args>
struct are_same<A,B,Args...>: public flow<std::decay_t<A>,std::decay_t<B>,Args...>
{};

template<class...Args>
constexpr bool are_same_v = are_same<Args...>().value;

int main(void)
{
	are_same<int,char> a;
	std::cout<<a.value;
		static_assert(are_same_v<int,int>, "compile assert");
	return 0;
}
