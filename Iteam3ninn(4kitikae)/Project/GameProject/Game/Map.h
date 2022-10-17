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
	CImage back;
public:
	int m_k;
	Map(int a);
	void Update();
	void Draw();
	//�w����W�̃`�b�v�ԍ����擾
	int GetTip(const CVector2D& pos);
	//�w���A�w��s�̃}�b�v�`�b�v���擾
	int GetTip(int col, int raw);
	//�}�b�v�Ƃ̓����蔻��
	int CollisionMap(const CVector2D& pos);
	int CollisionMap(const CVector2D& pos, const CRect& rect);
};