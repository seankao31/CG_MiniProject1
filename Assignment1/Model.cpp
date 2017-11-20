#include <iostream>
#include "Model.h"
#include "TextureManager.h"

using namespace std;

Model::Model()
{
	for (size_t i = 0; i < 4; ++i)
	{
		additional_translate[i] = 0;
	}
}

Model::~Model()
{
}

void Model::Reset()
{
	for (size_t i = 0; i < 4; ++i)
	{
		additional_translate[i] = 0;
	}
}

void Model::Render()
{
	int lastMaterial = -1;
	for (size_t i = 0; i < object->fTotal; ++i)
	{
		// set material property if this face used different material
		if (lastMaterial != object->faceList[i].m)
		{
			lastMaterial = (int)object->faceList[i].m;
			ApplyMaterial(lastMaterial);
		}

		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();
		TRStransform();
		ApplyTexture();
		DrawFace(i);
		glPopMatrix();
		DisapplyTexture();
	}
}

void Model::ApplyMaterial(int material)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, object->mList[material].Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, object->mList[material].Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, object->mList[material].Ks);
	glMaterialfv(GL_FRONT, GL_SHININESS, &object->mList[material].Ns);

	//you can obtain the texture name by object->mList[material].map_Kd
	//load them once in the main function before mainloop
	//bind them in display function here
}

void Model::TRStransform()
{
	glTranslatef(additional_translate[0], additional_translate[1], additional_translate[2]);
	glTranslatef(translate[0], translate[1], translate[2]);
	glRotatef(rotate[0], rotate[1], rotate[2], rotate[3]);
	glScalef(scale[0], scale[1], scale[2]);
}

void Model::ApplyTexture()
{
	TextureManager& tm = TextureManager::GetInstance();
	tm.textures[texture_index]->ApplyTexture();
}

void Model::DisapplyTexture()
{
	TextureManager& tm = TextureManager::GetInstance();
	tm.textures[texture_index]->DisapplyTexture();
}

void Model::DrawFace(int face)
{
	TextureManager& tm = TextureManager::GetInstance();
	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i<3; ++i)
	{
		float *point = object->tList[object->faceList[face][i].t].ptr;
		tm.textures[texture_index]->SetTexCoord(point);
		glTexCoord2f(point[0], point[1]);
		glNormal3fv(object->nList[object->faceList[face][i].n].ptr);
		glVertex3fv(object->vList[object->faceList[face][i].v].ptr);
	}
	glEnd();
}