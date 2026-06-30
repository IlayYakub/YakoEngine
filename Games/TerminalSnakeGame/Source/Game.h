#pragma once
#include <entt/entt.hpp>
#include <random>
#include <vector>

class Game
{
public:
    Game();
    void Run();

private:
    void DirectionSystem();
    void MoveSystem();
    void EatSystem();
    void RenderSystem();
    void CollideSystem();

    static constexpr int grid_width  = 30;
    static constexpr int grid_height = 20;

    entt::registry            registry;
    entt::entity              head;
    std::vector<entt::entity> body;

    std::mt19937                       gen{std::random_device{}()};
    std::uniform_int_distribution<int> xDist{0, grid_width - 1};
    std::uniform_int_distribution<int> yDist{0, grid_height - 1};

    std::vector<char> grid = std::vector<char>(grid_width * grid_height, '.');

    bool isRunning = true;
};