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
    
    printf("主线程：%ld\n",pthread_self());
    pthread_exit(NULL);  //主线程退出，不释放虚拟地址空间等资源，不影响子线程继续执行
                        //不调用该方法，主线程退出，释放虚拟地址空间等资源，所有子线程全部结束
    return 0;
}