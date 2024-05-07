#ifndef CMATERIAL_H
#define CMATERIAL_H
#define MATERIAL_NAME_LEN 64 

#include "CTexture.h"

class CMaterial 
{
public:
	//���_���̐ݒ�
	//VertexNum(���_��)
	void VertexNum(int num);
	//���_���̎擾
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
