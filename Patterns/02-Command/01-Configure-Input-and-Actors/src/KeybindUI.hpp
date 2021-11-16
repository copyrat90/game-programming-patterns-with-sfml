#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Window/Event.hpp>
#include <array>

#include "AssetManagers.hpp"
#include "InputHandler.hpp"

namespace sf
{
class Time;
class RenderTarget;
class RenderStates;
} // namespace sf

namespace igpp::c02_01
{

class KeybindUI : public sf::Drawable, public sf::Transformable
{
public:
    KeybindUI(const KeybindUI&) = delete;
    KeybindUI& operator=(const KeybindUI&) = delete;

public:
    static constexpr int TOTAL_BUTTONS = 4;

private:
    class KeyIcon : public sf::Drawable, public sf::Transformable
    {
    public:
        KeyIcon(const KeyIcon&) = delete;
        KeyIcon& operator=(const KeyIcon&) = delete;

    public:
        enum class State
        {
            NONE,
            MOUSE_HOVER,
            SELECTED
        };

    public:
        KeyIcon(InputHandler::Key key, char keyChar, InputHandler&, FontManager&);

    private:
        void initLines();
        void initRectShape();
        void initKeyChar(char keyChar, FontManager&);
        void initKeybindDescription(InputHandler::Key, InputHandler&, FontManager&);

    public:
        void handleEvent(const sf::Event&);
        void update(const sf::Time& dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void swapKeybindText(KeyIcon& other);

        InputHandler::Key getKey() const;

        void setState(State state);
        State getState() const;

    private:
        void setFocusLineVisible(bool visible);
        void setFocusLineColor(const sf::Color&);

        void setKeyIconColor(const sf::Color&);

    private:
        sf::RectangleShape keyRectShape_;
        const InputHandler::Key key_;
        sf::Text keyChar_;
        sf::Text keybindDescription_;
        State state_;
        bool focusLineVisible_;
        std::array<sf::Vertex[2], 8> focusLines_;
    };

public:
    KeybindUI(InputHandler&, FontManager&);

    void handleEvent(const sf::Event&);
    void update(const sf::Time& dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    void handleEvent(const sf::Event::MouseButtonEvent&);
    void handleEvent(const sf::Event::MouseMoveEvent&);

    bool pointHoverOnKeyIcon(const sf::Vector2f& point, const KeybindUI::KeyIcon& keyIcon) const;
    KeyIcon* getSelectedKey();

private:
    InputHandler& inputHandler_;

    std::array<KeyIcon, TOTAL_BUTTONS> keyIcons_;
    sf::Text helpMessage_;
};

} // namespace igpp::c02_01
