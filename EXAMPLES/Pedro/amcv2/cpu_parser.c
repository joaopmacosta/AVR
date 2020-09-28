//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: Pedro Gonçalves                                                  *
//***************************************************************************

#include <stdio.h>
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
#include "cpu_parser.h"

const char *state_mode = "s";
const char *all_mode = "a";
bool is_preamble = true;
char text_to_send_cpu[16];

uint8_t csum_cpu;
uint8_t parser_mode = PARSER;

char data_cpu_rx[UART_RX_BUF_SIZE];

uint8_t cnt_cpu = 0;

uint8_t
CRC8_CPU(unsigned char *data)
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
init_cpu_parser(void)
{
    for(uint8_t i = 0; i < NUMBER_OF_MOTORS; i++)
    {
        _motorSpeedValues[i].actual_speed = 0;
        _motorSpeedValues[i].speed_target = 0;
    }
}

void
cpu_praser(uint8_t data)
{
    if(parser_mode == PARSER)
    {
        if(data == '@')
        {
            memset(&data_cpu_rx, '\0', sizeof(data_cpu_rx));
            data_cpu_rx[cnt_cpu] = data;
            cnt_cpu++;
            parser_mode = DATA;
            csum_cpu = data;
        }
    }
    else if(parser_mode == DATA)
    {
        if(data == '*')
        {
            parser_mode = CSUM;
            data_cpu_rx[cnt_cpu] = data;
            cnt_cpu = 0;
        }
        else
        {
            data_cpu_rx[cnt_cpu] = data;
            cnt_cpu++;
            csum_cpu ^= data;
        }
    }
    else if(parser_mode == CSUM)
    {
        if(csum_cpu == data)
        {
            parse_cpu_data_rx(data_cpu_rx);
        }

        parser_mode = PARSER;
    }
}

void
parse_cpu_data_rx(char * data_rx)
{
    char *word = strtok(data_rx, ",");
    char pre_mode[2];
    sprintf(pre_mode, "%s", word);

    if(pre_mode[1] == 'S')
    {
        word = strtok(NULL, ",");
        pre_mode[0] = word[0];
        pre_mode[1] = '\0';
        _cpuData.id_motor = atoi(pre_mode);

        word = strtok(NULL, ",");
        char rx_set_rpm[16];
        sprintf(rx_set_rpm, "%s", word);
        rx_set_rpm[strlen(rx_set_rpm)] = '\0';

        _cpuData.set_rpm = (int) (MAX_VALUE_SPEED * atof(rx_set_rpm));

        set_speed_taget(_cpuData.id_motor, _cpuData.set_rpm);
        set_rpm(_cpuData.id_motor);
    }
    else if(pre_mode[1] == 'R')
    {
        word = strtok(NULL, ",");
        pre_mode[0] = word[0];
        pre_mode[1] = '\0';
        _cpuData.id_motor = atoi(pre_mode);

        word = strtok(NULL, ",");
        if (word[0] == 's')
        {
            memset(&text_to_send_cpu, '\0', sizeof(text_to_send_cpu));
            sprintf(text_to_send_cpu, "$A,I%d,*", _cpuData.id_motor);
        }
        else if(word[0] == 'a')
        {
            memset(&text_to_send_cpu, '\0', sizeof(text_to_send_cpu));
            sprintf(text_to_send_cpu, "$R,I%d,*", _cpuData.id_motor);
        }

        switch (_cpuData.id_motor)
        {
            case 0:
                UART_sendString(MOTOR0, text_to_send_cpu);
                UART_sendChar(MOTOR0, CRC8_CPU((unsigned char *)text_to_send_cpu));
                UART_sendChar(MOTOR0, '\n');
                break;

            case 1:
                UART_sendString(MOTOR1, text_to_send_cpu);
                UART_sendChar(MOTOR1, CRC8_CPU((unsigned char *)text_to_send_cpu));
                UART_sendChar(MOTOR1, '\n');
                break;

            case 2:
                UART_sendString(MOTOR2, text_to_send_cpu);
                UART_sendChar(MOTOR2, CRC8_CPU((unsigned char *)text_to_send_cpu));
                UART_sendChar(MOTOR2, '\n');
                break;

            case 3:
                UART_sendString(MOTOR3, text_to_send_cpu);
                UART_sendChar(MOTOR3, CRC8_CPU((unsigned char *)text_to_send_cpu));
                UART_sendChar(MOTOR3, '\n');
                break;

            default:
                break;
        }
    }
}

