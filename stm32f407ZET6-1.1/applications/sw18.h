#ifndef __SW18_H__
#define __SW18_H__
#include <rtdevice.h>
#include <rtthread.h>
#include <rthw.h>
#include <board.h>
/* Private defines -----------------------------------------------------------*/
#define SW18_PIN GET_PIN(A,5)		
#define SW18_GPIO_Port GPIOA
#define LED1_PIN    GET_PIN(A, 7)

struct rt_sw18_ops;//��Ҫ����
struct rt_sw18_device//�豸����̳�
{
    struct rt_device parent;
    const struct rt_sw18_ops *ops;
};
typedef struct rt_sw18_device rt_sw18_t;

struct rt_sw18_ops//�豸�ӿ�
{
    rt_err_t (*init)(rt_sw18_t *hx);
    rt_size_t (*read) (rt_sw18_t *hx);
		//rt_err_t  (*close)  (rt_device_t dev);��Ҫ���������ϸ�ʽ��д
    //rt_size_t (*read)   (rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
    //rt_size_t (*write)  (rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
    //rt_err_t  (*control)(rt_device_t dev, int cmd, void *args);
};
rt_err_t rt_hw_sw18_register(rt_sw18_t *hx,
                                 const char    *name,
                                 rt_uint32_t    flag,
                                 void          *data);//ע���������
extern uint8_t Detect_Shake(void);
extern unsigned long test;
#endif

