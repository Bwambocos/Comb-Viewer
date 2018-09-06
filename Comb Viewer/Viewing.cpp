// include
#include "Main.h"
#include "Viewing.h"

// âÊëúâ{óó èâä˙âª
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
		if (tempWork.workImage.height() >= tempWork.workImage.width()) tempWork.ragRatio = (double)Window::Height() / tempWork.workImage.height();
		else tempWork.ragRatio = (double)Window::Width() / tempWork.workImage.width();
		works.push_back(tempWork);
	}
	shadowImage = Texture(U"data//shadowImage.png");
	titleFont = Font(48, Typeface::Bold);
	makerFont = Font(36, Typeface::Medium);
	// descriptionFont = Font(28);
	detailsRect = Rect(0, Window::Height() - titleFont.height() - 30, Window::Width(), titleFont.height() + 30);
}

// âÊëúâ{óó çXêV
void Viewing::update()
{

}

// âÊëúâ{óó ï`âÊ
void Viewing::draw() const
{
	for (auto work : works)
	{
		work.workImage.scaled(work.ragRatio).drawAt(work.x, work.y);
		detailsRect.draw(Color(48, 48, 48));
		detailsRect.drawFrame(2, 1, Color(64, 64, 64));
		titleFont(work.titleName).draw(15, detailsRect.y + detailsRect.h / 2 - titleFont.height() / 2, Palette::White);
		makerFont(work.makerName).draw(Window::Width() - makerFont(work.makerName).region().w - 15, detailsRect.y + detailsRect.h / 2 - makerFont.height() / 2, Palette::White);
	}
	Rect(0, detailsRect.y - 30, Window::Width(), 30)(shadowImage).draw();
}
