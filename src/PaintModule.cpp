#include "PaintModule.hpp"
#include <sys/types.h>
#include <sstream>
#include <utility>
#include "clamp.hpp"

PaletteCouleur::PaletteCouleur() : couleur(NULL), visible(false)
{
    
}

int clampChannel(int value)
{
    return clamp<int>(value, 0, 255);
}

mat_data_t readColor(XmlLoader& loader)
{
    return
    mat_data_t(
        clampChannel(loader.element("bleu").text<int>()),
        clampChannel(loader.element("vert").text<int>()),
        clampChannel(loader.element("rouge").text<int>()),
        255
    );
}

void PaletteCouleur::readConfig(const std::string& fileName)
{
	// Lecture de la palette
    XmlLoader pLoader(fileName);
    mtl::log::info("Chargement de la Palette ", fileName);

    pLoader.node("parametres");

	this->_cols = pLoader.element("colonnes").text<int>();
	this->_rows = pLoader.element("lignes").text<int>();

	pLoader.node("taille");
	this->_square_width  = pLoader.element("width").text<int>();
	this->_square_height = pLoader.element("height").text<int>();
	pLoader.prev();

	pLoader.node("membres");
	pLoader.forEachElementNamed("membre", [this, &pLoader]() {
		this->ensembleMembre.push_back(static_cast<PlayerMember>(pLoader.text<int>()));
	});
	pLoader.prev();

	this->_activation_peinture = pLoader.element("tempsActivation").text<int>();

	// Node parametres
    pLoader.prev();
    pLoader.node("couleursPossibles");

    uint32_t nbCoul = 0;
    mtl::log::info("Chargement des couleurs de la Palette...");

    pLoader.forEachNodeNamed("couleur", [this, &pLoader, &nbCoul]() {
    	if(nbCoul < this->_cols * this->_rows)
    	{
	        std::string str = pLoader.attribute<std::string>("name");
	        mat_data_t color = readColor(pLoader);
	        mtl::log::info("---- Couleur : ", str, color);
	        this->addCouleur(color);
	        ++nbCoul;
	    }
    });

    mtl::log::info("Lecture de ", nbCoul, " couleur(s) sur les ", this->_cols * this->_rows, " requises");

    for(uint32_t i = nbCoul; i < this->_cols * this->_rows; ++i)
    	addCouleur(matBlackColor());
    
    // Application de la première couleur de la palette comme étant celle par défaut
    fillMat(*this->couleur, matAt(*this->ensembleSprite[0].second, 0, 0));
}

void PaletteCouleur::setCouleur(Sprite* couleur)
{
	this->couleur = couleur;
}

void PaletteCouleur::setEmplacement(int x, int y)
{
	this->x(x).y(y);
}

PaletteCouleur& PaletteCouleur::addCouleur(const mat_data_t& color)
{
	if (this->ensembleSprite.size() >= static_cast<unsigned int>(this->_rows * this->_cols))
	{
		mtl::log::warning("Impossible d'ajouter de Couleur à la Palette, il y a deja", this->_rows, 'x', this->_cols, "couleurs");
		return *this;
	}

	Sprite* spr = new Sprite(this->_square_width, this->_square_height, CV_8UC4);
	fillMat(*spr, color);

	int ind = static_cast<int>(this->ensembleSprite.size());
	int col = (ind % this->_cols);
	int row = (ind / this->_cols);

	ActionButton* bouton = new ActionButton;

	bouton->init("", [this, ind]() {
		this->ensembleSprite[ind].first->changeFirstActivation(false);
		fillMat(*this->couleur, matAt(*this->ensembleSprite[ind].second, 0, 0));
		this->visible = false;
	},
	spr,
	this->_x + (this->_square_width  * col),
	this->_y + (this->_square_height * row),
	this->_activation_peinture);
	bouton->addMembre(PlayerMember::LEFT_HAND).addMembre(PlayerMember::RIGHT_HAND);

	this->ensembleSprite.push_back(coloredButton_t(bouton, spr));

	if (col == 0)
	{
		WidgetManager manager;
		this->ensembleCouleur.push_back(manager);
	}

	this->ensembleCouleur[row].addWidget(this->ensembleSprite[ind].first);

	return *this;
}

PaletteCouleur::~PaletteCouleur()
{
	std::for_each(this->ensembleSprite.begin(), this->ensembleSprite.end(), [](coloredButton_t& c) {
		delete c.first;
		delete c.second;
	});
}

void PaletteCouleur::updateWidgets(void)
{
	std::for_each(this->ensembleCouleur.begin(), this->ensembleCouleur.end(), [](WidgetManager & w) {
		w.updateWidgets();
	});
}

