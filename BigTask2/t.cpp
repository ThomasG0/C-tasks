#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <functional>
#include <sstream>
#include <stdexcept>
using namespace std;   

std::string IntConv(const int i)
{
	std::ostringstream oss;
    oss<< i;
    return oss.str();
}
std::string DoubleConv(const double i)
{
	std::ostringstream oss;
    oss<< i;
    return oss.str();
}

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
		Basic* gimme(Key key,double st)
		{
			std::vector<double> v = {st};
			return	_gimme(key)(v);
		}
		Basic* gimme(Key key,int st)
		{
			std::vector<double> v = {(double)st};
			return	_gimme(key)(v);
		}
		Basic* gimme(Key key)
		{
			std::vector<double> v = {1.};
			return	_gimme(key)(v);
		}
};

class Function
{
	protected:
		std::function<double(double)> val;
		std::function<double(double)> der;
		std::string strp;
		std::vector<double> vals;
	public:
		Function(const std::vector<double> v): vals(v)
		{}
		Function(const double i): vals(std::vector({i}))
		{}
		Function()
		{}
		Function(const Function& other)
		{
			this->val = other.val;
			this->der = other.der;
			this->vals = other.vals;
		}

		virtual void who() {}
		virtual double value(const double i = 0) const { return val(i);}
		virtual double derivative(const double i = 0) const { return der(i);}
		virtual std::string ToString() const {return strp;}
		
		template<class T>
		Function operator+ (const T& other) const;
		template<class T>
		Function operator- (const T& other) const;
		template<class T>
		Function operator* (const T& other) const;
		template<class T>
		Function operator/ (const T& other) const;
		
		virtual ~Function(){}

};

class Const: public Function
{
	using Function::Function;
	public:
		void who() {std::cout<<"i am const\n";}
		double value(const double i = 0) const {return this->vals[0];}
		double derivative(const double i = 0) const {return 0.0;}
		std::string ToString() const
		{
			return DoubleConv(this->vals[0]);
		}
};

class Ident: public Function
{
	using Function::Function;
	public:
		void who() {std::cout<<"i am ident\n";}
		double value(const double i = 0) const {return i;}
		double derivative(const double i = 0) const {return 1.;}
		std::string ToString() const
		{
			return "x";
		}
};

class Exp: public Function
{
	using Function::Function;
	public:
		void who() {std::cout<<"i am exp\n";}
		double value(const double i = 0) const {return exp(this->vals[0]*i);}
		double derivative(const double i = 0) const {return this->vals[0]*exp(this->vals[0]*i);}
		std::string ToString() const
		{
			return std::string("e^") + DoubleConv(this->vals[0]) + "x";
		}
};

class Polynomial: public Function
{
	using Function::Function;
	public:
		void who() {std::cout<<"i am polynomial\n";}
		double value(const double i = 0) const
		{
			if (this->vals.size() < 1) return 0.0;
			 double sum = this->vals[0];
			 for(int j = 1; j < this->vals.size(); ++j)
			 {
				 sum += this->vals[j]*pow(i,j);
			 }
			 return sum;
		}
		double derivative(const double i = 0) const
		{
			 if (this->vals.size() < 2) return 0.0;
			 double sum = this->vals[1];
			 for(int j = 2; j < this->vals.size(); ++j) 
			 {
				 sum += this->vals[j]*j*pow(i,j-1);
			 }
			 return sum;
		}
		std::string ToString() const
		{
			std::string sum = DoubleConv(this->vals[0]);;
			for(int i = 1; i < this->vals.size(); ++i)
			{
				sum += "+" + DoubleConv(this->vals[i]) + "x^" + IntConv(i);
			}
			return std::string("x^") + DoubleConv(this->vals[0]);
		}
};

class Power: public Function
{
	using Function::Function;
	public:
		void who() {std::cout<<"i am power\n";}
		double value(const double i = 0) const
		{
			return pow(i,this->vals[0]);
		}
		double derivative(const double i = 0) const
		{
			return this->vals[0]*pow(i,this->vals[0]-1);
		}
		std::string ToString() const
		{
			return std::string("x^") + DoubleConv(this->vals[0]);
		}
};

