#pragma once

#include "CMatrix.h"
#include "CRect.h"
/*!
 *	@brief		AABB�N���X
 *
 *	OBB�̃p�����[�^�N���X
 */
class CAABB {
public:
	CVector3D min;
	CVector3D max;
	CAABB() {
	}
	CAABB(const CVector3D& imin, const CVector3D &imax) {
		min = imin;
		max = imax;
	}
	void Draw(const CVector4D& color);
};
/*!
 *	@brief		OBB�N���X
 *	
 *	OBB�̃p�����[�^�N���X
 */
class COBB {
public:
	CVector3D m_center;		//���S���W
	CVector3D m_axis[3];	//�e���x�N�g��
	CVector3D	 m_length;	//�e���̒���
	COBB() {
	}
	COBB(const CVector3D& center, const CVector3D& axis_x, const CVector3D& axis_y, const CVector3D& axis_z, const CVector3D& length) {
		m_center = center;
		m_axis[0] = axis_x;m_axis[1] = axis_y;m_axis[2] = axis_z;
		m_length = length;
	}
	//OBB�ɍs��𔽉f
	void Transeform(const CMatrix &mat);
	/*
		@brief	����e�X�g�pOBB�̕\��
		@retval	����
	*/
	void Draw(const CVector4D& color);
};

/*!
 *	@brief		�Փ˔���N���X
 *
 */
