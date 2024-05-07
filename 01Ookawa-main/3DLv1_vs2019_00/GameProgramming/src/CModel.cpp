#include "CModel.h"
#include <stdio.h>
#include "CVector.h"

int strcmp(const char* s1, const char* s2)
{
	int i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	return s1[i] - s2[i];
}

void CModel::Render()
{
	for (int i = 0; i < mTriangles.size(); i++)
	{
		mpMaterials[mTriangles[i].MaterialIdx()]->Enabled();
		mTriangles[i].Render();
		mpMaterials[mTriangles[i].MaterialIdx()]->Disabled();
	}
}

void CModel::Load(char* obj, char* mtl)
{
	FILE* fp;
	char buf[256];
	std::vector<CVector> vertex;
	std::vector<CVector> normal;
	std::vector<CVector> uv;

	fp = fopen(mtl, "r");
	if (fp == NULL)
	{
		printf("%s file open error��n", mtl);
		return;
	}
	int idx = 0;

	while (fgets(buf, sizeof(buf), fp) != NULL)
	{
		char str[4][64] = { "", "", "", "" };
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);
		if (strcmp(str[0], "newmtl") == 0)
		{
			CMaterial* pm = new CMaterial();
			pm->Name(str[1]);
			mpMaterials.push_back(pm);
			idx = mpMaterials.size() - 1;
		}
		else if (strcmp(str[0], "Kd") == 0)
		{
			mpMaterials[idx]->Diffuse()[0] = atof(str[1]);
			mpMaterials[idx]->Diffuse()[1] = atof(str[2]);
			mpMaterials[idx]->Diffuse()[2] = atof(str[3]);
		}

		else if (strcmp(str[0], "d") == 0)
		{
			mpMaterials[idx]->Diffuse()[3] = atof(str[1]);
		}

		//�擪��map_Kd�̎��A�e�N�X�`������͂���
		else if (strcmp(str[0], "map_Kd") == 0) {
			mpMaterials[idx]->Texture()->Load(str[1]);
		}
	}

	fclose(fp);

	fp = fopen(obj, "r");
	if (fp == NULL)
	{
		printf("%s file open error��n", obj);
		return;
	}

	while (fgets(buf, sizeof(buf), fp) != NULL)
	{
		char str[4][64] = { "", "", "", "" };
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);

		//�擪��v�̎��A���_�x�N�g�����쐬���Ēǉ�����
		if (strcmp(str[0], "v") == 0)
		{
			vertex.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}

		//�擪��f�̎��A�O�p�`���쐬���Ēǉ�����
		else if (strcmp(str[0], "f") == 0)
		{
			int v[3], n[3];
			//�e�N�X�`���}�b�s���O�̗L���𔻒�
			if (strstr(str[1], "//")) 
			{
				sscanf(str[1], "%d//%d", &v[0], &n[0]);
				sscanf(str[2], "%d//%d", &v[1], &n[1]);
				sscanf(str[3], "%d//%d", &v[2], &n[2]);
				CTriangle t;
				t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.Normal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				t.MaterialIdx(idx);
				mTriangles.push_back(t);
			}

			else
			{
				//�e�N�X�`���}�b�s���O�L��
				int u[3]; //�e�N�X�`���}�b�s���O�̔ԍ�
				//���_�Ɩ@���̔ԍ��擾�ƃ}�b�s���O�̔ԍ��擾
				sscanf(str[1], "%d/%d/%d", &v[0], &u[0], &n[0]);
				sscanf(str[2], "%d/%d/%d", &v[1], &u[1], &n[1]);
				sscanf(str[3], "%d/%d/%d", &v[2], &u[2], &n[2]);
				//�O�p�`�쐬
				CTriangle t;
				t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.Normal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				//�e�N�X�`���}�b�s���O�̐ݒ�
				t.UV(uv[u[0] - 1], uv[u[1] - 1], uv[u[2] - 1]);
				//�}�e���A���ԍ��̐ݒ�
				t.MaterialIdx(idx);
				//�ϒ��z��mTriangles�ɎO�p�`��ǉ�
				mTriangles.push_back(t);
			}
		}

		//�擪��vn�̎��A�@���x�N�g�����쐬���Ēǉ�����
		if (strcmp(str[0], "vn") == 0)
		{
			normal.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}

		else if (strcmp(str[0], "usemtl") == 0)
		{
			for (idx = mpMaterials.size() - 1; idx > 0; idx--)
			{
				if (strcmp(mpMaterials[idx]->Name(), str[1]) == 0)
				{
					break;
				}
			}
		}
		else if (strcmp(str[0], "vt") == 0) {
			//�ϒ��z��uv�ɒǉ�
			//atof(������)�@�����񂩂�float�^�̒l��Ԃ�
			uv.push_back(CVector(atof(str[1]), atof(str[2]), 0.0));
		}
	}
	fclose(fp);
	CreateVertexBuffer();
}

