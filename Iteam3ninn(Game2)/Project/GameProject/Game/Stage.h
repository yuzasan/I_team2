#pragma once

#include "../Base/Base.h"
class Player;
class Stage : public Base {
	CFont m_title_text;
public:
	int turn = 0;
	int k = 0;
	Player* player[4];
	int F = 0;
	int c = 0;
	Stage();
	~Stage();
	void Update();
	void Draw();
};
