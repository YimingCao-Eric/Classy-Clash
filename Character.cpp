#include "Character.h"
#include "raymath.h"

Character::Character(int windowWidth, int windowHeight){
    width = texture.width/maxFrames;
    height = texture.height;
    screenPos = { 
        static_cast<float>(windowWidth) * 0.5f - scale * width * 0.5f, 
        static_cast<float>(windowHeight) * 0.5f - scale * height * 0.5f
    };
}

void Character::tick(float deltaTime){
    worldPosLastFrame = worldPos;
    // Update the world position
    Vector2 direction{};
    if (IsKeyDown(KEY_A)) direction.x += -1.0;
    if (IsKeyDown(KEY_D)) direction.x += 1.0;
    if (IsKeyDown(KEY_W)) direction.y += -1.0;
    if (IsKeyDown(KEY_S)) direction.y += 1.0;
    if(Vector2Length(direction) != 0) {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    } else {
        texture = idle;
    }
    // update animation
    runningTime += deltaTime;
    if (runningTime >= updateTime) {
        frame++;
        runningTime = 0.f;
        if (frame >= maxFrames) frame = 0;
    }
    // Draw the knight
    Rectangle source{ frame* width, 0.0f, rightLeft* width, height };
    Rectangle dest{ screenPos.x, screenPos.y, scale* width, scale* height };
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

void Character::undoMovement(){
    worldPos = worldPosLastFrame;
}

Rectangle Character::GetCollisionRec(){
    return Rectangle{
        screenPos.x, 
        screenPos.y, 
        scale* width, 
        scale* height
    };
}