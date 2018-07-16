/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "et_stm32f_arm_kit_glcd.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_dac.h"
#include "stm32f10x_it.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*---------------------------------------------------------------------------*/

#define pi 3.141592654
#define MIN_FREQUENCY   20
#define MAX_FREQUENCY   10001
#define MIN_AMPLITUDE		0.5
#define MAX_AMPLITUDE		3


DAC_InitTypeDef       			DAC_InitStructure;
TIM_TimeBaseInitTypeDef			TIM_TimeBaseStructure;
NVIC_InitTypeDef						NVIC_InitStructure;
EXTI_InitTypeDef						EXTI_InitStructure;

long divider, An, Bn, Cn, Dn, En, Fn, X, Y;	
long X, Y;

//char num1,num2[3]={'0'},num3;
char num1, num3, num2[3];
int i, k = 0, w = 0, p, size, index1 = 0, count = 0, count1 = 0;
float amp = 0.5, yn[100], wo,b = 0, freq = 20, num = 0, Value[5], ap = 0.5;
uint16_t output = 0,angle = 0;
//char value2[5] = {'0'};
char value2[5];

//long cr_x=16,cr_y=161,x1,y1,x2,y2,s_color=BRIGHT_YELLOW;
long cr_x = 16, cr_y = 161;



static __IO uint32_t TimingDelay;
__IO uint32_t TimeDisplay = 0;


void delay_ms(__IO uint32_t nTime);	 		
void ET_STM32_RCC_Configuration(void);		
void TimingDelay_Decrement(void);
void GPIO_Conf(void);
void SYSTICK_setup(void);
void EXTI_Configuration(void);
void TIM_Configuration(void);
void NVIC_Configuration(void);
void DAC_Configuration(void);
void Set_Param(int m);
void Display_Gen(void);

