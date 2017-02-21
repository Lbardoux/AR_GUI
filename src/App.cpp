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
			this->peinture.updateTime(this->setCursor);
		}

		this->peinture.updateWidgets();
		this->widgets.updateWidgets();

		this->peinture.draw(this->cameraW.getCamera().colorFrame());
        if (this->player.isVisible())
		{
            this->setCursor.draw(this->cameraW.getCamera().colorFrame());
        }
		this->widgets.draw(this->cameraW.getCamera().colorFrame());
		this->windows.updateWindows();
		this->keyboard.checkInputs(12);
	}
	this->windows.closeWindows();
}

/*
        Camera *camera = new Camera();
        camera->init();
        camera->start(640, 480);
        Player player(*camera);

        GlContext::initGL(640, 480);
        Pipeline::fromXML("assets/PipelineConfig.xml");

        VertexShader vertex("assets/shaders/vertex.cpp");
        FragmentShader fragment("assets/shaders/fragment.cpp");
        ShaderProgram program({vertex, fragment});

        Mesh soubrette("assets/objs/soubrette.obj", "assets/objs/texture.bmp", program, Vector(0, -12.2, 0));

        Clothe clothe(player, LEFT_SHOULDER, RIGHT_SHOULDER, soubrette);

        MaidDrawer maid_drawer(player, clothe, program);
        maid_drawer.draw();

        GlContext::endGL();
*/

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
	this->initWindows();
	this->initWidgets();

	this->player.init(this->cameraW.getCamera());
	this->setCursor.init();
	this->peinture.init(this->cameraW.largeur(), this->cameraW.hauteur(), "assets/ModulePeinture.xml");
}


void App::initWindows(void)
{
    this->programState.setName("RED = KO / GREEN = OK");
    this->programState.open(0u, 0u);
    this->windows.addWindow(&this->programState);

	// Fenetre de la camera
	this->cameraW.init("Camera", 640, 480);
	this->windows.addWindow(&this->cameraW);
}

void App::initWidgets(void)
{
	this->quitter.init("Quitter", [this]() { this->process = false; }, &Sprites::test,
	                   this->cameraW.largeur() - Sprites::test.cols - 10,
	                   this->cameraW.hauteur() - Sprites::test.rows - 25, 3);
	this->quitter.addMembre(PlayerMember::LEFT_HAND).addMembre(PlayerMember::RIGHT_HAND)
                 .addMembre(PlayerMember::LEFT_FOOT).addMembre(PlayerMember::RIGHT_FOOT);
	this->widgets.addWidget(&this->quitter);
}
