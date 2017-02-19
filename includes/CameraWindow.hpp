#ifndef _CAMERA_WINDOW_HPP__
#define _CAMERA_WINDOW_HPP__

#include <string>

#include "OpenCVWindow.hpp"
#include "Camera.hpp"
#include "TouchButton.hpp"

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
	 * @date       16-Feb-2017
	 * @brief      Lit une frame
	 */
	void readFrame(void);

	/**
	 * @date       15-Feb-2017
	 * @brief      Récupère la caméra
	 * @return     La caméra
	 */
	Camera& getCamera();

	/**
	 * @date       18-Feb-2017
	 * @brief      Retourne la Largeur de la fenetre
	 * @return     La Largeur de la fenetre
	 */
	int largeur();
	/**
	 * @date       18-Feb-2017
	 * @brief      Retourne la Hauteur de la fenetre
	 * @return     La Hauteur de la fenetre
	 */
	int hauteur();

private:
    Camera camera; //!< Camera de profondeur
    int _width;	   //!< Largeur de la fenetre de la caméra
    int _height;    //!< Hauteur de la fenetre de la caméra

};

#endif