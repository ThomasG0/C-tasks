#include <gtest/gtest.h>



#include "liba.h"
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
	
    return RUN_ALL_TESTS();
}
