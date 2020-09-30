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

#include "../../Inc/driver/uart.h"
#include "../../Inc/driver/io.h"
#include "../../Inc/driver/cpu_parser.h"
#include "../../config.h"

const char *state_mode = "s";
const char *all_mode = "a";
bool is_preamble = true;
char text_to_send_cpu[16];

uint8_t csum_cpu;
uint8_t parser_mode = PARSER;

char data_cpu_rx[UART_RX_BUF_SIZE];
char data_cpu_cmd[UART_RX_BUF_SIZE];

uint8_t cnt_cpu = 0;

bool new_command = false;

enum
{
    START = 'S',
    STOP = 'P'
};

uint8_t CRC8_CPU(unsigned char *data)
{
    uint8_t csum = 0x00;
    uint8_t t = 0;
    while (data[t] != '*')
    {
        csum ^= data[t];
        t++;
    }
    //(csum | 0x80)
    return (csum | 0x80);
}

void cpu_parser(uint8_t data)
{
    if (parser_mode == PARSER)
    {
        if (data == '@')
        {
            cnt_cpu = 0;
            memset(&data_cpu_rx, '\0', sizeof(data_cpu_rx));
            data_cpu_rx[cnt_cpu] = data;
            cnt_cpu++;
            parser_mode = DATA;
            csum_cpu = data;
        }
    }
    else if (parser_mode == DATA)
    {
        //spew("DATA\n", data);
        if (data == '*')
        {
            parser_mode = CSUM;
            data_cpu_rx[cnt_cpu] = data;
            //verifica cnt_cpu < buf
        }
        else
        {
            data_cpu_rx[cnt_cpu] = data;
            cnt_cpu++;
            csum_cpu ^= data;
        }
    }
    else if (parser_mode == CSUM)
    {
        //if (csum_cpu == data)
        //{
        data_cpu_rx[cnt_cpu] = '\0';
        sprintf(data_cpu_cmd, "%s", data_cpu_rx);
        new_command = true;
        //}
        parser_mode = PARSER;
    }
}

void parse_cpu_data_rx(char *data_rx)
{
    spew("parse_cpu_data_rx: %s\n", data_rx);
    char *word = strtok(data_rx, ",");
    char pre_mode[2];
    sprintf(pre_mode, "%s", word);

    switch (pre_mode[1])
    {
    case START:
        word = strtok(NULL, ",");
        pre_mode[0] = word[0];
        pre_mode[1] = '\0';
        _cpuData.arg1 = atoi(pre_mode);
        spew("1 - %d\n", _cpuData.arg1);

        word = strtok(NULL, ",");
        char rx_arg2[16];
        sprintf(rx_arg2, "%s", word);
        rx_arg2[strlen(rx_arg2)] = '\0';

        _cpuData.arg2 = atoi(rx_arg2);
        spew("2 - %d\n", _cpuData.arg2);

        word = strtok(NULL, ",");
        char rx_arg3[16];
        sprintf(rx_arg3, "%s", word);
        rx_arg3[strlen(rx_arg3)] = '\0';

        _cpuData.arg3 = atoi(rx_arg3);
        spew("3 - %d\n", _cpuData.arg3);

        //DO STUFF!
        GPIO_SET(LED);
        break;

    case STOP:
        GPIO_CLR(LED);
        break;

    default:
        break;
    }
}

bool check_new_command(void)
{
    if (new_command)
    {
        return true;
    }
    else
    {
        return false;
    }
}

char* get_cpu_cmd() // NOT WORKING... :(
{
    return data_cpu_cmd;
}

void new_command_read()
{
    new_command = false;
}