void PaletteCouleur::updateTime(const CursorSet& cursors)
{
	std::for_each(this->ensembleCouleur.begin(), this->ensembleCouleur.end(), [&cursors](WidgetManager & w) {
		w.updateTime(cursors);
	});
}

void PaletteCouleur::draw(cv::Mat& frame)
{
	if (this->visible)
		std::for_each(this->ensembleCouleur.begin(), this->ensembleCouleur.end(), [&frame](WidgetManager & w) {
		w.draw(frame);
	});
}

mat_data_t PaletteCouleur::getCouleur() const
{
	return matAt(*this->couleur, 0, 0);
}

uint32_t PaletteCouleur::x() const
{
	return this->_x;
}

PaletteCouleur& PaletteCouleur::x(uint32_t x)
{
	this->_x = x;
	return *this;
}

uint32_t PaletteCouleur::y() const
{
	return this->_y;
}

PaletteCouleur& PaletteCouleur::y(uint32_t y)
{
	this->_y = y;
	return *this;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////

PaintModule::PaintModule() : visible(false), canSaveScreen(false), pidSauvegarde(::getpid()), numeroSauvegarde(0), tailleBordure(2)
{

}

PaintModule::~PaintModule()
{
    this->spr_palette.release();
    this->toile.release();
	this->bandeau.release();
}

void PaintModule::init(int width, int height, const std::string& fileName)
{
	this->width = width;
	this->height = height;


    this->spr_palette = cv::Mat(Sprites::tailleIcone, CV_8UC4);
	this->palette.setCouleur(&this->spr_palette);

	this->peintureActif = false;
	this->visible = true;

	this->readConfig(fileName);
	this->initWidgets();
}

void PaintModule::initWidgets()
{
	// Initialisation des widgets
	this->activePeinture.init("", [this]() {
		this->peinture(!this->peintureActif);
	}, NULL, this->activePeinture.x(), this->activePeinture.y(), this->_activation_module);
	// On force la désactivation de la peinture
	this->peinture(false);
	this->activePeinture.addMembre(PlayerMember::RIGHT_HAND).addMembre(PlayerMember::LEFT_HAND);
	this->widgets.addWidget(&this->activePeinture);

	this->ouvrePalette.init("Couleurs", [this]() {
		this->ouvrePalette.changeFirstActivation(false);
		this->palette.visible = !this->palette.visible;
		mtl::log::info("Affichage de la palette : ", this->palette.visible);
	}, &this->spr_palette, this->ouvrePalette.x(), this->ouvrePalette.y(), this->_activation_module);
	this->ouvrePalette.addMembre(PlayerMember::RIGHT_HAND).addMembre(PlayerMember::LEFT_HAND);
	this->widgets.addWidget(&this->ouvrePalette);

	this->reset.init("Reset", [this]() {
		this->resetToile();
	}, &Sprites::spr_peinture_reset, this->reset.x(), this->reset.y(), this->_activation_module);
	this->reset.addMembre(PlayerMember::RIGHT_HAND).addMembre(PlayerMember::LEFT_HAND);
	this->widgets.addWidget(&this->reset);

	this->sauvegarde.init("Save", [this]() {
		this->saveToile();
	} , &Sprites::spr_peinture_save, this->sauvegarde.x(), this->sauvegarde.y(), this->_activation_module);
	this->sauvegarde.addMembre(PlayerMember::RIGHT_HAND).addMembre(PlayerMember::LEFT_HAND);
	this->widgets.addWidget(&this->sauvegarde);
    
    this->activeDress.init("Robe", [this](void){
        this->dress(!this->dressActive);
    }, nullptr, this->activeDress.x(), this->activeDress.y(), this->_activation_module);
    this->dress(false);
    this->activeDress.addMembre(PlayerMember::LEFT_HAND).addMembre(PlayerMember::RIGHT_HAND);
    this->widgets.addWidget(&this->activeDress);
    
    this->switchHand.init("hands", [this](void){
        std::swap(this->membre, this->membreConf);
        this->switchHandValue(!this->isRight);
    }, nullptr, this->switchHand.x(), this->switchHand.y(), this->_activation_module);
    // en fonction des paramètres
    this->switchHandValue(this->membre == PlayerMember::RIGHT_HAND);
    this->switchHand.addMembre(PlayerMember::LEFT_HAND).addMembre(PlayerMember::RIGHT_HAND);
    this->widgets.addWidget(&this->switchHand);
    
    this->printScreen.init("print", [this](void){
        this->canSaveScreen = true;
        this->printScreen.changeFirstActivation(false);
    }, &Sprites::spr_print, this->printScreen.x(), this->printScreen.y(), this->_activation_module);
    this->printScreen.addMembre(PlayerMember::LEFT_HAND).addMembre(PlayerMember::RIGHT_HAND);
    this->widgets.addWidget(&this->printScreen);
}

void PaintModule::switchHandValue(bool value)
{
    this->isRight = value;
    this->switchHand.changeFirstActivation(false);
    this->switchHand.setSprite(this->isRight ? &Sprites::spr_switch_off : &Sprites::spr_switch_on);
}

void PaintModule::membreQuiPeint(PlayerMember p)
{
	this->membre = p;
}

void PaintModule::peinture(bool val)
{
	this->peintureActif = val;

	this->activePeinture.changeFirstActivation(false);
	this->activePeinture.getText() = this->peintureActif ? "Désactiver" : "Activer";
	this->activePeinture.setSprite(this->peintureActif ? &Sprites::spr_peinture_off : &Sprites::spr_peinture_on);
}

void PaintModule::dress(bool value)
{
    this->dressActive = value;
    this->activeDress.changeFirstActivation(false);
    
    this->activeDress.setSprite((this->dressActive) ? &Sprites::spr_clothe_on : &Sprites::spr_clothe_off);
}

void PaintModule::saveToile()
{
    if(!this->peintureActif)
        return;
    
	std::ostringstream fileName;
	fileName << "o_mon_beau_dessin_" << this->pidSauvegarde << "_" << (this->numeroSauvegarde++) << ".png";
	cv::Mat file;
	cv::cvtColor(this->toile, file, CV_RGBA2RGB);
	file.convertTo(file, CV_8UC3);
	cv::imwrite(fileName.str(), file);
	mtl::log::info("Image sauvegardée sous :", fileName.str());
	this->resetToile();
	this->sauvegarde.changeFirstActivation(false);
}

void PaintModule::resetToile(bool force)
{
    if(!force && !this->peintureActif)
        return;
    
	this->reset.changeFirstActivation(false);
	fillMat(this->toile, mat_data_t(255,255,255,170));
//	this->peinture(false);
    ::fillBordure(this->toile, matRedColor(), this->tailleBordure, 6);
}

bool PaintModule::canDrawDress(void)
{
    return this->dressActive;
}

bool PaintModule::canDrawBBox(void)
{
    return this->peintureActif;
}

void PaintModule::readConfig(const std::string& fileName)
{
    XmlLoader loader(fileName);
    mtl::log::info("Chargement du module de Peinture ", fileName);

    this->_activation_module = loader.element("tempsActivation").text<int>();

    loader.node("profilUtilisateurice");
    int habilite = loader.element("habilite").text<int>();
    if(habilite == 0)
    {
    	this->membre     = PlayerMember::RIGHT_HAND;
        this->membreConf = PlayerMember::LEFT_HAND;
    }
    else
    {
    	this->membre     = PlayerMember::LEFT_HAND;
        this->membreConf = PlayerMember::RIGHT_HAND;
    }
    loader.prev();

    this->setEmplacement(static_cast<Emplacement>(loader.element("emplacement").text<int>()));
    this->palette.readConfig(loader.element("Palette").text<std::string>());
}

void PaintModule::rendVisible(bool val)
{
	this->visible = val;
}

void PaintModule::saveScreen(cv::Mat& frame)
{
    std::ostringstream fileName;
    fileName << "o_le_beau_screen_" << this->pidSauvegarde << "_" << (this->numeroSauvegarde++) << ".png";
    cv::Mat file;
    cv::cvtColor(frame, file, CV_RGBA2RGB);
    file.convertTo(file, CV_8UC3);
    cv::imwrite(fileName.str(), file);
    mtl::log::info("Image sauvegardée sous :", fileName.str());
    this->sauvegarde.changeFirstActivation(false);
}

void PaintModule::setEmplacement(Emplacement e)
{
	this->emplacement = e;

	bool bas = true, droite = true, faitLigne = true;

	switch (e)
	{
	case PLACEMENT_HAUT_GAUCHE:
		bas       = false;
		droite    = false;
		faitLigne = true;
		break;
	case PLACEMENT_HAUT_DROIT:
		bas       = false;
		droite    = true;
		faitLigne = true;
		break;
	case PLACEMENT_BAS_GAUCHE:
		bas       = true;
		droite    = false;
		faitLigne = true;
		break;
	case PLACEMENT_BAS_DROIT:
		bas       = true;
		droite    = true;
		faitLigne = true;
		break;
	case PLACEMENT_DROITE:
		bas       = false;
		droite    = true;
		faitLigne = false;
		break;
	case PLACEMENT_GAUCHE:
		bas       = false;
		droite    = false;
		faitLigne = false;
		break;
	default:
		// On rappelle la fonction avec la valeur HAUT_GAUCHE par défaut. On s'assure de mettre quelque chose de correct
		// De plus, l'appel est certain de ne pas boucler, comme la valeur est prise dans un case
		this->setEmplacement(PLACEMENT_HAUT_GAUCHE);
		// On quitte, comme en arrivant ici on est déjà passé une fois dans la fonction 'valide'
		return;
	}
	// Pour ajouter un widget, il suffit d'appeler la fonction placeNouveauWidget
	// avec les memes paramètres, et le widget concerné
	placeNouveauWidget(this->activePeinture, bas, droite, faitLigne);
	placeNouveauWidget(this->ouvrePalette,   bas, droite, faitLigne);
	placeNouveauWidget(this->reset, 		 bas, droite, faitLigne);
	placeNouveauWidget(this->sauvegarde,     bas, droite, faitLigne);
	placeNouveauWidget(this->activeDress,    bas, droite, faitLigne);
    placeNouveauWidget(this->switchHand,     bas, droite, faitLigne);
    placeNouveauWidget(this->printScreen,    bas, droite, faitLigne);

	// Calcul du bandeau
	int epaisseurBandeau = (faitLigne ? Sprites::tailleIcone.height : Sprites::tailleIcone.width) + 35;

	this->toile = cv::Mat(height - Sprites::tailleIcone.height - 35, width, CV_8UC4);

	if(faitLigne)
	{
		this->bandeau  = cv::Mat(epaisseurBandeau, this->width, CV_8UC4);
		this->toile    = cv::Mat(this->height - epaisseurBandeau, this->width, CV_8UC4);
		this->toileX   = 0;
		this->toileY   = bas ? 0 : epaisseurBandeau;
		this->bandeauX = 0;
		this->bandeauY = bas ? this->height - epaisseurBandeau : 0;
	}
	else
	{
		this->bandeau  = cv::Mat(this->height, epaisseurBandeau, CV_8UC4);
		this->toile    = cv::Mat(this->height, this->width - epaisseurBandeau, CV_8UC4);
		this->toileY   = 0;
		this->toileX   = droite ? 0 : epaisseurBandeau;
		this->bandeauY = 0;
		this->bandeauX = droite ? this->width - epaisseurBandeau : 0;
	}

	fillMat(this->bandeau, mat_data_t(0, 0, 0, 170));
	this->resetToile(true);

	this->palette.setEmplacement(this->toileX + 20, this->toileY + 20);
}

void PaintModule::placeNouveauWidget(Widget& nouv, bool bas, bool droite, bool faitLigne)
{
	// Calcul des coordonnées du premier Widget
	static int x    = (this->width  - Sprites::tailleIcone.width)  * droite + ((1 - (2 * droite)) * 20);
	static int y    = (this->height - Sprites::tailleIcone.height) * bas    + ((1 - (2 * bas))    * 20);
	// Calcul des décalages
	static int decX = Sprites::tailleIcone.width  + 8;
	static int decY = Sprites::tailleIcone.height + 8;

	// Affectation des valeurs précédemment calculées
	nouv.x() = x;
	nouv.y() = y;

	// Calcul des prochaines coordonnées
	x += faitLigne    * decX * (1 - (2 * droite));
	y += (!faitLigne) * decY;
}

void PaintModule::updateWidgets(void)
{
	this->widgets.updateWidgets();
	if (this->palette.visible)
		this->palette.updateWidgets();
}

void PaintModule::updateTime(const CursorSet& cursors)
{
	this->widgets.updateTime(cursors);
	if (this->palette.visible)
		this->palette.updateTime(cursors);
	else
	{
		if (!this->peintureActif)
			return;
        if (!cursors.isInBoundingBox(this->membreConf))
        {
            cursors.setIsIn(false);
            return;
        }
        cursors.setIsIn(true);

		const ColoredCursor& c = cursors.getCursor(this->membre);

		if (!(c.y() >= static_cast<uint32_t>(this->toileY) && c.y() <= static_cast<uint32_t>(this->toileY + this->toile.rows)))
			return;

		this->pinceau = this->palette.getCouleur();
		this->pinceau.x(c.x() - this->toileX).y(c.y() - this->toileY);
		this->pinceau.draw(this->toile);
	}
}

void PaintModule::draw(cv::Mat& frame)
{
	if (this->visible)
	{
		blit(frame, this->bandeau, this->bandeauX, this->bandeauY);
		this->widgets.draw(frame);
		if(this->peintureActif)
			blit(frame, this->toile, this->toileX, this->toileY);
		this->palette.draw(frame);
        if(this->canSaveScreen)
        {
            this->canSaveScreen = false;
            this->saveScreen(frame);
        }
	}
}
