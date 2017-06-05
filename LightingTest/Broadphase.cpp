#include "Physics.h"

#define AABB_EXPAND 0.01f

//TODO:
bool Physics::IntersectAABB(const Vector3 &centerA, const Vector3 &halfA, 
	const Vector3 &centerB, const Vector3 &halfB){

	if (fabs(centerA[0] - centerB[0]) > halfA[0] + halfB[0]) return false;
	if (fabs(centerA[1] - centerB[1]) > halfA[1] + halfB[1]) return false;
	if (fabs(centerA[2] - centerB[2]) > halfA[2] + halfB[2]) return false;
	return true;
}

//ブロードフェーズ
void Physics::BroadPhase(RigidbodyState* states, Collider* colliders, unsigned int numRigidbodies,
	const Pair *oldPairs, const unsigned int numOldPairs, Pair *newPairs, unsigned int &numNewPairs, const unsigned int maxPairs,
	DefaultAllocator* allocator, void *userData, BroadPhaseCallback callback = NULL
	){

	assert(states);
	assert(colliders);
	assert(oldPairs);
	assert(newPairs);
	assert(allocator);

	numNewPairs = 0;

	// AABB交差ペアを見つける（総当たり）
	// TODO:高速化
	for (unsigned int i = 0; i<numRigidbodies; i++) {
		for (unsigned int j = i + 1; j<numRigidbodies; j++) {
			const RigidbodyState &stateA = states[i];
			const Collider &collidableA = colliders[i];
			const RigidbodyState &stateB = states[j];
			const Collider &collidableB = colliders[j];

			if (callback && !callback(i, j, userData)) {
				continue;
			}

			Matrix3 orientationA(stateA.m_orientation);
			Vector3 centerA = stateA.m_position + orientationA * collidableA.m_center;
			Vector3 halfA = absPerElem(orientationA) * (collidableA.m_half + Vector3(AABB_EXPAND));// AABBサイズを若干拡張

			Matrix3 orientationB(stateB.m_orientation);
			Vector3 centerB = stateB.m_position + orientationB * collidableB.m_center;
			Vector3 halfB = absPerElem(orientationB) * (collidableB.m_half + Vector3(AABB_EXPAND));// AABBサイズを若干拡張

			if (IntersectAABB(centerA, halfA, centerB, halfB) && numNewPairs < maxPairs) {
				//衝突情報を管理するクラスを作成
				Pair &newPair = newPairs[numNewPairs++];

				newPair.rigidBodyA = i<j ? i : j;
				newPair.rigidBodyB = i<j ? j : i;
				newPair.contact = NULL;
			}
		}
	}

	// ソート
	{
		Pair *sortBuff = (Pair*)allocator->allocate(sizeof(Pair)*numNewPairs);
		Sort<Pair>(newPairs, sortBuff, numNewPairs);
		allocator->deallocate(sortBuff);
	}

	// 新しく検出したペアと過去のペアを比較
	Pair *outNewPairs = (Pair*)allocator->allocate(sizeof(Pair)*numNewPairs);
	Pair *outKeepPairs = (Pair*)allocator->allocate(sizeof(Pair)*numOldPairs);
	assert(outNewPairs);
	assert(outKeepPairs);

	unsigned int nNew = 0;
	unsigned int nKeep = 0;

	unsigned int oldId = 0, newId = 0;

	while (oldId<numOldPairs&&newId<numNewPairs) {
		if (newPairs[newId].key > oldPairs[oldId].key) {
			// remove
			allocator->deallocate(oldPairs[oldId].contact);
			oldId++;
		}
		else if (newPairs[newId].key == oldPairs[oldId].key) {
			// keep
			assert(nKeep <= numOldPairs);
			outKeepPairs[nKeep] = oldPairs[oldId];
			nKeep++;
			oldId++;
			newId++;
		}
		else {
			// new
			assert(nNew <= numNewPairs);
			outNewPairs[nNew] = newPairs[newId];
			nNew++;
			newId++;
		}
	};

	if (newId<numNewPairs) {
		// all new
		for (; newId<numNewPairs; newId++, nNew++) {
			assert(nNew <= numNewPairs);
			outNewPairs[nNew] = newPairs[newId];
		}
	}
	else if (oldId<numOldPairs) {
		// all remove
		for (; oldId<numOldPairs; oldId++) {
			allocator->deallocate(oldPairs[oldId].contact);
		}
	}

	for (unsigned int i = 0; i<nNew; i++) {
		outNewPairs[i].contact = (Contact*)allocator->allocate(sizeof(Contact));
		outNewPairs[i].contact->Reset();
	}

	for (unsigned int i = 0; i<nKeep; i++) {
		outKeepPairs[i].contact->Refresh(
			states[outKeepPairs[i].rigidBodyA].m_position,
			states[outKeepPairs[i].rigidBodyA].m_orientation,
			states[outKeepPairs[i].rigidBodyB].m_position,
			states[outKeepPairs[i].rigidBodyB].m_orientation);
	}

	numNewPairs = 0;
	for (unsigned int i = 0; i<nKeep; i++) {
		outKeepPairs[i].type = PairTypeKeep;
		newPairs[numNewPairs++] = outKeepPairs[i];
	}
	for (unsigned int i = 0; i<nNew; i++) {
		outNewPairs[i].type = PairTypeNew;
		newPairs[numNewPairs++] = outNewPairs[i];
	}

	allocator->deallocate(outKeepPairs);
	allocator->deallocate(outNewPairs);

	// ソート
	{
		Pair *sortBuff = (Pair*)allocator->allocate(sizeof(Pair)*numNewPairs);
		Sort<Pair>(newPairs, sortBuff, numNewPairs);
		allocator->deallocate(sortBuff);
	}

}