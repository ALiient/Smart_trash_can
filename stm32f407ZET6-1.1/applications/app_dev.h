

#ifndef __APP_DEV_H
#define __APP_DEV_H

#include <rtthread.h> 
#include <rtdevice.h>
#include <dfs.h>
#include <dfs_file.h>
#include <dfs_fs.h>
#include <dfs_posix.h>
#include <rtconfig.h>
#include "app_script.h"
#include "sg90.h"
#include "HX711.h"
#include "sw18.h"
#include "usart.h"
#include "HC_SR04.h"


/*		app_device_name		*/
#define SW18_DEVICE_NAME	"sw18"			//	Vibration sensor
#define SG90_DEVICE_NAME    "sg90"			//	Steering gear
#define SAMPLE_UART_NAME    "uart1"
#define HX711_DEVICE_NAME 	"hx711_1"
#define SR04_DEVICE_NAME 	"sr04"


/*		rtc_data		*/
#define APP_YEAR 2019
#define APP_MON  7
#define APP_DAY  9
#define APP_HH   7
#define APP_MM   7
#define APP_SS   7




extern rt_device_t hx711;
extern rt_device_t serial;

extern rt_device_t sr04;


extern rt_sem_t sem;

void app_dev_init(void);
void rt_directory_init(void);



#endif
