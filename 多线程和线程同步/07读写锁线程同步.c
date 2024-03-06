#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


/*
读写锁是一把锁
读读不互斥
读写互斥
写写互斥
*/

// 不做线程同步

#define MAX 50

// 全部变量
int number;
pthread_rwlock_t rwlock;  


void *read_num(void *arg)
{
    for (int i = 0; i < MAX; i++)
    {
        pthread_rwlock_rdlock(&rwlock); // 加读锁
        printf("Thread read, id = %lu, number = %d\n", pthread_self(), number);
        pthread_rwlock_unlock(&rwlock); // 解锁
        usleep(rand() % 5);
    }
    return NULL;
}

void *write_num(void *arg)
{
    for (int i = 0; i < MAX; i++)
    {
        pthread_rwlock_wrlock(&rwlock); // 加写锁
        int cur = number;
        cur++;
        number = cur;
        printf("Thread B, id = %lu, number = %d\n", pthread_self(), number);
        pthread_rwlock_unlock(&rwlock); // 解锁
        usleep(1000);                   // 最小粒度加解锁，因此不包含
    }
    return NULL;
}

int main()
{
    pthread_t p1[5], p2[3];
    pthread_rwlock_init(&rwlock, NULL); // 初始化互斥锁资源

    for(int i = 0;i<5;i++)  //创建5个读线程
    {
        pthread_create(&p1[i], NULL, read_num, NULL);
    }
    for(int i = 0;i<3;i++)  //创建3个写线程
    {
        pthread_create(&p2[i], NULL, write_num, NULL);
    }

    // 阻塞，回收资源
    for(int i = 0;i<5;i++)
    {
        pthread_join(p1[i], NULL);
    }
    for(int i = 0;i<3;i++)
    {
        pthread_join(p2[i], NULL);
    }

    pthread_mutex_destroy(&rwlock); // 销毁互斥锁资源
}