#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <memory>
#include <vector>

class Component;
class Entity;
class Manager;

using ComponentId = std::size_t;
using Group = std::size_t;

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

inline ComponentId GetNewComponentTypeId() {
  static ComponentId lastId = 0;
  return lastId++;
}

template <typename T>
inline ComponentId GetComponentTypeId() noexcept {
  static ComponentId typeId = GetNewComponentTypeId();
  return typeId;
}

using ComponentBitset = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

class Component {
 public:
  Entity* entity;

  virtual void Init() {}
  virtual void Update() {}
  virtual void Draw() {}

  virtual ~Component() {}
};

//////////////
/// ENTITY ///
//////////////

class Entity {
 private:
  Manager& manager;
  bool mActive = true;
  std::vector<std::unique_ptr<Component>> mComponents;

  ComponentArray mComponentArray;
  ComponentBitset mComponentBitset;
  GroupBitset mGroupBitset;

 public:
  Entity(Manager& mManager) : manager(mManager) {}

  void Update() {
    for (auto& component : mComponents) {
      component->Update();
    }
  }

  void Draw() {
    for (auto& component : mComponents) {
      component->Draw();
    }
  }

  bool IsActive() { return mActive; }

  void Destroy() { mActive = false; }

  bool HasGroup(Group group) { return mGroupBitset[group]; }

  void AddGroup(Group group);

  void DelGroup(Group group) { mGroupBitset[group] = false; }

  template <typename T>
  bool HasComponent() const {
    return mComponentBitset[GetComponentTypeId<T>()];
  }

  template <typename T, typename... Targs>
  T& AddComponent(Targs&&... mArgs) {
    T* c(new T(std::forward<Targs>(mArgs)...));
    c->entity = this;
    std::unique_ptr<Component> uPtr{c};
    mComponents.emplace_back(std::move(uPtr));

    mComponentArray[GetComponentTypeId<T>()] = c;
    mComponentBitset[GetComponentTypeId<T>()] = true;

    c->Init();
    return *c;
  }

  template <typename T>
  T& GetComponent() const {
    auto ptr(mComponentArray[GetComponentTypeId<T>()]);
    return *static_cast<T*>(ptr);
  };
};

///////////////
/// MANAGER ///
///////////////

class Manager {
 private:
  std::vector<std::unique_ptr<Entity>> mEntities;
  std::array<std::vector<Entity*>, maxGroups> mGroupedEntities;

 public:
  void Update() {
    for (auto& entities : mEntities) {
      entities->Update();
    }
  }

  void Draw() {
    for (auto& entities : mEntities) {
      entities->Draw();
    }
  }

  void Refresh() {
    for (auto i(0u); i < maxGroups; i++) {
      auto v(mGroupedEntities[i]);
      v.erase(std::remove_if(std::begin(v), std::end(v),
                             [i](Entity* entity) {
                               return entity->IsActive() || entity->HasGroup(i);
                             }),
              std::end(v));
    }

    mEntities.erase(std::remove_if(std::begin(mEntities), std::end(mEntities),
                                   [](const std::unique_ptr<Entity>& mEntity) {
                                     return !mEntity->IsActive();
                                   }),
                    std::end(mEntities));
  }

  void AddToGroup(Entity* entity, Group group) {
    mGroupedEntities[group].emplace_back(entity);
  }

  std::vector<Entity*>& GetGroup(Group group) {
    return mGroupedEntities[group];
  }

  Entity& AddEntity() {
    Entity* entity = new Entity(*this);
    std::unique_ptr<Entity> uPtr{entity};
    mEntities.emplace_back(std::move(uPtr));
    return *entity;
  }
};
