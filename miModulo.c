#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h> /* for put_user */

int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static int encriptarCesar(void);

#define SUCCESS 0
#define DEVICE_NAME "UNGS"
#define BUF_LEN 80

/*
 * Global variables are declared as static, so are global within the file.
 */

static int Major;
static int Device_Open = 0;
static char msg[BUF_LEN];
static char *msg_ptr;

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release};

int init_module(void)
{ /* Constructor */
  //Registro el modulo con un mayor number
  Major = register_chrdev(0, DEVICE_NAME, &fops);
  if (Major < 0)
  {
    printk(KERN_ALERT "Fallo el registro del char device con %d\n", Major);
    return Major;
  }

  printk(KERN_INFO "Tengo major number %d.Hablarle al driver ", Major);
  printk(KERN_INFO ", crear un dev_file con \n");
  printk(KERN_INFO "sudo rm /dev/%s\n", DEVICE_NAME);
  printk(KERN_INFO "sudo mknod /dev/%s c %d 0\n", DEVICE_NAME, Major);
  printk(KERN_INFO "sudo chmod 666 /dev/%s\n", DEVICE_NAME);
  printk(KERN_INFO "Probá varios minor numbers. Probar cat y echo\n");
  printk(KERN_INFO "al device file.\n");
  printk(KERN_INFO "Eliminar el /dev y el modulo al termina.\n");

  return 0;
}
void cleanup_module(void)
{
  unregister_chrdev(Major, DEVICE_NAME);
  printk(KERN_INFO "UNGS : Driver desregistrado\n");
}

static int device_open(struct inode *inode, struct file *filp)
{
  if (Device_Open)
    return -EBUSY;

  try_module_get(THIS_MODULE);

  return SUCCESS;
}

static int device_release(struct inode *inode, struct file *filp)
{
  module_put(THIS_MODULE);
  return SUCCESS;
}

//cat /dev/UNGS -> Lo agarra el driver -> Lo copia a memoria de usuario
static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset)
{
  int bytes_read = 0;
  if (*msg_ptr == 0)
    return 0;

  while (length && *msg_ptr)
  {
    put_user(*(msg_ptr++), buffer++);
    length--;
    bytes_read++;
  }

  return bytes_read;
}

// Write
// echo 'Hola chardev' -> Buffer -> Lo agarra el driver -> Lo consume desde el Buffer, copiandolo a memoria de Kernel
// -> Tengo que devolver, hasta que posicion del archivo escribi.

static ssize_t device_write(struct file *filp, const char *tmp, size_t length, loff_t *offset)
{
  int i;
  for (i = 0; i < BUF_LEN; i++)
  {
    get_user(msg[i], tmp + i);
  }
  
  encriptarCesar();

  msg_ptr = msg;

  return i;
}
//Idea del algoritmo en https://www.geeksforgeeks.org/caesar-cipher-in-cryptography/
static int encriptarCesar(void){
    int s = 3;
    int i;
    for(i=0;i<BUF_LEN;i++){ 
      if ((msg[i])>=65 && (msg[i])<=90 ){
        msg[i] = (msg[i]+s-65)%26 +65; 
      }
      else{
          msg[i] = (msg[i]+s-97)%26 +97; 
      }
    } 
  return 0;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("UNGS");
MODULE_DESCRIPTION("Un primer driver");
