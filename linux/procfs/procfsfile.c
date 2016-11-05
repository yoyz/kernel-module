/**
 *  procfs2.c -  create a "file" in /proc
 *
 */

#include <linux/module.h>	/* Specifically, a module */
#include <linux/kernel.h>	/* We're doing kernel work */
#include <linux/proc_fs.h>	/* Necessary because we use the proc fs */
#include <asm/uaccess.h>	/* for copy_from_user */

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/seq_file.h>



#define PROCFS_MAX_SIZE		1024*1024
#define PROCFS_NAME 		"buffer1MiB"

/**
 * The buffer used to store character for this module
 */
static char procfs_buffer[PROCFS_MAX_SIZE];

/**
 * The size of the buffer
 */
static unsigned long procfs_buffer_size = 0;


static ssize_t procfile_read(struct file * file, char __user * buf, size_t count, loff_t * offset)
{
  int ret;
  printk(KERN_INFO "procfile_read (/proc/%s) called\n", PROCFS_NAME);
  if (count<PROCFS_MAX_SIZE)
    {
      memcpy(buf,procfs_buffer,count);
      ret=count;
    }
  else
    {
      memcpy(buf,procfs_buffer,PROCFS_MAX_SIZE);
      ret=PROCFS_MAX_SIZE;
    }

  
  return ret;
}

	


static ssize_t procfile_write(struct file * file, const char __user * buf, size_t count, loff_t * offset)
{
  printk(KERN_INFO "procfile_write (/proc/%s) called\n", PROCFS_NAME);
  /* get buffer size */
  int procfs_buffer_size = count;
  if (procfs_buffer_size > PROCFS_MAX_SIZE ) 
    {
      procfs_buffer_size = PROCFS_MAX_SIZE;
    }
	
  /* write data to the buffer */
  if ( copy_from_user(procfs_buffer, buf, procfs_buffer_size) ) 
    {
      return -EFAULT;
    }
  
  return procfs_buffer_size;
}



static int hz_show(struct seq_file *m, void *v)
{
  return 0;
}


static int myprocfile_open(struct inode *inode, struct file *file)
{
  return single_open(file, hz_show, NULL);
}

static const struct file_operations procfile_fops = {
  .owner      = THIS_MODULE,
  .open       = myprocfile_open,
  .release    = single_release,
  .read       = procfile_read,
  .write      = procfile_write,
};

int init_module()
{
  proc_create(PROCFS_NAME, 0, NULL, &procfile_fops);
  printk(KERN_INFO "/proc/%s created\n", &PROCFS_NAME);	
  return 0;	/* everything is ok */
}


void cleanup_module()
{
  remove_proc_entry(PROCFS_NAME,NULL);
  printk(KERN_INFO "/proc/%s removed\n", PROCFS_NAME);
}
