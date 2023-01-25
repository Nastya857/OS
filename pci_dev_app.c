#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

#define __NR_pci_dev_info 450

struct my_pci_dev {
    unsigned short device;
    unsigned short vendor;
    unsigned int devfn;
    unsigned int pin;
    unsigned int class;
    unsigned int revision;
    int cfg_size;
};

int main(int argc, char *argv[])
{

    unsigned int vendor_id;
    unsigned int device_id;
    long int ret_code = 0;
    bool is_device = false;
    bool is_vendor = false;

    struct my_pci_dev* buf = malloc(sizeof(struct my_pci_dev));

    if (sscanf(argv[1], "%x", &vendor_id)) is_vendor = true;
    if (sscanf(argv[2], "%x", &device_id)) is_device = true;

    if (is_vendor && is_device){

        ret_code = syscall(__NR_pci_dev_info, device_id, vendor_id, buf);

        if (!ret_code){
            printf("PCI Dev Info:\n");
            printf("PCI device id: %hu\n", buf -> device);
            printf("PCI vendor id: %hu\n", buf -> vendor);
            printf("Function index: %u\n", buf -> devfn);
            printf("Interrupt pin: %u\n", buf -> pin);
            printf("Class: %u\n", buf -> class);
            printf("Revision: %u\n", buf -> revision);
            printf("Config size: %d\n", buf -> cfg_size);
        } else {
            printf("System call pci_dev error occured!\n");
        }

    } else {
        printf("Wrong argument\n");
    }

    free(buf);
    return 0;
}