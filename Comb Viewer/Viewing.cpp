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
	pinImage[0] = Texture(U"data//pinImage_0.png");
	pinImage[1] = Texture(U"data//pinImage_1.png");
	slideshowImage[0] = Texture(U"data//slideshowImage_0.png");
	slideshowImage[1] = Texture(U"data//slideshowImage_1.png");
	exitImage = Texture(U"data//exitImage.png");
	titleFont = Font(36, Typeface::Bold);
	makerFont = Font(28, Typeface::Medium);
	// descriptionFont = Font(28);
	goLeftTrg = Triangle(15, Window::Height() / 2, 45, Window::Height() / 2 - 30, 45, Window::Height() / 2 + 30);
	goRightTrg = Triangle(Window::Width() - 15, Window::Height() / 2, Window::Width() - 45, Window::Height() / 2 - 30, Window::Width() - 45, Window::Height() / 2 + 30);
	detailsRect = Rect(0, Window::Height() - titleFont.height() - 15, Window::Width(), titleFont.height() + 15);
	goLeftRect = Rect(0, 0, 60, Window::Height());
	goRightRect = Rect(Window::Width() - 60, 0, 60, Window::Height());
	detailsRectTimer.reset();
	slideshowTimer.reset();
	fadeTimer.reset();
	prevMouseP = Cursor::Pos();
	detailsRectDrawFlag = true;
	pinnedFlag = false;
	slideshowFlag = false;
	nowWorkNum = 0;
	fadeFlag = 0;
	fadeNum = 0;
}

// ‰æ‘œ‰{—— XV
void Viewing::update()
{
	if (!pinnedFlag)
	{
		if (prevMouseP == Cursor::Pos())
		{
			detailsRectTimer.update();
			if (detailsRectTimer.query() >= detailsRectStairMilliSec) detailsRectDrawFlag = false;
		}
		else resetDetailsRectTimer();
	}
	else detailsRectDrawFlag = true;
	if (KeyRight.down() || goRightRect.leftClicked() || (slideshowTimer.query() >= slideshowMilliSec && slideshowFlag))
	{
		nextWorkNum = nowWorkNum;
		++nextWorkNum;
		nextWorkNum %= works.size();
		fadeFlag = -1;
		fadeTimer.reset();
	}
	if (KeyLeft.down() || goLeftRect.leftClicked())
	{
		nextWorkNum = nowWorkNum;
		--nextWorkNum;
		nextWorkNum = (nextWorkNum + (int)works.size()) % (int)works.size();
		fadeFlag = -1;
		fadeTimer.reset();
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
			work.x = (int32)Min<double>(work.x, Window::Width() - work.workImage.width()*work.ragRatio / 2);
			work.x = (int32)Max<double>(work.x, work.workImage.width()*work.ragRatio / 2);
		}
		else
		{
			if ((int32)(work.x + (int32)(work.workImage.width()*work.ragRatio / 2)) < Window::Width()) work.x = (int32)(Window::Width() - work.workImage.width()*work.ragRatio / 2);
			if ((int32)(work.x - (int32)(work.workImage.width()*work.ragRatio / 2)) > 0) work.x = (int32)(work.workImage.width()*work.ragRatio / 2);
		}
		if (work.workImage.height()*work.ragRatio <= Window::Height())
		{
			work.y = (int32)Min<double>(work.y, Window::Height() - work.workImage.height()*work.ragRatio / 2);
			work.y = (int32)Max<double>(work.y, work.workImage.height()*work.ragRatio / 2);
		}
		else
		{
			if ((int32)(work.y + (int32)(work.workImage.height()*work.ragRatio / 2)) < Window::Height()) work.y = (int32)(Window::Height() - work.workImage.height()*work.ragRatio / 2);
			if ((int32)(work.y - (int32)(work.workImage.height()*work.ragRatio / 2)) > 0) work.y = (int32)(work.workImage.height()*work.ragRatio / 2);
		}
	}
	if (resetImage.region(goRightRect.x - plusImage.width() - minusImage.width() - resetImage.width() - 45, 15).leftClicked())
	{
		work.ragRatio = work.ragRatio_def;
		work.x = Window::Width() / 2;
		work.y = Window::Height() / 2;
	}
	if (pinImage[pinnedFlag].region(goLeftRect.x + goLeftRect.w + 15, 15).leftClicked()) pinnedFlag = !pinnedFlag;
	if (slideshowImage[slideshowFlag].region(goLeftRect.x + goLeftRect.w + pinImage[pinnedFlag].width() + 30, 15).leftClicked())
	{
		slideshowFlag = !slideshowFlag;
		slideshowTimer.reset();
	}
	if (slideshowFlag)
	{
		if (slideshowTimer.query() >= slideshowMilliSec) slideshowTimer.reset();
		slideshowTimer.update();
	}
	if (exitImage.region(goLeftRect.x + goLeftRect.w + pinImage[pinnedFlag].width() + slideshowImage[slideshowFlag].width() + 45, 15).leftClicked()) System::Exit();
	if (fadeFlag == -1)
	{
		if (fadeTimer.query() >= fadeMilliSec)
		{
			fadeFlag = 1;
			fadeTimer.reset();
			nowWorkNum = nextWorkNum;
		}
		fadeNum = (int)((double)fadeTimer.query() / fadeMilliSec * 255.);
		fadeTimer.update();
	}
	if (fadeFlag == 1)
	{
		if (fadeTimer.query() >= fadeMilliSec)
		{
			fadeFlag = 0;
			fadeTimer.reset();
		}
		fadeNum = (int)(255. - (double)fadeTimer.query() / fadeMilliSec * 255.);
		fadeTimer.update();
	}
}

