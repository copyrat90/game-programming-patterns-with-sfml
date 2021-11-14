#include "Application.hpp"

#include <imgui-SFML.h>

#include "Dwarf.hpp"
#include "global.hpp"

namespace igpp::c02_01
{

Application::Application()
    : window_(sf::VideoMode(960, 540), "02_Command_01_Configure_Input_and_Actors",
              sf::Style::Titlebar | sf::Style::Close)
{
    window_.setFramerateLimit(60);
    textures_.load(TextureId::DWARF, "assets/dwarf.png");
    fonts_.load(FontId::D2CODING, "assets/d2coding.ttf");

    actors_.push_back(std::make_unique<Dwarf>(textures_, fonts_));
    dwarf_ = actors_[0].get();

    ImGui::SFML::Init(window_);
    global::logger.emplace(common::ImguiLogger::CornerPos::UPPER_RIGHT, window_.getSize(), ImVec2(620, 170));

    global::logger->AddLog("Program started\n");
}

Application::~Application()
{
    ImGui::SFML::Shutdown();
}

void Application::run()
{
    sf::Clock deltaTimer;
    while (window_.isOpen())
    {
        processEvents();
        update(deltaTimer.restart());
        render();
    }
}

void Application::processEvents()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);

        if (event.type == sf::Event::Closed)
            window_.close();
    }

    // Snippet from the book
    Command* command = inputHandler_.handleInput();
    if (command)
        command->execute(*dwarf_);
}

void Application::update(const sf::Time& deltaTime)
{
    for (auto& actor : actors_)
        actor->update(deltaTime);

    ImGui::SFML::Update(window_, deltaTime);
}

void Application::render()
{
    window_.clear();

    for (const auto& actor : actors_)
        window_.draw(*actor);

    global::logger->Draw("Log Window");

    ImGui::SFML::Render(window_);
    window_.display();
}

} // namespace igpp::c02_01
