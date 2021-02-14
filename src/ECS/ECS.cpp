#include <ECS/ECS.hpp>

void Entity::AddGroup(Group group) {
  mGroupBitset[group] = true;
  manager.AddToGroup(this, group);
}
