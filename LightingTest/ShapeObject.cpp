#include "ShapeObject.h"


ShapeObject::ShapeObject(GLuint vertNum,GLuint FaceNum,Vector3 Scale)
{
	vertPosition = new GLfloat[vertNum * 3];
	verticesNormal = new GLfloat[vertNum * 3];
	vertTex = new GLfloat[vertNum * 2];
	face = new GLuint[FaceNum * 3];

	numVert = vertNum;
	numFaces = FaceNum;

	scale = Scale;
}


ShapeObject::~ShapeObject()
{
	Common::Delete(vertPosition);
	Common::Delete(verticesNormal);
	Common::Delete(vertTex);
	Common::Delete(face);
}

void ShapeObject::MaterialSet(Material* mat){
	m_Material = mat;
}

void ShapeObject::Draw(){
	//•`‰æ
	m_Elements->Draw();
}

GLfloat* ShapeObject::GetVertices(){
	return vertPosition;
}

GLfloat ShapeObject::GetNumvertices(){
	return numVert;
}

GLuint* ShapeObject::GetFaces(){
	return face;
}
GLuint ShapeObject::GetNumFaces(){
	return numFaces;
}

Vector3 ShapeObject::GetScale(){
	return scale;
}