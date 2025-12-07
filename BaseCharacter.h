#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter {  
    public:
        BaseCharacter();
        Vector2 getWorldPos(){ return worldPos; }
        void undoMovement();
        Rectangle GetCollisionRec();
        virtual void tick(float deltaTime);
        virtual Vector2 getScreenPos() = 0;
        bool getAlive(){ return alive; }
        void setAlive(bool isAlive){ alive = isAlive; }

    protected:
        Texture2D texture{ LoadTexture("characters/knight_idle_spritesheet.png") };
        Texture2D idle{ LoadTexture("characters/knight_idle_spritesheet.png") };
        Texture2D run{ LoadTexture("characters/knight_run_spritesheet.png") };

        Vector2 worldPos{0.f, 0.f};
        Vector2 worldPosLastFrame{0.f, 0.f};

        float rightLeft{1.f}; // 1: facing right, -1: facing left
        float runningTime{0.f}; 
        int frame{0};
        int maxFrames{6};
        float updateTime{1.f/12.f}; 
        float speed{4.f};

        float width{0.f};
        float height{0.f};
        float scale{4.f};

        Vector2 velocity{0.f, 0.f};

    private:
        bool alive{true};
};

#endif