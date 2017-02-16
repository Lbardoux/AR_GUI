/**
 * @file Matrix.hpp
 * @brief Une matrice simple pour gérer les transformations.
 * @author Laurent BARDOUX p1108365
 */
#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

#include <cstdint>
#include <array>
#include <iostream>
#include "vec.hpp"


/**
 * @class Matrix
 * @brief Une matrice carrée de taille 4
 */
class Matrix final
{
	public:
		//! @brief Initialise une matrice de 16 éléments (dont les valeurs sont précisées par défaut).
		Matrix(const float& a = 0.0f, const float& b = 0.0f, const float& c = 0.0f, const float& d = 0.0f,
			   const float& e = 0.0f, const float& f = 0.0f, const float& g = 0.0f, const float& h = 0.0f,
			   const float& i = 0.0f, const float& j = 0.0f, const float& k = 0.0f, const float& l = 0.0f,
			   const float& m = 0.0f, const float& n = 0.0f, const float& o = 0.0f, const float& p = 0.0f) noexcept;
		//! @brief Détruit cette matrice.
		~Matrix(void) noexcept;
		/**
		 * @brief Copie @b other dans @b *this.
		 * @param[in] other La matrice à copier.
		 */
		Matrix(const Matrix& other) noexcept;
		/**
		 * @brief Déplace @b other dans @b *this.
		 * @param[in,out] other La matrice a déplacer.
		 */
		Matrix(Matrix&& other) noexcept;
		/**
		 * @brief Affecte @b other à @b *this.
		 * @param[in] other La matrice à affecter.
		 * @return *this.
		 */
		Matrix& operator=(const Matrix& other) noexcept;
		/**
		 * @brief Déplace par affectation @b other vers @b *this
		 * @param[in,out] other La matrice à déplacer.
		 * @return *this.
		 */
		Matrix& operator=(Matrix&& other) noexcept;
		/**
		 * @brief Multiplie plus facilement @b this par @b other.
		 * @param[in] other La matrice par laquelle multiplier.
		 * @return *this.
		 */
		Matrix& operator*=(const Matrix& other) noexcept;
		/**
		 * @brief Applique le scalaire @b v sur *this
		 * @param[in] v Le scalaire par lequel multiplier.
		 * @return *this.
		 */
		Matrix& operator*=(float v) noexcept;
		/**
		 * @brief Applique le scalaire @b v sur *this
		 * @param[in] v Le scalaire par lequel diviser.
		 * @return *this.
		 */
		Matrix& operator/=(float v) noexcept;
		/**
		 * @brief Faudra que tu fasses la doc Laurent.
		 */
		Matrix& inverse();
		/**
		 * @brief Renvoi une référence modifiable sur l'élément positionné sur la ligne @b y et la colonne @b x.
		 * @param[in] x Le numéro de colonne, entre 0 et 3 inclus.
		 * @param[in] y Le numéro de ligne  , entre 0 et 3 inclus.
		 * @return Une référence modifiable sur cet élément.
		 */
		float& at(int x, int y) noexcept;
		/**
		 * @brief Renvoi une référence sur l'élément positionné sur la ligne @b y et la colonne @b x.
		 * @param[in] x Le numéro de colonne, entre 0 et 3 inclus.
		 * @param[in] y Le numéro de ligne  , entre 0 et 3 inclus.
		 * @return Une référence  sur cet élément.
		 */
		const float& at(int x, int y) const noexcept;

		const float* getBuffer() const noexcept;
		
		friend std::ostream& operator<<(std::ostream& out, const Matrix& m);
		friend Matrix operator/(const Matrix& m, float v) noexcept;
		friend Matrix operator*(float v, const Matrix& m) noexcept;
		friend Matrix operator*(const Matrix& m, float v) noexcept;
		friend Matrix operator*(const Matrix& m1, const Matrix& m2) noexcept;
		friend Vector operator*(const Matrix& m, const Vector& v) noexcept;
		
