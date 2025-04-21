/******************
Name: shaked levy
ID:212730311
Assignment: ex3
*******************/

#include <stdio.h>


#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

#define addOne 1
#define addAll 2
#define stats 3
#define print 4
#define insights 5
#define deltas 6
#define done 7

void printMenu();
int If_Brand_Value(int day, int brand, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int TYPES_SIZE);
void Insert_Type_For_Brand(int day, int brandchoice, int suvchoice, int sedanchoice, int coupechoice, int gtchoice,
    int cube[][NUM_OF_BRANDS][NUM_OF_TYPES]);
int Brand_Sum_Sales(int day, int brandchoice, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int TYPES_SIZE);
int Best_Brand_Sales(int day, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int BRANDS_SIZE, int TYPES_SIZE);
int Type_Sum_Sales(int day, int type, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int BRANDS_SIZE);
int Best_Type_Sales(int day, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int BRANDS_SIZE, int TYPES_SIZE);
int All_Brands_Day_Sum_Sales(int day, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int BRANDS_SIZE, int TYPES_SIZE);
double Delta_Average(int brand, int currentday, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int TYPES_SIZE);


int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];//365*5*4
    int choice;
    int day = 0, sum = 0;
    int counter;
    int daychoice;
    //integers for case 1 and 2 use of choices
    int brandchoice, suvchoice, sedanchoice, coupechoice, gtchoice;

    //set cube to -1
    for (int i = 0; i < DAYS_IN_YEAR; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int w = 0; w < NUM_OF_TYPES; w++) {
                cube[i][j][w] = -1;
            }
        }
    }

    //first print
    printMenu();
    scanf("%d", &choice);

    //while for menu
    while(choice != done)
    {
        switch(choice)
        {
            case addOne:
            {
                printf("Enter Brand by index and 4 integers for SUV, Sedan, Coupe, GT: \n");
                scanf("%d %d %d %d %d", &brandchoice, &suvchoice, &sedanchoice, &coupechoice, &gtchoice);
                if (brandchoice < 0 || brandchoice > 4) {
                    printf("This brand is not valid\n");
                    printf("Enter Brand by index and 4 integers for SUV, Sedan, Coupe, GT: ");
                    scanf("%d %d %d %d %d", &brandchoice, &suvchoice, &sedanchoice, &coupechoice, &gtchoice);
                }
                cube[day+1][brandchoice][0] = suvchoice;
                cube[day+1][brandchoice][1] = sedanchoice;
                cube[day+1][brandchoice][2] = coupechoice;
                cube[day+1][brandchoice][3] = gtchoice;
                break;
            }
            case addAll:
            {
                counter = 0;
                while(counter < 4)
                {
                    counter = 0;
                    printf("No data for brands ");
                    for (int i = 0; i < NUM_OF_BRANDS; i++) {
                        if (!If_Brand_Value(day, i, cube, NUM_OF_TYPES)) {
                            printf("%s ",brands[i]);
                        } else {
                            counter++;
                        }
                    }
                    printf("\nPlease complete the data\n");
                    //scan and check for a valid brand
                    do {
                        scanf("%d", &brandchoice);
                        scanf("%d %d %d %d", &suvchoice, &sedanchoice, &coupechoice, &gtchoice);
                        if (brandchoice < 0 || brandchoice > 4) {
                            printf("This brand is not valid\n");
                        }
                    } while ((brandchoice<0 || brandchoice>4) && !If_Brand_Value(day,brandchoice,cube,NUM_OF_TYPES));

                    //set the data for the current day
                    Insert_Type_For_Brand(day, brandchoice, suvchoice, sedanchoice, coupechoice, gtchoice, cube);

                }
                day++;
                break;
            }
            case stats:
            {
                //for second uses of the case
                sum = 0;
                //scan for a valid day
                do {
                    printf("What day would you like to analyze? \n");
                    scanf("%d", &daychoice);
                    daychoice--;//because the user inputs days from 1 to 365
                    if (daychoice < 0 || daychoice >= day) {
                        printf("Please enter a valid day.\n");
                    }
                } while (daychoice < 0 || daychoice >= day);


                printf("In day number %d:\n", daychoice+1);

                //sales summary
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    sum += Brand_Sum_Sales(daychoice, i, cube, NUM_OF_TYPES);
                }
                printf("The sales total was %d\n", sum);

                //best sales brand
                brandchoice = Best_Brand_Sales(daychoice, cube, NUM_OF_BRANDS, NUM_OF_TYPES);

                //condition if there is no company with best sales
                if (brandchoice == -1) {
                    printf("There is no brand with the best sales for this day\n");
                } else {
                    printf("The best sold brand with %d sales was %s\n"
                        , Brand_Sum_Sales(daychoice, brandchoice, cube, NUM_OF_TYPES), brands[brandchoice]);
                }

                //best types sales
                brandchoice = Best_Type_Sales(daychoice, cube, NUM_OF_BRANDS, NUM_OF_TYPES);
                //I am using the brandchoice 2 times because there is no point in assigning another variable
                //condition if there is no type with best sales
                if (brandchoice == -1) {
                    printf("There is no type with the best sales for this day\n");
                } else {
                    printf("The best sold type with %d sales was %s\n",
                        Type_Sum_Sales(daychoice, brandchoice, cube, NUM_OF_BRANDS), types[brandchoice]);
                }
                break;
            }
            case print:
            {
                daychoice = 0;
                printf("*****************************************\n\n");

                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    printf("Sales for %s:\n", brands[i]);
                    for (int j = 0; j < DAYS_IN_YEAR; j++) {
                        if (If_Brand_Value(j, i, cube, NUM_OF_TYPES)) {
                            printf("Day %d- SUV: %d Sedan: %d Coupe: %d GT: %d\n",
                                (1+j), cube[j][i][0], cube[j][i][1], cube[j][i][2], cube[j][i][3]);
                        }
                    }
                }

                printf("\n*****************************************\n");
                break;
            }
            case insights:
            {
                //best selling brand overall
                int bestbrand[NUM_OF_BRANDS] = {0, 0, 0, 0, 0};
                int sumbestbrand = 0, bestbrandindex = -1;
                //*****************************************
                //add to the sum of each brand
                for (int i = 0; i < day; i++) {
                    for (int j = 0; j < NUM_OF_BRANDS; j++) {
                        bestbrand[j] += Brand_Sum_Sales(i, j, cube, NUM_OF_TYPES);
                    }
                }

                //check for the highest sales in each brand
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    if(sumbestbrand < bestbrand[i]) {
                        sumbestbrand = bestbrand[i];
                        bestbrandindex = i;
                    }
                }

                //check if no brand has the best and print, the -1 is if there is no values in the cube
                if(bestbrandindex == -1) {
                    printf("There is no brand with the best sales\n");
                } else {
                    printf("The best-selling brand overall is %s: %d$\n",
                        brands[bestbrandindex],bestbrand[bestbrandindex]);
                }
                //*************************************

                //Best selling type overall
                int besttype[NUM_OF_TYPES] = {0, 0, 0, 0};
                int sumbesttype = 0, besttypeindex = -1;

                //*************************************
                for (int i = 0; i < day; i++) {
                    for (int j = 0; j < NUM_OF_TYPES; j++) {
                        besttype[j] += Type_Sum_Sales(i, j, cube,NUM_OF_BRANDS);
                    }
                }

                //check for the highest sales in each type
                for (int i = 0; i < NUM_OF_TYPES; i++) {
                    if(sumbesttype < besttype[i]) {
                        sumbesttype = besttype[i];
                        besttypeindex = i;
                    }
                }

                //check if no type has the best and print, the -1 is if there is no values in the cube
                if(besttypeindex == -1) {
                    printf("There is no car type with the best sales\n");
                } else {
                    printf("The best-selling type of car is %s: %d$\n",
                        types[besttypeindex],besttype[besttypeindex]);
                }
                //**********************************

                //The most profitable day
                int bestdaysum = -1, bestdayindex = -1;
                //**********************************
                for (int i = 0; i < DAYS_IN_YEAR; i++) {
                    if(bestdaysum < All_Brands_Day_Sum_Sales(i, cube, NUM_OF_BRANDS, NUM_OF_TYPES)) {
                        bestdaysum = All_Brands_Day_Sum_Sales(i, cube, NUM_OF_BRANDS, NUM_OF_TYPES);
                        bestdayindex = i;
                    }
                }

                //check if there is no most profitable day and print
                if(bestdayindex == -1) {
                    printf("there is no day that is the most profitable");
                } else {
                    printf("The most profitable day was day number %d: %d$\n", bestdayindex + 1, bestdaysum);
                }
                //*********************************
                break;
            }
            case deltas:
            {
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    printf("Brand: %s, Average Delta: %f\n", brands[i], Delta_Average(i, day, cube, NUM_OF_TYPES));
                }

                break;
            }
            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }

    printf("Goodbye!\n");
    return 0;
}

