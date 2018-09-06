// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>

// �t���X�N���[���\����
void turnToFullScreen();

// ���Ԍv���N���X
class myTimer
{
private:
	uint64 nowMilliSec, startMilliSec;

public:
	void update();
	uint64 query();
	void reset();
};
