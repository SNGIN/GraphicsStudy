#include "CubeObject.h"

// サイズ1x1x1のボックス
const int box_numVertices = 8;
const int box_numIndices = 36;
const float box_vertices[] = {
	-1.000000, -1.000000, 1.000000, 1.000000, -1.000000, 1.000000, -1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000, -1.000000, 1.000000, -1.000000, 1.000000, 1.000000, -1.000000, -1.000000, -1.000000, -1.000000, 1.000000, -1.000000, -1.000000
};
const unsigned short box_indices[] = {
	0, 1, 2, 2, 1, 3, 2, 3, 4, 4, 3, 5, 4, 5, 6, 6, 5, 7, 6, 7, 0, 0, 7, 1, 1, 7, 3, 3, 7, 5, 6, 0, 4, 4, 0, 2
};

CubeObject::CubeObject()
{
}

CubeObject::CubeObject(Vector3 Cubescale,
	char* vert, char* flag, 
	GLfloat* ambColor, GLfloat* diffColor, GLfloat *specColor, GLfloat shiness
	) :ShapeObject(box_numVertices, box_numIndices, Cubescale){

	//頂点位置とインデックスの設定=============================================
	GLfloat p[box_numVertices][3];
	GLfloat n[box_numVertices][3];
	GLfloat t[box_numVertices][2];
	GLuint f[box_numIndices][3];

	for (GLuint i = 0; i<box_numVertices; i++) {
		p[i][0] = box_vertices[i * 3] * Cubescale.getX();
		p[i][1] = box_vertices[i * 3 + 1] * Cubescale.getY();
		p[i][2] = box_vertices[i * 3 + 2] * Cubescale.getZ();

		n[i][0] = box_vertices[i * 3];
		n[i][1] = box_vertices[i * 3 + 1];
		n[i][2] = box_vertices[i * 3 + 2];
	}

	for (GLuint i = 0; i<box_numVertices*3; i++){
		switch (i % 3)
		{
		case 0:
			vertPosition[i] = box_vertices[i] * Cubescale.getX();
			break;
		case 1:
			vertPosition[i] = box_vertices[i] * Cubescale.getY();
			break;
		case 2:
			vertPosition[i] = box_vertices[i] * Cubescale.getZ();
			break;
		}
		verticesNormal[i] = box_vertices[i];
	}

	for (GLuint i = 0; i<box_numIndices; i++) {
		f[i][0] = box_indices[i * 3];
		f[i][1] = box_indices[i * 3 + 1];
		f[i][2] = box_indices[i * 3 + 2];
	}

	for (GLuint i = 0; i<box_numIndices*3; i++){
		face[i] = box_indices[i];
	}

	m_Elements = new ShapeElements(box_numVertices, p, n, box_numIndices, f, GL_TRIANGLES);

	//====================================================================

	//使用するシェーダーの用意
	Shader* tile = new Shader(vert, flag);
	Material* mat = new Material(tile, ambColor , diffColor, specColor, &shiness);

	//マテリアルの設定(どのシェーダーを使うか)
	MaterialSet(mat);
}