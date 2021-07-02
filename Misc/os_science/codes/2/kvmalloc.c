#include <linux/module.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

MODULE_LICENSE("GPL");

unsigned char *kmallocmem1;
unsigned char *kmallocmem2;
unsigned char *vmallocmem1;
unsigned char *vmallocmem2;
unsigned char *vmallocmem3;

static int __init mem_module_init(void)
{
    printk("Start kmalloc!\n");

    kmallocmem1 = (unsigned char *)kmalloc(1024, GFP_KERNEL);
    if (kmallocmem1 != NULL)
    {
        printk(KERN_ALERT "kmallocmem1 1kb addr = %lx\n", (unsigned long)kmallocmem1);
    }
    else
    {
        printk("Failed to allocate kmallocmem1!\n");
    }

    kmallocmem2 = (unsigned char *)kmalloc(8192, GFP_KERNEL);
    if (kmallocmem2 != NULL)
    {
        printk(KERN_ALERT "kmallocmem2 8kb addr = %lx\n", (unsigned long)kmallocmem2);
    }
    else
    {
        printk("Failed to allocate kmallocmem2!\n");
    }

    // Tasks
    vmallocmem1 = (unsigned char *)vmalloc(8192);
    if (vmallocmem1 != NULL)
    {
        printk(KERN_ALERT "vmallocmem1 8kb addr = %lx\n", (unsigned long)vmallocmem1);
    }
    else
    {
        printk("Failed to allocate vmallocmem1!\n");
    }

    vmallocmem2 = (unsigned char *)vmalloc(1024 * 1024);
    if (vmallocmem2 != NULL)
    {
        printk(KERN_ALERT "vmallocmem2 1mb addr = %lx\n", (unsigned long)vmallocmem2);
    }
    else
    {
        printk("Failed to allocate vmallocmem2!\n");
    }

    vmallocmem3 = (unsigned char *)vmalloc(1024 * 1024 * 64);
    if (vmallocmem3 != NULL)
    {
        printk(KERN_ALERT "vmallocmem3 64mb addr = %lx\n", (unsigned long)vmallocmem3);
    }
    else
    {
        printk("Failed to allocate vmallocmem3!\n");
    }
    return 0;
}

static void __exit mem_module_exit(void)
{
    kfree(kmallocmem1);
    kfree(kmallocmem2);
    vfree(vmallocmem1);
    vfree(vmallocmem2);
    vfree(vmallocmem3);
    printk("Exit kmalloc!\n");
}

module_init(mem_module_init);
module_exit(mem_module_exit);
