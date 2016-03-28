//============================================================================
// Name        : Scorp_control.cpp
// Author      : Mark Strickland
// Version     : 0.1
// Copyright   : GPL
// Description : Controls the scorpion robot from Robotis using SDK
//============================================================================

#include "Scorp_control.h"

int main() {
	cout << "AX Control starts" << endl; // prints AX Control

	int error=0;
	int idAX12=18;
	int tossCode = 0;
	int pos;
	int choice;
	int scanerr = 0;
	int quitOption = 0;
	int i;
	FILE *ft;
	// FILE *fr;
	// char *line = NULL;
	// size_t len = 0;
	// ssize_t read;
	// int spos;
	// int num_line = 0;
	// char *ch;
	
	// SerialPort serialPort;
	// Dynamixel dynamixel;

	// double goalpos;
	// double ipos = 550;
	// double pi = 22.0/7.0;
	// int mdelay = 400;   // delay in milliseconds between positions
	// int spdax12 = 150;  // default speed of AX12 motor
	// int foot_range = 50;  // range of positions values for foot
	// int hip_range = 100;  // range of positions values for hip
	// int pinch_range = 60;  // range of positions for pinchers

	// open the serial port connection, send tossCode until a valid
	//  position value is returned
	if (serialPort.connect((char *)"/dev/ttyUSB0")!=0) {

	   // do-while for tossCode
	   do {
	      // send tossCode
	      tossCode = dynamixel.sendTossModeCommand(&serialPort);
	      // print out the tossCode rec'vd
	      printf("\n tossCode %d", tossCode);
	      // get the position of the AX12 of interest
	      pos = dynamixel.getPosition(&serialPort, idAX12);
	      // sleep for a while
	      Utils::sleepMS(500);
	   } while (tossCode == -1 || !(pos > 250 && pos < 1023));
	   // end of do-while for tossCode

	   // print main menu
	   do {
	      printf("*** Main Menu ***\n");
	      printf("1. Read position of each AX12 and write to file\n");
	      printf("2. Read from file and write positions to each AX12\n");
	      printf("3. 2 legged walking - pull 4 behind\n");
	      printf("4. 2 legged walking - push 4 in front\n");
	      printf("5. 2 legged - pull breast stroke\n");
	      printf("6. 2 legged - push breast stroke\n");
	      printf("7. 2 legged - rotate CW\n");
	      printf("8. 2 legged - rotate CCW\n");
	      printf("9. 4 legged walking - mid legs up\n");
	      printf("10. 4 legged - rotate CW\n");
	      printf("11. 4 legged - rotate CCW\n");
	      printf("12. 6 legged walking - drag side\n");
	      printf("13. 6 legged walking - rowing\n");
	      printf("14. 6 legged walking back - two tripods\n");
	      printf("15. 6 legged walking forward - two tripods\n");
	      printf("20. Pinchers open and close\n");
	      printf("30. Tail up and threatening\n");
	      printf("60. Set speed\n");
	      printf("61. Set mdelay\n");
	      printf("62. Set wdelay\n");
	      printf("99. Quit\n");
	      printf("Enter your choice: ");
	      scanerr = scanf("%d", &choice);

	      // if scan did not get anything, continue
	      if (scanerr <=0) {
		continue;
	      }

	      // set the speed of the AX12s
	      for (i = 1; i <= 18; i++) {
		dynamixel.setSpeed(&serialPort, i, spdax12);
	      }

	      // use switch to run correct menu option
	      switch(choice)
	      {
		 case 1:   // read AX12 positions and write to file
		    // debug mesg
		    printf("In case 1\n");
		    // open file for writing positions
		    ft = fopen("positions.txt", "w");

		    // use while loop to continue until told to stop
		   printf("Enter to read positions; s to stop\n");
		   while (getchar() != 's') {
		    // use for-loop to read position of each AX12
		    //  and write that position to the file
		    for (i = 1; i <= 18; i++) {
			pos = dynamixel.getPosition(&serialPort, i);
			fprintf(ft, "%d ", pos);
			// debug - write positions to stdout
			printf("AX12 ID: <%d>  Position: <%d>\n", i, pos);
		    }
		    fprintf(ft, "\n");
		    printf("Enter to read positions; s to stop\n");
		   }

		    // close the file
		    fclose(ft);
		    break;

		 case 2:   // read from file and write AX12 positions
		    // debug mesg
		    printf("In case 2\n");

		    // read the initial positions from file
		    readPos("initial_position.txt");
		    
		    break;

		 case 3:  // 2 legged walking - pull 4 behind
		    
		    // debug mesg
		    printf("In case 3\n");

		    // read the initial positions from file
		    readPos("initial_position.txt");

		    // use AX12ids 3(Lhip), 5(Lfoot), 4(Rhip), 6(Rfoot)
		    // set all feet up
		    allFeetUp();

		    // start repeating motion 
		    for (i = 0; i < 5; i++) {
		      lHipFwd(3);  
		      lFootDown(5);  
		      lHipMid(3);  
		      lFootUp(5); 

		      rHipFwd(4);
		      rFootDown(6);
		      rHipMid(4);
		      rFootUp(6);
		    }

		    break;

		case 4:   // 2 legged walking - push 4 in front

		    // debug mesg
		    printf("In case 4\n");

		    // read the initial positions from file
		    readPos("initial_position.txt");

		    // set all feet up
		    allFeetUp();

		    // start repeating motion 
		    for (i = 0; i < 5; i++) {
		      lHipMid(11);  
		      lFootDown(13);  
		      lHipBack(11);  
		      lFootUp(13); 

		      rHipMid(12);
		      rFootDown(14);
		      rHipBack(12);
		      rFootUp(14);
		    }

		    break;

		case 5:   // 2 legged - pull breast stroke

		    // debug mesg
		    printf("In case 5\n");

		    // read the initial positions from file
		    readPos("initial_position.txt");

		    // set all feet up
		    allFeetUp();

		    // start repeating motion 
		    for (i = 0; i < 5; i++) {
		      lHipFwd(3);  
		      rHipFwd(4);
		      lFootDown(5);  
		      rFootDown(6);
		      lHipMid(3);
		      rHipMid(4);
		      lFootUp(5);
		      rFootUp(6);
		    }

		    break;

		case 6:   // 2 legged - push breast stroke

		    // debug mesg
		    printf("In case 6\n");

		    // read the initial positions from file
		    readPos("initial_position.txt");

		    // set all feet up
		    allFeetUp();

		    // start repeating motion 
		    for (i = 0; i < 5; i++) {
		      lHipMid(11);  
		      rHipMid(12);
		      lFootDown(13);  
		      rFootDown(14);
		      lHipBack(11);
		      rHipBack(12);
		      lFootUp(13);
		      rFootUp(14);
		    }

		    break;

		case 7:   // 2 legged - rotate CW

		    // debug mesg
		    printf("In case 7\n");

		    // read the initial positions from file
		    readPos("initial_position.txt");

		    // set all feet up
		    allFeetUp();

		    // start repeating motion 
		    for (i = 0; i < 5; i++) {
		      lFootDown(9);
		      rFootDown(10);

		      lHipFwd(3);
		      rHipBack(12);

		      lFootUp(9);
		      rFootUp(10);

		      lFootDown(5);
		      rFootDown(14);
		      lHipMid(3);
		      rHipMid(12);
		      lFootUp(5);
		      rFootUp(14);

		    }

		    break;

		case 8:   // 2 legged - rotate CCW

		    // debug mesg
		    printf("In case 8\n");

		    // read the initial positions from file
		    readPos("initial_position.txt");

		    // set all feet up
		    allFeetUp();

		    // start repeating motion 
		    for (i = 0; i < 5; i++) {
		      lFootDown(9);
		      rFootDown(10);

		      lHipBack(11);
		      rHipFwd(4);

		      lFootUp(9);
		      rFootUp(10);

		      lFootDown(13);
		      rFootDown(6);
		      lHipMid(11);
		      rHipMid(4);
		      lFootUp(13);
		      rFootUp(6);

		    }

		    break;

		case 9:   // 4 legged walking - mid legs up

		    // debug mesg
		    printf("In case 9\n");

		    // read the initial positions from file
		    readPos("initial_position.txt");

		    // set all feet up
		    allFeetUp();

		    // start repeating motion 
		    for (i = 0; i < 5; i++) {

		      rHipMid(12);
		      rFootDown(14);  
		      rHipBack(12);  
		      rFootUp(14); 

		      lHipFwd(3);
		      lFootDown(5);
		      lHipMid(3);
		      lFootUp(5);

		      lHipMid(11);
		      lFootDown(13);
		      lHipBack(11);
		      lFootUp(13);

		      rHipFwd(4);
		      rFootDown(6);
		      rHipMid(4);
		      rFootUp(6);
		    }

		    break;

		case 10:   // 4 legged - rotate CW

		    // debug mesg
		    printf("In case 10\n");

		    // read the initial positions from file
		    readPos("initial_position.txt");

		    // set all feet up
		    allFeetUp();

		    // start repeating motion 
		    for (i = 0; i < 5; i++) {
		      lFootDown(9);
		      rFootDown(10);

		      lFootOut(13);
		      lFootOut(5);
		      rFootOut(14);
		      rFootOut(6);

		      lHipFwd(3);
		      rHipMid(4);
		      rHipBack(12);
		      lHipMid(11);

		      lFootDown(13);
		      lFootDown(5);
		      rFootDown(14);
		      rFootDown(6);

		      lFootOut(9);
		      rFootOut(10);

		      lHipMid(3);
		      rHipFwd(4);
		      rHipMid(12);
		      lHipBack(11);

		    }

		    break;

		case 11:   // 4 legged - rotate CCW

		    // debug mesg
		    printf("In case 11\n");

		    // read the initial positions from file
		    readPos("initial_position.txt");

		    // set all feet up
		    allFeetUp();

		    // start repeating motion 
		    for (i = 0; i < 5; i++) {
		      lFootDown(9);
		      rFootDown(10);

		      lFootOut(13);
		      lFootOut(5);
		      rFootOut(14);
		      rFootOut(6);

		      lHipBack(11);
		      lHipMid(3);
		      rHipFwd(4);
		      rHipMid(12);

		      lFootDown(13);
		      lFootDown(5);
		      rFootDown(14);
		      rFootDown(6);

		      lFootOut(9);
		      rFootOut(10);

		      lHipMid(11);
		      lHipFwd(3);
		      rHipMid(4);
		      rHipBack(12);

		    }

		    break;

		case 12:   // 6 legged walking - drag side

		    // debug mesg
		    printf("In case 12\n");

		    // read the initial positions from file
		    readPos("initial_position.txt");

		    // set all feet up
		    allFeetUp();

		  // dragging motion - repeat a few times
		  for (i=0; i < 8; i++) {
			// left side
			lHipFwd(3);
			lHipFwd(7);
			lHipFwd(11);

			rFootDown(10);

			lFootDown(13);
			lHipBack(11);
			lFootUp(13);

			lFootDown(9);
			lHipBack(7);
			lFootUp(9);

			lFootDown(5);
			lHipBack(3);
			lFootUp(5);

			rFootUp(10);

			// right side
			rHipFwd(4);
			rHipFwd(8);
			rHipFwd(12);

			lFootDown(9);

			rFootDown(14);
			rHipBack(12);
			rFootUp(14);

			rFootDown(10);
			rHipBack(8);
			rFootUp(10);

			rFootDown(6);
			rHipBack(4);
			rFootUp(6);

			lFootUp(9);
		  }

		    break;

		case 13:  // 6 legged walking - rowing
		    
		    // debug mesg
		    printf("In case 13\n");

		    // read the initial positions from file
		    readPos("initial_position.txt");

		    // set all feet up
		    allFeetUp();

		  // rowing motion - repeat a few times
		  for (i=0; i < 8; i++) {
		    // set middle feet down
		    // lFootDown(9);
		    // rFootDown(10);

		    // move hips fwd
		    lHipFwd(3);
		    rHipFwd(4);
		    lHipFwd(7);
		    rHipFwd(8);
		    lHipFwd(11);
		    rHipFwd(12);

		    // row motion - 3 pairs of legs
		    lFootDown(13);
		    rFootDown(14);
		    lHipBack(11);
		    rHipBack(12);
		    lFootUp(13);
		    rFootUp(14);

		    lFootDown(9);
		    rFootDown(10);
		    lHipBack(7);
		    rHipBack(8);
		    lFootUp(9);
		    rFootUp(10);

		    lFootDown(5);
		    rFootDown(6);
		    lHipBack(3);
		    rHipBack(4);
		    lFootUp(5);
		    rFootUp(6);

		  } // end of for loop

		    break;

		case 14:   // 6 legged walking back - two tripods

		    // debug mesg
		    printf("In case 14\n");

		    // read the initial positions from file
		    readPos("initial_position.txt");
		    Utils::sleepMS(wdelay);

		    // set all feet up
		    // allFeetUp();

		    // take spread stance
		    // spreadStance();

		    // set all feet down 
		    // allFeetDown();

		    // setup - move 2 hips into position
		    lFootUp(5);
		    rFootUp(14);
		    Utils::sleepMS(wdelay);
		    lHipFwd(3);
		    rHipBack(12);
		    Utils::sleepMS(wdelay);
		    lFootDown(5);
		    rFootDown(14);
		    Utils::sleepMS(wdelay);

		  // tripod motion - repeat a few times
		  for (i=0; i < 10; i++) {

		    // 1st tripod up/2d tripod down
		    lFootUp(5);
		    rFootUp(10);
		    lFootUp(13);
		    rFootDown(6);
		    lFootDown(9);
		    rFootDown(14);
		    Utils::sleepMS(wdelay);

		    // all 4 corners move CCW - R down
		    rHipMid(12);
		    rHipFwd(4);
		    lHipMid(3);
		    lHipBack(11);
		    Utils::sleepMS(wdelay);

		    // 1st tripod down/2d tripod up
		    lFootDown(5);
		    rFootDown(10);
		    lFootDown(13);
		    rFootUp(6);
		    lFootUp(9);
		    rFootUp(14);
		    Utils::sleepMS(wdelay);

		    // all 4 corners move CW - R up 
		    rHipBack(12);
		    rHipMid(4);
		    lHipFwd(3);
		    lHipMid(11);
		    Utils::sleepMS(wdelay);


		  } // end of for loop

		    break;

		case 15:   // 6 legged walking forward - two tripods

		    // debug mesg
		    printf("In case 15\n");

		    // read the initial positions from file
		    readPos("initial_position.txt");
		    Utils::sleepMS(wdelay);

		    // set all feet up
		    // allFeetUp();

		    // take spread stance
		    // spreadStance();

		    // set all feet down 
		    // allFeetDown();

		    // setup - move 2 hips into position
		    lFootUp(13);
		    rFootUp(6);
		    Utils::sleepMS(wdelay);
		    rHipFwd(4);
		    lHipBack(11);
		    Utils::sleepMS(wdelay);
		    lFootDown(13);
		    rFootDown(6);
		    Utils::sleepMS(wdelay);

		  // tripod motion - repeat a few times
		  for (i=0; i < 10; i++) {

		    // 1st tripod up/2d tripod down
		    lFootUp(5);
		    rFootUp(10);
		    lFootUp(13);
		    rFootDown(6);
		    lFootDown(9);
		    rFootDown(14);
		    Utils::sleepMS(wdelay);

		    // all 4 corners move CW - R up 
		    rHipBack(12);
		    rHipMid(4);
		    lHipFwd(3);
		    lHipMid(11);
		    Utils::sleepMS(wdelay);

		    // 1st tripod down/2d tripod up
		    lFootDown(5);
		    rFootDown(10);
		    lFootDown(13);
		    rFootUp(6);
		    lFootUp(9);
		    rFootUp(14);
		    Utils::sleepMS(wdelay);

		    // all 4 corners move CCW - R down
		    rHipMid(12);
		    rHipFwd(4);
		    lHipMid(3);
		    lHipBack(11);
		    Utils::sleepMS(wdelay);


		  } // end of for loop

		    break;

		case 20:   //  pinchers open and close

		   // debug mesg
		   printf("In case 20\n");

		   // read the initial positions from file
		   readPos("initial_position.txt");

		   // open and close the pinchers
		   for (i = 0; i < 10; i++) {
		    lPinchClose();
		    rPinchClose();
		    Utils::sleepMS(200);
		    lPinchOpen();
		    rPinchOpen();
		    Utils::sleepMS(500);
		   }

		   break;

		case 30:   //  tail up and threatening

		   // debug mesg
		   printf("In case 30\n");

		   // read the initial positions from file
		   readPos("initial_position.txt");

		   // move the tail up
		   tailUp();

		   // oscillate the tip of the tail
		   for (i = 0; i < 10; i++) {
		     tailTipOsc();
		   }
 
		   break;

		 case 60:

	      		printf("Enter your selected speed (0-1024): ");
	      		scanerr = scanf("%d", &spdax12);

	      		// set the speed of the AX12s
	      		for (i = 1; i <= 18; i++) {
				dynamixel.setSpeed(&serialPort, i, spdax12);
	      		}

		   	break;

		 case 61:

	      		printf("Enter your selected mdelay in ms: ");
	      		scanerr = scanf("%d", &mdelay);

		   	break;
		 case 62:

	      		printf("Enter your selected wdelay in ms: ");
	      		scanerr = scanf("%d", &wdelay);

		   	break;
		 case 99:  // Quit
		    printf("\nYou have chosen to quit.  Thank you!\n");
		    quitOption = 1;
		    break;

		 default:  // try again
		    printf("\nI did not understand your choice.\n");
		    printf("Please choose one of the available options.\n");
		    break;
	      } // end of switch(choice)

	   } while (quitOption == 0);   // end of do-while for main menu

	   // disconnect from the serial port
	   serialPort.disconnect();

	}
	else {
		printf ("\nCan't open serial port");
		error=-1;
	} // end of if-else for serial port

	cout << endl << "AX Control ends" << endl; // prints AX Control
	return error;
}

