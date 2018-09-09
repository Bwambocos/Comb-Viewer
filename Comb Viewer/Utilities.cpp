// include
#include "Utilities.h"

// �t���X�N���[���\����
void turnToFullScreen()
{
	const auto[displayIndex, displayMode] = OptimalScreen::Get(OptimalScreen::Preference::Max);
	Graphics::SetFullScreen(true, displayMode.size, displayIndex, displayMode.refreshRateHz);
}

// ���Ԍv���N���X
// ���ԍX�V
void myTimer::update()
{
	nowMilliSec = Time::GetMillisec();
}

// �o�ߎ��Ԍv�Z
uint64 myTimer::query()
{
	return nowMilliSec - startMilliSec;
}

// ���Z�b�g
void myTimer::reset()
{
	nowMilliSec = startMilliSec = Time::GetMillisec();
}
