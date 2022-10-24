#pragma once
#include "../Base/Base.h"

class Player : public Base {
private:
	int m_attack_no;
	int m_damage_no;
public:
	enum {
		eState_Idle,
		eState_Move,
		eState_Stop,
	};
	//ó‘Ô•Ï”
	int m_state;

	CImage m_img;
	CImage m_img2;
	CImage m_img3;

	bool m_flag;

	void StateIdle();
	void StateMove();
	void StateStop();

	float m_speed;
	float m_gen;
	int drag;
	int C;
public:
	int hp;
	int m;
	Player(const CVector2D& pos, float ang, float speed, int a, bool flag);
	void Update();
	void Draw();
	void Collision(Base* b);
};