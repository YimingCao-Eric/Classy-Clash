// Header guard to prevent multiple inclusions
#ifndef CHARACTER_H
#define CHARACTER_H

// Raylib library for graphics, textures, and vector/math types
#include "raylib.h"
// Base class for character functionality
#include "BaseCharacter.h"

/**
 * Character class
 * Represents the player character (knight) in the game
 * Inherits from BaseCharacter and adds player-specific features:
 * - Health system
 * - Weapon rendering and collision
 * - Screen position calculation (centered on player)
 */
class Character: public BaseCharacter {
    public:
        /**
         * Constructor
         * Initializes the player character with window dimensions
         * @param windowWidth Width of the game window (for screen position calculation)
         * @param windowHeight Height of the game window (for screen position calculation)
         */
        Character(int windowWidth, int windowHeight);
        
        /**
         * Override of BaseCharacter::tick
         * Updates the player character each frame
         * Handles input, movement, weapon rendering, and calls base class tick
         * @param deltaTime Time elapsed since last frame
         */
        virtual void tick(float deltaTime) override;
        
        /**
         * Override of BaseCharacter::getScreenPos (pure virtual)
         * Calculates the screen position of the character
         * Player is always centered on screen, so screen position is calculated from window center
         * @return Vector2 representing the character's position in screen coordinates
         */
        virtual Vector2 getScreenPos() override;
        
        /**
         * Gets the collision rectangle for the character's weapon
         * Used for combat collision detection with enemies
         * @return Rectangle representing the weapon's collision bounds
         */
        Rectangle getWeaponCollisionRec(){ return weaponCollisionRec; }
        
        /**
         * Gets the current health of the character
         * @return Current health value (0-100)
         */
        float getHealth() const { return health; }
        
        /**
         * Applies damage to the character
         * Reduces health and may set character as dead if health reaches 0
         * @param damage Amount of damage to apply
         */
        void takeDamage(float damage);
        
    private:
        // Width of the game window (used for centering player on screen)
        int windowWidth{};
        // Height of the game window (used for centering player on screen)
        int windowHeight{};
        // Texture for the weapon (sword)
        Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
        // Collision rectangle for the weapon (updated each frame based on position and facing)
        Rectangle weaponCollisionRec{};
        // Current health value (starts at 100, character dies when it reaches 0)
        float health{100.f};
};

#endif