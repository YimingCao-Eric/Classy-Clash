// Header guard to prevent multiple inclusions
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

// Raylib library for graphics, textures, and vector/math types
#include "raylib.h"

/**
 * BaseCharacter class
 * Base class for all characters in the game (player, enemies, etc.)
 * Provides common functionality for movement, animation, collision detection, and rendering
 * Uses virtual methods to allow derived classes to customize behavior
 */
class BaseCharacter {  
    public:
        /**
         * Default constructor
         * Initializes the base character with default values
         */
        BaseCharacter();
        
        /**
         * Gets the character's world position
         * @return Vector2 representing the character's position in world coordinates
         */
        Vector2 getWorldPos(){ return worldPos; }
        
        /**
         * Reverts the character's position to the previous frame's position
         * Used for collision handling and boundary checking
         */
        void undoMovement();
        
        /**
         * Gets the collision rectangle for this character
         * @return Rectangle representing the character's collision bounds
         */
        Rectangle GetCollisionRec();
        
        /**
         * Virtual update method - called every frame
         * Derived classes should override this to implement their specific update logic
         * @param deltaTime Time elapsed since last frame (for frame-rate independent movement)
         */
        virtual void tick(float deltaTime);
        
        /**
         * Pure virtual method - must be implemented by derived classes
         * Calculates the screen position based on world position and camera offset
         * @return Vector2 representing the character's position in screen coordinates
         */
        virtual Vector2 getScreenPos() = 0;
        
        /**
         * Gets the alive status of the character
         * @return true if character is alive, false if dead
         */
        bool getAlive(){ return alive; }
        
        /**
         * Sets the alive status of the character
         * @param isAlive true to set character as alive, false to set as dead
         */
        void setAlive(bool isAlive){ alive = isAlive; }

    protected:
        // Current texture being used for rendering (switches between idle/run)
        Texture2D texture{ LoadTexture("characters/knight_idle_spritesheet.png") };
        // Texture for idle animation
        Texture2D idle{ LoadTexture("characters/knight_idle_spritesheet.png") };
        // Texture for running animation
        Texture2D run{ LoadTexture("characters/knight_run_spritesheet.png") };

        // Current position in world coordinates
        Vector2 worldPos{0.f, 0.f};
        // Position from the previous frame (used for movement undo)
        Vector2 worldPosLastFrame{0.f, 0.f};

        // Direction facing: 1.0 = facing right, -1.0 = facing left
        float rightLeft{1.f};
        // Accumulated time for animation frame calculation
        float runningTime{0.f}; 
        // Current animation frame index
        int frame{0};
        // Total number of frames in the animation spritesheet
        int maxFrames{6};
        // Time between animation frame updates (1/12 = 12 frames per second)
        float updateTime{1.f/12.f}; 
        // Movement speed in pixels per frame
        float speed{4.f};

        // Width of the character texture (calculated from texture)
        float width{0.f};
        // Height of the character texture (calculated from texture)
        float height{0.f};
        // Scale factor for rendering the character texture
        float scale{4.f};

        // Current velocity vector (direction and speed of movement)
        Vector2 velocity{0.f, 0.f};

    private:
        // Whether the character is currently alive or dead
        bool alive{true};
};

#endif