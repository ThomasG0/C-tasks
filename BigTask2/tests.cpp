#include <gtest/gtest.h>
#include "liba.h"
TEST(exeptions,Subtest_1)
{
	Mark_Factory<std::string,Function,std::vector<double>> Factory;
	Factory.CreateTrack<Const>("const");
    Factory.CreateTrack<Ident>("ident");
    Factory.CreateTrack<Power>("power");
    Factory.CreateTrack<Polynomial>("polynomial");
    Factory.CreateTrack<Exp>("exp");
    // Factory block
    auto p = Factory.gimme("polynomial",{1,2,1});
    auto c = Factory.gimme("const",1.3);
	auto x = Factory.gimme("ident");
	auto e = Factory.gimme("exp");
	auto q = Factory.gimme("power",5);
	
	ASSERT_THROW(5+*p,std::logic_error);
	ASSERT_THROW(*p+5,std::logic_error);
	ASSERT_THROW(5+*p+*p,std::logic_error);
	ASSERT_THROW(*p+5+*p,std::logic_error);
	ASSERT_THROW(*p+*p+5,std::logic_error);
	
	ASSERT_THROW(5+*c,std::logic_error);
	ASSERT_THROW(*c+5,std::logic_error);
	ASSERT_THROW(5+*c+*c,std::logic_error);
	ASSERT_THROW(*c+5+*c,std::logic_error);
	ASSERT_THROW(*c+*c+5,std::logic_error);
	
	ASSERT_THROW(5+*x,std::logic_error);
	ASSERT_THROW(*x+5,std::logic_error);
	ASSERT_THROW(5+*x+*x,std::logic_error);
	ASSERT_THROW(*x+5+*x,std::logic_error);
	ASSERT_THROW(*x+*x+5,std::logic_error);
	
	ASSERT_THROW(5+*e,std::logic_error);
	ASSERT_THROW(*e+5,std::logic_error);
	ASSERT_THROW(5+*e+*e,std::logic_error);
	ASSERT_THROW(*e+5+*e,std::logic_error);
	ASSERT_THROW(*e+*e+5,std::logic_error);
	
	ASSERT_THROW(5+*q,std::logic_error);
	ASSERT_THROW(*q+5,std::logic_error);
	ASSERT_THROW(5+*q+*q,std::logic_error);
	ASSERT_THROW(*q+5+*q,std::logic_error);
	ASSERT_THROW(*q+*q+5,std::logic_error);

	ASSERT_THROW(5+*p+*x+*c+*e+*q,std::logic_error);
	ASSERT_THROW(*p+*x+*c+*e+*q+5,std::logic_error);
	ASSERT_THROW(*p+5+*x+*c+*e+*q,std::logic_error);
	ASSERT_THROW(*p+5+*x+*c+*e+5+*q,std::logic_error);
	ASSERT_THROW(*p+5+*x+5+*c+5+*e+5+*q,std::logic_error);
	
	// Native block
	Polynomial p1({1,2,3});
	Const c1(1.3);
	Ident x1();
	Exp e1();
	Power q1(5);

	ASSERT_THROW(5+p1,std::logic_error);
	ASSERT_THROW(p1+5,std::logic_error);
	ASSERT_THROW(5+p1+p1,std::logic_error);
	ASSERT_THROW(p1+5+p1,std::logic_error);
	ASSERT_THROW(p1+p1+5,std::logic_error);
	
	ASSERT_THROW(5+c1,std::logic_error);
	ASSERT_THROW(c1+5,std::logic_error);
	ASSERT_THROW(5+c1+c1,std::logic_error);
	ASSERT_THROW(c1+5+c1,std::logic_error);
	ASSERT_THROW(c1+c1+5,std::logic_error);
	
	ASSERT_THROW(5+x1,std::logic_error);
	ASSERT_THROW(x1+5,std::logic_error);
	ASSERT_THROW(5+x1+x1,std::logic_error);
	ASSERT_THROW(x1+5+x1,std::logic_error);
	ASSERT_THROW(x1+x1+5,std::logic_error);
	
	ASSERT_THROW(5+e1,std::logic_error);
	ASSERT_THROW(e1+5,std::logic_error);
	ASSERT_THROW(5+e1+e1,std::logic_error);
	ASSERT_THROW(e1+5+e1,std::logic_error);
	ASSERT_THROW(e1+e1+5,std::logic_error);
	
	ASSERT_THROW(5+q1,std::logic_error);
	ASSERT_THROW(q1+5,std::logic_error);
	ASSERT_THROW(5+q1+q1,std::logic_error);
	ASSERT_THROW(q1+5+q1,std::logic_error);
	ASSERT_THROW(q1+q1+5,std::logic_error);

	ASSERT_THROW(5+p1+x1+c1+e1+q1,std::logic_error);
	ASSERT_THROW(p1+x1+c1+e1+q1+5,std::logic_error);
	ASSERT_THROW(p1+5+x1+c1+e1+q1,std::logic_error);
	ASSERT_THROW(p1+5+x1+c1+e1+5+q1,std::logic_error);
	ASSERT_THROW(p1+5+x1+5+c1+5+e1+5+q1,std::logic_error);

	// rvalue block
	
	ASSERT_THROW(5+Polynomial({1,2,3},std::logic_error);
	ASSERT_THROW(Polynomial({1,2,3}+5,std::logic_error);
	ASSERT_THROW(5+Polynomial({1,2,3}+Polynomial({1,2,3},std::logic_error);
	ASSERT_THROW(Polynomial({1,2,3}+5+Polynomial({1,2,3},std::logic_error);
	ASSERT_THROW(Polynomial({1,2,3}+Polynomial({1,2,3}+5,std::logic_error);
	
	// Multy block

	ASSERT_THROW(5+Const(1.3)+c1*(*c),std::logic_error);
	ASSERT_THROW(Const(1.3)+c1*(*c)+5,std::logic_error);
	
	//+,-,*,/
	
	ASSERT_THROW(5+Const(1.3),std::logic_error);
	ASSERT_THROW(5*Const(1.3),std::logic_error);
	ASSERT_THROW(5-Const(1.3),std::logic_error);
	ASSERT_THROW(5/Const(1.3),std::logic_error);

	ASSERT_THROW(Const(1.3)+5,std::logic_error);
	ASSERT_THROW(Const(1.3)-5,std::logic_error);
	ASSERT_THROW(Const(1.3)*5,std::logic_error);
	ASSERT_THROW(Const(1.3)/5,std::logic_error);

	ASSERT_THROW(5+Const(1.3)+5,std::logic_error);
	ASSERT_THROW(5*Const(1.3)-5,std::logic_error);
	ASSERT_THROW(5-Const(1.3)*5,std::logic_error);
	ASSERT_THROW(5/Const(1.3)/5,std::logic_error);
	
	// NO THROW
	
	ASSERT_NO_THROW(c1+*c);
	ASSERT_NO_THROW(*c+c1);
	ASSERT_NO_THROW(c1+Const(1.3));
	ASSERT_NO_THROW(Const(1.3)+c1);
}

TEST(behavior, Subtest_2)
{
}
TEST(tostring, Subtest_3)
{
}
TEST(values,Subtest_4)
{
}
TEST(derivatives, Subtest_5)
{
}
TEST(operators,Subtest_6)
{
}
TEST(Gradient,Subtest_7)
{
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc,argv);
	
    return RUN_ALL_TESTS();
}
