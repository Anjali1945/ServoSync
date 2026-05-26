/*
 * lcd.h
 *
 *  Created on: 19-May-2026
 *      Author: Admin
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f4xx_hal.h"

// LCD pin definitions
#define RS_PIN GPIO_PIN_0
#define RS_PORT GPIOB
#define E_PIN GPIO_PIN_1
#define E_PORT GPIOB
#define D4_PIN GPIO_PIN_4
#define D4_PORT GPIOB
#define D5_PIN GPIO_PIN_5
#define D5_PORT GPIOB
#define D6_PIN GPIO_PIN_6
#define D6_PORT GPIOB
#define D7_PIN GPIO_PIN_7
#define D7_PORT GPIOB

// Function prototypes
void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_Print(char *str);
void LCD_PrintNumber(int num);

#endif /* LCD_H_ */
