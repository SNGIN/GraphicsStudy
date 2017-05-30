#include "PhysicsMathBase.h"
#include "Contact.h"

/// �y�A�̎��
enum PairType {
	PairTypeNew, ///< �V�K
	PairTypeKeep, ///< �ێ�
};

/// �y�A
struct Pair {
	PairType type; ///< ���
	union {
		unsigned long long key;///< ���j�[�N�ȃL�[
		struct {
			unsigned int rigidBodyA; ///< ����A�̃C���f�b�N�X
			unsigned int rigidBodyB; ///< ����B�̃C���f�b�N�X
		};
	};
	Contact* contact;//�Փˏ��
};