// function to read position(s)
void readPos(const char * filename) {
   
    ssize_t read;
    char * line = NULL;
    size_t len = 0;
    int num_line = 0;
    char * ch;
    int i;
    int spos;
    // debug mesg
    printf("In function readPos()\n");
    num_line = 0;
    FILE *fr = fopen(filename, "r");

    while ((read = getline(&line, &len, fr)) != -1) {
	i = 0;
	ch = strtok(line, " ");
	while (ch != NULL && i <= 17) {
	   i = i + 1;
	   spos = atoi(ch);
	   ch = strtok(NULL, " ");
	   if (spos > -1)
	      dynamixel.setPosition(&serialPort, i, spos);
	}
	if (num_line >= 0) {
	   printf("Read and processed line <%d>\n", num_line);
	   Utils::sleepMS(mdelay);
	   num_line++ ;
	}
    }
    fclose(fr);
} // end of function to read initial positions

// function to set L foot down
void lFootDown(int AX12id) {
	dynamixel.setPosition(&serialPort, AX12id, 512);
	Utils::sleepMS(mdelay);
}
	
// function to set L foot up
void lFootUp(int AX12id) {
	dynamixel.setPosition(&serialPort, AX12id, 462);
	Utils::sleepMS(mdelay);
}

// function to set L foot up and out of the way
void lFootOut(int AX12id) {
	dynamixel.setPosition(&serialPort, AX12id, 400);
	Utils::sleepMS(mdelay);
}

