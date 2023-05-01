#include "node.h"

#include <random>
#include <chrono>

#include "board.h"
#include "board_evaluator.h"
#include "ai.h"
#include "arrangement.h"



static std::default_random_engine random_engine(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));
static std::uniform_real_distribution<float> distribution(0.0, 1.0);


Node::Node(Board* board, BoardEvaluator* board_evaluator, int depth_left)
    :
    board_{ board },
    board_evaluator_{ board_evaluator },
    depth_left_{ depth_left }
{
    
}

AI::MoveConst Node::GetMove()
{
    depth_left_--;
    int min_cost = INT_MAX;

    std::vector<AI::Move> moves{ };
    Arrangement arrangement{ board_,  board_->GetAiPawnsPos() };
    while (arrangement.Next())
    {
        Node new_node{ board_, board_evaluator_, depth_left_ };
        int cost = new_node.GetMaximumCostAmongFuturePositions();

        if (cost < min_cost)
        {
            min_cost = cost;
            moves.clear();
            moves.push_back(AI::Move{ arrangement.From(), arrangement.To() });
        }
        else if (cost == min_cost)
        {
            moves.push_back(AI::Move{ arrangement.From(), arrangement.To() });
        }

        arrangement.Revert();
    }

    return moves[static_cast<int>(moves.size() * distribution(random_engine))];
}

int Node::GetMaximumCostAmongFuturePositions()
{
    if (IsDepthExhausted())
        return board_evaluator_->Evaluate();

    bool is_win = board_evaluator_->Evaluate() == 0;
    if (is_win)
        return 0;

    int max_cost = INT_MIN;
    Arrangement arrangement{ board_,  board_->GetHumanPawnsPos() };
    while (arrangement.Next())
    {
        Node new_node{ board_, board_evaluator_, depth_left_ };
        int cost = new_node.GetMinimumCostAmongFuturePositions();
        max_cost = std::max(max_cost, cost);

        arrangement.Revert();
    }
    return max_cost;
}

int Node::GetMinimumCostAmongFuturePositions()
{
    depth_left_--;
    int min_cost = INT_MAX;
    Arrangement arrangement{ board_, board_->GetAiPawnsPos() };
    while (arrangement.Next())
    {
        Node new_node{ board_, board_evaluator_, depth_left_ };
        int cost = new_node.GetMaximumCostAmongFuturePositions();
        min_cost = std::min(min_cost, cost);

        arrangement.Revert();
    }
    return min_cost;
}

bool Node::IsDepthExhausted()
{
    return depth_left_ == 0;
}
