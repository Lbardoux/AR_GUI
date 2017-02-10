/**
 * @file LaserCamera.hpp
 * @brief Gère une caméra de profondeur (voire plusieurs).
 * @author Laurent   BARDOUX p1108365
 * @author Mehdi     GHESH   p1209574
 * @author Charles   SULTAN  p1207507
 * @author Alexandre BELAIZI p
 */
#ifndef LASERCAMERA_HPP_INCLUDED
#define LASERCAMERA_HPP_INCLUDED

#include <OpenNI.h>
#include <opencv2/opencv.hpp>
#include <cstdint>
#include "logs.hpp"


/**
 * @struct Camera
 * @brief Gère la caméra et les 2 canals associés.
 */
struct Camera final
{
    public:

        Camera(void) = default;
        /**
         * @brief Initialise la caméra et les canals pour l'affichage.
         * En cas d'erreur, coupe OpenNI.
         * @param[in] uri Le nom sur la machine d'une caméra.
         * @throw std::runtime_error Si un problème survient lors de l'initialisation.
         */
        void init(const char* uri = openni::ANY_DEVICE);
        //! @brief Détruit la caméra et tout le tintouin.
        ~Camera(void);
        /**
         * @brief Capture une frame pour les 2 canaux.
         * Cela va remplir depthMat en recalant correctement l'image.
         */
        void readFrame(void);
		/**
		 * @brief Récupère la frame enregistrée en lecture seule.
		 * @return Une référence sur l'image capturée.
		 */
		const cv::Mat& depthFrame(void) const;
		/**
		 * @brief Récupère la frame enregistrée en lecture/écriture.
		 * @return Une référence sur l'image capturée.
		 */
		cv::Mat& depthFrame(void);
		/**
		 * @brief Récupère la frame enregistrée en lecture seule.
		 * @return Une référence sur l'image capturée.
		 */
		const cv::Mat& colorFrame(void) const;
		/**
		 * @brief Récupère la frame enregistrée en lecture/écriture.
		 * @return Une référence sur l'image capturée.
		 */
		cv::Mat& colorFrame(void);

    private:
        void initCamera(const char *uri);      //!< @brief Initialise le composant caméra.
        void initDepthStream(void); //!< @brief Initialise le canal de profondeur.
        void initColorStream(void); //!< @brief Initialise le canal couleur.

        openni::Device        device;     //!< La caméra elle-même.
        openni::VideoStream   depth;      //!< Le canal de profondeur.
        openni::VideoStream   color;      //!< Le canal couleur.
        openni::VideoFrameRef depthframe; //!< L'image capturée pour le canal profondeur.
        openni::VideoFrameRef colorframe; //!< L'image capturée pour le canal couleur.
        cv::Mat               depthMat;   //!< Ce qu'il faut afficher.
        cv::Mat               colorMat;   //!< Ce qu'il faut afficher.

};


#endif
