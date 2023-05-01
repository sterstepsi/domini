#pragma once

#include <SFML/Graphics.hpp>

#include "input.h"
#include "screen_board_input.h"
#include "board.h"
#include "ai.h"
#include "human.h"
#include "gameplay_renderer.h"


class GameplayLoop
{
public:
    explicit GameplayLoop(sf::RenderWindow* window, Input* input);
    GameplayLoop(const GameplayLoop& right) = default;
    GameplayLoop(GameplayLoop&& right) = default;
    GameplayLoop& operator=(const GameplayLoop& right) = default;
    GameplayLoop& operator=(GameplayLoop&& right) = default;
    virtual ~GameplayLoop() = default;

    Board::Winner GetWinner() { return board_.GetWinner();};
    void EnterFrame();
    void Reset();

private:
    sf::RenderWindow* const window_;
    Input* const input_;
    ScreenBoardInput screen_board_input_;
    bool is_human_turn_;
    Board board_;
    AI ai_;
    Human human_;
    GameplayRenderer gameplay_renderer_;

    bool MoveHuman();
    void MoveAI();
    void MovePlayers();
};