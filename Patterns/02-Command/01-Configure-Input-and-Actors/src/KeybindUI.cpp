#include "KeybindUI.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <sstream>
#include <string>

#include "constant.hpp"
#include "global.hpp"

namespace igpp::c02_01
{

namespace
{
constexpr int ICON_MARGIN_X = 20;
constexpr int ICON_MARGIN_Y = 20;
constexpr int ICON_WIDTH = 80;
constexpr int ICON_HEIGHT = 80;
constexpr int ICON_SECOND_ROW_MARGIN_X = (ICON_WIDTH + ICON_MARGIN_X) / 2;
constexpr int FOCUS_LINE_PADDING = 10;
constexpr int FOCUS_LINE_LENGTH = 20;
constexpr int TEXT_PADDING = 20;
constexpr int UI_POS_X = 260;
constexpr int UI_POS_Y = 250;
} // namespace

KeybindUI::KeyIcon::KeyIcon(InputHandler::Key key, char keyChar, InputHandler& inputHandler, FontManager& fonts)
    : key_(key), keyRectShape_({ICON_WIDTH, ICON_HEIGHT}), state_(State::NONE), focusLineVisible_(false)
{
    setOrigin(ICON_WIDTH / 2, ICON_HEIGHT / 2);
    initLines();
    initRectShape();
    initKeyChar(keyChar, fonts);
    initKeybindDescription(key, inputHandler, fonts);
}

void KeybindUI::KeyIcon::initLines()
{
    constexpr float top = -FOCUS_LINE_PADDING;
    constexpr float bottom = ICON_HEIGHT + FOCUS_LINE_PADDING;
    constexpr float left = -FOCUS_LINE_PADDING;
    constexpr float right = ICON_WIDTH + FOCUS_LINE_PADDING;
    const sf::Vector2f upperLeft = {left, top};
    const sf::Vector2f upperRight = {right, top};
    const sf::Vector2f lowerLeft = {left, bottom};
    const sf::Vector2f lowerRight = {right, bottom};
    focusLines_[0][0].position = focusLines_[0][1].position = upperLeft;
    focusLines_[1][0].position = focusLines_[1][1].position = upperLeft;
    focusLines_[2][0].position = focusLines_[2][1].position = upperRight;
    focusLines_[3][0].position = focusLines_[3][1].position = upperRight;
    focusLines_[4][0].position = focusLines_[4][1].position = lowerRight;
    focusLines_[5][0].position = focusLines_[5][1].position = lowerRight;
    focusLines_[6][0].position = focusLines_[6][1].position = lowerLeft;
    focusLines_[7][0].position = focusLines_[7][1].position = lowerLeft;

    focusLines_[0][1].position.y += FOCUS_LINE_LENGTH;
    focusLines_[1][1].position.x += FOCUS_LINE_LENGTH;
    focusLines_[2][1].position.x -= FOCUS_LINE_LENGTH;
    focusLines_[3][1].position.y += FOCUS_LINE_LENGTH;
    focusLines_[4][1].position.y -= FOCUS_LINE_LENGTH;
    focusLines_[5][1].position.x -= FOCUS_LINE_LENGTH;
    focusLines_[6][1].position.x += FOCUS_LINE_LENGTH;
    focusLines_[7][1].position.y -= FOCUS_LINE_LENGTH;
}

void KeybindUI::KeyIcon::initRectShape()
{
    keyRectShape_.setFillColor(sf::Color::Transparent);
    keyRectShape_.setOutlineColor(sf::Color::White);
    keyRectShape_.setOutlineThickness(3);
}

void KeybindUI::KeyIcon::initKeyChar(char keyChar, FontManager& fonts)
{
    keyChar_.setString(keyChar);

    keyChar_.setPosition(getOrigin());
    keyChar_.setFont(fonts.get(FontId::D2CODING));
    keyChar_.setCharacterSize(60);
    keyChar_.setColor(sf::Color::White);

    const auto bounds = keyChar_.getLocalBounds();
    keyChar_.setOrigin(bounds.width / 2, bounds.height * 9 / 10);
}

void KeybindUI::KeyIcon::initKeybindDescription(InputHandler::Key key, InputHandler& inputHandler, FontManager& fonts)
{
    std::ostringstream ss;
    ss << inputHandler.getBoundCommandName(key_) << "\n0x" << std::hex
       << reinterpret_cast<long long>(inputHandler.getBoundCommand(key_)) << std::dec;
    keybindDescription_.setString(ss.str());

    keybindDescription_.setFont(fonts.get(FontId::D2CODING));
    keybindDescription_.setCharacterSize(24);
    keybindDescription_.setColor(sf::Color::White);

    const auto bounds = keybindDescription_.getLocalBounds();
    keybindDescription_.setOrigin(bounds.width / 2, bounds.height / 2);

    float textXPos = (ICON_WIDTH + bounds.width) / 2 + TEXT_PADDING;
    // if the icon is on the left side, move the text to the left of the icon
    if (key % 2 == 0)
        textXPos = -textXPos;

    keybindDescription_.setPosition(getOrigin() + sf::Vector2f{textXPos, 0.f});
}

void KeybindUI::KeyIcon::handleEvent(const sf::Event& event)
{
    using SfKey = sf::Keyboard::Key;
    using IHKey = InputHandler::Key;

    if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
    {
        const SfKey iconKey = InputHandler::convertIHKeyToSfKey(key_);

        if (event.key.code == iconKey)
        {
            if (event.type == sf::Event::KeyPressed)
                setKeyIconColor(sf::Color::Green);
            else
                setKeyIconColor(sf::Color::White);
        }
    }
}

void KeybindUI::KeyIcon::update(const sf::Time& dt)
{
}

void KeybindUI::KeyIcon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(keyRectShape_, states);
    target.draw(keyChar_, states);
    target.draw(keybindDescription_, states);
    if (focusLineVisible_)
    {
        for (const auto& line : focusLines_)
            target.draw(line, 2, sf::Lines, states);
    }
}

