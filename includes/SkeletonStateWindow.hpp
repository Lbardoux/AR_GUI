/**
 * @file SkeletonStateWindow.hpp
 * @brief Gère une fenetre qui affichera l'état de l'application.
 * @author Laurent BARDOUX p1108365
 * @version 1.0
 */
#ifndef SKELETONSTATEWINDOW_HPP_INCLUDED
#define SKELETONSTATEWINDOW_HPP_INCLUDED

#include <opencv2/highgui/highgui.hpp>
#include <cstdint>
#include "OpenCVWindow.hpp"



class SkeletonStateWindow final : public OpenCVWindow
{
    public:
        //! @brief Constructeur par défaut de cette fenetre..
        SkeletonStateWindow(void);
        //! @brief Ne détruit rien, sans rire.
        ~SkeletonStateWindow(void);
        /**
         * @brief Permet de modifier l'état de l'application.
         * @param[in] value true pour une application valide, false sinon.
         * @return *this.
         */
        SkeletonStateWindow& setState(bool value) noexcept;
        
        void open(uint32_t width, uint32_t height) override;
        void close(void)                           override;
        void update(void)                          override;
        
        
    private:
        cv::Mat valid; //!< L'image quand l'application est valide.
        cv::Mat error; //!< L'image quand l'application est en erreur.
        bool    state; //!< La validité de l'application.
        
};


#endif
