// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Utilities.h"

// const
const int32 workShadowHeight = 50;
const uint64 detailsRectStairMilliSec = 3000;

// ç\ë¢ëÃ
struct work
{
	Texture workImage;
	String titleName, makerName /*, description */;
	int32 x, y;
	double ragRatio;
};

// âÊëúâ{óó
class Viewing :public MyApp::Scene
{
private:
	Array<work>works;
	Texture shadowImage;
	Font titleFont, makerFont, descriptionFont;
	Rect detailsRect;
	myTimer detailsRectTimer;
	Point prevMouseP;
	bool detailsRectDrawFlag;

public:
	Viewing(const InitData& init);
	void update() override;
	void draw() const override;
};
