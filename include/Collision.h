#pragma once
#include "SDL.h"

class ColliderComponent;

/**
 * @brief This class defines Collisions that are going to be implemented
 *        in the game. Currently only defines an AABB type collision.
 */
class Collision
{
public:
    /**
     * @brief Method to validate a Collision between two Game objects.
     * 
     * @param recA SDL_Rect corresponding to the first Game object.
     * @param recB SDL_Rect corresponding to the second Game object.
     * 
     * @return true  If collision occurs. 
     * @return false If collision does not occurs.
     */
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
    
    /**
     * @brief Define the comparison between two ColliderComponent in order to 
     *        get if a Collision state occurs.
     * 
     * @param colA ColliderComponent from the first Object.
     * @param colB ColliderComponent from the second Object.
     * 
     * @return true  If collision occurs. 
     * @return false If collision does not occurs.
     */
    static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};