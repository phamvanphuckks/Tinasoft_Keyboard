/**
  ******************************************************************************
  * @file    usbd_hid.c
  * @author  MCD Application Team
  * @version V2.4.2
  * @date    11-December-2015
  * @brief   This file provides the HID core functions.
  *
  * @verbatim
  *      
  *          ===================================================================      
  *                                HID Class  Description
  *          =================================================================== 
  *           This module manages the HID class V1.11 following the "Device Class Definition
  *           for Human Interface Devices (HID) Version 1.11 Jun 27, 2001".
  *           This driver implements the following aspects of the specification:
  *             - The Boot Interface Subclass
  *             - The Mouse protocol
  *             - Usage Page : Generic Desktop
  *             - Usage : Joystick
  *             - Collection : Application 
  *      
  * @note     In HS mode and when the DMA is used, all variables and data structures
  *           dealing with the DMA during the transaction process should be 32-bit aligned.
  *           
  *      
  *  @endverbatim
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "usbd_hid.h"
#include "usbd_desc.h"
#include "usbd_ctlreq.h"


/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */


/** @defgroup USBD_HID 
  * @brief usbd core module
  * @{
  */ 

/** @defgroup USBD_HID_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup USBD_HID_Private_Defines
  * @{
  */ 

/**
  * @}
  */ 


/** @defgroup USBD_HID_Private_Macros
  * @{
  */ 
/**
  * @}
  */ 




/** @defgroup USBD_HID_Private_FunctionPrototypes
  * @{
  */


static uint8_t  USBD_HID_Init (USBD_HandleTypeDef *pdev, 
                               uint8_t cfgidx);

static uint8_t  USBD_HID_DeInit (USBD_HandleTypeDef *pdev, 
                                 uint8_t cfgidx);

static uint8_t  USBD_HID_Setup (USBD_HandleTypeDef *pdev, 
                                USBD_SetupReqTypedef *req);

static uint8_t  *USBD_HID_GetCfgDesc (uint16_t *length);

static uint8_t  *USBD_HID_GetDeviceQualifierDesc (uint16_t *length);

static uint8_t  USBD_HID_DataIn (USBD_HandleTypeDef *pdev, uint8_t epnum);
/**
  * @}
  */ 

/** @defgroup USBD_HID_Private_Variables
  * @{
  */ 

USBD_ClassTypeDef  USBD_HID = 
{
  USBD_HID_Init,
  USBD_HID_DeInit,
  USBD_HID_Setup,
  NULL, /*EP0_TxSent*/  
  NULL, /*EP0_RxReady*/
  USBD_HID_DataIn, /*DataIn*/
  NULL, /*DataOut*/
  NULL, /*SOF */
  NULL,
  NULL,      
  USBD_HID_GetCfgDesc,
  USBD_HID_GetCfgDesc, 
  USBD_HID_GetCfgDesc,
  USBD_HID_GetDeviceQualifierDesc,
};

/* USB HID device Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_CfgDesc[USB_HID_CONFIG_DESC_SIZ]  __ALIGN_END =
{
  0x09, /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */
  USB_HID_CONFIG_DESC_SIZ,
  /* wTotalLength: Bytes returned */
  0x00,
  0x01,         /*bNumInterfaces: 1 interface*/
  0x01,         /*bConfigurationValue: Configuration value*/
  0x00,         /*iConfiguration: Index of string descriptor describing
  the configuration*/
  0xE0,         /*bmAttributes: bus powered and Support Remote Wake-up */
  0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/
  
  /************** Descriptor of Joystick Mouse interface ****************/
  /* 09 */
  0x09,         /*bLength: Interface Descriptor size*/
  USB_DESC_TYPE_INTERFACE,/*bDescriptorType: Interface descriptor type*/
  0x00,         /*bInterfaceNumber: Number of Interface*/
  0x00,         /*bAlternateSetting: Alternate setting*/
  0x01,         /*bNumEndpoints*/
  0x03,         /*bInterfaceClass: HID*/
  0x01,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
  0x01,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
  0,            /*iInterface: Index of string descriptor*/
  /******************** Descriptor of Joystick Mouse HID ********************/
  /* 18 */
  0x09,         /*bLength: HID Descriptor size*/
  HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
  0x11,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  HID_MOUSE_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
  0x00,
  /******************** Descriptor of Mouse endpoint ********************/
  /* 27 */
  0x07,          /*bLength: Endpoint Descriptor size*/
  USB_DESC_TYPE_ENDPOINT, /*bDescriptorType:*/
  
  HID_EPIN_ADDR,     /*bEndpointAddress: Endpoint Address (IN)*/
  0x03,          /*bmAttributes: Interrupt endpoint*/
  HID_EPIN_SIZE, /*wMaxPacketSize: 4 Byte max */
  0x00,
  HID_FS_BINTERVAL,          /*bInterval: Polling Interval (10 ms)*/
  /* 34 */
} ;

