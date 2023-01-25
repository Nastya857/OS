#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/pci.h>

struct my_pci_dev {
    unsigned short device;
    unsigned short vendor;
    unsigned int devfn;
    unsigned int pin;
    unsigned int class;
    unsigned int revision;
    int cfg_size;
};

SYSCALL_DEFINE3(pci_dev,unsigned short, device_id, unsigned short, vendor_id, struct my_pci_dev*, buf){

struct pci_dev* dev = NULL;

dev = pci_get_device(vendor_id, device_id, dev);

struct my_pci_dev* info = kmalloc(sizeof(struct my_pci_dev), GFP_KERNEL);

if (!dev){
printk(KERN_INFO "No pci device with such parameters(\n");
} else {

printk(KERN_INFO "PCI device name: %s\n", dev->dev.init_name);
printk(KERN_INFO "PCI device id: %hu\n", dev->device);
printk(KERN_INFO "PCI vendor id: %hu\n", dev->vendor);
printk(KERN_INFO "Function index: %u\n", dev->devfn);
printk(KERN_INFO "Interrupt pin: %u\n", dev->pin);
printk(KERN_INFO "Class: %u\n", dev->class);
printk(KERN_INFO "Revision: %u\n", dev->revision);
printk(KERN_INFO "Config size: %d\n", dev->cfg_size);

info -> device = dev->device;
info -> vendor = dev->vendor;
info -> devfn = dev->devfn;
info -> pin = dev->pin;
info -> class = dev->class;
info -> revision = dev->revision;
info -> cfg_size = dev->cfg_size;


copy_to_user(buf, info, sizeof(struct my_pci_dev));
}

kfree(info);

return 0;
}
