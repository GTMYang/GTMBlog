//
//  mcheck.c
//  MacOS_iOS
//
//  Created by 骆扬 on 2018/9/4.
//  Copyright © 2018年 SyncSoft. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <malloc/malloc.h> // malloc_printf()

typedef struct interpose_s {
    void *new_func;
    void *orig_func;
} interpose_t;

void *my_malloc(int size);  // 对应真实的malloc()
void my_free (void *);     // 对应真实的free()

static const interpose_t interposing_functions[] __attribute__ ((section("__DATA, __interpose"))) = {
    { (void *)my_free, (void *)free },
    { (void *)my_malloc, (void *)malloc }
};


void *my_malloc (int size) {
    // 在我们的函数中，要访问真正的malloc()函数
    
    void *returned = malloc(size);
    malloc_printf("+ %p %d\n", returned, size);
    
    return returned;
}

void my_free(void *freed) {
    malloc_printf("- %p\n", freed);
    
    free(freed);
}