/* USB HID device Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_Desc[USB_HID_DESC_SIZ]  __ALIGN_END  =
{
  /* 18 */
  0x09,         /*bLength: HID Descriptor size*/
  HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
  0x11,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  HID_MOUSE_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
  0x00,
};

/* USB Standard Device Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC]  __ALIGN_END =
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};

__ALIGN_BEGIN static uint8_t HID_MOUSE_ReportDesc[HID_MOUSE_REPORT_DESC_SIZE]  __ALIGN_END =
{
   0x05    ,//bSize: 0x01, bType: Global, bTag: Usage Page
	     0x01    ,//Usage Page(Generic Desktop Controls )
	     0x09    ,//bSize: 0x01, bType: Local, bTag: Usage
	     0x06    ,//Usage(Keyboard)
	     0xA1    ,//bSize: 0x01, bType: Main, bTag: Collection
	     0x01    ,//Collection(Application )
	     0x85    ,//bSize: 0x01, bType: Global, bTag: Report ID
	     0x01    ,//Report ID(0x1 )
	     0x05    ,//bSize: 0x01, bType: Global, bTag: Usage Page
	     0x07    ,//Usage Page(Keyboard/Keypad )
	     0x19    ,//bSize: 0x01, bType: Local, bTag: Usage Minimum
	     0xE0    ,//Usage Minimum(0xE0 )
	     0x29    ,//bSize: 0x01, bType: Local, bTag: Usage Maximum
	     0xE7    ,//Usage Maximum(0xE7 )
	     0x15    ,//bSize: 0x01, bType: Global, bTag: Logical Minimum
	     0x00    ,//Logical Minimum(0x0 )
	     0x25    ,//bSize: 0x01, bType: Global, bTag: Logical Maximum
	     0x01    ,//Logical Maximum(0x1 )
	     0x75    ,//bSize: 0x01, bType: Global, bTag: Report Size
	     0x01    ,//Report Size(0x1 )
	     0x95    ,//bSize: 0x01, bType: Global, bTag: Report Count
	     0x08    ,//Report Count(0x8 )
	     0x81    ,//bSize: 0x01, bType: Main, bTag: Input
	     0x02    ,//Input(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)
	     0x75    ,//bSize: 0x01, bType: Global, bTag: Report Size
	     0x08    ,//Report Size(0x8 )
	     0x95    ,//bSize: 0x01, bType: Global, bTag: Report Count
	     0x01    ,//Report Count(0x1 )
	     0x81    ,//bSize: 0x01, bType: Main, bTag: Input
	     0x01    ,//Input(Constant, Array, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)
	     0x05    ,//bSize: 0x01, bType: Global, bTag: Usage Page
	     0x07    ,//Usage Page(Keyboard/Keypad )
	     0x19    ,//bSize: 0x01, bType: Local, bTag: Usage Minimum
	     0x00    ,//Usage Minimum(0x0 )
	     0x29    ,//bSize: 0x01, bType: Local, bTag: Usage Maximum
	     0x65    ,//Usage Maximum(0x65 )
	     0x15    ,//bSize: 0x01, bType: Global, bTag: Logical Minimum
	     0x00    ,//Logical Minimum(0x0 )
	     0x25    ,//bSize: 0x01, bType: Global, bTag: Logical Maximum
	     0x65    ,//Logical Maximum(0x65 )
	     0x75    ,//bSize: 0x01, bType: Global, bTag: Report Size
	     0x08    ,//Report Size(0x8 )
	     0x95    ,//bSize: 0x01, bType: Global, bTag: Report Count
	     0x05    ,//Report Count(0x5 )
	     0x81    ,//bSize: 0x01, bType: Main, bTag: Input
	     0x00    ,//Input(Data, Array, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)
	     0xC0    ,//bSize: 0x00, bType: Main, bTag: End Collection
	     0x05    ,//bSize: 0x01, bType: Global, bTag: Usage Page
	     0x0C    ,//Usage Page(Consumer )
	     0x09    ,//bSize: 0x01, bType: Local, bTag: Usage
	     0x01    ,//Usage(Consumer Control)
	     0xA1    ,//bSize: 0x01, bType: Main, bTag: Collection
	     0x01    ,//Collection(Application )
	     0x85    ,//bSize: 0x01, bType: Global, bTag: Report ID
	     0x02    ,//Report ID(0x2 )
	     0x19    ,//bSize: 0x01, bType: Local, bTag: Usage Minimum
	     0x00    ,//Usage Minimum(0x0 )
	     0x2A    ,//bSize: 0x02, bType: Local, bTag: Usage Maximum
	     0x3C,
	     0x02 ,//Usage Maximum(0x23C )
	     0x15    ,//bSize: 0x01, bType: Global, bTag: Logical Minimum
	     0x00    ,//Logical Minimum(0x0 )
	     0x26    ,//bSize: 0x02, bType: Global, bTag: Logical Maximum
	     0x3C,
	     0x02 ,//Logical Maximum(0x23C )
	     0x95    ,//bSize: 0x01, bType: Global, bTag: Report Count
	     0x01    ,//Report Count(0x1 )
	     0x75    ,//bSize: 0x01, bType: Global, bTag: Report Size
	     0x10    ,//Report Size(0x10 )
	     0x81    ,//bSize: 0x01, bType: Main, bTag: Input
	     0x00    ,//Input(Data, Array, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)
	     0xC0    ,//bSize: 0x00, bType: Main, bTag: End Collection
	     0x05    ,//bSize: 0x01, bType: Global, bTag: Usage Page
	     0x01    ,//Usage Page(Generic Desktop Controls )
	     0x09    ,//bSize: 0x01, bType: Local, bTag: Usage
	     0x80    ,//Usage(System Control)
	     0xA1    ,//bSize: 0x01, bType: Main, bTag: Collection
	     0x01    ,//Collection(Application )
	     0x85    ,//bSize: 0x01, bType: Global, bTag: Report ID
	     0x03    ,//Report ID(0x3 )
	     0x19    ,//bSize: 0x01, bType: Local, bTag: Usage Minimum
	     0x81    ,//Usage Minimum(0x81 )
	     0x29    ,//bSize: 0x01, bType: Local, bTag: Usage Maximum
	     0x83    ,//Usage Maximum(0x83 )
	     0x15    ,//bSize: 0x01, bType: Global, bTag: Logical Minimum
	     0x00    ,//Logical Minimum(0x0 )
	     0x25    ,//bSize: 0x01, bType: Global, bTag: Logical Maximum
	     0x01    ,//Logical Maximum(0x1 )
	     0x75    ,//bSize: 0x01, bType: Global, bTag: Report Size
	     0x01    ,//Report Size(0x1 )
	     0x95    ,//bSize: 0x01, bType: Global, bTag: Report Count
	     0x03    ,//Report Count(0x3 )
	     0x81    ,//bSize: 0x01, bType: Main, bTag: Input
	     0x02    ,//Input(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)
	     0x95    ,//bSize: 0x01, bType: Global, bTag: Report Count
	     0x05    ,//Report Count(0x5 )
	     0x81    ,//bSize: 0x01, bType: Main, bTag: Input
	     0x01    ,//Input(Constant, Array, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)
	     0xC0    ,//bSize: 0x00, bType: Main, bTag: End Collection
	     0x06    ,//bSize: 0x02, bType: Global, bTag: Usage Page
	     0x01,
	     0xFF ,//Usage Page(Undefined )
	     0x09    ,//bSize: 0x01, bType: Local, bTag: Usage
	     0x01    ,//Usage(1)
	     0xA1    ,//bSize: 0x01, bType: Main, bTag: Collection
	     0x01    ,//Collection(Application )
	     0x85    ,//bSize: 0x01, bType: Global, bTag: Report ID
	     0x04    ,//Report ID(0x4 )
	     0x95    ,//bSize: 0x01, bType: Global, bTag: Report Count
	     0x01    ,//Report Count(0x1 )
	     0x75    ,//bSize: 0x01, bType: Global, bTag: Report Size
	     0x08    ,//Report Size(0x8 )
	     0x15    ,//bSize: 0x01, bType: Global, bTag: Logical Minimum
	     0x01    ,//Logical Minimum(0x1 )
	     0x25    ,//bSize: 0x01, bType: Global, bTag: Logical Maximum
	     0x0A    ,//Logical Maximum(0xA )
	     0x09    ,//bSize: 0x01, bType: Local, bTag: Usage
	     0x20    ,//Usage(32)
	     0xB1    ,//bSize: 0x01, bType: Main, bTag: Feature
	     0x03    ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
	     0x09    ,//bSize: 0x01, bType: Local, bTag: Usage
	     0x23    ,//Usage(35)
	     0xB1    ,//bSize: 0x01, bType: Main, bTag: Feature
	     0x03    ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
	     0x25    ,//bSize: 0x01, bType: Global, bTag: Logical Maximum
	     0x4F    ,//Logical Maximum(0x4F )
	     0x09    ,//bSize: 0x01, bType: Local, bTag: Usage
	     0x21    ,//Usage(33)
	     0xB1    ,//bSize: 0x01, bType: Main, bTag: Feature
	     0x03    ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
	     0x25    ,//bSize: 0x01, bType: Global, bTag: Logical Maximum
	     0x30    ,//Logical Maximum(0x30 )
	     0x09    ,//bSize: 0x01, bType: Local, bTag: Usage
	     0x22    ,//Usage(34)
	     0xB1    ,//bSize: 0x01, bType: Main, bTag: Feature
	     0x03    ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
	     0x95    ,//bSize: 0x01, bType: Global, bTag: Report Count
	     0x03    ,//Report Count(0x3 )
	     0x09    ,//bSize: 0x01, bType: Local, bTag: Usage
	     0x24    ,//Usage(36)
	     0xB1    ,//bSize: 0x01, bType: Main, bTag: Feature
	     0x03    ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
	     0xC0    ,//bSize: 0x00, bType: Main, bTag: End Collection
	     0x06    ,//bSize: 0x02, bType: Global, bTag: Usage Page
	     0x01,
	     0xFF ,//Usage Page(Undefined )
	     0x09    ,//bSize: 0x01, bType: Local, bTag: Usage
	     0x01    ,//Usage(1)
	     0xA1    ,//bSize: 0x01, bType: Main, bTag: Collection
	     0x01    ,//Collection(Application )
	     0x85    ,//bSize: 0x01, bType: Global, bTag: Report ID
	     0x05    ,//Report ID(0x5 )
	     0x95    ,//bSize: 0x01, bType: Global, bTag: Report Count
	     0x01    ,//Report Count(0x1 )
	     0x75    ,//bSize: 0x01, bType: Global, bTag: Report Size
	     0x08    ,//Report Size(0x8 )
	     0x15    ,//bSize: 0x01, bType: Global, bTag: Logical Minimum
	     0x01    ,//Logical Minimum(0x1 )
	     0x25    ,//bSize: 0x01, bType: Global, bTag: Logical Maximum
	     0x0A    ,//Logical Maximum(0xA )
	     0x09    ,//bSize: 0x01, bType: Local, bTag: Usage
	     0x20    ,//Usage(32)
	     0xB1    ,//bSize: 0x01, bType: Main, bTag: Feature
	     0x03    ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
	     0x09    ,//bSize: 0x01, bType: Local, bTag: Usage
	     0x23    ,//Usage(35)
	     0xB1    ,//bSize: 0x01, bType: Main, bTag: Feature
	     0x03    ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
	     0x25    ,//bSize: 0x01, bType: Global, bTag: Logical Maximum
	     0x4F    ,//Logical Maximum(0x4F )
	     0x09    ,//bSize: 0x01, bType: Local, bTag: Usage
	     0x21    ,//Usage(33)
	     0xB1    ,//bSize: 0x01, bType: Main, bTag: Feature
	     0x03    ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
	     0x25    ,//bSize: 0x01, bType: Global, bTag: Logical Maximum
	     0x30    ,//Logical Maximum(0x30 )
	     0x09    ,//bSize: 0x01, bType: Local, bTag: Usage
	     0x22    ,//Usage(34)
	     0xB1    ,//bSize: 0x01, bType: Main, bTag: Feature
	     0x03    ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
	     0x95    ,//bSize: 0x01, bType: Global, bTag: Report Count
	     0x03    ,//Report Count(0x3 )
	     0x09    ,//bSize: 0x01, bType: Local, bTag: Usage
	     0x24    ,//Usage(36)
	     0xB1    ,//bSize: 0x01, bType: Main, bTag: Feature
	     0x03    ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
	     0xC0    //bSize: 0x00, bType: Main, bTag: End Collection
	
}; 

/**
  * @}
  */ 

