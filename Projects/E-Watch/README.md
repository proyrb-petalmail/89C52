- **Delay**

  > ```c
  > void Delay2ms(void);
  > ```
  > 
  > 简介：按照特定时长`延时`。
  > 
  > 注意：只适用于频率为**`11.0592MHz`**的晶振。
  
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
  > | 宏标识      | 键值 |
  > | ----------- | ---- |
  > |BUTTON_NONE |`0x0F`|
  > |BUTTON_B1 |`0x0D`|
  > |BUTTON_B2 |`0x0E`|
  > |BUTTON_B3 |`0x0B`|
  > |BUTTON_B4| `0x07` |
  > |BUTTON_B1_B2| `0x0C` |
  > |BUTTON_B1_B3 |`0x09`|
  > |BUTTON_B1_B4 |`0x05`|
  > |BUTTON_B2_B3 |`0x0A`|
  > |BUTTON_B2_B4 |`0x06`|
  > |BUTTON_B3_B4 |`0x03`|
  > |BUTTON_B1_B2_B3 |`0x08`|
  > |BUTTON_B1_B2_B4 |`0x04`|
  > |BUTTON_B1_B3_B4 |`0x01`|
  > |BUTTON_B2_B3_B4 |`0x02`|
  > |BUTTON_B1_B2_B3_B4 |`0x00`|
  >
  
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
  > 1. `0`和`1`分别表示`发声`和`不发声`；

  > ```c
  > void Buzzer_Beep(void);
  > ```
  >
  > 简介：执行`发声`操作。
  >
  > 注意：此函数建议在定时器中断的`回调函数`中执行。

- **LEDQueue**

  > ```c
  > void LEDQueue_Light(const unsigned char number);
  > ```
  >
  > 简介：按照指定方式点亮发光二极管队列。

- **Digital**

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