void
set_speed_taget(int id, int value)
{
    switch(id)
    {
    case 0:
        if(value >= MIN_VALUE_SPEED && value <= MAX_VALUE_SPEED)
            _motorSpeedValues[id].speed_target = value;
        break;

    case 1:
        if(value >= MIN_VALUE_SPEED && value <= MAX_VALUE_SPEED)
            _motorSpeedValues[id].speed_target = value;
        break;

    case 2:
        if(value >= MIN_VALUE_SPEED && value <= MAX_VALUE_SPEED)
            _motorSpeedValues[id].speed_target = value;
        break;

    case 3:
        if(value >= MIN_VALUE_SPEED && value <= MAX_VALUE_SPEED)
            _motorSpeedValues[id].speed_target = value;
        break;

    default:
        break;
    }
}

void
set_rpm(int id)
{
    char text_to_send[UART_RX_BUF_SIZE];
    //int speed_value = pid_of_speed(_motorSpeedValues[id].actual_speed, _motorSpeedValues[id].speed_target);
    int speed_value = _motorSpeedValues[id].speed_target;
    sprintf(text_to_send, "$S,%d,*", speed_value);
    switch(id)
    {
    case 0:
        gpio_tgl_np(&LED_MOTOR_0_PORT, LED_MOTOR_0_PIN);
        UART_sendString(MOTOR0, text_to_send);
        UART_sendChar(MOTOR0, CRC8_CPU((unsigned char*)text_to_send));
        if(speed_value >= MIN_VALUE_SPEED && speed_value <= MAX_VALUE_SPEED)
            _motorSpeedValues[id].actual_speed = speed_value;
        break;

    case 1:
        gpio_tgl_np(&LED_MOTOR_1_PORT, LED_MOTOR_1_PIN);
        UART_sendString(MOTOR1, text_to_send);
        UART_sendChar(MOTOR1, CRC8_CPU((unsigned char*)text_to_send));
        if(speed_value >= MIN_VALUE_SPEED && speed_value <= MAX_VALUE_SPEED)
            _motorSpeedValues[id].actual_speed = speed_value;
        break;

    case 2:
        gpio_tgl_np(&LED_MOTOR_2_PORT, LED_MOTOR_2_PIN);
        UART_sendString(MOTOR2, text_to_send);
        UART_sendChar(MOTOR2, CRC8_CPU((unsigned char*)text_to_send));
        if(speed_value >= MIN_VALUE_SPEED && speed_value <= MAX_VALUE_SPEED)
            _motorSpeedValues[id].actual_speed = speed_value;
        break;

    case 3:
        gpio_tgl_np(&LED_MOTOR_3_PORT, LED_MOTOR_3_PIN);
        UART_sendString(MOTOR3, text_to_send);
        UART_sendChar(MOTOR3, CRC8_CPU((unsigned char*)text_to_send));
        if(speed_value >= MIN_VALUE_SPEED && speed_value <= MAX_VALUE_SPEED)
            _motorSpeedValues[id].actual_speed = speed_value;
        break;

    default:
        break;
    }
}

int
pid_of_speed(int actual, int target)
{
    int diff = 0;

    if(target > actual)
    {
        diff = abs((target/10) - (actual/10));

        if(diff > (JUMP_VALUE_SPEED_PID/10))
        {
            return (actual + JUMP_VALUE_SPEED_PID);
        }
        else
        {
            return target;
        }
    }
    else if (target < actual)
    {
        diff = abs((actual/10) - (target/10));

        if(diff > (JUMP_VALUE_SPEED_PID/10))
        {
            return (actual - JUMP_VALUE_SPEED_PID);
        }
        else
        {
            return target;
        }
    }

    return actual;
}