/*!
*	@brief	X�t�@�C���i�X�L�����b�V�����f���j�p���f���N���X
*
*
**/
#pragma once

#include "GL.h"

#include "CXModelLoader.h"
#include "CTexture.h"
#include "CShader.h"


#include "Vertex.h"
#include "CModel.h"

class CXMesh;
/*
���f���̊K�w�\���p�N���X
CXFrame���X�L�����b�V���p�ɔh��
*/
class CFrameBone : public CXFrame {
private:
	CMatrix boneMatrix;
	CMatrix sMatrix;
	CMatrix lMatrix;
	CMatrix matrixOffset;
	CMatrix blendMatrix;
	CXMesh	*pMesh;
	CMatrix bindMatrix;
	int		m_anim_layer;
	bool	m_bind;
	CModel* root;
public:
	CFrameBone() :CXFrame(), pMesh(nullptr){
		m_anim_layer = 0;
	}
	CFrameBone(CXFrame &f):pMesh(nullptr) {
		SetNo(f.GetNo());
		SetMatrix(f.GetMatrix());
		SetType(f.GetType());
		copyToken(f.GetToken());
		copyName(f.GetName());
		m_anim_layer = 0;
	}
	CFrameBone(CFrameBone &f, CFrameBone *parent, CFrameBone *prev,CModel* root);
	CMatrix GetSMatrix() {
		return sMatrix;

	}
	CMatrix GetLMatrix() {
		return lMatrix;

	}
	void SetAnimLayer(int layer) {
		m_anim_layer = layer;
	}
	void saveBlendMatrix() {
		blendMatrix = matrix;
	}
	void calcBlendMatrix(float r) {
		matrix = matrix * r + blendMatrix * (1 - r);
	}
	void calcBoneMatrix(CMatrix *out);
	void calcMatrix();
	CMatrix GetMatrixOffset() {
		return matrixOffset;
	}
	void seMatrixOffset(CMatrix mat) {
		matrixOffset = mat;
	}

	friend class CModelX;
	friend class CXAnimation;
	friend class CModelA3M;
};
/*
�A�j���[�V�����Ǘ��N���X
�ǂݍ��񂾃A�j���[�V�����\�������̂܂܎g�p
*/
class CXAnimation {

private:
	std::vector<CXAnimationSet*> *pAnimation;
	float time;
	int jam;
	float speed;
	bool loop;
	int endTime;
	CFrameBone *pBoneRoot;
	float blend;
	float blendS;
	float FPS;
	SAnimData *pAnimData;
private:
	CMatrix calcMatrix(CXAnimationKey &key, float t);
public:
	int m_anim_layer;
	CXAnimation();
	CXAnimation(std::vector<CXAnimationSet*> &a);
	~CXAnimation();
	void Release();
	int GetEndTime(int j);
	void changeAnimation(int j, bool l = true, bool check = true, float time = 0,int blendFrame = 0);
	void upDate();
	void updateMatrix();
	void saveBlendMatrix();
	bool isEnd() {
		if (time >= endTime - 1.0f) return true;
		return false;
	}
	int GetJam() {
		return jam;
	}
	int GetLoop() {
		return loop;
	}
	void SetSpeed(float s) {
		speed = s;
	}
	float GetAnimationFrame() {
		return time;
	}
	void attachFrame(CFrameBone *bone) {
		pBoneRoot = bone;
	}
	void attachAnimData(SAnimData* p) {
		pAnimData = p;
	}

	int GetAnimationSize() { return pAnimation->size(); }

	char* GetAnimationName(int jam) { return (*pAnimation)[jam]->GetName(); }
	friend class CModelX;
	friend class CModelA3M;
};
/*
�}�e���A���N���X
*/
class CMaterialX : public CMaterial {

public:
	CMaterialX(CXMaterial &m, char *path);
	CMaterialX(const CMaterialX& mesh);
};
struct SSkinWeight {
	SXVector4 bone;
	SXVector4 weight;
};


/*
�e���_�ɐݒ肳�ꂽ�E�F�C�g�l�𒸓_���ɂ܂Ƃ߂�N���X
*/
class CSkinWeights {
public:
	SSkinWeight * weight;
public:
	CSkinWeights(CXModelLoader &loader, CXLMesh &mesh);
	~CSkinWeights();
};
/*
�|���S���N���X
�}�e���A�����ɂ܂Ƃ߂�
*/
class CXPoly {
public:
	MY_VERTEX * m_pVertex;
	int			vertexCnt;
	int			faceCnt;
	bool		bNormal;
	bool		bTexCode;
	bool		bWeight;
	int			material;
	GLuint		buffer;
	GLuint		vao;
public:
	/*
	���[�_�[����|���S���f�[�^���\�z
	*/
	CXPoly(CXModelLoader &loader, CXLMesh &mesh, CSkinWeights *bone, int matNo);
	~CXPoly();
	/*
	�`��
	*/
	void draw(CShader *shader);

