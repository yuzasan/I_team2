#pragma once
#include "../Base/Base.h"

class Gameover : public Base {
	//�摜�I�u�W�F�N�g
	CImage m_img;
	//�����\���I�u�W�F�N�g
	CFont m_title_text;
public:
	Gameover();
	~Gameover();
	void Update();
	void Draw();
};