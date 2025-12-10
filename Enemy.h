// Raylib library for graphics, textures, and vector/math types
#include "raylib.h"
// Base class for character functionality
#include "BaseCharacter.h"
// Character class (player) - needed for targeting
#include "Character.h"

/**
 * Enemy class
 * Represents hostile enemies in the game (e.g., goblins, slimes)
 * Inherits from BaseCharacter and adds enemy-specific AI behavior:
 * - Automatic targeting and movement toward player
 * - Damage dealing on contact
 * - Custom textures for different enemy types
 */
class Enemy: public BaseCharacter {  
    public:
        /**
         * Constructor
         * Initializes the enemy with custom textures and starting position
         * @param idle_texture Texture for idle animation
         * @param run_texture Texture for running animation
         * @param pos Starting world position of the enemy
         */
        Enemy(Texture2D idle_texture, Texture2D run_texture, Vector2 pos);
        
        /**
         * Override of BaseCharacter::tick
         * Updates the enemy each frame
         * Handles AI movement toward target, collision detection, and damage dealing
         * @param deltaTime Time elapsed since last frame
         */
        virtual void tick(float deltaTime) override;
        
        /**
         * Sets the target character for the enemy to chase
         * @param character Pointer to the Character object to target (usually the player)
         */
        void setTarget(Character* character) { target = character; }
        
        /**
         * Override of BaseCharacter::getScreenPos (pure virtual)
         * Calculates the screen position of the enemy
         * Position is relative to the player's world position (camera offset)
         * @return Vector2 representing the enemy's position in screen coordinates
         */
        virtual Vector2 getScreenPos() override;
        
    private:
        // Pointer to the target character (player) that this enemy will chase
        Character* target;
        // Damage per second that the enemy deals when in contact with the player
        float damagePerSec{10.f};
        // Radius around the enemy for collision/damage detection
        float radius{25.f};
};