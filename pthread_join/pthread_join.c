/* 线程join相关使用示例 */
/* 使用数学公式时编译要加 -lm 参数 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 4

void *BusyWork(void *t) /* 线程函数 */
{
    int i;
    long tid;
    double result=0.0;
    tid = (long)t;

    printf("Thread %ld starting...\n",tid);
    for (i=0; i<1000000; i++) {
        result = result + sin(i) * tan(i); /* 进行数学运算 */
    }

    printf("Thread %ld done. Result = %e\n",tid, result);

    pthread_exit((void*) t); /* 带计算结果退出 */
}

int main (int argc, char *argv[]){

    pthread_t thread[NUM_THREADS];
    int rc;
    long t;
    void *status;

    for(t=0; t<NUM_THREADS; t++) {
        printf("Main: creating thread %ld\n", t);

        rc = pthread_create(&thread[t], NULL, BusyWork, (void *)t); /* 创建线程 */

        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);

        exit(-1);
        }
    }

    for(t=0; t<NUM_THREADS; t++) {
        rc = pthread_join(thread[t], &status); /*等待线程终止，并获取返回值*/

        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }

        printf("Main: completed join with thread %ld having a status of %ld\n",t,(long)status);
    }

    printf("Main: program completed. Exiting.\n");
    
    pthread_exit(NULL);
}