class CCollision {
private:
	/*!
		@brief	separate����ɓ��e����OBB���m���ڐG���Ă��邩���ׂ�
		@param	A			[in] �ՓˑΏ�OBB
		@param	B			[in] �ՓˑΏ�OBB
		@param	distVec		[in] A�̒��S����B�̒��S�܂ł̃x�N�g��
		@param	separate	[in] �������A���e���s����
		@retval	����:true�ڐG false��ڐG
	**/
	static bool CompareLength(const COBB &A,const COBB &B,const CVector3D &distVec,const CVector3D &separate,float *length=NULL);
public:
	/*!
	@brief	��`���m�̏Փ˔���
	@param	rect1		[in] �P�ڂ̋�`
	@param	rect2		[in] �Q�ڂ̋�`
	@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionRect(const CRect &rect1, const CRect &rect2);
	/*!
	@brief	��`�Ɠ_�Ƃ̏Փ˔���
	@param	rect		[in] ��`
	@param	point		[in] �_
	@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionRectPoint(const CRect &rect, const CVector2D point);
	/*!
		@brief	�����m�̏Փ˔���
		@param	centerA		[in] �P�ڂ̋��̒��S�ʒu
		@param	radiusA		[in] �P�ڂ̋��̔��a
		@param	centerB		[in] �Q�ڂ̋��̒��S�ʒu
		@param	radiusB		[in] �Q�ڂ̋��̔��a
		@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionShpere(const CVector3D &centerA,float radiusA,const CVector3D &centerB,float radiusB);
	static bool CollisionShpere(const CVector2D& centerA, float radiusA, const CVector2D& centerB, float radiusB);
	/*!
		@brief	AABB���m�̏Փ˔���
		@param	minA		[in] �P�ڂ�AABB�̍ŏ��ʒu
		@param	maxA		[in] �P�ڂ�AABB�̍ő�ʒu
		@param	minB		[in] �Q�ڂ�AABB�̍ŏ��ʒu
		@param	maxB		[in] �Q�ڂ�AABB�̍ő�ʒu
		@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionAABB(const CVector3D &minA,const CVector3D &maxA,const CVector3D &minB,const CVector3D &maxB);
	static bool CollisionAABB(const CAABB &A, const CAABB& B) {
		return CollisionAABB(A.min,A.max,B.min,B.max);
	}
	/*!
	@brief	AABB�Ɠ_�̏Փ˔���
	@param	min		[in] AABB�̍ŏ��ʒu
	@param	max		[in] AABB�̍ő�ʒu
	@param	point		[in] �_�̍��W
	@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionAABBPoint(const CVector3D &min, const CVector3D &max, const CVector3D &point);
	static bool CollisionAABBPoint(const CAABB &AABB, const CVector3D &point) {
		return CollisionAABBPoint(AABB.min, AABB.max, point);
	}

	/*!
	@brief	AABB�Ɛ��̏Փ˔���
	@param	cross	[in] �ڐG�_
	@param	length	[in] ����
	@param	min		[in] AABB�̍ŏ��ʒu
	@param	max		[in] AABB�̍ő�ʒu
	@param	point	[in] ����̓_
	@param	dir		[in] ���̕���
	@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionAABBRay(CVector3D *cross, float* length, const CVector3D& min, const CVector3D& max, const CVector3D& point, const CVector3D& dir);
	/*!
		@brief	OBB���m�̏Փ˔���
		@param	A			[in] �P�ڂ�OBB
		@param	B			[in] �Q�ڂ�OBB
		@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionOBB(const COBB &A,const COBB &B);
	/*!
	@brief	OBB�Ƌ��̏Փ˔���
	@param	A			[in] OBB
	@param	cneter		[in] ���̒��S
	@param	radius		[in] ���̔��a
	@param	axis		[in] �ڐG����
	@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionOBBShpere(const COBB &A, const CVector3D &cener, float radius, CVector3D *axis=nullptr,float *length=nullptr);

	/*!
		@brief	�J�v�Z���Ƌ��̏Փ˔���
		@param�@c_top		[in] �J�v�Z���J�n�n�_
		@param�@c_bottom	[in] �J�v�Z���I���n�_
		@param	c_radius	[in] �J�v�Z���̔��a
		@param	s_cneter	[in] ���̒��S
		@param	s_radius	[in] ���̔��a
		@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionCapsuleShpere(const CVector3D &c_top,const CVector3D &c_bottom,float c_radius,const CVector3D &s_center , float s_radius);
	static bool CollisionCapsuleShpere(const CVector2D& c_top, const CVector2D& c_bottom, float c_radius, const CVector2D& s_center, float s_radius);

	/*!
		@brief	�J�v�Z�����m�̏Փ˔���
		@param�@top1		[in] �J�v�Z���J�n�n�_
		@param�@bottom1		[in] �J�v�Z���I���n�_
		@param	radius1		[in] �J�v�Z���̔��a
		@param�@top2		[in] �J�v�Z���J�n�n�_
		@param�@bottom2		[in] �J�v�Z���I���n�_
		@param	radius2		[in] �J�v�Z���̔��a
		@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionCapsule(const CVector3D &top1,const CVector3D &bottom1,float radius1,const CVector3D &top2,const CVector3D &bottom2,float radius2);
	static bool CollisionCapsule(const CVector2D& top1, const CVector2D& bottom1, float radius1, const CVector2D& top2, const CVector2D& bottom2, float radius2);

	/*!
		@brief	�_C���O�p�`�|���S����ɂ��邩���ׂ�
		@param	C			[in] �_�̍��W
		@param	V0			[in] �O�p�`�|���S���̒��_1
		@param	V1			[in] �O�p�`�|���S���̒��_2
		@param	V2			[in] �O�p�`�|���S���̒��_3
		@param	N			[in] �O�p�`�|���S���̖@��
		@retval	����:true�ڐG false��ڐG
	**/
	static bool TriangleIntersect(const CVector3D &c,const CVector3D &v0,const  CVector3D &v1, const CVector3D &v2,const CVector3D &n);
	/*!
		@brief	�����ƎO�p�`�|���S���Ƃ̏Փ˔���
		@param	C			[out] �ڐG�n�_
		@param	S			[in] �����̊J�n�ʒu
		@param	E			[in] �����̏I���ʒu
		@param	V0			[in] �O�p�`�|���S���̒��_1
		@param	V1			[in] �O�p�`�|���S���̒��_2
		@param	V2			[in] �O�p�`�|���S���̒��_3
		@retval	����:true�ڐG false��ڐG
	**/
	static bool IntersectTriangleRay(CVector3D *corss,const CVector3D &p1,const  CVector3D &p2,const CVector3D& v0,const  CVector3D &v1,const  CVector3D &v2,float *dist);
	static bool IntersectTriangleRay(CVector3D *corss, const CVector3D &p1, const  CVector3D &p2, const CVector3D& v0, const  CVector3D &v1, const  CVector3D &v2, const  CVector3D &normal, float *dist);

	/*!
		@brief	point����߂�v0��v1����̓_�𒲂ׂ�
		@param	V0			[in] �����̊J�n�ʒu
		@param	V1			[in] �����̏I���ʒu
		@param	point		[in] �_
		@retval	����:true�ڐG false��ڐG
	**/
	static CVector3D PointOnLineSegmentNearestPoint(const CVector3D &v0,const CVector3D &v1,const CVector3D &point);
	
