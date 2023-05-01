#pragma once

#include "screen_board_input.h"
#include "board.h"


class Human
{
public:
    explicit Human(Board* board, ScreenBoardInput* input);
    Human(const Human& right) = default;
    Human(Human&& right) = default;
    Human& operator=(const Human& right) = default;
    Human& operator=(Human&& right) = default;
    virtual ~Human() = default;

    bool Move();

private:
    Board* const board_;
    ScreenBoardInput* const input_;
    bool is_pawn_chosen_;
    Board::Position selected_pawn_;

    bool PawnMove(Board::Position& pos);
    bool PawnChoose(Board::Position& pos);
};