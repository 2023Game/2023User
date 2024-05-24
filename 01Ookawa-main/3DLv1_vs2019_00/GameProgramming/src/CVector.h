#include "CMatrix.h"

#ifndef CVECTOR_H
#define CVECTOR_H

class CVector
{
public:
	//�x�N�g���̒�����Ԃ�
	float Length() const;
	CVector operator*(const CMatrix& m);
	CVector operator-(const CVector& v) const;
	CVector operator+(const CVector& v) const;
	CVector();
	CVector(float x, float y, float z);
	void Set(float x, float y, float z);
	float X() const;
	float Y() const;
	float Z() const;
private:
	float mX, mY, mZ;
};
#endif