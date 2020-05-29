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
		short x = -1;
		short y = -1;
	};

	// 記錄著 寬跟高
	struct ViewSize {
		short w = -1;
		short h = -1;
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
		std::string viewName = "";

		// 記錄著 View 的內容。
		Vec_2D_<char> element;

		// 出現的位置 以及 長寬。
		ViewStatus status;

		// 設定 left top 座標(x,y)
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

