#pragma once

#include "scene.h"

#include <EASTL/string.h>
#include <EASTL/fixed_vector.h>

#define MAX_SCENES 50
#define INIT_CAPACITY 10

namespace Muharrik
{
    class Scene;

    class SceneManager
    {
        using ScenesVec = eastl::fixed_vector<Scene*, MAX_SCENES, false>;
        using LoadedScenesVec = eastl::fixed_vector<int, MAX_SCENES, false>;

        public:
        SceneManager(){}
        ~SceneManager(){}

        void InitSceneManager();
        void UnloadScene(int id);
        void LoadScene(int id);
        int AddScene(const EntitiesVec& entities);
        void QuiteSceneManager();

        private:
        ScenesVec mScenesVector;
        LoadedScenesVec mCurrentScene;
        int mLastSceneID = -1;
    };

}