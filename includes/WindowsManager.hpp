/**
 * @file WindowsManager.hpp
 * @brief Point culminant des gestionnaires de fenetres.
 * C'est cette classe qui appelera les prodécures d'ouvertures de fenetres (SDL2, OpenCV, as you wish).
 * @author Laurent BARDOUX p1108365
 * @version 1.0
 */
#ifndef WINDOWSMANAGER_HPP_INCLUDED
#define WINDOWSMANAGER_HPP_INCLUDED

#include <vector>
#include <string>
#include <cstdint>


/**
 * @class Window
 * @brief Interface pour tout type de fenetre.
 * 
 * Ajouter ici tous les éléments communs aux fenetres. 
 */
class Window
{
    public:
        /**
         * @brief Doit ouvrir une fenetre de taille <b>width</b>x<b>height</b> pixels.
         * @param[in] width  Le nombre de pixels horizontaux.
         * @param[in] height Le nombre de pixels verticaux.
         */
        virtual void open(uint32_t width, uint32_t height) =0;
        /**
         * @brief Vérifie que la fenetre s'est bien ouverte.
         * @return true si elle est bien ouverte, false sinon.
         */
        virtual bool isGood(void) const =0;
        /**
         * @brief Ferme cette fenetre.
         */
        virtual void close(void) =0;
        /**
         * @brief Ordonne de mettre à jour la fenetre.
         */
        virtual void update(void) =0;
        /**
         * @brief Permet de fixer un nom à la fenetre.
         * @param[in] name Le nom que l'on veut mettre sur la fenetre.
         */
        virtual void setName(const std::string& name) =0;
        //! @brief Permet le polymorphisme.
        virtual ~Window(void) {}
};


class WindowsManager final
{
    public:
        //! @brief Crée juste le gestionnaire.
        WindowsManager(void) noexcept;
        //! @brief Appelle la méthode close() de chaque fenetre.
        ~WindowsManager(void);
        //! @brief Appelle la méthode update pour toutes les fenetres.
        void updateWindows(void);
        /**
         * @brief Ajoute @b window au gestionnaire.
         * @param[in,out] window L'adresse de la fenetre à ajouter.
         * Le gestionnaire ne désallouera rien !
         * @return *this
         */
        WindowsManager& addWindow(Window* window);
        //! @brief Ferme toutes les fenetres.
        void closeWindows(void);
        
    private:
        std::vector<Window*> windows; //!< L'ensemble des fenetres utilisées.
        
        WindowsManager(const WindowsManager& other)            = delete;
        WindowsManager(WindowsManager&& other)                 = delete;
        WindowsManager& operator=(const WindowsManager& other) = delete;
        WindowsManager& operator=(WindowsManager&& other)      = delete;
        
};


#endif
