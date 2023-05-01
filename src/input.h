#pragma once

#include <set>

#include <SFML/Graphics.hpp>

#include "events.h"


class Events;

class Input
{
    friend class Events;
public:
    Input() = default;
    Input(const Input& right) = default;
    Input(Input&& right) = default;
    Input& operator=(const Input& right) = default;
    Input& operator=(Input&& right) = default;
    virtual ~Input() = default;

    bool IsMousePressed() { return is_mouse_pressed_; }
    bool IsKeyPressed(const sf::Keyboard::Key& key) { return pressed_keys_.find(key) != pressed_keys_.end(); }
    const sf::Vector2i& GetMouseScreenPos() { return mouse_screen_pos_; }

private:
    bool is_mouse_pressed_ = false;
    sf::Vector2i mouse_screen_pos_;
    std::set<sf::Keyboard::Key> pressed_keys_;
};