#include "PhysicsInclude.h"
#include "Physics.h"
#include "VectorFunction.h"
#include "Solverbody.h"

void Physics::SolveConstraints(
		RigidbodyState *states,
		const RigidBodyElements *bodies,
		unsigned int numRigidBodies,const Pair *pairs,
		unsigned int numPairs,
		BallJoint *joints,unsigned int numJoints,
		unsigned int iteration,	float bias,float slop,
		float timeStep,Allocator *allocator)
	{
		assert(states);
		assert(bodies);
		assert(pairs);

		// ソルバー用プロキシを作成
		SolverBody *solverBodies = (SolverBody*)allocator->allocate(sizeof(SolverBody)*numRigidBodies);
		assert(solverBodies);

		for (unsigned int i = 0; i<numRigidBodies; i++) {
			RigidbodyState &state = states[i];
			const RigidBodyElements &body = bodies[i];
			SolverBody &solverBody = solverBodies[i];

			solverBody.orientation = state.m_orientation;
			solverBody.deltaLinearVelocity = Vector3(0.0f);
			solverBody.deltaAngularVelocity = Vector3(0.0f);

			if (state.m_motionType == MotionType::TypeStatic) {
				solverBody.massInv = 0.0f;
				solverBody.inertiaInv = Matrix3(0.0f);
			}
			else {
				solverBody.massInv = 1.0f / body.m_mass;
				Matrix3 m(solverBody.orientation);
				solverBody.inertiaInv = m * inverse(body.m_inertia) * transpose(m);
			}
		}

		// 拘束のセットアップ
		for (unsigned int i = 0; i<numJoints; i++) {
			BallJoint &joint = joints[i];

			RigidbodyState &stateA = states[joint.rigidBodyA];
			const RigidBodyElements &bodyA = bodies[joint.rigidBodyA];
			SolverBody &solverBodyA = solverBodies[joint.rigidBodyA];

			RigidbodyState &stateB = states[joint.rigidBodyB];
			const RigidBodyElements &bodyB = bodies[joint.rigidBodyB];
			SolverBody &solverBodyB = solverBodies[joint.rigidBodyB];

			Vector3 rA = rotate(solverBodyA.orientation, joint.anchorA);
			Vector3 rB = rotate(solverBodyB.orientation, joint.anchorB);

			Vector3 positionA = stateA.m_position + rA;
			Vector3 positionB = stateB.m_position + rB;
			Vector3 direction = positionA - positionB;
			float distanceSqr = lengthSqr(direction);

			if (distanceSqr < EPSILON * EPSILON) {
				joint.constraint.jacDiagInv = 0.0f;
				joint.constraint.rhs = 0.0f;
				joint.constraint.lowerLimit = -FLT_MAX;
				joint.constraint.upperLimit = FLT_MAX;
				joint.constraint.axis = Vector3(1.0f, 0.0f, 0.0f);
				continue;
			}

			float distance = sqrtf(distanceSqr);
			direction /= distance;

			Vector3 velocityA = stateA.m_linearVelocity + cross(stateA.m_angularVelocity, rA);
			Vector3 velocityB = stateB.m_linearVelocity + cross(stateB.m_angularVelocity, rB);
			Vector3 relativeVelocity = velocityA - velocityB;

			Matrix3 K = Matrix3::scale(Vector3(solverBodyA.massInv + solverBodyB.massInv)) -
				crossMatrix(rA) * solverBodyA.inertiaInv * crossMatrix(rA) -
				crossMatrix(rB) * solverBodyB.inertiaInv * crossMatrix(rB);

			float denom = dot(K * direction, direction);
			joint.constraint.jacDiagInv = 1.0f / denom;
			joint.constraint.rhs = -dot(relativeVelocity, direction); // velocity error
			joint.constraint.rhs -= joint.bias * distance / timeStep; // position error
			joint.constraint.rhs *= joint.constraint.jacDiagInv;
			joint.constraint.lowerLimit = -FLT_MAX;
			joint.constraint.upperLimit = FLT_MAX;
			joint.constraint.axis = direction;

			joint.constraint.accumImpulse = 0.0f;
		}

		for (unsigned int i = 0; i<numPairs; i++) {
			const Pair &pair = pairs[i];

			RigidbodyState &stateA = states[pair.rigidBodyA];
			const RigidBodyElements &bodyA = bodies[pair.rigidBodyA];
			SolverBody &solverBodyA = solverBodies[pair.rigidBodyA];

			RigidbodyState &stateB = states[pair.rigidBodyB];
			const RigidBodyElements &bodyB = bodies[pair.rigidBodyB];
			SolverBody &solverBodyB = solverBodies[pair.rigidBodyB];

			assert(pair.contact);

			pair.contact->m_friction = sqrtf(bodyA.m_friction * bodyB.m_friction);

			for (unsigned int j = 0; j<pair.contact->m_numContacts; j++) {
				ContactPoint &cp = pair.contact->m_contactPoints[j];

				Vector3 rA = rotate(solverBodyA.orientation, cp.pointA);
				Vector3 rB = rotate(solverBodyB.orientation, cp.pointB);

				Matrix3 K = Matrix3::scale(Vector3(solverBodyA.massInv + solverBodyB.massInv)) -
					crossMatrix(rA) * solverBodyA.inertiaInv * crossMatrix(rA) -
					crossMatrix(rB) * solverBodyB.inertiaInv * crossMatrix(rB);

				Vector3 velocityA = stateA.m_linearVelocity + cross(stateA.m_angularVelocity, rA);
				Vector3 velocityB = stateB.m_linearVelocity + cross(stateB.m_angularVelocity, rB);
				Vector3 relativeVelocity = velocityA - velocityB;

				Vector3 tangent1, tangent2;

				CalcTangentVector(cp.normal, tangent1, tangent2);

				float restitution = pair.type == PairTypeNew ? 0.5f*(bodyA.m_restitution + bodyB.m_restitution) : 0.0f;

				// Normal
				{
					Vector3 axis = cp.normal;
					float denom = dot(K * axis, axis);
					cp.constraints[0].jacDiagInv = 1.0f / denom;
					cp.constraints[0].rhs = -(1.0f + restitution) * dot(relativeVelocity, axis); // velocity error
					cp.constraints[0].rhs -= (bias * MIN(0.0f, cp.distance + slop)) / timeStep; // position error
					cp.constraints[0].rhs *= cp.constraints[0].jacDiagInv;
					cp.constraints[0].lowerLimit = 0.0f;
					cp.constraints[0].upperLimit = FLT_MAX;
					cp.constraints[0].axis = axis;
				}

				// Tangent1
				{
					Vector3 axis = tangent1;
					float denom = dot(K * axis, axis);
					cp.constraints[1].jacDiagInv = 1.0f / denom;
					cp.constraints[1].rhs = -dot(relativeVelocity, axis);
					cp.constraints[1].rhs *= cp.constraints[1].jacDiagInv;
					cp.constraints[1].lowerLimit = 0.0f;
					cp.constraints[1].upperLimit = 0.0f;
					cp.constraints[1].axis = axis;
				}

				// Tangent2
				{
					Vector3 axis = tangent2;
					float denom = dot(K * axis, axis);
					cp.constraints[2].jacDiagInv = 1.0f / denom;
					cp.constraints[2].rhs = -dot(relativeVelocity, axis);
					cp.constraints[2].rhs *= cp.constraints[2].jacDiagInv;
					cp.constraints[2].lowerLimit = 0.0f;
					cp.constraints[2].upperLimit = 0.0f;
					cp.constraints[2].axis = axis;
				}
			}
		}

		// Warm starting
		for (unsigned int i = 0; i<numPairs; i++) {
			const Pair &pair = pairs[i];

			SolverBody &solverBodyA = solverBodies[pair.rigidBodyA];
			SolverBody &solverBodyB = solverBodies[pair.rigidBodyB];

			for (unsigned int j = 0; j<pair.contact->m_numContacts; j++) {
				ContactPoint &cp = pair.contact->m_contactPoints[j];
				Vector3 rA = rotate(solverBodyA.orientation, cp.pointA);
				Vector3 rB = rotate(solverBodyB.orientation, cp.pointB);

				for (unsigned int k = 0; k<3; k++) {
					float deltaImpulse = cp.constraints[k].accumImpulse;
					solverBodyA.deltaLinearVelocity += deltaImpulse * solverBodyA.massInv * cp.constraints[k].axis;
					solverBodyA.deltaAngularVelocity += deltaImpulse * solverBodyA.inertiaInv * cross(rA, cp.constraints[k].axis);
					solverBodyB.deltaLinearVelocity -= deltaImpulse * solverBodyB.massInv * cp.constraints[k].axis;
					solverBodyB.deltaAngularVelocity -= deltaImpulse * solverBodyB.inertiaInv * cross(rB, cp.constraints[k].axis);
				}
			}
		}

		// 拘束の演算
		for (unsigned int itr = 0; itr<iteration; itr++) {
			for (unsigned int i = 0; i<numJoints; i++) {
				BallJoint &joint = joints[i];

				SolverBody &solverBodyA = solverBodies[joint.rigidBodyA];
				SolverBody &solverBodyB = solverBodies[joint.rigidBodyB];

				Vector3 rA = rotate(solverBodyA.orientation, joint.anchorA);
				Vector3 rB = rotate(solverBodyB.orientation, joint.anchorB);

				Constraint &constraint = joint.constraint;
				float deltaImpulse = constraint.rhs;
				Vector3 deltaVelocityA = solverBodyA.deltaLinearVelocity + cross(solverBodyA.deltaAngularVelocity, rA);
				Vector3 deltaVelocityB = solverBodyB.deltaLinearVelocity + cross(solverBodyB.deltaAngularVelocity, rB);
				deltaImpulse -= constraint.jacDiagInv * dot(constraint.axis, deltaVelocityA - deltaVelocityB);
				float oldImpulse = constraint.accumImpulse;
				constraint.accumImpulse = CLAMP(oldImpulse + deltaImpulse, constraint.lowerLimit, constraint.upperLimit);
				deltaImpulse = constraint.accumImpulse - oldImpulse;
				solverBodyA.deltaLinearVelocity += deltaImpulse * solverBodyA.massInv * constraint.axis;
				solverBodyA.deltaAngularVelocity += deltaImpulse * solverBodyA.inertiaInv * cross(rA, constraint.axis);
				solverBodyB.deltaLinearVelocity -= deltaImpulse * solverBodyB.massInv * constraint.axis;
				solverBodyB.deltaAngularVelocity -= deltaImpulse * solverBodyB.inertiaInv * cross(rB, constraint.axis);
			}

			for (unsigned int i = 0; i<numPairs; i++) {
				const Pair &pair = pairs[i];

				SolverBody &solverBodyA = solverBodies[pair.rigidBodyA];
				SolverBody &solverBodyB = solverBodies[pair.rigidBodyB];

				for (unsigned int j = 0; j<pair.contact->m_numContacts; j++) {
					ContactPoint &cp = pair.contact->m_contactPoints[j];
					Vector3 rA = rotate(solverBodyA.orientation, cp.pointA);
					Vector3 rB = rotate(solverBodyB.orientation, cp.pointB);

					{
						Constraint &constraint = cp.constraints[0];
						float deltaImpulse = constraint.rhs;
						Vector3 deltaVelocityA = solverBodyA.deltaLinearVelocity + cross(solverBodyA.deltaAngularVelocity, rA);
						Vector3 deltaVelocityB = solverBodyB.deltaLinearVelocity + cross(solverBodyB.deltaAngularVelocity, rB);
						deltaImpulse -= constraint.jacDiagInv * dot(constraint.axis, deltaVelocityA - deltaVelocityB);
						float oldImpulse = constraint.accumImpulse;
						constraint.accumImpulse = CLAMP(oldImpulse + deltaImpulse, constraint.lowerLimit, constraint.upperLimit);
						deltaImpulse = constraint.accumImpulse - oldImpulse;
						solverBodyA.deltaLinearVelocity += deltaImpulse * solverBodyA.massInv * constraint.axis;
						solverBodyA.deltaAngularVelocity += deltaImpulse * solverBodyA.inertiaInv * cross(rA, constraint.axis);
						solverBodyB.deltaLinearVelocity -= deltaImpulse * solverBodyB.massInv * constraint.axis;
						solverBodyB.deltaAngularVelocity -= deltaImpulse * solverBodyB.inertiaInv * cross(rB, constraint.axis);
					}

					float maxFriction = pair.contact->m_friction * fabs(cp.constraints[0].accumImpulse);
					cp.constraints[1].lowerLimit = -maxFriction;
					cp.constraints[1].upperLimit = maxFriction;
					cp.constraints[2].lowerLimit = -maxFriction;
					cp.constraints[2].upperLimit = maxFriction;

					{
						Constraint &constraint = cp.constraints[1];
						float deltaImpulse = constraint.rhs;
						Vector3 deltaVelocityA = solverBodyA.deltaLinearVelocity + cross(solverBodyA.deltaAngularVelocity, rA);
						Vector3 deltaVelocityB = solverBodyB.deltaLinearVelocity + cross(solverBodyB.deltaAngularVelocity, rB);
						deltaImpulse -= constraint.jacDiagInv * dot(constraint.axis, deltaVelocityA - deltaVelocityB);
						float oldImpulse = constraint.accumImpulse;
						constraint.accumImpulse = CLAMP(oldImpulse + deltaImpulse, constraint.lowerLimit, constraint.upperLimit);
						deltaImpulse = constraint.accumImpulse - oldImpulse;
						solverBodyA.deltaLinearVelocity += deltaImpulse * solverBodyA.massInv * constraint.axis;
						solverBodyA.deltaAngularVelocity += deltaImpulse * solverBodyA.inertiaInv * cross(rA, constraint.axis);
						solverBodyB.deltaLinearVelocity -= deltaImpulse * solverBodyB.massInv * constraint.axis;
						solverBodyB.deltaAngularVelocity -= deltaImpulse * solverBodyB.inertiaInv * cross(rB, constraint.axis);
					}
					{
						Constraint &constraint = cp.constraints[2];
						float deltaImpulse = constraint.rhs;
						Vector3 deltaVelocityA = solverBodyA.deltaLinearVelocity + cross(solverBodyA.deltaAngularVelocity, rA);
						Vector3 deltaVelocityB = solverBodyB.deltaLinearVelocity + cross(solverBodyB.deltaAngularVelocity, rB);
						deltaImpulse -= constraint.jacDiagInv * dot(constraint.axis, deltaVelocityA - deltaVelocityB);
						float oldImpulse = constraint.accumImpulse;
						constraint.accumImpulse = CLAMP(oldImpulse + deltaImpulse, constraint.lowerLimit, constraint.upperLimit);
						deltaImpulse = constraint.accumImpulse - oldImpulse;
						solverBodyA.deltaLinearVelocity += deltaImpulse * solverBodyA.massInv * constraint.axis;
						solverBodyA.deltaAngularVelocity += deltaImpulse * solverBodyA.inertiaInv * cross(rA, constraint.axis);
						solverBodyB.deltaLinearVelocity -= deltaImpulse * solverBodyB.massInv * constraint.axis;
						solverBodyB.deltaAngularVelocity -= deltaImpulse * solverBodyB.inertiaInv * cross(rB, constraint.axis);
					}
				}
			}
		}

		// 速度を更新
		for (unsigned int i = 0; i<numRigidBodies; i++) {
			states[i].m_linearVelocity += solverBodies[i].deltaLinearVelocity;
			states[i].m_angularVelocity += solverBodies[i].deltaAngularVelocity;
		}

		allocator->deallocate(solverBodies);
	}