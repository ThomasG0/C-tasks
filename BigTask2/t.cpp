#include <map>
#include <iostream>
#include <string>
#include <vector>
using namespace std;   

template<class Key,class Basic,class Stage>
class Mark_Factory
{
	private:
		typedef Basic* (*Tmaker)(Stage);
		std::map<Key,Tmaker> giver;
		template<class Given>
		static Basic* maker(Stage arg)
		{
			return new Given(arg);
		}
		Tmaker _gimme(Key key)
		{
			return giver[key];
		}
	public:
		template<class Given>
		void CreateTrack(Key key)
		{
			giver[key] = &maker<Given>;
		}
		Basic* gimme(Key key,Stage st)
		{
			return	_gimme(key)(st);
		}
		Basic* gimme(Key key,int st)
		{
			return	_gimme(key)(std::vector<double>((double)st));
		}
		Basic* gimme(Key key)
		{
			return	_gimme(key)(std::vector<double>((double)0));
		}
};

class Function
{
	public:
		std::vector<double> vals;
		Function(std::vector<double> v): vals(v)
		{}
		Function(int i): vals(std::vector<double>((double)i))
		{}
		Function(double i): vals(std::vector<double>(i))
		{}
		Function()
		{}
		virtual ~Function(){}
		virtual void who() = 0;
};

class Const: public Function
{
	using Function::Function;
	public:
		void who() {std::cout<<"i am const\n";}
};

class Ident: public Function
{
	using Function::Function;
	public:
		void who() {std::cout<<"i am ident\n";}
};

class Exp: public Function
{
	using Function::Function;
	public:
		void who() {std::cout<<"i am exp\n";}
};

class Polynomial: public Function
{
	using Function::Function;
	public:
	void who() {std::cout<<"i am polynomial\n";}
};

class Power: public Function
{
	using Function::Function;
	public:
		void who() {std::cout<<"i am power\n";}
};

int main(void)
{
    Mark_Factory<std::string,Function,std::vector<double>> Factory;
    
    Factory.CreateTrack<Const>("const");
    Factory.CreateTrack<Ident>("ident");
    Factory.CreateTrack<Power>("power");
    Factory.CreateTrack<Polynomial>("polynomial");
    Factory.CreateTrack<Exp>("exp");
    Factory.gimme("polynomial",{1,2,3});
    Function *a = Factory.gimme("const",1.3);
    a->who();
    Function *b = Factory.gimme("exp");
    b->who();
    std::vector<double> aq(1.1);
    Polynomial u();
    return 0;
}
