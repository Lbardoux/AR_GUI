/**
 * @file SetCursor.hpp
 * @brief Classe regroupant un ensemble de Cursor
 * @author Mehdi GHESH p1209574
 * @version 1.0
 */
#ifndef _SET_CURSOR_HPP__
#define _SET_CURSOR_HPP__ 

#include <map>
#include "Cv_core.hpp"
#include "Cursor.hpp"

// Todo : Ajouter le nombre de valeurs dans l'enum de Charles
enum Charles_enum_type{EMPTY};

typedef std::pair<Cursor, mat_data_t> coloredCursor_t; //!< Encapsulation d'un curseur et de sa couleur
typedef std::map<Charles_enum_type, coloredCursor_t> mapCursor_t; //!< Map contenant un ensemble de curseurs colorés

class SetCursor final
{
public:
	SetCursor();
	~SetCursor();


	/**
	 * @date       08-Feb-2017
	 * @brief      Ajoute/modifie le curseur du type demandé
	 * Si une valeur est déjà présente pour le type demandé, elle est écrasée
	 * @param[in]  type    Type du curseur à ajouter/modifier
	 * @param[in]  cursor  Curseur à enregistrer
	 * @param[in]  color   Couleur du curseur
	 * @post       Le curseur du type demandé aura les nouvelles valeurs
	 */
	void addCursor(Charles_enum_type type, const Cursor& cursor, const mat_data_t& color=matRedColor());

	/**
	 * @date       08-Feb-2017
	 * @brief      Mise à jour du curseur du type demandé
	 * @param[in]  type    Type du curseur à modifier
	 * @param[in]  cursor  Nouvelle valeur du curseur
	 * @pre        Le type demandé a déjà été ajouté
	 */
	void updateCursor(Charles_enum_type type, const Cursor& cursor);

	/**
	 * @date       08-Feb-2017
	 * @brief      Mise à jour de la couleur du cureseur du type demandé
	 * @param[in]  type   Type du curseur à modifier
	 * @param[in]  color  Nouvelle couleur du curseur
	 * @pre        Le type demandé a déjà été ajouté
	 */
	void updateColor(Charles_enum_type type, const mat_data_t& color);

	/**
	 * @date       08-Feb-2017
	 * @brief      Récupère le curseur en lecture seule pour le type demandé
	 * @param[in]  type  Type du curseur
	 * @return     Le curseur
	 */
	const Cursor& getCursor(Charles_enum_type type) const;
	/**
	 * @date       08-Feb-2017
	 * @brief      Récupère le curseur en lecture/écriture pour le type demandé
	 * @param[in]  type  Type du curseur
	 * @return     Le curseur
	 */
	Cursor& getCursor(Charles_enum_type type);

	mapCursor_t::const_iterator begin() const;
	mapCursor_t::iterator begin();
	mapCursor_t::const_iterator end() const;
	mapCursor_t::iterator end();

	/**
	 * @date       08-Feb-2017
	 * @brief      Affichage d'un ensemble de curseur dans la frame
	 * @param      frame  La frame
	 */
	void update(cv::Mat& frame);

private:
	mapCursor_t _cursors; //!< Ensemble des cursors
};

#endif