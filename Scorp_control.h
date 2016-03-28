//======================================================
// Name		: Scorp_control.h
// Author	: Mark Strickland
// Version	: 0.1
// Copyright	: GPL
// Description	: Header file for scorpion control program
//======================================================

// includes
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
using namespace std;
#include "SerialPort.h"
#include "Dynamixel.h"
#include "Utils.h"

// global variables
SerialPort serialPort;
Dynamixel dynamixel;
int spdax12 = 200;	// speed of AX12 motors
int mdelay = 10;	// delay in ms between positions
int wdelay = 500;	// delay in ms for walking case 14

// function prototypes
void readPos(const char * filename);
void lFootDown(int AX12id);
void lFootUp(int AX12id);
void lFootOut(int AX12id);
void rFootDown(int AX12id);
void rFootUp(int AX12id);
void rFootOut(int AX12id);
void lHipFwd(int AX12id);
void lHipMid(int AX12id);
void lHipBack(int AX12id);
void rHipFwd(int AX12id);
void rHipMid(int AX12id);
void rHipBack(int AX12id);
void lPinchOpen(void);
void lPinchClose(void);
void rPinchOpen(void);
void rPinchClose(void);
void tailUp(void);
void tailTipOsc(void);
void allFeetUp(void);
void allFeetDown(void);
void spreadStance(void);
void lHipF45(int AX12id);
void lHipB45(int AX12id);
void rHipF45(int AX12id);
void rHipB45(int AX12id);

