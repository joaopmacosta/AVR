//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: Pedro Gonçalves                                                  *
//***************************************************************************

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdbool.h>

#include "drivers/uart.h"
#include "drivers/io.h"
#include "config.h"
#include "motor_parser.h"

char data_motor0_rx[UART_RX_BUF_SIZE];
char data_motor1_rx[UART_RX_BUF_SIZE];
char data_motor2_rx[UART_RX_BUF_SIZE];
char data_motor3_rx[UART_RX_BUF_SIZE];

uint8_t cnt_motor0 = 0;
uint8_t cnt_motor1 = 0;
uint8_t cnt_motor2 = 0;
uint8_t cnt_motor3 = 0;

char data_text_to_cpu[UART_RX_BUF_SIZE];

uint8_t csum_0, csum_1, csum_2, csum_3;

int rpm;
float volt;
float amp;
float temp;
uint8_t state[NUMBER_OF_MOTORS];

uint8_t
CRC8(unsigned char *data)
{
	uint8_t csum = 0x00;
    uint8_t t = 0;
    while(data[t] != '*')
    {
        csum ^= data[t];
        t++;
    }
    //(csum | 0x80)
	return (csum | 0x80);
}

void
init_motor_parser(void)
{
    for (uint8_t i = 0; i < NUMBER_OF_MOTORS; i++)
        state[i] = PARSER;
}

void
parse_data_rx(uint8_t id_motor, char *data_rx)
{
    memset(&data_text_to_cpu, '\0', sizeof(data_text_to_cpu));
    if(data_rx[1] == 'A')
    {
        sprintf(data_text_to_cpu, "$S,I%d,1,*", id_motor);
        UART_sendString(DEBUG, data_text_to_cpu);
        UART_sendChar(DEBUG, CRC8((unsigned char*)data_text_to_cpu));
        UART_sendChar(DEBUG, '\n');
    }
    else
    {
        rpm = 0;
        volt = 0;
        amp = 0;
        temp = 0;

        sscanf(data_rx, "&%d,%f,%f,%f,*", &rpm, &volt, &amp, &temp);

        sprintf(data_text_to_cpu, "$A,I%d,R%d,T%.2f,V%.2f,C%.2f,*", id_motor, rpm, temp, volt, amp);
        UART_sendString(DEBUG, data_text_to_cpu);
        UART_sendChar(DEBUG, CRC8((unsigned char*)data_text_to_cpu));
        UART_sendChar(DEBUG, '\n');
    }
}

void
parse_motor0(uint8_t data)
{
    if(state[0] == PARSER)
    {
        if(data == '&')
        {
            memset(&data_motor0_rx, '\0', sizeof(data_motor0_rx));
            data_motor0_rx[cnt_motor0] = data;
            cnt_motor0++;
            state[0] = DATA;
            csum_0 = data;
        }
    }
    else if(state[0] == DATA)
    {
        if(data == '*')
        {
            state[0] = CSUM;
            data_motor0_rx[cnt_motor0] = data;
            cnt_motor0 = 0;
        }
        else
        {
            data_motor0_rx[cnt_motor0] = data;
            cnt_motor0++;
            csum_0 ^= data;
        }
    }
    else if(state[0] == CSUM)
    {
        if((csum_0 | 0x80) == data)
        {
            parse_data_rx(0, data_motor0_rx);
        }

        state[0] = PARSER;
        gpio_tgl_np(&LED_MOTOR_0_PORT, LED_MOTOR_0_PIN);
    }
}

void
parse_motor1(uint8_t data)
{
    if(state[1] == PARSER)
    {
        if(data == '&')
        {
            memset(&data_motor1_rx, '\0', sizeof(data_motor1_rx));
            data_motor1_rx[cnt_motor1] = data;
            cnt_motor1++;
            state[1] = DATA;
            csum_1 = data;
        }
    }
    else if(state[1] == DATA)
    {
        if(data == '*')
        {
            state[1] = CSUM;
            data_motor1_rx[cnt_motor1] = data;
            cnt_motor1 = 0;
        }
        else
        {
            data_motor1_rx[cnt_motor1] = data;
            cnt_motor1++;
            csum_1 ^= data;
        }
    }
    else if(state[1] == CSUM)
    {
        if((csum_1 | 0x80) == data)
        {
            parse_data_rx(1, data_motor1_rx);
        }

        state[1] = PARSER;
        gpio_tgl_np(&LED_MOTOR_1_PORT, LED_MOTOR_1_PIN);
    }
}

void
parse_motor2(uint8_t data)
{
    if(state[2] == PARSER)
    {
        if(data == '&')
        {
            memset(&data_motor2_rx, '\0', sizeof(data_motor2_rx));
            data_motor2_rx[cnt_motor2] = data;
            cnt_motor2++;
            state[2] = DATA;
            csum_2 = data;
        }
    }
    else if(state[2] == DATA)
    {
        if(data == '*')
        {
            state[2] = CSUM;
            data_motor2_rx[cnt_motor2] = data;
            cnt_motor2 = 0;
        }
        else
        {
            data_motor2_rx[cnt_motor2] = data;
            cnt_motor2++;
            csum_2 ^= data;
        }
    }
    else if(state[2] == CSUM)
    {
        if((csum_2 | 0x80) == data)
        {
            parse_data_rx(2, data_motor2_rx);
        }

        state[2] = PARSER;
        gpio_tgl_np(&LED_MOTOR_2_PORT, LED_MOTOR_2_PIN);
    }
}

void
parse_motor3(uint8_t data)
{
    if(state[3] == PARSER)
    {
        if(data == '&')
        {
            memset(&data_motor3_rx, '\0', sizeof(data_motor3_rx));
            data_motor3_rx[cnt_motor3] = data;
            cnt_motor3++;
            state[3] = DATA;
            csum_3 = data;
        }
    }
    else if(state[3] == DATA)
    {
        if(data == '*')
        {
            state[3] = CSUM;
            data_motor3_rx[cnt_motor3] = data;
            cnt_motor3 = 0;
        }
        else
        {
            data_motor3_rx[cnt_motor3] = data;
            cnt_motor3++;
            csum_3 ^= data;
        }
    }
    else if(state[3] == CSUM)
    {
        if((csum_3 | 0x80) == data)
        {
            parse_data_rx(3, data_motor3_rx);
        }

        state[3] = PARSER;
        gpio_tgl_np(&LED_MOTOR_3_PORT, LED_MOTOR_3_PIN);
    }
}