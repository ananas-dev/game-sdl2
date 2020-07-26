#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentId = std::size_t;

inline ComponentId GetComponentTypeId()
{
    static ComponentId lastId = 0;
    return lastId++;
}

template <typename T> inline ComponentId GetComponentTypeId() noexcept
{
    static ComponentId typeId = GetComponentTypeId();
    return typeId;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
    public:
        Entity* entity;

        virtual void Init() {}
        virtual void Update() {}
        virtual void Draw() {}

        virtual ~Component() {}
};

class Entity
{
    private:
        bool active_ = true;
        std::vector<std::unique_ptr<Component>> components_;

        ComponentArray componentArray_;
        ComponentBitSet componentBitset_;

    public:
        void Update()
        {
            for (auto& c : components_) c->Update();
        }
        void Draw()
        {
            for (auto& c : components_) c->Draw();
        }
        bool IsActive() { return active_; }
        void Destroy() { active_ = false; }

        template <typename T>
        bool HasComponent() const
        {
            return componentBitset_[GetComponentTypeId<T>()];
        }

        template <typename T, typename... Targs>
        T& AddComponent(Targs&&... mArgs)
        {
            T* c(new T(std::forward<Targs>(mArgs)...));
            c->entity = this;
            std::unique_ptr<Component> uPtr{c};
            components_.emplace_back(std::move(uPtr));

            componentArray_[GetComponentTypeId<T>()] = c;
            componentBitset_[GetComponentTypeId<T>()] = true;

            c->Init();
            return *c;

        }

        template <typename T>
        T& GetComponent() const
        {
            auto ptr(componentArray_[GetComponentTypeId<T>()]);
            return *static_cast<T*>(ptr);
        }
};

class Manager
{
    private:
        std::vector<std::unique_ptr<Entity>> entities_;

    public:
        void Update()
        {
            for (auto& e : entities_ ) e->Update();
        }
        void Draw()
        {
            for (auto& e : entities_ ) e->Draw();
        }
        void Refresh()
        {
            entities_.erase(std::remove_if(std::begin(entities_), std::end(entities_),
                                           [](const std::unique_ptr<Entity> &mEntity)
                                           {
                                               return !mEntity->IsActive();
                                           }),
                            std::end(entities_));
        }
        Entity& AddEntity()
        {
            Entity* e = new Entity();
            std::unique_ptr<Entity> uPtr{e};
            entities_.emplace_back(std::move(uPtr));
            return *e;
        }
};
