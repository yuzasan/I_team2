#pragma once

#include "../Base/Base.h"
class Player2;
class Game2 : public Base {
	CFont m_title_text;
public:
	int turn = 0;
	Player2* player[4];
	int F = 0;
	Game2();
	~Game2();
	void Update();
	void Draw();
};
