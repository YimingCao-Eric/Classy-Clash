#include "Enemy.h"
// Raylib math utilities for vector operations
#include "raymath.h"

/**
 * Constructor implementation
 * Initializes the enemy with custom textures, position, and properties
 * @param idle_texture Texture for idle animation
 * @param run_texture Texture for running animation
 * @param pos Starting world position of the enemy
 */
Enemy::Enemy(Texture2D idle_texture, Texture2D run_texture, Vector2 pos)
{
    // Set current texture to idle (initial state)
    texture = idle_texture;
    // Store idle texture for animation switching
    idle = idle_texture;
    // Store run texture for animation switching
    run = run_texture;
    // Set the enemy's starting world position
    worldPos = pos;
    // Calculate width of a single frame from the spritesheet
    // Spritesheet contains multiple frames horizontally
    width = texture.width / maxFrames;
    // Height is the full height of the texture (single row spritesheet)
    height = texture.height;
    // Set enemy movement speed (slower than player for balance)
    speed = 3.f;
}

/**
 * getScreenPos implementation
 * Calculates the screen position of the enemy
 * Position is relative to the player's world position (camera follows player)
 * @return Vector2 representing the enemy's position in screen coordinates
 */
Vector2 Enemy::getScreenPos() {
    // Convert world position to screen position by subtracting target's world position
    // This creates a camera effect where enemies move relative to the player
    return Vector2Subtract(worldPos, target->getWorldPos());
}

/**
 * tick implementation
 * Updates the enemy each frame
 * Handles AI movement toward target, collision detection, and damage dealing
 * @param deltaTime Time elapsed since last frame
 */
void Enemy::tick(float deltaTime) {
    // Skip update if enemy is dead
    if (!getAlive()) return;
    
    // Calculate direction vector from enemy to target (player)
    // This creates the chasing behavior - enemy moves toward player
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    
    // Stop moving if enemy is within attack radius of the target
    // Prevents enemies from overlapping with player
    if (Vector2Length(velocity) < radius) {
        velocity = {};  // Set velocity to zero (stop moving)
    };

    // Call base class tick to handle movement, animation, and rendering
    BaseCharacter::tick(deltaTime);
    
    // Check for collision between enemy and target (player)
    if (CheckCollisionRecs(GetCollisionRec(), target->GetCollisionRec())) {
        // Apply damage to player when in contact
        // Damage is scaled by deltaTime for frame-rate independent damage
        target->takeDamage(damagePerSec * deltaTime);
    }
}
