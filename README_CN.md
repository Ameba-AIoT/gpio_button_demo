* [English Version](./README.md)

### RTL8721Dx GPIO输入（按钮）控制LED示例（FreeRTOS）

🚀 这是一个演示如何使用RTL8721Dx系列SoC进行LED控制和按钮输入的示例。

- 📎 开发板链接  [🛒 淘宝](https://item.taobao.com/item.htm?id=904981157046)   |[📦 Amazon](https://www.amazon.com/-/zh/dp/B0FB33DT2C/)
- 📄 [芯片详情](https://aiot.realmcu.com/cn/module/index.html)
- 📚 [GPIO Document](https://aiot.realmcu.com/cn/latest/rtos/peripherals/gpio/index.html)

### 功能特点

✅ 初始化GPIOs —— PA14/PA15/PA16/PA30  
✅ 初始化后，程序配置GPIO端口让LED以200ms的间隔闪烁。    
✅ 当按下一个按钮时，所有LED将会全部点亮，直到您释放按钮。

### 搭建硬件环境

1️⃣ **所需组件**
   - 3个LED
   ⚠️ 开发板上有内置LED，您可以直接观察效果。
   - 1个按钮

2️⃣ **连接导线**
   - 将一个按钮连接到 
   ` BUTTON_PIN (_PA_30)` 和 `GND`
   - 将LED分别连接到 
      - `LED1_PIN(_PA_14)//绿色`   
      - `LED2_PIN(_PA_15)//红色` 
      - `LED3_PIN(_PA_16)//蓝色` 
      - 和 `GND`

### 快速开始

1️⃣ **初始化SDK环境**
   - 设置 `env.sh` (`env.bat`) 路径：`source {sdk}/env.sh`
   - 将 `{sdk}` 替换为 [ameba-rtos SDK](https://github.com/Ameba-AIoT/ameba-rtos) 根目录的绝对路径。

2️⃣ **编译**
   ```bash
   source env.sh
   ameba.py build
   ```

3️⃣ **烧录 FLASH**
   ```bash
   ameba.py flash --p COMx --image boot.bin 0x08000000 0x8014000 --image app.bin 0x08014000 0x8200000
   ```
   ⚠️ 注意：项目目录中提供的预编译bin文件也可以用如下方式烧录：
   ```bash
   ameba.py flash --p COMx --image ../boot.bin 0x08000000 0x8014000 --image ../app.bin 0x08014000 0x8200000
   ```

> ⚠️ **bin 文件命名说明**：bin 文件名称取决于所使用的 SDK 版本。
> 最新 SDK 编译产物为 `boot.bin` + `app.bin`；
> 旧版 SDK 编译产物为 `km4_boot_all.bin` + `km0_km4_app.bin`。
> 请根据实际编译输出修改上方命令中的文件名。

4️⃣ **打开串口监视**
   -  `ameba.py monitor --port COMx --b 1500000`

5️⃣ **点击EVB RST按钮后，观察日志输出**

---

### 日志示例

```bash
日志：
15:55:05.291  ROM:[V1.1]
15:55:05.291  FLASH RATE:1, Pinmux:1
15:55:05.296  IMG1(OTA1) VALID, ret: 0
15:55:05.296  IMG1 ENTRY[f80078d:0]
15:55:05.296  [BOOT-I] KM4 BOOT REASON 0: Initial Power on
15:55:05.296  [BOOT-I] KM4 CPU CLK: 240000000 Hz
15:55:05.296  [BOOT-I] KM0 CPU CLK: 96000000 Hz
15:55:05.296  [BOOT-I] PSRAM Ctrl CLK: 240000000 Hz 
15:55:05.301  [BOOT-I] IMG1 ENTER MSP:[30009FDC]
15:55:05.301  [BOOT-I] Build Time: Jan 20 2026 16:43:53
15:55:05.301  [BOOT-I] IMG1 SECURE STATE: 1
15:55:05.306  [FLASH-I] FLASH CLK: 80000000 Hz
15:55:05.306  [FLASH-I] Flash ID: 85-20-16 (Capacity: 32M-bit)
15:55:05.306  [FLASH-I] Flash Read 4IO
15:55:05.306  [FLASH-I] FLASH HandShake[0x2 OK]
15:55:05.311  [BOOT-I] KM0 XIP IMG[0c000000:79e0]
15:55:05.311  [BOOT-I] KM0 SRAM[20068000:860]
15:55:05.311  [BOOT-I] KM0 PSRAM[0c008240:20]
15:55:05.311  [BOOT-I] KM0 ENTRY[20004d00:60]
15:55:05.311  [BOOT-I] KM4 XIP IMG[0e000000:17ca0]
15:55:05.311  [BOOT-I] KM4 SRAM[2000b000:460]
15:55:05.311  [BOOT-I] KM4 PSRAM[0e018100:20]
15:55:05.311  [BOOT-I] KM4 ENTRY[20004d80:40]
15:55:05.311  [BOOT-I] IMG2 BOOT from OTA 1, Version: 1.1 
15:55:05.311  [BOOT-I] Image2Entry @ 0xe007795 ...
15:55:05.311  [APP-I] [KM4 APP START LOCKS-I]
15:55:05.311  [APP-I KM0 ini] VTOR: t_retarg30007000et_locks, VTOR_NS:300070
15:55:05.311  00
15:55:05.311  [APP-I] VTOR: 30007000, VTOR_NS:30007000
15:55:05.311  [APP-I] IMG2 SECURE STAT[MAIN-I]E: 1
15:55:05.311   IWDG refresh on!
15:55:05.316  [MAIN-I] KM0 OS[ CSLTK-AIR]T  [C
15:55:05.316  AL4M]: delta:0 target:320 PPM: 0 PPM_Limit:30000 
15:55:05.321  [CLK-I] [CAL131K]: delta:8 target:2441 PPM: 3277 PPM_Limit:30000 
15:55:05.321  [LOCKS-I] KM4 init_retarget_locks
15:55:05.331  [APP-I] BOR arises when supply voltage decreases under 2.57V and recovers above 2.7V.
15:55:05.331  [MAIN-I] KM4 MAIN 
15:55:05.331  [VER-I] AMEBA-RTOS SDK VERSION: 1.2.0
15:55:05.331  [MAIN-I] File System Init Success 
15:55:05.331  [app_main-I] gpio_led_demo start!
15:55:05.331  gpio_led_setup ready!
15:55:08.333  [app_main-I] gpio_button_init start!
15:55:08.333  SWD PAD Port0_Pin30 is configured to funcID 
15:55:08.333   ==>Read GPIO: 1 
15:55:08.333  [MAIN-I] KM4 START SCHEDULER 
15:55:08.333  ==>Read GPIO: 1 
15:55:08.934  ==> LED toggle count:1
15:55:08.934  ==>Read GPIO: 1 
15:55:09.534  ==> LED toggle count:2
15:55:09.534  ==>Read GPIO: 1 
15:55:10.135  ==> LED toggle count:3
15:55:10.135  ==>Read GPIO: 1 
15:55:10.731  ==> LED toggle count:4
15:55:10.735  ==>Button30 pressed_count = 1,all LEDs turn on!
15:55:12.735  ==>Button30 is pressed and not released!
15:55:14.735  ==>Button30 is pressed and not released!
15:55:16.736  ==>Read GPIO: 1 
15:55:17.340  ==> LED toggle count:5
15:55:17.340  ==>Read GPIO: 1 
15:55:17.939  ==> LED toggle count:6
15:55:17.939  ==>Read GPIO: 1 
15:55:18.539  ==> LED toggle count:7
15:55:18.539  ==>Button30 pressed_count = 2,all LEDs turn on!
15:55:20.539  ==>Read GPIO: 1 
15:55:21.139  ==> LED toggle count:8
15:55:21.139  ==>Read GPIO: 1 
15:55:21.743  ==> LED toggle count:9
15:55:21.743  ==>Button30 pressed_count = 3,all LEDs turn on!
15:55:23.742  ==>Read GPIO: 1 
15:55:24.343  ==> LED toggle count:10
15:55:24.345  ==>Read GPIO: 1 
15:55:24.944  ==> LED toggle count:11
15:55:24.945  ==>Read GPIO: 1 
15:55:25.544  ==> LED toggle count:12
15:55:25.544  ==>Button30 pressed_count = 4,all LEDs turn on!
15:55:27.547  ==>Read GPIO: 1 
```