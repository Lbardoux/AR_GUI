# AUTEURS
# Laurent   BARDOUX p1108365
# Mehdi     GHESH   p1209574
# Charles   SULTAN  p1207507
# Alexandre BELAIZI p


.PHONY: doc tar help decompress push

VERBOSE  := 0
CXX_V    := g++
CC_0      = @echo "Compiling $<..."; $(CXX_V)
CC_1     := $(CXX_V)

CXX       = $(CC_$(VERBOSE))
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
OPENNI2   := $(LIBS)/OpenNI-Linux-x64-2.2
NITE2     := $(LIBS)/NiTE2
MTLKIT    := $(LIBS)/mtlkit
LOGS      := $(LIBS)/logs

LDLIBS   := -L$(OBJ)/ -lOpenNI2 -L$(NITE2)/Redist -lpthread -lNiTE2 -lGL -lGLEW -lSDL2 -lSDL2_image -lm
LDFLAGS  := -I$(INCLUDES)/ -I$(XMLLOADER)/ -I$(NITE2)/Include -I$(MTLKIT)/ -I$(LOGS)
location := $(shell whoami)
README   := ReadMe.html

COMMIT := "Commit par defaut fait par un fainéant"

ifeq ($(location), student)
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
else ifeq ($(location), bardoux)
	LDLIBS  += `pkg-config opencv --libs`
	LDFLAGS += `pkg-config opencv --cflags`
else ifeq ($(location), mehdi)
	LDLIBS  += -L/home/mehdi/master/m2/embarquee/opencv-2.4.13/build/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video \
               -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann
	LDFLAGS += -I/home/mehdi/master/m2/embarquee/opencv-2.4.13/include -I/home/mehdi/master/m2/embarquee/opencv-2.4.13/include/opencv2 \
               -I/home/mehdi/master/m2/embarquee/opencv-2.4.13/build $(addprefix -I, $(shell find /home/mehdi/master/m2/embarquee/opencv-2.4.13/modules/ -name "include"))
else ifeq ($(location), alex)
	LDLIBS  += 
	LDFLAGS += 
else
	# Cas de Charles, par défaut.
	LDLIBS  += `pkg-config opencv --libs`
	LDFLAGS += `pkg-config opencv --cflags`
endif

LDLIBS  += -L$(shell grep "Redist" $(LIBS)/OpenNI-Linux-x64-2.2/OpenNIDevEnvironment | cut -d' ' -f2 | cut -d'=' -f2)
LDFLAGS += -I$(shell grep "Include" $(LIBS)/OpenNI-Linux-x64-2.2/OpenNIDevEnvironment | cut -d' ' -f2 | cut -d'=' -f2)

