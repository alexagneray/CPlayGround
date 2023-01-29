// obj-m := mymodule.o
// # Additionally, if spilt in multiple source files:
// # mymodule-objs := source1.o source2.o
// Then one runs the following to build the module, from the directory which contains above file:

// make -C /path/to/kernel/build M=$(pwd) modules

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

static int my_init(void)
{
    printk(KERN_INFO "Hello world\n");   
    return  0;
}
   
static void my_exit(void)
{
    printk(KERN_INFO "Good bye world\n");
    return;
}
   
module_init(my_init);
module_exit(my_exit);