/**
 * @brief
 * The Entity-Component-System (ECS) pattern separates data (components) from behavior (systems) and identifies objects (entities)
 * by IDs. It improves cache locality, flexibility, and decouples systems for better performance and scalability.
 * 
 * Key Concepts:
 * - Entity: A unique identifier representing an object in the world.
 * - Component: Plain data associated with entities (no logic).
 * - System: Operates on entities with specific components.
 * 
 * Benefits:
 * - Improved cache locality by storing components contiguously.
 * - Flexible composition of behavior by mixing components.
 * - Decouples data and logic for better maintainability and testing.
 */

#include <iostream>
#include <memory>
#include <vector>

/**
 * @brief Simple data component representing position.
 */
struct Position
{
    float x{}, y{};
};

/**
 * @brief Simple data component representing velocity.
 */
struct Velocity
{
    float dx{}, dy{};
};

/**
 * @brief Alias for entity identifier.
 */
using Entity = std::size_t;

/**
 * @brief ECS world managing entities and their components.
 */
class World
{
public:
    /**
     * @brief Creates a new entity.
     * @return The ID of the newly created entity.
     */
    Entity createEntity()
    {
        Entity id = m_nextEntityId++;
        if (id >= m_entityExists.size())
        {
            m_entityExists.resize(id + 1, true);
            m_positions.resize(id + 1);
            m_velocities.resize(id + 1);
        }
        else
        {
            m_entityExists[id] = true;
        }
        return id;
    }

    /**
     * @brief Adds a component of type T to the given entity.
     * @tparam T The component type.
     * @param entity The target entity.
     * @param component The component instance to store.
     */
    template <typename T>
    void addComponent(Entity entity, const T &component)
    {
        auto &storage = getComponentStorage<T>();
        if (entity >= storage.size())
        {
            storage.resize(entity + 1);
        }
        storage[entity] = std::make_shared<T>(component);
    }

    /**
     * @brief Gets the component of type T for a given entity.
     * @tparam T The component type.
     * @param entity The target entity.
     * @return A shared_ptr to the component.
     */
    template <typename T>
    std::shared_ptr<T> getComponent(Entity entity)
    {
        auto &storage = getComponentStorage<T>();
        if (entity < storage.size())
        {
            return storage[entity];
        }
        return nullptr;
    }

    /**
     * @brief Runs an update on all entities having both Position and Velocity components.
     */
    void update()
    {
        for (Entity id = 0; id < m_nextEntityId; ++id)
        {
            if (!m_entityExists[id])
            {
                continue;
            }

            auto pos = getComponent<Position>(id);
            auto vel = getComponent<Velocity>(id);
            if (pos && vel)
            {
                pos->x += vel->dx;
                pos->y += vel->dy;
                std::cout << "Entity " << id << " moved to (" << pos->x << ", " << pos->y << ")\n";
            }
        }
    }

private:
    Entity m_nextEntityId{0};
    std::vector<bool> m_entityExists;
    std::vector<std::shared_ptr<Position>> m_positions;
    std::vector<std::shared_ptr<Velocity>> m_velocities;

    template <typename T>
    std::vector<std::shared_ptr<T>> &getComponentStorage(); ///< Declared only
};

// --- Specializations for Component Storage ---

template <>
std::vector<std::shared_ptr<Position>> &World::getComponentStorage<Position>()
{
    return m_positions;
}

template <>
std::vector<std::shared_ptr<Velocity>> &World::getComponentStorage<Velocity>()
{
    return m_velocities;
}

// --- Main ---

int main()
{
    World world;

    auto entity1 = world.createEntity();
    world.addComponent(entity1, Position{0.0f, 0.0f});
    world.addComponent(entity1, Velocity{1.0f, 1.5f});

    auto entity2 = world.createEntity();
    world.addComponent(entity2, Position{5.0f, 5.0f});
    world.addComponent(entity2, Velocity{-0.5f, 0.5f});

    world.update();

    return 0;
}
