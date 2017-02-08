/**
 * @file WindowsManager.cpp
 */
#include <algorithm>
#include <functional>

#include "WindowsManager.hpp"



WindowsManager::WindowsManager(void) noexcept
{
    
}

WindowsManager::~WindowsManager(void)
{
    std::for_each(this->windows.begin(), this->windows.end(), [](Window* w){
        w->close();
        delete w;
    });
    this->windows.clear();
    this->windowsNames.clear();
}
