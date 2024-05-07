#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CVector.h"

class CTriangle
{
public:
	void UV(const CVector& v0, const CVector& v1, const CVector& v2);
	int MaterialIdx();
	void MaterialIdx(int idx);
	void Vertex(const CVector& v0, const CVector& v1, const CVector& v2);
	void Normal(const CVector& n);
	void Normal(const CVector& v0, const CVector& v1, const CVector& v2);
	void Render();
	void Render(const CMatrix& m);
	//���_���W�𓾂�
	const CVector& V0() const; //mV[0]��Ԃ��܂�
	const CVector& V1() const; //mV[1]��Ԃ��܂�
	const CVector& V2() const; //mV[2]��Ԃ��܂�
	//�@���𓾂�
	const CVector& N0() const; //mN[0]��Ԃ��܂�
	const CVector& N1() const; //mN[1]��Ԃ��܂�
	const CVector& N2() const; //mN[2]��Ԃ��܂�
	//UV�𓾂�
	const CVector& U0() const; //mUv[0]��Ԃ��܂�
	const CVector& U1() const; //mUv[1]��Ԃ��܂�
	const CVector& U2() const; //mUv[2]��Ԃ��܂�
private:
	CVector mUv[3]; //�e�N�X�`���}�b�s���O
	CVector mV[3];
	CVector mN[3];
	int mMaterialIdx;
};
#endif