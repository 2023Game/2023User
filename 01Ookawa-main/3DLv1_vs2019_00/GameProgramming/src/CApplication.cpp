#include "CApplication.h"
#include "CRectangle.h"
#include "glut.h"
#include "CVector.h"
#include "CTriangle.h"
#include "CMatrix.h"


#define MODEL_OBJ "res\\f14.obj", "res\\f14.mtl"
//�w�i���f���f�[�^�̎w��
#define MODEL_BACKGROUND  "res\\sky.obj", "res\\sky.mtl"
//�G�A���@���f��
#define MODEL_C5 "res\\c5.obj", "res\\c5.mtl"

CVector mEye;
//�N���X��static�ϐ�
CTexture CApplication::mTexture;
CCharacterManager CApplication::mCharacterManager;

#define SOUND_BGM "res\\mario.wav" //BGM�����t�@�C��
#define SOUND_OVER "res\\mdai.wav" //�Q�[���I�[�o�[�����t�@�C��

CCharacterManager* CApplication::CharacterManager()
{
	return &mCharacterManager;
}

CTexture* CApplication::Texture()
{
	return &mTexture;
}

CTaskManager CApplication::mTaskManager;
CTaskManager* CApplication::TaskManager()
{
	return &mTaskManager;
}


void CApplication::Start()
{
	mEye = CVector(1.0f, 2.0f, 3.0f);
	//C5���f���̓ǂݍ���
	mModelC5.Load(MODEL_C5);
	mModel.Load(MODEL_OBJ);
	mBackGround.Load(MODEL_BACKGROUND);
	CMatrix matrix;
	matrix.Print();
	//mCharacter.Model(&mModel);
	//mCharacter.Scale(CVector(0.1f, 0.1f, 0.1f));

	//�G�@�̃C���X�^���X�쐬
	new CEnemy(&mModelC5, CVector(0.0f, 10.0f, -100.0f),
		CVector(), CVector(0.1f, 0.1f, 0.1f));
	new CEnemy(&mModelC5, CVector(30.0f, 10.0f, -130.0f),
		CVector(), CVector(0.1f, 0.1f, 0.1f));

	mPlayer.Model(&mModel);
	mPlayer.Scale(CVector(0.1f, 0.1f, 0.1f));
	mPlayer.Position(CVector(0.0f, 0.0f, -3.0f));
	mPlayer.Rotation(CVector(0.0f, 180.0f, 0.0f));
}

void CApplication::Update()
{
	//�^�X�N�}�l�[�W���̍X�V
	mTaskManager.Update();

	CVector v0, v1, v2, n;
	n.Set(0.0f, 1.0f, 0.0f);
	v0.Set(0.0f, 0.0f, 0.5f);
	v1.Set(1.0f, 0.0f, 0.0f);
	v2.Set(0.0f, 0.0f, -0.5f);

	if (mInput.Key('J'))
	{
		mEye = mEye - CVector(0.1f, 0.0f, 0.0f);
	}
	if (mInput.Key('L'))
	{
		mEye = mEye + CVector(0.1f, 0.0f, 0.0f);
	}
	if (mInput.Key('I'))
	{
		mEye = mEye - CVector(0.0f, 0.0f, 0.1f);
	}
	if (mInput.Key('K'))
	{
		mEye = mEye + CVector(0.0f, 0.0f, 0.1f);
	}
	if (mInput.Key('O'))
	{
		mEye = mEye + CVector(0.0f, 0.1f, 0.0f);
	}
	if (mInput.Key('M'))
	{
		mEye = mEye - CVector(0.0f, 0.1f, 0.0f);
	}

	//gluLookAt(mEye.X(), mEye.Y(), mEye.Z(), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//mCharacter.Update();
	//mCharacter.Render();

	//mPlayer.Update();
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = mPlayer.Position() + CVector(0.0f, 1.0f, -3.0f) * mPlayer.MatrixRotate();
	//�����_�����߂�
	c = mPlayer.Position();
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f) * mPlayer.MatrixRotate();
	//�J�����̐ݒ�
	gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());

	//mPlayer.Render();

	mBackGround.Render();

	
	//�^�X�N���X�g�̍폜
	mTaskManager.Delete();
	//�^�X�N�}�l�[�W���̕`��
	mTaskManager.Render();
}


