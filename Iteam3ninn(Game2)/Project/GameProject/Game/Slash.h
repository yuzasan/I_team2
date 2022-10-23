#pragma once
#include "../Base/Base.h"

class Slash :public Base {
private:
	CImage m_img;
	int m_attack_no;
public:
	int t = 0;
	Slash(const CVector2D& pos, int type, int attack_no);
	void Update();
	void Draw();
	int GetAttackNo() {
		return m_attack_no;
	}
};