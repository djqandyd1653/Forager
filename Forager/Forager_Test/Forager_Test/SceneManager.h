#pragma once
#include "pch.h"
#include "Singleton.h"

class GameNode;

class SceneManager : public Singleton<SceneManager>
{
private:
	map<string, GameNode*> sceneData;
	map<string, GameNode*> loadingSceneData;
	map<string, GameNode*>::iterator itScene;
	map<string, GameNode*>::iterator itLoadingScene;

public:
	static GameNode* currScene;		// 현재 출력 중인 씬
	static GameNode* loadingScene;	// 다음 씬 준비 중에 출력될 씬
	static GameNode* readyScene;	// 준비 중인 씬

public:
	void Release();

	// 씬 추가
	GameNode* AddScene(string key, GameNode* scene);
	GameNode* AddLoadingScene(string key, GameNode* scene);

	HRESULT ChangeScene(string name);								// 로딩 씬 X
	HRESULT ChangeScene(string scenename, string loadingScenename);	// 로딩 씬 O
};

