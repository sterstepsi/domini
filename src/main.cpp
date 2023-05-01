#define DOMINI_DEBUG

#include <SFML/Graphics.hpp>

#include "debug/console.h"

#include "const.h"
#include "input.h"
#include "events.h"
#include "gameplay_loop.h"
#include "board.h"



void StartGame()
{
    sf::RenderWindow window(sf::VideoMode(kWindowWidth, kWindowHeight), "Chess game");
    window.setFramerateLimit(30);
    Input input;
    Events events{ &window, &input };
    GameplayLoop gameplay_loop{ &window, &input };
    
    while (window.isOpen())
    {
        events.Process();

        if (events.IsWindowClosedEvent())
        {
            window.close();
            break;
        }

        gameplay_loop.EnterFrame();

        Board::Winner winner = gameplay_loop.GetWinner();
        if (winner != Board::Winner::kNobody)
            gameplay_loop.Reset();
    }
}

int main()
{
    debug::CreateConsole();
    StartGame();
    return 0;
}