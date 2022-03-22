#include "Enemy.h"
#include "raymath.h"
Enemy::Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex)
{
    worldPos = pos;
    texture = idle_tex;
    idle = idle_tex;
    run = run_tex;
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 3.5f;
}

void Enemy::Tick(float deltaTime)
{
    if (!GetAlive())
        return;
    //Get toTarget
    velocity = Vector2Subtract(target->GetScreenPos(), GetScreenPos());
    if(Vector2Length(velocity) < radius) velocity = {};
    BaseCharacter::Tick(deltaTime);

    if (CheckCollisionRecs(target->GetCollisionRec(),GetCollisionRec()))
    {
        target->TakeDamage(damagePerSec * deltaTime);
    }
    
}

Vector2 Enemy::GetScreenPos()
{
    return Vector2Subtract(worldPos, target->GetWorldPos());
}