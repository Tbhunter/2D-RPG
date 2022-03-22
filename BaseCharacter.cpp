#include "BaseCharacter.h"
#include "raymath.h"
BaseCharacter::BaseCharacter()
{
}

void BaseCharacter::Tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    //update animation frame
    runningTime += GetFrameTime();
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        //set worldPos  = worldPos - directions
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

    velocity = {};
    //draw character
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{GetScreenPos().x, GetScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

void BaseCharacter::UndoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec()
{
    return Rectangle{
        GetScreenPos().x,
        GetScreenPos().y,
        width * scale,
        height * scale};
}