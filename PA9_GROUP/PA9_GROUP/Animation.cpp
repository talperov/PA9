/*
As the rubric stated we were allowed to use AI to better our code, in order to better our code, we
used Generative AI (Grok) to add comments on our functions and variables so the reader of the code, or
writer themselves can easily understand what is going on in it.
*/

#include "Animation.hpp"
#include <iostream>
using std::cout;
using std::endl;

// Sets up a new empty animation
Animation::Animation()
{
    currentFrame = 0;      // Start showing the first frame
    timer = 0.0f;          // No time has passed yet
    frameTime = 0.1f;      // Each frame lasts 0.1 seconds by default
}

// Loads a sprite sheet and cuts it into individual frames
bool Animation::loadFromFile(const std::string& filename, int frameCount, int frameWidth, int frameHeight)
{
    // Try to load the big image
    bool loaded = texture.loadFromFile(filename);
    if (loaded == false)
    {
        cout << "Failed to load image: " << filename << endl;
        return false;      // Could not load the picture
    }

    frames.clear();        // Remove any old frames

    // Create a box for each frame (all in one row)
    for (int i = 0; i < frameCount; i = i + 1)
    {
        sf::IntRect frameRect;
        frameRect.left = i * frameWidth;   // Move right for each new frame
        frameRect.top = 0;
        frameRect.width = frameWidth;
        frameRect.height = frameHeight;
        frames.push_back(frameRect);       // Save the box
    }

    currentFrame = 0;      // Start at first frame again
    timer = 0.0f;
    return true;           // Everything worked!
}

// Moves the animation forward based on time passed
void Animation::update(float deltaTime)
{
    timer = timer + deltaTime;         // Count how much time passed this frame

    if (timer >= frameTime)            // Time to show next frame?
    {
        timer = 0.0f;                  // Reset timer
        currentFrame = currentFrame + 1; // Go to next frame

        // If we reached the end, go back to the first frame
        if (currentFrame >= static_cast<int>(frames.size()))
        {
            currentFrame = 0;
        }
    }
}

// Returns a sprite that shows the current frame
sf::Sprite Animation::getSprite() const
{
    sf::Sprite sprite;
    sprite.setTexture(texture);                    // Use the big sprite sheet
    sprite.setTextureRect(frames[currentFrame]);   // Show only the current frame
    return sprite;
}

// Puts the animation back to the very beginning
void Animation::reset()
{
    currentFrame = 0;
    timer = 0.0f;
}
