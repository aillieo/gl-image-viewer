#include "SceneManager.h"

int SceneManager::index = 0;
int SceneManager::sceneIndexMax = 1;
bool SceneManager::willChangeScene = false;

void SceneManager::toNext()
{
	index ++;
	if(index > sceneIndexMax)
	{
		index = 0;
	}
	willChangeScene = true;
}

void SceneManager::toPrevious()
{
	index --;
	if(index < 0)
	{
		index = sceneIndexMax;
	}
	willChangeScene = true;
}

