#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    //window dimension
    int windowDimensions[2] = {500, 500};

    InitWindow(windowDimensions[0], windowDimensions[1], "Swords and Fjords");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{3.0};
    Character knight{windowDimensions[0], windowDimensions[1]};
    Prop props[2]{
        Prop{Vector2{1200.f, 1000.f}, LoadTexture("nature_tileset//Rock.png")},
        Prop{Vector2{1000.f, 1200.f}, LoadTexture("nature_tileset//Log.png")}};

    Enemy goblin{Vector2{800.f, 1500.f},
                 LoadTexture("characters/goblin_idle_spritesheet.png"),
                 LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy slime{
        Vector2{1000.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy *enemies[]{&goblin, &slime};

    for (auto enemy : enemies)
    {
        enemy->SetTarget(&knight);
    }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.GetWorldPos(), -1.f);

        //draw map
        DrawTextureEx(map, mapPos, 0, mapScale, WHITE);

        //draw props
        for (auto prop : props)
        {
            prop.Render(knight.GetWorldPos());
        }

        if (!knight.GetAlive())
        {
            DrawText("Game Over!!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.GetHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        knight.Tick(GetFrameTime());

        //check map bounds
        if (knight.GetWorldPos().x < 0.f ||
            knight.GetWorldPos().y < 0.f ||
            knight.GetWorldPos().x + windowDimensions[0] > map.width * mapScale ||
            knight.GetWorldPos().y + windowDimensions[1] > map.height * mapScale)
        {
            knight.UndoMovement();
        }

        //check prop collision
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.GetCollisionRec(knight.GetWorldPos()), knight.GetCollisionRec()))
            {
                knight.UndoMovement();
            }
        }

        for (auto enemy : enemies)
        {
            enemy->Tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->GetCollisionRec(), knight.GetWeaponCollisionRec()))
                {
                    enemy->SetAlive(false);
                }
            }
        }
        EndDrawing();
    }
    CloseWindow();
}