void Set_Param(int m){

	int o = 0;
	uint32_t length = 0;
	float a[3] = {0}, am;
	cr_x = 16;
	cr_y = 161;

	Rectan_Hor(5,235,310,133,3,BRIGHT_YELLOW,0);
	Rectan_Hor(11,230,304,139,5,BRIGHT_BLUE,0);
	
  
	Line_Hor(11,178,304,178,5,BRIGHT_BLUE);
	Rectan_Hor(16,177,299,144,1,WHITE,1);																					//Rectang White for Clear Text
 								   	
  // Button 
  button_build_Hor(5, 93, 50, 35, BT_BLUE, "1", 1, WHITE); 		 									//Button 1
  button_build_Hor(65, 93, 50, 35, BT_CYAN, "2", 1, WHITE);		   								//Button 2 
  button_build_Hor(125, 93, 50, 35, BT_RED, "3", 1, WHITE);											//Button 3
  button_build_Hor(5, 48, 50, 35, BT_MAGENTA, "4", 1, WHITE);										//Button 4									
	button_build_Hor(65, 48, 50, 35, BT_GREEN, "5", 1, WHITE);										//Button 5
  button_build_Hor(125, 48, 50, 35, BT_YELLOW, "6", 1, WHITE);									//Button 6
	button_build_Hor(5, 3, 50, 35, BT_BLUE, "7", 1, WHITE);										  	//Button 7
	button_build_Hor(65, 3, 50, 35, BT_CYAN, "8", 1, WHITE);										  //Button 8
	button_build_Hor(125, 3, 50, 35, BT_RED, "9", 1, WHITE);											//Button 9
	button_build_Hor(185, 3, 50, 35, BT_MAGENTA, "0", 1, WHITE);									//Button 0
	button_build_Hor(260, 93, 50, 35, BT_YELLOW, "SET", 3, WHITE);								//Button SET Value
	button_build_Hor(260, 48, 50, 35, BT_GREEN, "CLE", 3 , WHITE);								//Button CLEAR Value
	button_build_Hor(260 , 3, 50, 35, BT_YELLOW, "Back", 4, WHITE);								//Button Back to Menu
	
  Rectan_Hor(16, 225, 299, 183, 1, WHITE, 1); 																	//Clear Screen white color Positin Input Value
	
	if(m == 4){
		lcd_printStr_Hor("Current Frequency:        Hz", 20, 210, RED, WHITE);
		if(freq>=MIN_FREQUENCY)lcd_printStr_Hor(value2, 170, 210, RED, WHITE);
		else lcd_printStr_Hor("0", 170, 210, RED, WHITE);
		lcd_printStr_Hor("Set Frequency =        Hz", 20, 190, RED, WHITE);
	}
	else if (m == 2){
		button_build_Hor(185, 48, 50, 35, BT_MAGENTA, ".", 1, WHITE);
		lcd_printStr_Hor("Current Amplitude:        Vpp", 20, 210, RED, WHITE);
		if(amp>=MIN_AMPLITUDE)lcd_printStr_Hor(num2, 180, 210, RED, WHITE);
		else lcd_printStr_Hor("0", 170, 210, RED, WHITE);
		lcd_printStr_Hor("Set Amplitude =        Vpp", 20, 190, RED, WHITE);
	}
	
		while(1){
		
			if(Get_Status_Touch()){                 																		// return (1) if touch screen is detected.
				TCS_Get_Point_Hor(20);
				
				//check button 1,2,3,SET
				if((Y >= 93)&&(Y <= 128)){
					
					if((X >= 5)&&(X <= 55)){																								//Check X Position of Button "1"
						o++;
							if(m == 2){
								if(o <= 3){
							
									a[o - 1] = 1;
									num2[o - 1] = '1';
									lcd_printStr_Hor("1", cr_x, cr_y, BRIGHT_RED, no_bg);
									cr_x = cr_x + 10;	
								}
								else lcd_printStr_Hor("Input invalid only..CLE & SET Agin", cr_x, cr_y, BRIGHT_RED, WHITE);
							}
							if(m == 4){
								if(o<=4){
									Value[o - 1] = 1;
									value2[o - 1] = '1';
									lcd_printStr_Hor("1", cr_x, cr_y, BRIGHT_RED, no_bg); 					// Plot text "1"
									cr_x = cr_x + 10;			                            							//Position Next Text
								}
								else{ 			
									Rectan_Hor(16, 177, 299, 144, 1, WHITE, 1);
									cr_x = 16;
									lcd_printStr_Hor("Input invalid..CLE & SET Agin", cr_x, cr_y, BRIGHT_RED, no_bg); 
								}
							}
						while(Get_Status_Touch()); 																						//Protect Press Button Double
						X = 0;
					}
					if((X>=65)&&(X<=115)){																									//Check X Position of Button "2"
						o++;
						if(m == 2){
							if(o <= 3){
								a[o - 1] = 2;
								num2[o - 1] = '2';
								lcd_printStr_Hor("2", cr_x, cr_y, BRIGHT_RED, no_bg);
								cr_x = cr_x + 10;
							}
							else lcd_printStr_Hor("Input invalid only..CLE & SET Agin",cr_x,cr_y,BRIGHT_RED,WHITE);
						}
						if(m == 4){							
							if(o <= 4){
								Value[o-1] = 2;
								value2[o-1] = '2';
								// Show Text "1" 
								lcd_printStr_Hor("2", cr_x, cr_y, BRIGHT_RED, no_bg); 							// Plot text "2"
								cr_x = cr_x + 10;			                            									//Position Next Text 
							}
							else{ 
								Rectan_Hor(16, 177, 299, 144, 1, WHITE, 1);
								cr_x = 16;
								lcd_printStr_Hor("Input invalid only..CLE & SET Agin", cr_x, cr_y, BRIGHT_RED, no_bg); 
							}
						}
						while(Get_Status_Touch()); 																						//Protect Press Button Double
						X = 0;
					}
					if((X >= 125) && (X <= 175)){																						//Check X Position of Button "3" To Menu
						o++;
							if(m == 2){
								if(o <= 3){
									a[o - 1] = 3;
									num2[o - 1] = '3';
									lcd_printStr_Hor("3", cr_x, cr_y, BRIGHT_RED, no_bg);
									cr_x = cr_x + 10;	
								}
								else lcd_printStr_Hor("Input invalid only..CLE & SET Agin", cr_x, cr_y, BRIGHT_RED, WHITE);
							}
							
							if(m == 4){
								if(o <= 4){
									Value[o - 1] = 3;
									value2[o - 1] = '3'; 
									lcd_printStr_Hor("3", cr_x, cr_y, BRIGHT_RED, no_bg); 					// Plot text "3"
									cr_x = cr_x + 10;			                            							//Position Next Text 
								}
								else{ 
									Rectan_Hor(16, 177, 299, 144, 1, WHITE, 1);
									cr_x = 16;
									lcd_printStr_Hor("Input invalid..CLE & SET Agin", cr_x, cr_y, BRIGHT_RED, no_bg); 
								}
							}
						while(Get_Status_Touch()); 																					//Protect Press Button Double
						X = 0;
					}
					
					if((X >= 260) && (X <= 310)){																					//Check X Position of Button SET Value				
						o++;
							if(m == 2){																												//Check When Select SET Amplitude Menu		
								if(num2[1] == '.') am = a[0] + (a[2] * 0.1);
								else if(num2[0] == '.') am = a[1] * 0.1;
								else if(num2[0] > '0' && num2[1] > 0) am = 4;
								else am = a[0];
								if (am > MAX_AMPLITUDE || am < MIN_AMPLITUDE){ 
									Rectan_Hor(16, 177, 299, 144, 1, WHITE, 1);
									lcd_printStr_Hor("Input value is invalid! ", 16, 167, BRIGHT_RED, no_bg);
									lcd_printStr_Hor("CLE & SET Value Agian. ", 16, 150, BRIGHT_RED, no_bg);
									am = 0;
									while(1){
										if(Get_Status_Touch()){                 										// return (1) if touch screen is detected.
											TCS_Get_Point_Hor(20);
											if((Y >= 48) && (Y <= 83)){											
												if((X >= 260) && (X <= 310)){														//Check X Position of Button Clear Value											  
													Rectan_Hor(16, 177, 299, 144, 1, WHITE, 1);
													cr_x = 16; cr_y = 161; k = 0; o = 0;			
													break;
												}
											}
										}
									}
								}	
							else{ 
								amp = am;							
								lcd_printStr_Hor(num2, 170, 190, BRIGHT_RED, no_bg);
								Rectan_Hor(170, 225, 220, 205, 1, WHITE, 1);
								lcd_printStr_Hor(num2, 180, 210, RED, WHITE);
								o = 0;
							}
							}
						if(m == 4){
							Value[o - 1] = 'e';
							length = o - 1;					
							for (w = 0; w < 5; w++){ 
								if (Value[w] != 'e'){ 
										switch (length - w - 1){ 
											case 0:
											num += (Value[w] * 1);
											break;

											case 1:
											num += (Value[w] * 10);
											break;

											case 2:
											num += (Value[w] * 100);
											break;

											case 3:
											num += (Value[w] * 1000);
											break;
										}
								}
							}
						
							if (num > MAX_FREQUENCY || num < MIN_FREQUENCY){ 
									Rectan_Hor(16, 177, 299, 144, 1, WHITE, 1);
									lcd_printStr_Hor("Input value is invalid! ", 16, 167, BRIGHT_RED, no_bg);
									lcd_printStr_Hor("CLE & SET Value Agian! ", 16, 150, BRIGHT_RED, no_bg);
									o = 0;
									for(p = 0; p < 5; p++){Value[p] = 0; value2[p] = 0;}
									while(1){
										if(Get_Status_Touch()){                 													// return (1) if touch screen is detected.					  
											TCS_Get_Point_Hor(20);
											if((Y >= 48) && (Y <= 83)){
												if((X >= 260) && (X <= 310)){																	//Check X Position of Button Clear Value
													Rectan_Hor(16, 177, 299, 144, 1, WHITE, 1);
													cr_x = 16; cr_y = 161; num = 0;
													break;
												}
											}
										}
									}
							}	
						else{
							freq = num;
							if(freq == 10) freq += 0.5;
							lcd_printStr_Hor(value2, 165, 190, BRIGHT_RED, no_bg);
							Rectan_Hor(170, 225, 220, 205, 1, WHITE, 1);	
							lcd_printStr_Hor(value2, 185, 210, RED, WHITE);
							//num=0;																					
						}
						}
						while(Get_Status_Touch()); 																								//Protect Press Button Double	                
						X = 0;					
					}	
				}				
				//check button 4,5,6,.,CLE			
				if((Y >= 48) && (Y <= 83)){																										//Check Y Position Y Touch
					if((X >= 5) && (X <= 55)){																									//Check X Position Touch of Button "4"
						o++;		
						if(m == 2){
							if(o <= 3){
								a[o - 1] = 4;
								num2[o - 1] = '4';
								lcd_printStr_Hor("4", cr_x, cr_y, BRIGHT_RED, no_bg);
							}
							else lcd_printStr_Hor("Input invalid..CLE & SET Agin", cr_x, cr_y, BRIGHT_RED, WHITE);
						}
							
						if(m == 4){	
							if(o <= 4){
								Value[o - 1] = 4;
								value2[o - 1] = '4'; 
								lcd_printStr_Hor("4", cr_x, cr_y, BRIGHT_RED, no_bg); 							// Plot text "4"
								cr_x = cr_x + 10;			                            									//Position Next Text 
							}
							else{ 
								Rectan_Hor(16, 177, 299, 144, 1, WHITE, 1);
								cr_x = 16;
								lcd_printStr_Hor("Input invalid..CLE & SET Agin", cr_x, cr_y, BRIGHT_RED, no_bg); 
							}
						}
						while(Get_Status_Touch()); 																						//Protect Press Button Double
						X = 0;
					}				
					if((X >= 65) && (X <= 115)){																						//Check X Position Touch of Button "5"
						o++;
						if(m == 2){
							if(o <= 3){
								a[o - 1] = 5;
								num2[o - 1] = '5';
								lcd_printStr_Hor("5", cr_x, cr_y, BRIGHT_RED, no_bg);
								cr_x = cr_x + 10;
							}
							else lcd_printStr_Hor("Input invalid..CLE & SET Agin", cr_x, cr_y, BRIGHT_RED, WHITE);
						}						
						if(m==4){	
							if(o <= 4){
								Value[o - 1] = 5;
								value2[o - 1] = '5'; 
								lcd_printStr_Hor("5", cr_x, cr_y, BRIGHT_RED, no_bg); 						// Plot text "5"
								cr_x = cr_x + 10;			                            								//Position Next Text 
							}
							else{
								Rectan_Hor(16, 177, 299, 144, 1, WHITE, 1);
								cr_x = 16;
								lcd_printStr_Hor("Input invalid..CLE & SET Agin",cr_x,cr_y,BRIGHT_RED,no_bg); 
							}
						}
						while(Get_Status_Touch()); 																						//Protect Press Button Double
						X = 0;
					}	
					if((X >= 125) && (X <= 175)){																						//Check X Position Touch of Button "6"			
						o++;
						if(m == 2){							
							if(o <= 3){							
								a[o - 1] = 6;
								num2[o - 1] = '6';
								lcd_printStr_Hor("6", cr_x, cr_y, BRIGHT_RED, no_bg);
								cr_x = cr_x + 10;
							}
							else lcd_printStr_Hor("Input invalid..CLE & SET Agin",cr_x,cr_y,BRIGHT_RED,WHITE);
						}							
						if(m == 4){						
							if(o <= 4){							
								Value[o - 1] = 6;
								value2[o - 1] = '6'; 
								lcd_printStr_Hor("6", cr_x, cr_y, BRIGHT_RED, no_bg); 					// Plot text "6"
								cr_x = cr_x + 10;			                            							//Position Next Text 
							}
							else{ 
								Rectan_Hor(16, 177, 299, 144, 1, WHITE, 1);
								cr_x = 16;
								lcd_printStr_Hor("Input invalid..CLE & SET Agin", cr_x, cr_y, BRIGHT_RED, no_bg); 						
							}
						}
						while(Get_Status_Touch()); 																					//Protect Press Button Double
						X = 0;
					}
					if((X >= 185) && (X <= 235)){																					//Check X Position Touch of Button "."			
						o++;
						k++;
						if(m == 2){							
							if(k == 1){	
									num2[o - 1] = '.';							
									lcd_printStr_Hor(".", cr_x, cr_y, BRIGHT_RED, no_bg);
									cr_x = cr_x + 10;	
							}
									
						}
							
						while(Get_Status_Touch()); 																					//Protect Press Button Double
						X = 0;
					}
					if((X >= 260) && (X <= 310)){																					//Check X Position of Button Clear Value			  
						Rectan_Hor(16, 177, 299, 144, 1, WHITE, 1);
						Rectan_Hor(150, 200, 200, 183, 1, WHITE, 1); 
						Rectan_Hor(170, 225, 220, 205, 1, WHITE, 1);
				    o = 0; cr_x = 16; cr_y = 161;							
						if(m == 4){	
							num = 0;
							for(p = 0; p < 5; p++){
								Value[p] = 0; value2[p] = 0;
							}
						
						}
						if(m == 2){	
							am = 0; amp = 0; k = 0;
							for(p = 0; p < 3; p++){	
								a[p] = 0;
								num2[p] = 0;	
							}
						}
						
					}	
				}
				
				//check Button 7,8,9,Back 
				if((Y >= 3) && (Y <= 35)){																						//Check Y Position of Button Back To Menu 	
					if((X >= 260) && (X <= 310)){																				//Check X Position of Button Back To Menu
					  delay_ms(100);
				    bg_color(BLACK);																									//Clear Screen
						break;
					}
					if((X >= 5) && (X <= 55)){																					//Check X Position of Button "7" To Menu	
						o++;
						if(m == 2){
							if(o <= 3){
								a[o - 1] = 7;
								num2[o - 1] = '7';
								lcd_printStr_Hor("7", cr_x, cr_y, BRIGHT_RED, no_bg);
								cr_x = cr_x + 10;
							}
							else lcd_printStr_Hor("Input invalid..CLE & SET Agin", cr_x, cr_y, BRIGHT_RED, WHITE);
						}
							
						if(m == 4){	
							if(o <= 4){
								Value[o - 1] = 7;
								value2[o - 1] = '7'; 
								lcd_printStr_Hor("7", cr_x, cr_y, BRIGHT_RED, no_bg); 					// Plot text "7"
								cr_x = cr_x + 10;			                            							//Position Next Text 
							}
							else{ 
								Rectan_Hor(16, 177, 299, 144, 1, WHITE, 1);
								cr_x = 16;
								lcd_printStr_Hor("Input invalid..CLE & SET Agin", cr_x, cr_y, BRIGHT_RED, no_bg); 		
							}
						}
						while(Get_Status_Touch()); 																					//Protect Press Button Double
						X = 0;
					}
					if((X >= 65) && (X <= 115)){																					//Check X Position of Button "8" To Menu
						o++;
						if(m == 2){
							if(o <= 3){
								a[o - 1] = 8;
								num2[o - 1] = '8';
								lcd_printStr_Hor("8", cr_x, cr_y, BRIGHT_RED, no_bg);
								cr_x = cr_x + 10;
							}
							else lcd_printStr_Hor("Input invalid..CLE & SET Agin",cr_x,cr_y,BRIGHT_RED,WHITE);
						}
							
						if(m == 4){							
							if(o <= 4){		
								Value[o-1] = 8;
								value2[o-1] = '8'; 
								lcd_printStr_Hor("8", cr_x, cr_y, BRIGHT_RED, no_bg); 					// Plot text "8"
								cr_x = cr_x + 10;			                            							//Position Next Text 
							}
							else{ 
								Rectan_Hor(16, 177, 299, 144, 1, WHITE, 1);
								cr_x = 16;
								lcd_printStr_Hor("Input invalid..CLE & SET Agin", cr_x, cr_y, BRIGHT_RED, no_bg); 
							}
						}
						while(Get_Status_Touch()); 																					//Protect Press Button Double
						X = 0;
					}
					if((X >= 125) && (X <= 175)){																					//Check X Position Touch of Button "9"
						o++;
						if(m == 2){
							if(o <= 3){
									a[o - 1] = 9;
									num2[o - 1] = '9';
									lcd_printStr_Hor("9", cr_x, cr_y, BRIGHT_RED, no_bg);
									cr_x = cr_x + 10;
							}
							else lcd_printStr_Hor("Input invalid..CLE & SET Agin", cr_x, cr_y, BRIGHT_RED, WHITE);
						}
							
						if(m == 4){
							if(o <= 4){
									Value[o - 1] = 9;
									value2[o - 1] = '9'; 
									lcd_printStr_Hor("9", cr_x, cr_y, BRIGHT_RED, no_bg); 					// Plot text "9"
									cr_x = cr_x + 10;			                          			  				//Position Next Text 
							}
							else{
								Rectan_Hor(16, 177, 299, 144, 1, WHITE, 1);
								cr_x = 16;
								lcd_printStr_Hor("Input invalid..CLE & SET Agin", cr_x, cr_y, BRIGHT_RED, no_bg); 			
							}
						}
						while(Get_Status_Touch()); 																						//Protect Press Button Double
						X = 0;
					}
					if((X >= 185) && (X <= 235)){																						//Check X Position Touch of Button "0"
						o++;
						if(m == 2){
							if(o <= 3){	
								num2[o - 1] = '0';
								lcd_printStr_Hor("0", cr_x, cr_y, BRIGHT_RED, no_bg);
								cr_x = cr_x + 10;
							}
							else lcd_printStr_Hor("Input invalid..CLE & SET Agin", cr_x, cr_y, BRIGHT_RED, WHITE);
						}
							
						if(m == 4){
							if(o <= 4){
								Value[o - 1] = 0;
								value2[o - 1] = '0'; 
								lcd_printStr_Hor("0", cr_x, cr_y, BRIGHT_RED, no_bg); 						// Plot text "0"
								cr_x = cr_x + 10;			                            								//Position Next Text 
							}
							else{ 			
								Rectan_Hor(16, 177, 299, 144, 1, WHITE, 1);
								cr_x = 16;
								lcd_printStr_Hor("Input invalid..CLE & SET Agin", cr_x, cr_y, BRIGHT_RED, no_bg); 						
							}
						}	
						while(Get_Status_Touch()); 																						//Protect Press Button Double
						X = 0;
					}		
				}		
			}
		}	
}

