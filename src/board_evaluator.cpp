#include "board_evaluator.h"

#include "hungarian/Hungarian.h"

#include "board.h"
#include "const.h"

static const std::vector<Board::Position> kTargetPositions{
        Board::Position{7,7},
        Board::Position{6,7},
        Board::Position{7,6},
        Board::Position{6,6},
        Board::Position{7,5},
        Board::Position{5,7},
        Board::Position{5,6},
        Board::Position{6,5},
        Board::Position{5,5}
};


BoardEvaluator::BoardEvaluator(Board* board)
        :board_{ board },
        distances_{ kPawnsCount, std::vector<double>(kPawnsCount) },
        hungarian_algorithm_{},
        assignment_{}
    {
    }

int BoardEvaluator::Evaluate()
{
    CalculateDistances();
    return GetHungarianSolve();
}

int BoardEvaluator::GetHungarianSolve()
{
    double cost = hungarian_algorithm_.Solve(distances_, assignment_);
    return static_cast<int>(cost);
}

// Считаем кол-во шагов для каждой пары "пешка - целевая позиция"
void BoardEvaluator::CalculateDistances()
{
    Board::PositionsConstRef aiPawnsPos = board_->GetAiPawnsPos();
    for (int i = 0; i < kTargetPositions.size(); ++i)
    {
        for (int j = 0; j < aiPawnsPos.size(); ++j)
        {
            distances_[i][j] = Distance(kTargetPositions[i], aiPawnsPos[j]);
        }
    }
}

int BoardEvaluator::Distance(Board::PositionConstRef pos1, Board::PositionConstRef pos2)
{
    return std::abs(pos1.x - pos2.x) + std::abs(pos1.y - pos2.y);
}