void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}

//checks a brand if at least one value is -1 that means its empty
int If_Brand_Value(int day, int brand,int cube[][NUM_OF_BRANDS][NUM_OF_TYPES],int TYPES_SIZE) {
    for (int i = 0; i < TYPES_SIZE; i++) {
        if(cube[day][brand][i] == -1) {
            return 0;
        }
     }
    return 1;
}

void Insert_Type_For_Brand(int day, int brandchoice, int suvchoice, int sedanchoice, int coupechoice, int gtchoice,
    int cube[][NUM_OF_BRANDS][NUM_OF_TYPES]) {
        cube [day][brandchoice][0] = suvchoice;
        cube [day][brandchoice][1] = sedanchoice;
        cube [day][brandchoice][2] = coupechoice;
        cube [day][brandchoice][3] = gtchoice;
}

int Brand_Sum_Sales(int day, int brandchoice, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int TYPES_SIZE) {
    int sum = 0;
    for (int i = 0; i < TYPES_SIZE; i++) {
        if (cube[day][brandchoice][i] != -1) {
            sum += cube[day][brandchoice][i];
        }
    }
    return sum;
}

int Best_Brand_Sales(int day, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int BRANDS_SIZE, int TYPES_SIZE) {
    int bestsum = -1, bestbrand = -1, sumtemp;

    for (int i = 0; i < BRANDS_SIZE; i++) {
        sumtemp = Brand_Sum_Sales(day, i, cube, TYPES_SIZE);
        if (bestsum < sumtemp) {
            bestsum = sumtemp;
            bestbrand = i;
        }

    }
    return bestbrand;
}

