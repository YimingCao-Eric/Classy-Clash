// Raylib library for graphics, window management, and game utilities
#include "raylib.h"
// Raylib math utilities for vector operations
#include "raymath.h"
// Custom character class for the player (knight)
#include "Character.h"
// Custom prop class for static objects in the world
#include "Prop.h"
// Custom enemy class for hostile entities
#include "Enemy.h"
#include <string>

/**
 * Main game entry point
 * Implements a top-down action game with a knight character, enemies, and props
 */
int main() {
    // Window dimensions
    const int windowWidth = 384;
    const int windowHeight = 384;
    // Initialize the game window
    InitWindow(windowWidth, windowHeight, "Top down");
    
    // Load the world map texture
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    // Map position (used for camera/offset calculations)
    Vector2 mapPos = { 0.0, 0.0 };
    // Scale factor for the map texture
    const float mapScale = 4.0;

    // Initialize the player character (knight)
    Character knight(windowWidth, windowHeight);
    
    // Initialize enemies with their idle and run sprites, and starting positions
    Enemy goblin(
        LoadTexture("characters/goblin_idle_spritesheet.png"), 
        LoadTexture("characters/goblin_run_spritesheet.png"), 
        Vector2{500.f, 700.f}
    );
    Enemy slime(
        LoadTexture("characters/slime_idle_spritesheet.png"), 
        LoadTexture("characters/slime_run_spritesheet.png"), 
        Vector2{800.f, 100.f}
    );
    
    // Array of enemy pointers for easy iteration
    Enemy* enemies[] = { 
        &goblin, 
        &slime 
    };

    // Set all enemies to target the knight (player)
    for (auto enemy : enemies) {
        enemy->setTarget(&knight);
    }

    // Initialize static props (rocks) in the world
    Prop props[2]{
       Prop({600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")),
       Prop({400.f, 500.f}, LoadTexture("nature_tileset/Rock.png"))
    };

    // Set target frame rate to 60 FPS
    SetTargetFPS(60);
    
    // Main game loop - runs until window is closed
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        // Calculate map position based on knight's world position (camera follows player)
        // Negative scaling creates the parallax/camera effect
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        // Draw the map background
        DrawTextureEx(map, mapPos, 0, mapScale, WHITE);

        // Draw all props in the world
        for (auto prop : props) {
            prop.Render(knight.getWorldPos());
        }

        // Update knight's state (movement, animation, etc.)
        knight.tick(GetFrameTime());
        
        // Boundary checking: prevent knight from moving outside map bounds
        if (knight.getWorldPos().x < 0.f || 
            knight.getWorldPos().x + windowWidth > map.width*mapScale || 
            knight.getWorldPos().y < 0.f || 
            knight.getWorldPos().y + windowHeight > map.height*mapScale) 
        {
            // Revert movement if knight would go out of bounds
            knight.undoMovement();
        }
        
        // Check for collision between knight and props
        for (auto prop : props) {
            if (CheckCollisionRecs(knight.GetCollisionRec(), prop.GetCollisionRec(knight.getWorldPos()))) {
                // Revert movement if collision detected
                knight.undoMovement();
            }
        }

        // Check if knight is still alive
        if (!knight.getAlive()) {
            // Display game over message
            DrawText("Game Over", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue; // Skip rest of frame if game over
        } else {
            // Display knight's current health
            std::string knightHealth = "Health: ";
            knightHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightHealth.c_str(), 55.f, 45.f, 40, RED);
        }
        
        // Update all enemies (movement, AI, animation, etc.)
        for (auto enemy : enemies) {    
            enemy->tick(GetFrameTime());
        }

        // Combat system: check for weapon hits when left mouse button is pressed
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            // Check collision between knight's weapon and each enemy
            for (auto enemy : enemies) {
                if (CheckCollisionRecs(knight.getWeaponCollisionRec(), enemy->GetCollisionRec())) {
                    // Kill enemy if hit by weapon
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }
    
    // Cleanup: close window and unload resources
    CloseWindow();
    UnloadTexture(map);
}