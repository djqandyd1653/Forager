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
	static GameNode* currScene;		// ���� ��� ���� ��
	static GameNode* loadingScene;	// ���� �� �غ� �߿� ��µ� ��
	static GameNode* readyScene;	// �غ� ���� ��

public:
	void Release();

	// �� �߰�
	GameNode* AddScene(string key, GameNode* scene);
	GameNode* AddLoadingScene(string key, GameNode* scene);

	HRESULT ChangeScene(string name);								// �ε� �� X
	HRESULT ChangeScene(string scenename, string loadingScenename);	// �ε� �� O
};

