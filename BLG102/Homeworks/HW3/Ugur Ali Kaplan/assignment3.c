/*
* Copyright (c) 2018 by Uğur Ali Kaplan
* You are free to do anything you want with this code
* provided you give attribute to original author.
*/

#include <stdio.h> // for printf and scanf
#include <stdbool.h> // for boolean data type
#include <stdlib.h>
#define SIZE 50

// function prototypes
void calculate_distance(bool park[][SIZE], int result[2], int size);
void place_cars(bool park[][SIZE], int size);

int main(void){
    // Learn the size of parking lot
    int size;
    printf("Size: ");
    bool work = false;
    
    while (scanf("%d", &size) == 1){
        while (size > 50 || size <= 0){
            if (size > 50){
                printf("max size must be 50\n");
            } else {
                printf("min size must be 1\n");
            }
            printf("Size: ");
            scanf("%d", &size);
        }


        // Learn the the number of cars
        int cars;
        printf("Cars: ");
        scanf("%d", &cars);
        while (cars < 0){
            printf("min size must be 0\n");
            printf("Size: ");
            scanf("%d", &cars);
        }

        // Initiliaze the parking lot
        bool park[SIZE][SIZE] = {0};
        if (cars == size * size){
            printf("Best Slot Found In: 0 0\n");
            work = true;
        } else {
            for(int i = 0; i < cars; i++){
                place_cars(park, size);
            }

            // Code showing the parking lot if needed
            // for(int i = 0; i < size; i++){
            //     for(int j = 0; j < size; j++){
            //         printf("%d |", park[i][j]);
            //     }
            //     printf("\n");
            // }

            int result[2]; // (result[0], result[1]) = (x, y) for best spot
            calculate_distance(park, result, size);

            work = true;
            printf("Best Slot Found In: %d %d\n", result[0], result[1]);

        }
        if (!work){
            printf("You should enter an integer!\n");
            return EXIT_FAILURE;
        } else {
        return EXIT_SUCCESS;
        }
    }
}

/*
*   place_cars places the cars in the parking lot according to
*   information given by the user
*   @param park[][SIZE] is a 2d array representing our parking space
*   @param size specifies the park size entered by the user
*/

void place_cars(bool park[][SIZE], int size){
    int comp1, comp2;
    printf("Locations: ");
    // Take two integers
    if (scanf("%d %d", &comp1, &comp2) == 2){
        // Check if it is in the range
        if (comp1 <= size && comp2 <= size){
            // Check if it is occupied
            if (!park[size - comp2][comp1 - 1] && ((comp1 >= 1) && (comp2 >= 1))){
                // Place the car
                park[size - comp2][comp1 - 1] = 1;
            }
        }
        }
    }


/*
*   calculate_distance finds the best spot for our car to park
*   and gives these values to result[0] and result[1]
*   @param park[][SIZE] a 2d array representing our parking space
*   @param result[2] this will hold coordinates for our best case scenario
*   @param size specifies the park size entered by the user
*/
void calculate_distance(bool park[][SIZE], int result[2], int size){
    int max_distance = 0;
    int x_empty, y_empty;
    result[0] = 0;
    result[1] = 0;
    int closest_distance;
    // Going through the parking lots one by one
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            // where we are right now
            x_empty = j + 1;
            y_empty = size - i;
            // is it empty
            if (!park[i][j]){
                closest_distance = 100;
                // if it is empty, look for occupied spaces one by one
                for (int k = 0; k < size; k++){
                    for (int l = 0; l < size; l++){
                        // is it occupied
                        if (park[k][l]){
                            // getting the absolute value of x and y distances
                            int x_dist = (l > j) ? (l - j) : (j - l);
                            int y_dist = (k > i) ? (k - i) : (i - k);
                            // add them together
                            int distance = x_dist + y_dist;
                            // is this occupied space closest one to me?
                            if (distance < closest_distance){
                                closest_distance = distance;
                            }
                        }
                    }
                }
            // is nearest car to this empty lot is further
            // away compared the other lots
            // obviously prefer lower x and y values values
            if (closest_distance > max_distance){
                result[0] = x_empty;
                result[1] = y_empty;
                max_distance = closest_distance;
            } else if (closest_distance == max_distance){
                if (x_empty < result[0]){
                    result[0] = x_empty;
                    result[1] = y_empty;
                    max_distance = closest_distance;
                } else if (x_empty == result[0]){
                    if (y_empty < result[1]){
                        result[0] = x_empty;
                        result[1] = y_empty;
                        max_distance = closest_distance;
                    }
                }
            }
            }
        }
    }
}
