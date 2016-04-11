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

// constants
#define PI 3.141519265

// global variables
SerialPort serialPort;
Dynamixel dynamixel;
int spdax12 = 200;	// speed of AX12 motors
int mdelay = 10;	// delay in ms between positions
int wdelay = 50;	// delay in ms for 2 tripod movement
int p0 = 462;			// middle position of motor
int hr = 50;			// half-range of motor
float omeg = 2*PI/5;				// frequency
float phiHIP = 0;		// phase angle for HIPS
float phiFT = PI/2;		// phase angle for Feet 5, 6, 13, 14
float phiFT910 = 3*PI/2; 	// phase angle for Feet 9 and 10
int posHIP312 = 512;	// position of Hips 3 and 12
int posHIP411 = 512;	// position of Hips 4 and 11
int posFT513 = 512; 	// position of Feet 5 and 13
int posFT614 = 512; 	// position of Feet 6 and 14
int posFT9 = 512;		// position of Foot 9
int posFT10 = 512;		// position of Foot 10

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

