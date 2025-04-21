/******************
Name: Shaked levy
Assignment: ex1
*******************/
#include <stdio.h>

// REMIDER : YOU CANT USE ANY CONTROL FLOW OPERATIONS OR FUNCTIONS, ONLY BITWISE.

int main() {

  // What bit

  /*Scan two integers (representing number and a position)
  Print the bit in this position. */
  printf("What bit:\n");
  int num, pos;
  //scan for 2 integers and saves them
  printf("Please enter a number:\n");
  scanf("%d",&num);
  printf("Please enter a position:\n");
  scanf("%d",&pos);
  //the scans above can be written in one line, i wrote it like that to see the logic

  //shifts the num by number of pos and checks with one to print 0 or 1 the least of them
  int bit = (num >> pos)&1;
  printf("The bit in position %d of number %d is: %d\n", pos, num, bit);

  //********************************************************//

  // Set bit

  /*Scan two integers (representing number and a position)
  Make sure the bit in this position is "on" (equal to 1)
  Print the output
  Now make sure it's "off" (equal to 0)
  Print the output */
  printf("\nSet bit:\n");

  printf("Please enter a number:\n");
  scanf("%d",&num);
  printf("Please enter a position:\n");
  scanf("%d",&pos);
  // new int for how much to add or subtract
  int mask = 1 << pos;
  // to check we will take the mask and turn it from 0001 to 1110 and check for the 0 that shows up in the two numbers
  //xnor and flip the mask and use 1's compliment
  printf("Number with bit %d set to 1: %d\n", pos, mask | num);
  printf("Number with bit %d set to 0: %d\n", pos, ~mask & num);

  //**************************************************//

  // Toggle bit
  /*Scan two integers (representing number and a position)
  Toggle the bit in this position
  Print the new number */
  printf("\nToggle bit:\n");

  printf("Please enter a number:\n");
  scanf("%d",&num);
  printf("Please enter a position:\n");
  scanf("%d",&pos);

  mask = 1 << pos;
  bit = mask ^ num;
  printf("Number with bit %d toggled: %d\n",pos, bit);

  //************************************************//

  // Even - Odd
  /* Scan an integer
If the number is even - print 1, else - print 0. */
  printf("\nEven - Odd:\n");
  int num1;
  printf("Please enter a number:\n");
  scanf("%d",&num1);
  //we want to take only the lsb because it is the one that decides if the number is odd or even
  printf("%d\n", (num1&1)^1);

  // 3, 5, 7, 11
  printf("\n3, 5, 7, 11:\n");
  /* Scan two integers in octal base
  sum them up and print the result in hexadecimal base
  Print only 4 bits, in positions: 3,5,7,11 in the result. */
  printf("Please enter the first number (octal):\n");
  scanf("%o",&num);
  printf("Please enter the second number (octal):\n");
  scanf("%o",&pos);

  int hexnum = num + pos;
  printf("The sum in hexadecimal: %X\n",hexnum);
  printf("The 3,5,7,11 bits are: %d%d%d%d\n",(hexnum>>3)&1, (hexnum>>5)&1, (hexnum>>7)&1, (hexnum>>11)&1);


  printf("Bye!\n");
  
  return 0;
}
