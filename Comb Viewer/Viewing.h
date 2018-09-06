// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>

// \‘¢‘Ì
struct work
{
	Texture workImage;
	String titleName, makerName /*, description */;
	int32 x, y;
	double ragRatio;
};

// ‰æ‘œ‰{——
class Viewing :public MyApp::Scene
{
private:
	Array<work>works;
	Texture shadowImage;
	Font titleFont, makerFont, descriptionFont;
	Rect detailsRect;

public:
	Viewing(const InitData& init);
	void update() override;
	void draw() const override;
};
