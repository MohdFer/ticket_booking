#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_TICKETS 5

// ANSI color escape codes
#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"

// Structure to store train information
struct Train {
    int sl_no;
    char date[11];
    char boarding[4];
    char destination[4];
    char train_name[50];
    int train_no;
    char departure_time[6];
    char arrival_time[6];
    int platform_no;
};

// Structure to store passenger information
struct Passenger {
    char name[MAX_NAME_LENGTH];
    int age;
    int compartment_class;
    int seat_no;
    float fare;
};

// Function to display available trains
void displayAvailableTrains(struct Train trains[], int n) {
    printf("+------+-----------+-------------+--------------+---------------------------------------+-----------+----------------+--------------+-------------+\n");
    printf("|SL.NO.|  DATE     |  BOARDING   |  DESTINATION | TRAIN NAME                            | TRAIN NO. | DEPARTURE TIME | ARRIVAL TIME | PLATFORM NO.|\n");
    printf("+------+-----------+-------------+--------------+---------------------------------------+-----------+----------------+--------------+-------------+\n");
    int i;
	for (i = 0; i < n; i++) {
        printf("| %-5d| %-10s| %-12s| %-13s| %-32s      | %-10d| %-15s| %-13s| %-12d|\n",
               trains[i].sl_no, trains[i].date, trains[i].boarding, trains[i].destination, 
               trains[i].train_name, trains[i].train_no, trains[i].departure_time, 
               trains[i].arrival_time, trains[i].platform_no);
    }
    printf("+------+-----------+-------------+--------------+---------------------------------------+-----------+----------------+--------------+-------------+\n");
}

// Function to book tickets
void bookTicket(struct Train *train, struct Passenger passengers[], int *num_tickets) {
    int num_tickets_to_book;
    printf("Enter the number of tickets to book: ");
    scanf("%d", &num_tickets_to_book);

    if (num_tickets_to_book <= 0) {
        printf("Invalid number of tickets.\n");
        return;
    }

    int i;
	for ( i = 0; i < num_tickets_to_book; i++) {
        printf("\nPassenger %d:\n", *num_tickets + i + 1);
        printf("Name: ");
        scanf(" %[^\n]s", passengers[*num_tickets + i].name);
        printf("Age: ");
        scanf("%d", &passengers[*num_tickets + i].age);
        printf("Compartment Class (1: First Class, 2: Sleeper Class, 3: General Compartment): ");
        scanf("%d", &passengers[*num_tickets + i].compartment_class);
        printf("Seat Number: ");
        scanf("%d", &passengers[*num_tickets + i].seat_no);

        // Calculate fare (example fares for demonstration purposes)
        if (passengers[*num_tickets + i].compartment_class == 1)
            passengers[*num_tickets + i].fare = 1671.0; // Example fare for First Class
        else if (passengers[*num_tickets + i].compartment_class == 2)
            passengers[*num_tickets + i].fare = 447.0; // Example fare for Sleeper Class
        else if (passengers[*num_tickets + i].compartment_class == 3)
            passengers[*num_tickets + i].fare = 438.0; // Example fare for General Compartment
    }

    *num_tickets += num_tickets_to_book;

    // Ticket booking confirmation
    printf("\nTickets booked successfully for Train %d (%s) from %s to %s.\n", train->train_no, train->train_name, train->boarding, train->destination);
}

// Function to print receipt
void printReceipt(struct Train *train, struct Passenger passengers[], int num_tickets) {
    printf("\n--------------------- RECEIPT ---------------------\n");
    printf("TRAIN DETAILS:\n");
    printf("Train Name: %s\n", train->train_name);
    printf("Train No.: %d\n", train->train_no);
    printf("Date: %s\n", train->date);
    printf("Boarding: %s\n", train->boarding);
    printf("Destination: %s\n", train->destination);
    printf("Departure Time: %s\n", train->departure_time);
    printf("Arrival Time: %s\n", train->arrival_time);
    printf("Platform No.: %d\n", train->platform_no);
    printf("+------------------------------------------------------------------+\n");
    printf("|                       PASSENGER DETAILS:                         |\n");
    printf("+------------------------------------------------------------------+\n");                            
    printf("| %-5s| %-20s| %-4s| %-19s| %-9s|\n", "No.", "Name", "Age", "Compartment Class", "Fare");
    printf("+------------------------------------------------------------------+\n");
    float total_fare = 0.0;
    int i;
    for ( i = 0; i < num_tickets; i++) {
        char compartment[20];
        if (passengers[i].compartment_class == 1)
            strcpy(compartment, "First Class");
        else if (passengers[i].compartment_class == 2)
            strcpy(compartment, "Sleeper Class");
        else if (passengers[i].compartment_class == 3)
            strcpy(compartment, "General Compartment");
        printf("| %-5d| %-20s| %-4d| %-19s| " GREEN "Rs.%-6.2f" RESET "|\n", i + 1, passengers[i].name, passengers[i].age, compartment, passengers[i].fare);
        total_fare += passengers[i].fare;
    }
    printf("+------------------------------------------------------------------+\n");
    printf("|                                             TOTAL FARE: "GREEN "Rs.%6.2f" RESET "|\n", total_fare);
    printf("+------------------------------------------------------------------+\n");
}

int main() {
    // Array to store available trains
    struct Train trains[] = {
        {1, "08/05/2024", "MS", "CBE", "Coimbatore Shatabdi Express", 12243, "08:00", "10:00", 1},
        {2, "09/05/2024", "MS", "TPJ", "Tiruchirappalli Rockfort Express", 12653, "10:30", "13:00", 3},
        {3, "09/05/2024", "MS", "NJT", "Nagercoil Guruvayur Express", 16344, "10:30", "13:00", 2},
        {4, "09/05/2024", "MS", "MDU", "Madurai Pandian Express", 12637, "10:30", "13:00", 1},
        {5, "10/05/2024", "MS", "TJ", "Thanjavur Uzhavan Express", 16184, "10:30", "13:00", 3},
        {6, "10/05/2024", "MS", "KMU", "Kumbakonam Express", 16182, "10:30", "13:00", 2}
    };

    int num_trains = sizeof(trains) / sizeof(trains[0]);

    // Display available trains
    printf(BLUE "========= Welcome to Indian Railways =========\n" RESET);
    printf(YELLOW "Attractions: Enjoy your train journey!\n" RESET);
    displayAvailableTrains(trains, num_trains);

    // Prompt user to select a train
    int choice;
    printf("Select a train (1, 2, 3 etc.): ");
    scanf("%d", &choice);

    // Validate user input
    if (choice < 1 || choice > num_trains) {
        printf("Invalid choice. Please select a valid train.\n");
        return 1;
    }

    struct Passenger passengers[MAX_TICKETS];
    int num_tickets = 0;

    // Perform booking
    bookTicket(&trains[choice - 1], passengers, &num_tickets);

    // Print receipt
    printReceipt(&trains[choice - 1], passengers, num_tickets);

    return 0;
}
