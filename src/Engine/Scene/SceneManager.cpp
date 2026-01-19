#include "SceneManager.h"

#include <cstdio>

namespace Muharrik
{
    void SceneManager::InitSceneManager()
    {
    }

    int SceneManager::AddScene(const EntitiesVec& entities)
    {
        int result = -1;

        if(!mAvailableSpaces.empty())
        {
            result = mAvailableSpaces.front();
            mAvailableSpaces.pop();
        }

        Scene* newScene = new Scene();
        newScene->AddEntities(entities);

        if(result == -1)
        {
            mScenesVector.push_back(newScene);
            result = mScenesVector.size() - 1;
        }
        else
        {
            mScenesVector[result] = newScene;
        }

        return result;
    }

    void SceneManager::RemoveScene(int i)
    {
        if(i >= mScenesVector.size())
        {
            std::printf("SceneManager: Scene vector is: %lu while i is:%d\n", mScenesVector.size(), i);
            return;
        }

        Scene* s = mScenesVector[i];
        if( s != nullptr)
        {
            delete s;
            s = nullptr;

            mAvailableSpaces.push(i);
        }
    }

    void SceneManager::ClearScenes()
    {
        for(auto s : mScenesVector)
        {
            delete s;
        }

        mScenesVector.clear();
    }
}