// function to set R foot down
void rFootDown(int AX12id) {
	dynamixel.setPosition(&serialPort, AX12id, 512);
	Utils::sleepMS(mdelay);
}
	
// function to set R foot up
void rFootUp(int AX12id) {
	dynamixel.setPosition(&serialPort, AX12id, 562);
	Utils::sleepMS(mdelay);
}

// function to set R foot up and out of the way
void rFootOut(int AX12id) {
	dynamixel.setPosition(&serialPort, AX12id, 620);
	Utils::sleepMS(mdelay);
}

// function to set L hip forward
void lHipFwd(int AX12id) {
	dynamixel.setPosition(&serialPort, AX12id, 375);
	Utils::sleepMS(mdelay);
}

// function to set L hip middle
void lHipMid(int AX12id) {
	dynamixel.setPosition(&serialPort, AX12id, 512);
	Utils::sleepMS(mdelay);
}

// function to set L hip backward
void lHipBack(int AX12id) {
	dynamixel.setPosition(&serialPort, AX12id, 612);
	Utils::sleepMS(mdelay);
}

// function to set R hip forward
void rHipFwd(int AX12id) {
	dynamixel.setPosition(&serialPort, AX12id, 623);
	Utils::sleepMS(mdelay);
}

// function to set R hip middle
void rHipMid(int AX12id) {
	dynamixel.setPosition(&serialPort, AX12id, 512);
	Utils::sleepMS(mdelay);
}

