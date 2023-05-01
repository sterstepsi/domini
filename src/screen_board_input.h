#pragma once

#include "board.h"
#include "input.h"


class ScreenBoardInput
{
public:
    explicit ScreenBoardInput(Input* input);
    ScreenBoardInput(const ScreenBoardInput& right) = default;
    ScreenBoardInput(ScreenBoardInput&& right) = default;
    ScreenBoardInput& operator=(const ScreenBoardInput& right) = default;
    ScreenBoardInput& operator=(ScreenBoardInput&& right) = default;
    virtual ~ScreenBoardInput() = default;

    bool GetPos(Board::PositionRef cell) const;

private:
    Input* const input_;
};