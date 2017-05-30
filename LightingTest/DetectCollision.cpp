#pragma once
#include "Physics.h"
#include "PhysicsInclude.h"

void Physics::DetectCollision(const RigidbodyState *states, const Collider *colliders, 
	unsigned int numRigidBodies, const Pair *pairs, unsigned int numPairs){

	assert(states);
	assert(colliders);
	assert(pairs);

	for (unsigned int i = 0; i < numPairs; i++){
		const Pair &pair = pairs[i];

		assert(pair.contact);

		const RigidbodyState &stateA = states[pair.rigidBodyA];
		const RigidbodyState &stateB = states[pair.rigidBodyB];
		const Collider &collA = colliders[pair.rigidBodyA];
		const Collider &collB = colliders[pair.rigidBodyB];

		Transform3 transformA(stateA.m_orientation, stateA.m_position);
		Transform3 transformB(stateB.m_orientation, stateB.m_position);

		for (unsigned int j = 0; j<collA.m_numShapes; j++) {
			const PhysicsShape &shapeA = collA.m_shapes[j];
			Transform3 offsetTransformA(shapeA.m_offsetOrientation, shapeA.m_offsetPosition);
			Transform3 worldTransformA = transformA * offsetTransformA;

			for (unsigned int k = 0; k<collB.m_numShapes; k++) {
				const PhysicsShape &shapeB = collB.m_shapes[k];
				Transform3 offsetTransformB(shapeB.m_offsetOrientation, shapeB.m_offsetPosition);
				Transform3 worldTransformB = transformB * offsetTransformB;

				Vector3 contactPointA;
				Vector3 contactPointB;
				Vector3 normal;
				float penetrationDepth;

				if (ConvexConvexContact(
					shapeA.m_geometry, worldTransformA,
					shapeB.m_geometry, worldTransformB,
					normal, penetrationDepth,
					contactPointA, contactPointB) && penetrationDepth < 0.0f) {

					// 衝突点を剛体の座標系へ変換し、コンタクトへ追加する。
					pair.contact->AddContact(
						penetrationDepth, normal,
						offsetTransformA.getTranslation() + offsetTransformA.getUpper3x3() * contactPointA,
						offsetTransformB.getTranslation() + offsetTransformB.getUpper3x3() * contactPointB);
				}
			}
		}
	}

}