#ifndef _PAINT_MODULE
#define _PAINT_MODULE 

#include "Cv_core.hpp"
#include "Sprite.hpp"
#include "ActionButton.hpp"
#include "Player.hpp"

enum Emplacement
{
	HAUT_GAUCHE = 0,
	HAUT_DROIT,
	BAS_GAUCHE,
	BAS_DROIT,
	NB_PLACEMENT
};

typedef std::pair<ActionButton*, Sprite*> coloredButton_t;

#define COULEUR_HAUTEUR  50
#define COULEUR_LONGUEUR 50
#define ACTIVATION_PEINTURE 3

class PaletteCouleur
{
	public:
		PaletteCouleur();
		~PaletteCouleur();
		
		/**
		 * @date       18-Feb-2017
		 * @brief      Initialise une palette
		 * @param      couleur  Sprite qui contient la couleur choisie
		 * @param[in]  rows     Nombre de ligne de couleur dans la palette
		 * @param[in]  cols     Nombre de colonne de couleur dans la palette
		 * @param[in]  x        Position en X de la palette
		 * @param[in]  y        Position en Y de la palette
		 */
		void init(Sprite* couleur, uint32_t rows, uint32_t cols, uint32_t x=0, uint32_t y=0);
		//! @brief Appelle la méthode update du manager de Widget
        void updateWidgets(void);
        //! @brief Appelle la méthode updateTime du manager de Widget
        void updateTime(const CursorSet& cursors);
        //! @brief      Ajoute une couleur à la palette
        PaletteCouleur& addCouleur(const mat_data_t& color);
		/**
		 * @date       18-Feb-2017
		 * @brief      Affiche la palette
		 * @param[in]  frame  Frame sur laquelle on affiche
		 */
		void draw(cv::Mat& frame);

		/**
		 * @date       19-Feb-2017
		 * @brief      Récupère la couleur sélectionnée sur la palette
		 * @return     La couleur
		 */
		mat_data_t getCouleur() const;

		uint32_t x() const;
		PaletteCouleur& x(uint32_t x);
		uint32_t y() const;
		PaletteCouleur& y(uint32_t y);

		friend class PaintModule;
	private:
		std::vector<WidgetManager> ensembleCouleur;  //!< Toutes les couleurs permettant de dessiner
		std::vector<coloredButton_t> ensembleSprite;  //!< Tous les Sprites contenant les couleurs

		Sprite* couleur; //!< La couleur sélectionnée
		bool visible;
		uint32_t _x; //!< Coordonées en X de le palette
		uint32_t _y; //!< Coordonées en Y de le palette
		uint32_t _rows; //!< Nombre de ligne de couleur dans la palette
		uint32_t _cols; //!< Nombre de colonne de couleur dans la palette
};

class PaintModule
{
	public:
		PaintModule();
		~PaintModule();

		/**
		 * @date       18-Feb-2017
		 * @brief      Initialise le module de Peinture
		 * @param[in]  width   Longueur de la fenetre
		 * @param[in]  height  Hauteur de la fenetre
		 * @param[in]  membre  Membre qui peut intéragir, qui peint
		 */
		void init(int width, int height, PlayerMember membre=PlayerMember::RIGHT_HAND);
		/**
		 * @date       18-Feb-2017
		 * @brief      Indique le membre qui peut intéragir avec le module
		 * @param[in]  p     Membre qui intéragira
		 */
		void membreQuiPeint(PlayerMember p);
		/**
		 * @date       18-Feb-2017
		 * @brief      Rend visible ou non le module de peinture
		 * @param[in]  val   Visibilité
		 */
		void rendVisible(bool val);
		/**
		 * @date       19-Feb-2017
		 * @brief      Active ou désactive la peinture
		 * @param[in]  val   Valeur de la peinture
		 */
		void peinture(bool val);
		/**
		 * @date       19-Feb-2017
		 * @brief      Fonction qui remet la toile à 0 et tout ce qui va avec
		 */
		void resetToile();
		/**
		 * @date       19-Feb-2017
		 * @brief      Fonction qui sauvegarde la toile La toile est sauvegardée
		 *             dans le répertoire d'exécution
		 */
		void saveToile();
		/**
		 * @date       18-Feb-2017
		 * @brief      Indique ou sont disposés les widgets du module
		 * @param[in]  e     Emplacement des widgets
		 */
		void setEmplacement(Emplacement e);
		//! @brief Appelle la méthode update du manager de Widget
        void updateWidgets(void);
        //! @brief Appelle la méthode updateTime du manager de Widget
        void updateTime(const CursorSet& cursors);
		/**
		 * @date       18-Feb-2017
		 * @brief      Affiche le module de Peinture
		 * @param[in]  frame  Frame sur laquelle on affiche
		 */
		void draw(cv::Mat frame);

	private:
		bool visible;  					//!< Indique si le module de peinture est visible
		WidgetManager widgets;			//!< Ensemble des widgets du module de Peinture
		PaletteCouleur palette;			//!< Palette de couleur du module
		ActionButton activePeinture; 	//!< Widget pour activer / désactiver le mode peinture

		Sprite spr_palette; 			//!< Icone de la palette
		ActionButton ouvrePalette; 		//!< Widget qui permet d'ouvrir la palette des couleurs
		ActionButton reset;				//!< Bouton pour remettre la toile à 0

		const int pidSauvegarde;		//!< PID du programme, pour faire des sauvegardes uniques
		int numeroSauvegarde;			//!< Numéro du dessin à sauvegarder
		ActionButton sauvegarde;		//!< Bouton de sauvegarde de l'image

		Emplacement emplacement; 		//!< Emplacement des widgets du module
		PlayerMember membre; 			//!< Membre qui peut intéragire avec le module / qui peint

		cv::Mat toile; 					//!< Toile qui contient le dessin
		ColoredCursor pinceau;			//!< Représente le pinceau
		int toileX;						//!< Coordonnées en X de la toile 
		int toileY;						//!< Coordonnées en Y de la toile 
		int tailleBordure;				//!< Taille de la bordure de la toile
		bool peintureActif;				//!< Indique si le mode peinture est actif

		int width;						//!< Largeur de la fenetre
		int height;						//!< Hauteur de la fenetre

		/**
		 * @date       19-Feb-2017
		 * @brief      Rempli la bordure de la toile
		 */
		void fillBordure();
};

#endif	