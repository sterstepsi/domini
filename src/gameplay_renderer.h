#pragma once

#include <SFML/Graphics.hpp>

#include "board.h"



class GameplayRenderer
{
public:
    explicit GameplayRenderer(sf::RenderWindow* window);
    GameplayRenderer(const GameplayRenderer& right) = default;
    GameplayRenderer(GameplayRenderer&& right) = default;
    GameplayRenderer& operator=(const GameplayRenderer& right) = default;
    GameplayRenderer& operator=(GameplayRenderer&& right) = default;
    virtual ~GameplayRenderer() = default;

    void SetPlayerColor(bool is_white);
    void Render(const Board& board);

private:
    sf::RenderWindow* const window_;

    bool is_player_white_;

    std::vector<sf::Texture> textures_{3};
    int empty_texture_index_ = 0;

    sf::Sprite board_sprite_;
    sf::Sprite white_pawn_sprite_;
    sf::Sprite black_pawn_sprite_;


    void PopulateSprite(sf::Sprite& sprite, const char* path, const float& scale);
    sf::Sprite& GetPlayerPawnSprite();
    sf::Sprite& GetAIPawnSprite();
    void DrawBoard();
    void DrawPawns(sf::Sprite& sprite, Board::PositionsConstRef pawns);
};