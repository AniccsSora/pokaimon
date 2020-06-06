#include "Displayer.h"
#include "rlutil.h"

Displayer::Displayer(){

}

// one-base
void Displayer::showView(MySpace::ViewPtr view, short x, short y){
	//格式為: "{row}:{rlutil number}
	std::vector<std::string> flg = view->color_flg;

	rlutil::locate(x, y);
	rlutil::saveDefaultColor();
	for (size_t i = 0; i < (size_t)view->element.size(); ++i) {
		for (size_t j = 0; j < (size_t)view->element.at(i).size(); ++j) {
			
			try
			{
				if (view->isASCII) {
					// 他是 ASCII 圖片 不設定顏色
				}
				else {
					// 判斷是否在邊框, 給定不同顏色

					// (i,j) 位於邊框時。  ( 上邊 || 下邊 || 
					//                     左邊 || 右邊 )
					if (i == 0 || i == view->element.size() - 1 ||
						j == 0 || j == view->element.at(i).size() - 1) {
						rlutil::setColor(view->frameColor);
					}
					else if ( flg.size() ) { // View::color_flg 取得 是否要 印 特殊顏色
						for (auto f : flg) {// 走訪 "{row}:{rlutil number};" 字串旗標
							
							int row_int = -1;//第幾行
							int rlutil_cnumber = -1;//色彩代號

							int split_1 = f.find(':'); // 尋找{row}: 的 冒號位置
							int split_2 = f.find(';'); // 尋找{rlutil number}; 的 分號位置

							// {row 字串 轉 int
							row_int = std::atoi(f.substr(0, split_1).c_str());
							// {rlutil number}字串 轉 int
							rlutil_cnumber = std::atoi(f.substr(split_1+1, split_2-split_1-1).c_str());


							if ( i == row_int){ // 比對 ( 列 && 旗標的 {row}
								rlutil::setColor(rlutil_cnumber);
								break; //不然他會跳到別的  "{row}:{rlutil number};" 反而走去 else 又設回原本顏色。
							}
							else {
								rlutil::setColor(view->msgColor);
							}
						}
					}
					else {
						rlutil::setColor(view->msgColor);
					}
				}
				
				// 印出內容
				std::cout << view->element.at(i).at(j);
			}
			catch (std::out_of_range & oor) {
				std::cout << "out_of_range : (" << i << ", " << j << ")...";
				rlutil::anykey("\n");
			}
			catch (std::exception & e) {
				std::cout << "Other exception happen in Displayer::showView()...";
				rlutil::anykey("\n");
			}
		}
		rlutil::locate(x, ++y);
	}
	rlutil::resetColor();
}

void Displayer::showView(MySpace::ViewPtr view)
{
	if (view->status.lefttop.x < 0 ||
		view->status.lefttop.y < 0) {
		throw "Undefined lefttop!"; // TODO: 要改成丟 exception 物件。
	}
	
	showView(view, view->status.lefttop.x, view->status.lefttop.y);
}

void Displayer::showRegisteredView()
{
	for (size_t i = 0; i < viewList.size(); ++i) {
		showView(viewList[i]);
	}
}

void Displayer::registerView(MySpace::ViewPtr view)
{
	if (view->status.lefttop.x < 0 ||
		view->status.lefttop.y < 0) {
		throw "Undefined lefttop!";
	}// TODO : 要設計 "你忘記給 View 左上角了" 的 exception

	viewList.push_back(view);
}

void Displayer::clearALLview()
{
	this->viewList.clear();
}
