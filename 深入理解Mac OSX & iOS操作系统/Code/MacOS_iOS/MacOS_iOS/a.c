//
//  a.c
//  MacOS_iOS
//
//  Created by 骆扬 on 2018/9/5.
//  Copyright © 2018年 SyncSoft. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int global_j;
const int ci = 24;

int main(int argc, char **argv) {
    int local_stack = 0;
    char *const_data = "This data is constant";
    char *tiny = malloc(32);                // 分配32字节
    char *small = malloc(2 * 1024);         // 分配 2K 字节
    char *large = malloc(1 * 1024 * 1024);  // 分配 1M 字节
    
    printf("Text is %p\n", main);
    printf("Global data is  %p\n", &global_j);
    printf("Local (Stack) is  %p\n", &local_stack);
    printf("Constant data is  %p\n", &ci);
    printf("Hardcoded string (also constant) are at  %p\n", const_data);
    printf("Tiny allocations from  %p\n", tiny);
    printf("Small allocations from  %p\n", small);
    printf("Large allocations from  %p\n", large);
    printf("Malloc (i.e. libSystem) is at  %p\n", malloc);
    

  //  sleep(100); // 为了在进程退出之前通过vmmap分析这个进程
    
    return 0;
}
