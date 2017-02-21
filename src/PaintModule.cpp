#include "PaintModule.hpp"
#include <sys/types.h>
#include <sstream>

PaletteCouleur::PaletteCouleur() : couleur(NULL), visible(false)
{
}

int clampChannel(int value)
{
	if(value < 0)
		return 0;
	else if (value > 255)
		return 255;
	else
		return value;
}

mat_data_t readColor(XmlLoader& loader)
{
    return
    mat_data_t(
        clampChannel(loader.element("rouge").text<int>()),
        clampChannel(loader.element("vert").text<int>()),
        clampChannel(loader.element("bleu").text<int>()),
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

PaintModule::PaintModule() : visible(false), pidSauvegarde(::getpid()), numeroSauvegarde(0), tailleBordure(2)
{

}

PaintModule::~PaintModule()
{

}

void PaintModule::init(int width, int height, const std::string& fileName)
{
	this->width = width;
	this->height = height;

	this->toile = cv::Mat(height - Sprites::spr_peinture_on.rows - 35, width, CV_8UC4);
	fillBordure();

	// this->palette.init(&this->spr_palette, 2, 2, 150, 150);
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
	peinture(false);
	this->activePeinture.addMembre(PlayerMember::RIGHT_HAND).addMembre(PlayerMember::LEFT_HAND);
	this->widgets.addWidget(&this->activePeinture);

	this->spr_palette = cv::Mat(Sprites::tailleIcone, CV_8UC4);
	fillMat(this->spr_palette, matBlackColor());
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

void PaintModule::saveToile()
{
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

void PaintModule::resetToile()
{
	this->reset.changeFirstActivation(false);
	fillMat(this->toile, matEmptyColor());
	this->peinture(false);
    this->fillBordure();
}

void PaintModule::readConfig(const std::string& fileName)
{
	// XmlLoader loader("ModulePeinture.xml");
    XmlLoader loader(fileName);
    mtl::log::info("Chargement du module de Peinture ", fileName);

    this->_activation_module = loader.element("tempsActivation").text<int>();

    loader.node("profilUtilisateurice");
    int habilite = loader.element("habilite").text<int>();
    // habilite == 0 -> Droitier
    if(habilite == 0)
    	this->membre = PlayerMember::RIGHT_HAND;
    else
    	this->membre = PlayerMember::LEFT_HAND;
    loader.prev();

    this->setEmplacement(static_cast<Emplacement>(loader.element("emplacement").text<int>()));
    // this->setEmplacement(Emplacement::HAUT_DROIT);
    this->palette.readConfig(loader.element("Palette").text<std::string>());
}

void PaintModule::rendVisible(bool val)
{
	this->visible = val;
}

void PaintModule::setEmplacement(Emplacement e)
{
	this->emplacement = e;

	const int HAUT   = 20;
	const int BAS    = this->height - Sprites::tailleIcone.height - 20;
	const int GAUCHE = 1;
	const int DROITE = -1;
	int x, y;

	switch (e)
	{
	case HAUT_GAUCHE:
		x = GAUCHE;
		y = HAUT;
		break;
	case HAUT_DROIT:
		x = DROITE;
		y = HAUT;
		break;
	case BAS_GAUCHE:
		x = GAUCHE;
		y = BAS;
		break;
	case BAS_DROIT:
		x = DROITE;
		y = BAS;
		break;
	default:
		x = GAUCHE;
		y = HAUT;
		break;
	}

	this->toileX = 0;

	if (y == HAUT)
		this->toileY = Sprites::tailleIcone.height + 35;
	else
		this->toileY = 0;

	int decalage = 0;
	if (x == DROITE)
		decalage = this->width - Sprites::tailleIcone.width;

	this->activePeinture.x() = (20 * x) + decalage;
	mtl::log::info("this->activePeinture.x() : ", this->activePeinture.x());
	this->activePeinture.y() = y;
	mtl::log::info("this->activePeinture.y() : ", this->activePeinture.y());

	decalage = 8;

	this->ouvrePalette.x() = this->activePeinture.x() + (x * (Sprites::tailleIcone.width + decalage));
	mtl::log::info("this->ouvrePalette.x() : ", this->ouvrePalette.x());
	this->ouvrePalette.y() = y;
	mtl::log::info("this->ouvrePalette.y() : ", this->ouvrePalette.y());

	this->reset.x() = this->ouvrePalette.x() + (x * (Sprites::tailleIcone.width + decalage));
	mtl::log::info("this->reset.x() : ", this->reset.x());
	this->reset.y() = y;
	mtl::log::info("this->reset.y() : ", this->reset.y());

	this->sauvegarde.x() = this->reset.x() + (x * (Sprites::tailleIcone.width + decalage));
	this->sauvegarde.y() = y;

	this->palette.setEmplacement(this->toileX + 2, this->toileY + 2);
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

		const ColoredCursor& c = cursors.getCursor(this->membre);

		if (!(c.y() >= static_cast<uint32_t>(this->toileY) && c.y() <= static_cast<uint32_t>(this->toileY + this->toile.rows)))
			return;

		this->pinceau = this->palette.getCouleur();
		this->pinceau.x(c.x() - this->toileX).y(c.y() - this->toileY);
		this->pinceau.draw(this->toile);
	}
}

void PaintModule::draw(cv::Mat frame)
{
	if (this->visible)
	{
		this->widgets.draw(frame);
		blit(frame, this->toile, this->toileX, this->toileY);
		this->palette.draw(frame);
	}
}

void PaintModule::fillBordure()
{
	for (int i = 0; i < this->tailleBordure; ++i)
	{
		for (int x = 0; x < this->toile.cols; ++x)
		{
			matAt(this->toile, x, i) = matBlackColor();
			matAt(this->toile, x, this->toile.rows - i - 1) = matBlackColor();
		}
		for (int y = 0; y < this->toile.rows; ++y)
		{
			matAt(this->toile, i, y) = matBlackColor();
			matAt(this->toile, this->toile.cols - i - 1, y) = matBlackColor();
		}
	}
}