void KeybindUI::KeyIcon::setState(State newState)
{
    if (state_ != newState)
    {
        state_ = newState;
        switch (newState)
        {
        case State::NONE:
            setFocusLineVisible(false);
            keybindDescription_.setColor(sf::Color::White);
            break;
        case State::MOUSE_HOVER:
            setFocusLineVisible(true);
            setFocusLineColor(sf::Color::White);
            keybindDescription_.setColor(sf::Color::White);
            break;
        case State::SELECTED:
            setFocusLineVisible(true);
            setFocusLineColor(sf::Color::Cyan);
            keybindDescription_.setColor(sf::Color::Cyan);
        }
    }
}

KeybindUI::KeyIcon::State KeybindUI::KeyIcon::getState() const
{
    return state_;
}

InputHandler::Key KeybindUI::KeyIcon::getKey() const
{
    return key_;
}

void KeybindUI::KeyIcon::setFocusLineVisible(bool visible)
{
    focusLineVisible_ = visible;
}

void KeybindUI::KeyIcon::setFocusLineColor(const sf::Color& color)
{
    for (auto& line : focusLines_)
    {
        for (auto& vertex : line)
            vertex.color = color;
    }
}

void KeybindUI::KeyIcon::setKeyIconColor(const sf::Color& color)
{
    keyChar_.setColor(color);
    keyRectShape_.setOutlineColor(color);
}

void KeybindUI::KeyIcon::swapKeybindText(KeybindUI::KeyIcon& other)
{
    auto tempOrigin = keybindDescription_.getOrigin();
    keybindDescription_.setOrigin(other.keybindDescription_.getOrigin());
    other.keybindDescription_.setOrigin(tempOrigin);

    auto tempStr = keybindDescription_.getString();
    keybindDescription_.setString(other.keybindDescription_.getString());
    other.keybindDescription_.setString(tempStr);
}

KeybindUI::KeybindUI(InputHandler& inputHandler, FontManager& fonts)
    : inputHandler_(inputHandler), keyIcons_{KeyIcon(InputHandler::Key::A, 'A', inputHandler, fonts),
                                             KeyIcon(InputHandler::Key::S, 'S', inputHandler, fonts),
                                             KeyIcon(InputHandler::Key::Z, 'Z', inputHandler, fonts),
                                             KeyIcon(InputHandler::Key::X, 'X', inputHandler, fonts)}
{
    const sf::Font& font = fonts.get(FontId::D2CODING);
    helpMessage_.setFont(font);
    helpMessage_.setCharacterSize(20);
    helpMessage_.setColor(sf::Color::White);
    helpMessage_.setPosition(constant::WINDOW_WIDTH / 2, constant::WINDOW_HEIGHT - 100);

    keyIcons_[0].setPosition(0, 0);
    keyIcons_[1].setPosition(ICON_WIDTH + ICON_MARGIN_X, 0);
    keyIcons_[2].setPosition(ICON_SECOND_ROW_MARGIN_X, ICON_HEIGHT + ICON_MARGIN_Y);
    keyIcons_[3].setPosition(ICON_SECOND_ROW_MARGIN_X + ICON_WIDTH + ICON_MARGIN_X, ICON_HEIGHT + ICON_MARGIN_Y);

    setPosition(UI_POS_X, UI_POS_Y);
}

