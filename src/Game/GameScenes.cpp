#include "GameScenes.h"

#include "Scene/SceneManager.h"
#include "Core/engine.h"
#include "AssetManager/SpriteSerializedData.h"
//#include "Core/factory.h"

#include <entt/entt.hpp>
#include <EASTL/string.h>
#include <EASTL/fixed_vector.h>

namespace MuharrikGame
{
    void GameScenes::InitScenes(Muharrik::Engine* engine)
    {
        //TEST
        //const char* relativePath = "content/engine/test.png";
        //entt::entity e1 = Muharrik::OnCreateSpriteEntityDelegate(relativePath, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f);
        entt::entity e1 = engine->OnCreateSpriteEntity(Muharrik::SpriteEnum::Test_Duck, 
            0.0f, 0.0f, 0.0f, 0.5f, 1.0f);
        //const char* relativePath2 = "content/engine/test2.png";
        //entt::entity e2 = Muharrik::OnCreateSpriteEntityDelegate(relativePath2, 250.0f, 0.0f, 0.0f, 0.5f, 1.0f);
        entt::entity e2 = engine->OnCreateSpriteEntity(Muharrik::SpriteEnum::Test_Pigeon, 
            250.0f, 0.0f, 0.0f, 0.5f, 1.0f);

        entt::entity e3 = engine->OnCreateSpriteEntity(Muharrik::SpriteEnum::Test_Pigeon, 
        450.0f, 0.0f, 0.0f, 1.0f, 1.0f);

        Muharrik::EntitiesVec entities;
        entities.push_back(e1);
        entities.push_back(e2);
        entities.push_back(e3);

        engine->OnAddEntitiesToSceneManager(entities);

    }

    void GameScenes::SetStartupScenes()
    {
    }
    
}