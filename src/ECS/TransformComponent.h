#pragma once
#include "Components.h"
#include "Vector2D.h"
#include <map>

/**
 * @brief This component is in charge of any movement or
 * entity/texture/sprite position change through the game.
 */
struct TransformComponent : public Component
{
private:
    /**
     * @brief Flag that defines if the Entity is moving. 
     */
    bool _isMoving = false;
    /**
     * @brief Vector defining the destination position. 
     */
    Vector2D _destPosition;
    /**
     * @brief Reference to the latest safe position (no collision). 
     */
    Vector2D _latestSafePosition;
    /**
     * @brief Map definition of the possible movements directions.
     */
    std::map<std::string, int> _DIRECTIONS_MAP = {
        {"DIR_LEFT", -1},
        {"DIR_RIGHT", 1},
        {"DIR_UP", -1},
        {"DIR_DOWN", 1}
    };

public:
    /**
     * @brief Local reference to the position in X and Y. 
     */
    Vector2D position;
    /**
     * @brief Local reference of the values of X and Y velocity. 
     */
    Vector2D velocity;
    /**
     * @brief Sprite heigh in pixels.
     */
    int height = 16;
    /**
     * @brief Sprite width in pixels.
     */
    int width = 16;
    /**
     * @brief Sprite texture scaling.
     */
    int scale = 1;
    /**
     * @brief Sprite constant value to move.
     */
    float speed = 1;

    /**
     * @brief Construct a new Transform Component object with default
     *        values.
     */
    TransformComponent()
    {
        position.Zero();
    }
    
    /**
     * @brief Construct a new Transform Component object with a scaling
     *        value set, which should be related to the UI scaling factor.
     * 
     * @param x   Position in -x axis.
     * @param y   Position in -y axis.
     * @param sc  Integer value for scaling.
     */
    TransformComponent(float x, float y, int sc)
    {
        position.x = x;
        position.y = y;
        scale = sc;
    }
    
    /**
     * @brief Construct a new Transform Component object, with the Sprite/Tile
     *        pixels width and height.
     * 
     * @param x   Position in -x axis.
     * @param y   Position in -y axis.
     * @param h   Sprite/Tile height in pixels
     * @param w   Sprite/Tile width in pixels
     * @param sc  Integer value for scaling.
     */
    TransformComponent(float x, float y, int h, int w, int sc)
    {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = sc;
    }

    void init() override
    {
        velocity.x = 0;
        velocity.y = 0;

         _destPosition.x = position.x;
         _destPosition.y = position.y;
    }

    /**
     * @brief In this implementation, the update will check if the
     *        entity has a destination in any axis, and will perform 
     *        the movement in case the actual position doesn't match 
     *        the destination position.
     */
    void update() override
    {
        if (position.x != _destPosition.x) {
            // Check if moving in -x axis
            _isMoving = true;
            position.x += velocity.x * speed;
        } else if (position.y != _destPosition.y) {
            // Check if moving in -y axis
            _isMoving = true;
            position.y += velocity.y * speed;
        } else {
            _isMoving = false;
            _latestSafePosition = position;
        }
    }

    /**
     * @brief This method defines how an Entity will move in a 
     *        fixed motion.
     * 
     * @param dir  String defining movement direction. 
     */
    void fixedMovement(std::string dir)
    {
        if(!_isMoving) {
            /**
             * Sets a specific destination position in the -x axis
             * towards which the player is going to be moving.
             */
            if (dir == "DIR_UP" || dir == "DIR_DOWN") {
                int y = _DIRECTIONS_MAP[dir];
                _destPosition.y = position.y + (y * height * scale); 
                _destPosition.x = position.x; 
                velocity.y = y;
            }
            /**
             * Sets a specific destination position in the -y axis
             * towards which the player is going to be moving.
             */
            if (dir == "DIR_LEFT" || dir == "DIR_RIGHT") {
                int x = _DIRECTIONS_MAP[dir];
                _destPosition.x = position.x + (x * width * scale); 
                _destPosition.y = position.y; 
                velocity.x = x;
            }
        }
    }

    /**
     * @brief Function to reset the current destination Position
     *        in case of collision.  
     */
    void resetDestinationPosition()
    {
        position = _latestSafePosition;
        _destPosition = position;
    }
};