// function to set R hip backward
void rHipBack(int AX12id) {
	dynamixel.setPosition(&serialPort, AX12id, 412);
	Utils::sleepMS(mdelay);
}

// function to set L pincher open
void lPinchOpen(void) {
	dynamixel.setPosition(&serialPort, 1, 506);
	Utils::sleepMS(mdelay);
}

// function to set L pincher closed
void lPinchClose(void) {
	dynamixel.setPosition(&serialPort, 1, 435);
	Utils::sleepMS(mdelay);
}

// function to set R pincher open
void rPinchOpen(void) {
	dynamixel.setPosition(&serialPort, 2, 521);
	Utils::sleepMS(mdelay);
}

// function to set R pincher closed
void rPinchClose(void) {
	dynamixel.setPosition(&serialPort, 2, 584);
	Utils::sleepMS(mdelay);
}

// move the tail up
void tailUp(void) {
	dynamixel.setPosition(&serialPort, 16, 691);
	dynamixel.setPosition(&serialPort, 17, 885);
	dynamixel.setPosition(&serialPort, 18, 608);
}

// make the tail tip oscillate
void tailTipOsc(void) {
	dynamixel.setPosition(&serialPort, 18, 608);
	Utils::sleepMS(mdelay);
	dynamixel.setPosition(&serialPort, 18, 588);
	Utils::sleepMS(mdelay);
}

