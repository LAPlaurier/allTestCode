// valgrind 
// --tool=memcheck 检查内存问题
// --tool=helgrind 检查多线程竞争问题

// 数组越界、内存泄漏
// valgrind --tool=memcheck --leck-check=full ./testValgrind
// ==> Invalid write of size 4
// ==> 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
/*
#include <stdlib.h>

void f(void) {
   int* x = new int[10];
   x[10] = 0;        
}

int main(void) {
   f();
   return 0;
}
*/


// 内存重复释放
// valgrind --tool=memcheck --leck-check=full ./testValgrind
// ==> Invalid free() / delete / delete[] / realloc()

/*
#include <stdio.h>
  
int main(int argc, char **argv) {

    char *p = new char;

    *p = 'a';

    char c = *p; // 地址加1

    printf("[%c]\n",c);

    delete p;
    delete p;// 内存多次释放
    delete p;// 内存多次释放

    return 0;
}
*/


// 内存释放后读写
// # --leak-check=full 所有泄露检查
// valgrind --tool=memcheck --leak-check=full ./testValgrind
// ==> Invalid read of size 1
/*
#include <stdio.h>
 
int main(int argc, char **argv) {

    char *p = new char;

    *p = 'a';

    char c = *p;

    printf("[%c]\n",c);

    delete p; // 释放

    c = *p; //取值 读

    return 0;
}
*/


// 无效读写
// valgrind --tool=memcheck --leak-check=full ./testValgrind
// Invalid read of size 1
/*
#include <stdio.h>
  
int main(int argc, char **argv) {

    char *p = new char;

    *p = 'a';

    char c = *(p+1); // 地址加1 无效读

    printf("[%c]\n",c);

    delete p; // 释放
    
    return 0;
}
*/


// 多线程数据竞争
// valgrind --tool=helgrind ./testValgrind
// ==> Possible data race during read of size 4 at 0x40403C by thread #1
// ==4037== Locks held: none
/*
#include <pthread.h>

int var = 0;

void* child_fn ( void* arg ) {
   var++;
   return NULL;
}

int main ( void ) {
   pthread_t child;
   pthread_create(&child, NULL, child_fn, NULL);
   var++;
   pthread_join(child, NULL);
   return 0;
}
*/


// 不正确的匹配
// valgrind --tool=memcheck --leak-check=full ./testValgrind
// ==> Mismatched free() / delete / delete []
#include <iostream>
int main() {
    int *a = new int(10);
    free(a);
    return 0;
}