void Display_Gen(){

	Rectan_Hor(1, 238, 318, 1, 5, BRIGHT_BLUE, 0);
	Line_Hor(6, 178, 313, 178, 5, BRIGHT_RED);
	Line_Hor(6, 83, 313, 83, 5, BRIGHT_RED);
	lcd_printStr_Hor("Digital Osciilator ", 100, 210, BLACK, WHITE); 
	lcd_printStr_Hor("Display  ", 100, 190, BLACK, WHITE);
	lcd_printStr_Hor("Frequency =        Hz", 30, 138, RED, WHITE);
	if(freq>=MIN_FREQUENCY)lcd_printStr_Hor(value2, 130, 138, RED,WHITE);
	else lcd_printStr_Hor("0", 130, 138, RED, WHITE);
	lcd_printStr_Hor("Amplitude =        Vpp", 30, 41, RED, WHITE);
	if(amp>=MIN_AMPLITUDE)lcd_printStr_Hor(num2, 130, 41, RED, WHITE);
	else lcd_printStr_Hor("0", 130, 41, RED, WHITE);
	button_build_Hor(263, 6, 50, 35, BT_YELLOW, "Back", 4, WHITE);													// Button-Back
	
	
	
		
	
	
	w = 2;
	
	//EXTI_Configuration();
	//TIM_Configuration();
	//NVIC_Configuration();

	while(1){
		yn[w] = -b * yn[w - 1] - yn[w - 2];
		angle = ((yn[w] + 1.0001) * (4096 / 2));
		DAC_SetChannel2Data(DAC_Align_12b_R,angle);
	
		if(w == 99){
			w = 1;
			yn[1] = yn[99];	
			yn[0] = yn[99-1];
		}
		w++;

		if(Get_Status_Touch()){                 																	// return (1) if touch screen is detected.	  
			TCS_Get_Point_Hor(20);
			if((Y >= 3) && (Y <= 35)){	
					if((X >= 263) && (X <= 313)){																				//Check X Position of Button Back To Menu
					  delay_ms(100);
				    bg_color(BLACK);																									//Clear Screen
						break;
					}
			}
		}
	}
}


