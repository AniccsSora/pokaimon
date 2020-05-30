#pragma once
#include <string>

// Event 父類別
class Event
{
public :
	// 給個 事件名稱
	Event(std::string eN) :eventName(eN) {};

	// 觸發此事件，由子類別實做
	virtual void touchOff();

protected:

	// 事件名稱
	std::string eventName = "Undefined Event Name.";
};

// 遭遇 Monster 事件
class EncounterMonster : public Event {
public:
	// 呼叫父類別建構
	EncounterMonster(std::string eN) : Event(eN) {
	};
	void touchOff();
private:
	; // Nothing ~~
};

