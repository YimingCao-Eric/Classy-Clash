#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Texture2D idle_texture, Texture2D run_texture, Vector2 pos)
{
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    worldPos = pos;
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 3.f;
}

Vector2 Enemy::getScreenPos() {
    return Vector2Subtract(worldPos, target->getWorldPos());
}

void Enemy::tick(float deltaTime) {
    if (!getAlive()) return;
    
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    BaseCharacter::tick(deltaTime);
    if (CheckCollisionRecs(GetCollisionRec(), target->GetCollisionRec())) {
        target->takeDamage(damagePerSec * deltaTime);
    }
}
