#pragma once

#include "IUpdateObject.h"
#include "CustomRenderer.h"
#include <vector>
#include <SDL.h>
class Scene
{
private:
	std::vector<IUpdateObject*> updateObjects;//업데이트함수 실행대상 오브젝트들
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