#include "Displayer.h"
#include "rlutil.h"

Displayer::Displayer(){

}

// one-base
void Displayer::showView(MySpace::ViewPtr view, short x, short y){
	
	rlutil::locate(x, y);
	rlutil::saveDefaultColor();
	for (size_t i = 0; i < (size_t)view->element.size(); ++i) {
		for (size_t j = 0; j < (size_t)view->element.at(i).size(); ++j) {
			
			try
			{
				if (view->isASCII) {
					// �L�O ASCII �Ϥ� ���]�w�C��
				}
				else {
					// �P�_�O�_�b���, ���w���P�C��

					// (i,j) �����خɡC  ( �W�� || �U�� || 
					//                     ���� || �k�� )
					if (i == 0 || i == view->element.size() - 1 ||
						j == 0 || j == view->element.at(i).size() - 1) {
						rlutil::setColor(view->frameColor);
					}
					else {
						rlutil::setColor(view->msgColor);
					}
				}
				
				// �L�X���e
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
		throw "Undefined lefttop!"; // TODO: �n�令�� exception ����C
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
