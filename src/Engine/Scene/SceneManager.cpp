#include "SceneManager.h"

namespace Muharrik
{
    void SceneManager::InitSceneManager()
    {
        for(int i = 0; i < INIT_CAPACITY; ++i)
        {
            Scene* newScene = new Scene();
            mScenesVector.push_back(newScene);
        }
        mLastSceneID = -1;
    }

    void SceneManager::UnloadScene(int id)
    {

    }

    void SceneManager::LoadScene(int id)
    {

    }

    int SceneManager::AddScene(const EntitiesVec& entities)
    {
        if(mLastSceneID >= INIT_CAPACITY - 1)
        {
            Scene* newScene = new Scene();
            mScenesVector.push_back(newScene);
        }

        ++mLastSceneID;

        Scene* s = mScenesVector[mLastSceneID];
        s->AddEntities(entities);

        return mLastSceneID;
    }

    void SceneManager::QuiteSceneManager()
    {
        for(auto s : mScenesVector)
        {
            delete s;
        }

        mScenesVector.clear();
    }
}