int main(void){ 
  //char str_buf1[25];
  //char n,touch_mark_point=0;	
  //SystemInit();
	
  if(SysTick_Config(SystemFrequency / 1000)){
    while (1);
  }

  
  ET_STM32_RCC_Configuration();
  Initial_GLCD_Hardware();
  Initial_GLCD_Hor();
  Touch_Calibrate_Hor();
	
	GPIO_Conf();
	//SysTick_Config(9000);
	TIM_Configuration();
	DAC_Configuration();
	
	while(1){
		
	lcd_printStr_Hor("Digital Osciilator ", 100, 210, WHITE,BLACK); 
	lcd_printStr_Hor("Tap to Select Menu  ", 100, 190, WHITE,BLACK);
	Line_Hor(0, 178, 319, 178, 5, BRIGHT_RED);
	lcd_printStr_Hor("1.FREQUENCY ", 11, 152, YELLOW, BLACK);
	button_build_Hor(130, 138, 50, 35, BT_BLUE, "SET", 3, WHITE);
	lcd_printStr_Hor("2.Amplitude ", 11, 93, YELLOW, BLACK);
	button_build_Hor(130, 75, 50, 35, BT_BLUE, "SET", 3, WHITE);
	lcd_printStr_Hor("3.Display ", 11, 38, YELLOW, BLACK);
	button_build_Hor(130, 21, 50, 35, BT_BLUE, "SHOW", 4, WHITE);
	freq = num;
	ap = (amp / 5.2);
	if(amp == 3) freq = num + (num * (3) / 100);	
		while(1){	
			if(Get_Status_Touch()){                 													// return (1) if touch screen is detected.	  
				TCS_Get_Point_Hor(30);     
				if((X >= 130) && (X <= 180)){	
					if((Y >= 138) && (Y <= 173)){
						i = 4;
						delay_ms(100);
						bg_color(BLACK);                                                         	// Clear Screen
						Set_Param(i);		
						break;
					}
					if((Y >= 75) && (Y <= 110)){
						i = 2;
						delay_ms(100);
						bg_color(BLACK);                                                         	// Clear Screen
						Set_Param(i);
						break;
					}
					if((Y >= 21) && (Y <= 56)){		
						i = 3;
						delay_ms(100);
						bg_color(WHITE);                                                         	// Clear Screen		
						wo = (2 * pi * (freq) / 125840);
						yn[1] = -(ap) * sin(wo);
						yn[0] = -(ap) * sin(2 * wo);
						b = -2 * cos(wo);			
						Display_Gen();
						break;
					}		
				}  	 
			}	
		}		
	}
}		

