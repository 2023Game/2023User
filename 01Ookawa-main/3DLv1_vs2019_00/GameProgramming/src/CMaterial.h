#ifndef CMATERIAL_H
#define CMATERIAL_H
#define MATERIAL_NAME_LEN 64 

#include "CTexture.h"

class CMaterial 
{
public:
	//’¸“_”‚Ìİ’è
	//VertexNum(’¸“_”)
	void VertexNum(int num);
	//’¸“_”‚Ìæ“¾
	int VertexNum();
	CTexture* Texture();
	void Disabled();
	CMaterial();
	void Enabled();
	char* Name();
	void Name(char* name);
	float* Diffuse();
private:
	int mVertexNum;
	CTexture mTexture;
	char mName[MATERIAL_NAME_LEN + 1];
	float mDiffuse[4];
};

#endif
