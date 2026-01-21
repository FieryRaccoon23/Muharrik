#include "GameScenes.h"

#include "Core/engine.h"
#include "AssetManager/SpriteSerializedData.h"
#include "Scene/SceneManager.h"

#include <EASTL/fixed_vector.h>
#include <entt/entt.hpp>

namespace MuharrikGame
{
    void AppendEntities(Muharrik::EntitiesVec& currentEntites, const Muharrik::EntitiesVec& sceneEntities)
    {
        const auto need = currentEntites.size() + sceneEntities.size();
        if (need > currentEntites.max_size()) 
        {
            return;
        }

        currentEntites.insert(currentEntites.end(), currentEntites.begin(), currentEntites.end());
    }

    /////////////////////////////////SCENES//////////////////////////////////////////////////

    void Scene1(Muharrik::Engine* engine, Muharrik::EntitiesVec& sceneEntities)
    {
        entt::entity e1 = engine->OnCreateSpriteEntity(Muharrik::SpriteEnum::Test_Duck, 
            0.0f, 0.0f, 0.0f, 0.5f, 1.0f);

        entt::entity e2 = engine->OnCreateSpriteEntity(Muharrik::SpriteEnum::Test_Pigeon, 
            250.0f, 0.0f, 0.0f, 0.5f, 1.0f);

        sceneEntities.push_back(e1);
        sceneEntities.push_back(e2);

        engine->OnAddEntitiesToSceneManager(sceneEntities);
    }

    void Scene2(Muharrik::Engine* engine, Muharrik::EntitiesVec& sceneEntities)
    {
        entt::entity e1 = engine->OnCreateSpriteEntity(Muharrik::SpriteEnum::Test_Duck, 
            0.0f, 100.0f, 0.0f, 1.0f, 0.5f);

        entt::entity e2 = engine->OnCreateSpriteEntity(Muharrik::SpriteEnum::Test_Pigeon, 
            250.0f, 150.0f, 0.0f, 1.0f, 2.0f);

        sceneEntities.push_back(e1);
        sceneEntities.push_back(e2);

        engine->OnAddEntitiesToSceneManager(sceneEntities);
    }

    ////////////////////////////////////////////////////////////////////////////////////////

    void GameScenes::InitScenes(Muharrik::Engine* engine)
    {
        Muharrik::EntitiesVec sceneEntities;

        Scene1(engine, sceneEntities);
        sceneEntities.clear();

        // Scene2(engine, sceneEntities);
        // sceneEntities.clear();
    }
    
    void GameScenes::AnotherScene(Muharrik::Engine* engine)
    {
        Muharrik::EntitiesVec sceneEntities;

        Scene2(engine, sceneEntities);
        sceneEntities.clear();
    }
}