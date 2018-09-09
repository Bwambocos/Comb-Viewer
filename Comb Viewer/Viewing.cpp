// include
#include "Main.h"
#include "Viewing.h"

// ‰æ‘œ‰{—— ‰Šú‰»
Viewing::Viewing(const InitData& init) :IScene(init)
{
	TextReader listReader(U"data//work_list.txt");
	String folderName;
	while (listReader.readLine(folderName))
	{
		work tempWork;
		tempWork.workImage = Texture(U"data//" + folderName + U"//Image.png");
		TextReader descriptionReader(U"data//" + folderName + U"//Description.txt");
		descriptionReader.readLine(tempWork.titleName);
		descriptionReader.readLine(tempWork.makerName);
		// String tempDescription;
		// while (descriptionReader.readLine(tempDescription)) tempWork.description += tempDescription;
		tempWork.x = Window::Width() / 2;
		tempWork.y = Window::Height() / 2;
		tempWork.ragRatio_def = tempWork.ragRatio = Min((double)Window::Height() / tempWork.workImage.height(), (double)Window::Width() / tempWork.workImage.width());
		works.push_back(tempWork);
	}
	shadowImage = Texture(U"data//shadowImage.png");
	plusImage = Texture(U"data//plusImage.png");
	minusImage = Texture(U"data//minusImage.png");
	resetImage = Texture(U"data//resetImage.png");
	titleFont = Font(48, Typeface::Bold);
	makerFont = Font(36, Typeface::Medium);
	// descriptionFont = Font(28);
	goLeftTrg = Triangle(15, Window::Height() / 2, 45, Window::Height() / 2 - 30, 45, Window::Height() / 2 + 30);
	goRightTrg = Triangle(Window::Width() - 15, Window::Height() / 2, Window::Width() - 45, Window::Height() / 2 - 30, Window::Width() - 45, Window::Height() / 2 + 30);
	detailsRect = Rect(0, Window::Height() - titleFont.height() - 30, Window::Width(), titleFont.height() + 30);
	goLeftRect = Rect(0, 0, 60, Window::Height());
	goRightRect = Rect(Window::Width() - 60, 0, 60, Window::Height());
	detailsRectTimer.reset();
	prevMouseP = Cursor::Pos();
	detailsRectDrawFlag = true;
	nowWorkNum = 0;
}

// ‰æ‘œ‰{—— XV
void Viewing::update()
{
	if (prevMouseP == Cursor::Pos())
	{
		detailsRectTimer.update();
		if (detailsRectTimer.query() >= detailsRectStairMilliSec) detailsRectDrawFlag = false;
	}
	else resetDetailsRectTimer();
	if (KeyRight.down() || goRightRect.leftClicked())
	{
		++nowWorkNum;
		nowWorkNum %= works.size();
		resetDetailsRectTimer();
	}
	if (KeyLeft.down() || goLeftRect.leftClicked())
	{
		--nowWorkNum;
		nowWorkNum = (nowWorkNum + works.size()) % works.size();
		resetDetailsRectTimer();
	}
	auto& work = works[nowWorkNum];
	if (plusImage.region(goRightRect.x - plusImage.width() - 15, 15).leftClicked())
	{
		work.ragRatio += ragRatioDiff;
		resetDetailsRectTimer();
	}
	if (minusImage.region(goRightRect.x - plusImage.width() - minusImage.width() - 30, 15).leftClicked())
	{
		work.ragRatio -= ragRatioDiff;
		resetDetailsRectTimer();
	}
	work.ragRatio += Mouse::Wheel();
	work.ragRatio = Max(work.ragRatio, work.ragRatio_def);
	if (MouseL.pressed())
	{
		work.x += Cursor::ScreenDelta().x;
		work.y += Cursor::ScreenDelta().y;
		if (work.workImage.width()*work.ragRatio <= Window::Width())
		{
			work.x = Min<double>(work.x, Window::Width() - work.workImage.width()*work.ragRatio / 2);
			work.x = Max<double>(work.x, work.workImage.width()*work.ragRatio / 2);
		}
		else
		{
			if (work.x + work.workImage.width()*work.ragRatio / 2 < Window::Width())
			{
				work.x = Window::Width() - work.workImage.width()*work.ragRatio / 2;
			}
			if (work.x - work.workImage.width()*work.ragRatio / 2 > 0)
			{
				work.x = work.workImage.width()*work.ragRatio / 2;
			}
		}
		if (work.workImage.height()*work.ragRatio <= Window::Height())
		{
			work.y = Min<double>(work.y, Window::Height() - work.workImage.height()*work.ragRatio / 2);
			work.y = Max<double>(work.y, work.workImage.height()*work.ragRatio / 2);
		}
		else
		{
			if (work.y + work.workImage.height()*work.ragRatio / 2 < Window::Height())
			{
				work.y = Window::Height() - work.workImage.height()*work.ragRatio / 2;
			}
			if (work.y - work.workImage.height()*work.ragRatio / 2 > 0)
			{
				work.y = work.workImage.height()*work.ragRatio / 2;
			}
		}
	}
	if (resetImage.region(goRightRect.x - plusImage.width() - minusImage.width() - resetImage.width() - 45, 15).leftClicked())
	{
		work.ragRatio = work.ragRatio_def;
		work.x = Window::Width() / 2;
		work.y = Window::Height() / 2;
	}
}

// ‰æ‘œ‰{—— •`‰æ
void Viewing::draw() const
{
	auto& work = works[nowWorkNum];
	work.workImage.scaled(work.ragRatio).drawAt(work.x, work.y);
	if (detailsRectDrawFlag)
	{
		goLeftRect.draw(rectColor);
		goLeftRect.drawFrame(3, 2, frameColor);
		goLeftTrg.draw(goLeftRect.mouseOver() ? highlightColor : Color(200, 200, 200, 150));
		goRightRect.draw(rectColor);
		goRightRect.drawFrame(3, 2, frameColor);
		goRightTrg.draw(goRightRect.mouseOver() ? highlightColor : Color(200, 200, 200, 150));
		detailsRect.draw(rectColor);
		detailsRect.drawFrame(3, 2, frameColor);
		titleFont(work.titleName).draw(15, detailsRect.y + detailsRect.h / 2 - titleFont.height() / 2, Palette::White);
		makerFont(work.makerName).draw(Window::Width() - makerFont(work.makerName).region().w - 15, detailsRect.y + detailsRect.h / 2 - makerFont.height() / 2, Palette::White);
		Rect(0, detailsRect.y - workShadowHeight, Window::Width(), workShadowHeight)(shadowImage).draw();
		plusImage.draw(goRightRect.x - plusImage.width() - 15, 15);
		minusImage.draw(goRightRect.x - plusImage.width() - minusImage.width() - 30, 15);
		resetImage.draw(goRightRect.x - plusImage.width() - minusImage.width() - resetImage.width() - 45, 15);
	}
}

void Viewing::resetDetailsRectTimer()
{
	prevMouseP = Cursor::Pos();
	detailsRectTimer.reset();
	detailsRectDrawFlag = true;
}
