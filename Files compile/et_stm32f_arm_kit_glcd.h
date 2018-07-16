/**
  ******************************************************************************
  * @file    et_stm32f_arm_kit_glcd.h
  * @author  MCD Application Team
  * @version V3.1.2
  * @date    09/28/2009
  * @brief   This file contains all the functions prototypes for the lcd firmware driver.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ET_STM32F_ARM_KIT_GLCD_H
#define __ET_STM32F_ARM_KIT_GLCD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/******************************/
/* Define Color Code For GLCD */
/* Color = RRRRR GGGGGG BBBBB */
/******************************/
#define no_bg           	0x0001			// No Color Back Ground
#define BLACK           	0x0000
#define WHITE           	0xFFFF
#define RED             	0x8000
#define GREEN           	0x0400
#define BLUE            	0x0010
#define YELLOW          	0xFFF0
#define CYAN            	0x0410
#define MAGENTA         	0x8010
#define BROWN           	0xFC00
#define OLIVE	        	0x8400

#define BRIGHT_RED      	0xF800
#define BRIGHT_GREEN    	0x07E0
#define BRIGHT_BLUE     	0x001F
#define BRIGHT_YELLOW   	0xFFE0
#define BRIGHT_CYAN     	0x07FF
#define BRIGHT_MAGENTA  	0xF81F

#define LIGHT_GRAY      	0x8410
#define DARK_GRAY       	0x4208
#define LIGHT_BLUE      	0x841F
#define LIGHT_GREEN     	0x87F0
#define LIGHT_CYAN      	0x87FF
#define LIGHT_RED       	0xFC10
#define LIGHT_MAGENTA   	0xFC1F

#define GRAY0       		0xE71C
#define GRAY1         		0xC618
#define GRAY2           	0xA514
#define GRAY3           	0x630C
#define GRAY4           	0x4208
#define GRAY5	        	0x2104
#define	GRAY6	        	0x3186	

#define	BLUE0	        	0x1086	
#define	BLUE1       		0x3188 
#define	BLUE2          		0x4314
#define BLUE3         		0x861C	

#define	CYAN0	        	0x3D34
#define	CYAN1           	0x1DF7		

#define	GREEN0          	0x0200	
#define	GREEN1          	0x0208	

//------------ Color For Build Button -------------
#define BT_RED          	1
#define BT_GREEN        	2
#define BT_BLUE         	3
#define	BT_YELLOW       	4
#define BT_WHITE        	5
#define BT_CYAN         	6
#define BT_MAGENTA      	7
#define BT_BROWN        	8

#define BT_LRED         	9
#define BT_LGREEN       	10
#define BT_LBLUE        	11
#define	BT_LYELLOW      	12
#define BT_LWHITE       	13
#define BT_LCYAN        	14
#define BT_LMAGENTA     	15
#define BT_LBROWN       	16

/** 
  * @brief  LCD Control pins  
  */ 
#define LCD_CS_PIN          GPIO_Pin_8                  // PC8 = CS# GLCD
#define LCD_CS_GPIO_PORT    GPIOC                       
#define LCD_CS_GPIO_CLK     RCC_APB2Periph_GPIOC  

#define LCD_BL_PIN          GPIO_Pin_7                  // PD7 = BL GLCD
#define LCD_BL_GPIO_PORT    GPIOD                       
#define LCD_BL_GPIO_CLK     RCC_APB2Periph_GPIOD 

/** 
  * @brief  LCD SPI Interface pins 
  */ 
#define LCD_SPI_SCK_PIN     GPIO_Pin_10                 
#define LCD_SPI_MISO_PIN    GPIO_Pin_11                 
#define LCD_SPI_MOSI_PIN    GPIO_Pin_12                 
#define LCD_SPI_GPIO_PORT   GPIOC                       
#define LCD_SPI_GPIO_CLK    RCC_APB2Periph_GPIOC  
#define LCD_SPI			    SPI3
#define LCD_SPI_CLK		    RCC_APB1Periph_SPI3

/** 
  * @brief  TCS Control pins (ADS7846:Touch Sensor) 
  */ 
// PE3(PEN#) <--
// PE4(MISO) <--
// PE5(MOSI) -->
// PE6(CS#)	 -->
// PE7(SCK)	 --> 
#define TCS_GPIO_CLK        RCC_APB2Periph_GPIOE  
#define TCS_GPIO_PORT      	GPIOE
#define TCS_PEN_PIN         GPIO_Pin_3                  // PE3 = PEN# Touch Sensor                       
#define TCS_MISO_PIN        GPIO_Pin_4                  // PE4 = MISO Touch Sensor
#define TCS_MOSI_PIN        GPIO_Pin_5                  // PE5 = MOSI Touch Sensor
#define TCS_CS_PIN          GPIO_Pin_6                  // PE6 = CS# Touch Sensor
#define TCS_SCK_PIN         GPIO_Pin_7                  // PE7 = SCK Touch Sensor

