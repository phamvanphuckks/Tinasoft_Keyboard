
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2019 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "usb_device.h"
#include "usbd_hid.h"

UART_HandleTypeDef huart1;

#ifdef __GNUC__
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
	return ch;
}


uint8_t bufferHID[8];

extern USBD_HandleTypeDef hUsbDeviceFS;


void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);

uint16_t ret = 0;
char rx_data[4];



int main(void)
{

  HAL_Init();

  SystemClock_Config();


  MX_GPIO_Init();
  MX_USB_DEVICE_Init();
  MX_USART1_UART_Init();
	
	bufferHID[0] = 1;
	bufferHID[1] = 0;   
	bufferHID[2] = 0;   
	bufferHID[3] = 0;  
	bufferHID[4] = 0; 
	bufferHID[5] = 0;
	bufferHID[6] = 0;
	bufferHID[7] = 0;
  while (1)
  {
		memset(rx_data, 0 , 4);
		HAL_UART_Receive(&huart1, (uint8_t *)rx_data, 4, 200);
		HAL_Delay(1);
		ret = atoi(rx_data);
	
		if(ret == 225) // ?
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x38;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
	
		if(ret == 226) // <
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x36;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 227) // ?
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x1e;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 228) // %
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x22 ;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 229) // @
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x1f;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 230) // ^
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x23;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 231) // #
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x20;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 232) // &
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x24;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 233) // :
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x33;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 234) // {
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x2f;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 235) // $
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x21;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		
		if(ret == 237) // A
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x04;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 238) // S
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x16;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 239) // H
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x0b;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 240) // N
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x11;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 241) // M
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x10;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 242) // J
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x0d;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 243) // C
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x06;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 244) // R
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x15;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 245) // K
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x0e;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 246) // T
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x17;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 247) // D
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x07;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 248) // L
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x0f;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 249) // Y
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x1C;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 250) // O
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x12;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 251) // E
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x08;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 252) // V
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x19;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 253) // U
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x18;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 254) // P
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x13;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 255) // F
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x09;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 256) // B
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x05;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 257) // X
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x1b;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 258) // W
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x1a;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 259) // I
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x0c;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 260) // Z
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x1d;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 261) // Q
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x14;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 262) // >
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x37;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		if(ret == 263)//G
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0x02;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0x0A;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
		
		else if(ret != 0)
		{
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = ret;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			bufferHID[0] = 1;
			bufferHID[1] = 0;   
			bufferHID[2] = 0;   
			bufferHID[3] = 0;  
			bufferHID[4] = 0; 
			bufferHID[5] = 0;
			bufferHID[6] = 0;
			bufferHID[7] = 0;
			USBD_HID_SendReport(&hUsbDeviceFS,bufferHID, 8);
			HAL_Delay(30);
			ret = 0;
		}
  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 250000;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
