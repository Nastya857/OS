#include <linux/kernel.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define __NR_vm_area 449

struct my_vm_area {
    unsigned long size;
    unsigned long offset;
    unsigned long rb_subtree_gap;
    char flag_read;
    char flag_write;
    char flag_exec;
    char flag_mayshare;
};


int main(int argc, char *argv[])
{

    int pid;
    long int ret_code = 0;
    bool is_pid = false;

    if (sscanf(argv[1], "%d", &pid)) is_pid = true;

    struct my_vm_area* buf = malloc(sizeof(struct my_vm_area));

    if (is_pid){
        ret_code = syscall(__NR_vm_area, pid, buf);

        if (ret_code == 0){
            printf("\nvm_area_struct info:\n");
            printf("\tsize: %lu\n", buf -> size);
            printf("\toffset: %lu\n", buf -> offset);
            printf("\trb_subtree_gap: %lu\n", buf -> rb_subtree_gap);
            printf("\tflags = %c%c%c%c\n", buf->flag_read, buf->flag_write,
                   buf->flag_exec, buf->flag_mayshare);
        } else {
            printf("System call vm_area error occured!");
        }

    } else {
        printf("Wrong argument\n");
    }

    free(buf);

    return 0;
}