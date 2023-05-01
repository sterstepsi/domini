#pragma once

#include <vector>

#include "const.h"


class Board
{
public:
    enum class Winner
    {
        kNobody,
        kAI,
        kHuman
    };

    struct Position
    {
        int x = 0;
        int y = 0;
    };

    using PositionRef = typename Position&;

    using PositionConstRef = typename const Position&;

    using Positions = typename std::vector<Position>;

    using PositionsRef = typename Positions&;

    using PositionsConstRef = typename const Positions&;


    Board();
    Board(const Board& right) = default;
    Board(Board&& right) = default;
    Board& operator=(const Board& right) = default;
    Board& operator=(Board&& right) = default;
    virtual ~Board() = default;

    PositionsConstRef GetAiPawnsPos() const { return ai_pawns_pos_; }
    PositionsConstRef GetHumanPawnsPos() const { return human_pawns_pos_; }
    bool IsHumanPawn(PositionConstRef pos) const;
    bool IsAIPawn(PositionConstRef pos) const;
    Winner GetWinner() const;
    void Reset();
    bool Move(PositionConstRef from, PositionConstRef to);

private:
    enum class PawnsOnBoard
    {
        kEmpty,
        kHuman,
        kAI
    };

    struct Cell
    {
        PawnsOnBoard player;
        int index;
    };

    Positions ai_pawns_pos_{ kPawnsCount };
    Positions human_pawns_pos_{ kPawnsCount };
    std::vector<std::vector<Cell>> board_ {kBoardSize, std::vector<Cell>(kBoardSize)} ;

    bool IsWinner(const int&& diagonal_pos, const PawnsOnBoard& value) const;
    bool IsPermittedMove(PositionConstRef from, PositionConstRef to);
    bool IsPosOnBoard(PositionConstRef pos) const;
    PositionRef GetPawn(PositionConstRef pos);
    void KnockThePiecesOffTheBoard();
    void ArrangeAIFigures();
    void ArrangeHumanFigures();
};