#pragma once
#include "../Base/Base.h"

class Arrow : public Base {
	CImage m_img;
public:
	Arrow(const CVector2D& pos, float ang);
	void Update();
	void Draw();
};