/** @defgroup USBD_HID_Private_Functions
  * @{
  */ 

/**
  * @brief  USBD_HID_Init
  *         Initialize the HID interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_HID_Init (USBD_HandleTypeDef *pdev, 
                               uint8_t cfgidx)
{
  uint8_t ret = 0;
  
  /* Open EP IN */
  USBD_LL_OpenEP(pdev,
                 HID_EPIN_ADDR,
                 USBD_EP_TYPE_INTR,
                 HID_EPIN_SIZE);  
  
  pdev->pClassData = USBD_malloc(sizeof (USBD_HID_HandleTypeDef));
  
  if(pdev->pClassData == NULL)
  {
    ret = 1; 
  }
  else
  {
    ((USBD_HID_HandleTypeDef *)pdev->pClassData)->state = HID_IDLE;
  }
  return ret;
}

/**
  * @brief  USBD_HID_Init
  *         DeInitialize the HID layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_HID_DeInit (USBD_HandleTypeDef *pdev, 
                                 uint8_t cfgidx)
{
  /* Close HID EPs */
  USBD_LL_CloseEP(pdev,
                  HID_EPIN_ADDR);
  
  /* FRee allocated memory */
  if(pdev->pClassData != NULL)
  {
    USBD_free(pdev->pClassData);
    pdev->pClassData = NULL;
  } 
  
  return USBD_OK;
}

