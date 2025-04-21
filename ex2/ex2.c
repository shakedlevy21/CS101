/******************
Name: shaked levy
Assignment: ex2
*******************/


#include <stdio.h>

int main() {
	// Case 1: Draw Happy Face with given symbols for eyes, nose and mouse
	/* Example:
	* n = 3:
	* 0   0
	*   o
	* \___/
	*/
	//flag for breaking
	int flag = 1, option = 1;
	//Case 1
    int space = 0;
	char eyes, nose, mouth;
	//Case 2
	int num, temp, counter = 0;
	int sumright = 0, sumleft = 0;
	int skipodd = 0;;
	//Case 3
	int sum	= 0;
	//Case 4
	int reversedigit = 0, flag4 = 0;
	//Case 5
	int digit = 0, shownum;
	//Case 6
	int cheer = 0, smile = 0, maxnum;
while (flag) {
	printf("Choose an option:\n    1. Happy Face\n    2. Balanced Number\n    3. Generous Number\n    4. Circle Of Joy\n    5. Happy Numbers \n    6. Festival Of Laughter\n    7. Exit\n");
	scanf("%d", &option);
	//each start of a case we will zero the variables for more than one use, else they will keep the value from previous cases
	switch (option)
	{

		case 1:
		{
			//eyes
			printf("Enter symbols for the eyes, nose, and mouth:\n");
			scanf(" %c %c %c", &eyes, &nose, &mouth);
			printf("Enter face size:\n");
			scanf(" %d", &space);
			while (1)
			{
				if(space % 2 == 1 && space >= 1) {
					break;
				} else {
					printf("The face's size must be an odd and positive number, please try again:\n");
					scanf("%d", &space);
				}
			}
			//eyes
			printf("%c", eyes);
			for (int i = 1; i <= space; i++) {
				printf(" ");
			}
			printf("%c\n", eyes);
			//nose
			for (int i = 1; i <= space/2+1; i++) {
				printf(" ");
			}
			printf("%c\n", nose);

			//mouth
			printf("\\");
			for (int i = 1; i <= space; i++) {
				printf("%c", mouth);
			}
			printf("/\n");
			continue;
		}
		case 2:
		{
			counter = 0, sumright = 0, sumleft = 0, skipodd = 0;
			printf("Enter a number:\n");
			scanf("%d", &num);
			while (1) {
				if (num >= 1) {
					break;
				} else {
					printf("Only positive number is allowed, please try again:\n");
					scanf("%d", &num);
				}
			}
			//counter for size of digits
			temp = num;
			while (temp != 0) {
				temp = temp / 10;
				counter++;
			}
			temp = num;
			//now the counter is the number of digits in the num

			if (counter % 2 == 1) {
				skipodd = 1;
			}
			counter/=2;

			while (counter != 0) {
				sumright = sumright + (temp%10);
				temp/=10;
				counter--;
			};
			if (skipodd == 1) {
				temp/=10;
			};
			while (temp != 0) {
				sumleft = sumleft + temp%10;
				temp/=10;
			};
			if (sumleft == sumright) {
				printf("This number is balanced and brings harmony!\n");
			} else {
				printf("This number isn't balanced and destroys harmony.\n");
			}
			continue;
		}
		case 3:
		{
			sum = 0;
			printf("Enter a number:\n");
			scanf("%d", &num);
			while (1) {
				if (num >= 1) {
					break;
				} else {
					printf("Only positive number is allowed, please try again:\n");
					scanf("%d", &num);
				}
			}
			for (int i = 2; i < num; i++) {
				if (num % i == 0) {
					sum+=i;
				};
			}
			if (sum > num) {
				printf("This number is generous!\n");
			} else {
				printf("This number does not share.\n");
			}
			continue;
		}
		case 4:
		{
			sum = 0, flag4 = 0, reversedigit = 0;
			printf("Enter a number:\n");
			scanf("%d", &num);
			while (num < 1) {
					printf("Only positive number is allowed, please try again:\n");
					scanf("%d", &num);
			}
			for (int i = 2; i < num; i++) {
				if (num % i == 0) {
					printf("The circle remains incomplete.\n");
					flag4 = 1;
					break;
				}
			}
			if (flag4 == 1) {
				break;
			}
			//now we will check the reverse number
			while (num != 0) {
				reversedigit = num % 10;
				num = num / 10;
				if (num == 0) {
					sum = (sum + reversedigit);
				} else {
					sum = (sum + reversedigit) * 10;
				}
			}
			//now the number "sum" is reversed
			for (int i = 2; i < sum; i++) {
				if (sum % i == 0) {
					printf("The circle remains incomplete.\n");
					flag4 = 1;
					break;
				}
				//printf("This number completes the circle of joy!\n");
			}
			if (flag4 == 0) {
				printf("This number completes the circle of joy!\n");
			}
			continue;
		}
		case 5:
		{
			sum = 0;
			printf("Enter a number:\n");
			scanf("%d", &num);
			while (1) {
				if (num >= 1) {
					break;
				} else {
					printf("Only positive number is allowed, please try again:\n");
					scanf("%d", &num);
				}
			}
			shownum = num;
			//the shownum is temp for the num because we make a lot of changes to it
			printf("Between 1 and %d only these numbers bring happiness: 1", shownum);
			for (int i = 2; i <= shownum;i++) {
				num = i;
				while (1) {
					sum = 0;
					while(num > 0) {
						digit = num % 10;
						sum = sum + (digit*digit);
						num = num / 10;
					}
					//the only two digits that are happy are 1 and 7 so we will check the number until it will arrive at less than 10
					if (sum <= 9) {
						if (sum == 1 || sum == 7) {
							printf(" %d", i);
							break;
						}
						break;
					}
					num = sum;
				}
			}
			printf("\n");
			continue;
		}
		case 6:
		{

			printf("Enter a smile and cheer number:\n");
			//this cleans the buffer by telling it to scan only after the \n and delete everything before that
			scanf("%*[^'\n']");
			scanf(" smile: %d, cheer: %d", &smile, &cheer);
			if (cheer == 0 && smile == 0) {
				while (1)
				{
					printf("Only 2 different positive numbers in the given format are allowed for the festival, please try again:\n");
					scanf("%*[^'\n']");
					scanf(" smile: %d, cheer: %d", &smile, &cheer);
					if (cheer != 0 && smile != 0) {
						break;
					}
				}
			}

			//ask for the max number
			printf("Enter maximum number for the festival:\n");
			scanf("%d", &maxnum);
			while (1) {
				if (maxnum >= 1) {
					break;
				} else {
					printf("Only positive maximum number is allowed, please try again:\n");
					scanf("%d", &maxnum);
				}
			}
			for (int i = 1; i <= maxnum; i++) {
				if (i % cheer == 0 && i % smile == 0) {
					printf("Festival!\n");
				}
				else if (i % cheer == 0) {
					printf("Cheer!\n");
				}
				else if (i % smile == 0) {
					printf("Smile!\n");
				} else {
					printf("%d\n", i);
				}
			}
			//does not require continue but just for uniformity
			continue;
		}
		case 7:
		{
			break;
		}
	}
	if (option == 7) {
		printf("Thank you for your journey through Numeria!\n");
		break;
	}
	if (option > 7 || option < 1) {
		printf("This option is not available, please try again.\n");
	}
}

	// Case 2: determine whether the sum of all digits to the left of the middle digit(s)
	// and the sum of all digits to the right of the middle digit(s) are equal
	/* Examples:
	Balanced: 1533, 450810, 99
	Not blanced: 1552, 34
	Please notice: the number has to be bigger than 0.
	*/
	//size of number


	// Case 3: determine whether the sum of the proper divisors (od an integer) is greater than the number itself
	/* Examples:
	Abudant: 12, 20, 24
	Not Abudant: 3, 7, 10
	Please notice: the number has to be bigger than 0.
	*/


	// Case 4: determine weather a number is a prime.
	/* Examples:
	This one brings joy: 3, 5, 11
	This one does not bring joy: 15, 8, 99
	Please notice: the number has to be bigger than 0.
	*/

		// it will check the second if only if the for didnt break which means the number is prime

	// Happy numbers: Print all the happy numbers between 1 to the given number.
	// Happy number is a number which eventually reaches 1 when replaced by the sum of the square of each digit
	/* Examples:
	Happy :) : 7, 10
	Not Happy :( : 5, 9
	Please notice: the number has to be bigger than 0.
	*/

	// Festival of Laughter: Prints all the numbers between 1 the given number:
	// and replace with "Smile!" every number that divided by the given smile number
	// and replace with "Cheer!" every number that divided by the given cheer number
	// and replace with "Festival!" every number that divided by both of them
	/* Example:
	6, smile: 2, cheer: 3 : 1, Smile!, Cheer!, Smile!, 5, Festival!
	*/
	return 0;
};
