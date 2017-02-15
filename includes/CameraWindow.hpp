#ifndef _CAMERA_WINDOW_HPP__
#define _CAMERA_WINDOW_HPP__ 

#include <string>

#include "OpenCVWindow.hpp"
#include "Camera.hpp"

class Player;

class CameraWindow final : public OpenCVWindow
{
public:
	CameraWindow();
	~CameraWindow();

	/**
	 * @date       14-Feb-2017
	 * @brief      Initialise la CameraWindow
	 * Par défaut les paramètres valent :
	 * \tname   = "CameraWindow"
	 * \twidth  = 640
	 * \theight = 480 
	 * @param[in]  name    Nom de la fenetre
	 * @param[in]  width   Largeur de la fenetre
	 * @param[in]  height  Hauteur de la fenetre
	 */
	void init(const std::string& name = "CameraWindow", int width = 640, int height = 480);
	
	void close(void) override;
	void update(void) override;

	/**
	 * @date       15-Feb-2017
	 * @brief      Récupère la caméra
	 * @return     La caméra
	 */
	Camera& getCamera();

private:
	Camera camera; //!< Camera de profondeur

};

#endif