// ‰æ‘œ‰{—— •`‰æ
void Viewing::draw() const
{
	auto& work = works[nowWorkNum];
	work.workImage.scaled(work.ragRatio).drawAt(work.x, work.y);
	if (fadeFlag != 0) Window::ClientRect().draw(Color(0, 0, 0, fadeNum));
	if (detailsRectDrawFlag)
	{
		goLeftRect.draw(rectColor);
		goLeftRect.drawFrame(3, 2, frameColor);
		goLeftTrg.draw(goLeftRect.mouseOver() ? highlightColor : Color(200, 200, 200, 150));
		goRightRect.draw(rectColor);
		goRightRect.drawFrame(3, 2, frameColor);
		goRightTrg.draw(goRightRect.mouseOver() ? highlightColor : Color(200, 200, 200, 150));
		plusImage.draw(goRightRect.x - plusImage.width() - 15, 15);
		minusImage.draw(goRightRect.x - plusImage.width() - minusImage.width() - 30, 15);
		resetImage.draw(goRightRect.x - plusImage.width() - minusImage.width() - resetImage.width() - 45, 15);
		pinImage[pinnedFlag].draw(goLeftRect.x + goLeftRect.w + 15, 15);
		slideshowImage[slideshowFlag].draw(goLeftRect.x + goLeftRect.w + pinImage[pinnedFlag].width() + 30, 15);
		exitImage.draw(goLeftRect.x + goLeftRect.w + pinImage[pinnedFlag].width() + slideshowImage[slideshowFlag].width() + 45, 15);
		detailsRect.draw(rectColor);
		detailsRect.drawFrame(3, 2, frameColor);
		titleFont(work.titleName).draw(15, detailsRect.y + detailsRect.h / 2 - titleFont.height() / 2, Palette::White);
		makerFont(work.makerName).draw(Window::Width() - makerFont(work.makerName).region().w - 15, detailsRect.y + detailsRect.h / 2 - makerFont.height() / 2, Palette::White);
		Rect(0, detailsRect.y - workShadowHeight, Window::Width(), workShadowHeight)(shadowImage).draw();
	}
	else if (slideshowFlag)
	{
		detailsRect.draw(rectColor);
		detailsRect.drawFrame(3, 2, frameColor);
		titleFont(work.titleName).draw(15, detailsRect.y + detailsRect.h / 2 - titleFont.height() / 2, Palette::White);
		makerFont(work.makerName).draw(Window::Width() - makerFont(work.makerName).region().w - 15, detailsRect.y + detailsRect.h / 2 - makerFont.height() / 2, Palette::White);
		Rect(0, detailsRect.y - workShadowHeight, Window::Width(), workShadowHeight)(shadowImage).draw();
	}
}

void Viewing::resetDetailsRectTimer()
{
	prevMouseP = Cursor::Pos();
	detailsRectTimer.reset();
	detailsRectDrawFlag = true;
}
