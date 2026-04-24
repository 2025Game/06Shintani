#pragma once
#ifndef CXPLAYER_E
#define CXPLAYER_E

#include "CXCharacter.h"

class CXPlayer :public CXCharacter
{
public:
	void Update() override;
};
#endif // !CXPLAYER_E
