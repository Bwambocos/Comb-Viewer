// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Utilities.h"

// const
const int32 workShadowHeight = 25;
const uint64 detailsRectStairMilliSec = 3000;
const uint64 slideshowMilliSec = 7500;
const uint64 fadeMilliSec = 810;
const Color rectColor = Color(48, 48, 48, 150);
const Color frameColor = Color(64, 64, 64);
const Color highlightColor = Color(255, 165, 0, 150);
const double ragRatioDiff = 1.0;
const FilePath fontDataPath = U"data//fontData.otf";

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
	Texture shadowImage, plusImage, minusImage, resetImage, pinImage[2], slideshowImage[2], exitImage;
	Font titleFont, makerFont, descriptionFont;
	Triangle goLeftTrg, goRightTrg;
	Rect detailsRect, goLeftRect, goRightRect;
	myTimer detailsRectTimer, slideshowTimer, fadeTimer;
	Point prevMouseP;
	bool detailsRectDrawFlag, pinnedFlag, slideshowFlag;
	int nowWorkNum, fadeFlag, fadeNum, nextWorkNum;

public:
	Viewing(const InitData& init);
	void update() override;
	void draw() const override;
	void resetDetailsRectTimer();
};
