#include <vector>
#include "CTriangle.h"
#include "CMaterial.h"
#include "CVertex.h"

#ifndef CMODEL_H
#define CMODEL_H

class CModel 
{
public:
	~CModel();
	void Load(char* obj, char* mtl);
	void Render();
	void Render(const CMatrix& m);
private:
	//’¸“_‚Ì”z—ñ
	CVertex* mpVertexes;
	void CreateVertexBuffer();
	std::vector<CTriangle> mTriangles;
	std::vector<CMaterial*> mpMaterials;
};

#endif

