/**
 * @file main.cpp
 * @mainpage
 * @section s_id_depot Lien vers le projet
 * <a href="https://github.com/Lbardoux/AR_GUI">Lien vers GitHub</a>
 * @section    s_id_usage Utilisation
 * @subsection ss_id_compile Installer tout ça.
 * Salut camarade développeur ! Alors comme ça tu veux compiler ce truc ?@n
 * Pour cela, rien de plus dur, il suffit, si tu es chez toi, d'avoir les <b>libs suivantes</b> d'installées@n
 * Une procédure va etre détaillée pour chaque morceau, mais ça donne une idée de l'ampleur de la tache :
 *    - @b <a href="http://opencv.org/downloads.html">OpenCV</a>
 *    - @b <a href="http://openni.ru/openni-sdk/">OpenNI</a>
 *    - @b <a href="http://openni.ru/files/nite/">Nite</a>
 *    - @b tinyxml2 et son wrapper XmlLoader.
 *    - @b mtlkit.
 *    - @b logs
 * 
 * 
 * @subsection ss_id_base Le plus facile d'abord !
 * Ici cela va consister à installer la première librairie (la mienne - by MTLCRBN), il suffit juste de faire:
 * @code
 * make install
 * @endcode
 * Cela va créer les répertoires qu'il faut, décompresser XmlLoader, et compiler la lib.
 * 
 * @subsection ss_id_openni_sucks Installer OpenNI2, les VRAIS ennuis.
 * Actuellement le plus gros morceau de l'installation, cela va vous prendre des heures de sueur, sang et larmes.
 * Toujours près ?@n
 * Il va falloir suivre vraiment pas à pas cette procédure, sinon ... il vous en cuira.
 *     - On commence par télécharger OpenNI2 à cette <a href="https://structure.io/openni">adresse</a>, en choississant
 *       le bon format (x86 ou x64).
 *     - Puis on déplace l'archive téléchargée dans le répertoire @b libs/ du projet.
 *     - On le dézippe.
 *     - On se rend dans le répertoire créé
 *       @code
 *       cd OpenNI-Linux-*
 *       @endcode
 *     - On lance le "script d'installation" :
 *       @code
 *       sudo ./install.sh
 *       @endcode
 *     - Pour tester que le bousin s'est bien établie, on procède de la façon suivante :
 *       @code
 *       cd Tools
 *       ./NiViewer
 *       @endcode
 *       Si vous n'avez rien de brancher, ça ne va rien démarrer, mais le programme va se lancer :D.@n
 *       Sinon, si la caméra n'est pas reconnue, essayer l'astuce suivante :
 *       @code
 *       sudo ln -s /lib/x86_64-linux-gnu/libudev.so.X.X.X /lib/x86_64-linux-gnu/libudev.so.0
 *       @endcode
 *       En remplaçant les X par les bons nombres (auto-complétion, toussa toussa).
 *     - Ensuite, le contenu du fichier OpenNIDevEnvironment va permettre de configurer les options -I et -L.
 *       Cette partie étant spécifique, elle sera refaite via le Makefile lors de chaque compilation.
 *     - Et enfin, il suffit d'ajouter dans votre .bashrc :
 *       @code
 *       export LD_LIBRARY_PATH="$LD_LIBRARY_PATH":"chemin_jusqua_repertoire_qui_contient_libOpenNI2.so"
 *       @endcode
 *       Puis ensuite, de taper :
 *       @code
 *       source "$HOME"/.bashrc
 *       @endcode
 * 
 * Si cela fonctionne, un <b>immense milliers de mercis</b> à @b Ashwin de CodeYarns.
 * 
 * @subsection ss_id_OpenCV Installer OpenCV 3.1.0
 * On impose bien entendu la version 3.1.0 comme version commune.@n
 * Ainsi, il suffit de se rendre à cette <a href="http://opencv.org/downloads.html">adresse</a> et de suivre la procédure indiquée, c'est simple en fait.
 *     - Télécharger l'archive 3.1.0 pour linux.
 *     - Chercher sur ce merveilleux site <a href="http://docs.opencv.org/3.0-last-rst/doc/tutorials/introduction/linux_install/linux_install.html">la doc</a> pour installer OpenCV.
 * 
 * 
 * @subsection ss_id_nite2 Installer NiTE2
 * Et on repart sur des magouilles !@n
 * Bon pour commencé, il vous faut l'archive NiTE2.tar.gz (fournie hier, réuploadable au besoin), et la décompresser dans @b libs/.
 * Puis, à partir de là, retourner modifier votre .bashrc en ajoutant la ligne suivante :
 * @code
 * export LD_LIBRARY_PATH="$LD_LIBRARY_PATH":"chemin_jusqua_libNiTE2.so"
 * @endcode
 * Puis faite pour la seconde fois :
 * @code
 * source .bashrc
 * @endcode
 * 
 * @subsection ss_id_compiler Compiler sur nos machines.
 * <b>Ne pas tenter cette étape si chacune des étapes de l'installation n'ont pas été faites !</b>
 * 
 * Remplacer @b nom par votre nom/alias (ils sont dans le Makefile).
 * @code
 * make
 * @endcode
 * 
 * @subsection ss_id_usage Lancer le programme
 * En premier lieu, il nous faut une caméra de profondeur branchée sur un port USB.
 * Puis, il suffit ensuite de taper la commande suivante <b>dans le répertoire où se trouve le binaire</b> :
 * @code
 * ./AdvancedGUI gl|cv
 * @endcode
 * 
 * @subsection ss_id_guignol Utiliser l'application
 * Placer vous face à la caméra à une bonne distance, et bouger !
 * 
 * @subsection ss_id_git_commands Quelques commandes GIT
 * Pour oublier les changements fait sur un ensemble de fichier et faire en sorte de pouvoir <b><code>git pull</code></b>
 * qui pourrait poser problème, faire :
 * @code
 * git checkout -- file1 file2 ...
 * @endcode
 * Si par contre vous voulez conserver vos modifications sur certains fichiers, vous devez faire :
 * @code
 * git stash
 * git pull
 * git stash pop
 * @endcode
 * Normalement cela devrait remettre vos fichiers modifiés en l'état, avec peut être des résolutions de conflits
 * à faire par vos soins.
 * 
 * @author Laurent   BARDOUX   p1108365
 * @author Mehdi     GHESH     p1209574
 * @author Charles   SULTAN    p1207507
 * @version 1.0
 */
