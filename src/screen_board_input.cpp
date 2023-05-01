#include "screen_board_input.h"

#include <SFML/Graphics.hpp>

#include "input.h"
#include "const.h"


ScreenBoardInput::ScreenBoardInput(Input* input)
    :input_(input)
{

}

bool ScreenBoardInput::GetPos(Board::PositionRef cell) const
{
    if (!input_->IsMousePressed())
    {
        cell.x = -1;
        cell.y = -1;
        return false;
    }

    const sf::Vector2i& mouse_screen_pos = input_->GetMouseScreenPos();

    if (mouse_screen_pos.x < kHalfWindowWidth - kCellSizeOnScreen * 4 ||
        mouse_screen_pos.x > kHalfWindowWidth + kCellSizeOnScreen * 4 ||
        mouse_screen_pos.y < kHalfWindowHeight - kCellSizeOnScreen * 4 ||
        mouse_screen_pos.y > kHalfWindowHeight + kCellSizeOnScreen * 4)
    {
        cell.x = -1;
        cell.y = -1;
        return false;
    }

    cell.x = (mouse_screen_pos.x - (kHalfWindowWidth - kCellSizeOnScreen * 4)) / kCellSizeOnScreen;
    cell.y = (mouse_screen_pos.y - (kHalfWindowHeight - kCellSizeOnScreen * 4)) / kCellSizeOnScreen;
    return true;
}