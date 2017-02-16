/**
 * @file textPutter.hpp
 * @brief Utilise OpenCV pour afficher du texte d'une manière plus facile sur une cv::Mat.
 * @author Laurent BARDOUX p1108365
 * @version 1.0
 */
#ifndef TEXTPUTTER_HPP_INCLUDED
#define TEXTPUTTER_HPP_INCLUDED

#include <cstdint>
#include <string>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


/**
 * @class TextPutter
 * @brief Cache les appels à cv::putText.
 * dans quelque chose de plus simple à utiliser.
 */
class TextPutter final
{
    public:
        //! @brief Crée un simple TextPutter pour enchainer les appels et écrire.
        TextPutter(void) noexcept;
        /**
         * @brief Configure la couleur du texte qui sera affiché.
         * @param[in] r la variante rouge voulue.
         * @param[in] g la variante verte voulue.
         * @param[in] b la variante bleue voulue.
         * @return *this
         */
        TextPutter& rgb(uint8_t r, uint8_t g, uint8_t b) noexcept;
        /**
         * @brief Change la taille de la police du texte.
         * @param[in] s La taille voulue.
         * @return *this
         */
        TextPutter& fontSize(float s) noexcept;
        /**
         * @brief Change la position du texte (aligné à gauche).
         * @param[in] x La colonne à laquelle commencer.
         * @param[in] y La ligne   à laquelle commencer.
         * @return *this
         */
        TextPutter& pos(int x, int y) noexcept;
        /**
         * @brief Change la police avec une valeur énumérée.
         * @param[in] enumValue Une valeur énumérée concernant les polices disponibles.
         * 
         * Les valeurs possibles sont (préfixées par cv::HersheyFonts::)
         *    - FONT_HERSHEY_SIMPLEX
         *    - FONT_HERSHEY_PLAIN
         *    - FONT_HERSHEY_DUPLEX
         *    - FONT_HERSHEY_COMPLEX
         *    - FONT_HERSHEY_TRIPLEX
         *    - FONT_HERSHEY_COMPLEX_SMALL
         *    - FONT_HERSHEY_SCRIPT_SIMPLEX
         *    - FONT_HERSHEY_SCRIPT_COMPLEX
         *    - FONT_ITALIC
         * 
         * @return *this
         */
        TextPutter& font(cv::HersheyFonts enumValue) noexcept;
        /**
         * @brief Ecrit @b text sur @b dst avec les paramètres actuels.
         * @param[in,out] dst  La frame sur laquelle dessiner.
         * @param[in]     text Le texte à afficher.
         * @return *this
         */
        TextPutter& write(cv::Mat& dst, const std::string& text);
        
        
    private:
        uint8_t red;   //!< La variante rouge de la couleur du texte.
        uint8_t green; //!< La variante verte de la couleur du texte.
        uint8_t blue;  //!< La variante bleue de la couleur du texte.
        int     x;     //!< La position x à laquelle on commence à écrire le texte.
        int     y;     //!< La position y à laquelle on commence à écrire le texte.
        int     face;  //!< La police employe (5 par défaut).
        float   size;  //!< La taille de la police.
};


#endif

