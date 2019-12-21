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
	
	EXPECT_THROW(5+*p,std::logic_error);
	EXPECT_THROW(*p+5,std::logic_error);
	EXPECT_THROW(5+*p+*p,std::logic_error);
	EXPECT_THROW(*p+5+*p,std::logic_error);
	EXPECT_THROW(*p+*p+5,std::logic_error);
	
	EXPECT_THROW(5+*c,std::logic_error);
	EXPECT_THROW(*c+5,std::logic_error);
	EXPECT_THROW(5+*c+*c,std::logic_error);
	EXPECT_THROW(*c+5+*c,std::logic_error);
	EXPECT_THROW(*c+*c+5,std::logic_error);
	
	EXPECT_THROW(5+*x,std::logic_error);
	EXPECT_THROW(*x+5,std::logic_error);
	EXPECT_THROW(5+*x+*x,std::logic_error);
	EXPECT_THROW(*x+5+*x,std::logic_error);
	EXPECT_THROW(*x+*x+5,std::logic_error);
	
	EXPECT_THROW(5+*e,std::logic_error);
	EXPECT_THROW(*e+5,std::logic_error);
	EXPECT_THROW(5+*e+*e,std::logic_error);
	EXPECT_THROW(*e+5+*e,std::logic_error);
	EXPECT_THROW(*e+*e+5,std::logic_error);
	
	EXPECT_THROW(5+*q,std::logic_error);
	EXPECT_THROW(*q+5,std::logic_error);
	EXPECT_THROW(5+*q+*q,std::logic_error);
	EXPECT_THROW(*q+5+*q,std::logic_error);
	EXPECT_THROW(*q+*q+5,std::logic_error);

	EXPECT_THROW(5+*p+*x+*c+*e+*q,std::logic_error);
	EXPECT_THROW(*p+*x+*c+*e+*q+5,std::logic_error);
	EXPECT_THROW(*p+5+*x+*c+*e+*q,std::logic_error);
	EXPECT_THROW(*p+5+*x+*c+*e+5+*q,std::logic_error);
	EXPECT_THROW(*p+5+*x+5+*c+5+*e+5+*q,std::logic_error);
	
	// Native block
	Polynomial p1({1,2,3});
	Const c1(1.3);
	Ident x1;
	Exp e1;
	Power q1(5);

	EXPECT_THROW(5+p1,std::logic_error);
	EXPECT_THROW(p1+5,std::logic_error);
	EXPECT_THROW(5+p1+p1,std::logic_error);
	EXPECT_THROW(p1+5+p1,std::logic_error);
	EXPECT_THROW(p1+p1+5,std::logic_error);

	EXPECT_THROW(5/p1,std::logic_error);
	EXPECT_THROW(p1/5,std::logic_error);
	EXPECT_THROW(5/p1/p1,std::logic_error);
	EXPECT_THROW(p1/5/p1,std::logic_error);
	EXPECT_THROW(p1/p1/5,std::logic_error);

	EXPECT_THROW(5*p1,std::logic_error);
	EXPECT_THROW(p1*5,std::logic_error);
	EXPECT_THROW(5*p1*p1,std::logic_error);
	EXPECT_THROW(p1*5*p1,std::logic_error);
	EXPECT_THROW(p1*p1*5,std::logic_error);

	EXPECT_THROW(5*p1,std::logic_error);
	EXPECT_THROW(p1*5,std::logic_error);
	EXPECT_THROW(5*p1-p1,std::logic_error);
	EXPECT_THROW(p1-5-p1,std::logic_error);
	EXPECT_THROW(p1-p1-5,std::logic_error);
	
	EXPECT_THROW(5+c1,std::logic_error);
	EXPECT_THROW(c1+5,std::logic_error);
	EXPECT_THROW(5+c1+c1,std::logic_error);
	EXPECT_THROW(c1+5+c1,std::logic_error);
	EXPECT_THROW(c1+c1+5,std::logic_error);
	
	EXPECT_THROW(5+x1,std::logic_error);
	EXPECT_THROW(x1+5,std::logic_error);
	EXPECT_THROW(5+x1+x1,std::logic_error);
	EXPECT_THROW(x1+5+x1,std::logic_error);
	EXPECT_THROW(x1+x1+5,std::logic_error);
	
	EXPECT_THROW(5+e1,std::logic_error);
	EXPECT_THROW(e1+5,std::logic_error);
	EXPECT_THROW(5+e1+e1,std::logic_error);
	EXPECT_THROW(e1+5+e1,std::logic_error);
	EXPECT_THROW(e1+e1+5,std::logic_error);
	
	EXPECT_THROW(5+q1,std::logic_error);
	EXPECT_THROW(q1+5,std::logic_error);
	EXPECT_THROW(5+q1+q1,std::logic_error);
	EXPECT_THROW(q1+5+q1,std::logic_error);
	EXPECT_THROW(q1+q1+5,std::logic_error);

	EXPECT_THROW(5+p1+x1+c1+e1+q1,std::logic_error);
	EXPECT_THROW(p1+x1+c1+e1+q1+5,std::logic_error);
	EXPECT_THROW(p1+5+x1+c1+e1+q1,std::logic_error);
	EXPECT_THROW(p1+5+x1+c1+e1+5+q1,std::logic_error);
	EXPECT_THROW(p1+5+x1+5+c1+5+e1+5+q1,std::logic_error);

	// rvalue block
	
	EXPECT_THROW(5+Polynomial({1,2,3}),std::logic_error);
	EXPECT_THROW(Polynomial({1,2,3})+5,std::logic_error);
	EXPECT_THROW(5+Polynomial({1,2,3})+Polynomial({1,2,3}),std::logic_error);
	EXPECT_THROW(Polynomial({1,2,3})+5+Polynomial({1,2,3}),std::logic_error);
	EXPECT_THROW(Polynomial({1,2,3})+Polynomial({1,2,3})+5,std::logic_error);
	
	EXPECT_THROW(5/Polynomial({1,2,3}),std::logic_error);
	EXPECT_THROW(Polynomial({1,2,3})/5,std::logic_error);
	EXPECT_THROW(5+Polynomial({1,2,3})/Polynomial({1,2,3}),std::logic_error);
	EXPECT_THROW(Polynomial({1,2,3})/5/Polynomial({1,2,3}),std::logic_error);
	EXPECT_THROW(Polynomial({1,2,3})/Polynomial({1,2,3})/5,std::logic_error);

	EXPECT_THROW(5*Polynomial({1,2,3}),std::logic_error);
	EXPECT_THROW(Polynomial({1,2,3})*5,std::logic_error);
	EXPECT_THROW(5*Polynomial({1,2,3})*Polynomial({1,2,3}),std::logic_error);
	EXPECT_THROW(Polynomial({1,2,3})*5*Polynomial({1,2,3}),std::logic_error);
	EXPECT_THROW(Polynomial({1,2,3})*Polynomial({1,2,3})*5,std::logic_error);

	EXPECT_THROW(5-Polynomial({1,2,3}),std::logic_error);
	EXPECT_THROW(Polynomial({1,2,3})-5,std::logic_error);
	EXPECT_THROW(5-Polynomial({1,2,3})+Polynomial({1,2,3}),std::logic_error);
	EXPECT_THROW(Polynomial({1,2,3})-5+Polynomial({1,2,3}),std::logic_error);
	EXPECT_THROW(Polynomial({1,2,3})-Polynomial({1,2,3})-5,std::logic_error);
	
	// Multy block

	EXPECT_THROW(5+Const(1.3)+c1*(*c),std::logic_error);
	EXPECT_THROW(Const(1.3)+c1*(*c)+5,std::logic_error);
	
	EXPECT_THROW(5/Const(1.3)/c1*(*c),std::logic_error);
	EXPECT_THROW(Const(1.3)/c1*(*c)/5,std::logic_error);
	
	EXPECT_THROW(5+Const(1.3)*c1*(*c),std::logic_error);
	EXPECT_THROW(Const(1.3)*c1*(*c)*5,std::logic_error);
	
	EXPECT_THROW(5+Const(1.3)-c1*(*c),std::logic_error);
	EXPECT_THROW(Const(1.3)-c1*(*c)-5,std::logic_error);
	
	//+,-,*,/
	
	EXPECT_THROW(5+Const(1.3),std::logic_error);
	EXPECT_THROW(5*Const(1.3),std::logic_error);
	EXPECT_THROW(5-Const(1.3),std::logic_error);
	EXPECT_THROW(5/Const(1.3),std::logic_error);

	EXPECT_THROW(Const(1.3)+5,std::logic_error);
	EXPECT_THROW(Const(1.3)-5,std::logic_error);
	EXPECT_THROW(Const(1.3)*5,std::logic_error);
	EXPECT_THROW(Const(1.3)/5,std::logic_error);

	EXPECT_THROW(5+Const(1.3)+5,std::logic_error);
	EXPECT_THROW(5*Const(1.3)-5,std::logic_error);
	EXPECT_THROW(5-Const(1.3)*5,std::logic_error);
	EXPECT_THROW(5/Const(1.3)/5,std::logic_error);
	
	// NO THROW
	
	EXPECT_NO_THROW(c1+*c);
	EXPECT_NO_THROW(*c+c1);
	EXPECT_NO_THROW(c1+Const(1.3));
	EXPECT_NO_THROW(Const(1.3)+c1);
	
	EXPECT_NO_THROW(c1 / *c);
	EXPECT_NO_THROW(*c/c1);
	EXPECT_NO_THROW(c1/Const(1.3));
	EXPECT_NO_THROW(Const(1.3)/c1);

	EXPECT_NO_THROW(c1* *c);
	EXPECT_NO_THROW(*c*c1);
	EXPECT_NO_THROW(c1*Const(1.3));
	EXPECT_NO_THROW(Const(1.3)*c1);
	
	EXPECT_NO_THROW(c1-*c);
	EXPECT_NO_THROW(*c-c1);
	EXPECT_NO_THROW(c1-Const(1.3));
	EXPECT_NO_THROW(Const(1.3)-c1);
}

