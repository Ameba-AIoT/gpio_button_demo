#ifndef _GPIO_BUTTON_DEMO_H_
#define _GPIO_BUTTON_DEMO_H_

#include "ameba_soc.h"
// #include "ameba_gpio.h"
#include "os_wrapper.h"
#include <stdio.h>
#include "platform_autoconf.h"


//定义三个gpio对应的evb pin idex
#define LED1_PIN _PA_14 //Green
#define LED2_PIN _PA_15 //Red
#define LED3_PIN _PA_16 //Blue

//定义一个按钮，实现对LED的手动控制
#define BUTTON_PIN _PA_30

void gpio_led_init(void);
void gpio_led_toggle(void);
void gpio_button_init(void);
bool button_pressed(void);

#endif
