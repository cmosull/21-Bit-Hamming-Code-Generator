#include <stdio.h> //Libraries are included
#include <string.h>
#include <stdlib.h>
#include <math.h>

int CodeShift(int word);
int Ptest(int num, int test);
int AddParity(int cword, int pbit, int test);

int main() {
   int i,j,cnt = 1,val1,val2,max1 = 1398101,max2 = 419430,max3 = 1603704,max4 = 32640,max5 = 2064384;
   int ascii[2],icode,pbuff,pbuff2,firstP,secondP,thirdP,fourthP,fifthP;
   char values[6];
   char key[6] = {'q','u','i','t','\n','\0'};
   int code,fcode,bittest = 1;
   
   //While loop that tests if the user wants to quit the program
   while (cnt == 1) {
	  //Do while allows user to input ascii characters, and makes sure that the user inputs only 2 characters
	  do {
		 printf("\n\nPlease Enter 2 ASCII Characters or type quit: ");
		 fgets(values, 6, stdin);
	  } while (strcmp(values,key) != 0 && values[2] != '\n');

	  //Conditional that checks if the user entered in the keyword "quit" to leave the program
	  if (strcmp(values,key) == 0) {
		 cnt = 0; //If the user did, it breaks the initial While loop
	  }
	  //If the entered the input correctly, the code runs through here
	  else { 
		 ascii[0] = (int)values[0]; //Both ASCII characters are turned into int values
		 ascii[1] = (int)values[1];

		 val1 = ascii[0]; //Int values are then turned into normal ints
		 val2 = ascii[1];

		 //Both values are shifted into one int creating a 16 bit code
		 icode = (val2 << 8) + val1; 
		 code = icode;

		 //Function is called to insert the 5 parity bit slots creating a 21 bit code
		 fcode = CodeShift(code);
		 
		 //The 5 parity bits are calculated and returned using a function call
		 firstP = Ptest(fcode,max1);
		 secondP = Ptest(fcode,max2);
		 thirdP = Ptest(fcode,max3);
		 fourthP = Ptest(fcode,max4);
		 fifthP = Ptest(fcode,max5);
		 
		 //Function is called adding the parity bits to their proper spots in the 21 bit code
		 bittest = 1;
		 fcode = AddParity(fcode,firstP,bittest);
		 bittest += 1;
		 fcode = AddParity(fcode,secondP,bittest);
		 bittest += 1;
		 fcode = AddParity(fcode,thirdP,bittest);
		 bittest += 1;
		 fcode = AddParity(fcode,fourthP,bittest);
		 bittest += 1;
		 fcode = AddParity(fcode,fifthP,bittest);
		 
		 //All values are printed out to the shell
		 printf("\n\n\n\n\n--------------------------------------------------------");
		 printf("\nFirst ASCII Value: %i; Second ASCII Value: %i",ascii[1],ascii[0]); //ASCII values are printed out
		 printf("\n\nInitial 16-bit code: "); //Initial 16 bit code printed out using a for loop
		 for (i = 15; i >= 0; i--) {
			pbuff = (icode >> i);
			if (pbuff & 1) {
			   printf("1");
			}
			else {
			   printf("0");
			}
		 }
		 printf("\nInitial 16-bit code in Hex: 0x0000%X",icode); //Initiial 16 bit code printed out in Hex
		 printf("\n\nP1:%i P2:%i P3:%i P4:%i P5:%i",firstP,secondP,thirdP,fourthP,fifthP); //The 5 parity bit values are printed out here
		 printf("\n\nFinal Hamming Code in Binary: "); //Final 21-bit code is printed out in binary using a for loop
		 for (j = 20; j >= 0; j--) {
			pbuff2 = (fcode >> j);
			if (pbuff2 & 1) {
			   printf("1");
			}
			else {
			   printf("0");
			}
		 }
		printf("\nFinal Hamming Code in Hex: 0x000%X",fcode); //Final 21-bit code is printed out in hex
		printf("\n--------------------------------------------------------\n\n\n");
	  }
   }

   return 0;
}

//Function to shift the code and add the 5 parity bit slots
int CodeShift(int word) {
   int buff = 0; //Temporary buffer is initialized

   buff = (word & 2047); //P16 is inserted using bit masking and bit shifting
   word = word - buff;
   word = (word << 1) + buff;
   
   buff = (word & 15); //P8 is inserted using bit masking and bit shifting
   word = word - buff;
   word = (word << 1) + buff;
   
   buff = (word & 1); //P4 is inserted using bit masking and bit shifting
   word = word - buff;
   word = (word << 1) + buff;
   
   word = (word << 2); //P2 and P1 are inserted by shifting 2 bits over

   return word; //The final 21-bit code is returned
}

//Function that creates the proper parity bits for the 21 bit code
int Ptest(int num, int test) {
   int ind = 0, val3 = 0, buff = 0, cntr = 0,parity = 0;
   
   buff = (num & test); //The code is bit masked with a max number to create a code that allows
                        //the proper arithmetic to be done on the code to create the parity bit
   
   //For loop runs through the code and adds up all the spots where a 1 exists
   for (ind = 0; ind < 21; ind++) {
	  val3 = buff % 2;
	  
	  //Adds up all the 1's in the code
	  if (val3 == 1) {
		 cntr = cntr + 1;
	  }
	  buff = buff / 2;
   }
   //If the number of ones is odd, then the parity is a 1 to make it even
   if ((cntr % 2) == 1) {
	  parity = 1;
   }
   //If the number of ones is even, then the parity is a 0
   else {
	  parity = 0;
   }
   return parity; //Returns the parity bit
}

//Function that inserts the parity bit to its proper place
int AddParity(int cword, int pbit, int test) {

   //Conditional that checks what parity bit it is
   if (test == 1) {
	  cword = cword + pbit * pow(2,0); //If P1, it inserts the bit here
   }
   else if (test == 2) {
	  cword = cword + pbit * pow(2,1); //If P2, it inserts the bit here
   }
   else if (test == 3) {
	  cword = cword + pbit * pow(2,3); //If P4, it inserts the bit here
   }
   else if (test == 4) {
	  cword = cword + pbit * pow(2,7); //If P8, it inserts the bit here
   }
   else {
	  cword = cword + pbit * pow(2,15); //If P16, it inserts the bit here
   }
   return cword; //Returns the 21 bit code with the parity bit inserted
}

