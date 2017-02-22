/**
 * @file CursorSet.hpp
 * @brief Classe regroupant un ensemble de Cursor
 * @author Mehdi GHESH p1209574
 * @version 1.0
 */
#ifndef _SET_CURSOR_HPP__
#define _SET_CURSOR_HPP__ 

#include <map>
#include "Cv_core.hpp"
#include "Cursor.hpp"
#include "Player.hpp"

typedef ColoredCursor coloredCursor_t; //!< Encapsulation d'un curseur et de sa couleur
typedef std::map<PlayerMember, coloredCursor_t> mapCursor_t; //!< Map contenant un ensemble de curseurs colorés

class CursorSet final
{
public:
    CursorSet();
    ~CursorSet();

	/**
	 * @date       16-Feb-2017
	 * @brief      Initialise l'ensemble des Cursor à partir du Player
	 * @param[in]  color   Couleur des Cursor
	 */
	void init(const mat_data_t& color=matRedColor());

    /**
     * @date       08-Feb-2017
     * @brief      Ajoute/modifie le curseur du type demandé
     * Si une valeur est déjà présente pour le type demandé, elle est écrasée
     * @param[in]  type    Type du curseur à ajouter/modifier
     * @param[in]  cursor  Curseur à enregistrer
     * @param[in]  color   Couleur du curseur
     * @post       Le curseur du type demandé aura les nouvelles valeurs
     */
    void addCursor(PlayerMember type, const ColoredCursor& cursor);

    /**
     * @date       08-Feb-2017
     * @brief      Mise à jour du curseur du type demandé
     * @param[in]  type    Type du curseur à modifier
     * @param[in]  cursor  Nouvelle valeur du curseur
     * @pre        Le type demandé a déjà été ajouté
     */
    void updateCursor(PlayerMember type, const ColoredCursor& cursor);

    /**
     * @date       08-Feb-2017
     * @brief      Mise à jour de la couleur du cureseur du type demandé
     * @param[in]  type   Type du curseur à modifier
     * @param[in]  color  Nouvelle couleur du curseur
     * @pre        Le type demandé a déjà été ajouté
     */
    void updateColor(PlayerMember type, const mat_data_t& color);

    /**
     * @date       08-Feb-2017
     * @brief      Récupère le curseur en lecture seule pour le type demandé
     * @param[in]  type  Type du curseur
     * @return     Le curseur
     */
    const ColoredCursor& getCursor(PlayerMember type) const;
    /**
     * @date       08-Feb-2017
     * @brief      Récupère le curseur en lecture/écriture pour le type demandé
     * @param[in]  type  Type du curseur
     * @return     Le curseur
     */
    ColoredCursor& getCursor(PlayerMember type);

    mapCursor_t::const_iterator begin() const;
    mapCursor_t::iterator begin();
    mapCursor_t::const_iterator end() const;
    mapCursor_t::iterator end();

    /**
     * @date       08-Feb-2017
     * @brief      Affichage d'un ensemble de curseur dans la frame
     * @param      frame  La frame
     */
    void draw(cv::Mat& frame);

    /**
     * @date       09-Feb-2017
     * @brief      Mets à jour les positions des curseurs
     * @param[in]  player  Squelette qui contient les informations des positions
     */
    void update(const Player& player);
    void setIsIn(bool value) const;
    bool isInBoundingBox(PlayerMember type) const;

private:
    mapCursor_t _cursors; //!< Ensemble des cursors
    int xmin, xmax; //!< Les coordonnées X de la boite englobante.
    int ymin, ymax; //!< Les coordonnées Y de la boite englobante.
    mutable bool isIn;      //!< Pour savoir si on est dans la BBox ce coup-ci.
};

#endif