// PEN#(PE3)
#define TCS_PEN_PORT        GPIOE
#define TCS_PEN_CLK         RCC_APB2Periph_GPIOE
#define TCS_PEN_PORT_SOURCE GPIO_PortSourceGPIOE
#define TCS_PEN_PIN         GPIO_Pin_3					
#define TCS_PEN_PIN_SOURCE  GPIO_PinSource3
#define TCS_PEN_EXTI_LINE   EXTI_Line3
#define TCS_PEN_IRQn        EXTI3_IRQn 

#define GLCD_CS_LOW()     	GPIO_ResetBits(LCD_CS_GPIO_PORT, LCD_CS_PIN)
#define GLCD_CS_HIGH()    	GPIO_SetBits(LCD_CS_GPIO_PORT, LCD_CS_PIN)
#define GLCD_BL_OFF()     	GPIO_ResetBits(LCD_BL_GPIO_PORT, LCD_BL_PIN)
#define GLCD_BL_ON()    	GPIO_SetBits(LCD_BL_GPIO_PORT, LCD_BL_PIN)
#define TCS_CS_LOW()     	GPIO_ResetBits(TCS_GPIO_PORT, TCS_CS_PIN)
#define TCS_CS_HIGH()    	GPIO_SetBits(TCS_GPIO_PORT, TCS_CS_PIN)

/** @defgroup STM3210C_EVAL_LCD_Exported_Functions
  * @{
  */ 
/* Function Control Graphic LCD ET-TFT240320TP-3.2 Rev.B (Driver SPFD5408A)*/
void Initial_GLCD_Hardware(void);	
unsigned char GLCD_SPI_Read_Write(unsigned char DataByte);
void GLCD_Write_Command(unsigned char GLCD_Command);
void GLCD_Write_Data(unsigned int GLCD_Data);
char Get_Status_Touch(void);
unsigned char TCS_SPI_Write(unsigned char DataByte);
void TCS_Average_X_Y(unsigned char num);
void bg_color(long bg_color);
void dec_to_ascii(long num);
    
//Start of Horizontal
void Initial_GLCD_Hor(void);
void TCS_Set_Matrix_Hor(void);
void Touch_Calibrate_Hor(void);
void TCS_SPI_Read_Hor(void);
void TCS_Get_Point_Hor(char num);
void plot_dot_Hor(unsigned long Xadd,unsigned long Yadd,unsigned long color);
void plot_mark_Hor(long x1,long y1,long x2,long y2,long color);
void text_7x11_Hor(char row,long adx,long ady,long fg_clr,long bg_clr);
void Line_Hor(long x_1,long y_1,long x_2,long y_2,char line_type,long color);
void Circle_Hor(long CX,long CY,char Radius,char tick,long color,char fill);
void Ellipse_Hor(unsigned int h,unsigned int k,
             long rx,long ry,char tick,long color,char fill);
void Rectan_Hor(long x1,long y1,long x2,long y2,
            char tick,long color,char fill);
void lcd_printStr_Hor(char *str,long cur_x,long cur_y,
                      long fg_color,long bg_color);
void lcd_print3Cha_Hor(char ch1,char ch2,char ch3,
                       long cur_x,long cur_y,long fg_color,long bg_color);
void plot_tab_Hor(unsigned long color);       
void button_build_Hor(long px,long py,long width,long high,
                      long c_bt,unsigned char *tx,char num_tx,long c_tx);
void plot_picture_Hor(const char *bmp,long xad,long yad,long width,long high); 
//End of Horizontal

//Start of Vertical
void Initial_GLCD_Ver(void);
void TCS_Set_Matrix_Ver(void);
void Touch_Calibrate_Ver(void);
void TCS_SPI_Read_Ver(void);
void TCS_Get_Point_Ver(char num);
void plot_dot_Ver(unsigned long Xadd,unsigned long Yadd,unsigned long color);
void plot_mark_Ver(long x1,long y1,long x2,long y2,long color);
void text_7x11_Ver(char row,long adx,long ady,long fg_clr,long bg_clr);
void Line_Ver(long x_1,long y_1,long x_2,long y_2,char line_type,long color);
void Circle_Ver(long CX,long CY,char Radius,char tick,long color,char fill);
void Ellipse_Ver(unsigned int h,unsigned int k,
                 long rx,long ry,char tick,long color,char fill);
void Rectan_Ver(long x1,long y1,long x2,long y2,
                char tick,long color,char fill);
void lcd_printStr_Ver(char *str,long cur_x,long cur_y,
                      long fg_color,long bg_color);
void lcd_print3Cha_Ver(char ch1,char ch2,char ch3,
                       long cur_x,long cur_y,long fg_color,long bg_color);
void plot_tab_Ver(unsigned long color);
void button_build_Ver(long px,long py,long width,long high,
                      long c_bt,unsigned char *tx,char num_tx,long c_tx);
void plot_picture_Ver(const char *bmp,long xad,long yad,long width,long high);  
//End of Vertical

#ifdef __cplusplus
}
#endif

#endif /* __ET_STM32F_ARM_KIT_GLCD_H */

/**
  * @}
  */ 
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
