/**
 * @file Cv_core.hpp
 * @brief Propose des fonctionnalités relatives à OpenCV
 * On retrouve dans ce fichier l'ensemble des include/typedef/fonctions
 * qui se rapportent à OpenCV. Il est à include dans chacun des fichiers
 * utilisant OpenCV. <b>Toutes les parties utilisant les couleurs d'OpenCV
 * fonctionnent en BGR</b> !!
 * @author Mehdi GHESH p1209574
 * @version 1.0
 */
#ifndef _CV_CORE_HPP__
#define _CV_CORE_HPP__

// ############################################################################
// Liste des includes

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// ############################################################################
// Définition des maccros

#ifndef UNUSED
	#ifdef __GNUC__
		#define UNUSED(x) x __attribute__((__unused__))
	#else
		#define UNUSED(x) x
	#endif
#endif

// ############################################################################
// Définition des typedefs

typedef cv::Vec4b mat_data_t; //!< Type stockée dans nos matrices, et évite de taper cv::Vec4i à chaque fois

// ############################################################################
// Déclaration des fonctions usuelles

/**
 * @date       08-Feb-2017
 * @brief      Accesseur de matrice en lecture seule
 * @param[in]  mat   La matrice
 * @param[in]  x     Ligne dans la matrice
 * @param[in]  y     Colonne dans la matrice
 * @return     Valeur stockée dans la matrice
 */
const mat_data_t matAt(const cv::Mat& mat, int x, int y);
/**
 * @date       08-Feb-2017
 * @brief      Accesseur de matrice en lecture/écriture
 * @param[in]  mat   La matrice
 * @param[in]  x     Ligne dans la matrice
 * @param[in]  y     Colonne dans la matrice
 * @return     Référence sur la valeur stockée dans la matrice
 */
mat_data_t& matAt(cv::Mat& mat, int x, int y);

/**
 * @date       08-Feb-2017
 * @brief      Fonction qui donne une couleur rouge
 * @return     Renvoie la couleur rouge selon le format stockée dans nos matrices
 */
mat_data_t matRedColor(void);
/**
 * @date       08-Feb-2017
 * @brief      Fonction qui donne une couleur bleue
 * @return     Renvoie la couleur bleue selon le format stockée dans nos matrices
 */
mat_data_t matBlueColor(void);
/**
 * @date       08-Feb-2017
 * @brief      Fonction qui donne une couleur verte
 * @return     Renvoie la couleur verte selon le format stockée dans nos matrices
 */
mat_data_t matGreenColor(void);

#endif
