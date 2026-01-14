#pragma once

#include <EASTL/string.h>
#include <EASTL/fixed_vector.h>

#define MAX_SCENES 50

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

        void UnloadScene(int id);
        void LoadScene(int id);

        private:
        ScenesVec mScenesVector;
        LoadedScenesVec mCurrentScene;
    };

}