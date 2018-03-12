# MES rev 3/12/2018
C++ to control Scorpion robot - Robotis Bioloid Premium

To connect the Scorpion via USB cable to Ubuntu computer:
 - plug in the USB cable to computer and Scorpion CM-530
 - turn on power of Scorpion CM-530
 - press red "MODE" button on Scorpion CM-530 until "PC LINK" light is "MANAGE" (top light)
 - press "START" button on Scorpion CM-530
 - verify on computer that /dev/ttyUSB0 appears
     - if /dev/ttyUSB0 does not appear, trying unplugging all cables from computer and robot, try again
 - sudo chmod 777 /dev/ttyUSB0

 Once the Scorpion is successfully connected to the Ubuntu computer, compile the code:
  - make

 Then, run the program:  
  - ./scorp
