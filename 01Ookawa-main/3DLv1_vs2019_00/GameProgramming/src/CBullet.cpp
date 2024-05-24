#include "CBullet.h"

//���Ɖ��s���̐ݒ�
//Set(��, ���s)
void CBullet::Set(float w, float d) 
{
	//�X�P�[���ݒ�
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//�O�p�`�̒��_�ݒ聨�q���g 3
	mT.Vertex(CVector(w, 0.0f, 0.0f), CVector(0.0f, 0.0f, -d), CVector(-w, 0.0f, 0.0f));
	//�O�p�`�̖@���ݒ�
	mT.Normal(CVector(0.0f, 1.0f, 0.0f));
}

//�X�V
void CBullet::Update()
{
	//�������Ԃ̔���
	if (mLife-- > 0) {
		CTransform::Update();
		//�ʒu�X�V
		mPosition = mPosition + CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;;
	}
	else {
		//�����ɂ���
		mEnabled = false;
	}
}

//�`��
void CBullet::Render() 
{
	//DIFFUSE���F�ݒ�
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//�O�p�`�`��
	mT.Render(mMatrix);
	//mCollider1.Render();
}

CBullet::CBullet()
	: mLife(50)
	, mCollider1(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.1f)
{}

//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CBullet::Collision(CCollider* m, CCollider* o)
{
	//�R���C�_��m��o���Փ˂��Ă��邩����
	if (CCollider::Collision(m, o))
	{
		//�Փ˂��Ă��鎞�͖����ɂ���
		mEnabled = false;
	}
}
