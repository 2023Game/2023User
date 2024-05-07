#ifndef CMATRIX_H
#define CMATRIX_H

class CMatrix
{
public:
	float* M() const;
	const CMatrix operator*(const CMatrix& m) const;
	void M(int row, int col, float value);
	CMatrix Translate(float mx, float my, float mz);
	CMatrix RotateX(float degree);
	CMatrix RotateZ(float degree);
	CMatrix RotateY(float degree);
	void Print();
	CMatrix();
	CMatrix Identity();
	CMatrix Scale(float sx, float sy, float sz);
	float M(int r, int c) const;
private:
	float mM[4][4];
};
#endif

