// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>

// フルスクリーン表示化
void turnToFullScreen();

// 時間計測クラス
class myTimer
{
private:
	uint64 nowMilliSec, startMilliSec;

public:
	void update();
	uint64 query();
	void reset();
};
