#pragma once
#include <vector>
#include <string>

namespace MySpace {

	template <typename T>
	using Vec_2D_ = std::vector<std::vector<T>>;
	
	template <typename T>
	using Vec_1D_ = std::vector<T>;

	// �y��, 1-base.
	struct Coordi {
		short x;
		short y;
	};

	// �O���� �e��
	struct ViewSize {
		short w;
		short h;
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
		std::string viewName;

		// �O���� View �����e�C
		Vec_2D_<char> element;

		ViewStatus status;
	};
}

