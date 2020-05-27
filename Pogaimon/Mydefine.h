#pragma once
#include <vector>
#include <string>

namespace MySpace {

	template <typename T>
	using Vec_2D_ = std::vector<std::vector<T>>;
	//typedef std::vector<std::vector<std::string>> Vec_2D;

	template <typename T>
	using Vec_1D_ = std::vector<T>;

	// �O��²�浲�c
	struct Coordi {
		short x;
		short y;
	};

	// �Шϥ�
	struct View {
		// �o�� View �W�١C
		std::string viewName;
		// �|�O�� �o�� View �����e�C
		Vec_2D_<char> element;
		// View ���_�l�y��
		Coordi LeftTop;
	};
}

