#include "gameplay_renderer.h"

#include <SFML/Graphics.hpp>

#include "board.h"
#include "const.h"

static constexpr char kBoardTexturePath[] = "resources/textures/board.png";
static constexpr char kWhitePawnTexturePath[] = "resources/textures/white_pawn.png";
static constexpr char kBlackPawnTexturePath[] = "resources/textures/black_pawn.png";


GameplayRenderer::GameplayRenderer(sf::RenderWindow* window)
   : window_(window)
{
    PopulateSprite(board_sprite_, kBoardTexturePath, 0.5f);
    board_sprite_.setPosition(kHalfWindowWidth, kHalfWindowHeight);

    PopulateSprite(white_pawn_sprite_, kWhitePawnTexturePath, 0.45f);
    PopulateSprite(black_pawn_sprite_, kBlackPawnTexturePath, 0.45f);
}

void GameplayRenderer::SetPlayerColor(bool is_white)
{
    is_player_white_ = is_white;
}

void GameplayRenderer::PopulateSprite(sf::Sprite& sprite, const char* path, const float& scale)
{
    sf::Texture &texture = textures_[empty_texture_index_];
    texture.loadFromFile(path);
    texture.setSmooth(true);
    auto texSize = texture.getSize();

    sprite.setTexture(texture);
    sprite.setScale(scale, scale);
    sprite.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);

    empty_texture_index_++;
}

void GameplayRenderer::Render(const Board& board)
{
    window_->clear();

    DrawBoard();
    DrawPawns(GetPlayerPawnSprite(), board.GetHumanPawnsPos());
    DrawPawns(GetAIPawnSprite(), board.GetAiPawnsPos());

    window_->display();
}

void GameplayRenderer::DrawBoard()
{
    window_->draw(board_sprite_);
}

void GameplayRenderer::DrawPawns(sf::Sprite& sprite, Board::PositionsConstRef pawns)
{
    for (Board::PositionConstRef pawn : pawns)
    {
        float pos_x = static_cast<float>(kHalfWindowWidth + (-4 + pawn.x) * kCellSizeOnScreen + kHalfCellSizeOnScreen);
        float pos_y = static_cast<float>(kHalfWindowHeight + (-4 + pawn.y) * kCellSizeOnScreen + kHalfCellSizeOnScreen);
        sprite.setPosition(pos_x, pos_y);
        window_->draw(sprite);
    }
}

sf::Sprite& GameplayRenderer::GetPlayerPawnSprite()
{
    return (is_player_white_) ? white_pawn_sprite_ : black_pawn_sprite_;
}


sf::Sprite& GameplayRenderer::GetAIPawnSprite()
{
    return (is_player_white_) ? black_pawn_sprite_ : white_pawn_sprite_;
}