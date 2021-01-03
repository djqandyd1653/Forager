#include "SceneManager.h"
#include "GameNode.h"

DWORD CALLBACK LoadingThread(LPVOID pvParam)
{
	SceneManager::readyScene->Init();
	SceneManager::currScene = SceneManager::readyScene;

	SceneManager::loadingScene->Release();
	SceneManager::loadingScene = nullptr;
	SceneManager::readyScene = nullptr;

	return 0;
}

GameNode* SceneManager::currScene = nullptr;
GameNode* SceneManager::loadingScene = nullptr;
GameNode* SceneManager::readyScene = nullptr;

void SceneManager::Release()
{
	itScene = sceneData.begin();

	for(;itScene != sceneData.end(); itScene++)
	{
		SAFE_RELEASE(itScene->second);
		SAFE_DELETE(itScene->second);
		itScene = sceneData.erase(itScene);
	}
	sceneData.clear();

	itScene = loadingSceneData.begin();

	for (; itScene != loadingSceneData.end(); itScene++)
	{
		SAFE_RELEASE(itScene->second);
		SAFE_DELETE(itScene->second);
		itScene = loadingSceneData.erase(itScene);
	}
	loadingSceneData.clear();
}

GameNode * SceneManager::AddScene(string key, GameNode * scene)
{
	if (scene == nullptr)
		return nullptr;

	itScene = sceneData.find(key);

	if (itScene != sceneData.end())
		return nullptr;
	sceneData.insert(make_pair(key, scene));
	return scene;
}

GameNode * SceneManager::AddLoadingScene(string key, GameNode * scene)
{
	if (scene == nullptr)
		return nullptr;
	if (loadingSceneData.find(key) != loadingSceneData.end())
		return nullptr;
	loadingSceneData.insert(make_pair(key, scene));
	return scene;
}

HRESULT SceneManager::ChangeScene(string name)
{
	itScene = sceneData.find(name);
	if (itScene != sceneData.end())
	{
		GameNode* scene = itScene->second;
		if (scene)
		{
			//TimeManager::GetSingleton()->AllDeleteTimer();
			if (SUCCEEDED(scene->Init()))
			{
				if (currScene)
				{
					currScene->Release();
				}
				currScene = scene;

				return S_OK;
			}
		}
	}

	return E_FAIL;
}

HRESULT SceneManager::ChangeScene(string scenename, string loadingScenename)
{
	itScene = sceneData.find(scenename);
	if (itScene == sceneData.end())
		return E_FAIL;
	
	itLoadingScene = loadingSceneData.find(loadingScenename);
	if (itLoadingScene != loadingSceneData.end())
		return ChangeScene(scenename);

	if (SUCCEEDED(itLoadingScene->second->Init()))
	{
		if (currScene)
		{
			currScene->Release();
		}
		currScene = itLoadingScene->second;

		readyScene = itScene->second;
		loadingScene = itLoadingScene->second;

		currScene = itLoadingScene->second;
		//TimerManager::GetSingleton()->AllDeleteTimer();
		// 스레드 핸들
		HANDLE hThread;
		DWORD loadThreadID;
		hThread = CreateThread(NULL, 0,
								LoadingThread,	//실행시킬 함수
								NULL,			//함수 파라미터
								0, &loadThreadID);

		CloseHandle(hThread);
		return S_OK;
	}

	return E_FAIL;
}