	bool CollisionRay(CVector3D *c, CVector3D *n, const CVector3D &s, const CVector3D &e, float *pLength);
	int CollisionSphere(CCollTriangle *out, const CVector3D &center, float radius);
	int CollisionCupsel(CCollTriangle *out, const CVector3D &top, const CVector3D &bottom, float radius);

};
/*
���b�V�����̃{�[���I�t�Z�b�g�s����i�[
*/
class CBoneOffset {
public:
	char transformNodeName[64];
	CMatrix matrixOffset;
	CBoneOffset() {
	}
	/*
	SkinWeights����{�[�����ƃ}�g���b�N�X�݂̂��i�[
	*/
	CBoneOffset(CXSkinWeights &s) {
		strcpy_s(transformNodeName, sizeof(transformNodeName), s.transformNodeName);
		matrixOffset = s.matrixOffset;
	}

};
/*
���b�V���N���X
*/
class CXMesh {
private:
	std::vector<CXPoly*> polyList;
	std::vector<CBoneOffset*> boneList;
	CMatrix matrix;
	bool visibility;
public:
	/*
	���[�_�[���烁�b�V���f�[�^���\�z
	*/
	CXMesh(CXModelLoader &loader, CXLMesh &mesh, CSkinWeights *bone);
	CXMesh(const CXMesh& mesh);
	~CXMesh();
	CXMesh operator = (const CXMesh &m);
	void Release();
	/*
	�`��
	*/
	void draw(std::vector<CMaterialX*> &materialList, CShader *shader, CFrameBone *pFrameRoot, CMatrix *boneMatrix, int boneNum);

	void SetVisibility(bool f) { visibility = f; }
	bool CollisionRay(CVector3D *c, CVector3D *n, const CVector3D &s, const CVector3D &e, float *pLength);
	int CollisionSphere(CCollTriangle *out, const CVector3D &center, float radius);
	int CollisionCupsel(CCollTriangle *out, const CVector3D &top, const CVector3D &bottom, float radius);
	friend class CModelX;
	friend class CXMesh;
	friend class CModelA3M;

};

/*
���t�@�C���p���f���N���X
*/
class CModelX : public CModel {
public:
	std::vector<CXMesh*> *pMeshList;
	std::vector<CMaterialX*> *pMaterialList;
	CFrameBone *pFrameRoot;
	int			boneNum;
	CMatrix *boneMatrix;
	CXAnimation *animation;
	void createFrame(CXFrame *xf, CFrameBone *f, int *num);
	void createMesh(CFrameBone *f, CXModelLoader &loader);
	void createMeshList(CFrameBone *f);
	void drawMesh(CFrameBone *f, const CMatrix& m, const CMatrix& view_matrix);
	void outputFrameInfo(FILE* fp, CXFrame *f, int depth);
public:
	CModelX();
	~CModelX();
	CModelX(const CModelX &m);
	void operator = (const CModelX &m);
	void Release();
	/*
	���[�_�[���烂�f�����\�z
	*/
	bool Load(CXModelLoader &loader);
	/*
	�t�@�C�����烂�f�����\�z
	*/
	bool Load(const char* filePath);
	/*
	�A�j���[�V�������X�V
	*/
	void UpdateAnimation();
	/*!
		@brief	���W�A��]�l�A�X�P�[���l���烏�[���h�s����쐬����
		@retval	����
	**/
	void UpdateMatrix();


	/*!
		@brief	�w��̍s��Ŋe�{�[�����X�V����
		@retval	����
	**/
	void UpdateMatrix(CMatrix& m);


	/*
	�A�j���[�V�����̏I���𔻒�
	*/
	bool isAnimationEnd(int layer);
	bool isAnimationEnd();
	/*
	�A�j���[�V�����̎�ނ��擾
	*/
	int GetAnimationJam(int layer = 0);
	/*
	�A�j���[�V�������[�v�t���O���擾
	*/
	int GetAnimatioLoop(int layer = 0);
	/*
	�@�A�j���[�V�������x�̕ύX
	 */
	void SetAnimationSpeed(int layer, float s);
	void SetAnimationSpeed(float s);
	/*!
	@brief	�A�j���[�V�����̌��݃t���[�����擾
	@retval	�t���[��
	**/
	float GetAnimationFrame(int layer) {
		return 	animation[layer].GetAnimationFrame();
	}
	float GetAnimationFrame() {
		return 	animation[0].GetAnimationFrame();
	}
	/*
	@brief	�A�j���[�V�������擾
	@retval	�A�j���[�V������
	**/
	int GetAnimationSize(int layer) const { return animation ? animation[layer].GetAnimationSize():0; }

