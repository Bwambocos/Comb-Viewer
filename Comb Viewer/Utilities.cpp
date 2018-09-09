// include
#include "Utilities.h"

// フルスクリーン表示化
void turnToFullScreen()
{
	const auto[displayIndex, displayMode] = OptimalScreen::Get(OptimalScreen::Preference::Max);
	Graphics::SetFullScreen(true, displayMode.size, displayIndex, displayMode.refreshRateHz);
}

// 時間計測クラス
// 時間更新
void myTimer::update()
{
	nowMilliSec = Time::GetMillisec();
}

// 経過時間計算
uint64 myTimer::query()
{
	return nowMilliSec - startMilliSec;
}

// リセット
void myTimer::reset()
{
	nowMilliSec = startMilliSec = Time::GetMillisec();
}
