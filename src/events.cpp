#include "events.h"

#include <SFML/Graphics.hpp>

#include "input.h"


Events::Events(sf::RenderWindow* window, Input* input)
    : window_(window), input_(input), is_window_closed_event_(false)
{
}

void Events::Process()
{
    Clear();

    sf::Event event;
    while (window_->pollEvent(event))
    {
        switch (event.type) 
        {
            case sf::Event::Closed:
                ProcessCloseEvent(event);
                return;
            case sf::Event::MouseButtonPressed:
                ProcessMouseEvent(event);
                break;
            case sf::Event::KeyPressed:
                ProcessKeyboardEvent(event);
                break;
            default:
                break;
        }
    }
}

void Events::Clear()
{
    is_window_closed_event_ = false;
    input_->is_mouse_pressed_ = false;
    input_->pressed_keys_ = {};
}

void Events::ProcessCloseEvent(sf::Event& event)
{
    is_window_closed_event_ = true;
}

void Events::ProcessMouseEvent(sf::Event& event)
{
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        input_->is_mouse_pressed_ = true;
        input_->mouse_screen_pos_ = std::move(sf::Mouse::getPosition(*window_));
    }
}

void Events::ProcessKeyboardEvent(sf::Event& event)
{
    input_->pressed_keys_.insert(event.key.code);
}
