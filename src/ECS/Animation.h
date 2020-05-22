#pragma once

/**
 * @brief Struct definition for Animation related capabilities.
 */
struct Animation
{
    /**
     * @brief -x axis position in a texture file from where
     *        the animation starts (1st frame).  
     */
    int index;
    /**
     * @brief Reference to the amount of frames that an animation
     *        is composed with.
     */
    int frames;
    /**
     * @brief Amount of milliseconds an each frame should last
     *        within an Animation cycle. 
     */
    int speed;

    /**
     * @brief Construct a new Animation object
     */
    Animation() {}
    /**
     * @brief Construct a new Animation object with parameteres.
     * 
     * @param i  Texture's -x axis position index.
     * @param f  Amount of frames to read form the texture's file.
     * @param s  Each frame duration in milliseconds.
     */
    Animation(int i, int f, int s)
    {
        index = i;
        frames = f;
        speed = s;
    }
};