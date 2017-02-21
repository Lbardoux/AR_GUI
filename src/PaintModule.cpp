#include "PaintModule.hpp"
#include <sys/types.h>
#include <sstream>
// #include <unistd.h>

PaletteCouleur::PaletteCouleur()
{
	init(NULL, 2, 2);
}

void PaletteCouleur::init(Sprite* couleur, uint32_t rows, uint32_t cols, uint32_t x, uint32_t y)
{
	this->_x = x;
	this->_y = y;
	this->visible = false;

	this->_rows = rows;
	this->_cols = cols;

	this->couleur = couleur;
}

PaletteCouleur& PaletteCouleur::addCouleur(const mat_data_t& color)
{
	if (this->ensembleSprite.size() >= static_cast<unsigned int>(this->_rows * this->_cols))
	{
		mtl::log::warning("Impossible d'ajouter de Couleur à la Palette, il y a deja", this->_rows, 'x', this->_cols, "couleurs");
		return *this;
	}

	Sprite* spr = new Sprite(COULEUR_HAUTEUR, COULEUR_LONGUEUR, CV_8UC4);
	fillMat(*spr, color);

	int ind = static_cast<int>(this->ensembleSprite.size());
	int col = (ind % this->_cols);
	int row = (ind / this->_cols);

	ActionButton* bouton = new ActionButton;

	bouton->init("", [this, ind]() {
		this->ensembleSprite[ind].first->changeFirstActivation(false);
		fillMat(*this->couleur, matAt(*this->ensembleSprite[ind].second, 0, 0));
	},
	spr,
	this->_x + (COULEUR_LONGUEUR * col),
	this->_y + (COULEUR_HAUTEUR  * row),
	ACTIVATION_PEINTURE);
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

void PaintModule::init(int width, int height, PlayerMember membre)
{
	this->width = width;
	this->height = height;

	this->palette.init(&this->spr_palette, 2, 2, 150, 150);
	this->palette.addCouleur(matRedColor()).addCouleur(matBlackColor())
	.addCouleur(matBlueColor()).addCouleur(matGreenColor());

	this->activePeinture.init("", [this]() {
		this->peinture(!this->peintureActif);
	}, NULL, 0, 0, ACTIVATION_PEINTURE);
	// On force la désactivation de la peinture
	peinture(false);
	this->activePeinture.addMembre(PlayerMember::RIGHT_HAND).addMembre(PlayerMember::LEFT_HAND);
	this->widgets.addWidget(&this->activePeinture);

	this->spr_palette = cv::Mat(Sprites::tailleIcone, CV_8UC4);
	fillMat(this->spr_palette, matBlackColor());
	this->ouvrePalette.init("Couleurs", [this]() {
		this->ouvrePalette.changeFirstActivation(false);
		this->palette.visible = !this->palette.visible;
	}, &this->spr_palette, 100 + Sprites::spr_peinture_on.cols + 50, 100, ACTIVATION_PEINTURE);
	this->ouvrePalette.addMembre(PlayerMember::RIGHT_HAND).addMembre(PlayerMember::LEFT_HAND);
	this->widgets.addWidget(&this->ouvrePalette);

	this->reset.init("Reset", [this]() {
		this->resetToile();
	}, &Sprites::spr_peinture_reset, 0, 0, ACTIVATION_PEINTURE);
	this->reset.addMembre(PlayerMember::RIGHT_HAND).addMembre(PlayerMember::LEFT_HAND);
	this->widgets.addWidget(&this->reset);

	this->sauvegarde.init("Save", [this]() {
		this->saveToile();
	} , &Sprites::spr_peinture_save, 0, 0, ACTIVATION_PEINTURE);
	this->sauvegarde.addMembre(PlayerMember::RIGHT_HAND).addMembre(PlayerMember::LEFT_HAND);
	this->widgets.addWidget(&this->sauvegarde);

	this->setEmplacement(Emplacement::HAUT_GAUCHE);
	this->membre = membre;

	this->peintureActif = false;
	this->visible = true;

	this->toile = cv::Mat(height - Sprites::spr_peinture_on.rows - 35, width, CV_8UC4);
	fillBordure();
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
		return;
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
	this->activePeinture.y() = y;

	decalage = 8;

	this->ouvrePalette.x() = this->activePeinture.x() + (x * (Sprites::tailleIcone.width + decalage));
	this->ouvrePalette.y() = y;

	this->reset.x() = this->ouvrePalette.x() + (x * (Sprites::tailleIcone.width + decalage));
	this->reset.y() = y;

	this->sauvegarde.x() = this->reset.x() + (x * (Sprites::tailleIcone.width + decalage));
	this->sauvegarde.y() = y;
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
		// mtl::log::warning("Couleur : ", this->palette.getCouleur());
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
