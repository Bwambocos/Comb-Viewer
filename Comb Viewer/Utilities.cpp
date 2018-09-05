// include
#include "Utilities.h"

// �t���X�N���[���\����
void turnToFullScreen()
{
	const auto[displayIndex, displayMode] = OptimalScreen::Get(OptimalScreen::Preference::Max);
	Graphics::SetFullScreen(true, displayMode.size, displayIndex, displayMode.refreshRateHz);
}
