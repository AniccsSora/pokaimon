#pragma once
#include <string>

// Event �����O
class Event
{
public :
	// ���� �ƥ�W��
	Event(std::string eN) :eventName(eN) {};

	// Ĳ�o���ƥ�A�Ѥl���O�갵
	virtual void touchOff();

protected:

	// �ƥ�W��
	std::string eventName = "Undefined Event Name.";
};

// �D�J Monster �ƥ�
class EncounterMonster : public Event {
public:
	// �I�s�����O�غc
	EncounterMonster(std::string eN) : Event(eN) {
	};
	void touchOff();
private:
	; // Nothing ~~
};