	private:
		std::array<float, 16> buffer; //!< Le conteneur de la matrice.
		
};

/**
 * @brief Multiplie @b m1 par @b m2.
 * @param[in] m1 L'operande de gauche pour la multiplication.
 * @param[in] m2 L'operande de droite pour la multiplication.
 * @return La matrice résultante du calcul.
 */
Matrix operator*(const Matrix& m1, const Matrix& m2) noexcept;

/**
 * @brief Multiplie @b m par @b v.
 * @param[in] m L'operande de gauche pour la multiplication.
 * @param[in] v L'operande de droite pour la multiplication.
 * @return La matrice résultante du calcul.
 */
Vector operator*(const Matrix& m, const Vector& v) noexcept;

/**
 * @brief Multiplication de @b m par un scalaire @b v.
 * @param[in] m La matrice à multiplier.
 * @param[in] v Le scalaire par lequel multiplier.
 * @return Une nouvelle matrice qui embarque le résultat.
 */
Matrix operator*(const Matrix& m, float v) noexcept;

/**
 * @brief Multiplication de @b m par un scalaire @b v en inversant les values.
 * @param[in] m La matrice à multiplier.
 * @param[in] v Le scalaire par lequel multiplier.
 * @return Une nouvelle matrice qui embarque le résultat.
 */
Matrix operator*(float v, const Matrix& m) noexcept;

/**
 * @brief Divise @b m par un scalaire @b v.
 * @param[in] m La matrice à diviser.
 * @param[in] v Le scalaire par lequel diviser.
 * @return Une nouvelle matrice qui contient le résultat.
 */
Matrix operator/(const Matrix& m, float v) noexcept;

/**
 * @brief Affiche @m sur @b out.
 * @param[in,out] out Le flux sur lequel afficher.
 * @param[in]     m   La matrice a afficher.
 * @return out
 */
std::ostream& operator<<(std::ostream& out, const Matrix& m);

/**
 * @brief Crée une matrice de rotation selon l'axe X.
 * @param[in] angle L'angle voulu.
 * @return La matrice résultat.
 */
Matrix rotationXMatrix(float angle);

/**
 * @brief Crée une matrice de rotation selon l'axe Y.
 * @param[in] angle L'angle voulu.
 * @return La matrice résultat.
 */
Matrix rotationYMatrix(float angle);

/**
 * @brief Crée une matrice de rotation selon l'axe Z.
 * @param[in] angle L'angle voulu.
 * @return La matrice résultat.
 */
Matrix rotationZMatrix(float angle);

/**
 * @brief Crée une matrice de translation.
 * @param[in] x Le déplacement en X.
 * @param[in] y Le déplacement en Y.
 * @param[in] z Le déplacement en Z.
 * @return La matrice résultat.
 */
Matrix translationMatrix(float x, float y, float z);

/**
 * @brief Crée une matrice de translation.
 * @param[in] vector Le vecteur de translation que l'on veut.
 * @return La matrice résultat.
 */
Matrix translationMatrix(const Vector& v);

/**
 * @brief Crée une matrice de mise à l'échelle.
 * @param[in] x La taille d'augmentation voulue pour l'axe x.
 * @param[in] y La taille d'augmentation voulue pour l'axe y.
 * @param[in] z La taille d'augmentation voulue pour l'axe z.
 * @return La matrice résultat.
 */
Matrix scaleMatrix(float x, float y, float z);

/**
 * @brief Faudra que tu fasses la doc Laurent.
 */
Matrix lookAt(const Point& from, const Point& to, const Vector& up);
/**
 * @brief Faudra que tu fasses la doc Laurent.
 */
Matrix perspective(const float fov_radian, const float aspect, const float znear, const float zfar);

/**
 * @brief Construit une matrice identité.
 * @return cette fameuse matrice.
 */
Matrix identityMatrix(void);


typedef Matrix Transform;

#endif
