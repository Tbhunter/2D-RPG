#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) : windowWidth(winWidth),
                                                    windowHeight(winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;
}

Vector2 Character::GetScreenPos()
{
    return Vector2{static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
                   static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)};
}

void Character::Tick(float deltaTime)
{
    if (!GetAlive())
        return;

    float rotation{};
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    BaseCharacter::Tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    if (rightLeft > 0.f)
    {
        origin = {0.f, weapon.height * scale};
        offset = {35.f, 55.f};
        weaponCollisionRec = {GetScreenPos().x + offset.x,
                              GetScreenPos().y + offset.y - weapon.height * scale,
                              weapon.width * scale,
                              weapon.height * scale};

        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 35.f : rotation = 0.f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        weaponCollisionRec = {GetScreenPos().x + offset.x - weapon.width * scale,
                              GetScreenPos().y + offset.y - weapon.height * scale,
                              weapon.width * scale,
                              weapon.height * scale};

        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -35.f : rotation = 0.f;
    }

    //draw sword
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{GetScreenPos().x + offset.x, GetScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);
}

void Character::TakeDamage(float damage)
{
    health -= damage;
    if (health <= 0.f)
    {
        SetAlive(false);
    }
}
