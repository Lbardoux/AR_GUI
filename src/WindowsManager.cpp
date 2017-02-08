/**
 * @file WindowsManager.cpp
 */
#include <algorithm>
#include <functional>
#include <iostream>

#include "WindowsManager.hpp"


WindowsManager::WindowsManager(void) noexcept
{
    
}

WindowsManager::~WindowsManager(void)
{
    this->windows.clear();
}

void WindowsManager::closeWindows(void)
{
    std::for_each(this->windows.begin(), this->windows.end(), [](Window* w){
        w->close();
    });
}

void WindowsManager::updateWindows(void)
{
    std::for_each(this->windows.begin(), this->windows.end(), [](Window* w){
        w->update();
    });
}

WindowsManager& WindowsManager::addWindow(Window* window)
{
    this->windows.push_back(window);
    return *this;
}
