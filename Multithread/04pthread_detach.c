
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

    pthread_detach(tid);  //子线程和主线程分离 子线程资源有内核回收
                          //线程分离主要是不由主线程回收子线程资源

    pthread_exit(NULL);  //主线程退出之后不影响子线程运行

    return 0;
}