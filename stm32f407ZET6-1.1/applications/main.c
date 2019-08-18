/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 * 2018-11-19     flybreak     add stm32f407-atk-explorer bsp
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "app_script.h"
#include "application_init.h"


int main(void)
{
	
	rt_apps_init();			// all apps_init
	
}


/* 
	sw18.h中的#define SW18_PIN GET_PIN(A,6)	
			换成了#define SW18_PIN GET_PIN(A,5)	
*/



