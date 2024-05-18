#include <stdio.h>
#include <stdlib.h>

int main() {
    int choice;
    printf("Choose a option\n");
    printf("1. Bus\n");
    printf("2. Flight\n");
    printf("3. Train\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Call bus ticket booking function
            system("gcc -o bus bus.c");
            system("C:/Users/Lenovo/Downloads/ticket_booking/bus");//location of the executable file
            break;
        case 2:
            // Call flight ticket booking function
            system("gcc -o flight flight.c");
            system("C:/Users/Lenovo/Downloads/ticket_booking/flight");//location of the executable file
            break;
        case 3:
            // Call train ticket booking function
            system("gcc -o train train.c");
            system("C:/Users/Lenovo/Downloads/ticket_booking/train");//location of the executable file
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
}
