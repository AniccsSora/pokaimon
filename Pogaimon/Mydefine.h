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

	// View 使用的例外
	struct ViewOutOfRangeException : public std::exception {
		std::string s;
		ViewOutOfRangeException(std::string ss) : s(ss) {}
		~ViewOutOfRangeException() throw() {}
		const char* what() const throw() { return s.c_str(); }
	};

	// 座標, 1-base.
	struct Coordi {
		short x = -1;
		short y = -1;
	};

	// 記錄著 寬跟高
	struct ViewSize {

		// 1-base
		short w = -1; short h = -1;
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
		std::string viewName = "好像沒洨用了...";

		// 記錄著 View 的內容。
		Vec_2D_<char> element;

		// 出現的位置 以及 長寬。 1-base。
		ViewStatus status;

		// 是 ASCII image ??
		bool isASCII = false;

		// 邊框顏色;
		rlutil_Color frameColor= rlutil::WHITE;

		// 字體顏色
		rlutil_Color msgColor = rlutil::WHITE;

		// set frameColor
		void setframeColor(rlutil_Color tarC) { frameColor = tarC;}

		// zero-base
		char getCube(short x, short y) {
			std::cout << "element size:" << element.size() << std::endl;;
			return element.at(y).at(x);
		}

		// 設定 left top 座標(x,y)
		inline void setLeftTop(short x, short y);
		inline void setLeftTop(Coordi c);

		// 在此 view 的 第 pos 行 插入 msg。(不會印在 console)
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

		// 檢查 要 print 的位置 及大小 在 此 view 的容許範圍。
		try{
			if (msg.size() > status.size_w_h.w - 2) {// -2, 去除左右邊框後，剩下的空白大小。
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
			rlutil::anykey("Exception happened!!\n");
		}

		//short target_x = status.lefttop.x + 1; // view 的 左上角 +1
		//short target_y = status.lefttop.y + pos;// log 真正在 console 的高度。

		// 覆寫該 view, 第 pos 行的所有字元如果超出 msg 則補 ' '。
		for (size_t view_col_idx = 0; view_col_idx < status.size_w_h.w-2; ++view_col_idx) {
			if ( (int)msg.size()-1 >= view_col_idx ) {
				// (i + 1): 因為有左邊邊框; (i - 1):msg是 0-base.
				element.at(pos).at(view_col_idx + 1) = msg.at(view_col_idx);
			}
			else {  // .at(pos) 0-base, 跟多出的 上框剛好 計數抵銷 (-1 + 1) = 0。
				element.at(pos).at(view_col_idx + 1) = ' ';
			} 
		}

		// 最大可印區域。-2:去頭尾, -1: 1-base(status) to 0-base(.at()).
		//short max_can_printIdx_of_view_col = status.size_w_h.w -2 -1;
		//for (size_t msg_idx = 0; msg_idx <= msg.size(); ++msg_idx) {// i = 1, 因為 最左邊邊框不希望變空; -2 同理。
		//	if ( msg_idx < view_col_idx) {
		//		// (i + 1): 跟左邊邊框多一格(好看用); (i - 1):msg是 0-base.
		//		element.at(pos).at(view_col_idx + 1) = msg.at(view_col_idx - 1);
		//	}
		//	else {  // .at(pos) 0-base, 跟多出的 上框剛好 計數抵銷 (-1 + 1) = 0。
		//		element.at(pos).at(view_col_idx + 1) = ' ';
		//	}
		//}
	}
	
}

