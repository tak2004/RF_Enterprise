#include <RadonFramework/Radon.hpp>
#include <RFECS/BaseComponent.hpp>
#include <RFECS/ComponentManager.hpp>
#include <RFECS/Collector.hpp>
#include <RFECS/SharedAttributePool.hpp>
#include <RFECS/Allocator.hpp>

// define components
namespace CompontID {
enum :RF_Type::UInt32
{
    Physic,
    AI,
    Render,

    MAX
};
}

// define shared attributes
namespace SharedAttributID {
enum :RF_Type::UInt32
{
    Transform
};
}

// data description of an attribute
struct Transform
{
    RF_Type::Float32 pos[4];
    RF_Geo::Quaternion<RF_Type::Float32> quaternion;
    RF_Type::Float32 scale[4];
};

// specialize our components
namespace RadonFastEntityComponentSystem {

template<>
struct BaseComponent<CompontID::Physic>
{
    BaseComponent():m_Entity(0), m_Transform(0) { }

    void Setup(EntityID Entity, RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data,
        SharedAttributePool& SharedAttributes)
    {
        m_Entity = Entity;

        m_Transform = reinterpret_cast<Transform*>(
            SharedAttributes.AttachToEntity(SharedAttributID::Transform,
            sizeof(SharedAttributID::Transform), m_Entity));
    }

    void Process()
    {
        // 100us
        RF_Time::TimeSpan consumptionTime = RF_Time::TimeSpan::CreateByTime(0, 0, 0, 0, 1);
        RF_SysThread::Thread::Sleep(consumptionTime);
    }
private:
    Transform* m_Transform;
    EntityID m_Entity;
};

template<>
struct BaseComponent<CompontID::AI>
{
    BaseComponent():m_Entity(0), m_Transform(0), m_State(Initialize)
    {
    }

    void Setup(EntityID Entity, RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data,
        SharedAttributePool& SharedAttributes)
    {
        m_Entity = Entity;

        m_Transform = reinterpret_cast<Transform*>(
            SharedAttributes.AttachToEntity(SharedAttributID::Transform,
            sizeof(SharedAttributID::Transform), m_Entity));
    }

    void Process()
    {
        // 100us
        RF_Time::TimeSpan consumptionTime = RF_Time::TimeSpan::CreateByTime(0, 0, 0, 0, 1);
        RF_SysThread::Thread::Sleep(consumptionTime);
    }
private:
    Transform* m_Transform;// shared 
    EntityID m_Entity;
    enum { Initialize, Discover, Flee } m_State;
};

template<>
struct BaseComponent<CompontID::Render>
{
    BaseComponent():m_Entity(0), m_Transform(0)
    {
    }

    void Setup(EntityID Entity, RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data,
        SharedAttributePool& SharedAttributes)
    {
        m_Entity = Entity;

        m_Transform = reinterpret_cast<Transform*>(
            SharedAttributes.AttachToEntity(SharedAttributID::Transform,
            sizeof(SharedAttributID::Transform), m_Entity));
    }

    void Process()
    {
        // 100us
        RF_Time::TimeSpan consumptionTime = RF_Time::TimeSpan::CreateByTime(0, 0, 0, 0, 1);
        RF_SysThread::Thread::Sleep(consumptionTime);
    }
private:
    Transform* m_Transform;
    EntityID m_Entity;
};

}

// shortcuts for base components
using PhysicBehaviour = RFECS::BaseComponent<CompontID::Physic>;
using AIBehaviour = RFECS::BaseComponent<CompontID::AI>;
using RenderBehaviour = RFECS::BaseComponent<CompontID::Render>;

// specialize and create a shortcut of a component manager
using RenderManager = RFECS::ComponentManager<CompontID::Render>;

// custom component manager
class PhysicsAndAIManager: public RFECS::BaseComponentManager
{
public:
    PhysicsAndAIManager();
    virtual void Setup(RFECS::Allocator& MemoryAllocator, RFECS::SharedAttributePool& AttributePool);
    virtual void Process();
    virtual RF_Type::Bool AttachComponentOnEntity(RFECS::ComponentID Component,
        RF_Mem::AutoPointerArray<RF_Type::UInt8>& ComponentData,
        RFECS::EntityID Entity, RFECS::SharedAttributePool& SharedAttributes);
private:
    RF_Collect::Array<AIBehaviour> m_AIComponents;
    RF_Collect::Array<PhysicBehaviour> m_PhysicComponents;
};

