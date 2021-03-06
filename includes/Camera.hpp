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

class Player;

/**
 * @struct Camera
 * @brief Gère la caméra et les 2 canaux associés.
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
        /**
         * @date       14-Feb-2017
         * @brief      Démarre les flux
         * @param[in]  width   Largeur de la sortie du flux voulu
         * @param[in]  height  Hauteur de la sortie du flux voulu
         * @post       Si la hauteur et la largeur pour le flux sont
         *             disponibles, alors ils sont mis en place, sinon les
         *             paramètres par défaut sont laissés
         */    
        void start(int width, int height);
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
        const cv::Mat& colorFrame(void) const;
        /**
         * @date       15-Feb-2017
         * @brief      Récupère la frame enregistrée en lecture/écriture.
         * @return     Une référence sur l'image capturée.
         */
        cv::Mat& colorFrame(void);

        friend class Player;

    private:
        void initCamera(const char *uri);      //!< @brief Initialise le composant caméra.
        void initColorStream(void); //!< @brief Initialise le canal couleur.


        openni::Device        device;     //!< La caméra elle-même.
        openni::VideoStream   color;      //!< Le canal couleur.
        openni::VideoFrameRef colorframe; //!< L'image capturée pour le canal couleur.
        cv::Mat               colorMat;   //!< Ce qu'il faut afficher.

        /**
         * @date       14-Feb-2017
         * @brief      Fonction qui recherche les différents modes vidéos C'est
         *             avec son résultat que l'on sera capable de changer la
         *             taille des vidéos reçues
         * @param[in]  width       Largeur du flux voulu
         * @param[in]  height      Hauteur du flux voulu
         * @param[in]  sensorType  Type du sensor sur lequel on veut les infos
         * @param      videoMode   VideoMode dans lequel on stocke ce qu'on a
         *                         trouvé
         * @param[in]  printMods   Si vrai, les modes possibles sont affichés, faux par défaut
         * @return     True si on a trouvé le mode voulu, False sinon
         */
        bool findVideoModes(int width, int height, openni::SensorType sensorType, openni::VideoMode& videoMode, bool printMods = false);

        /**
         * @date       15-Feb-2017
         * @brief      Récupère le device
         * @return     Le device
         */
        openni::Device& getDevice();

};

void QuitOpenNI(void);

#endif