#include <cstdlib>
#include <string>

#include "logs.hpp"
#include "CLmanager.hpp"
#include "App.hpp"
#include "GlCore.hpp"
#include "GlContext.hpp"
#include "Pipeline.hpp"
#include "Loop.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Player.hpp"
#include "Clothe.hpp"

/*Transform model = Translation(-3, -2, 10);
Transform view = Lookat(Point(0, 0, 0), Point(0, 0, 1), Vector(0, 1, 0));
Transform projection = Perspective(45, 640.0f / 480.0f, 0.1f, 1000.0f);*/
bool met_ton_code_la_charles(Mesh & mesh, Player & player, Clothe & clothe)
{
    Pipeline::clear(true, true);

    //Epaule 1
    Point p1(3, 5, 0);
    const Transform model1 = scaleMatrix(0.1, 0.1, 0.1) * translationMatrix(p1);
    const Transform view = translationMatrix(0, 0, 0);
    const Transform projection = translationMatrix(0, 0, 0);
    mesh.draw(model1, view, projection);

    //Epaule 2
    Point p2(-3, 0, 0);
    const Transform model2 = scaleMatrix(0.1, 0.1, 0.1) * translationMatrix(p2);
    mesh.draw(model2, view, projection);

    //Vetement
    clothe.draw(p1, p2, view, projection);

    return false;
}

*/


int main(int argc, char** argv)
{
    checkCommandLine(argc, argv);
    mtl::log::info("Ligne de commande valide");
    if (std::string(argv[1]) == "cv")
    {
        mtl::log::info("Lancement avec OpenCV");
        App appli;
        mtl::log::info("Creation de l'application reussie");
        appli.mainLoop();
        mtl::log::info("Terminaison en cours");
        appli.quit();
    }
    else if (std::string(argv[1]) == "test")
    {
        Matrix mat1(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
        Matrix mat2(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
        std::cout << mat1*mat2 << std::endl;
    }
    else
    {
        /*GlContext::initGL(640, 480);
        GlContext::windowCaption("OpenGL window");
        Pipeline::fromXML("assets/PipelineConfig.xml");

        VertexShader vertex("assets/shaders/vertex.cpp");
        FragmentShader fragment("assets/shaders/fragment.cpp");
        ShaderProgram program({vertex, fragment});

        Mesh mesh("assets/objs/cube.obj", program);

        nite::UserTracker * user_tracker = new nite::UserTracker;	//Très mal initialisé, 
    	Player player(*user_tracker);								//juste pour faire plaisir au compilo

        Clothe clothe(player, LEFT_SHOULDER, RIGHT_SHOULDER, mesh);

        program.use();
        renderLoop(30, met_ton_code_la_charles, mesh, player, clothe);
        
        GlContext::endGL();*/
    }
    
    return EXIT_SUCCESS;
}



//
//Main de Charles
//
/*
#include "Player.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    //Initialisation de OpenNI
    openni::Status status = openni::OpenNI::initialize();
    if(status != openni::STATUS_OK)
    {
        printf("Failed to initialize OpenNI\n%s\n", openni::OpenNI::getExtendedError());
        return status;
    }
    std::cout<<"(1/4) OpenNI initialisé"<<std::endl;

    //Ouvre n'importe quelle caméra
    const char* deviceUri = openni::ANY_DEVICE;
    openni::Device device;
    status = device.open(deviceUri);
    if (status != openni::STATUS_OK)
    {
        printf("Failed to open device\n%s\n", openni::OpenNI::getExtendedError());
        return status;
    }
    std::cout<<"(2/4) Caméra initialisée"<<std::endl;

    //Initialisation de nite
    nite::NiTE::initialize();
    std::cout<<"(3/4) NiTE initialisé"<<std::endl;

    //Création du tracker
    nite::UserTracker * user_tracker = new nite::UserTracker;
    if(user_tracker->create(&device) != nite::STATUS_OK)
    {
        printf("Failed to create tracker\n");
        return openni::STATUS_ERROR;
    }
    std::cout<<"(4/4) Tracker initialisé"<<std::endl;

    //Création du squelette
    Player player(*user_tracker);

    //Exemple
    while(true)
    {
        player.update();
        nite::Point3f  position = player.getPositionOf(HEAD);
        std::cout<<position.x<<" "<<position.y<<" "<<position.z<<std::endl;    
    }
}
*/



//
// (Fait par la) Main de Mehdi
//
/*
#include "Camera.hpp"
int main(int argc, char const *argv[])
{
    // Camera cam;

    // cam.init();


    
    App app;

    app.mainLoop();

    app.quit();
    return 0;
}
*/
