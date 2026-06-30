#include "Game.h"
#include "Components.h"
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>

namespace
{
void HideCursor()
{
    HANDLE              hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void MoveCursorToTop()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, {0, 0});
}
}  // namespace

Game::Game()
{
    HideCursor();

    head = registry.create();
    registry.emplace<Head>(head);
    registry.emplace<Position>(head, 12, 4);
    registry.emplace<Direction>(head, 1, 0);
    registry.emplace<Renderable>(head, '@');

    auto bodySeg = registry.create();
    registry.emplace<Body>(bodySeg);
    registry.emplace<Position>(bodySeg, 11, 4);
    registry.emplace<Renderable>(bodySeg, 'o');
    body.push_back(bodySeg);

    auto food = registry.create();
    registry.emplace<Food>(food);
    registry.emplace<Position>(food, 3, 4);
    registry.emplace<Renderable>(food, '*');
}

void Game::Run()
{
    while (isRunning)
    {
        MoveCursorToTop();

        DirectionSystem();
        MoveSystem();
        CollideSystem();
        EatSystem();
        RenderSystem();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    system("cls");
    std::cout << "Game over!" << std::endl;
}

void Game::DirectionSystem()
{
    auto& direction = registry.get<Direction>(head);

    if (!_kbhit())
        return;

    int key = _getch();
    if (key != 224)
        return;

    key = _getch();
    switch (key)
    {
        case 72:
            direction = {0, -1};
            break;  // up
        case 80:
            direction = {0, 1};
            break;  // down
        case 75:
            direction = {-1, 0};
            break;  // left
        case 77:
            direction = {1, 0};
            break;  // right
    }
}

void Game::MoveSystem()
{
    auto& head_pos  = registry.get<Position>(head);
    auto& direction = registry.get<Direction>(head);

    Position prev_head_pos = head_pos;
    head_pos.x += direction.vx;
    head_pos.y += direction.vy;

    if (head_pos.x == grid_width)
        head_pos.x = 0;
    if (head_pos.x < 0)
        head_pos.x = grid_width - 1;
    if (head_pos.y == grid_height)
        head_pos.y = 0;
    if (head_pos.y < 0)
        head_pos.y = grid_height - 1;

    for (auto& segment : body)
    {
        auto&    segment_pos = registry.get<Position>(segment);
        Position temp        = segment_pos;
        segment_pos          = prev_head_pos;
        prev_head_pos        = temp;
    }
}

void Game::EatSystem()
{
    auto& headPos = registry.get<Position>(head);

    auto foodView = registry.view<Food, Position>();
    for (auto [foodEntity, foodPos] : foodView.each())
    {
        if (foodPos.x != headPos.x || foodPos.y != headPos.y)
            continue;

        registry.destroy(foodEntity);

        auto newFood = registry.create();
        registry.emplace<Food>(newFood);
        registry.emplace<Position>(newFood, Position{xDist(gen), yDist(gen)});
        registry.emplace<Renderable>(newFood, '*');

        Position tailPos    = body.empty() ? headPos : registry.get<Position>(body.back());
        auto     newSegment = registry.create();
        registry.emplace<Body>(newSegment);
        registry.emplace<Position>(newSegment, tailPos);
        registry.emplace<Renderable>(newSegment, 'o');
        body.push_back(newSegment);

        break;
    }
}

void Game::RenderSystem()
{
    std::fill(grid.begin(), grid.end(), '.');

    auto view = registry.view<Renderable, Position>();
    view.each([this](const auto& renderable, const auto& position)
              { grid[(position.y * grid_width) + position.x] = renderable.symbol; });

    for (int i = 0; i < grid_height; i++)
    {
        for (int j = 0; j < grid_width; j++)
            std::cout << grid[i * grid_width + j];
        std::cout << std::endl;
    }
}

void Game::CollideSystem()
{
    auto& headPos = registry.get<Position>(head);

    for (auto& segment : body)
    {
        auto& segmentPos = registry.get<Position>(segment);

        if (headPos.x == segmentPos.x && headPos.y == segmentPos.y)
        {
            isRunning = false;
        }
    }
}