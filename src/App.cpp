/**
 * @file App.cpp
 */


#include "App.hpp"
#include "GlCore.hpp"
#include "GlContext.hpp"
#include "Pipeline.hpp"


App::App(void) noexcept : process(true)//, actionCatch(&Sprites::test, "Saisir"), actionQuit(&Sprites::test, "Quitter")
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
	mtl::log::info("Aboutissement de l'application");
	Sprites::empty();
}

void App::mainLoop(void)
{
	mtl::log::info("Démarrage de la Main loop");
	this->process = true;
	while(this->process)
	{
		this->cameraW.readFrame();
		
		this->player.update();
		this->programState.setState(this->player.isVisible());
		// this->actionCatch.draw(this->cameraW.getCamera().colorFrame());
		// this->actionQuit.draw(this->cameraW.getCamera().colorFrame());
		
		if (this->player.isVisible())
		{
			this->setCursor.update(this->player);
			this->setCursor.draw(this->cameraW.getCamera().colorFrame());
			this->widgets.updateTime(this->setCursor);
		}

		this->widgets.updateWidgets();
		this->widgets.draw(this->cameraW.getCamera().colorFrame());
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
    this->keyboard.addAction('q', [this](void){this->process = false;});
    this->keyboard.addAction('e', [this](void){this->programState.setState(true);});
    this->keyboard.addAction('d', [this](void){this->programState.setState(false);});
}

void App::initLibs(void)
{
	mtl::log::info("Initialisation des libraires");
	Sprites::init();
}

void App::initComponents(void)
{
    this->programState.setName("RED = KO / GREEN = OK");
    this->programState.open(0u, 0u);
    this->windows.addWindow(&this->programState);

	// Fenetre de la camera
	this->cameraW.init("Camera", 640, 480);
	this->windows.addWindow(&this->cameraW);

	this->player.init(this->cameraW.getCamera());
	// this->actionCatch.x() = 0;
	// this->actionCatch.y() = 400;
	// this->actionQuit.x() = 96;
	// this->actionQuit.y() = 400;
	// this->setCursor.init(this->player);
	this->setCursor.init();

	this->quitter.init("Quitter", [this]() { this->process = false; }, &Sprites::test, 5, 5, 3);
	this->quitter.addMembre(PlayerMember::LEFT_HAND).addMembre(PlayerMember::RIGHT_HAND);
	// this->quitter.membres.push_back(PlayerMember::LEFT_HAND);
	// this->quitter.membres.push_back(PlayerMember::RIGHT_HAND);
	this->widgets.addWidget(&this->quitter);
}
