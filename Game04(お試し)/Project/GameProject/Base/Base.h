#pragma once
#include <GLLibrary.h>
enum {
	eType_Field,
	eType_Player,
	eType_Enemy,
	eType_Player_Bullet,
	eType_Enemy_Bullet,
	eType_Goal,
	eType_Effect,
	eType_UI,
	eType_Scene,
};

//�d�͉����x
#define GRAVITY (9.8f/20)

class Base {
public:
	//�I�u�W�F�N�g�̎��
	int m_type;
	//���W
	CVector2D m_pos;
	//�ړ��O�̍��W
	CVector2D m_pos_old;
	//�ړ��x�N�g��
	CVector2D m_vec;
	//��]�l
	float m_ang;
	//���a
	float m_rad;	
	//��`
	CRect m_rect;
	//�q�b�gID
	int	m_hit_id;
	//�폜�t���O
	bool m_kill;
	//�X�N���[���l
	static CVector2D m_scroll;

	//�I�u�W�F�N�g���X�g
	static std::list<Base*> m_list;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="type">�I�u�W�F�N�g�̎��</param>
	/// <returns></returns>
	Base(int type);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <returns></returns>
	virtual ~Base();


	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update();


	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// �폜�t���OON
	/// </summary>
	void SetKill() {
		m_kill = true;
	}
	/// <summary>
	/// �����蔻�茟��
	/// </summary>
	/// <param name="b">����ΏۃI�u�W�F�N�g</param>
	virtual void Collision(Base* b);

	/// <summary>
	/// �S�ẴI�u�W�F�N�g�̍X�V
	/// </summary>
	static void UpdateAll();

	/// <summary>
	/// �S�ẴI�u�W�F�N�g�̕`��
	/// </summary>
	static void DrawAll();

	/// <summary>
	/// �S�ẴI�u�W�F�N�g�̏Փ˃`�F�b�N
	/// </summary>
	static void CollisionAll();

	/// <summary>
	/// �S�ẴI�u�W�F�N�g�̍폜�`�F�b�N
	/// </summary>
	static void CheckKillAll();

	/// <summary>
	/// �S�ẴI�u�W�F�N�g���폜
	/// </summary>
	static void KillAll();

	/// <summary>
	/// �I�u�W�F�N�g�̒ǉ�
	/// </summary>
	/// <param name="b">�ǉ�����I�u�W�F�N�g</param>
	static void Add(Base* b);

	/// <summary>
	/// �~���m�̔���
	/// </summary>
	/// <param name="b1">����I�u�W�F�N�g�P</param>
	/// <param name="b2">����I�u�W�F�N�g�Q</param>
	/// <returns>true:�ڐG</returns>
	static bool CollisionCircle(Base* b1, Base* b2);

	/// <summary>
	/// ��`���m�̔���
	/// </summary>
	/// <param name="b1">����I�u�W�F�N�g�P</param>
	/// <param name="b2">����I�u�W�F�N�g�Q</param>
	/// <returns>true:�ڐG</returns>
	static bool CollisionRect(Base* b1, Base* b2);


	/// <summary>
	/// ��`�̕\��
	/// </summary>
	void DrawRect();



	/// <summary>
	/// �I�u�W�F�N�g�̌���
	/// </summary>
	/// <param name="type">��������I�u�W�F�N�g�̎��</param>
	/// <returns>��ԏ��߂Ɍ������I�u�W�F�N�g�ւ̃|�C���^</returns>
	static Base* FindObject(int type);

	/// <summary>
	/// �I�u�W�F�N�g�̌���
	/// </summary>
	/// <param name="type">��������I�u�W�F�N�g�̎��</param>
	/// <returns>�������I�u�W�F�N�g�̃��X�g</returns>
	static std::list<Base*> FindObjects(int type);


	/// <summary>
	/// �X�N���[���l�𔽉f������ʏ�ł̈ʒu���擾
	/// </summary>
	/// <param name="pos">���[���h���W</param>
	/// <returns>�X�N���[�����W</returns>
	static CVector2D GetScreenPos(const CVector2D& pos);
};