void KeybindUI::handleEvent(const sf::Event& event)
{
    switch (event.type)
    {
    case sf::Event::MouseMoved:
        handleEvent(event.mouseMove);
        break;
    case sf::Event::MouseButtonPressed:
        handleEvent(event.mouseButton);
        break;
    }

    for (auto& keyIcon : keyIcons_)
        keyIcon.handleEvent(event);
}

void KeybindUI::update(const sf::Time& dt)
{
    for (KeyIcon& keyIcon : keyIcons_)
        keyIcon.update(dt);
}

void KeybindUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    for (const KeyIcon& keyIcon : keyIcons_)
        keyIcon.draw(target, states);

    // states are not applied to the help message, to use absolute coordinate.
    // This is a very lazy implementation;  but it simplifies the codebase.
    target.draw(helpMessage_);
}

void KeybindUI::handleEvent(const sf::Event::MouseButtonEvent& event)
{
    if (event.button == sf::Mouse::Button::Left)
    {
        KeyIcon* prevSelectedKey = getSelectedKey();
        KeyIcon* currClickedKey = nullptr;
        const sf::Vector2f mousePos(event.x, event.y);
        for (auto& keyIcon : keyIcons_)
        {
            if (pointHoverOnKeyIcon(mousePos, keyIcon))
            {
                currClickedKey = &keyIcon;
                break;
            }
        }

        if (prevSelectedKey)
        {
            if (currClickedKey)
            {
                if (prevSelectedKey == currClickedKey)
                {
                    currClickedKey->setState(KeyIcon::State::MOUSE_HOVER);
                }
                else
                {
                    // Swap keys
                    prevSelectedKey->setState(KeyIcon::State::NONE);
                    inputHandler_.swapKeys(prevSelectedKey->getKey(), currClickedKey->getKey());
                    prevSelectedKey->swapKeybindText(*currClickedKey);

                    global::logger->AddLog("=======================================================\n");
                    const char swapped1 = InputHandler::KEY_CHARS[currClickedKey->getKey()];
                    const char swapped2 = InputHandler::KEY_CHARS[prevSelectedKey->getKey()];
                    global::logger->AddLog("<1> KeybindUI::handleEvent(const sf::Event::MouseButtonEvent&) calls\n");
                    global::logger->AddLog("    InputHandler::swapKeys(Key::%c, Key::%c).\n", swapped2, swapped1);
                    global::logger->AddLog("<2> buttons_[Key::%c].swap(buttons_[Key::%c]) called.\n", swapped2,
                                           swapped1);
                }
            }
            else
            {
                prevSelectedKey->setState(KeyIcon::State::NONE);
            }
        }
        else
        {
            if (currClickedKey)
            {
                currClickedKey->setState(KeyIcon::State::SELECTED);
            }
        }
    }
}

void KeybindUI::handleEvent(const sf::Event::MouseMoveEvent& event)
{
    // TODO
    const sf::Vector2f mousePos(event.x, event.y);

    for (int i = 0; i < TOTAL_BUTTONS; ++i)
    {
        const bool isHover = pointHoverOnKeyIcon(mousePos, keyIcons_[i]);
        const auto state = keyIcons_[i].getState();
        if (isHover && (state == KeyIcon::State::NONE))
            keyIcons_[i].setState(KeyIcon::State::MOUSE_HOVER);
        else if (!isHover && (state == KeyIcon::State::MOUSE_HOVER))
            keyIcons_[i].setState(KeyIcon::State::NONE);
    }
}

bool KeybindUI::pointHoverOnKeyIcon(const sf::Vector2f& point, const KeybindUI::KeyIcon& keyIcon) const
{
    const sf::FloatRect buttonRect{0, 0, ICON_WIDTH, ICON_HEIGHT};
    auto movedPos = (keyIcon.getInverseTransform() * getInverseTransform()).transformPoint(point);
    return buttonRect.contains(movedPos);
}

KeybindUI::KeyIcon* KeybindUI::getSelectedKey()
{
    for (auto& keyIcon : keyIcons_)
        if (keyIcon.getState() == KeyIcon::State::SELECTED)
            return &keyIcon;
    return nullptr;
}

} // namespace igpp::c02_01
