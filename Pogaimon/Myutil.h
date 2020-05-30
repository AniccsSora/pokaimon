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
	// row �i�H�g�X��r�C
	// column �@��i�H�g�h�֦r�C
	// default color : �աC
	MySpace::ViewPtr inline createView(char style,short row, short column);

	// �b�׺ݾ� �L�X �ؼ� �U�� �����t�m
	void inline screen_ruler();
}


void myutil::helloMother(){
		std::cout << "hello" << std::endl;
}

// Ū�� Map�C���|�L�X Map�C
GameMapPtr myutil::loadMap(std::string filename)
{
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

// �b�ù��U��K�[ log�C one line only�C FOR DEBUG
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


MySpace::ViewPtr myutil::createView(char style, short rowSize, short columnSize)
{
	// �ŧi�� View �̫�^��
	MySpace::ViewPtr rtnView = new MySpace::View();

	// View �O�|�Q�h "��"�@��C �ҥH�n�U�[�W2�C hard code�C�g��
	rowSize += 2;
	columnSize += 2;
	
	// ���View ��DATA�A�̫�n�Q�]�h View::element. �� ��l�� vector �j�p�C
	MySpace::Vec_2D_<char> element(rowSize);

	for (size_t i=0; i < rowSize; ++i) {
		//rowBuffer.clear();
		for (size_t j=0; j < columnSize; ++j) {
			if (i == 0 || i == rowSize-1) {// "�y"�X���(�W && �U)�C
				element.at(i).push_back(style);
				continue;
			}
			if (j == 0 || j == columnSize-1) {
				element.at(i).push_back(style);
				continue;
			}
			// ��l�P�w�� content area(�N��i�H��J �ۤv���n��ƪ������C)
			element.at(i).push_back(' ');
			continue;
		}// One row data complete.
	}

	// ��� View���c (�Ѽƥ]�q)�C
	MySpace::ViewStatus status;

	// �]�������D�L���y�� �ҥH���]�w�C
	//status.lefttop = ???;

	// View ���骺 ��x�e (�`�N: �� �i�H���L msg ���ϰ�j�p���P)
	status.size_w_h.h = rowSize;
	status.size_w_h.w = columnSize;

	//���] rtnView
	rtnView->element = element;
	rtnView->status = status;
	
	return rtnView;
}

void myutil::screen_ruler()
{
	int MAX_ROW = 40;
	int MAX_COL = 150;
	for (size_t row_idx = 0; row_idx < MAX_ROW; ++row_idx) {
		for (size_t col_idx = 0; col_idx < MAX_COL; ++col_idx) {
			if (row_idx == 0 || row_idx == MAX_ROW-1 ) { // first row
				std::cout << (col_idx + 1) % 10; // �u�L�X �Ʀr...
				continue;
			}
			else { // not first row
				if (col_idx == 0) { // first item of row, but not first row.
					std::cout << (row_idx + 1) % 10; // �C�檺�Ĥ@�Ӥ���, �]�u�L�Ʀr�C
					continue;
				}
				else { // not first item of row
					if (col_idx % 10 == 9) { // �L�X �������j�u�C
						std::cout << '|'; continue;
					}
					else {
						if (row_idx % 10 == 9) { // �L�X �������j�u�C
							std::cout << '-'; continue;
						}
						else {
							std::cout << ' '; continue;
						}
					}
				}
			}
		}
		cout << endl;
	}
}

