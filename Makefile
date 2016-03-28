CC  = c++
GCC = g++

CFLAGS  = -O -c
MYFLAGS = -O2 -Wall

LINUX_LIBS   = 
LIBS         = $(LINUX_LIBS)

SOURCE  = Dynamixel.cpp SerialPort.cpp Utils.cpp Scorp_control.cpp 
OBJECTS = Dynamixel.o SerialPort.o Utils.o Scorp_control.o

DEST = scorp

RUBBISH = *.o *~ core $(DEST)

.SUFFIXES: .cpp .h

all: scorp

.cpp.o:
	$(GCC) -c  $(MYFLAGS) $< -o $@

scorp: $(OBJECTS)
	$(GCC) $(OBJECTS) -o $(DEST) $(LIBS)
clean:
	-rm -f $(RUBBISH)
