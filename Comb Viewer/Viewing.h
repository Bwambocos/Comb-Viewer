// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>

// �\����
struct work
{
	Texture workImage;
	String titleName, makerName, description;
	int32 x, y;
	double ragRatio;
};

// �摜�{��
class Viewing :public MyApp::Scene
{
private:
	Array<work>works;
	Font titleFont, makerFont, descriptionFont;

public:
	Viewing(const InitData& init);
	void update() override;
	void draw() const override;
};
