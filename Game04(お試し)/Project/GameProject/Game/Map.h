#pragma once
#include "../Base/Base.h"
//�}�b�v�̉��̃`�b�v��
#define MAP_WIDTH	40
//�}�b�v�̏c�̃`�b�v��
#define MAP_HEIGHT	22
//�}�b�v�`�b�v�̑傫��
#define MAP_TIP_SIZE	32

class Map :public Base {
private:
	CImage m_img;
public:
	Map();
	void Draw();
	//�w����W�̃`�b�v�ԍ����擾
	int GetTip(const CVector2D& pos, int* c = NULL, int* r = NULL);
	//�w���A�w��s�̃}�b�v�`�b�v���擾
	int GetTip(int col, int raw);
	//�}�b�v�Ƃ̓����蔻��
	int CollisionMap(const CVector2D& pos, int* c = NULL, int* r = NULL);
	int CollisionMap(const CVector2D& pos, const CRect& rect);
};