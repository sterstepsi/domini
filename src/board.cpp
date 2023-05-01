#pragma once

#include "board.h"
#include "const.h"


Board::Board() 
{ 
    Reset(); 
};

void Board::Reset()
{
    KnockThePiecesOffTheBoard();
    ArrangeAIFigures();
    ArrangeHumanFigures();
}

void Board::KnockThePiecesOffTheBoard()
{
    for (int i = 0; i < kBoardSize; ++i)
    {
        for (int j = 0; j < kBoardSize; ++j)
        {
            board_[i][j].player = PawnsOnBoard::kEmpty;
        }
    }
}

void Board::ArrangeAIFigures()
{
    int index = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            board_[i][j].player = PawnsOnBoard::kAI;
            board_[i][j].index = index;

            ai_pawns_pos_[index].x = i;
            ai_pawns_pos_[index].y = j;
            ++index;
        }
    }
}

void Board::ArrangeHumanFigures()
{
    int index = 0;
    for (int i = kBoardSize - 3; i < kBoardSize; ++i)
    {
        for (int j = kBoardSize - 3; j < kBoardSize; ++j)
        {
            board_[i][j].player = PawnsOnBoard::kHuman;
            board_[i][j].index = index;

            human_pawns_pos_[index].x = i;
            human_pawns_pos_[index].y = j;
            ++index;
        }
    }
}


bool Board::Move(PositionConstRef from, PositionConstRef to)
{
    if (!IsPermittedMove(from, to))
        return false;

    Board::PositionRef pawn = GetPawn(from);
    pawn.x = to.x;
    pawn.y = to.y;

    std::swap(board_[from.x][from.y], board_[to.x][to.y]);

    return true;
}

bool Board::IsHumanPawn(PositionConstRef pos) const
{
    return board_[pos.x][pos.y].player == PawnsOnBoard::kHuman;
}

bool Board::IsAIPawn(PositionConstRef pos)  const
{
    return board_[pos.x][pos.y].player == PawnsOnBoard::kAI;
}

bool Board::IsPermittedMove(PositionConstRef from, PositionConstRef to)
{
    if (!IsPosOnBoard(from) || !IsPosOnBoard(to))
        return false;

    if (board_[from.x][from.y].player == PawnsOnBoard::kEmpty)
        return false;

    if (board_[to.x][to.y].player != PawnsOnBoard::kEmpty)
        return false;

    int x_shift = std::abs(from.x - to.x);
    int y_shift = std::abs(from.y - to.y);
    return x_shift + y_shift == 1;
}

Board::PositionRef Board::GetPawn(PositionConstRef pos)
{
    Board::PositionsRef pawns = (board_[pos.x][pos.y].player == PawnsOnBoard::kHuman)
        ? human_pawns_pos_
        : ai_pawns_pos_;

   return pawns[board_[pos.x][pos.y].index];
}

Board::Winner Board::GetWinner() const
{
    if (IsWinner(kBoardSize - 3, PawnsOnBoard::kAI))
        return Winner::kAI;
    if (IsWinner(0, PawnsOnBoard::kHuman))
        return Winner::kHuman;
    return Winner::kNobody;
}

bool Board::IsWinner(const int&& diagonal_pos, const PawnsOnBoard& value) const
{
    for (int i = diagonal_pos; i < diagonal_pos + 3; ++i)
    {
        for (int j = diagonal_pos; j < diagonal_pos + 3; ++j)
        {
            if (board_[i][j].player != value)
                return false;
        }
    }
    return true;
}

bool Board::IsPosOnBoard(PositionConstRef pos) const
{
    if (pos.x < 0 || pos.x >= kBoardSize ||
        pos.y < 0 || pos.y >= kBoardSize)
        return false;
    return true;
}