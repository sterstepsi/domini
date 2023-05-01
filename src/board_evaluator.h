#pragma once

#include "hungarian/Hungarian.h"

#include "board.h"
#include "const.h"


class BoardEvaluator
{
public:
    explicit BoardEvaluator(Board* board);
    BoardEvaluator(const BoardEvaluator& right) = default;
    BoardEvaluator(BoardEvaluator&& right) = default;
    BoardEvaluator& operator=(const BoardEvaluator& right) = default;
    BoardEvaluator& operator=(BoardEvaluator&& right) = default;
    virtual ~BoardEvaluator() = default;

    int Evaluate();

private:
    Board* const board_;
    std::vector<std::vector<double>> distances_;
    std::vector<int> assignment_;
    HungarianAlgorithm hungarian_algorithm_;

    void CalculateDistances();
    int GetHungarianSolve();
    int Distance(Board::PositionConstRef pos1, Board::PositionConstRef pos2);
};
