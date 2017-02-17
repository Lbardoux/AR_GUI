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
#include "Sprite.hpp"
#include "vec.hpp"
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
class Cursor
{
    public:
        static Interval vertical;   //!< Un buffer pour stocker l'intervalle de définition vertical   (en y).
        static Interval horizontal; //!< Un buffer pour stocker l'intervalle de définition horizontal (en x).
                                    
        /**
         * @brief Construit un curseur
         * 
         * On peut également définir sa position ((0,0) par défaut), et tout overflow par rapport
         * aux intervalles seront corrigés.
         * @param[in] x       La position x initiale du curseur.
         * @param[in] y       La position y initiale du curseur.
         */
        Cursor(uint32_t x=0u, uint32_t y=0u) noexcept;
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

		Cursor(const nite::Point3f& p)
		{
			x(p.x);
            y(p.y);
		}

        template<typename T>
        Cursor(const T& t)
        {
            x(t.x());
            y(t.y());
        }
		
		

        //! @brief Remet tout à zéro.
        ~Cursor(void) noexcept;
        
        uint32_t x(void)         const noexcept;
        uint32_t y(void)         const noexcept;
        Cursor& x(uint32_t value)      noexcept;
        Cursor& y(uint32_t value)      noexcept;

        Cursor& operator=(const Cursor& cursor);        
        
    protected:
        uint32_t _x; //!< La position horizontale sur l'image (@b x eme colonne).
        uint32_t _y; //!< La position verticale   sur l'image (@b y eme ligne).
        
        /**
         * @brief remet toutes les valeurs à zéro.
         */
        virtual void reset(void) noexcept;
    
};



class ColoredCursor final : public Cursor
{
    public:
        ColoredCursor(const Cursor& cursor, const mat_data_t& color=matRedColor(), uint32_t radius=3u);
        ColoredCursor(uint32_t x=0u, uint32_t y=0u, uint32_t radius=3u, const mat_data_t& color=matRedColor());
        template<typename T>
        ColoredCursor(const T& t, const mat_data_t& color=matRedColor()) : Cursor(t), _color(color)
        {

        }

        ~ColoredCursor();

        uint32_t       radius(void)     const noexcept;
        ColoredCursor& radius(uint32_t value) noexcept;
        
        ColoredCursor& operator=(const ColoredCursor& c);
        ColoredCursor& operator=(const mat_data_t& c);

        void setColor(const mat_data_t& color);

        /**
         * @date          08-Feb-2017
         * @brief         Dessine un curseur.
         * @param[in,out] frame  La frame
         */
        void draw(cv::Mat& frame) const noexcept;
        
    private:
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
        uint32_t _radius;  //!< Rayon du ColoredCursor pour l'affichage. Un rayon de 1 correspond à 1 pixel
        Sprite _spr;       //!< Sprite du ColoredCursor
        mat_data_t _color; //!< Couleur du Sprite

        virtual void reset(void) noexcept;
};


#endif
