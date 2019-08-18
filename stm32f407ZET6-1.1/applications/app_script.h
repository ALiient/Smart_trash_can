

#ifndef __APP_SCRIPT_H
#define __APP_SCRIPT_H

#include <rtthread.h> 
#include <rtdevice.h> 
#include <dfs.h>
#include <dfs_file.h>
#include <dfs_fs.h>
#include <dfs_posix.h>
#include <rtconfig.h>
#include "app_dev.h"



void rt_directory_check(const char *name);

void sw18_thread_entry(void *parameter);
void sg90_thread_entry(void *parameter);
void hx711_thread_entry(void *parameter);
void led_thread_entry(void *parameter);
void hcsr04_thread_entry(void *parameter);

#endif
