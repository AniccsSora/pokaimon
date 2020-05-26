#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "rlutil.h"

namespace myutil {
	//����  // inline can resolve error LNK2005
	void inline helloMother(); 
	// Ū�� Map�A��show�b�׺�
	void inline loadMap(std::string filename);
    // �ШϥΪ̮ե� console�C
    void inline correctionConsole();
}


void myutil::helloMother(){
		std::cout << "hello" << std::endl;
}

void myutil::loadMap(std::string filename)
{
    std::string line;
    std::ifstream mapfile(filename);
    if (mapfile.is_open())
    {
        while (getline(mapfile, line))
        {
            std::cout << line << '\n';
        }
        mapfile.close();
    }
    else { 
        std::cout << "Unable to open file: " << "\"" << filename << "\"" << std::endl;
    }

}

void myutil::correctionConsole()
{
    using std::cout;
    using std::endl;
    cout << "*************************************************"\
         << "**************************************************" << endl;
    for (int i = 0; i < 32; i++) {
        cout << "*";
        for (int i = 0; i < 96; i++) {
            cout << " ";
        } cout << "*" << endl;

    }

    cout << "Please make this line to \"ONE\" row." << endl;
    rlutil::anykey("\n\nPress any key to continue...\n");
    rlutil::cls();
}

