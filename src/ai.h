#pragma once

#include "board.h"
#include "board_evaluator.h"

class AI
{
public:
    struct Move
    {
        Board::Position from;
        Board::Position to;
    };

    using MoveConst = typename const Move;

    explicit AI(Board* board);
    AI(const AI& right) = default;
    AI(AI&& right) = default;
    AI& operator=(const AI& right) = default;
    AI& operator=(AI&& right) = default;
    virtual ~AI() = default;

    AI::MoveConst GetMove();

private:
    Board* const board_;
    BoardEvaluator board_evaluator_;
};