int Type_Sum_Sales(int day, int type, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int BRANDS_SIZE) {
    int sum = 0;
    for (int i = 0; i < BRANDS_SIZE; i++) {
        sum += cube[day][i][type];
    }
    return sum;
}

int Best_Type_Sales(int day, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int BRANDS_SIZE, int TYPES_SIZE) {
    int bestsum = -1, besttype = -1, sumtemp;

    for (int i = 0; i < TYPES_SIZE; i++) {
        sumtemp = Type_Sum_Sales(day, i, cube, BRANDS_SIZE);
        if (bestsum < sumtemp) {
            bestsum = sumtemp;
            besttype = i;
        }

    }
    return besttype;
}

int All_Brands_Day_Sum_Sales(int day, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int BRANDS_SIZE, int TYPES_SIZE) {
    int sum = 0;
    for (int i = 0; i < BRANDS_SIZE; i++) {
        for (int j = 0; j < TYPES_SIZE; j++) {
            sum += cube[day][i][j];
        }
    }
    return sum;
}

double Delta_Average(int brand,int currentday, int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int TYPES_SIZE) {
    double sum = 0, difference;
    for (int i = 1; i < currentday; i++) {
        difference = Brand_Sum_Sales(i, brand, cube, TYPES_SIZE)-Brand_Sum_Sales(i-1, brand, cube, TYPES_SIZE);
        sum += difference;
    }
    return sum/(currentday-1);
}
