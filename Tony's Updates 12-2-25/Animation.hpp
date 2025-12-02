/*
As the rubric stated we were allowed to use AI to better our code, in order to better our code, we
used Generative AI (Grok) to add comments on our functions and variables so the reader of the code, or
writer themselves can easily understand what is going on in it.
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Animation
{
private:
    sf::Texture texture; // Full sprite sheet (the big picture with all frames)
    std::vector<sf::IntRect> frames; // List of boxes that mark each frame in the sheet
    float timer; // Counts time to know when to switch to the next frame
    float frameTime; // How long each frame stays on screen (in seconds)

public:
    int currentFrame; // Which frame we are showing right now (0 = first frame)

    Animation(); // Sets up a new animation

    bool loadFromFile(const std::string& filename, int frameCount, int frameWidth, int frameHeight); // Loads the sprite sheet and cuts it into frames

    void update(float deltaTime); // Checks if enough time passed and moves to next frame
    
    sf::Sprite getSprite() const; // Gives back a sprite that shows the current frame
    
    void reset(); // Starts the animation over from the first frame
    
    //Helper to make the frames look more smoothish
    void forceFrame(int index) { currentFrame = index; } // Quickly changes to any frame you choose
};