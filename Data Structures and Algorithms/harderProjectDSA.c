#include <stdio.h>
#include <stdlib.h>

#define PEDESTRIAN_SPEED 1e9 // Pedestrian speed: 1 lane per second (in picoseconds)
#define CAR_SPEED 1e9 // Car speed: 1 lane per second (in picoseconds)
#define CROSSING_TIME 7.2e9 // Time for the pedestrian to cross all lanes (7.2 seconds in picoseconds)

// Function to calculate the earliest safe crossing time for a pedestrian
long calculate_safe_crossing_time(int a, int b, long **left_cars, int *left_car_counts, long **right_cars, int *right_car_counts) {
    long time = 0;
    
    // Iterate through each lane with cars coming from the left
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < left_car_counts[i]; j++) {
            long car_position = left_cars[i][j];
            // Calculate the time for the car to reach the crossing point
            long car_time = car_position / CAR_SPEED;
            // If the car's time conflicts with the pedestrian's crossing time, adjust the crossing time
            if (car_time + CROSSING_TIME > time) {
                time = car_time + CROSSING_TIME;
            }
        }
    }
    
    // Iterate through each lane with cars coming from the right
    for (int i = 0; i < b; i++) {
        for (int j = 0; j < right_car_counts[i]; j++) {
            long car_position = right_cars[i][j];
            // Calculate the time for the car to reach the crossing point
            long car_time = (car_position - (720 * CAR_SPEED)) / CAR_SPEED;
            // If the car's time conflicts with the pedestrian's crossing time, adjust the crossing time
            if (car_time + CROSSING_TIME > time) {
                time = car_time + CROSSING_TIME;
            }
        }
    }
    
    // Return the earliest safe crossing time
    return time;
}

int main() {
    int a = 2, b = 3;
    
    // Allocate memory for car counts
    int *left_car_counts = malloc(a * sizeof(int));
    int *right_car_counts = malloc(b * sizeof(int));
    
    // Allocate memory for left car lanes
    long **left_cars = malloc(a * sizeof(long *));
    left_car_counts[0] = 1;
    left_car_counts[1] = 1;
    left_cars[0] = malloc(1 * sizeof(long));
    left_cars[1] = malloc(1 * sizeof(long));
    left_cars[0][0] = 9000000000;
    left_cars[1][0] = 3781250000;

    // Allocate memory for right car lanes
    long **right_cars = malloc(b * sizeof(long *));
    right_car_counts[0] = 2;
    right_car_counts[1] = 0;
    right_car_counts[2] = 4;
    right_cars[0] = malloc(2 * sizeof(long));
    right_cars[1] = malloc(0 * sizeof(long));
    right_cars[2] = malloc(4 * sizeof(long));
    right_cars[0][0] = 11781250000;
    right_cars[0][1] = 25000000000;
    right_cars[2][0] = 1000000000;
    right_cars[2][1] = 6000000000;
    right_cars[2][2] = 17000000000;
    right_cars[2][3] = 27781250000;
    
    // Calculate the earliest safe crossing time
    long safe_crossing_time = calculate_safe_crossing_time(a, b, left_cars, left_car_counts, right_cars, right_car_counts);
    // Print the earliest safe crossing time
    printf("%ld\n", safe_crossing_time);

    // Free allocated memory
    for (int i = 0; i < a; i++) {
        free(left_cars[i]);
    }
    for (int i = 0; i < b; i++) {
        free(right_cars[i]);
    }
    free(left_cars);
    free(right_cars);
    free(left_car_counts);
    free(right_car_counts);

    return 0;
}