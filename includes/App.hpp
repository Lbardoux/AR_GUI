/**
 * @file App.hpp
 * @brief Une classe qui va embarquer le nécessaires à la gestion de l'application.
 * @author Laurent BARDOUX p1108365
 */
#ifndef APP_HPP_INCLUDED
#define APP_HPP_INCLUDED

#include <functional>
#include "Cv_core.hpp"
#include "KeyboardMapping.hpp"
#include "WindowsManager.hpp"
#include "SkeletonStateWindow.hpp"
#include "CameraWindow.hpp"
#include "Player.hpp"
#include "CursorSet.hpp"
#include "WidgetManager.hpp"
#include "ActionButton.hpp"
#include "TouchButton.hpp"
#include "PaintModule.hpp"


/**
 * @class App
 * @brief Embarque les modules essentiels de l'application et gère la logiqe applicative.
 */
class App final
{
	public:
		/**
		 * @brief Initialise les composants internes.
		 * Cela va également démarrer les libs, etc.
		 */
		App(void) noexcept;
		/**
		 * @brief Détruit les composants internes.
		 * Quitte les libs.
		 */
		~App(void) noexcept;
		/**
		 * @brief Met en place la boucle principale du programme.
		 */
		void mainLoop(void);
		/**
		 * @brief Vide tout.
		 */
		void quit(void);
		
		
		KeyboardMapping<char, std::function<void(void)>>& getKeyboard(void) noexcept;
		WindowsManager& getWindowsManager(void) noexcept;
		
		
	private:
		//---------------------------------------------------------------------
		//----------------- Déclaration des Windows ---------------------------
		//---------------------------------------------------------------------
		/**
		 * @date       18-Feb-2017
		 * @brief      Initialise les Fenetres de l'application
		 */
		void initWindows(void);
		WindowsManager      windows;      //!< Les fenetres de l'application.
		SkeletonStateWindow programState; //!< La fenetre qui affiche l'état du programme.
		CameraWindow        cameraW;      //!< Fenetre de la camera
		
		//---------------------------------------------------------------------
		//----------------- Déclaration des Widgets ---------------------------
		//---------------------------------------------------------------------
		/**
		 * @date       18-Feb-2017
		 * @brief      Initialise les Widgets de l'application
		 */
		void initWidgets(void);
		WidgetManager widgets; //!< Les Widgets de l'application.
		ActionButton  quitter; //!< Bouton qui quitte l'application
		ActionButton  paint;   //!< Bouton qui active la peinture
		
		KeyboardMapping<char, std::function<void(void)>> keyboard;     //!< Les actions pour le clavier.
		bool                                             process;      //!< Etat de l'application (true on continue, false on quitte).
		Player 											 player;	   //!< Joueur
		// ActionButton                                     actionCatch;
		// ActionButton                                     actionQuit;
		PaintModule 									 peinture; //!< Module de peinture
		
		CursorSet 										 setCursor;    //!< Ensemble des Cursor liés au Player

		/**
		 * @brief Fais le mapping des évènements claviers.
		 */
		void initInputs(void);
		/**
		 * @brief Charge ce qu'il faut pour NiTE, OpenNI, etc.
		 */
		void initLibs(void);
		/**
		 * @brief Applique les opérations supplémentaires pour l'initialisation des composants.
		 */
		void initComponents(void);
		
};




#endif
