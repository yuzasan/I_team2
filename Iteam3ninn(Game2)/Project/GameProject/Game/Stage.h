#pragma once

#include "../Base/Base.h"

class Stage : public Base {
	CFont m_title_text;
public:
	Stage();
	~Stage();
	void Update();
	void Draw();
};
