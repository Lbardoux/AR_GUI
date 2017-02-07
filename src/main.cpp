/**
 * @file main.cpp
 * @mainpage
 * @section    s_id_usage Utilisation
 * @subsection ss_id_compile [DEV] : Compiler chez nous
 * Salut camarade développeur ! Alors comme ça tu veux compiler ce truc ?@n
 * Pour cela, rien de plus dur, il suffit, si tu es chez toi, d'avoir les <b>libs suivantes</b> d'installées@n
 * La version reste encore à définir :
 *    - @b <a href="http://opencv.org/downloads.html">OpenCV</a> 
 *    - @b <a href="http://openni.ru/openni-sdk/">OpenNI</a>
 *    - @b <a href="http://openni.ru/files/nite/">Nite</a>
 * 
 * Une fois que ce travail épuisant est accompli, il suffit alors de taper :
 * @code
 * make
 * @endcode
 * 
 * Il est possible d'écraser certaines variables du @b Makefile, par exemple si on veut compiler sans les warnings :
 * @code
 * make WARNINGS=
 * @endcode
 * 
 * 
 * @subsection ss_id_compile2 [DEV-TD8] : Compiler en TD8
 * Eh oui, il y a une section à part entière pour cela, compiler chez Mr.Guillou va justement consister à
 * écraser une variable du @b Makefile, il va falloir spécifier que l'on se trouve en TD8, et qu'il faudra donc charger
 * les dépendances sans utiliser des trucs pratiques comme @b pkg-config our autre :
 * @code
 * make location=td8
 * @endcode
 * 
 * @subsection ss_id_usage Lancer le programme
 * En premier lieu, il nous faut une caméra de profondeur branchée sur un port USB.
 * Puis, il suffit ensuite de taper la commande suivante <b>dans le répertoire où se trouve le binaire</b> :
 * @code
 * ./advancedGUI
 * @endcode
 * 
 * @subsection ss_id_guignol Utiliser l'application
 * Placer vous face à la caméra à une bonne distance, et bouger !
 * 
 * @author Laurent   BARDOUX   p1108365
 * @author Mehdi     GHESH     p
 * @author Charles   SULTAN    p
 * @author Alexandre BELAIZI   p
 * @version 1.0
 */
#include <cstdlib>
#include "CLmanager.hpp"
#include "OpenNI.h"
#include "NiTE.h"

int main(int argc, char** argv)
{
    checkCommandLine(argc, argv);
    return EXIT_SUCCESS;
}
