#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
    static ComponentID lastID = 0u;

    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static_assert (std::is_base_of<Component, T>::value, "");
    static ComponentID typeID = getNewComponentTypeID(); // Generates a last ID

    return typeID;
}

/**
 * @brief Constant that defines the amount of maximum components that
 *        an entity can get.
 */
constexpr std::size_t maxComponents = 32;
/**
 * @brief Constant that defines the amount of maximum Groups
 */
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
/**
 * @brief Custom type, refeering to an Array of Component pointers/
 */
using ComponentArray = std::array<Component*, maxComponents>;

/**
 * @brief   Main definition of a Component, which will be the base class
 *          from which any other component will be created.
 */
class Component
{
public:
    /**
     * @brief Reference to it's Entity owner.
     */
    Entity* entity; // reference to its owner.

    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}

    virtual ~Component() {}
};

/**
 * @brief   The definition for any Entity int the application. The Entity is going
 *          to be fundamental unit for creating Game objects, having components that
 *          will define each entity's behaviours and characteristics.
 */
class Entity
{
private:
    /**
     * @brief Reference to the Entity's manager.
     */
	Manager& manager;
    /**
     * @brief Flag to determine if entity is active or not, in order
     *        to be able to remove from the game.
     */
    bool active = true;
    /**
     * @brief Vector of all the Component that are part of a specific
     *        entity.
     */
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitset;
    GroupBitSet groupBitSet;

public:
	Entity(Manager& mManager) : manager(mManager) {}

    // Entity Loop over all components and call the updates
    void update()
    {
        for(auto& c : components) c-> update();
    }
    void draw()
    {
        for(auto& c : components) c-> draw();
    }

    /**
     * @brief Method to get the if the Entity is active or not.
     *
     * @return true
     * @return false
     */
    bool isActive() const { return active; }

    /**
     * @brief Function to set the active status on false and
     *        remove/clear the Entity.
     */
    void destroy() { active = false; }


    bool hasGroup(Group mGroup)
    {
        return groupBitSet[mGroup];
    }

    void addGroup(Group mGroup);
    void delGroup(Group mGroup)
    {
        groupBitSet[mGroup] = false;
    }

    template <typename T> bool hasComponent() const
    {
        return componentBitset[getComponentTypeID<T>()];
    }

    // Add a component to the entity
    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr { c };
        components.emplace_back(std::move(uPtr));

        // When we add a position component, we are
        // adding at the same position in the array.
        componentArray[getComponentTypeID<T>()] = c;
        componentBitset[getComponentTypeID<T>()] = true;

        c->init();

        return *c;
    }

    template<typename T> T& getComponent() const
    {
        auto ptr(componentArray[getComponentTypeID<T>()]);

        return *static_cast<T*>(ptr);
    }
};

/**
 * @brief The Manager class is in charge of handling and overseeing
 *        all the Entities that are created, used and/or deleted
 *        through the game.
 */
class Manager
{
private:
    /**
     * @brief Local reference for the Entities that are created
     *        through the Game.
     */
    std::vector<std::unique_ptr<Entity>> entities;
    /**
     * @brief Local reference to an array storing the previous Entity's pointers
     *        that are being stored in specific group.
     */
    std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
    /**
     * @brief Iterate each Entity and run its update function.
     */
    void update()
    {
        for (auto& e: entities) e->update();
    }
    /**
     * @brief Iterate each Entity and run its draw function.
     */
    void draw()
    {
        for (auto& e: entities) e->draw();
    }
    /**
     * @brief Method to check within each Entity group, then through each
     *        Entity in order to evaluate its status, if is Active and/or
     *        if it has group assigned, in order to remove it.
     *
     */
    void refresh()
    {
        for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
			{
				return !mEntity->isActive() || !mEntity->hasGroup(i);
			}),
				std::end(v));
		}
        entities.erase(std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr<Entity> &mEntity)
        {
            return !mEntity->isActive();
        }),
            std::end(entities));
    }
    /**
     * @brief Method to add an Entity to a specific Entity Group.
     *
     * @param mEntity   Pointer reference to a specific Entity.
     * @param mGroup    Reference to an Entity Group where the Entity
     *                  is going to be added.
     */
    void AddToGroup(Entity* mEntity, Group mGroup)
    {
        groupedEntities[mGroup].emplace_back(mEntity);
    }
    /**
     * @brief Get the Group object.
     *
     * @param mGroup Target Entity Group to be returned.
     *
     * @return std::vector<Entity*>&
     */
    std::vector<Entity*>& getGroup(Group mGroup)
    {
        return groupedEntities[mGroup];
    }
    /**
     * @brief Method to add an Entity to the Entity vector.
     *
     * @return Entity& Return Entity's pointer reference.
     */
    Entity& addEntity()
    {
        Entity* e = new Entity(*this);
        std::unique_ptr<Entity> uPtr { e };
        entities.emplace_back(std::move(uPtr));

        return *e;
    }
};

