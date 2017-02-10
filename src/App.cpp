/**
 * @file App.cpp
 */


#include "App.hpp"


App::App(void) noexcept : keyboard(), windows(), process(true)
{
	this->initLibs();
	this->initInputs();
	this->initComponents();
	
}

App::~App(void) noexcept
{
	
}

void App::mainLoop(void)
{
	this->
	
	
	
}


KeyboardMapping& App::getKeyboard(void) noexcept
{
	return this->keyboard;
}

WindowsManager& App::getWindowsManager(void) noexcept
{
	return this->windows;
}

void App::initInputs(void)
{
	this->keyboard->addAction('q', [&process](void){process = false;});
	
}

void App::initLibs(void)
{
	
}

void App::initComponents(void)
{
	
}