TEST(values,Subtest_4)
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
	EXPECT_DOUBLE_EQ(p->value(5),36.);
	EXPECT_DOUBLE_EQ(c->value(4),1.3);
	EXPECT_DOUBLE_EQ(x->value(3),3.);
	EXPECT_DOUBLE_EQ(e->value(2),std::exp(2));
	EXPECT_DOUBLE_EQ(q->value(1),1.);
	//Native block
	Polynomial p1({1,2,3});
	Polynomial p12({-100.});
	Polynomial p13();
	Polynomial p14({});
	Const c1(1.3);
	Ident x1;
	Ident x12(1.);
	Ident x13(-100);
	Exp e1;
	Exp e12(1.);
	Exp e13(1);
	Power q1(5);
	EXPECT_DOUBLE_EQ(p1.value(0),1.);
	EXPECT_DOUBLE_EQ(c1.value(-1),1.3);
	EXPECT_DOUBLE_EQ(x1.value(0),0.);
	EXPECT_DOUBLE_EQ(e1.value(0),1.);
	EXPECT_DOUBLE_EQ(q1.value(-1),-1.);
	//General block
	auto pp = *p + p1;
	EXPECT_DOUBLE_EQ(pp.value(1),10.);
	pp = *p - p1;
	EXPECT_DOUBLE_EQ(pp.value(2),-8.);
	pp = *p * p1;
	EXPECT_DOUBLE_EQ(pp.value(-1),0.);
	Const c2(1.);
	auto ip = x1/c2;
	EXPECT_DOUBLE_EQ(ip.value(1),1.);
}
TEST(derivatives, Subtest_5)
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
	
	EXPECT_DOUBLE_EQ(p->derivative(1),4.);
	EXPECT_DOUBLE_EQ(c->derivative(2),0.);
	EXPECT_DOUBLE_EQ(x->derivative(3),1.);
	EXPECT_DOUBLE_EQ(e->derivative(4),std::exp(4.));
	EXPECT_DOUBLE_EQ(q->derivative(5),3125.);
	Polynomial p1({1,2,3});
	Const c1(1.3);
	Ident x1;
	Exp e1;
	Power q1(5);

	EXPECT_DOUBLE_EQ(p1.derivative(1),8.);
	EXPECT_DOUBLE_EQ(c1.derivative(2),0.);
	EXPECT_DOUBLE_EQ(x1.derivative(3),1.);
	EXPECT_DOUBLE_EQ(e1.derivative(4),std::exp(4.));
	EXPECT_DOUBLE_EQ(q1.derivative(5),3125.);
	//General block
	auto pp = *p + p1;
	EXPECT_DOUBLE_EQ(pp.derivative(1),12.);
	pp = *p * p1;
	EXPECT_DOUBLE_EQ(pp.derivative(1),56.);
}