void delay_ms(__IO uint32_t nTime){
	
  TimingDelay = nTime;

  while(TimingDelay != 0)
  {
  }
}

void TimingDelay_Decrement(void){

  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

void ET_STM32_RCC_Configuration(void){

  RCC_ClocksTypeDef RCC_ClockFreq;
  ErrorStatus HSEStartUpStatus;

   
  RCC_DeInit();
  RCC_HSEConfig(RCC_HSE_ON);
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS){
  
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    FLASH_SetLatency(FLASH_Latency_2);
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK2Config(RCC_HCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    RCC_PREDIV2Config(RCC_PREDIV2_Div5);
    RCC_PLL2Config(RCC_PLL2Mul_8);
    RCC_PLL2Cmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET)
    {}
    RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2, RCC_PREDIV1_Div5);
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);
    RCC_PLLCmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {}
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while (RCC_GetSYSCLKSource() != 0x08)
    {}
			
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  }
  RCC_GetClocksFreq(&RCC_ClockFreq);
}

void GPIO_Conf(void){

  GPIO_InitTypeDef GPIO_InitStructure;
	
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void DAC_Configuration(void){

	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;
	//DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
  DAC_Init(DAC_Channel_2, &DAC_InitStructure);
  DAC_Cmd(DAC_Channel_2, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}

void TIM_Configuration(void){

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
  TIM_TimeBaseStructure.TIM_Period = 1;          
  TIM_TimeBaseStructure.TIM_Prescaler = 35;       
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);
	//TIM_Cmd(TIM2, ENABLE);
}

/*void NVIC_Configuration(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}*/
/*void EXTI_Configuration(void)
{
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}*/


