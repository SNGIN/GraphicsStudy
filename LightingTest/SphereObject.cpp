#include "SphereObject.h"

const GLuint sphere_numVertices = 12;
const GLuint sphere_numIndices = 60;
const GLfloat sphere_vertices[] = {
	0.267617, -0.500000, -0.823639, -0.700629, -0.500000, -0.509037, -0.700629, -0.500000, 0.509037, 0.267617, -0.500000, 0.823639, 0.866025, -0.500000, 0.000000, 0.267617, 0.500000, -0.823639, -0.700629, 0.500000, -0.509037, -0.700629, 0.500000, 0.509037, 0.267617, 0.500000, 0.823639, 0.866025, 0.500000, 0.000000, 0.000000, -1.000000, 0.000000, 0.000000, 1.000000, 0.000000
};
const GLuint sphere_indices[] = {
	0, 1, 5, 5, 1, 6, 1, 2, 6, 6, 2, 7, 2, 3, 7, 7, 3, 8, 3, 4, 8, 8, 4, 9, 4, 0, 9, 9, 0, 5, 1, 0, 10, 2, 1, 10, 3, 2, 10, 4, 3, 10, 0, 4, 10, 5, 6, 11, 6, 7, 11, 7, 8, 11, 8, 9, 11, 9, 5, 11
};

SphereObject::SphereObject()
{
}

SphereObject::SphereObject(Vector3 radius, int slices, int stacks) :ShapeObject(sphere_numVertices, sphere_numIndices,radius){

	GLfloat p[sphere_numVertices][3];
	GLfloat n[sphere_numVertices][3];
	GLfloat t[sphere_numVertices][2];
	GLuint f[sphere_numIndices][3];

	// 頂点の位置とテクスチャ座標を求める
	/*for (int k = 0, j = 0; j <= stacks; ++j)
	{
		const float t(static_cast<float>(j) / static_cast<float>(stacks));
		const float ph(3.141593f * t);
		const float y(cos(ph));
		const float r(sin(ph));

		for (int i = 0; i <= slices; ++i)
		{
			const float s(static_cast<float>(i) / static_cast<float>(slices));
			const float th(2.0f * 3.141593f * s);
			const float x(r * cos(th));
			const float z(r * sin(th));

			// 頂点の座標値
			pv[k][0] = x * radius;
			pv[k][1] = y * radius;
			pv[k][2] = z * radius;

			// 頂点の法線ベクトル
			nv[k][0] = x;
			nv[k][1] = y;
			nv[k][2] = z;

			// 頂点のテクスチャ座標値
			tv[k][0] = s;
			tv[k][1] = t;

			++k;
		}
	}

	//TODO:convexMeshが持ってる情報で取得
	// 面の指標を求める
	for (int k = 0, j = 0; j < stacks; ++j)
	{
		for (int i = 0; i < slices; ++i)
		{
			const int count((slices + 1) * j + i);

			// 上半分の三角形
			face[k][0] = count;
			face[k][1] = count + slices + 2;
			face[k][2] = count + 1;
			++k;

			// 下半分の三角形
			face[k][0] = count;
			face[k][1] = count + slices + 1;
			face[k][2] = count + slices + 2;
			++k;
		}
	}*/

	for (GLuint i = 0; i<sphere_numVertices; i++) {
		p[i][0] = sphere_vertices[i * 3] * radius.getX();
		p[i][1] = sphere_vertices[i * 3 + 1] * radius.getY();
		p[i][2] = sphere_vertices[i * 3 + 2] * radius.getZ();

		n[i][0] = sphere_vertices[i * 3];
		n[i][1] = sphere_vertices[i * 3 + 1];
		n[i][2] = sphere_vertices[i * 3 + 2];
	}

	for (GLuint i = 0; i<sphere_numVertices*3; i++){
		switch (i % 3)
		{
		case 0:
			vertPosition[i] = sphere_vertices[i] * radius.getX();
			break;
		case 1:
			vertPosition[i] = sphere_vertices[i] * radius.getY();
			break;
		case 2:
			vertPosition[i] = sphere_vertices[i] * radius.getZ();
			break;
		}
		verticesNormal[i] = sphere_vertices[i];
	}

	for (GLuint i = 0; i<sphere_numIndices; i++) {
		f[i][0] = sphere_indices[i * 3];
		f[i][1] = sphere_indices[i * 3 + 1];
		f[i][2] = sphere_indices[i * 3 + 2];
	}

	for (GLuint i = 0; i<sphere_numIndices*3; i++){
		face[i] = sphere_indices[i];
	}

	m_Elements = new ShapeElements(sphere_numVertices, p, n, sphere_numIndices, f, GL_TRIANGLES);
}


SphereObject::~SphereObject()
{
}