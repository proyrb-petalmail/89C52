# Guide of Libraries for 89C52RC

## Brief Introduction

> First of all, I am very pleased that you can use the library I have written for this microcontroller and its peripheral devices. If you encounter any problems during use, you can provide me with feedback through the email provided below. Thank you.
>
> Email: **proyrb@petalmail.com**

## Library Directory

> As of now, the library includes the following modules.
>
> - **Delay**
>
>   Implementing software delay by enabling the microcontroller to perform empty operations.
>
> - **Timer**
>
>   By using the built-in counter of the microcontroller to achieve timing function.
>
> - **KeyMatrix**
>
>   Obtain key values by scanning the status of the key matrix.
>
> - **LCD1602**
>
>   Implementing LCD display by interacting with LCD1602 through an 8-bit register.
>   
> - **LEDMatrix**
>
>   Lighting up the LED matrix through continuous scanning.
>
> - **Buzzer**
>
>   Can emit a fixed frequency of buzzing sound.
>
> The remaining modules are in the development stage.

## Usage

> How to use these libraries in an engineering project?
>
> 1. Add the `.c` and `.h` files from the desired library to the engineering project.
>
> 2. Include the corresponding library header file in the module where you want to use the library added in the previous step.
>
>    ```c
>    //...
>       
>    #include <xxx.h>
>       
>    //...
>    ```
