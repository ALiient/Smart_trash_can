#ifndef __HC_SR04__
#define __HC_SR04__
#include <rtdevice.h>
#include <rtthread.h>
#include <rthw.h>
#include <board.h>
#define Trig_PIN	GET_PIN(G, 3)
#define	Echo_PIN	GET_PIN(E, 9)
struct rt_sr04_ops;
struct rt_sr04_device
{
    struct rt_device parent;
    const struct rt_sr04_ops *ops;
};
typedef struct rt_sr04_device rt_sr04_t;

struct rt_sr04_ops
{
    rt_err_t (*init)(rt_sr04_t *sr);
    rt_size_t (*read) (rt_sr04_t *sr);
};

rt_err_t rt_hw_sr04_register(rt_sr04_t *sr,
                                 const char    *name,
                                 rt_uint32_t    flag,
                                 void          *data);

static struct rt_timer timer1;
static rt_uint8_t flag_overtime=0;
#endif
