/**
 * @file Cursor.hpp
 * @brief Interface pour les éléments qui vont devoir intéragir avec un Cursor.
 * @author Laurent BARDOUX p1108365
 * @version 1.0
 */
#ifndef CURSORLISTENER_HPP_INCLUDED
#define CURSORLISTENER_HPP_INCLUDED

#include <cstdint> // Pour les uint*, permettant de choisir le nombre d'octets que l'on veut.
#include "Cv_core.hpp"
#include <NiTE.h>


/**
 * @struct Interval
 * @brief Un POD qui permet de construire un interval de valeur entières non signées.
 * On l'utilise de cette façon : {min, max} avec [min;max]
 */
struct Interval final
{
    uint32_t min; //!< La borne inférieure incluse de l'intervalle.
    uint32_t max; //!< La borne supérieure incluse de l'intervalle.
};

/**
 * @class Cursor
 * @brief Cette structure embarque ce qu'il faut pour identifier un curseur, ie un doublet
 * de coordonnées @b x et @b y .
 * Ces valeurs sont bornées par des intervalles, afin de ne pas sortir de l'image.
 */
class Cursor final
{
    public:
        /**
         * @date       09-Feb-2017
         * @brief      Constructeur par défaut
         */
        Cursor() noexcept;
        /**
         * @brief Construit un curseur en définissant son intervalle de définition.
         * 
         * On peut également définir sa position ((0,0) par défaut), et tout overflow par rapport
         * aux intervalles seront corrigés.
         * @param[in] hor     L'intervalle des valeurs pour @b x.
         * @param[in] ver     L'intervalle des valeurs pour @b y.
         * @param[in] x       La position x initiale du curseur.
         * @param[in] y       La position y initiale du curseur.
         * @param[in] radius  Rayon du curseur à afficher
         */
        Cursor(const Interval& hor, const Interval& ver, uint32_t x=0u, uint32_t y=0u, uint32_t radius=0u) noexcept;
        /**
         * @date       10-Feb-2017
         * @brief      Constructeur à partir d'un Point3f de Nite
         * @param[in]  vec   Le vecteur
         */
        Cursor(const nite::Point3f& vec) noexcept;
        /**
         * @brief Construit un nouveau curseur en copiant @b other.
         * @param[in] other Le curseur à copier.
         */
        Cursor(const Cursor& other) noexcept;
        /**
         * @brief Construit un nouveau curseur en déplaçant @b other.
         * @param[in,out] other Le curseur à déplacer.
         * @post @b other est désormais inutilisable.
         */
        Cursor(Cursor&& other) noexcept;
        //! @brief Remet tout à zéro.
        ~Cursor(void) noexcept;
        
        uint32_t x(void)         const noexcept;
        uint32_t y(void)         const noexcept;
        uint32_t radius(void)    const noexcept;
        Cursor& x(uint32_t value)      noexcept;
        Cursor& y(uint32_t value)      noexcept;
        Cursor& radius(uint32_t value) noexcept;

        Cursor& operator=(const Cursor& cursor);

        /**
         * @date          08-Feb-2017
         * @brief         Dessine un curseur.
         * @param[in,out] frame  La frame
         * @param[in]     color  Couleur du curseur
         */
        void draw(cv::Mat& frame, const mat_data_t& color = matRedColor()) const noexcept;
        
        
        
    private:
        Interval vertical;   //!< Un buffer pour stocker l'intervalle de définition vertical   (en y).
        Interval horizontal; //!< Un buffer pour stocker l'intervalle de définition horizontal (en x).
        uint32_t _x;         //!< La position horizontale sur l'image (@b x eme colonne).
        uint32_t _y;         //!< La position verticale   sur l'image (@b y eme ligne).
        /**
         * Rayon du cursor pour l'affichage.
         * @code
         * +-------------------------> _x
         * |    ***
         * |    ***           *
         * |    ***
         * |
         * | _radius=1    _radius=0
         * v
         * _y
         * @endcode
         */
        uint32_t _radius;    //!< Rayon du cursor pour l'affichage. Un rayon de 1 correspond à 1 pixel
        
        /**
         * @brief remet toutes les valeurs à zéro.
         */
        void reset(void) noexcept;
    
};



#endif
