#include "PhysicsMathBase.h"
#include "Contact.h"

/// ペアの種類
enum PairType {
	PairTypeNew, ///< 新規
	PairTypeKeep, ///< 維持
};

/// ペア
struct Pair {
	PairType type; ///< 種類
	union {
		unsigned long long key;///< ユニークなキー
		struct {
			unsigned int rigidBodyA; ///< 剛体Aのインデックス
			unsigned int rigidBodyB; ///< 剛体Bのインデックス
		};
	};
	Contact* contact;//衝突情報
};