TEST(Gradient,Subtest_7)
{
	Mark_Factory<std::string,Function,std::vector<double>> Factory;
	Factory.CreateTrack<Const>("const");
    Factory.CreateTrack<Ident>("ident");
    Factory.CreateTrack<Power>("power");
    Factory.CreateTrack<Polynomial>("polynomial");
    Factory.CreateTrack<Exp>("exp");
    
    auto p = Factory.gimme("polynomial",{1,2,1});
    EXPECT_NEAR(GD(*p,0.000001,100),-1.0, 0.1);
    auto p2 = Factory.gimme("polynomial",{0,2,1});
    EXPECT_NEAR(GD(*p2,0.000001,100),0.0, 0.1);
    auto p3 = Factory.gimme("polynomial",{0,0,1});
    EXPECT_NEAR(GD(*p3,0.000001,100),0.0, 0.1);
    auto p4 = Factory.gimme("polynomial",{0,1,1,1});
    EXPECT_NEAR(GD(*p4,0.00000001,100),0.0, 0.1);
    auto p5 = Factory.gimme("power",1);
    EXPECT_NEAR(GD(*p5,0.000001,100),0.0, 0.1);
}

TEST(strings,Subtest_8)
{
	Mark_Factory<std::string,Function,std::vector<double>> Factory;
	Factory.CreateTrack<Const>("const");
    Factory.CreateTrack<Ident>("ident");
    Factory.CreateTrack<Power>("power");
    Factory.CreateTrack<Polynomial>("polynomial");
    Factory.CreateTrack<Exp>("exp");

    auto p = Factory.gimme("polynomial",{1,2,1});
    auto c = Factory.gimme("const",1.3);
	auto x = Factory.gimme("ident");
	auto e = Factory.gimme("exp");
	auto q = Factory.gimme("power",5);

    EXPECT_EQ(p->ToString(), std::string("1+2x^1+1x^2"));
    EXPECT_EQ(c->ToString(), std::string("1.3"));
    EXPECT_EQ(x->ToString(), std::string("x"));
    EXPECT_EQ(e->ToString(), std::string("e^1x"));
    EXPECT_EQ(q->ToString(), std::string("x^5"));
    EXPECT_EQ((*p+*q).ToString(), std::string("Unknown info"));
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc,argv);
	
    return RUN_ALL_TESTS();
}
