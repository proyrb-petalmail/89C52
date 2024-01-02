# 为89C52定制的模块库

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

下列函数的声明和定义分别位于相应库的`.h`和`.c`文件中，想要深入了解各模块库如何实现可以打开学习。

### Delay

  > ```c
  > void Delay2ms(void);
  > void Delay10ms(void);
  > ```
  > 
  > 简介：按照特定时长`延时`。
  > 
  >注意：以上函数只适用于频率为**`11.0592MHz`**的晶振。

### Timer

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

### Button

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
  > | 宏标识             | 键值   |
  > | ------------------ | ------ |
  > | BUTTON_NONE        | `0x0F` |
  > | BUTTON_B1          | `0x0D` |
  > | BUTTON_B2          | `0x0E` |
  > | BUTTON_B3          | `0x0B` |
  > | BUTTON_B4          | `0x07` |
  > | BUTTON_B1_B2       | `0x0C` |
  > | BUTTON_B1_B3       | `0x09` |
  > | BUTTON_B1_B4       | `0x05` |
  > | BUTTON_B2_B3       | `0x0A` |
  > | BUTTON_B2_B4       | `0x06` |
  > | BUTTON_B3_B4       | `0x03` |
  > | BUTTON_B1_B2_B3    | `0x08` |
  > | BUTTON_B1_B2_B4    | `0x04` |
  > | BUTTON_B1_B3_B4    | `0x01` |
  > | BUTTON_B2_B3_B4    | `0x02` |
  > | BUTTON_B1_B2_B3_B4 | `0x00` |


### KeyMatrix

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
  > | 宏标识             | 键值   |
  > | ------------------ | ------ |
  > |KEYBOARD_NONE |`0`|
  > |KEYBOARD_K1 |`1`|
  > |KEYBOARD_K2 |`2`|
  > |KEYBOARD_K3 |`3`|
  > |KEYBOARD_K4 |`4`|
  > |KEYBOARD_K5 |`5`|
  > |KEYBOARD_K6 |`6`|
  > |KEYBOARD_K7 |`7`|
  > |KEYBOARD_K8| `8` |
  > |KEYBOARD_K9| `9` |
  > |KEYBOARD_K10 |`10`|
  > |KEYBOARD_K11 |`11`|
  > |KEYBOARD_K12 |`12`|
  > |KEYBOARD_K13 |`13`|
  > |KEYBOARD_K14 |`14`|
  > |KEYBOARD_K15 |`15`|
  > |KEYBOARD_K16 |`16`|

### Buzzer

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
  > 1. `0`和`1`分别表示`发声`和`不发声`；

  > ```c
  > void Buzzer_Beep(void);
  > ```
  >
  > 简介：执行`发声`操作。
  >
  > 注意：此函数建议在定时器中断的`回调函数`中执行。

### LEDQueue

  > ```c
  > void LEDQueue_Light(const unsigned char number);
  > ```
  >
  > 简介：按照指定方式点亮发光二极管队列。

### Digital

  > ```c
  > void Digital_Initial(const unsigned char item[], const unsigned char amount);
  > ```
  >
  > 简介：设置数码管`显示内容`和`其长度`。
  >
  > 参数：
  >
  > 1. `item`储存的值是要显示的内容的数组地址，各元素的值依次表示对应的数码管的显示内容；
  > 1. `amount`储存的值是`该数组长度`；
  >
  > 注意：数码管初始化后默认从`0`作为显示起点。

  > ```c
  > void Digital_Light(void);
  > ```
  >
  > 简介：**点亮**数码管。
  >
  > 注意：点亮过程为逐个数码管进行亮点，每个数码管点亮的间隔或者时长为`2ms`。

  > ```c
  > void Digital_Left(void);
  > ```
  >
  > 简介：`左移`数码管显示内容。
  >
  > 注意：可以循环显示。

  > ```C
  > void Digital_Right(void);
  > ```
  >
  > 简介：`右移`数码管显示内容。
  >
  > 注意：可以循环显示。

### LEDMatrix

  > ```c
  > void LEDMatrix_Initial(const unsigned char item[], const unsigned char amount);
  > ```
  >
  > 简介：设置发光二极管矩阵`显示的内容`和`其长度`。
  >
  > 参数：
  >
  > 1. `item`储存的值是要显示的内容的数组的地址，该数组中的元素的值表示的是一列发光二极管的亮灭组合；
  > 2. `amount`储存的值是上述数组的长度；
  >
  > 注意：初始化后默认从`0`作为显示起点。

  > ```c
  > void LEDMatrix_Light(void);
  > ```
  >
  > 简介：通过逐列扫描来`点亮`LED矩阵。
  >
  > 注意：当前`start`决定了`从何处开始显示`。

  > ```c
  > void LEDMatrix_Left(void);
  > ```
  >
  > 简介：`左移`显示内容。
  >
  > 注意：可以循环显示。

  > ```c
  > void LEDMatrix_Right(void);
  > ```
  >
  > 简介：`右移`显示内容。
  >
  > 注意：可以循环显示。

### LCD1602

  > ```c
  > void LCD_Initial(void);
  > ```
  >
  > 简介：`初始化`液晶屏。
  >
  > 详细：
  >
  > 1. 尝试启动；
  > 2. 使用八位数据接口，两行显示，5*7点阵；
  > 3. `数据`读、写操作后，光标自动移动，显示区域不动；
  > 4. 显示开，光标关，闪烁关；
  > 5. 清屏，光标复位；

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
  > void LCD_PrtCharAt(const char value, const unsigned char x, const bit y);
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
  > void LCD_PrtStr(const char * value);
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
  > void LCD_PrtStrAt(const char * value, const unsigned char x, const bit y);
  > ```
  >
  > 简介：在`指定位置`打印字符串。
  >
  > 参数：
  >
  > 1. `value`储存的值是一个指向字符串的地址；
  > 2. `x`和`y`储存的值是开始打印的位置；
  >
  > 详细：将光标移动到`指定位置`打印`value`指定的`字符串`，**字符串必须以`\0`结尾**，`光标自动移动`。

### Motor

  > ```c
  > void Motor_Initial(const float invert_rate);
  > ```
  >
  > 简介：`初始化`直流电机。
  >
  > 参数：
  >
  > 1. 设置直流电机的驱动时长所占比例，取值为`0.0~1.0`之间，取值越大转速越快；

  > ```c
  > void Motor_Emit(const bit value);
  > ```
  >
  > 简介：发出信号。
  >
  > 参数：
  >
  > 1. `0`和`1`分别表示`驱动`和`不驱动`；

  > ```c
  > void Motor_Drive(void);
  > ```
  >
  > 简介：`驱动`直流电机。
  >
  > 注意：此函数建议在定时器中断时的`回调函数`中执行。