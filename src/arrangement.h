#pragma once

#include "board.h"

class Arrangement
{
public:
    explicit Arrangement(Board* board, Board::PositionsConstRef pawns);
    Arrangement(const Arrangement& right) = default;
    Arrangement(Arrangement&& right) = default;
    Arrangement& operator=(const Arrangement& right) = default;
    Arrangement& operator=(Arrangement&& right) = default;
    virtual ~Arrangement() = default;

    bool Next();
    void Revert();
    Board::Position From() { return from_; }
    Board::Position To() { return to_; }

private:
    Board* const board_;
    Board::Position from_;
    Board::Position to_;
    Board::PositionsConstRef pawns_;
    int i_;
    int j_;
};