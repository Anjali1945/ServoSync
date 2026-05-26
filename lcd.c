/*
 * lcd.c
 *
 *  Created on: 19-May-2026
 *      Author: Admin
 */
#include <stdio.h>
#include "lcd.h"

static void LCD_Enable(void)
{
    HAL_GPIO_WritePin(E_PORT, E_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(E_PORT, E_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
}

static void LCD_SendNibble(uint8_t nibble)
{
    HAL_GPIO_WritePin(D4_PORT, D4_PIN, (nibble >> 0) & 1);
    HAL_GPIO_WritePin(D5_PORT, D5_PIN, (nibble >> 1) & 1);
    HAL_GPIO_WritePin(D6_PORT, D6_PIN, (nibble >> 2) & 1);
    HAL_GPIO_WritePin(D7_PORT, D7_PIN, (nibble >> 3) & 1);
    LCD_Enable();
}

static void LCD_SendByte(uint8_t byte, uint8_t rs)
{
    HAL_GPIO_WritePin(RS_PORT, RS_PIN, rs);
    LCD_SendNibble(byte >> 4);   // send upper nibble
    LCD_SendNibble(byte & 0x0F); // send lower nibble
}

void LCD_Init(void)
{
    HAL_Delay(50);

    // Initialize sequence for 4-bit mode
    HAL_GPIO_WritePin(RS_PORT, RS_PIN, GPIO_PIN_RESET);

    LCD_SendNibble(0x03);
    HAL_Delay(5);
    LCD_SendNibble(0x03);
    HAL_Delay(1);
    LCD_SendNibble(0x03);
    HAL_Delay(1);
    LCD_SendNibble(0x02); // set 4-bit mode

    LCD_SendByte(0x28, 0); // 4-bit, 2 lines, 5x8 font
    LCD_SendByte(0x0C, 0); // display on, cursor off
    LCD_SendByte(0x06, 0); // entry mode
    LCD_SendByte(0x01, 0); // clear display
    HAL_Delay(2);
}

void LCD_Clear(void)
{
    LCD_SendByte(0x01, 0);
    HAL_Delay(2);
}

void LCD_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t address;
    if(row == 0)
        address = 0x80 + col;
    else
        address = 0xC0 + col;
    LCD_SendByte(address, 0);
}

void LCD_Print(char *str)
{
    while(*str)
    {
        LCD_SendByte(*str++, 1);
    }
}

void LCD_PrintNumber(int num)
{
    char buf[16];
    sprintf(buf, "%d", num);
    LCD_Print(buf);
}
