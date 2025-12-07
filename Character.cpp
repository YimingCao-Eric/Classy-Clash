#include "Character.h"
#include "raymath.h"

Character::Character(int windowWidth, int windowHeight):
    windowWidth(windowWidth),
    windowHeight(windowHeight)
{
    width = texture.width/maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos() {
    return Vector2{
        static_cast<float>(windowWidth) * 0.5f - scale * width * 0.5f, 
        static_cast<float>(windowHeight) * 0.5f - scale * height * 0.5f
    };
}

void Character::tick(float deltaTime){
    if (!getAlive()) return;

    // Update the world position
    if (IsKeyDown(KEY_A)) velocity.x += -1.0;
    if (IsKeyDown(KEY_D)) velocity.x += 1.0;
    if (IsKeyDown(KEY_W)) velocity.y += -1.0;
    if (IsKeyDown(KEY_S)) velocity.y += 1.0;
    
    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    // facing right
    if (rightLeft > 0.f) {
        origin = {0.f, weapon.height * scale};
        offset = {35.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x, 
            getScreenPos().y + offset.y - weapon.height * scale, 
            weapon.width * scale, 
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? 35.f : 0.f;
    } 
    // facing left
    else {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        rotation = -35.f;
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale, 
            getScreenPos().y + offset.y - weapon.height * scale, 
            weapon.width * scale, 
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? -35.f : 0.f;
    }
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

}

void Character::takeDamage(float damage){
    health -= damage;
    if (health <= 0.f) {
        setAlive(false);
    }
}