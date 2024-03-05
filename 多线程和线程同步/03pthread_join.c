#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

struct Test
{
    int num;
    int age;
};

void *callback(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        printf("子线程: i = %d\n", i);
    }
    printf("子线程：%ld\n", pthread_self()); // pthread_self 获取线程id

    // static struct Test t;
    struct Test * t= (struct Test *)arg;
    t->num = 100;
    t->age = 66;
    pthread_exit(t); // 线程退出，并传出一个结构体t
    return NULL;
}

int main()
{
    struct Test t;
    pthread_t tid;
    pthread_create(&tid, NULL, callback, &t);  //子线程使用主线程栈空间中的结构体数据t

    printf("主线程：%ld\n", pthread_self());

    void *ptr;
    pthread_join(tid, &ptr); // 主线程阻塞，并用ptr接收子线程传出的数据，不想接收可以用NULL
                                //每调用一次只能回收一个子线程资源
    struct Test *pt = (struct Test *)ptr;
    // printf("num: %d, age: %d\n", pt->num, pt->age);
    printf("num: %d, age: %d\n", t.num, t.age);

    return 0;
}