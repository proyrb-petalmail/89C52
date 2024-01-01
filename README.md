# 为89C52定制的模块库

## 简介

> 首先非常高兴您能对此项目感到有趣，希望可以帮助到你。这篇文章主要针对`STC89C52`及其`外围设备`编写的模块库，但是对`C51`系列的单片机也同样适用。首先我会在`如何使用`这部分告诉你如何引入想要使用的库对应的头文件，其次我会在`库详解`这部分告诉你每个库中列出的函数是如何使用的。
>
> 最后，如果你在学习和使用过程中，发现任何问题可以通过这个电子邮箱联系我：proyrb@petalmail.com

## 如何使用

> 在一个项目中如何使用这些模块库？
>
> 1. 首先将要使用的模块库对应的`.h`文件和`.c`文件加入项目目录中；
>
> 2. 在想要使用库函数的文件中加入对应的`.h`头文件，于是在该文件中就可以调用对应的`.c`文件了；
>
>    ```c
>    //其他头文件
>                         
>    #include <xxx.h>
>                         
>    //在你想要调用的位置调用库函数
>    ```

## 库详解

下列函数的声明和定义分别位于相应库的`.h`和`.c`文件中，想要深入了解模块库实现原理可以打开学习。

- **Delay**

  > ```c
  > void Delay2ms(void);
  > void Delay10ms(void);
  > ```
  > 
  > 简介：按照特定时长`延时`。
  > 
  >注意：以上函数只适用于频率为**`11.0592MHz`**的晶振。
  
- **Timer**

  > ```c
  > void Timer_Initial(const bit timer, const unsigned char high, const unsigned char low);
  > ```
  >
  > 简介：将`指定定时器`进行`初始化`操作。
  >
  > 参数：
  >
  > 1. `timer`储存的值规定为`0`或`1`，分别表示`定时器0`和`定时器1`，为此函数指定要操作的定时器；
  >
  > 2. `high`和`low`储存的值分别是一个长度共十六位的无符号二进制数（可表示0~65536）的高八位和低八位；
  >
  >    > 常用计时长度：
  >    >
  >    > | 计时长度（毫秒） | 十六位二进制数 | 高八位 | 低八位 |
  >    > | :--------------: | :------------: | :----: | :----: |
  >    > |       0.50       |     65075      | `0xFE` | `0x33` |
  >    > |       1.00       |     64614      | `0xFC` | `0x66` |
  >    > |       10.0       |     56320      | `0xDC` | `0x00` |
  >    > |       50.0       |     19456      | `0x4C` | `0x00` |
  >
  > 详细：
  >
  > 1. 首先将`high`和`low`赋值给指定定时器对应的全局变量，再将该全局变量赋值用于设置定时器计时起点；
  > 2. 接着为该定时器设置默认固定的工作模式`1`；
  > 3. 然后打开该定时器对应的分中断；
  > 4. 最后打开总中断；
  
  > ```c
  > void Timer_Control(const bit timer, const bit control);
  > ```
  >
  > 简介：控制指定定时器`开始或停止计时`。
  >
  > 参数：
  >
  > 1. `timer`储存的值规定为`0`或`1`，分别表示`定时器0`和`定时器1`，为此函数指定要操作的定时器；
  > 2. `control`储存的值规定为`0`或`1`，分别表示`停止`和`开始`计时；

  > ```c
  > void Timer_Callback(const bit timer, const void * const callback);
  > ```
  >
  > 简介：为指定定时器`配置中断时的回调函数`。
  >
  > 参数：
  >
  > 1. `timer`储存的值是指定的定时器；
  > 2. `callback`储存的值是回调函数的地址；
  >
  > 注意：配置的回调函数`callback`必须满足以下两个条件，没有返回值（即返回值类型必须是`void`），且没有参数（即`void`）。
  
- **Button**

  > ```c
  > unsigned char Button_Value(void);
  > ```
  >
  > 简介：扫描按钮并`返回键值`。
  >
  > 详细：
  >
  > 1. 当扫描到`没有任何按钮抬起`时，返回宏`BUTTON_NONE`；
  > 2. 当扫描到`按钮全部抬起`时，返回对应键值；
  >
  > 注意：按钮返回的键值是可以包含多按钮键值，以下是键值表：
  >
  > ```c
  > BUTTON_NONE 0x0F //定义无按钮组合
  > BUTTON_B1 0x0D
  > BUTTON_B2 0x0E
  > BUTTON_B3 0x0B
  > BUTTON_B4 0x07
  > BUTTON_B1_B2 0x0C
  > BUTTON_B1_B3 0x09
  > BUTTON_B1_B4 0x05
  > BUTTON_B2_B3 0x0A
  > BUTTON_B2_B4 0x06
  > BUTTON_B3_B4 0x03
  > BUTTON_B1_B2_B3 0x08
  > BUTTON_B1_B2_B4 0x04
  > BUTTON_B1_B3_B4 0x01
  > BUTTON_B2_B3_B4 0x02
  > BUTTON_B1_B2_B3_B4 0x00
  > ```


- **KeyMatrix**

  > ```c
  > unsigned char Keyboard_Value(void);
  > ```
  >
  > 简介：扫描键盘并`返回键值`。
  >
  > 详细：
  >
  > 1. 当扫描到`没有任何按键抬起`时，返回`0`；
  > 2. 当扫描到`有且只有一个按键抬起`时，返回对应键值；
  >
  > 注意：扫描按键矩阵过程中，`只对一个按键的抬起返回有效键值`，即`长按和同时按都不会返回对应键值`，以下是键值表：
  >
  > ```c
  > KEYBOARD_NONE 0 //定义无按钮组合
  > KEYBOARD_K1 1
  > KEYBOARD_K2 2
  > KEYBOARD_K3 3
  > KEYBOARD_K4 4
  > KEYBOARD_K5 5
  > KEYBOARD_K6 6
  > KEYBOARD_K7 7
  > KEYBOARD_K8 8
  > KEYBOARD_K9 9
  > KEYBOARD_K10 10
  > KEYBOARD_K11 11
  > KEYBOARD_K12 12
  > KEYBOARD_K13 13
  > KEYBOARD_K14 14
  > KEYBOARD_K15 15
  > KEYBOARD_K16 16
  > ```

