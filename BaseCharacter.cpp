#include "BaseCharacter.h"
// Raylib math utilities for vector operations
#include "raymath.h"

/**
 * Constructor implementation
 * Initializes the base character with default values
 * Member variables are initialized in the header file with default values
 */
BaseCharacter::BaseCharacter() {
    // Default initialization handled by member initializers in header
}

/**
 * undoMovement implementation
 * Reverts the character's position to the previous frame's position
 * Called when collision is detected or character moves out of bounds
 */
void BaseCharacter::undoMovement(){
    // Restore position from before the current frame's movement
    worldPos = worldPosLastFrame;
}

/**
 * GetCollisionRec implementation
 * Calculates the collision rectangle for this character in screen space
 * @return Rectangle representing the character's collision bounds in screen coordinates
 */
Rectangle BaseCharacter::GetCollisionRec(){
    // Return rectangle with screen position and scaled dimensions
    return Rectangle{
        getScreenPos().x,        // X position in screen space
        getScreenPos().y,        // Y position in screen space
        scale* width,            // Width scaled by character's scale factor
        scale* height            // Height scaled by character's scale factor
    };
}

/**
 * tick implementation
 * Main update method called every frame
 * Handles animation, movement, and rendering
 * @param deltaTime Time elapsed since last frame (for frame-rate independent updates)
 */
void BaseCharacter::tick(float deltaTime){
    // Save current position before any movement (for potential undo)
    worldPosLastFrame = worldPos;
    
    // Update the animation frame based on elapsed time
    runningTime += deltaTime;
    // Advance to next frame when enough time has passed
    if (runningTime >= updateTime) {
        frame++;
        runningTime = 0.f;  // Reset timer for next frame
    }
    // Loop animation back to first frame when reaching the end
    if (frame >= maxFrames) {
        frame = 0;
    }   

    // Handle movement and animation state based on velocity
    if(Vector2Length(velocity) != 0) {
        // Character is moving: update position and set running animation
        // Normalize velocity to get direction, then scale by speed
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        // Set facing direction based on velocity: left if negative X, right if positive X
        velocity.x < 0.f? rightLeft = -1.f : rightLeft = 1.f;
        // Switch to running texture
        texture = run;
    } else {
        // Character is not moving: reset velocity and use idle animation
        velocity = {0.f, 0.f};
        texture = idle;
    }
    // Reset velocity after processing (will be set by derived classes for next frame)
    velocity = {0.f, 0.f};

    // Draw the character sprite
    // Source rectangle: selects current frame from spritesheet, flips horizontally if facing left
    Rectangle source{ frame* width, 0.0f, rightLeft* width, height };
    // Destination rectangle: position and size on screen
    Rectangle dest{ getScreenPos().x, getScreenPos().y, scale* width, scale* height };
    // Draw the texture with source and destination rectangles
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}