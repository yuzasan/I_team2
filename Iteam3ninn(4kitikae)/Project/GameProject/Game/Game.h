#pragma once

#include "../Base/Base.h"
class Player2;
class Game : public Base {
	CFont m_title_text;
	//int tarn = 0;
	//Player2* player[2];
public:
	int turn = 0;
	int k = 0;
	Player2* player[4];
	int F=0;
	int c = 0;
	Game();
	~Game();
	void Update();
	void Draw();
};
