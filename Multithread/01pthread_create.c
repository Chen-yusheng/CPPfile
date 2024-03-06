#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void* callback(void * arg)
{
    for(int i = 0; i<5;i++)
    {
        printf("子线程: i = %d\n",i);
    }
    printf("子线程：%ld\n",pthread_self());  //pthread_self 获取线程id
    return NULL;
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, callback, NULL);
    for(int i = 0; i<5;i++)
    {
        printf("主线程: i = %d\n",i);
    }
    printf("主线程：%ld\n",pthread_self());
    sleep(3);
    return 0;
}