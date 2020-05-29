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

	// �L�X cube
	// �L�|�̷өw�q���C��ӦL�X cube�r���C�p�G x= -1, y= -1 �N�����w locate
	void inline printCube(int x,int y, char cube);

	// ���Ӥ��|�Q�{���ϥ�... �S���|�Ψ�XD
	MySpace::View inline createViewByFile(std::string filename, std::string viewName);

	// View �N�O�@�ӥ� �Y�� �Ÿ��򦨪��ϰ�A�|���� �i�L�X�y�Ц��X��A�̤j���פ䴩��h�֡C
	MySpace::View inline createView(char style,short row, short column);

}


void myutil::helloMother(){
		std::cout << "hello" << std::endl;
}

// Ū�� Map�A��show�b�׺�
GameMapPtr myutil::loadMap(std::string filename)
{
    std::string line; // �C�檺 tmp
    std::ifstream mapfile(filename);
    
    if (mapfile.is_open())
    {
        while (getline(mapfile, line))
        {
            // �B�z �@���ơC
            for (size_t i = 0; i < line.length(); i++) {
				printCube(-1, -1, line[i]); // -1 �N�����w locate
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

// ���\���a���ʨè̷� map ���޿�h����ʽd��
// void inline playerService();
// �b�ù��U��K�[ log�C one line only�C
void myutil::update_log(std::string msg)
{
    rlutil::locate(1, 32);
    cout << "\r" << std::string(40,' ')<< endl;// ��J40�� �ť�
    rlutil::locate(1, 32);
    cout << "\rlog: "<<msg << endl;
}

void myutil::printCube(int x, int y, char cube)
{
	// ���O�� �w�]���C��A���� handle �ܼƨS���Y�C
	rlutil::saveDefaultColor();

	// �w�� ���
	if (x != -1 && y != -1){ rlutil::locate(x, y); }
	
	if ('*' == cube) {// * ���,�L�k��V
		// ���
	}
	else if (';' == cube) {//; ��a, green,�i�H��V
		rlutil::setColor(rlutil::GREEN);
	}
	else if ('!' == cube) {// ! ���, brown,�L�k��V
		rlutil::setColor(rlutil::BROWN);
	}
	else if ('~' == cube) {// ~ ����, blue,�i�H��V
		rlutil::setColor(rlutil::BLUE);
	}
	/*else if (' ' == line[i]) {
		// another~~
	}*/
	else if ('#' == cube) {// # �ؿv�J�f, yellow,�i�H��V
		rlutil::setColor(rlutil::YELLOW);
	}
	cout << cube;
	rlutil::resetColor();
}

MySpace::View myutil::createViewByFile(std::string filename, std::string viewName)
{
	// ���ө� �r�� ��ơC
	MySpace::Vec_2D_<char> viewData;
	MySpace::Vec_1D_<char> singleLineTmp; // �@�檺 data tmp

	std::string line; // �C�檺 tmp
	std::ifstream viewfile(filename);

	short max_length_of_row = 0;
	if (viewfile.is_open())
	{
		while (getline(viewfile, line))
		{
			// �B�z �@���ơC
			for (size_t i = 0; i < line.length(); i++) {
				singleLineTmp.push_back(line[i]);
			}cout << "\n";
			// ��s�̤j����
			if ( (short)singleLineTmp.size() > max_length_of_row) {
				max_length_of_row = (short)singleLineTmp.size();
			}
			viewData.push_back(singleLineTmp);
			// GOTO next line
		}
		viewfile.close();
	}
	else {
		std::cout << "Unable to open file: " << "\"" << filename << "\"" << std::endl;
	}

	// ViewStatus ��Ƶ��c�C
	MySpace::ViewStatus status;
	// �{�b�ٵL�k���w �� view �� �L�X����I�C
	status.lefttop.x = -1;
	status.lefttop.y = -1;
	// view �����e
	status.size_w_h.w = max_length_of_row;
	status.size_w_h.h = (short)viewData.size();

	// �}�l�զX View ��Ƶ��c
	MySpace::View thisView;
	thisView.element = viewData;
	thisView.status = status;
	thisView.viewName = viewName;

	return thisView;
}

MySpace::View myutil::createView(char style, short rowSize, short columnSize)
{
	// �ŧi�� View �̫�^��
	MySpace::View rtnView;

	// �C�@�檺��ƼȦs, ����l�� vector ��j�p�C
	MySpace::Vec_1D_<char> rowBuffer(columnSize);

	// ���View ��DATA�A�̫�n�Q�]�h View::element. �� ��l�� vector �j�p�C
	MySpace::Vec_2D_<char> element(rowSize);

	// ��� View���c �Ѽ�
	MySpace::ViewStatus status;

	// �]�������D�L���y�� �ҥH���]�w�C
	//status.lefttop = ???;

	status.size_w_h.h = columnSize;
	status.size_w_h.w = rowSize;

	//���] rtnView
	rtnView.element = element;
	rtnView.status = status;
	


	return rtnView;
}

