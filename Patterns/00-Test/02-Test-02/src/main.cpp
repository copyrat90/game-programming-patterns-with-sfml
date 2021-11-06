#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <imgui-SFML.h>

#include "Common/ImguiLogger.hpp"

using namespace igpp;

int main()
{
    sf::RenderWindow window(sf::VideoMode(960, 540), "Hello SFML", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    ImGui::SFML::Init(window);
    common::ImguiLogger logger(common::ImguiLogger::CornerPos::UPPER_RIGHT, window.getSize(), ImVec2(300, 100));
    logger.AddLog("Hello, world!");

    sf::Clock deltaClock;

    // Game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        logger.Draw("Log window");

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
