Sources=main.cpp drawbdparams.cpp toyflvpdf.cpp toycppdf.cpp toydbldalitzpdf.cpp
Executable=fsbl
CFlags=-c -Wall -g -Iinc -std=c++11 -I. `root-config --cflags`
LDFlags= -I. -Wl,--no-as-needed `root-config --glibs` -lm -lstdc++ -lRooFit -lRooFitCore -ldalitz
ObjectDir=obj/
SourceDir=src/
BinDir=bin/

CC=g++
RM=rm

#!!!!!DO NOT EDIT ANYTHING UNDER THIS LINE!!!!!
Objects=$(Sources:.cpp=.o)
CSources=$(addprefix $(SourceDir),$(Sources))
CObjects=$(addprefix $(ObjectDir),$(Objects))
CExecutable=$(addprefix $(BinDir),$(Executable))

all: $(CSources) $(CExecutable)

$(CExecutable): $(CObjects)
	$(CC) $(LDFlags) $(CObjects) -o $@

$(ObjectDir)%.o: $(SourceDir)%.cpp
	$(CC) $(CFlags) $< -o $@

clean:
	$(RM) $(CObjects)
