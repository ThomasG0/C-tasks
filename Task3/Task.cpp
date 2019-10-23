#include <iostream>
#include <memory>

class A {
	public:
	static void * operator new(size_t size) {
		std::cout << "operator new!" << std::endl;
		return ::operator new(size);
	}
	static void operator delete(void *p, size_t size) {
		std::cout << "operator delete!" << std::endl;
		return ::operator delete(p);
	}
};

template<class T,class S>
struct g_allocator
{
	typedef T value_type;
    g_allocator()
    {}
    template <class Pos>
		g_allocator (const g_allocator<Pos,Pos>& non)
		{}
    value_type* allocate (size_t vol) {
        return reinterpret_cast<value_type*>(S::operator new(vol*sizeof(value_type)));
    }
    void deallocate (value_type* elem, size_t vol) {
        ::operator delete(elem);
    }
};

int main() {
	auto sp = std::make_shared<A>();
	auto sps = std::allocate_shared<A>(g_allocator<A,A>());
}
