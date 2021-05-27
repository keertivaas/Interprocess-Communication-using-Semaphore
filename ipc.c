#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Buffer_Size 10
typedef int eletype;
eletype Buffer[Buffer_Size];
static int in = 0, out = 0;
static int itemid;
static int rand_count = 0;
static int S = 0; //Semaphore variable
int wait()
{

    if (S <= 0)
    {
        printf("Buffer is empty. Nothing to consume.\n");
        return (1);
    }
    else
    {
        S--;
        return 0;
    }
}
int signal()
{
    if (S > 10)
    {
        printf("\nBuffer size is full..");
        return 1;
    }
    else
    {
        S++;
        return 0;
    }
}
int Producer(eletype item)
{
    if (signal() == 0)
    {
        Buffer[in] = item;
        in = (in + 1) % Buffer_Size;
        printf("Producer produced with value : %d\n", item);
    }
    return 0;
}
eletype Consumer()
{
    eletype item;
    if (wait() == 1)
    {
        return (-32767);
    }
    else
    {
        item = Buffer[out];

        out = (out + 1) % Buffer_Size;
        return item;
    }
}
int main()
{
    int data[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int choice;
    eletype item1;
    int l = 0;
    int i = 1;
    srand(time(0));
    while (i <= 10) // We execute it 10 times
    {
        choice = rand() % 10000;
        if (choice % 2 == 0)
        {
            printf("\n%d. Producer : \n", i);
            item1 = data[l++];
            Producer(item1);
        }
        else
        {

            printf("\n%d. Consumer : \n", i);
            item1 = Consumer();
            if (item1 != -32767) // We can only return int so we take the highest magnitude negative integer value as NULL
                    printf("Data in the item : %d\n", item1);
        }
        i++;
    }
    return 0;
}