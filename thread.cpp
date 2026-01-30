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
   intvalue = 45;
   pthread_create(&t1, NULL, thread_task &value);
    
    return 0;
}