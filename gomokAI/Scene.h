#pragma once

#include "IUpdateObject.h"
#include "CustomRenderer.h"
#include <vector>
#include <SDL.h>
class Scene
{
private:
	std::vector<IUpdateObject*> updateObjects;//������Ʈ�Լ� ������ ������Ʈ��
public:
	Scene(CustomRenderer* customRenderer);
	void Update();
	void AddUpdateObject(IUpdateObject* object);
	virtual void EventHandling(SDL_Event) = 0;
	virtual Scene* NextScene() = 0;
	virtual void UpdateScene() = 0;
	bool GetNextSceneReady();
	void ReadyToNextScene();
protected:
	CustomRenderer* customRenderer;
private:
	bool nextSceneReady = false;
};