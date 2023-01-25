#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/pid.h>

struct my_vm_area {
    unsigned long size;
    unsigned long offset;
    unsigned long rb_subtree_gap;
    char flag_read;
    char flag_write;
    char flag_exec;
    char flag_mayshare;
};

SYSCALL_DEFINE2(vm_area, int, pid_input, struct my_vm_area*, buf)
{

struct task_struct* task = NULL;
struct pid *pid_struct = find_get_pid(pid_input);
task = pid_task(pid_struct,PIDTYPE_PID);

struct my_vm_area* info = kmalloc(sizeof(struct my_vm_area), GFP_KERNEL);

if (task == NULL){

printk(KERN_INFO "No task with such pid\n");

}else {

if (task->mm){

char flag_read = (task->mm->mmap->vm_flags & VM_READ) ? 'r' : '-';
char flag_write = (task->mm->mmap->vm_flags & VM_WRITE) ? 'w' : '-';
char flag_exec = (task->mm->mmap->vm_flags & VM_EXEC) ? 'x' : '-';
char flag_share = (task->mm->mmap->vm_flags & VM_MAYSHARE) ? 's' : 'p';

printk(KERN_INFO "vm_area_struct info:\n");
printk(KERN_INFO "size: %lu\n", task->mm->mmap->vm_end - task->mm->mmap->vm_start);
printk(KERN_INFO "offset: %lu\n", task->mm->mmap->vm_pgoff);
printk(KERN_INFO "rb_subtree_gap: %lu\n", task->mm->mmap->rb_subtree_gap);
printk(KERN_INFO "read_flag: %c\n", flag_read);
printk(KERN_INFO "write_flag: %c\n", flag_write);
printk(KERN_INFO "exec_flag: %c\n", flag_exec);
printk(KERN_INFO "share_flag: %c\n", flag_share);

info->size = task->mm->mmap->vm_end - task->mm->mmap->vm_start;
info->offset = task->mm->mmap->vm_pgoff;
info->rb_subtree_gap = task->mm->mmap->rb_subtree_gap;
info->flag_read = flag_read;
info->flag_write = flag_write;
info->flag_exec = flag_exec;
info->flag_mayshare = flag_share;

}else{
printk(KERN_INFO "vm_area_struct is not valid\n");
}

copy_to_user(buf, info, sizeof (struct my_vm_area));

kfree(info);
}

return 0;
}