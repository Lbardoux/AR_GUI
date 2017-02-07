/**
 * @file CLmanager.hpp
 * @brief Permet de gerer la ligne de commande du programme (Command Line).
 * @author Laurent   BARDOUX   p1108365
 * @version 1.0
 */
#ifndef CLMANAGER_HPP_INCLUDED
#define CLMANAGER_HPP_INCLUDED


/**
 * @brief Verifie que la ligne de commande possede bien le bon nombre d'argument.
 * 
 * En cas d'erreur dans la ligne de commande, elle affiche le contenu de son fichier de configuration
 * sur la sortie d'erreur.
 * @param[in] argc Le nombre d'element dans @b argv.
 * @param[in] argv Les arguments venant de la ligne de commande.
 * @throw std::runtime_error     Si la ligne de commande est invalide.
 * @throw std::ios_base::failure Si le fichier qui contient les informations n'a pas ete trouve.
 */
void checkCommandLine(int argc, char** argv);


#endif
