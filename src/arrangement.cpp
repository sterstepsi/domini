#include "arrangement.h"

#include "board.h"

static const std::vector<Board::Position> kDirections{
        Board::Position{-1,0},
        Board::Position{1,0},
        Board::Position{0,-1},
        Board::Position{0,1}
};

Arrangement::Arrangement(Board* board, Board::PositionsConstRef pawns)
    :
    board_{ board },
    pawns_ { pawns },
    i_{ 0 },
    j_{ -1 }
{
}

bool Arrangement::Next()
{
    while (true)
    {
        ++j_;
        if (j_ >= kDirections.size())
        {
            j_ = 0;
            ++i_;
        }
            
        if (i_ >= pawns_.size())
            return false;

        from_ = pawns_[i_];
        to_.x = from_.x + kDirections[j_].x;
        to_.y = from_.y + kDirections[j_].y;

        if (board_->Move(from_, to_))
            return true;
    }
}

void Arrangement::Revert()
{
    board_->Move(to_, from_);
}