/**
 * @file Matrix.hpp
 * @brief Une matrice simple pour gérer les transformations.
 * @author Laurent BARDOUX p1108365
 */
#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

#include <cstdint>
#include <array>


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
 * @brief Crée une matrice de rotation selon l'axe X.
 * @param[in] angle L'angle voulu.
 * @return La matrice résultat.
 */
Matrix rotationX(float angle);

/**
 * @brief Crée une matrice de rotation selon l'axe Y.
 * @param[in] angle L'angle voulu.
 * @return La matrice résultat.
 */
Matrix rotationY(float angle);

/**
 * @brief Crée une matrice de rotation selon l'axe Z.
 * @param[in] angle L'angle voulu.
 * @return La matrice résultat.
 */
Matrix rotationZ(float angle);

/**
 * @brief Crée une matrice de translation.
 * @param[in] x Le déplacement en X.
 * @param[in] y Le déplacement en Y.
 * @param[in] z Le déplacement en Z.
 * @return La matrice résultat.
 */
Matrix translation(float x, float y, float z);

/**
 * @brief Crée une matrice de mise à l'échelle.
 * @param[in] s La taille d'augmentation voulue.
 * @return La matrice résultat.
 */
Matrix scale(float s);

#endif

