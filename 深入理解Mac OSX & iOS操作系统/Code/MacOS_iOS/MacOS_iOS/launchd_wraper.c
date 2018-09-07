//
//  launchd_wraper.c
//  MacOS_iOS
//
//  Created by 骆扬 on 2018/9/7.
//  Copyright © 2018年 SyncSoft. All rights reserved.
//

#include <stdio.h>
#include <sys/socket.h>
#include <launch.h>         // LaunchD相关的定义
#include <stdlib.h>         // exit之类的调用
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>      // get address info
#include <fcntl.h>      // file control


#define JOBKEY_LISTENERS "Listeners"
#define MAX_SIZE 1024
#define CMD_MAX 80

int main(int argc, char **argv) {
    launch_data_t checkinReq, checkinResp;
    launch_data_t mySocketsDict;
    launch_data_t myListeners;
    
    int fdNum;
    int fd;
    struct sockaddr sa;
    unsigned int len = sizeof(struct sockaddr);
    int fdSession;
    
    /*首先必须在launchd中登记*/
    checkinReq = launch_data_new_string(LAUNCH_KEY_CHECKIN);
    checkinResp = launch_msg(checkinReq);
    
    if (!checkinResp) {
        // 登记失败——只有当我们没有运行在其上下文中才会失效
        // 打印消息并退出
        fprintf(stderr, "This command can only be run under launchd\n");
        exit(2);
    }
    
    mySocketsDict = launch_data_dict_lookup(checkinResp, LAUNCH_JOBKEY_SOCKETS);
    
    if (!mySocketsDict) {
        fprintf(stderr, "Can't find <Sockets> Key in plist\n");
        exit(1);
    }
    
    myListeners = launch_data_dict_lookup(mySocketsDict, JOBKEY_LISTENERS);
    if (!myListeners) {
        fprintf(stderr, "Can't find <Listeners> Key inside <Sockets> in plist\n");
        exit(1);
    }
    
    fdNum = launch_data_array_get_count(myListeners);
    if (fdNum != 1) {
        fprintf(stderr, "Number of File Descriptors is %d - should be 1\n", fdNum);
        exit(1);
    }
    
    // 获得launchd的文件描述符(套接字)
    fd = launch_data_get_fd(launch_data_array_get_index(myListeners, 0));
    
    fdSession = accept(fd, &sa, &len);
    
    launch_data_free(checkinResp); // 程序要厚道
    
    // 在重定向之前打印至stderr(/var/log/system.log)
    fprintf(stderr, "Excing %s\n", argv[1]);
    
    dup2(fdSession, 0);         // 重定向stdin
    dup2(fdSession, 1);         // 重定向stdout
    dup2(fdSession, 2);         // 重定向stderr
    dup2(fdSession, 255);       // shell还有文件描述符255
    
    // 这个例子采用简单粗暴的设定——假设这个包装程序至少有两个参数
    // 第一个是要执行的程序的路径，第二个是launchd程序的参数
    execl(argv[1], argv[1], argv[2], NULL);
    
    // 运行到这里表示execl失败了
    close(fdSession);
    
    
    return (42);
}





