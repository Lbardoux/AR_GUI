/**
 * @file App.cpp
 */


#include "App.hpp"
#include "GlCore.hpp"
#include "GlContext.hpp"
#include "Pipeline.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Player.hpp"
#include "Mesh.hpp"
#include "vec.hpp"
#include "Clothe.hpp"
#include "MaidDrawer.hpp"

#include "fbo2cvmat.hpp"


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
    mtl::log::info("Fermeture des fenetres");
	this->windows.closeWindows();
    QuitOpenNI();
	Sprites::empty();
    mtl::log::info("Extinction du contexte OpenGL");
    GlContext::endGL();
    mtl::log::info("Aboutissement de l'application");
}

void App::mainLoop(void)
{
	this->process = true;
    mtl::log::info("Chargement du contexte OpenGL --->", mtl::log::hold_on());
    GlContext::initGL(this->cameraW.largeur(), this->cameraW.hauteur());
    mtl::log::info("OK");
    
    mtl::log::info("Chargement de la configuration du pipeline --->", mtl::log::hold_on());
    Pipeline::fromXML("assets/PipelineConfig.xml");
    mtl::log::info("OK");
    
    mtl::log::info("Chargement des shaders : ", mtl::log::hold_on());
    VertexShader vertex("assets/shaders/vertex.cpp");
    mtl::log::info("vertex(OK) ", mtl::log::hold_on());
    FragmentShader fragment("assets/shaders/fragment.cpp");
    mtl::log::info("fragment(OK)", mtl::log::hold_on());
    ShaderProgram program({vertex, fragment});
    mtl::log::info("shaderProgram(OK)");
    
    Mesh soubrette("assets/objs/soubrette.obj", "assets/objs/texture.bmp", program, Vector(0, -12.2, 0));
    Clothe clothe(this->player, PlayerMember::LEFT_SHOULDER, PlayerMember::RIGHT_SHOULDER, soubrette);
    MaidDrawer maid_drawer(this->player, clothe, program);
    cv::Mat my_beautiful_clothe;
    
    mtl::log::info("Démarrage de la Main loop");
	while(this->process)
	{
		this->cameraW.readFrame();
		this->player.update();
		this->programState.setState(this->player.isVisible());
		if (this->player.isVisible())
		{
			this->setCursor.update(this->player);
			this->setCursor.draw(this->cameraW.getCamera().colorFrame());
			this->widgets.updateTime(this->setCursor);
			this->peinture.updateTime(this->setCursor);
            if (this->peinture.canDrawDress())
            {
                fbo2cvmat(maid_drawer.draw(), my_beautiful_clothe, this->cameraW.largeur(), this->cameraW.hauteur());
                blit(this->cameraW.getCamera().colorFrame(), my_beautiful_clothe, 0, 0);
            }
		}

		this->peinture.updateWidgets();
		this->widgets.updateWidgets();
		this->peinture.draw(this->cameraW.getCamera().colorFrame());
		this->widgets.draw(this->cameraW.getCamera().colorFrame());
        if (this->player.isVisible())
        {
            this->setCursor.draw(this->cameraW.getCamera().colorFrame());
        }
		this->windows.updateWindows();
		this->keyboard.checkInputs(6);
	}
    my_beautiful_clothe.release();
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
