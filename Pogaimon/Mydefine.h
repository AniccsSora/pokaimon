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

		Coordi() = default;
		Coordi(const Coordi& c) {
			if (this != &c) {
				this->x = c.x;
				this->y = c.y;
			}
		}
	};

	// 記錄著 寬跟高
	struct ViewSize {

		// 1-base
		short w = -1; short h = -1;
		ViewSize() = default;
		ViewSize(const ViewSize& v) {
			if (this != &v) {
				this->w = v.w;
				this->h = v.h;
			}
		}
	};
	
	// 某個 view 的位置資訊
	struct ViewStatus {

		// view 的起始座標。
		Coordi lefttop;

		// view 所佔有空間大小。
		ViewSize size_w_h;

		ViewStatus() = default;
		ViewStatus(const ViewStatus& s) {
			this->lefttop = Coordi(s.lefttop);
			this->size_w_h = ViewSize(s.size_w_h);
		}
	};

	struct View {
		View() = default;
		View(const View&); // copy constructor

		// 這個 View 名稱。
		std::string viewName = "好像沒洨用了...";

		// 記錄著 View 的內容。
		Vec_2D_<char> element;
		// 格式為 : "{row}:{rlutil number};", 紀錄{row}行的 顏色({rlutil number})，有呼叫 print_c() 才會在紀錄在此。
		Vec_1D_<std::string> color_flg;

		// 出現的位置 以及 長寬。 1-base。
		ViewStatus status;

		// 是 ASCII image ??
		bool isASCII = false;

		// 邊框顏色;
		rlutil_Color frameColor= rlutil::WHITE;

		// 字體顏色
		rlutil_Color msgColor = rlutil::WHITE;

		// 邊框字體
		char frameSymbol = '*';

		// 可以寫字的區間，最大可寫寬度 與 最大可寫行數。
		int rowSize = -1;
		int columnSize = -1;

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

		// 在此 view 的 第 pos 行 插入 msg且該行會有特別顏色。(不會印在 console)
		inline void print_c(short pos, std::string msg,int c);

		// 設定 View Name
		inline void setViewName(std::string name);

		inline std::string getViewName();

	}; typedef View*  ViewPtr;

	inline View::View(const View& src) // copy constructor
	{
		if (this != &src) { //防護自我參考
			this->element = Vec_2D_<char>(src.element);
			this->frameColor = src.frameColor;
			this->isASCII = src.isASCII;
			this->status = *(new ViewStatus(src.status));
			this->msgColor = src.msgColor;
		}
	}

	inline void View::setLeftTop(short x, short y) {
		status.lefttop.x = x; status.lefttop.y = y;
	}

	inline void View::setLeftTop(Coordi c){
		status.lefttop = c;
	}

	inline void View::print(short pos, std::string msg){
		// 根本沒有要插入東西的話 就直接返回
		if (msg.size() <= 0) { return; }

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

		// 覆寫該 view, 第 pos 行的所有字元如果超出 msg 則補 ' '。
		for (size_t view_col_idx = 0; view_col_idx < status.size_w_h.w-2; ++view_col_idx) {
			try
			{
				if ((int)msg.size() - 1 >= view_col_idx) {
					// (i + 1): 因為有左邊邊框; (i - 1):msg是 0-base.
					element.at(pos).at(view_col_idx + 1) = msg.at(view_col_idx);
				}
				else {  // .at(pos) 0-base, 跟多出的 上框剛好 計數抵銷 (-1 + 1) = 0。
					element.at(pos).at(view_col_idx + 1) = ' ';
				}
			}
			catch (std::out_of_range& oor) {
				std::cout << "\nout_of_range, what(): \"" << oor.what() <<"\", " 
					<< "view_col_idx=" << std::to_string(view_col_idx) << ", "
					<< "pos="<< std::to_string(pos) << ", " 
					<< "msg.size()=" << std::to_string(msg.size()) << ", "
					<< "element.szie()=" << std::to_string(element.size())  << std::endl;
				throw std::exception();//中斷時要跳到這邊用的
			}
			catch (std::exception& e) {
				std::cout << "\nexception, what(): \"" << e.what() << "\", "
					<< "view_col_idx=" << std::to_string(view_col_idx) << ", "
					<< "pos=" << std::to_string(pos) << ", "
					<< "msg.size()=" << std::to_string(msg.size()) << ", "
					<< "element.szie()=" << std::to_string(element.size()) << std::endl;
				throw std::exception();//中斷時要跳到這邊用的
			}

		}
	}

	inline void View::print_c(short pos, std::string msg, int c){
		short max_idx = status.size_w_h.h - 2;

		//"{row}:{rlutil number};"
		View::color_flg.push_back( std::to_string(pos)+":"+std::to_string(c)+";");

		// 檢查 要 print 的位置 及大小 在 此 view 的容許範圍。
		try {
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

		// 覆寫該 view, 第 pos 行的所有字元如果超出 msg 則補 ' '。
		for (size_t view_col_idx = 0; view_col_idx < status.size_w_h.w - 2; ++view_col_idx) {
			if ((int)msg.size() - 1 >= view_col_idx) {
				// (i + 1): 因為有左邊邊框; (i - 1):msg是 0-base.
				element.at(pos).at(view_col_idx + 1) = msg.at(view_col_idx);
			}
			else {  // .at(pos) 0-base, 跟多出的 上框剛好 計數抵銷 (-1 + 1) = 0。
				element.at(pos).at(view_col_idx + 1) = ' ';
			}
		}
	}

	inline void View::setViewName(std::string name)
	{
		this->viewName = name;
	}

	inline std::string View::getViewName()
	{
		return this->viewName;
	}


}

