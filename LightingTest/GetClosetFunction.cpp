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

	// 逆行列の存在をチェック
	if (det*det > EPSILON) {
		s = (c*d - b*e) / det;
	}

	// 線分A上の最近接点を決めるパラメータsを0.0～1.0でクランプ
	s = CLAMP(s, 0.0f, 1.0f);

	// 線分Bのtを求める
	//t = dot((segmentPointA0+s*v1) - segmentPointB0,v2) / dot(v2,v2);
	t = (e + s*b) / c;

	// 線分B上の最近接点を決めるパラメータtを0.0～1.0でクランプ
	t = CLAMP(t, 0.0f, 1.0f);

	// 再度、線分A上の点を求める
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
	// ３角形面上の投影点
	Vector3 proj = point - dot(triangleNormal, point - trianglePoint0) * triangleNormal;

	// エッジP0,P1のボロノイ領域
	Vector3 edgeP01 = trianglePoint1 - trianglePoint0;
	Vector3 edgeP01_normal = cross(edgeP01, triangleNormal);

	float voronoiEdgeP01_check1 = dot(proj - trianglePoint0, edgeP01_normal);
	float voronoiEdgeP01_check2 = dot(proj - trianglePoint0, edgeP01);
	float voronoiEdgeP01_check3 = dot(proj - trianglePoint1, -edgeP01);

	if (voronoiEdgeP01_check1 > 0.0f && voronoiEdgeP01_check2 > 0.0f && voronoiEdgeP01_check3 > 0.0f) {
		GetClosestPointLine(trianglePoint0, edgeP01, proj, closestPoint);
		return;
	}

	// エッジP1,P2のボロノイ領域
	Vector3 edgeP12 = trianglePoint2 - trianglePoint1;
	Vector3 edgeP12_normal = cross(edgeP12, triangleNormal);

	float voronoiEdgeP12_check1 = dot(proj - trianglePoint1, edgeP12_normal);
	float voronoiEdgeP12_check2 = dot(proj - trianglePoint1, edgeP12);
	float voronoiEdgeP12_check3 = dot(proj - trianglePoint2, -edgeP12);

	if (voronoiEdgeP12_check1 > 0.0f && voronoiEdgeP12_check2 > 0.0f && voronoiEdgeP12_check3 > 0.0f) {
		GetClosestPointLine(trianglePoint1, edgeP12, proj, closestPoint);
		return;
	}

	// エッジP2,P0のボロノイ領域
	Vector3 edgeP20 = trianglePoint0 - trianglePoint2;
	Vector3 edgeP20_normal = cross(edgeP20, triangleNormal);

	float voronoiEdgeP20_check1 = dot(proj - trianglePoint2, edgeP20_normal);
	float voronoiEdgeP20_check2 = dot(proj - trianglePoint2, edgeP20);
	float voronoiEdgeP20_check3 = dot(proj - trianglePoint0, -edgeP20);

	if (voronoiEdgeP20_check1 > 0.0f && voronoiEdgeP20_check2 > 0.0f && voronoiEdgeP20_check3 > 0.0f) {
		GetClosestPointLine(trianglePoint2, edgeP20, proj, closestPoint);
		return;
	}

	// ３角形面の内側
	if (voronoiEdgeP01_check1 <= 0.0f && voronoiEdgeP12_check1 <= 0.0f && voronoiEdgeP20_check1 <= 0.0f) {
		closestPoint = proj;
		return;
	}

	// 頂点P0のボロノイ領域
	if (voronoiEdgeP01_check2 <= 0.0f && voronoiEdgeP20_check3 <= 0.0f) {
		closestPoint = trianglePoint0;
		return;
	}

	// 頂点P1のボロノイ領域
	if (voronoiEdgeP01_check3 <= 0.0f && voronoiEdgeP12_check2 <= 0.0f) {
		closestPoint = trianglePoint1;
		return;
	}

	// 頂点P2のボロノイ領域
	if (voronoiEdgeP20_check2 <= 0.0f && voronoiEdgeP12_check3 <= 0.0f) {
		closestPoint = trianglePoint2;
		return;
	}
}
