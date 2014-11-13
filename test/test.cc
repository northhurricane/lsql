#include "lsemaphore.h"
#include <semaphore.h>

int main(int argc, char *argv[])
{
sem_t sem;
sem_init(&sem, 0, 0);
return 0;
}
