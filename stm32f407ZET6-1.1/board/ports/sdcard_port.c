/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-13     balanceTWK   add sdcard port file
 */

#include <rtthread.h>
#include "app_script.h"
#include "app_dev.h"

#ifdef BSP_USING_SDCARD

#include <dfs_elm.h>
#include <dfs_fs.h>
#include <dfs_posix.h>

#define DBG_SECTION_NAME  "app.card"
#define DBG_LEVEL DBG_INFO
#include <rtdbg.h>

void sd_mount(void *parameter)
{
    while (1)
    {
        rt_thread_mdelay(500);
        if(rt_device_find("sd0") != RT_NULL)
        {
            if (dfs_mount("sd0", "/", "elm", 0, 0) == RT_EOK)
            {
                LOG_I("sd card mount to '/'");
				rt_directory_init();			//build AVDE and MONI directory
                break;
            }
            else
            {
                LOG_E("sd card mount to '/' failed!");
            }
        }
    }
}

int stm32_sdcard_mount(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("sd_mount", sd_mount, RT_NULL,
                           1024, RT_THREAD_PRIORITY_MAX - 2, 20);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
		LOG_I("create sd_mount thread ok!\n");
    }
    else
    {
        LOG_E("create sd_mount thread err!\n");
    }
    return RT_EOK;
}
INIT_APP_EXPORT(stm32_sdcard_mount);

#endif /* BSP_USING_SDCARD */