PhysicsAndAIManager::PhysicsAndAIManager()
:BaseComponentManager()
{
    m_ComponentIdentifiers.Resize(2);
    m_ComponentIdentifiers(0) = static_cast<RF_Type::UInt32>(CompontID::Physic);
    m_ComponentIdentifiers(1) = static_cast<RF_Type::UInt32>(CompontID::AI);
}

void PhysicsAndAIManager::Setup(RFECS::Allocator& MemoryAllocator, 
    RFECS::SharedAttributePool& AttributePool)
{
    m_Allocator = &MemoryAllocator;
    m_AttributePool = &AttributePool;
}

void PhysicsAndAIManager::Process()
{
    RF_Algo::ForEach(m_PhysicComponents, [](RF_Collect::Array<PhysicBehaviour>::EnumeratorType& Enum) {
        Enum->Process(); });
    RF_Algo::ForEach(m_AIComponents, [](RF_Collect::Array<AIBehaviour>::EnumeratorType& Enum) {
        Enum->Process(); });
}

RF_Type::Bool PhysicsAndAIManager::AttachComponentOnEntity(RFECS::ComponentID Component, 
    RF_Mem::AutoPointerArray<RF_Type::UInt8>& ComponentData, RFECS::EntityID Entity,
    RFECS::SharedAttributePool& SharedAttributes)
{
    RF_Type::Bool result = false;
    switch(Component)
    {
    case CompontID::Physic:
        m_PhysicComponents.Resize(m_PhysicComponents.Count() + 1);
        m_PhysicComponents(m_PhysicComponents.Count() - 1).Setup(Entity, ComponentData,
            SharedAttributes);
        result = true;
        break;
    case CompontID::AI:
        m_AIComponents.Resize(m_AIComponents.Count() + 1);
        m_AIComponents(m_AIComponents.Count() - 1).Setup(Entity, ComponentData,
            SharedAttributes);
        result = true;
        break;
    }
    return result;
}

struct Allocator: public RFECS::Allocator
{
    virtual void* Allocate(RF_Type::Size Bytes, RF_Type::Size ByteAlignment)
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> newBlock(Bytes);
        void* result = newBlock.Get();
        m_ResizablePool.PushBack(newBlock);
        return result;
    }

    virtual void Free(void* MemoryBlock)
    {
        for(RF_Type::Size i = 0; i < m_ResizablePool.Count(); ++i)
        {
            if(m_ResizablePool[i] == MemoryBlock)
            {
                m_ResizablePool.Erase(i);
                break;
            }
        }
    }
private:
    RF_Collect::AutoVector<RF_Type::UInt8> m_ResizablePool;
};


class ComponentTest:public RF_Test::TestSuite
{
public:
    RF_Type::String txt;

    ComponentTest()
    :TestSuite("RadonFastEntityComponentSystem::Component")
    {
        AddTest(MakeDelegate(this, &ComponentTest::SingleThreaded), 
            "ComponentTest::SingleThreaded", "Process the components on a single core.");
        AddTest(MakeDelegate(this, &ComponentTest::MultiThreaded), 
            "ComponentTest::MultiThreaded", "Process the components on all available cores.");
    }

    void Setup(RFECS::Collector& collector)
    {
        RF_Mem::AutoPointer<RFECS::BaseComponentManager> renderManager(new RenderManager);
        RF_Mem::AutoPointer<RFECS::BaseComponentManager> physicsAndAIManager(new PhysicsAndAIManager);
        collector.RegisterComponentManager(physicsAndAIManager);
        collector.RegisterComponentManager(renderManager);
        for(RF_Type::Size i = 0; i < 1000;++i)
        {
            RF_Mem::AutoPointerArray<RF_Type::UInt8> data;
            collector.AttachComponentOnEntity(CompontID::Physic, data, i);
            collector.AttachComponentOnEntity(CompontID::AI, data, i);
            collector.AttachComponentOnEntity(CompontID::Render, data, i);
        }
    }

    RF_Type::Bool SingleThreaded()
    {
        RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance().DisableQueing();
        Allocator allocator;
        RFECS::Collector collector;
        collector.Setup(allocator);
        Setup(collector);

        collector.Process();
        RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance().EnableQueing();
        return true;
    }

    RF_Type::Bool MultiThreaded()
    {
        Allocator allocator;
        RFECS::Collector collector;
        collector.Setup(allocator);
        Setup(collector);

        collector.Process();
        return true;
    }
};




ComponentTest ComponentTestInstance;