#pragma once

#include "scene.h"

#include <EASTL/queue.h>
#include <EASTL/deque.h>
#include <EASTL/string.h>
#include <EASTL/fixed_vector.h>
#include <EASTL/unique_ptr.h>

#define MAX_SCENES 50

namespace Muharrik
{
    class Scene;

    class SceneManager
    {
        using ScenePtr  = eastl::unique_ptr<Scene>;
        using ScenesVec = eastl::fixed_vector<ScenePtr, MAX_SCENES, false>;
        using ScenesIDVec = eastl::fixed_vector<int, MAX_SCENES, false>;

        public:
        SceneManager(){}
        ~SceneManager(){}

        void InitSceneManager();
        int AddScene(const EntitiesVec& entities);
        void RemoveScene(int i);
        void ClearScenes();
        const EntitiesVec& GetEntitiesOfScene(int i);

        private:
        ScenesVec mScenesVector;
        eastl::queue<int> mAvailableSpaces;
    };

}