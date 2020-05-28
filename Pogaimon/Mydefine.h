#pragma once
#include <vector>
#include <string>

namespace MySpace {

	template <typename T>
	using Vec_2D_ = std::vector<std::vector<T>>;
	
	template <typename T>
	using Vec_1D_ = std::vector<T>;

	// 座標, 1-base.
	struct Coordi {
		short x;
		short y;
	};

	// 記錄著 寬跟高
	struct ViewSize {
		short w;
		short h;
	};
	
	// 某個 view 的位置資訊
	struct ViewStatus {

		// view 的起始座標。
		Coordi lefttop;

		// view 所佔有空間大小。
		ViewSize size_w_h;
	};

	struct View {
		
		// 這個 View 名稱。
		std::string viewName;

		// 記錄著 View 的內容。
		Vec_2D_<char> element;

		ViewStatus status;
	};
}

