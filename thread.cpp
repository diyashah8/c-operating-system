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
   
    
    return 0;
}