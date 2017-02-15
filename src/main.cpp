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
#include "Sprite.hpp"

bool met_ton_code_la_charles(Mesh & fond, Mesh & mesh_test, Player & player, Clothe & clothe, Camera & camera)
{
    Pipeline::clear(true, true);

    //Fond
    //
    Transform model = translationMatrix(0, 0, 9000) * scaleMatrix(15 * 640.0f, 15 * 480.0f, 1);
	Transform view = lookAt(Point(0, 0, 0), Point(0, 0, 1), Vector(0, 1, 0));
	Transform projection = perspective(45, 640.0f / 480.0f, 0.1f, 10000.0f);
    fond.readTextureFromCamera(camera);
    fond.draw(model, view, projection);

   	//Joueur
    //
   	player.update();
    //Epaule 1
    //Point position_1(-100, 300, 1000);// = player.getPointOf(LEFT_SHOULDER);
    Point position_1 = player.getPointOf(RIGHT_SHOULDER);
    if(position_1.x() != 0 || position_1.y() != 0 || position_1.z() != 0)
    {
	    model = translationMatrix(position_1) * scaleMatrix(50, 50, 50);
	    mesh_test.draw(model, view, projection);
	}
	//Epaule 2
    //Point position_2(100, 200, 1000);// = player.getPointOf(RIGHT_SHOULDER);
	Point position_2 = player.getPointOf(LEFT_SHOULDER);
    if(position_2.x() != 0 || position_2.y() != 0 || position_2.z() != 0)
    {
	    model = translationMatrix(position_2) * scaleMatrix(50, 50, 50);
	    mesh_test.draw(model, view, projection);
	}

    //Vetement
    if(	position_1.x() != 0 || position_1.y() != 0 || position_1.z() != 0 || 
    	position_2.x() != 0 || position_2.y() != 0 || position_2.z() != 0)
    {
	    clothe.draw(position_1, position_2, view, projection);
	}

    return false;
}

int main(int argc, char** argv)
{
    checkCommandLine(argc, argv);
    mtl::log::info("Ligne de commande valide");
	mtl::log::info("Chargement des sprites...");
	Sprites::init();
	mtl::log::info("Chargement des sprites terminé");
	
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
		//QApplication app(argc, argv);
        cv::namedWindow("test");
		cv::resizeWindow("test", 640u, 640u);
		cv::Mat img = cv::Mat(640u, 640u, CV_8UC4, cv::Scalar(0));
//		cv::Mat img2 = cv::Mat(40u, 40u, CV_8UC4, cv::Scalar(1));
		blit(img, Sprites::test, 0, 0);
		cv::imshow("test", img);
		cv::waitKey(0);
		cv::destroyWindow("test");
    }
    else
    {
        Camera camera;
	    camera.init();
	    camera.start(640, 480);
    	Player player(camera);

    	GlContext::initGL(640, 480);
		GlContext::windowCaption("OpenGL window");
		Pipeline::fromXML("assets/PipelineConfig.xml");

        VertexShader vertex("assets/shaders/vertex.cpp");
        FragmentShader fragment("assets/shaders/fragment.cpp");
        ShaderProgram program({vertex, fragment});

        Mesh soubrette("assets/objs/soubrette.obj", "assets/objs/texture.bmp", program, Vector(0, -12.2, 0));
        Mesh cube("assets/objs/cube.obj", "assets/objs/texture.bmp", program);
        Mesh fond("assets/objs/squarre.obj", camera, program);

        Clothe clothe(player, LEFT_SHOULDER, RIGHT_SHOULDER, soubrette);

        program.use();
        renderLoop(30, met_ton_code_la_charles, fond, cube, player, clothe, camera);
        
        GlContext::endGL();
    }

    Sprites::empty();
	mtl::log::info("Vidage des sprites");
    return EXIT_SUCCESS;
}

//
// (Fait par la) Main de Mehdi
//

// #include "Camera.hpp"
// int main(int argc, char const *argv[])
// {
//     // Camera cam;

//     // cam.init();


    
//     App app;

//     app.mainLoop();

//     app.quit();
//     return 0;
// }

