#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

// 不做线程同步

#define MAX 50

// 全部变量
int number;
pthread_mutex_t mutex;

void *funcA_num(void *arg)
{
    for (int i = 0; i < MAX; i++)
    {
        pthread_mutex_lock(&mutex); // 加锁
        int cur = number;
        cur++;
        usleep(1000);
        number = cur;
        printf("Thread A, id = %lu, number = %d\n", pthread_self(), number);
        pthread_mutex_unlock(&mutex); // 解锁
    }
    return NULL;
}

void *funcB_num(void *arg)
{
    for (int i = 0; i < MAX; i++)
    {
        pthread_mutex_lock(&mutex); // 加锁
        int cur = number;
        cur++;
        number = cur;
        printf("Thread B, id = %lu, number = %d\n", pthread_self(), number);
        pthread_mutex_unlock(&mutex); // 解锁
        usleep(1000);                   // 最小粒度加解锁，因此不包含
    }
    return NULL;
}

int main()
{
    pthread_t p1, p2;
    pthread_mutex_init(&mutex, NULL); // 初始化互斥锁资源

    // 创建两个线程
    pthread_create(&p1, NULL, funcA_num, NULL);
    pthread_create(&p2, NULL, funcB_num, NULL);

    // 阻塞，回收资源
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    pthread_mutex_destroy(&mutex); // 销毁互斥锁资源
}