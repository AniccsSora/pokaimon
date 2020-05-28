#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Mydefine.h"
#include "rlutil.h"
#include "GameMap.h"
using std::cout;
using std::endl;



namespace myutil {
	//����  // inline can resolve error LNK2005
	void inline helloMother(); 

	// Ū�� Map�A��show�b�׺ݡA ** �o�ӷ| new ���� �Ъ`�N�n DELETE **
    GameMapPtr inline loadMap(std::string filename);

    // �ШϥΪ̮ե� console�C
    void inline correctionConsole();

	// ���\���a���ʨè̷� map ���޿�h����ʽd��
	// void inline playerService();
    // �b�ù��U��K�[ log�C one line only�C
    void inline update_log(std::string msg);
}


void myutil::helloMother(){
		std::cout << "hello" << std::endl;
}

GameMapPtr myutil::loadMap(std::string filename)
{
    std::string line;
    std::ifstream mapfile(filename);
    // ���O�� �w�]���C��A���� handle �ܼƨS���Y�C
    rlutil::saveDefaultColor();
    if (mapfile.is_open())
    {
        while (getline(mapfile, line))
        {
            // �B�z �@���ơC
            for (size_t i = 0; i < line.length(); i++) {
                {
                    if ('*' == line[i]) {// * ���,�L�k��V
                        ;
                    }
                    else if (';' == line[i]) {//; ��a, green,�i�H��V
                        rlutil::setColor(rlutil::GREEN);

                    }
                    else if ('!' == line[i]) {// ! ���, brown,�L�k��V
                        rlutil::setColor(rlutil::BROWN);
                    }
                    else if ('~' == line[i]) {// ~ ����, blue,�i�H��V
                        rlutil::setColor(rlutil::BLUE);
                    }
                    /*else if (';' == line[i]) {
                        // �r��
                    }*/
                    else if ('#' == line[i]) {// # �ؿv�J�f, yellow,�i�H��V
                        rlutil::setColor(rlutil::YELLOW);
                    }
                    else {
                        //cout << "���h�l���r���|��handle" << endl;
                    }
                }
                // �W��|�M�w COLOR�C
                cout << line[i];
                rlutil::resetColor();
            }cout << "\n";
            // GOTO next line
        }
        mapfile.close();
    }
    else { 
        std::cout << "Unable to open file: " << "\"" << filename << "\"" << std::endl;
    }
    return new GameMap(filename);
}

void myutil::correctionConsole()
{
    using std::cout;
    using std::endl;
    cout << "*************************************************"\
         << "**************************************************" << endl;
    for (int i = 0; i < 31; i++) {
        cout << "*";
        for (int i = 0; i < 97; i++) {
            cout << " ";
        } cout << "*" << endl;
    }
    cout << "*************************************************"\
        << "**************************************************" << endl;

    cout << "Please make \"****\" line to be \"retangle\"." << endl;
    rlutil::anykey("\n\nPress any key to continue...\n");
    rlutil::cls();
}

void myutil::update_log(std::string msg)
{
    rlutil::locate(1, 32);
    cout << "\r" << std::string(40,' ')<< endl;// ��J40�� �ť�
    rlutil::locate(1, 32);
    cout << "\rlog: "<<msg << endl;
}

