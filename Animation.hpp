#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Animation
{
private:
    sf::Texture texture;               // Full sprite sheet
    std::vector<sf::IntRect> frames;   // Frames in the sheet
    int currentFrame;                   // Current frame index
    float timer;                        // Timer for animation
    float frameTime;                    // Time per frame

public:
    Animation();
    bool loadFromFile(const std::string& filename, int frameCount, int frameWidth, int frameHeight);
    void update(float deltaTime);
    sf::Sprite getSprite() const;
    void reset();

    // New helper to force a frame (for fake jump)
    void forceFrame(int index) { currentFrame = index; }
};
