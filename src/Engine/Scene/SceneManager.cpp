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

        ScenePtr newScene = eastl::make_unique<Scene>();
        newScene->AddEntities(entities);

        if(result == -1)
        {
            mScenesVector.push_back(eastl::move(newScene));
            result = mScenesVector.size() - 1;
        }
        else
        {
            mScenesVector[result] = eastl::move(newScene);
        }
        mScenesVector[result]->mID = result;

        return result;
    }

    void SceneManager::RemoveScene(int i)
    {
        if(i >= mScenesVector.size())
        {
            std::printf("SceneManager: Scene vector is: %lu while i is:%d\n", mScenesVector.size(), i);
            return;
        }

        Scene* s = mScenesVector[i].get();
        if( s != nullptr)
        {
            mAvailableSpaces.push(i);
            mScenesVector[i].reset();
        }
    }

    void SceneManager::ClearScenes()
    {
        mScenesVector.clear();
    }

    const EntitiesVec& SceneManager::GetEntitiesOfScene(int i)
    {
        return mScenesVector[i]->GetEntities();
    }
}