/**
  * @brief  USBD_HID_Setup
  *         Handle the HID specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
static uint8_t  USBD_HID_Setup (USBD_HandleTypeDef *pdev, 
                                USBD_SetupReqTypedef *req)
{
  uint16_t len = 0;
  uint8_t  *pbuf = NULL;
  USBD_HID_HandleTypeDef     *hhid = (USBD_HID_HandleTypeDef*) pdev->pClassData;
  
  switch (req->bmRequest & USB_REQ_TYPE_MASK)
  {
  case USB_REQ_TYPE_CLASS :  
    switch (req->bRequest)
    {
      
      
    case HID_REQ_SET_PROTOCOL:
      hhid->Protocol = (uint8_t)(req->wValue);
      break;
      
    case HID_REQ_GET_PROTOCOL:
      USBD_CtlSendData (pdev, 
                        (uint8_t *)&hhid->Protocol,
                        1);    
      break;
      
    case HID_REQ_SET_IDLE:
      hhid->IdleState = (uint8_t)(req->wValue >> 8);
      break;
      
    case HID_REQ_GET_IDLE:
      USBD_CtlSendData (pdev, 
                        (uint8_t *)&hhid->IdleState,
                        1);        
      break;      
      
    default:
      USBD_CtlError (pdev, req);
      return USBD_FAIL; 
    }
    break;
    
  case USB_REQ_TYPE_STANDARD:
    switch (req->bRequest)
    {
    case USB_REQ_GET_DESCRIPTOR: 
      if( req->wValue >> 8 == HID_REPORT_DESC)
      {
        len = MIN(HID_MOUSE_REPORT_DESC_SIZE , req->wLength);
        pbuf = HID_MOUSE_ReportDesc;
      }
      else if( req->wValue >> 8 == HID_DESCRIPTOR_TYPE)
      {
        pbuf = USBD_HID_Desc;   
        len = MIN(USB_HID_DESC_SIZ , req->wLength);
      }
      
      USBD_CtlSendData (pdev, 
                        pbuf,
                        len);
      
      break;
      
    case USB_REQ_GET_INTERFACE :
      USBD_CtlSendData (pdev,
                        (uint8_t *)&hhid->AltSetting,
                        1);
      break;
      
    case USB_REQ_SET_INTERFACE :
      hhid->AltSetting = (uint8_t)(req->wValue);
      break;
    }
  }
  return USBD_OK;
}

/**
  * @brief  USBD_HID_SendReport 
  *         Send HID Report
  * @param  pdev: device instance
  * @param  buff: pointer to report
  * @retval status
  */
