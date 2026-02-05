#include "gpio_button_demo.h"


// @brief  GPIO Init Structure Definition
  
// typedef struct {
// 	u32 GPIO_Mode;			/*!< Specifies the operating mode for the selected pins.
// 								This parameter can be a value of @ref GPIO_Mode */

// 	u32 GPIO_PuPd;			/*!< Specifies the operating Pull-up/Pull down for the selected pins.
// 								This parameter can be a value of @ref GPIO_Pull_Type */

// 	u32 GPIO_ITTrigger;		/*!< Specifies interrupt mode is level or edge trigger
// 								This parameter can be a value of @ref GPIO_INT_Trigger_Type */

// 	u32 GPIO_ITPolarity;	/*!< Specifies interrupt mode is high or low active trigger
// 								This parameter can be a value of @ref GPIO_INT_Polarity_Type */

// 	u32 GPIO_ITDebounce;	/*!< Specifies enable or disable de-bounce for interrupt
// 								This parameter can be a value of @ref GPIO_INT_Debounce_Type*/

// 	u32 GPIO_Pin;			/*!< Specifies the selected pins.
// 								This parameter contains two parts: Pin[7:5]: port number; Pin[4:0]: pin number */
// } GPIO_InitTypeDef; 
uint press_cnt = 0;
bool is_pressed_temp = false;

void gpio_led_init()
{    
    //定义三个gpio给LED使用
    GPIO_InitTypeDef led1_gpio;
    GPIO_InitTypeDef led2_gpio;
    GPIO_InitTypeDef led3_gpio;

    //初始化LED 对应的GPIO io
    led1_gpio.GPIO_Pin = LED1_PIN;
    led2_gpio.GPIO_Pin = LED2_PIN;
    led3_gpio.GPIO_Pin = LED3_PIN;

    //GPIO mode == out
    led1_gpio.GPIO_Mode = GPIO_Mode_OUT;
    led2_gpio.GPIO_Mode = GPIO_Mode_OUT;
    led3_gpio.GPIO_Mode = GPIO_Mode_OUT;

    //GPIO init
    GPIO_Init(&led1_gpio); 
    GPIO_Init(&led2_gpio); 
    GPIO_Init(&led3_gpio); 
   
    printf("gpio_led_setup ready!\r\n");
    //LED 全部亮一次后再全灭
    GPIO_WriteBit(LED1_PIN, 1);
     rtos_time_delay_ms(1000);
    GPIO_WriteBit(LED2_PIN, 1);
     rtos_time_delay_ms(1000);
    GPIO_WriteBit(LED3_PIN, 1);
    rtos_time_delay_ms(1000);
    GPIO_WriteBit(LED1_PIN, 0);
    GPIO_WriteBit(LED2_PIN, 0);
    GPIO_WriteBit(LED3_PIN, 0); 
    return;
}

void gpio_button_init()
{
    GPIO_InitTypeDef button_gpio;
    button_gpio.GPIO_Pin = BUTTON_PIN;
    button_gpio.GPIO_Mode = GPIO_Mode_IN;
    button_gpio.GPIO_PuPd = GPIO_PuPd_UP;//初始化为高电平
    GPIO_Init(&button_gpio);
    printf("\r\n ==>Read GPIO: %lu \n", GPIO_ReadDataBit(button_gpio.GPIO_Pin));
    return;
}

bool button_pressed()
{   
    //bit反转，表示button被按下    
    if (! GPIO_ReadDataBit(BUTTON_PIN))
    {
        if (! is_pressed_temp)
        {
            is_pressed_temp = true;
            press_cnt ++;
            // printf("==>Read GPIO: %lu \n", GPIO_ReadDataBit(BUTTON_PIN));
            //按键按下，按键值=0，LED全亮，跳出LED toggle           
            printf("==>Button%lu pressed_count = %d,all LEDs turn on!\r\n", (uint32_t)BUTTON_PIN, press_cnt);            
            return is_pressed_temp;
        }
        else
        {
             printf("==>Button%lu is pressed and not released!\r\n", (uint32_t)BUTTON_PIN); 
             return is_pressed_temp;   
        }
             
    }
    else
    {
        printf("==>Read GPIO: %lu \n", GPIO_ReadDataBit(BUTTON_PIN));
        is_pressed_temp = false;
        return is_pressed_temp;
    }       
}

void gpio_led_toggle()
{    
    uint i = 0;
    // int press_cnt = 0;
    while (1)
    {        
        if (button_pressed())
        {  
            GPIO_WriteBit(LED1_PIN, 1);
            GPIO_WriteBit(LED2_PIN, 1);
            GPIO_WriteBit(LED3_PIN, 1);           
            rtos_time_delay_ms(2000);
            continue;
        }
         //led toggle，间隔1s切换一次gpio
        GPIO_WriteBit(LED1_PIN, 1);
        rtos_time_delay_ms(200);

        GPIO_WriteBit(LED1_PIN, 0);
        GPIO_WriteBit(LED2_PIN, 1);
        rtos_time_delay_ms(200);

        GPIO_WriteBit(LED2_PIN, 0);
        GPIO_WriteBit(LED3_PIN, 1);
        rtos_time_delay_ms(200);

        GPIO_WriteBit(LED3_PIN, 0);
        printf("==> LED toggle count:%d\r\n", ++i);   
    } 
    rtos_task_delete(NULL);
}