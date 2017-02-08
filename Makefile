# AUTEURS
# Laurent   BARDOUX p1108365
# Mehdi     GHESH   p1209574
# Charles   SULTAN  p
# Alexandre BELAIZI p

# Utilisation
# Etant donné les configurations des machines de TP8, qui diffèrent bien trop des notres, il va falloir ruser.
# Ainsi, il suffira de spécifier location=td8 si on est en TD8, et de ne rien mettre sinon.
# Exemple :
# On est chez Guillou :          make location=td8
# On est sur des ordis normaux : make


.PHONY: doc tar help decompress link_openni

CXX      := g++
WARNINGS := -Wall -Wextra
STD      := -std=c++11
TARGET   := -g
CXXFLAGS := $(TARGET) $(STD) $(WARNINGS)

SRC       := src
OBJ       := obj
DOC       := doc
INCLUDES  := includes
LIBS      := libs
XMLLOADER := $(LIBS)/XMLLoader
OPENNI2   := 
NITE2     := $(LIBS)/NiTE2

LDLIBS   := -L$(OBJ)/ -lOpenNI2 -L$(NITE2)/Redist
LDFLAGS  := -I$(INCLUDES)/ -I$(XMLLOADER)/ -I$(NITE2)/Include
location := td8
README   := ReadMe.html

ifeq ($(location), td8)
	LDLIBS  += -L"/Locals/OpenCV-2.4.10/lib" -L"/Shared/TP_VTDVR/LIRIS-VISION/ModulesAndBricks/Apicamera/build" \
               -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video \
               -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib \
               -lopencv_legacy -lopencv_flann -lcameraUVC -Xlinker \
               -rpath="/Locals/OpenCV-2.4.10/lib:/Shared/TP_VTDVR/LIRIS-VISION/ModulesAndBricks/Apicamera/build:" \
               -L"/Shared/TP_VTDVR/LIRIS-VISION/ModulesAndBricks/Apicamera/build" \
               -L"/Shared/TP_VTDVR/LIRIS-VISION/ModulesAndBricks/Calibration/build" -L"/Locals/OpenCV-2.4.10/lib/" \
               -lopencv_contrib -lapicamera -lcameraFILE -lcameraOPENCV -lcalibration \
               -lpthread -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor\
               -rpath="/Shared/TP_VTDVR/LIRIS-VISION/ModulesAndBricks/Apicamera/build:/Shared/TP_VTDVR/LIRIS-VISION/ModulesAndBricks/Calibration/build:"
	LDFLAGS += -I"/Shared/TP_VTDVR/LIRIS-VISION" -I"/Locals/OpenCV-2.4.10/include" -I"/Locals/OpenCV-2.4.10/include/opencv" \
               -I"/Shared/TP_VTDVR/LIRIS-VISION/ModulesAndBricks"
else ifeq ($(location), laurent)
	LDLIBS  += `pkg-config opencv --libs`
	LDFLAGS += `pkg-config opencv --cflags`
	OPENNI2 += $(LIBS)/OpenNI-Linux-x64-2.2
else ifeq ($(location), mehdi)
	LDLIBS  += 
	LDFLAGS +=
	OPENNI2 +=
else ifeq ($(location), charles)
	LDLIBS  += 
	LDFLAGS +=
	OPENNI2 +=
else ifeq ($(location), alex)
	LDLIBS  += 
	LDFLAGS +=
	OPENNI2 +=
endif

LDLIBS  += -L$(shell grep "Redist" libs/OpenNI-Linux-x64-2.2/OpenNIDevEnvironment | cut -d' ' -f2 | cut -d'=' -f2)
LDFLAGS += -I$(shell grep "Include" libs/OpenNI-Linux-x64-2.2/OpenNIDevEnvironment | cut -d' ' -f2 | cut -d'=' -f2)

EXE_NAME    := AdvancedGUI
DOXYFILE    := $(DOC)/Doxyfile
OBJECTS     := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(wildcard $(SRC)/*.cpp))
XMLOBJECTS  := $(patsubst $(XMLLOADER)/%.cpp, $(OBJ)/%.o, $(wildcard $(XMLLOADER)/*.cpp))

all : $(EXE_NAME)

$(EXE_NAME) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

# Ajouter ici quand on veut un fichier supplémentaire à compiler.
$(OBJ)/main.o           : $(INCLUDES)/CLmanager.hpp
$(OBJ)/CLmanager.o      : $(INCLUDES)/CLmanager.hpp
$(OBJ)/CursorListener.o : $(INCLUDES)/CursorListener.hpp $(INCLUDES)/clamp.hpp


$(OBJ)/%.o : $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< $(LDFLAGS) -o $@


# Concerne l'installation et la gestion des dépendances (Maaaaaveeeeen, où es-tu :( ?) ################
install : _directories decompress
	$(MAKE) libs

_directories: 
	mkdir -p $(OBJ)

libs : $(XMLOBJECTS)

$(OBJ)/XmlBase.o   : $(XMLLOADER)/XmlBase.hpp   $(XMLLOADER)/tinyxml2.h  $(OBJ)/tinyxml2.o
$(OBJ)/XmlLoader.o : $(XMLLOADER)/XmlLoader.hpp $(XMLLOADER)/XmlBase.hpp
$(OBJ)/XmlWriter.o : $(XMLLOADER)/XmlWriter.hpp $(XMLLOADER)/XmlBase.hpp
$(OBJ)/tinyxml2.o  : $(XMLLOADER)/tinyxml2.h
$(OBJ)/%.o : $(XMLLOADER)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(XMLLOADER) -c $< -o $@

decompress:
	cd $(LIBS) && tar -xzf XMLLoader.tar.gz

#########################################################################################################

doc:
	doxygen $(DOXYFILE)
	rm -f $(README)
	ln -s $(DOC)/html/index.html $(README)

clean:
	rm -rf $(OBJECTS) $(EXE_NAME)

mrproper: clean
	rm -rf $(DOC)/html $(OBJ)/*.o $(README)

tar:
	tar -czf $(EXE_NAME).tar.gz $(SRC)/* $(INCLUDES)/* $(DOXYFILE) Makefile assets/* libs/*.tar.gz

help:
	clear
	@echo "Makefile ---> options disponibles :"
	@echo "\ttar      : Fabrique une archive nommee $(EXE_NAME).tar.gz contenant les sources et le doxyfile."
	@echo "\tdoc      : Genere la documentation avec Doxygen."
	@echo "\tclean    : Nettoie les objets de compilation seulement."
	@echo "\tmrproper : Applique clean, supprime la doc si elle existe, et supprime les objets des libs internes."
	@echo "\tinstall  : Cree les repertoires qu'il faut pour l'application."
	@echo "\n\t[all]    : Compile les sources, et on a deux possibilites ici :"
	@echo "\t\t - On precise location=XXX avec le bon argument."
	@echo "\t\t - On ne met rien si on est chez nous."
