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
		String tempDescription;
		while (descriptionReader.readLine(tempDescription)) tempWork.description += tempDescription;
		tempWork.x = Window::Width() / 2;
		tempWork.y = Window::Height() / 2;

		if (tempWork.workImage.height() >= tempWork.workImage.width()) tempWork.ragRatio = (double)Window::Height() / tempWork.workImage.height();
		else tempWork.ragRatio = (double)Window::Width() / tempWork.workImage.width();
		works.push_back(tempWork);
	}
	titleFont = Font(48);
	makerFont = Font(36);
	descriptionFont = Font(28);
}

// ‰æ‘œ‰{—— XV
void Viewing::update()
{

}

// ‰æ‘œ‰{—— •`‰æ
void Viewing::draw() const
{
	for (auto work : works)
	{
		work.workImage.scaled(work.ragRatio).drawAt(work.x, work.y);
	}
}
