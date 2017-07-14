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
**CONTROL**| 中断控制文件
**DMP**| DMP文件
**ENCODER**| 编码功能相关文件
**EXTI**| 外部中断控制文件
**filter**| 滤波文件
**IIC**| IIC相关文件
**KEY**| 按键控制文件
**LED**| LED控制文件
**MPU6050**| MPU6050控制文件
### OBJ
None