CModel::~CModel()
{
	printf("�ʉ߂P\n");
	for (int i = 0; i < mpMaterials.size(); i++)
	{
		printf("�ʉ߂Q\n");
		delete mpMaterials[i];
	}
	delete[] mpVertexes;
}

void CModel::Render(const CMatrix& m)
{
	//�s��̑ޔ�
	glPushMatrix();
	//�����s����|����
	glMultMatrixf(m.M());
	//���_���W�̈ʒu��ݒ�
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(CVertex), (void*)&mpVertexes[0].mPosition);
	//�@���x�N�g���̈ʒu��ݒ�
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(CVertex), (void*)&mpVertexes[0].mNormal);
	//�e�N�X�`���}�b�s���O�̈ʒu��ݒ�
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(CVertex), (void*)&mpVertexes[0].mTextureCoords);

	int first = 0; //�`��ʒu
	//�}�e���A�����ɕ`�悷��
	for (size_t i = 0; i < mpMaterials.size(); i++) {
		//�}�e���A����K�p����
		mpMaterials[i]->Enabled();
		//�`��ʒu����̃f�[�^�ŎO�p�`��`�悵�܂�
		glDrawArrays(GL_TRIANGLES, first, mpMaterials[i]->VertexNum());
		//�}�e���A���𖳌��ɂ���
		mpMaterials[i]->Disabled();
		//�`��ʒu���ړ�
		first += mpMaterials[i]->VertexNum();
	}
	//�s���߂�
	glPopMatrix();

	//���_���W�̔z��𖳌��ɂ���
	glDisableClientState(GL_VERTEX_ARRAY);
	//�@���̔z��𖳌��ɂ���
	glDisableClientState(GL_NORMAL_ARRAY);
	//�e�N�X�`���}�b�s���O�̔z��𖳌��ɂ���
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


void CModel::CreateVertexBuffer()
{
	mpVertexes = new CVertex[mTriangles.size() * 3];
	int idx = 0;
	for (int i = 0; i < mpMaterials.size(); i++)
	{
		for (int j = 0; j < mTriangles.size(); j++)
		{
			if (i == mTriangles[j].MaterialIdx())
			{
				mpMaterials[i]->VertexNum(mpMaterials[i]->VertexNum() + 3);
				mpVertexes[idx].mPosition = mTriangles[j].V0();
				mpVertexes[idx].mNormal = mTriangles[j].N0();
				mpVertexes[idx++].mTextureCoords = mTriangles[j].U0();
				mpVertexes[idx].mPosition = mTriangles[j].V1();
				mpVertexes[idx].mNormal = mTriangles[j].N1();
				mpVertexes[idx++].mTextureCoords = mTriangles[j].U1();
				mpVertexes[idx].mPosition = mTriangles[j].V2();
				mpVertexes[idx].mNormal = mTriangles[j].N2();
				mpVertexes[idx++].mTextureCoords = mTriangles[j].U2();
			}
		}
	}
}

