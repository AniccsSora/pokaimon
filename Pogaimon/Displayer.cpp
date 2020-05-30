#include "Displayer.h"
#include "rlutil.h"

Displayer::Displayer(){

}

// one-base
void Displayer::showView(MySpace::ViewPtr view, short x, short y){

	rlutil::locate(x, y);
	rlutil::saveDefaultColor();
	//rlutil::setColor(view->frameColor);
	for (size_t i = 0; i < (size_t)view->element.size(); ++i) {
		for (size_t j = 0; j < (size_t)view->element.at(i).size(); ++j) {
			
			try
			{
				// 判斷是否在邊框, 給定不同顏色

				// (i,j) 不位於邊框時。  ( 上邊 || 下邊 || 
				//                       左邊 || 右邊 )
				/*if (i != 0 || i != view->element.size() - 1 ||
					j != 0 || j != view->element.at(i).size()-1) {
					rlutil::setColor(view->msgColor);
				}
				else {
					rlutil::setColor(view->frameColor);
				}*/
				
				// 印出內容
				std::cout << view->element.at(i).at(j);
			}
			catch (std::out_of_range & oor) {
				std::cout << "out_of_range : (" << i << ", " << j << ")...";
			}
			catch (std::exception & e) {
				std::cout << "Other exception of Displayer::showView()...";
			}
		}
		std::cout << "\n";
		rlutil::locate(x, ++y);
	}
	rlutil::resetColor();
}

void Displayer::showView(MySpace::ViewPtr view)
{
	if (view->status.lefttop.x < 0 ||
		view->status.lefttop.y < 0) {
		throw "Undefined lefttop!";
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
	}

	viewList.push_back(view);
}
