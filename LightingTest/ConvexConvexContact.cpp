#pragma once
#include "PhysicsInclude.h"
#include "Physics.h"

enum EpxSatType {
	EpxSatTypePointAFacetB,
	EpxSatTypePointBFacetA,
	EpxSatTypeEdgeEdge,
};

#define CHECK_MINMAX(axis,AMin,AMax,BMin,BMax,type) \
{\
	satCount++;\
	float d1 = AMin - BMax;\
	float d2 = BMin - AMax;\
	if (d1 >= 0.0f || d2 >= 0.0f){\
		return false;\
	}\
	if (distanceMin < d1) {\
		distanceMin = d1; \
		axisMin = axis; \
		satType = type; \
		axisFlip = false; \
	}\
	if (distanceMin < d2) {\
		distanceMin = d2; \
		axisMin = -axis; \
		satType = type; \
		axisFlip = true; \
	}\
}

bool Physics::ConvexConvexContact_Local(
const ConvexMesh &convexA, const Transform3 &transformA,
const ConvexMesh &convexB, const Transform3 &transformB,
Vector3 &normal,float &penetrationDepth,
Vector3 &contactPointA,Vector3 &contactPointB){
	Transform3 transformAB, transformBA;
	Matrix3 matrixAB, matrixBA;
	Vector3 offsetAB, offsetBA;

	// B���[�J����A���[�J���ւ̕ϊ�
	transformAB = orthoInverse(transformA) * transformB;
	matrixAB = transformAB.getUpper3x3();
	offsetAB = transformAB.getTranslation();

	// A���[�J����B���[�J���ւ̕ϊ�
	transformBA = orthoInverse(transformAB);
	matrixBA = transformBA.getUpper3x3();
	offsetBA = transformBA.getTranslation();

	// �ł��󂢊ђʐ[�x�Ƃ��̂Ƃ��̕�����
	float distanceMin = -FLT_MAX;
	Vector3 axisMin(0.0f);
	EpxSatType satType = EpxSatTypeEdgeEdge;
	bool axisFlip;

	//----------------------------------------------------------------------------
	// ����������

	int satCount = 0;

	// ConvexA�̖ʖ@���𕪗����Ƃ���
	for(unsigned int f = 0; f<convexA.m_numFacets; f++) {
		const Facet &facet = convexA.m_facets[f];
		const Vector3 separatingAxis = facet.normal;

		// ConvexA�𕪗����ɓ��e
		float minA, maxA;
		GetProjection(minA, maxA, &convexA, separatingAxis);

		// ConvexB�𕪗����ɓ��e
		float minB, maxB;
		GetProjection(minB, maxB, &convexB, matrixBA * facet.normal);
		float offset = dot(offsetAB, separatingAxis);
		minB += offset;
		maxB += offset;

		// ����
		CHECK_MINMAX(separatingAxis, minA, maxA, minB, maxB, EpxSatTypePointBFacetA);
	}

	// ConvexB�̖ʖ@���𕪗����Ƃ���
	for (unsigned int f = 0; f<convexB.m_numFacets; f++) {
		const Facet &facet = convexB.m_facets[f];
		const Vector3 separatingAxis = matrixAB * facet.normal;

		// ConvexA�𕪗����ɓ��e
		float minA, maxA;
		GetProjection(minA, maxA, &convexA, separatingAxis);

		// ConvexB�𕪗����ɓ��e
		float minB, maxB;
		GetProjection(minB, maxB, &convexB, facet.normal);
		float offset = dot(offsetAB, separatingAxis);
		minB += offset;
		maxB += offset;

		// ����
		CHECK_MINMAX(separatingAxis, minA, maxA, minB, maxB, EpxSatTypePointAFacetB);
	}

	// ConvexA��ConvexB�̃G�b�W�̊O�ς𕪗����Ƃ���
	for (unsigned int eA = 0; eA<convexA.m_numEdges; eA++) {
		const Edge &edgeA = convexA.m_edges[eA];
		if (edgeA.type != EdgeTypeConvex) continue;

		const Vector3 edgeVecA = convexA.m_vertices[edgeA.vertId[1]] - convexA.m_vertices[edgeA.vertId[0]];

		for (unsigned int eB = 0; eB<convexB.m_numEdges; eB++) {
			const Edge &edgeB = convexB.m_edges[eB];
			if (edgeB.type != EdgeTypeConvex) continue;

			const Vector3 edgeVecB = matrixAB * (convexB.m_vertices[edgeB.vertId[1]] - convexB.m_vertices[edgeB.vertId[0]]);

			Vector3 separatingAxis = cross(edgeVecA, edgeVecB);
			if (lengthSqr(separatingAxis) < EPSILON*EPSILON) continue;

			separatingAxis = normalize(separatingAxis);

			// ConvexA�𕪗����ɓ��e
			float minA, maxA;
			GetProjection(minA, maxA, &convexA, separatingAxis);

			// ConvexB�𕪗����ɓ��e
			float minB, maxB;
			GetProjection(minB, maxB, &convexB, matrixBA * separatingAxis);
			float offset = dot(offsetAB, separatingAxis);
			minB += offset;
			maxB += offset;

			// ����
			CHECK_MINMAX(separatingAxis, minA, maxA, minB, maxB, EpxSatTypeEdgeEdge);
		}
	}

	// �����܂œ��B�����̂ŁA�Q�̓ʃ��b�V���͌������Ă���B
	// �܂��A�����x�N�g��(axisMin)�Ɗђʐ[�x(distanceMin)�����܂����B
	// �����x�N�g���͂`�����������������v���X�ɂƂ�B

	//epxPrintf("sat check count %d\n",satCount);

	//----------------------------------------------------------------------------
	// �Փˍ��W���o

	int collCount = 0;

	float closestMinSqr = FLT_MAX;
	Vector3 closestPointA, closestPointB;
	Vector3 separation = 1.1f * fabs(distanceMin) * axisMin;

	for (unsigned int fA = 0; fA<convexA.m_numFacets; fA++) {
		const Facet &facetA = convexA.m_facets[fA];

		float checkA = dot(facetA.normal, -axisMin);
		if (satType == EpxSatTypePointBFacetA && checkA < 0.99f && axisFlip) {
			// ���莲����A�̖@���̂Ƃ��A�����̈ႤA�̖ʂ͔��肵�Ȃ�
			continue;
		}

		if (checkA < 0.0f) {
			// �Փ˖ʂƋt�Ɍ����Ă���ʂ͔��肵�Ȃ�
			continue;
		}

		for (unsigned int fB = 0; fB<convexB.m_numFacets; fB++) {
			const Facet &facetB = convexB.m_facets[fB];

			float checkB = dot(facetB.normal, matrixBA * axisMin);
			if (satType == EpxSatTypePointAFacetB && checkB < 0.99f && !axisFlip) {
				// ���莲����B�̖@���̂Ƃ��A�����̈ႤB�̖ʂ͔��肵�Ȃ�
				continue;
			}

			if (checkB < 0.0f) {
				// �Փ˖ʂƋt�Ɍ����Ă���ʂ͔��肵�Ȃ�
				continue;
			}

			collCount++;

			// �ʂ`�Ɩʂa�̍ŋߐړ_�����߂�
			Vector3 triangleA[3] = {
				separation + convexA.m_vertices[facetA.vertId[0]],
				separation + convexA.m_vertices[facetA.vertId[1]],
				separation + convexA.m_vertices[facetA.vertId[2]],
			};

			Vector3 triangleB[3] = {
				offsetAB + matrixAB * convexB.m_vertices[facetB.vertId[0]],
				offsetAB + matrixAB * convexB.m_vertices[facetB.vertId[1]],
				offsetAB + matrixAB * convexB.m_vertices[facetB.vertId[2]],
			};

			// �G�b�W���m�̍ŋߐړ_�Z�o
			for (int i = 0; i<3; i++) {
				if (convexA.m_edges[facetA.edgeId[i]].type != EdgeTypeConvex) continue;

				for (int j = 0; j<3; j++) {
					if (convexB.m_edges[facetB.edgeId[j]].type != EdgeTypeConvex) continue;

					Vector3 sA, sB;
					GetClosestTwoSegments(
						triangleA[i], triangleA[(i + 1) % 3],
						triangleB[j], triangleB[(j + 1) % 3],
						sA, sB);

					float dSqr = lengthSqr(sA - sB);
					if (dSqr < closestMinSqr) {
						closestMinSqr = dSqr;
						closestPointA = sA;
						closestPointB = sB;
					}
				}
			}

			// ���_�`���ʂa�̍ŋߐړ_�Z�o
			for (int i = 0; i<3; i++) {
				Vector3 s;
				GetClosestPointTriangle(triangleA[i], triangleB[0], triangleB[1], triangleB[2], matrixAB * facetB.normal, s);
				float dSqr = lengthSqr(triangleA[i] - s);
				if (dSqr < closestMinSqr) {
					closestMinSqr = dSqr;
					closestPointA = triangleA[i];
					closestPointB = s;
				}
			}

			// ���_�a���ʂ`�̍ŋߐړ_�Z�o
			for (int i = 0; i<3; i++) {
				Vector3 s;
				GetClosestPointTriangle(triangleB[i], triangleA[0], triangleA[1], triangleA[2], facetA.normal, s);
				float dSqr = lengthSqr(triangleB[i] - s);
				if (dSqr < closestMinSqr) {
					closestMinSqr = dSqr;
					closestPointA = s;
					closestPointB = triangleB[i];
				}
			}
		}
	}

	//epxPrintf("intersection check count %d\n",collCount);

	normal = transformA.getUpper3x3() * axisMin;
	penetrationDepth = distanceMin;
	contactPointA = closestPointA - separation;
	contactPointB = offsetBA + matrixBA * closestPointB;

	return true;
}

bool Physics::ConvexConvexContact(
	const ConvexMesh &convexA, const Transform3 &transformA,
	const ConvexMesh &convexB, const Transform3 &transformB,
	Vector3 &normal,float &penetrationDepth,
	Vector3 &contactPointA,Vector3 &contactPointB)
{
	// ���W�n�ϊ��̉񐔂����炷���߁A�ʐ��̑����������W�n�̊�ɂƂ�

	bool ret;
	if (convexA.m_numFacets >= convexB.m_numFacets) {
		ret = ConvexConvexContact_Local(
			convexA, transformA,
			convexB, transformB,
			normal, penetrationDepth, contactPointA, contactPointB);
	}
	else {
		ret = ConvexConvexContact_Local(
			convexB, transformB,
			convexA, transformA,
			normal, penetrationDepth, contactPointB, contactPointA);
		normal = -normal;
	}

	return ret;
}