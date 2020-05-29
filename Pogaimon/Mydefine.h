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

	

	// �y��, 1-base.
	struct Coordi {
		short x = -1;
		short y = -1;
	};

	// �O���� �e��
	struct ViewSize {
		short w = -1;
		short h = -1;
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
		
	};
	inline void View::setLeftTop(short x, short y) {
		status.lefttop.x = x; status.lefttop.y = y;
	}

	inline void View::setLeftTop(Coordi c){
		status.lefttop = c;
	}
	
}

