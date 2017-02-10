/**
 * @file App.hpp
 * @brief Une classe qui va embarquer le nécessaires à la gestion de l'application.
 * @author Laurent BARDOUX p1108365
 */
#ifndef APP_HPP_INCLUDED
#define APP_HPP_INCLUDED

#include <functional>
#include "KeyboardMapping.hpp"
#include "WindowsManager.hpp"

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
		
		
		KeyboardMapping& getKeyboard(void) noexcept;
		WindowsManager& getWindowsManager(void) noexcept;
		
		
	private:
		KeyboardMapping<char, std::function<void(void)>> keyboard; //!< Les actions pour le clavier.
		WindowsManager                                   windows;  //!< Les fenetres de l'application.
		bool                                             process;  //!< Etat de l'application (true on continue, false on quitte).
		
		
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
