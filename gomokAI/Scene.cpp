#include "Scene.h"
Scene::Scene(CustomRenderer* customRenderer)
{
	this->customRenderer = customRenderer;
}
void Scene::Update()
{
	for (int i = 0; i < this->updateObjects.size(); i++)
	{
		this->updateObjects[i]->Update();
	}
}
void Scene::AddUpdateObject(IUpdateObject* object)
{
	this->updateObjects.push_back(object);
}
bool Scene::GetNextSceneReady()
{
	return this->nextSceneReady;
}
void Scene::ReadyToNextScene()
{
	this->nextSceneReady = true;
}