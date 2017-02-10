/**
 * @file App.cpp
 */


#include "App.hpp"
#include "GlCore.hpp"
#include "GlContext.hpp"
#include "Pipeline.hpp"

App::App(void) noexcept : process(true)
{
	this->initLibs();
	this->initInputs();
	this->initComponents();
	
}

App::~App(void) noexcept
{
	
}

void App::quit(void)
{
#ifdef USING_OPENGL
	GlContext::endGL();
#endif
}

void App::mainLoop(void)
{
	this->process = true;
	while(this->process)
	{
		this->windows.updateWindows();
		this->keyboard.checkInputs(25);
	}
	this->windows.closeWindows();
}


KeyboardMapping<char, std::function<void(void)>>& App::getKeyboard(void) noexcept
{
	return this->keyboard;
}

WindowsManager& App::getWindowsManager(void) noexcept
{
	return this->windows;
}

void App::initInputs(void)
{
#ifndef USING_OPENGL
	this->keyboard.addAction('q', [this](void){this->process = false;});
	this->keyboard.addAction('e', [this](void){this->programState.setState(true);});
	this->keyboard.addAction('d', [this](void){this->programState.setState(false);});
#endif
}

void App::initLibs(void)
{
#ifdef USING_OPENGL
	GlContext::initGL(640, 480);
	GlContext::windowCaption("OpenGL window");
	Pipeline::fromXML("assets/PipelineConfig.xml");
#endif
	
}

void App::initComponents(void)
{
#ifndef USING_OPENGL
	this->programState.setName("RED = KO / GREEN = OK");
	this->programState.open(0u, 0u);
	this->windows.addWindow(&this->programState);
#endif
}
