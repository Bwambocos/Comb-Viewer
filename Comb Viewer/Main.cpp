// include
#include "Main.h"
#include "Utilities.h"
#include "Viewing.h"

void Main()
{
	// ウィンドウ関連 初期化
	Window::SetTitle(U"Comb Viewer " + versionStr);
	Graphics::SetBackground(Color(32, 32, 32));
#ifdef _DEBUG
	Window::Resize(1280, 720);
#else
	turnToFullScreen();
#endif

	// シーン 初期化
	MyApp sceneMgr;
	sceneMgr.add<Viewing>(U"Viewing");

	// メインループ
	while (System::Update())
	{
		sceneMgr.updateScene();
		sceneMgr.drawScene();
	}
}
