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

#include "../../Inc/driver/io.h"
#include "../../Inc/driver/uart.h"
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
    STOP = 'A'
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

/*bool read_new_command(void)
{
    if (new_command)
    {
        parse_cpu_data_rx(get_cpu_cmd());
        new_command = false;
        return true;
    }
    else
    {
        return false;
    }
}*/

void parse_cpu_data_rx(char *data_rx)
{
    spew("parse_cpu_data_rx: %s\n", data_rx);
    char *word = strtok(data_rx, ",");
    char pre_mode[2];
    sprintf(pre_mode, "%s", word);

    switch (pre_mode[1])
    {
    case START:
        spew("on\n");
        GPIO_SET(LED);
        _cpuData.cmd = atoi(pre_mode);

        word = strtok(NULL, ",");
        pre_mode[0] = word[0];
        pre_mode[1] = '\0';

        _cpuData.arg1 = atoi(pre_mode);

        //spew("CMD: %d | ARG: %d\n", _cpuData.cmd, _cpuData.arg1);

        //DO STUFF!
        break;

    case STOP:
        spew("off\n");
        GPIO_CLR(LED);
        break;

    default:

        break;
    }
}

char *get_cpu_buffer(void)
{
    return data_cpu_cmd;
}

bool is_new_command_available(void)
{
    return new_command;
}

void new_command_read_done(void)
{
    new_command = false;
}
