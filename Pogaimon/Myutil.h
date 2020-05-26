#pragma once
#include <iostream>

namespace myutil {
	void inline helloMother(); // inline can resolve error LNK2005
}


void myutil::helloMother(){
		std::cout << "hello" << std::endl;
	
}