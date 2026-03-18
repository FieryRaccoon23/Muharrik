#include "PhysicsSystem.h"

namespace Muharrik
{
    void PhysicsSystem::Init()
    {
        char error[1000] = "";
        mModel = mj_loadXML(mModelPath, nullptr, 
                            error, sizeof(error));
        if (!mModel) 
        {
            printf("MuJoCo load error: %s\n", error);
            return;
        }
        mData = mj_makeData(mModel);
    }

    void PhysicsSystem::Step(float dt)
    {
        if (!mModel || !mData) 
        {
            return;
        }
        mj_step(mModel, mData);
    }

    void PhysicsSystem::Quit()
    {
        if (mData)
        { 
            mj_deleteData(mData);   
            mData  = nullptr; 
        }
        
        if (mModel) 
        { 
            mj_deleteModel(mModel); 
            mModel = nullptr; 
        }
    }
    
}