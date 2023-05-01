#include "gameplay_loop.h"

#include <chrono>
#include <random>

#include <SFML/Graphics.hpp>

#include "input.h"

static std::default_random_engine random_engine(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));
static std::uniform_real_distribution<float> distribution(0.0, 1.0);


GameplayLoop::GameplayLoop(sf::RenderWindow* window, Input* input)
    : window_{ window },
    input_{ input },
    screen_board_input_( input_ ),
    board_{},
    ai_{ &board_ },
    human_{ &board_, &screen_board_input_ },
    gameplay_renderer_{ window }
{
    Reset();
}

void GameplayLoop::EnterFrame()
{
    MovePlayers();
    gameplay_renderer_.Render(board_);
}

void GameplayLoop::MovePlayers()
{
    if (is_human_turn_)
    {
        is_human_turn_ = !MoveHuman();
    }
    else
    {
        MoveAI();
        is_human_turn_ = true;
    }
}

bool GameplayLoop::MoveHuman()
{
    return human_.Move();
}

void GameplayLoop::MoveAI()
{
    AI::MoveConst move = ai_.GetMove();
    board_.Move(move.from, move.to);
}

void GameplayLoop::Reset()
{
    is_human_turn_ = (static_cast<int>(distribution(random_engine) * 2) == 1)
        ? true
        : false;
    board_.Reset();
    gameplay_renderer_.SetPlayerColor(is_human_turn_);
}