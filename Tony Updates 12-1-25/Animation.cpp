#include "Animation.hpp"
#include <iostream>

using std::cout;
using std::endl;

// -------------------------
// Constructor
// -------------------------
Animation::Animation()
{
    currentFrame = 0;        // Start at first frame
    timer = 0.0f;            // Timer for animation frame changes
    frameTime = 0.1f;        // Default time per frame (0.1 seconds)
}

// -------------------------
// Load animation from file
// -------------------------
bool Animation::loadFromFile(const std::string& filename, int frameCount, int frameWidth, int frameHeight)
{
    // Load the texture
    bool loaded = texture.loadFromFile(filename);

    if (loaded == false)
    {
        cout << "Failed to load image: " << filename << endl;
        return false;
    }

    // Clear any previous frames
    frames.clear();

    // Add each frame as a rectangle
    for (int i = 0; i < frameCount; i = i + 1)
    {
        sf::IntRect frameRect;
        frameRect.left = i * frameWidth;
        frameRect.top = 0;
        frameRect.width = frameWidth;
        frameRect.height = frameHeight;

        frames.push_back(frameRect);
    }

    // Reset animation
    currentFrame = 0;
    timer = 0.0f;

    return true;
}

// -------------------------
// Update animation frame
// -------------------------
void Animation::update(float deltaTime)
{
    // Add elapsed time
    timer = timer + deltaTime;

    // Check if it's time to switch to the next frame
    if (timer >= frameTime)
    {
        timer = 0.0f;

        // Advance to next frame, loop back if at end
        currentFrame = currentFrame + 1;

        if (currentFrame >= static_cast<int>(frames.size()))
        {
            currentFrame = 0;
        }
    }
}

// -------------------------
// Get current sprite
// -------------------------
sf::Sprite Animation::getSprite() const
{
    sf::Sprite sprite;

    sprite.setTexture(texture);
    sprite.setTextureRect(frames[currentFrame]);

    return sprite;
}

// -------------------------
// Reset animation to first frame
// -------------------------
void Animation::reset()
{
    currentFrame = 0;
    timer = 0.0f;
}