	/*!
		@brief	point����߂�v0��v1����̓_�𒲂ׂ�i�񎟌��p�j
		@param	V0			[in] �����̊J�n�ʒu
		@param	V1			[in] �����̏I���ʒu
		@param	point		[in] �_
		@retval	����:true�ڐG false��ڐG
	**/
	static CVector2D PointOnLineSegmentNearestPoint(const CVector2D &v0,const CVector2D &v1,const CVector2D &point);

	/*!
		@brief	�O�p�|���S���Ƌ��̏Փ˔���
		@param	V0			[in] �O�p�`�|���S���̒��_1
		@param	V1			[in] �O�p�`�|���S���̒��_2
		@param	V2			[in] �O�p�`�|���S���̒��_3
		@param	cneter		[in] ���̒��S
		@param	rudius		[in] ���̔��a
		@param	cross		[out] �ŒZ�ڐG�_
		@param	length		[out] �ŒZ����
		@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionTriangleSphere(const CVector3D &v0,const CVector3D &v1,const CVector3D &v2,const CVector3D &center,float radius,CVector3D *cross=0,float *length = 0);
	static bool CollisionTriangleSphere(const CVector3D &v0, const CVector3D &v1, const CVector3D &v2, const CVector3D &normal,const CVector3D &center, float radius, CVector3D *cross = 0, float *length = 0);

	/*!
		@brief	�O�p�|���S���ƃJ�v�Z���̏Փ˔���
		@param	V0			[in] �O�p�`�|���S���̒��_1
		@param	V1			[in] �O�p�`�|���S���̒��_2
		@param	V2			[in] �O�p�`�|���S���̒��_3
		@param	cneter		[in] ���̒��S
		@param	rudius		[in] ���̔��a
		@param	cross		[out] �ŒZ�ڐG�_
		@param	length		[out] �ŒZ����
		@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionTriangleCapsule(const CVector3D &v0,const CVector3D &v1,const CVector3D &v2,const CVector3D &top,const CVector3D &bottom,float radius,CVector3D *cross=0,float *length = 0);
	static bool CollisionTriangleCapsule(const CVector3D &v0, const CVector3D &v1, const CVector3D &v2, const CVector3D &normal,const CVector3D &top, const CVector3D &bottom, float radius, CVector3D *cross = 0, float *length = 0);


	/*!
		@brief	2�����Ԃ̋���
		@param	s1			[in] �����P�̊J�n�n�_
		@param	e1			[in] �����P�̏I���n�_
		@param	s2			[in] �����Q�̊J�n�n�_
		@param	e2			[in] �����Q�̏I���n�_
		@param	c1			[out] �����P��ł̍ŒZ�n�_�i�������j
		@param	c2			[out] �����Q��ł̍ŒZ�n�_�i�������j
		@retval	����
	**/
	static float DistanceLine(const CVector3D &s1,const CVector3D &e1,const CVector3D &s2,const CVector3D &e2,CVector3D *c1=NULL,CVector3D *c2=NULL);
	static float DistanceLine(const CVector2D& s1, const CVector2D& e1, const CVector2D& s2, const CVector2D& e2, CVector2D* c1 = NULL, CVector2D* c2 = NULL);


	/*!
	@brief	2�����Ԃ̌���
	@param	s1			[in] �����P�̊J�n�n�_
	@param	e1			[in] �����P�̏I���n�_
	@param	s2			[in] �����Q�̊J�n�n�_
	@param	e2			[in] �����Q�̏I���n�_
	@retval	����
	**/
	static bool CollitionLine(const CVector2D &s1, const CVector2D &e1, const CVector2D &s2, const CVector2D &e2);


	/*!
		@brief	�_�Ɛ��̋���
		@param	v0			[in] �����̊J�n�n�_
		@param	v1			[in] �����̏I���n�_
		@param	p			[in] �_
		@retval�@����
	**/
	static float DistancePointToLine(const CVector3D &v0,const CVector3D &v1,const CVector3D &p);
	static float DistancePointToLine(const CVector2D &v0, const CVector2D &v1, const CVector2D &p);
	/*!
		@brief	�_�Ɛ��̋����̓��
		@param	v0			[in] �����̊J�n�n�_
		@param	v1			[in] �����̏I���n�_
		@param	p			[in] �_
		@retval�@�����̓��
	**/
	static float DistancePointToLineSq(const CVector3D &v0,const CVector3D &v1,const CVector3D &p);
	static float DistancePointToLineSq(const CVector2D& v0, const CVector2D& v1, const CVector2D& p);

};