- **Buzzer**

  > ```c
  > void Buzzer_Initial(const unsigned char time, const unsigned char period);
  > ```
  >
  > 简介：`初始化`蜂鸣器。
  >
  > 参数：
  >
  > 1. 设置`发声时长`；
  > 2. 设置`频率`；

  > ```c
  > void Buzzer_Emit(const bit value);
  > ```
  >
  > 简介：发出信号；
  >
  > 参数：
  >
  > 1. `0`和`1`分别表示发声和不发声；

  > ```c
  > void Buzzer_Beep(void);
  > ```
  >
  > 简介：执行`发声`操作。
  >
  > 注意：此函数建议在定时器中断的回调函数中执行。

- **LCD1602**

  > ```c
  > void LCD_Write(const unsigned char value, const unsigned char mode);
  > ```
  >
  > 简介：向LCD液晶写入`指令`或`数据`并`执行`。
  >
  > 参数：
  >
  > 1. `value`储存的值是想要向LCD液晶写入的值；
  >
  > 2. `mode`储存的值是表示`value`中的内容是`指令`还是`数据`；
  >
  >    > | **mode** |      **含义**       |
  >    > | :------: | :-----------------: |
  >    > |   `0`    | value中的值是`指令` |
  >    > |   `1`    | value中的值是`数据` |
  >
  > 详细：
  >
  > 1. 首先从LCD液晶读取其状态，如果`正忙`则继续读取，直到`不忙`；
  > 2. 接着向LCD液晶写入内容，并执行该内容；

  > ```c
  > void LCD_Initial(void);
  > ```
  >
  > 简介：``初始化``LCD液晶。
  >
  > 详细：
  >
  > 1. 使用八位数据接口，两行显示，5*7点阵；
  > 2. `数据`读、写操作后，光标自动移动，显示区域不动；
  > 3. 显示开，光标关，闪烁关；
  > 4. 清屏，光标复位；

  > ```c
  > void LCD_Clear(void);
  > ```
  >
  > 简介：`清屏`。

  > ```C
  > void LCD_PrtChar(const char value);
  > ```
  >
  > 简介：`打印单个字符`。
  >
  > 参数：
  >
  > 1. `value`储存的值是要打印的单个字符；
  >
  > 详细：在光标的`当前位置`打印`value`储存的单个字符，`光标自动移动`。

  > ```c
  > void LCD_PrtCharAt(const char value, const unsigned char x, const unsigned char y);
  > ```
  >
  > 简介：在`指定位置`打印单个字符。
  >
  > 参数：
  >
  > 1. `value`储存的值是要打印的单个字符；
  > 2. `x`和`y`储存的值是要打印的坐标位置；
  >
  > 详细：将光标移动到`指定位置`打印`value`储存的`单个字符`，`光标自动移动`。

  > ```c
  > void LCD_PrtStr(const char *value);
  > ```
  >
  > 简介：`打印字符串`。
  >
  > 参数：
  >
  > 1. `value`储存的值是一个指向字符串的地址；
  >
  > 详细：在光标`当前位置`打印`value`指定的`字符串`，**字符串必须以`\0`结尾**，`光标自动移动`。

  > ```c
  > void LCD_PrtStrAt(const char *value, const unsigned char x, const unsigned char y);
  > ```
  >
  > 简介：在`指定位置`打印字符串。
  >
  > 参数：
  >
  > 1. `value`储存的值是一个指向字符串的地址；
  > 2. `x`和`y`储存的值是开始打印的位置；
  >
  > 详细：将光标移动到`指定位置`打印`value`指定的`字符串`，`光标自动移动`。

- **LEDMatrix**

  > ```c
  > void LEDMatrix_Initial(const unsigned char values[], const unsigned char length);
  > ```
  >
  > 简介：`初始化`LED矩阵。
  >
  > 参数：
  >
  > 1. `values`储存的值是一维数组的地址，该数组中的元素的值表示的是一列LED的亮灭组合；
  > 2. `length`储存的值是上述数组的长度；
  >
  > 详细：
  >
  > 1. 首先将`values`和`length`分别赋值给全局变量进行储存；
  > 2. 最后设置开始显示的数组下标`index`为`0`；

  > ```c
  > void LEDMatrix_Light(void);
  > ```
  >
  > 简介：通过逐列扫描来`点亮`LED矩阵。
  >
  > 注意：LED矩阵每列的亮灭组合由`values`和当前显示的下标`index`共同决定；如果显示下标超过数组长度则会继续从头显示。

  > ```c
  > void LEDMatrix_Next(void);
  > ```
  >
  > 简介：`移动显示下标`。
  >
  > 注意：如果超出数组长度则会自动回到`0`。

- **Digital**

  > ```c
  > void Digital_Initial(const unsigned char values[8]);
  > ```
  >
  > 简介：`初始化`数码管模块。
  >
  > 参数：
  >
  > 1. `values`储存的值是一组长度为`8`的数组首地址，各元素的值依次表示对应的数码管的显示内容；
  >
  > 注意：`values`的长度固定为`8`。

  > ```c
  > void Digital_Light(void);
  > ```
  >
  > 简介：**点亮**数码管。
  >
  > 注意：点亮过程为逐个数码管进行亮点，每个数码管点亮的间隔或者时长为`2ms`。