uint8_t USBD_HID_SendReport     (USBD_HandleTypeDef  *pdev, 
                                 uint8_t *report,
                                 uint16_t len)
{
  USBD_HID_HandleTypeDef     *hhid = (USBD_HID_HandleTypeDef*)pdev->pClassData;
  
  if (pdev->dev_state == USBD_STATE_CONFIGURED )
  {
    if(hhid->state == HID_IDLE)
    {
      hhid->state = HID_BUSY;
      USBD_LL_Transmit (pdev, 
                        HID_EPIN_ADDR,                                      
                        report,
                        len);
    }
  }
  return USBD_OK;
}

/**
  * @brief  USBD_HID_GetPollingInterval 
  *         return polling interval from endpoint descriptor
  * @param  pdev: device instance
  * @retval polling interval
  */
uint32_t USBD_HID_GetPollingInterval (USBD_HandleTypeDef *pdev)
{
  uint32_t polling_interval = 0;

  /* HIGH-speed endpoints */
  if(pdev->dev_speed == USBD_SPEED_HIGH)
  {
   /* Sets the data transfer polling interval for high speed transfers. 
    Values between 1..16 are allowed. Values correspond to interval 
    of 2 ^ (bInterval-1). This option (8 ms, corresponds to HID_HS_BINTERVAL */
    polling_interval = (((1 <<(HID_HS_BINTERVAL - 1)))/8);
  }
  else   /* LOW and FULL-speed endpoints */
  {
    /* Sets the data transfer polling interval for low and full 
    speed transfers */
    polling_interval =  HID_FS_BINTERVAL;
  }
  
  return ((uint32_t)(polling_interval));
}

/**
  * @brief  USBD_HID_GetCfgDesc 
  *         return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_HID_GetCfgDesc (uint16_t *length)
{
  *length = sizeof (USBD_HID_CfgDesc);
  return USBD_HID_CfgDesc;
}


/**
  * @brief  USBD_HID_DataIn
  *         handle data IN Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  USBD_HID_DataIn (USBD_HandleTypeDef *pdev, 
                              uint8_t epnum)
{
  
  /* Ensure that the FIFO is empty before a new transfer, this condition could 
  be caused by  a new transfer before the end of the previous transfer */
  ((USBD_HID_HandleTypeDef *)pdev->pClassData)->state = HID_IDLE;
  return USBD_OK;
}


/**
* @brief  DeviceQualifierDescriptor 
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
static uint8_t  *USBD_HID_GetDeviceQualifierDesc (uint16_t *length)
{
  *length = sizeof (USBD_HID_DeviceQualifierDesc);
  return USBD_HID_DeviceQualifierDesc;
}

/**
  * @}
  */ 


/**
  * @}
  */ 


/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
