// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Utilities.h"

// const
const int32 workShadowHeight = 50;
const uint64 detailsRectStairMilliSec = 3000;
const Color rectColor = Color(48, 48, 48, 150);
const Color frameColor = Color(64, 64, 64);
const Color highlightColor = Color(255, 165, 0, 150);
const double ragRatioDiff = 1.5;

// ç\ë¢ëÃ
struct work
{
	Texture workImage;
	String titleName, makerName /*, description */;
	int32 x, y;
	double ragRatio_def, ragRatio;
};

// âÊëúâ{óó
class Viewing :public MyApp::Scene
{
private:
	Array<work>works;
	Texture shadowImage, plusImage, minusImage, resetImage;
	Font titleFont, makerFont, descriptionFont;
	Triangle goLeftTrg, goRightTrg;
	Rect detailsRect, goLeftRect, goRightRect;
	myTimer detailsRectTimer;
	Point prevMouseP;
	bool detailsRectDrawFlag;
	int nowWorkNum;

public:
	Viewing(const InitData& init);
	void update() override;
	void draw() const override;
	void resetDetailsRectTimer();
};
