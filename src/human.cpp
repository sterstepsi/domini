#include "human.h"

#include "screen_board_input.h"
#include "board.h"


Human::Human(Board* board, ScreenBoardInput* input)
    :board_(board), input_(input), is_pawn_chosen_(false)
{

}

bool Human::Move()
{
    Board::Position pos;
    if (!input_->GetPos(pos))
        return false;

    if (PawnChoose(pos))
        return false;

    return is_pawn_chosen_ ? PawnMove(pos) : false;
}

bool Human::PawnMove(Board::PositionRef pos)
{
    return board_->Move(selected_pawn_, pos);
}

bool Human::PawnChoose(Board::PositionRef pos)
{
    if (board_->IsHumanPawn(pos))
    {
        is_pawn_chosen_ = true;
        selected_pawn_ = std::move(pos);
        return true;
    }
    return false;
}