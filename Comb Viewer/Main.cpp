// include
#include "Main.h"

void Main()
{
	// ウィンドウ関連 初期化
	Window::SetTitle(U"Comb Viewer " + versionStr);

	// シーン 初期化
	SceneManager<String, sharedData> sceneMgr;

	// メインループ
	while (System::Update())
	{
		sceneMgr.updateScene();
		sceneMgr.drawScene();
	}
}
