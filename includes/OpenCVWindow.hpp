/**
 * @file OpenCVWindow.hpp
 * @brief Définit une fenetre via OpenCV.
 * @author Laurent BARDOUX p1108365
 * @version 1.0
 */
#ifndef OPENCVWINDOW_HPP_INCLUDED
#define OPENCVWINDOW_HPP_INCLUDED

#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <string>
#include "WindowsManager.hpp"

class OpenCVWindow : public Window
{
    public:
        //! @brief Constructeur par défaut qui ne fait rien globalement.
        OpenCVWindow(void);
        //! @brief Destructeur qui ne fait rien, valide pour le polymorphisme.
        ~OpenCVWindow(void);
        
        virtual void open(uint32_t width, uint32_t height) override;
        virtual bool isGood(void) const override;
        virtual void close(void) override;
        virtual void update(void) override;
        virtual void setName(const std::string& name) override;
        
        std::string name; //!< Le nom de la fenetre.
    
};



#endif
