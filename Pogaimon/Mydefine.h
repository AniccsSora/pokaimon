#pragma once
#include <vector>
#include <string>

namespace MySpace {

	template <typename T>
	using Vec_2D_ = std::vector<std::vector<T>>;
	//typedef std::vector<std::vector<std::string>> Vec_2D;

	template <typename T>
	using Vec_1D_ = std::vector<T>;

	// 保持簡單結構
	struct Coordi {
		short x;
		short y;
	};

	// 請使用
	struct View {
		// 這個 View 名稱。
		std::string viewName;
		// 會記錄 這個 View 的內容。
		Vec_2D_<char> element;
		// View 的起始座標
		Coordi LeftTop;
	};
}