EXE_NAME      := AdvancedGUI
DOXYFILE      := $(DOC)/Doxyfile
OBJECTS       := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(wildcard $(SRC)/*.cpp))
XMLOBJECTS    := $(patsubst $(XMLLOADER)/%.cpp, $(OBJ)/%.o, $(wildcard $(XMLLOADER)/*.cpp))
MTLKITOBJECTS := $(patsubst $(MTLKIT)/%.cpp, $(OBJ)/%.o, $(wildcard $(MTLKIT)/*.cpp))


all : $(EXE_NAME)

$(EXE_NAME) : $(OBJECTS) $(XMLOBJECTS) $(MTLKITOBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

# Ajouter ici quand on veut un fichier supplémentaire à compiler.
$(OBJ)/main.o                : 
$(OBJ)/Mesh.o                : $(INCLUDES)/Mesh.hpp $(MTLKIT)/vec.hpp $(INCLUDES)/GlCore.hpp $(INCLUDES)/Matrix.hpp $(MTLKIT)/ShaderProgram.hpp
$(OBJ)/OpenCVWindow.o        : $(INCLUDES)/OpenCVWindow.hpp $(INCLUDES)/WindowsManager.hpp
$(OBJ)/Player.o              : $(INCLUDES)/Player.hpp $(MTLKIT)/ShaderProgram.hpp
$(OBJ)/SetCursor.o           : $(INCLUDES)/SetCursor.hpp $(INCLUDES)/Player.hpp $(INCLUDES)/Cv_core.hpp
$(OBJ)/SkeletonStateWindow.o : $(INCLUDES)/SkeletonStateWindow.hpp $(INCLUDES)/OpenCVWindow.hpp $(INCLUDES)/Cv_core.hpp $(INCLUDES)/logs.hpp
$(OBJ)/WindowsManager.o      : $(INCLUDES)/WindowsManager.hpp
$(OBJ)/Widget.o              : $(INCLUDES)/Widget.hpp $(INCLUDES)/Cv_core.hpp $(INCLUDES)/Cursor.hpp
$(OBJ)/Cv_core.o             : $(INCLUDES)/Cv_core.hpp
$(OBJ)/Clothe.o              : $(INCLUDES)/Clothe.hpp $(INCLUDES)/Player.hpp $(INCLUDES)/Mesh.hpp $(INCLUDES)/Matrix.hpp
$(OBJ)/Cursor.o              : $(INCLUDES)/Cursor.hpp $(INCLUDES)/clamp.hpp $(INCLUDES)/Cv_core.hpp
$(OBJ)/Matrix.o              : $(INCLUDES)/Matrix.hpp $(MTLKIT)/vec.hpp
$(OBJ)/App.o                 : $(INCLUDES)/App.hpp $(INCLUDES)/WindowsManager.hpp $(INCLUDES)/KeyboardMapping.hpp $(INCLUDES)/Cv_core.hpp \
                               $(INCLUDES)/SkeletonStateWindow.hpp
$(OBJ)/Camera.o              : $(INCLUDES)/logs.hpp $(INCLUDES)/Camera.hpp
$(OBJ)/CLmanager.o           : $(INCLUDES)/CLmanager.hpp

$(OBJ)/%.o : $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< $(LDFLAGS) -o $@


install : _directories decompress
	$(MAKE) libs

_directories: 
	mkdir -p $(OBJ)

libs : $(XMLOBJECTS) $(MTLKITOBJECTS)

#dépendances pour XmlLoader/Writer
$(OBJ)/XmlBase.o   : $(XMLLOADER)/XmlBase.hpp   $(XMLLOADER)/tinyxml2.h  $(OBJ)/tinyxml2.o
$(OBJ)/XmlLoader.o : $(XMLLOADER)/XmlLoader.hpp $(XMLLOADER)/XmlBase.hpp
$(OBJ)/XmlWriter.o : $(XMLLOADER)/XmlWriter.hpp $(XMLLOADER)/XmlBase.hpp
$(OBJ)/tinyxml2.o  : $(XMLLOADER)/tinyxml2.h
$(OBJ)/%.o : $(XMLLOADER)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -I$(XMLLOADER) -o $@

# Dépendances pour MTLKIT
$(OBJ)/Events.o          : $(MTLKIT)/keymap.hpp        $(MTLKIT)/Events.hpp
$(OBJ)/GlContext.o       : $(MTLKIT)/GlCore.hpp        $(MTLKIT)/GlContext.hpp       $(MTLKIT)/Events.hpp
$(OBJ)/Pipeline.o        : $(MTLKIT)/GlCore.hpp        $(MTLKIT)/Pipeline_traits.hpp $(MTLKIT)/vec.hpp    $(XMLLOADER)/XmlLoader.hpp $(MTLKIT)/Pipeline.hpp
$(OBJ)/Pipeline_traits.o : $(MTLKIT)/GlCore.hpp        $(MTLKIT)/Pipeline_traits.hpp
$(OBJ)/ShaderProgram.o   : $(MTLKIT)/ShaderProgram.hpp $(MTLKIT)/GlCore.hpp
$(OBJ)/%.o : $(MTLKIT)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -I$(MTLKIT) -I$(XMLLOADER) -lGL -lGLEW -lSDL2 -lSDL2_image -o $@

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
	@echo "\tpush     : Permet de add/commit/push en meme temps. Attention, il est impossible de préciser des noms"
	@echo "\n\t[all]    : Compile les sources, et on a deux possibilites ici :"
	@echo "\t\t - On precise location=XXX avec le bon argument."
	@echo "\t\t - On ne met rien si on est chez nous."

push:
	git add $(SRC)/* $(INCLUDES)/* assets/* Makefile README.md
	git commit -m "$(COMMIT)"
	git push
