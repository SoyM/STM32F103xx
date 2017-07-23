# STM32F103xx
基于STM32F103C8T6（ARM Cortex-M3内核）开发的项目，开发工具为keil uvision5和vs2017.
## 项目结构
### USER
* **test.c** -主文件
### SYSTEM
|文件夹|功能|
|---|:---|
|**delay**|     延时函数文件|
|**sys**|       系统定义及基本功能函数文件|
|**usart**| 串口调试函数文件|
### HARDWARE
文件夹|功能
---|:---
**ADC** | 电池电压检测
**CONTROL** | 中断控制文件
**DataScope_DP** | MiniBalance上位机通讯
**DHT11** | 温湿度模块（数据口-PB12）
**DMP** | MPU6050 DMP文件
**ENCODER** | 编码功能相关文件
**EXTI** | 外部中断控制文件
**filter** | 滤波文件
**HC_SR04** | HC_SR04超声波测距（ECHO-PB0，TRIG-PB1）
**IIC**| IIC相关文件
**KEY**| 按键控制文件
**LED**| LED控制文件（PA8）
**MOTIR** | 电机接口初始化
**MPU6050**| MPU6050控制文件
**show** | OLED显示模块
**STMFLASH** | FLASH操作
**TIMER** | 定时器初始化
**USART2** | USART2模块
### OBJ
None
