#pragma once
#include "PhysicsInclude.h"
#include "Physics.h"

void Physics::GetClosestTwoSegments(const Vector3 &segmentPointA0, const Vector3 &segmentPointA1,
	const Vector3 &segmentPointB0, const Vector3 &segmentPointB1,
	Vector3 &closestPointA, Vector3 &closestPointB)
{
	Vector3 v1 = segmentPointA1 - segmentPointA0;
	Vector3 v2 = segmentPointB1 - segmentPointB0;
	Vector3 r = segmentPointA0 - segmentPointB0;

	float a = dot(v1, v1);
	float b = dot(v1, v2);
	float c = dot(v2, v2);
	float d = dot(v1, r);
	float e = dot(v2, r);
	float det = -a*c + b*b;
	float s = 0.0f, t = 0.0f;

	// �t�s��̑��݂��`�F�b�N
	if (det*det > EPSILON) {
		s = (c*d - b*e) / det;
	}

	// ����A��̍ŋߐړ_�����߂�p�����[�^s��0.0�`1.0�ŃN�����v
	s = CLAMP(s, 0.0f, 1.0f);

	// ����B��t�����߂�
	//t = dot((segmentPointA0+s*v1) - segmentPointB0,v2) / dot(v2,v2);
	t = (e + s*b) / c;

	// ����B��̍ŋߐړ_�����߂�p�����[�^t��0.0�`1.0�ŃN�����v
	t = CLAMP(t, 0.0f, 1.0f);

	// �ēx�A����A��̓_�����߂�
	//s = dot((segmentPointB0+t*v2) - segmentPointA0,v1) / dot(v1,v1);
	s = (-d + t*b) / a;
	s = CLAMP(s, 0.0f, 1.0f);

	closestPointA = segmentPointA0 + s * v1;
	closestPointB = segmentPointB0 + t * v2;
}

inline
void GetClosestPointLine(const Vector3 &point,const Vector3 &linePoint,const Vector3 &lineDirection,Vector3 &closestPoint)
{
	float s = dot(point - linePoint, lineDirection) / dot(lineDirection, lineDirection);
	closestPoint = linePoint + s * lineDirection;
}

void Physics::GetClosestPointTriangle(const Vector3 &point,
	const Vector3 &trianglePoint0,	const Vector3 &trianglePoint1,const Vector3 &trianglePoint2,
	const Vector3 &triangleNormal,Vector3 &closestPoint)
{
	// �R�p�`�ʏ�̓��e�_
	Vector3 proj = point - dot(triangleNormal, point - trianglePoint0) * triangleNormal;

	// �G�b�WP0,P1�̃{���m�C�̈�
	Vector3 edgeP01 = trianglePoint1 - trianglePoint0;
	Vector3 edgeP01_normal = cross(edgeP01, triangleNormal);

	float voronoiEdgeP01_check1 = dot(proj - trianglePoint0, edgeP01_normal);
	float voronoiEdgeP01_check2 = dot(proj - trianglePoint0, edgeP01);
	float voronoiEdgeP01_check3 = dot(proj - trianglePoint1, -edgeP01);

	if (voronoiEdgeP01_check1 > 0.0f && voronoiEdgeP01_check2 > 0.0f && voronoiEdgeP01_check3 > 0.0f) {
		GetClosestPointLine(trianglePoint0, edgeP01, proj, closestPoint);
		return;
	}

	// �G�b�WP1,P2�̃{���m�C�̈�
	Vector3 edgeP12 = trianglePoint2 - trianglePoint1;
	Vector3 edgeP12_normal = cross(edgeP12, triangleNormal);

	float voronoiEdgeP12_check1 = dot(proj - trianglePoint1, edgeP12_normal);
	float voronoiEdgeP12_check2 = dot(proj - trianglePoint1, edgeP12);
	float voronoiEdgeP12_check3 = dot(proj - trianglePoint2, -edgeP12);

	if (voronoiEdgeP12_check1 > 0.0f && voronoiEdgeP12_check2 > 0.0f && voronoiEdgeP12_check3 > 0.0f) {
		GetClosestPointLine(trianglePoint1, edgeP12, proj, closestPoint);
		return;
	}

	// �G�b�WP2,P0�̃{���m�C�̈�
	Vector3 edgeP20 = trianglePoint0 - trianglePoint2;
	Vector3 edgeP20_normal = cross(edgeP20, triangleNormal);

	float voronoiEdgeP20_check1 = dot(proj - trianglePoint2, edgeP20_normal);
	float voronoiEdgeP20_check2 = dot(proj - trianglePoint2, edgeP20);
	float voronoiEdgeP20_check3 = dot(proj - trianglePoint0, -edgeP20);

	if (voronoiEdgeP20_check1 > 0.0f && voronoiEdgeP20_check2 > 0.0f && voronoiEdgeP20_check3 > 0.0f) {
		GetClosestPointLine(trianglePoint2, edgeP20, proj, closestPoint);
		return;
	}

	// �R�p�`�ʂ̓���
	if (voronoiEdgeP01_check1 <= 0.0f && voronoiEdgeP12_check1 <= 0.0f && voronoiEdgeP20_check1 <= 0.0f) {
		closestPoint = proj;
		return;
	}

	// ���_P0�̃{���m�C�̈�
	if (voronoiEdgeP01_check2 <= 0.0f && voronoiEdgeP20_check3 <= 0.0f) {
		closestPoint = trianglePoint0;
		return;
	}

	// ���_P1�̃{���m�C�̈�
	if (voronoiEdgeP01_check3 <= 0.0f && voronoiEdgeP12_check2 <= 0.0f) {
		closestPoint = trianglePoint1;
		return;
	}

	// ���_P2�̃{���m�C�̈�
	if (voronoiEdgeP20_check2 <= 0.0f && voronoiEdgeP12_check3 <= 0.0f) {
		closestPoint = trianglePoint2;
		return;
	}
}
