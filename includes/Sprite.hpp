/**
 * @file Sprite.hpp
 * @brief Offre un moyen de charger des sprites au format @b png.
 * 
 * On conserve @b png comme unique format.
 * @author Laurent BARDOUX p1108365
 */
#ifndef SPRITE_HPP_INCLUDED
#define SPRITE_HPP_INCLUDED

#include "Cv_core.hpp"


typedef cv::Mat Sprite; //!< Beaucoup plus simple à manipuler.


/**
 * @class Sprites
 * @brief Contient tous les sprites de l'application.
 * 
 * Méthode d'ajout :
 * Déclarer un Sprite static dans la partie publique de cette class.
 * @code
 * static Sprite spr_monsprite; //!< Un peu de doc silvoupliz.
 * @endcode
 * Puis ajouter dans le fichier @b Sprite.cpp la ligne suivante (avec les autres) :
 * @code
 * Sprite Sprites::spr_monsprite;
 * @endcode
 * 
 * Enfin, dans la fonction membre init(), ajouter le chargement de votre image.
 * Pour finir, libérer votre Sprite dans empty().
 */
class Sprites final
{
    public:
        static Sprite test;
        static cv::Size tailleIcone;
        /**
         * @brief Charge les sprites en un coup.
         * @throw std::runtime_error Si un chargement a échoué.
         */
        static void init(void);
        /**
         * @brief Vide les images.
         */
        static void empty(void);

        static Sprite spr_peinture_on;    //!< Sprite pour la peinture ON
        static Sprite spr_peinture_off;   //!< Sprite pour la peinture OFF
        static Sprite spr_peinture_reset; //!< Sprite pour réinitialiser la toile
        static Sprite spr_peinture_save;  //!< Sprite pour la sauvegarde de l'image
        static Sprite spr_clothe_on;      //!< Dessin pour la robe ON.
        static Sprite spr_clothe_off;     //!< Dessin pour la robe OFF.
        static Sprite spr_switch_on;      //!< Dessin pour changer de main ON
        static Sprite spr_switch_off;     //!< Dessin pour changer de main OFF
        static Sprite spr_print;          //!< Pour prendre en photo tout l'écran
};

/**
 * @brief Charge un sprite depuis le fichier @b fname.
 * @param[in]  fname Le nom du fichier, depuis la racine du projet.
 * @param[out] dst   Le réceptacle qui va stocker l'image.
 */
void loadSprite(const std::string& fname, Sprite& dst, bool resize = false);

/**
 * @brief Affiche @b dst sur @b sprite en mettant son origine à @b x et @b y.
 * @param[in,out] dst    La matrice sur laquelle on va dessiner.
 * @param[in]     sprite Ce qu'on veut dessiner.
 * @param[in]     x      La position x à laquelle dessiner.
 * @param[in]     y      La position y à laquelle dessiner.
 */
void blit(Sprite& dst, const Sprite& sprite, int x, int y);


/**
 * @date       19-Feb-2017
 * @brief      Rempli la bordure de la toile
 * @post       Le sprite aura une bordure carrée
 * @param      sprite            Sprite sur lequel on applique la bordure
 * @param[in]  color             Couleur de la bordure
 * @param[in]  epaisseurBordure  Epaisseur de la bordure
 * @param[in]  taillePointille   Ecart et taille en pointillé de la bordure. Si
 *                               ce paramètre vaut 0, alors pas de pointillé
 */
void fillBordure(Sprite& sprite, const mat_data_t& color, int epaisseurBordure, int taillePointille = 0);

#endif
