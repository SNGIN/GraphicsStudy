#include "CubeObject.h"


CubeObject::CubeObject()
{
}

CubeObject::CubeObject(Vector3 scale){

	for (GLuint i = 0; i<box_numVertices; i++) {
		pv[i][0] = box_vertices[i * 3] * scale.getX();
		pv[i][1] = box_vertices[i * 3 + 1] * scale.getY();
		pv[i][2] = box_vertices[i * 3 + 2] * scale.getZ();
	}

	for (GLuint i = 0; i<box_numIndices; i++) {
		face[i][0] = box_indices[i * 3];
		face[i][1] = box_indices[i * 3 + 1];
		face[i][2] = box_indices[i * 3 + 2];
	}

	m_Elements = new ShapeElements(box_numVertices, pv, pv, box_numIndices, face, GL_TRIANGLES);

}


CubeObject::~CubeObject()
{
}

void CubeObject::Draw(){
	//•`‰æ
	m_Elements->Draw();
}

GLfloat* CubeObject::GetVertices(){
	return *pv;
}

GLfloat CubeObject::GetNumvertices(){
	return box_numVertices;
}

GLuint* CubeObject::GetFaces(){
	return *face;
}
GLuint CubeObject::GetNumFaces(){
	return box_numIndices;
}