# AUTEURS
# Laurent   BARDOUX p1108365
# Mehdi     GHESH   p
# Charles   SULTAN  p
# Alexandre BELAIZI p

# Utilisation
# Etant donné les configurations des machines de TP8, qui diffèrent bien trop des notres, il va falloir ruser.
# Ainsi, il suffira de spécifier location=td8 si on est en TD8, et de ne rien mettre sinon.
# Exemple :
# On est chez Guillou :          make location=td8
# On est sur des ordis normaux : make


.PHONY: doc tar help decompress

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
OPENNI2   := $(LIBS)/OpenNI2
NITE2     := $(LIBS)/NiTE2

LDLIBS   := -L$(INCLUDES)/ -L$(XMLLOADER)/ -L$(NITE2)/Redist/  -L$(OPENNI2)/Redist/
LDFLAGS  := -I$(INCLUDES)/ -L$(XMLLOADER)/ -I$(NITE2)/Include/ -I$(OPENNI2)/Include/
location := regular
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
               -lpthread -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor \
               -rpath="/Shared/TP_VTDVR/LIRIS-VISION/ModulesAndBricks/Apicamera/build:/Shared/TP_VTDVR/LIRIS-VISION/ModulesAndBricks/Calibration/build:"
	LDFLAGS += -I"/Shared/TP_VTDVR/LIRIS-VISION" -I"/Locals/OpenCV-2.4.10/include" -I"/Locals/OpenCV-2.4.10/include/opencv" \
               -I"/Shared/TP_VTDVR/LIRIS-VISION/ModulesAndBricks"
else
	LDLIBS  += -L/usr/local/lib -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres \
	           -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio \
	           -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core
	LDFLAGS += -I/usr/local/include/opencv -I/usr/local/include
endif


LDLF := $(LDLIBS) $(LDFLAGS)


EXE_NAME    := AdvancedGUI
DOXYFILE    := $(DOC)/Doxyfile
OBJECTS     := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(wildcard $(SRC)/*.cpp))
XMLOBJECTS  := $(patsubst $(XMLLOADER)/%.cpp, $(OBJ)/%.o, $(wildcard $(XMLLOADER)/*.cpp))

all : $(EXE_NAME)

$(EXE_NAME) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDLF) $^ -o $@

# Ajouter ici quand on veut un fichier supplémentaire à compiler.
$(OBJ)/main.o           : $(INCLUDES)/CLmanager.hpp
$(OBJ)/CLmanager.o      : $(INCLUDES)/CLmanager.hpp
$(OBJ)/CursorListener.o : $(INCLUDES)/CursorListener.hpp $(INCLUDES)/clamp.hpp



$(OBJ)/%.o : $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) $(LDLF) -c $< -o $@

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

doc:
	doxygen $(DOXYFILE)
	rm -f $(README)
	ln -s $(DOC)/html/index.html $(README)

clean:
	rm -rf $(OBJECTS) $(EXE_NAME)

mrproper: clean
	rm -rf $(DOC)/html $(OBJ)/*.o $(README)
	rm -rf $(LIBS)/NiTE2 $(LIBS)/XMLLoader $(LIBS)/OpenNI2

tar:
	tar -czf $(EXE_NAME).tar.gz $(SRC)/* $(INCLUDES)/* $(DOXYFILE) Makefile assets/* libs/*.tar.gz

decompress:
	cd $(LIBS) && tar -xzf NiTE2.tar.gz && tar -xzf XMLLoader.tar.gz && tar -xzf OpenNI2.tar.gz

help:
	clear
	@echo "Makefile ---> options disponibles :"
	@echo "\ttar      : Fabrique une archive nommee $(EXE_NAME).tar.gz contenant les sources et le doxyfile."
	@echo "\tdoc      : Genere la documentation avec Doxygen."
	@echo "\tclean    : Nettoie les objets de compilation seulement."
	@echo "\tmrproper : Applique clean, supprime la doc si elle existe, et supprime les objets des libs internes."
	@echo "\tinstall  : Cree les repertoires qu'il faut pour l'application."
	@echo "\n\t[all]    : Compile les sources, et on a deux possibilites ici :"
	@echo "\t\t - On precise LOCATION=TD8 si on est dans la caverne numerique d'Alibaba."
	@echo "\t\t - On ne met rien si on est chez nous."
