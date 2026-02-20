#include "stdafx.h"
#include "system/system.h"

#include<InitGUID.h>
#include<dxgidebug.h>




void ReportLiveObjects()
{
	IDXGIDebug* pDxgiDebug;

	typedef HRESULT(__stdcall* fPtr)(const IID&, void**);
	HMODULE hDll = GetModuleHandleW(L"dxgidebug.dll");
	fPtr DXGIGetDebugInterface = (fPtr)GetProcAddress(hDll, "DXGIGetDebugInterface");

	DXGIGetDebugInterface(__uuidof(IDXGIDebug), (void**)&pDxgiDebug);

	// 出力。
	pDxgiDebug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_DETAIL);
}

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));
	//////////////////////////////////////
	// ここから初期化を行うコードを記述する。
	//////////////////////////////////////


	/***************** 生成 *****************/ 

	SoundManager::CreateInstance();		// SoundManagerのインスタンスを作成
	ParameterManager::CreateInstance(); // パラメーターマネージャーを作成
	auto* gameEffectManager = NewGO<GameEffectObject>(CreateClassPriority::Enum::GameEffectManager, "gameEffectObject");	// GameEffectManager用のオブジェクトを作成
	auto* fadeManagerObject = NewGO<FadeManagerObject>(CreateClassPriority::Enum::FadeManager, "fadeManagerObject");	// FadeManager用のオブジェクトを作成
	auto* sceneManagerObject = NewGO<SceneManagerObject>(CreateClassPriority::Enum::SceneManager, "sceneManagerObject"); // SceneManager用のオブジェクトを作成

	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	
	/***************** ゲームループ *****************/
	while (DispatchWindowMessage())
	{
		if (SceneManager::Get().IsAvailable()) 
		{
			SceneManager::Get().Update();
		}

		K2Engine::GetInstance()->Execute();
	}


	/***************** 生成したものの破棄 *****************/
	{
		// シングルトンクラスの破棄
		{
			SoundManager::Get().DestroyInstance();	// SoundManagerのインスタンスを破棄
			ParameterManager::Get().DestroyInstance(); // パラメーターマネージャーを破棄
		}
		
		// オブジェクトの削除
		{
			DeleteGO(gameEffectManager);
			DeleteGO(fadeManagerObject);
			DeleteGO(sceneManagerObject);
		}
	}
	K2Engine::DeleteInstance();

#ifdef _DEBUG
	ReportLiveObjects();
#endif // _DEBUG
	return 0;
}

