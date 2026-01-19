#pragma once

#include "scene.h"

#include <EASTL/queue.h>
#include <EASTL/deque.h>
#include <EASTL/string.h>
#include <EASTL/fixed_vector.h>

#define MAX_SCENES 50

namespace Muharrik
{
    class Scene;

    class SceneManager
    {
        using ScenesVec = eastl::fixed_vector<Scene*, MAX_SCENES, false>;
        using ScenesIDVec = eastl::fixed_vector<int, MAX_SCENES, false>;

        public:
        SceneManager(){}
        ~SceneManager(){}

        void InitSceneManager();
        int AddScene(const EntitiesVec& entities);
        void RemoveScene(int i);
        void ClearScenes();

        private:
        ScenesVec mScenesVector;
        eastl::queue<int> mAvailableSpaces;
    };

}