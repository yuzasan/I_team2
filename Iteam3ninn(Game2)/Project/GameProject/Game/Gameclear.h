#pragma once
#include "../Base/Base.h"

class Gameclear : public Base {
	//�摜�I�u�W�F�N�g
	CImage m_img;
	//�����\���I�u�W�F�N�g
	CFont m_title_text;
public:
	Gameclear();
	~Gameclear();
	void Update();
	void Draw();
};