// set all the feet up
void allFeetUp(void) {
    // set all feet up
    lFootUp(5);
    rFootUp(6);
    lFootUp(9);
    rFootUp(10);
    lFootUp(13);
    rFootUp(14);
}

// set all the feet down 
void allFeetDown(void) {
    // set all feet down
    lFootDown(5);
    rFootDown(6);
    lFootDown(9);
    rFootDown(10);
    lFootDown(13);
    rFootDown(14);
}

// spread stance
void spreadStance(void) {

    lHipMid(7);
    lFootDown(9);
    rHipMid(8);
    rFootDown(10);

    lHipFwd(3);
    rHipFwd(4);
    lHipBack(11);
    rHipBack(12);

    lFootUp(9);
    rFootUp(10);
}

// Left Hip Forward 45deg
void lHipF45(int AX12id) {
	dynamixel.setPosition(&serialPort, AX12id, 462);
	Utils::sleepMS(mdelay);
}

// Left Hip Back 45deg
void lHipB45(int AX12id) {
	dynamixel.setPosition(&serialPort, AX12id, 562);
	Utils::sleepMS(mdelay);
}

// Right Hip Forward 45deg
void rHipF45(int AX12id) {
	dynamixel.setPosition(&serialPort, AX12id, 562);
	Utils::sleepMS(mdelay);
}

// Right Hip Back 45deg
void rHipB45(int AX12id) {
	dynamixel.setPosition(&serialPort, AX12id, 462);
	Utils::sleepMS(mdelay);
}

