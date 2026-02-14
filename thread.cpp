#include <stdio.h>
#include<p.thread>
void*thread_task(void*args)
{
    printf("Hello from thread!");
    return NULL;
}
int main()
{
    pthread_t t1;
   int value = 45;
   pthread_create(&t1,NULL, thread_task &values);
    pthread_JOIN(t1,NULL);
    printf("Thread has finished execution!\n");
    return 0;
}