#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

/*
5个生产者，5个消费者
*/
pthread_cond_t cond;
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
        pthread_mutex_lock(&mutex);
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->number = rand() % 1000;
        newNode->next = head;
        head = newNode;
        printf("producer,id:%ld, number:%d\n", pthread_self(), newNode->number);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
        sleep(rand() % 3);
    }
    return NULL;
}

//消费者
void * consumer(void * arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        while(head == NULL)
        {
            //没有东西消费，消费者线程阻塞，阻塞后会自动释放互斥锁
            pthread_cond_wait(&cond,&mutex);
        }
        struct Node * node = head;
        printf("consumer,id:%ld, number:%d\n",pthread_self(),node->number);
        if(head) head = head->next;
        free(node);
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3);
    }

    return NULL;
}

int main()
{
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);

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
    pthread_cond_destroy(&cond);
    return 0;
}