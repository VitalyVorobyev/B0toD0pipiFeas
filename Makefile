all: fsbl

fsbl: main.o drawbdparams.o toyflvpdf.o toycppdf.o toydbldalitzpdf.o
	g++ main.o drawbdparams.o toyflvpdf.o toycppdf.o toydbldalitzpdf.o -I. -Wl,--no-as-needed `root-config --glibs` -Wl,-rpath=/home/vitaly/B0toD0pipi/libDalitz -lm -lstdc++ -lRooFit -lRooFitCore -ldalitz -o fsbl

main.o: main.cpp
	g++ -c main.cpp -I. `root-config --cflags`

drawbdparams.o: drawbdparams.cpp
	g++ -c drawbdparams.cpp -I. `root-config --cflags`

toyflvpdf.o: toyflvpdf.cpp
	g++ -c toyflvpdf.cpp -std=c++11 -I. `root-config --cflags`

toycppdf.o: toycppdf.cpp
	g++ -c toycppdf.cpp -std=c++11 -I. `root-config --cflags`

toydbldalitzpdf.o: toydbldalitzpdf.cpp
	g++ -c toydbldalitzpdf.cpp -std=c++11 -I. `root-config --cflags`

clean:
	rm -rf *.o fsbl

