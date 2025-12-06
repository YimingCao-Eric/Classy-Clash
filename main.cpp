#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

int main() {
    const int windowWidth = 384;
    const int windowHeight = 384;
    InitWindow(windowWidth, windowHeight, "Top down");
    
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos = { 0.0, 0.0 };
    const float mapScale = 4.0;

    Character knight(windowWidth, windowHeight);

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
        EndDrawing();
    }
    CloseWindow();
    UnloadTexture(map);
}