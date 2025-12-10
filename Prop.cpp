#include "Prop.h"
// Raylib math utilities for vector operations
#include "raymath.h"

/**
 * Constructor implementation
 * Initializes the prop with a world position and texture
 * @param pos World position where the prop will be placed
 * @param tex Texture to use for rendering the prop
 */
Prop::Prop(Vector2 pos, Texture2D tex):
    texture(tex),
    worldPos(pos)
{ 
    // Member variables initialized via initializer list above
}

/**
 * Render implementation
 * Draws the prop on screen by converting world position to screen coordinates
 * The screen position is calculated relative to the knight's position (camera effect)
 * @param knightPos Current world position of the knight (used for camera offset)
 */
void Prop::Render(Vector2 knightPos){
    // Convert world position to screen position by subtracting knight's position
    // This creates a camera effect where the prop moves relative to the player
    Vector2 screenPos = Vector2Subtract(worldPos, knightPos);
    // Draw the texture at the calculated screen position with the prop's scale
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}

/**
 * GetCollisionRec implementation
 * Calculates the collision rectangle for this prop in screen space
 * Used for collision detection with characters
 * @param knightPos Current world position of the knight (used for camera offset)
 * @return Rectangle representing the prop's collision bounds in screen coordinates
 */
Rectangle Prop::GetCollisionRec(Vector2 knightPos){
    // Convert world position to screen position (same calculation as Render)
    Vector2 screenPos = Vector2Subtract(worldPos, knightPos);
    // Return a rectangle with the screen position and scaled texture dimensions
    return Rectangle{
        screenPos.x,                                    // X position in screen space
        screenPos.y,                                    // Y position in screen space
        texture.width * scale,                         // Width scaled by prop's scale factor
        texture.height * scale                         // Height scaled by prop's scale factor
    };
}