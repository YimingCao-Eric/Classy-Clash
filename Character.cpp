#include "Character.h"
// Raylib math utilities for vector operations
#include "raymath.h"

/**
 * Constructor implementation
 * Initializes the player character with window dimensions and calculates sprite dimensions
 * @param windowWidth Width of the game window
 * @param windowHeight Height of the game window
 */
Character::Character(int windowWidth, int windowHeight):
    windowWidth(windowWidth),
    windowHeight(windowHeight)
{
    // Calculate width of a single frame from the spritesheet
    // Spritesheet contains multiple frames horizontally
    width = texture.width/maxFrames;
    // Height is the full height of the texture (single row spritesheet)
    height = texture.height;
}

/**
 * getScreenPos implementation
 * Calculates the screen position of the character
 * Player is always centered on screen, so position is calculated from window center
 * @return Vector2 representing the character's position in screen coordinates
 */
Vector2 Character::getScreenPos() {
    // Center the character on screen by:
    // 1. Start at window center (windowWidth/2, windowHeight/2)
    // 2. Offset by half the scaled character size to center the sprite
    return Vector2{
        static_cast<float>(windowWidth) * 0.5f - scale * width * 0.5f,   // X: center - half sprite width
        static_cast<float>(windowHeight) * 0.5f - scale * height * 0.5f  // Y: center - half sprite height
    };
}

/**
 * tick implementation
 * Updates the player character each frame
 * Handles input, movement, weapon rendering, and calls base class update
 * @param deltaTime Time elapsed since last frame
 */
void Character::tick(float deltaTime){
    // Skip update if character is dead
    if (!getAlive()) return;

    // Handle keyboard input to set movement velocity
    // WASD controls: W=up, S=down, A=left, D=right
    if (IsKeyDown(KEY_A)) velocity.x += -1.0;  // Move left
    if (IsKeyDown(KEY_D)) velocity.x += 1.0;    // Move right
    if (IsKeyDown(KEY_W)) velocity.y += -1.0;   // Move up (negative Y is up in screen space)
    if (IsKeyDown(KEY_S)) velocity.y += 1.0;    // Move down
    
    // Call base class tick to handle movement, animation, and base rendering
    BaseCharacter::tick(deltaTime);

    // Weapon rendering and collision setup
    Vector2 origin{};      // Rotation origin point for weapon
    Vector2 offset{};      // Offset from character position to weapon position
    float rotation{};      // Rotation angle for weapon (swing animation)
    
    // Calculate weapon position and collision based on facing direction
    // facing right
    if (rightLeft > 0.f) {
        // Set rotation origin to bottom-left of weapon (for right-facing rotation)
        origin = {0.f, weapon.height * scale};
        // Offset weapon position relative to character (to the right side)
        offset = {35.f, 55.f};
        // Calculate weapon collision rectangle in screen space
        weaponCollisionRec = {
            getScreenPos().x + offset.x,                                    // X position
            getScreenPos().y + offset.y - weapon.height * scale,           // Y position (adjusted for origin)
            weapon.width * scale,                                           // Scaled width
            weapon.height * scale                                           // Scaled height
        };
        // Rotate weapon when attacking (left mouse button pressed)
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? 35.f : 0.f;
    } 
    // facing left
    else {
        // Set rotation origin to bottom-right of weapon (for left-facing rotation)
        origin = {weapon.width * scale, weapon.height * scale};
        // Offset weapon position relative to character (to the left side)
        offset = {25.f, 55.f};
        // Calculate weapon collision rectangle (adjusted for left-facing)
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale,            // X position (adjusted for left-facing)
            getScreenPos().y + offset.y - weapon.height * scale,           // Y position
            weapon.width * scale,                                           // Scaled width
            weapon.height * scale                                           // Scaled height
        };
        // Rotate weapon when attacking (negative rotation for left-facing)
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? -35.f : 0.f;
    }
    
    // Prepare source rectangle from weapon texture (flip horizontally if facing left)
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    // Prepare destination rectangle for rendering weapon on screen
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    // Draw the weapon texture with rotation and proper origin point
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

}

/**
 * takeDamage implementation
 * Applies damage to the character and checks if character should die
 * @param damage Amount of damage to apply
 */
void Character::takeDamage(float damage){
    // Reduce health by damage amount
    health -= damage;
    // Check if health has reached zero or below
    if (health <= 0.f) {
        // Set character as dead
        setAlive(false);
    }
}