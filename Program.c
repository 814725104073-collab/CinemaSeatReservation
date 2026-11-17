
#include <stdio.h>
#include <pthread.h>

#define TOTAL_SEATS 10

int seats[TOTAL_SEATS] = {0};

pthread_mutex_t lock;

void displaySeats()
{
    int i;

    printf("\nBooked Seats: ");
    for(i = 0; i < TOTAL_SEATS; i++)
    {
        if(seats[i] == 1)
            printf("%d ", i + 1);
    }

    printf("\nAvailable Seats: ");
    for(i = 0; i < TOTAL_SEATS; i++)
    {
        if(seats[i] == 0)
            printf("%d ", i + 1);
    }
    printf("\n");
}

void* bookSeat(void* arg)
{
    int seat = *(int*)arg;

    pthread_mutex_lock(&lock);

    printf("\nUser requesting Seat %d\n", seat);

    if(seats[seat - 1] == 0)
    {
        seats[seat - 1] = 1;
        printf("Seat %d booked successfully!\n", seat);
    }
    else
    {
        printf("Seat %d is already booked!\n", seat);
    }

    displaySeats();

    pthread_mutex_unlock(&lock);

    return NULL;
}

int main()
{
    pthread_t t1, t2;
    int s1 = 3, s2 = 3;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, bookSeat, &s1);
    pthread_create(&t2, NULL, bookSeat, &s2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}
