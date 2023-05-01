#pragma once

#include "board.h"
#include "board_evaluator.h"
#include "ai.h"


class Node
{
public:
    explicit Node(Board* board, BoardEvaluator* board_evaluator, int depth_left);
    Node(const Node& right) = default;
    Node(Node&& right) = default;
    Node& operator=(const Node& right) = default;
    Node& operator=(Node&& right) = default;
    virtual ~Node() = default;

    AI::MoveConst GetMove();

private:
    Board* const board_;
    BoardEvaluator* const board_evaluator_;
    int depth_left_;

    bool IsDepthExhausted();
    int GetMinimumCostAmongFuturePositions();
    int GetMaximumCostAmongFuturePositions();
};