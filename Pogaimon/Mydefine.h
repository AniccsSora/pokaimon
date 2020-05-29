#pragma once
#include <vector>
#include <string>
#include "rlutil.h"
#define rlutil_Color int

namespace MySpace {

	template <typename T>
	using Vec_2D_ = std::vector<std::vector<T>>;
	
	template <typename T>
	using Vec_1D_ = std::vector<T>;

	// View �ϥΪ��ҥ~
	struct ViewOutOfRangeException : public std::exception {
		std::string s;
		ViewOutOfRangeException(std::string ss) : s(ss) {}
		~ViewOutOfRangeException() throw() {}
		const char* what() const throw() { return s.c_str(); }
	};


	// �y��, 1-base.
	struct Coordi {
		short x = -1;
		short y = -1;
	};

	// �O���� �e��
	struct ViewSize {

		// 1-base
		short w = -1; short h = -1;
	};
	
	// �Y�� view ����m��T
	struct ViewStatus {

		// view ���_�l�y�СC
		Coordi lefttop;

		// view �Ҧ����Ŷ��j�p�C
		ViewSize size_w_h;
	};

	struct View {
		
		// �o�� View �W�١C
		std::string viewName = "�n���S�m�ΤF...";

		// �O���� View �����e�C
		Vec_2D_<char> element;

		// �X�{����m �H�� ���e�C 1-base�C
		ViewStatus status;

		// ����C��;
		rlutil_Color frameColor= rlutil::WHITE;

		// set frameColor
		void setframeColor(rlutil_Color tarC) { frameColor = tarC;}

		// zero-base
		char getCube(short x, short y) {
			std::cout << "element size:" << element.size() << std::endl;;
			return element.at(y).at(x);
		}

		// �]�w left top �y��(x,y)
		inline void setLeftTop(short x, short y);
		inline void setLeftTop(Coordi c);

		// �b�� view �� �� pos �� ���J msg�C(���|�L�b console)
		inline void print(short pos, std::string msg);
		
	}; typedef View*  ViewPtr;

inline void View::setLeftTop(short x, short y) {
		status.lefttop.x = x; status.lefttop.y = y;
	}

	inline void View::setLeftTop(Coordi c){
		status.lefttop = c;
	}

	inline void View::print(short pos, std::string msg){

		short max_idx = status.size_w_h.h - 2;

		// �ˬd �n print ����m �Τj�p �b �� view ���e�\�d��C
		try{
			if (msg.size() > status.size_w_h.w - 4) { 
				std::string errMsg = " Max of massage legth = " + std::to_string(status.size_w_h.w - 4) + 
					", but your length = " + std::to_string(msg.size());
				throw ViewOutOfRangeException(errMsg); 
			}
			if (pos > max_idx) { 
				std::string errMsg = "Max of idx=" + std::to_string(max_idx) + ", but your idx = " + 
					std::to_string(pos);
				throw ViewOutOfRangeException(errMsg);
			}
		}
		catch (ViewOutOfRangeException& caught) {
			std::cout << caught.what() << std::endl;
		}

		short target_x = status.lefttop.x + 1; // view �� ���W�� +1
		short target_y = status.lefttop.y + pos;// log �u���b console �����סC

		// �� erase �� view, �� pos �檺�Ҧ��r���C
		for (size_t i = 1; i < status.size_w_h.w-2; ++i) {// i = 1, �]�� �̥�����ؤ��Ʊ��ܪ�; -2 �P�z�C
			if (msg.size() >= i) { 
				// (i + 1): ������ئh�@��(�n�ݥ�); (i - 1):msg�O 0-base.
				element.at(pos).at(i + 1) = msg.at(i - 1); 
			}
			else {  // .at(pos) 0-base, ��h�X�� �W�ح�n �p�Ʃ�P (-1 + 1) = 0�C
				element.at(pos).at(i) = ' '; 
			} 
		}
	}
	
}

