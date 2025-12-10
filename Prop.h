// Raylib library for graphics, textures, and vector/math types
#include "raylib.h"

/**
 * Prop class
 * Represents static objects in the game world (e.g., rocks, trees, obstacles)
 * Props are rendered relative to the player's position and can collide with characters
 */
class Prop {
    public:
        /**
         * Constructor
         * @param pos World position of the prop
         * @param tex Texture to use for rendering the prop
         */
        Prop(Vector2 pos, Texture2D tex);
        
        /**
         * Renders the prop on screen
         * Calculates screen position based on the knight's world position (camera offset)
         * @param knightPos Current world position of the knight (for camera calculation)
         */
        void Render(Vector2 knightPos);
        
        /**
         * Gets the collision rectangle for this prop
         * Used for collision detection with characters
         * @param knightPos Current world position of the knight (for camera calculation)
         * @return Rectangle representing the prop's collision bounds in screen space
         */
        Rectangle GetCollisionRec(Vector2 knightPos);
        
    private:
        // Texture used to render the prop
        Texture2D texture{};
        // World position of the prop (absolute position in the game world)
        Vector2 worldPos{};
        // Scale factor for rendering the prop texture (default: 4x)
        float scale{4.f};
};