template<class T>
Function Function::operator+(const T& other) const
{
	if constexpr (std::is_base_of_v<Function, T> == false)
	{
        throw std::logic_error("bad_operand");
    }
	else
	{
		Function new_el;
		new_el.val = [&](double j){return this->value(j) + other.value(j);};
		new_el.der = [&](double j){return this->derivative(j) + other.derivative(j);};
		new_el.strp += this->ToString() + "+" + other.ToString();
		return new_el;
	}
}
template<class T>
Function Function::operator-(const T& other) const
{
	if constexpr (std::is_base_of_v<Function, T> == false)
	{
        throw std::logic_error("bad_operand");
    }
    else
    {
		Function new_el;
		new_el.val = [&](double j){return this->value(j) - other.value(j);};
		new_el.der = [&](double j){return this->derivative(j) - other.derivative(j);};
		new_el.strp += this->ToString() + "-" + other.ToString();
		return new_el;
	}
}
template<class T>
Function Function::operator*(const T& other) const
{
	if constexpr (std::is_base_of_v<Function, T> == false)
	{
        throw std::logic_error("bad_operand");
    }
    else
    {
		Function new_el;
		new_el.val = [&](double j){return this->value(j) * other.value(j);};
		new_el.der = [&](double j){return this->derivative(j)*other.value(j) + other.derivative(j)*this->value(j);};
		new_el.strp += this->ToString() + "*" + other.ToString();
		return new_el;
	}
}
template<class T>
Function Function::operator/(const T& other) const
{
	if constexpr (std::is_base_of_v<Function, T> == false)
	{
        throw std::logic_error("bad_operand");
    }
    else
    {
		Function new_el;
		new_el.val = [&](double j){return this->value(j) / other.value(j);};
		new_el.der = [&](double j){return (this->derivative(j)*other.value(j) - other.derivative(j)*this->value(j))/(other.value(j)*other.value(j)) ;};
		new_el.strp += this->ToString() + "/" + other.ToString();
		return new_el;
	}
}
template<class T>
Function operator+(const T& other,const Function& a)
{
	if constexpr (std::is_base_of_v<Function, T> == false)
	{
        throw std::logic_error("bad_operand");
    }
    else
    {
		return other.operator+(a);
	}
}
template<class T>
Function operator-(const T& other,const Function& a)
{
	if constexpr (std::is_base_of_v<Function, T> == false)
	{
        throw std::logic_error("bad_operand");
    }
    else
    {
		return other.operator-(a);
	}
}
template<class T>
Function operator*(const T& other,const Function& a)
{
	if constexpr (std::is_base_of_v<Function, T> == false)
	{
        throw std::logic_error("bad_operand");
    }
    else
    {
		return other.operator*(a);
	}
}
template<class T>
Function operator/(const T& other,const Function& a)
{
	if constexpr (std::is_base_of_v<Function, T> == false)
	{
        throw std::logic_error("bad_operand");
    }
    else
    {
		return other.operator/(a);
	}
}

double GD(const Function& g, double eps, int j)
{
	double y = 1.,x = 0.;
	int count = 0;
	Function f = g*g;
	if (std::abs(f.derivative(x)) < eps ) x+=eps;
	for(double i = 2.; count == 0 || ((f.value(x)-f.value(y)) > eps) &&  (count < j); i += 1.)
	{
		++count;
		y = x;
		x = x - (1/std::pow(i,2))*f.derivative(x); x;
	}
	return x;
}

int main(void)
{
    Mark_Factory<std::string,Function,std::vector<double>> Factory;
    
    Factory.CreateTrack<Const>("const");
    Factory.CreateTrack<Ident>("ident");
    Factory.CreateTrack<Power>("power");
    Factory.CreateTrack<Polynomial>("polynomial");
    Factory.CreateTrack<Exp>("exp");
    
    auto b = Factory.gimme("polynomial",{1,2,1});
    auto a = Factory.gimme("const",1.3);
	auto e = Factory.gimme("ident");
    return 0;
}
