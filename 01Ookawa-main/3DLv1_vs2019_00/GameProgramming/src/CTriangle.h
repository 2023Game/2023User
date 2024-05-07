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
	//頂点座標を得る
	const CVector& V0() const; //mV[0]を返します
	const CVector& V1() const; //mV[1]を返します
	const CVector& V2() const; //mV[2]を返します
	//法線を得る
	const CVector& N0() const; //mN[0]を返します
	const CVector& N1() const; //mN[1]を返します
	const CVector& N2() const; //mN[2]を返します
	//UVを得る
	const CVector& U0() const; //mUv[0]を返します
	const CVector& U1() const; //mUv[1]を返します
	const CVector& U2() const; //mUv[2]を返します
private:
	CVector mUv[3]; //テクスチャマッピング
	CVector mV[3];
	CVector mN[3];
	int mMaterialIdx;
};
#endif