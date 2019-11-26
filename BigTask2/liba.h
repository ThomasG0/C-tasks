#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <functional>
#include <sstream>
#include <stdexcept>

using namespace std;   

std::string IntConv(const int i) // Предстиавление целого числа в виде строки
{
	std::ostringstream oss;
    oss<< i;
    return oss.str();
}
std::string DoubleConv(const double i) // Представление вещественного числа в виде строки
{
	std::ostringstream oss;
    oss<< i;
    return oss.str();
}

template<class Key,class Basic,class Stage> // Фабрика. Ключ, Базовый класс, Тип принимаемого значения конструктором базового класса.
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
		void CreateTrack(Key key) // Создаем дорожки, с которых будем забирать элементы производных типов (отн. базового)
		{
			giver[key] = &maker<Given>;
		}
		Basic* gimme(Key key,Stage st) // Если дан вектор
		{
			return	_gimme(key)(st);
		}
		Basic* gimme(Key key,double st) // Если дано число
		{
			std::vector<double> v = {st};
			return	_gimme(key)(v);
		}
		Basic* gimme(Key key,int st) // Если дано число
		{
			std::vector<double> v = {(double)st};
			return	_gimme(key)(v);
		}
		Basic* gimme(Key key) // Если значения нет (по умолчанию 1)
		{
			std::vector<double> v = {1.};
			return	_gimme(key)(v);
		}
};

class Function // Базовый класс
{
	protected:
		std::function<double(double)> val; // адресс функции, считающей значение функции в точке
		std::function<double(double)> der; // Адресс функции, считающей значение производной функции в точке
		std::string strp; // Строковое представление (поддерживается только у потомков)
		std::vector<double> vals; // Вектор значений для аргументов функции (если не полином, то занимает только одну ячейку)
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
		virtual std::string ToString() const {return "Unknown info";}

		template<class T,class S>
		friend Function operator+(const T& a, const S& b);
		template<class T,class S>
		friend Function operator-(const T& a, const S& b);
		template<class T,class S>
		friend Function operator*(const T& a, const S& b);
		template<class T,class S>
		friend Function operator/(const T& a, const S& b);
		
		virtual ~Function(){}

};

class Const: public Function // Константная функция
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

class Ident: public Function // ТОжд. функция (f = x)
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

class Exp: public Function // Экспонента (e^mx)
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

class Polynomial: public Function // Полином (a0 + a1*x + a2*x^2 + ... + an*x^n)
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
			std::string sum = DoubleConv(this->vals[0]);
			for(int i = 1; i < this->vals.size(); ++i)
			{
				sum += "+" + DoubleConv(this->vals[i]) + "x^" + IntConv(i);
			}
			return sum;
		}
};

class Power: public Function //  Степенная функция (x^k)
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

template<class T,class S>
Function operator+(const T& a, const S& b)
{
	if constexpr (std::is_base_of_v<Function, T> == false || std::is_base_of_v<Function, S> == false)
	{ // Если не совпадает с базовым классом или не потомок, тогда кидаем исключение
        throw std::logic_error("bad_operand");
    }
	else
	{
		Function new_el;
		new_el.val = [&](double j){return a.value(j) + b.value(j);};
		new_el.der = [&](double j){return a.derivative(j) + b.derivative(j);};
		new_el.strp += a.ToString() + "+" + b.ToString();
		return new_el;
	}
}
template<class T,class S>
Function operator-(const T& a, const S& b)
{
	if constexpr (std::is_base_of_v<Function, T> == false || std::is_base_of_v<Function, S> == false)
	{ // Если не совпадает с базовым классом или не потомок, тогда кидаем исключение
        throw std::logic_error("bad_operand");
    }
	else
	{
		Function new_el;
		new_el.val = [&](double j){return a.value(j) - b.value(j);};
		new_el.der = [&](double j){return a.derivative(j) - b.derivative(j);};
		return new_el;
	}
}
template<class T,class S>
Function operator*(const T& a, const S& b)
{
	if constexpr (std::is_base_of_v<Function, T> == false || std::is_base_of_v<Function, S> == false)
	{ // Если не совпадает с базовым классом или не потомок, тогда кидаем исключение
        throw std::logic_error("bad_operand");
    }
	else
	{
		Function new_el;
		new_el.val = [&](double j){return a.value(j) * b.value(j);};
		new_el.der = [&](double j){return a.derivative(j) * b.derivative(j);};
		return new_el;
	}
}
template<class T,class S>
Function operator/(const T& a, const S& b)
{
	if constexpr (std::is_base_of_v<Function, T> == false || std::is_base_of_v<Function, S> == false)
	{ // Если не совпадает с базовым классом или не потомок, тогда кидаем исключение
        throw std::logic_error("bad_operand");
    }
	else
	{
		Function new_el;
		new_el.val = [&](double j){return a.value(j) / b.value(j);};
		new_el.der = [&](double j){return a.derivative(j) / b.derivative(j);};
		return new_el;
	}
}

double GD(const Function& g, double eps, int j) // Метод градиентного спуска с квадратично убывающим показателем (сходится при любом начальном приближении)
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
	return 0;
}
