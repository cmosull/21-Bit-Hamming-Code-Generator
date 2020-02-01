# 21-Bit-Hamming-Code-Generator

## Basic Description
The purpose of this program is to take two ASCII characters entered by user and generate a 21-bit Hamming code using a couple functions that I created that use basic bit-masking on the ASCII character's binary values. The five parity bits are calculated and inserted into the 16-bit code using a simple function I created. All functions are included in the C file becuase I did not see the need to add a seperate file for the functions since the program itself is very compact and basic. For better readability, I have it all in one file. I've put this code up so that programmers starting to learn C can see and example of bit-masking implemented in a program.

  It's meant to be run from the command line and takes no arguments at the command line. After taking inputs from the user, a basic output is printed in the terminal for the user showing a relatively clean display of the generated Hamming code. Users can generate as many Hamming codes as they want and need to type in the proper command for the program to quit. At some point in the future I plan to clean up the file, and condense it into more functions, and will create a seperate file for those who want just the functions.
  
## Tools and Further Comments
I already provide an executable, but feel free to take the source code and compile yourself. This file was complied using gcc version 7.4.0 on Ubuntu 18.04.1.

The following libraries are used:

  *stdio.h
  
  *string.h
  
  *stdlib.h
  
  *math.h
  
I did my best to provide helpful comments to enchance code reading. If a comment is unclear or unhelpful, please change it and recommit the updated file.
