#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

/*
5个生产者，5个消费者
*/
// 生产者信号量
sem_t semp;
// 消费者信号量
sem_t semc;

pthread_mutex_t mutex;

struct Node
{
    int number;
    struct Node *next;
};

struct Node *head = NULL;

// 生产者
void *producer(void *arg)
{
    while (1)
    {
        sem_wait(&semp);
        pthread_mutex_lock(&mutex);  //互斥锁的操作必须在信号量下面
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->number = rand() % 1000;
        newNode->next = head;
        head = newNode;
        printf("producer,id:%ld, number:%d\n", pthread_self(), newNode->number);
        pthread_mutex_unlock(&mutex);
        sem_post(&semc);
        sleep(rand() % 3);
    }
    return NULL;
}

// 消费者
void *consumer(void *arg)
{
    while (1)
    {
        sem_wait(&semc);
        pthread_mutex_lock(&mutex);
        struct Node *node = head;
        printf("consumer,id:%ld, number:%d\n", pthread_self(), node->number);
        if (head)
            head = head->next;
        free(node);
        pthread_mutex_unlock(&mutex);
        sem_post(&semp);
        sleep(rand() % 3);
    }

    return NULL;
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    // 生产者
    sem_init(&semp, 0, 5);
    // 消费者 -> 初始化为0
    sem_init(&semc, 0, 0);

    // 线程创建
    pthread_t t1[5], t2[5];
    for (int i = 0; i < 5; ++i)
    {
        pthread_create(&t1[i], NULL, producer, NULL);
    }
    for (int i = 0; i < 5; ++i)
    {
        pthread_create(&t2[i], NULL, consumer, NULL);
    }

    // 线程资源释放
    for (int i = 0; i < 5; ++i)
    {
        pthread_join(t1[i], NULL);
        pthread_join(t2[i], NULL);
    }

    pthread_cond_destroy(&mutex);
    sem_destroy(&semp);
    sem_destroy(&semc);

    return 0;
}