	int GetAnimationSize() const { return animation ? animation[0].GetAnimationSize() : 0; }

	char* GetAnimationName(int layer, int jam) const { return animation ? animation[layer].GetAnimationName(jam):nullptr; }

	char* GetAnimationName(int jam) const { return animation ? animation[0].GetAnimationName(jam):nullptr; }

	/*
	�A�j���[�V������؂�ւ���
	*/
	void ChangeAnimation(int jam, bool loop = true, bool check = true, float time = 0, int blendFrame = 5);
	void ChangeAnimation(int layer, int jam, bool loop = true, bool check = true, float time = 0, int blendFrame = 0);
	void SetAnimation(int layer_dst, int layer_src);
	void attachAnimData(int layer, SAnimData* p);
	void attachAnimData(SAnimData* p);

	/*!
	@brief	�{�[�����w��̕����֌�����
	@param	no			[in] �{�[���ԍ�
	@param	mat			[in] ��]�s��
	**/
	void BindFrameMatrix(int no, const CMatrix& mat);
	/*!
	@brief	�{�[�����w��̕����֌�����
	@param	no			[in] �{�[�����O
	@param	mat			[in] ��]�s��
	**/
	void BindFrameMatrix(const char* name, const CMatrix& mat);

	/*!
	@brief	�{�[���̎w������ւ̌Œ������
	@param	no			[in] �{�[���ԍ�
	**/
	void UnbindFrameMatrix(int no);
	/*!
	@brief	�{�[���̎w������ւ̌Œ������
	@param	no			[in] �{�[�����O
	**/
	void UnbindFrameMatrix(const char* name);
	/*
	�`��
	*/
	void Render(CMatrix &m);

	void Render();
	/*
	�@�{�[���̍s����擾
	 */
	CMatrix GetFrameMatrix(const char *name, bool local = false);
	/*
	�@�{�[���̍s����擾
	 */
	CMatrix GetFrameMatrix(int no, bool local = false);


	/*
	�@���b�V�����擾
	 */
	CXMesh *GetMesh(const char *name);
	CXMesh *GetMesh(int no);



	/*
	�@�{�[���擾
	 */
	CFrameBone* GetFrameBone(const char *name)const ;
	CFrameBone* GetFrameBone(int no)const;


	/*!
	@brief	�}�e���A���̎擾
	@param	no				[in] �}�e���A���ԍ�
	@retval	�}�e���A���̃|�C���^
	**/
	CMaterial *GetMaterial(int no);


	/*!
	@brief	�}�e���A�����̎擾
	@param	no				[in] �}�e���A���ԍ�
	@retval	�}�e���A���̃|�C���^
	**/
	int GetMaterialSize() const {
		return pMaterialList->size();
	}
	/*!
	@brief	�����ƃ��f���̔���
	@param	c				[out] �ڐG�n�_
	@param	s				[in] �����̊J�n�n�_
	@param	e				[in] �����̏I���n�_
	@retval	true:�ڐG�@false:��ڐG
	**/
	bool CollisionRay(CVector3D *c, CVector3D *n, const CVector3D &s, const CVector3D &e) const;


	/*!
	@brief	���ƃ��f���̔���
	@param	out				[out] �ڐG�f�[�^
	@param	center			[in] ���̒��S
	@param	radius			[in] ���̔��a
	@retval	�ڐG�|���S����
	**/
	int CollisionSphere(CCollTriangle *out, const CVector3D &center, float radius, int maxcnt = 1) const;


	/*!
	@brief	�J�v�Z���ƃ��f���̔���
	@param	out				[out] �ڐG�f�[�^
	@param	top				[in] �J�v�Z���̓V��
	@param	bottom			[in] �J�v�Z���̒�
	@param	radius			[in] ���̔��a
	@retval	�ڐG�|���S����
	**/
	int CollisionCupsel(CCollTriangle *out, const CVector3D &top, const CVector3D &bottom, float radius, int maxcnt = 1) const;


	/*!
	@brief	�{�[���̊K�w�\�����t�@�C���֏o�͂���
	@param	file_name		[in] �������ݐ�
	@retval	�ڐG�|���S����
	**/
	void OutputFrameInfo(const char *file_name);

	friend class CModelX;
	friend class CModelA3M;
};