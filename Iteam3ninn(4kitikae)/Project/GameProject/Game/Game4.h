#pragma once

#include "../Base/Base.h"
class Player2;
class Game4 : public Base {
	CFont m_title_text;
public:
	int turn = 0;
	Player2* player[4];
	int F = 0;
	int c = 0;
	Game4();
	~Game4();
	void Update();
	void Draw();
};
