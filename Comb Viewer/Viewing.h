// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>

// �摜�{��
class Viewing :public MyApp::Scene
{
private:

public:
	Viewing(const InitData& init);
	void update() override;
	void draw() const override;
};
