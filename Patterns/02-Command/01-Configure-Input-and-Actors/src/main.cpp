#include "Application.hpp"

#include <iostream>
#include <stdexcept>

using namespace igpp::c02_01;

int main()
{
    try
    {
        Application app;
        app.run();
    }
    catch (std::exception& e)
    {
        std::cout << "[ERROR] Exception thrown: " << e.what() << std::endl;
    }
    return 0;
}
