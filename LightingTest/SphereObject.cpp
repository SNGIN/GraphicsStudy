#include "SphereObject.h"


SphereObject::SphereObject()
{
}

SphereObject::SphereObject(float radius, int slices, int stacks){

	// ���_�̈ʒu�ƃe�N�X�`�����W�����߂�
	for (int k = 0, j = 0; j <= stacks; ++j)
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

			// ���_�̍��W�l
			pv[k][0] = x * radius;
			pv[k][1] = y * radius;
			pv[k][2] = z * radius;

			// ���_�̖@���x�N�g��
			nv[k][0] = x;
			nv[k][1] = y;
			nv[k][2] = z;

			// ���_�̃e�N�X�`�����W�l
			tv[k][0] = s;
			tv[k][1] = t;

			++k;
		}
	}

	//TODO:convexMesh�������Ă���Ŏ擾
	// �ʂ̎w�W�����߂�
	for (int k = 0, j = 0; j < stacks; ++j)
	{
		for (int i = 0; i < slices; ++i)
		{
			const int count((slices + 1) * j + i);

			// �㔼���̎O�p�`
			face[k][0] = count;
			face[k][1] = count + slices + 2;
			face[k][2] = count + 1;
			++k;

			// �������̎O�p�`
			face[k][0] = count;
			face[k][1] = count + slices + 1;
			face[k][2] = count + slices + 2;
			++k;
		}
	}

	m_Elements = new ShapeElements((slices + 1)*(stacks + 1), pv, nv, slices*stacks * 2, face, GL_TRIANGLE_FAN);

}


SphereObject::~SphereObject()
{
}

void SphereObject::Draw(){
	//�`��
	m_Elements->Draw();
}

GLfloat* SphereObject::GetVertices(){
	return *pv;
}

GLfloat SphereObject::GetNumvertices(){
	return VERTICES;
}

GLuint* SphereObject::GetFaces(){
	return *face;
}
GLuint SphereObject::GetNumFaces(){
	return FACES;
}