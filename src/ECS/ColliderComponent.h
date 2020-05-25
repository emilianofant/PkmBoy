#pragma once

#include <string>
#include "SDL2/SDL.h"
#include "Components.h"
#include "TextureManager.h"

/**
 * @brief This component defines a Collision behaviours for any entity that
 *        implements it.
 */
class ColliderComponent : public Component
{
public:
    /**
     * @brief The local reference to the SDL_Rect that the collider
     *        for the entity will represent. 
     */
    SDL_Rect collider;
    /**
     * @brief Collider's string identifier. 
     */
    std::string tag;
    /**
     * @brief Local reference to the SDL_Texture object from the library
     *        used to Draw the Collider's texture (if there is one).
     * @todo: validate if we really need this.
     */
    SDL_Texture* tex;
    /**
     * @brief Local reference to the source Rectangle that represents the
     *        collider graphically.
     */
    SDL_Rect srcR;
    /**
     * @brief Local reference to the destination Rectangle that represents the
     *        collider graphically.
     */ 
    SDL_Rect destR;
    /**
     * @brief Local reference to the Entity's TransformComponent.
     */
    TransformComponent* transform;

    /**
     * @brief Construct a new Collider Component object with only
     *        a tag parameter.
     * 
     * @param t String name identifier/tag.
     */
    ColliderComponent(std::string t)
    {
        tag = t;
    }

    /**
     * @brief Construct a new Collider Component object with a specific position
     *        and a square position (used in tiles).
     * 
     * @param t     String name identifier.
     * @param xpos  -x axis position of the Entity in the Game.
     * @param ypos  -y axis position of the Entity in the Game.
     * @param size  Texture/Entity size in pixels.
     */
    ColliderComponent(std::string t, int xpos, int ypos, int size)
    {
        tag = t;
        collider.x = xpos + 1;
        collider.y = ypos + 1;
        collider.h = collider.w = size - 1;
    }

    /**
     * @brief Construct a new Collider Component object with a specific position
     *        and a custom width/height. 
     * 
     * @param t           String name identifier.
     * @param xpos        -x axis position of the Entity in the Game.
     * @param ypos        -y axis position of the Entity in the Game.
     * @param widthSize   Texture/Entity width size in pixels.
     * @param heightSize  Texture/Entity height size in pixels.
     */
    ColliderComponent(std::string t, int xpos, int ypos, int heightSize, int widthSize)
    {
        tag = t;
        collider.x = xpos + 1;
        collider.y = ypos + 1;
        collider.h = heightSize - 1;
        collider.w = widthSize - 1;
    }

    void init() override
    {
        if (!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();

        // @todo: check of we can remove texture for the collition tile.
        //  this works just for validationg where the colliders are being positioned.
        tex = TextureManager::LoadTexture("assets/coltex.png");
        srcR = { 0, 0, 8, 8 };

        if(tag == "wall")
        {
            destR = { collider.x, collider.y, collider.w, collider.h};
        } else {
            destR = { collider.x, collider.y, collider.w * 2, collider.h * 2};
        }
    }

    void update() override
    {
        if(tag != "wall")
        {
            collider.x = static_cast<int>(transform->position.x) + 1;
            collider.y = static_cast<int>(transform->position.y) + 1;
            collider.w = (transform->width * transform->scale) - 1;
            collider.h = (transform->height * transform->scale) - 1;
        }

        destR.x = collider.x - Game::camera.x; 
        destR.y = collider.y - Game::camera.y; 
    }

    void draw () override
    {
        TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }

};
