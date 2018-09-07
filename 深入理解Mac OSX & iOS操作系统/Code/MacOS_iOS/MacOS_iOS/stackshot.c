//
//  stackshot.c
//  MacOS_iOS
//
//  Created by 骆扬 on 2018/9/6.
//  Copyright © 2018年 SyncSoft. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


struct frame {
    void *retaddr;
    void *fp;
};

// 下面的宏定义和数据结构复制自osfmk/kern/debug.h
#define STACKSHOT_TASK_SNAPSHOT_MAGIC 0xdecafbad
#define STACKSHOT_THREAD_SNAPSHOT_MAGIC 0xfeedface
#define STACKSHOT_MEM_SNAPSHOT_MAGIC 0xabcddcba

struct thread_snapshot {
    uint32_t                    snapshot_magic;
    uint32_t                    nkern_frames;
    uint32_t                    nuser_frames;
    uint64_t                    wait_event;
    uint64_t                    continuation;
    uint64_t                    thread_id;
    uint64_t                    user_time;
    uint64_t                    system_time;
    uint32_t                    state;
    char                        ss_flags;
} __attribute__ ((packed));

struct task_snapshot {
    uint32_t                    snapshot_magic;
    uint32_t                    pid;
    uint32_t                    nloadinfos;
    uint64_t                    user_time_in_terminated_threads;
    uint64_t                    system_time_in_terminated_threads;
    int                         suspend_count;
    int                         task_size;          // 页面数
    int                         faults;             // 页错误次数
    int                         pageins;            // 实际页面换入次
    int                         cow_faults;         // 写时复制页错误次数
    char                        ss_flags;
    char                        p_comm[17];
} __attribute__ ((packed));

int stack_snapshot(int pid, char *tracebuf, int bufsize, int options) {
//    return kdebug_signpost(365, pid, tracebuf, bufsize, options);
    return syscall(365, pid, tracebuf, bufsize, options);
}

int dump_thread_snapshot(struct thread_snapshot *ths) {
    if (ths->snapshot_magic != STACKSHOT_THREAD_SNAPSHOT_MAGIC) {
        fprintf(stderr, "Error: Magic %u expected, Foud %un", STACKSHOT_THREAD_SNAPSHOT_MAGIC, ths->snapshot_magic);
        return 0;
    }
    
    printf("\tThread ID: 0x%llx ", ths->thread_id);
    printf("\tState: 0x%x ", ths->state);
    if (ths->wait_event) {
        printf("\tWaiting on: 0x%llx ", ths->wait_event);
    }
    if (ths->continuation) {
        printf("\tContinuation: 0x%llx ", ths->continuation);
    }
    if (ths->nkern_frames || ths->nuser_frames) {
        printf("\tFrames: %d kernel %d user\n ", ths->nkern_frames, ths->nuser_frames);
    }
    
    
    return (ths->nuser_frames + ths->nuser_frames);
}

void dump_task_snapshot(struct task_snapshot *ts) {
    if (ts->snapshot_magic != STACKSHOT_TASK_SNAPSHOT_MAGIC) {
        fprintf(stderr, "Error: Magic %u expected, Foud %un", STACKSHOT_TASK_SNAPSHOT_MAGIC, ts->snapshot_magic);
        return ;
    }
    fprintf(stdout, "PID: %d (%s)\n", ts->pid, ts->p_comm);
}

#define BUFSIZE 5000    // 足够大......

/*
int main(int argc, char **argv) {
    char buf[BUFSIZE];
    int rc = stack_snapshot(-1, buf, BUFSIZE, 100);
    struct task_snapshot *ts;
    struct thread_snapshot *ths;
    int off = 0;
    int warn = 0;
    int nframes = 0;
    
    if (rc < 0) {
        perror("stack_snapshot");
        return (-1);
    }
    
    while (off < rc) {
        // 遍历缓冲区，缓冲区里保存的是连续导出的snapshot结构体
        
        ts = (struct task_snapshot *) (buf + off);
        ths = (struct thread_snapshot *) (buf + off);
        
        switch (ts->snapshot_magic) {
            case STACKSHOT_TASK_SNAPSHOT_MAGIC:
                dump_task_snapshot(ts);
                off += (sizeof(struct task_snapshot));
                warn = 0;
                break;
                
            case STACKSHOT_THREAD_SNAPSHOT_MAGIC:
                nframes = dump_thread_snapshot(ths);
                off += (sizeof(struct thread_snapshot));
                off += 8;
                if (nframes) {
                    printf("\t\tReturn Addr\tFrame Ptr\n");
                    while (nframes) {
                        struct frame *f = (struct frame *) (buf + off);
                        printf("\t\t%p\t%p\n", f->retaddr, f->fp);
                        off += sizeof(struct frame);
                        nframes--;
                    }
                }
                warn = 0;
                break;
                
            case STACKSHOT_MEM_SNAPSHOT_MAGIC:
                printf("MEM magic - left as an exercise to the reader\n");
                break;
                
            default:
                if (!warn) {
                    warn++;
                    fprintf(stdout, "Magic %u at offset %d? Seeking to next magic\n", ts->snapshot_magic, off);
                }
                off++;;
                break;
        }
    }
}
*/







