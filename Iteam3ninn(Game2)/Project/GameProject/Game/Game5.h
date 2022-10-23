#pragma once

#include "../Base/Base.h"
class Player2;
class Game5 : public Base {
	CFont m_title_text;
public:
	int turn = 0;
	Player2* player[4];
	int F = 0;
	int c = 0;
	Game5();
	~Game5();
	void Update();
	void Draw();
};
