#pragma once
#include "PhysicsMathBase.h"

struct Constraint{
	Vector3 axis;//S‘©²
	float jacDiagInv;//S‘©®‚Ì•ª•ê
	float rhs;//‰ŠúS‘©—Í
	float lowerLimit;//S‘©—Í‚Ì‰ºŒÀ
	float upperLimit;//S‘©—Í‚ÌãŒÀ
	float accumImpulse;//’~Ï‚³‚ê‚éS‘©—Í
};