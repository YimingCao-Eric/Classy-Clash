#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main() {
    const int windowWidth = 384;
    const int windowHeight = 384;
    InitWindow(windowWidth, windowHeight, "Top down");
    
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos = { 0.0, 0.0 };
    const float mapScale = 4.0;

    Character knight(windowWidth, windowHeight);
    Enemy goblin(
        LoadTexture("characters/goblin_idle_spritesheet.png"), 
        LoadTexture("characters/goblin_run_spritesheet.png"), 
        Vector2{100.f, 100.f}
    );
    goblin.setTarget(&knight);

    Prop props[2]{
       Prop({600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")),
       Prop({400.f, 500.f}, LoadTexture("nature_tileset/Rock.png"))
    };

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        // Draw the map
        DrawTextureEx(map, mapPos, 0, mapScale, WHITE);

        // Draw the props
        for (auto prop : props) {
            prop.Render(knight.getWorldPos());
        }

        knight.tick(GetFrameTime());
        if (knight.getWorldPos().x < 0.f || 
            knight.getWorldPos().x + windowWidth > map.width*mapScale || 
            knight.getWorldPos().y < 0.f || 
            knight.getWorldPos().y + windowHeight > map.height*mapScale) 
        {
            knight.undoMovement();
        }
        
        // Check for collision
        for (auto prop : props) {
            if (CheckCollisionRecs(knight.GetCollisionRec(), prop.GetCollisionRec(knight.getWorldPos()))) {
                knight.undoMovement();
            }
        }

        if (!knight.getAlive()) {
            DrawText("Game Over", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        } else {
            std::string knightHealth = "Health: ";
            knightHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightHealth.c_str(), 55.f, 45.f, 40, RED);
        }
        
        goblin.tick(GetFrameTime());
        if (CheckCollisionRecs(knight.GetCollisionRec(), goblin.GetCollisionRec())) {
                goblin.undoMovement();
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionRecs(knight.getWeaponCollisionRec(), goblin.GetCollisionRec())) {
                goblin.setAlive(false);
            }
        }

        EndDrawing();
    }
    CloseWindow();
    UnloadTexture(map);
}