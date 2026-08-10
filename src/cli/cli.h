#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define CLI_LINE_BUF_MAX 128
#define CLI_CMD_LIST_MAX 32
#define CLI_CMD_ARG_MAX 16
#define CLI_HIST_MAX 10
typedef void (*cli_callback_t)(void); // type구조 정의
typedef enum
{
    CLI_STATE_NORMAL = 0,
    CLI_STATE_ESC_RCVD, // 알아서 1번
    CLI_STATE_BRACKET_RCVD
} cli_input_state_t; // cli_input_state_t로 선언가능

void cliInit(void);
void cliMain(void);
void cliPrintf(char *fmt, ...);
void cliAdd(char *cmd_str, void (*cmd_func)(uint8_t argc, char *argv[])); // 함수도 주소로 전달해줄수 있음(callback함수)

void cliSetCtrlHandler(cli_callback_t handler);