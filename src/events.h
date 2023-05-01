#pragma once

#include <SFML/Graphics.hpp>

#include "input.h"

class Input;

class Events
{
public:
    explicit Events(sf::RenderWindow* window, Input* input);
    Events(const Events& right) = default;
    Events(Events&& right) = default;
    Events& operator=(const Events& right) = default;
    Events& operator=(Events&& right) = default;
    virtual ~Events() = default;

    void Process();
    bool IsWindowClosedEvent() { return is_window_closed_event_; }

private:
    sf::RenderWindow* const window_;
    Input* const input_;
    bool is_window_closed_event_;

    void Clear();
    void ProcessCloseEvent(sf::Event& event);
    void ProcessMouseEvent(sf::Event& event);
    void ProcessKeyboardEvent(sf::Event& event);
};