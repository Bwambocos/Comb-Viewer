// include
#include "Utilities.h"

// フルスクリーン表示化
void turnToFullScreen()
{
	const auto[displayIndex, displayMode] = OptimalScreen::Get(OptimalScreen::Preference::Max);
	Graphics::SetFullScreen(true, displayMode.size, displayIndex, displayMode.refreshRateHz);
}
