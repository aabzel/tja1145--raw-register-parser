
#ifndef GENERATED_PARSER_TJA1145_H
#define GENERATED_PARSER_TJA1145_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "parse_tja1145_regs.h"

extern uint16_t proc_reg_cnt;

bool parse_tja1145_reg (uint8_t reg_addr, FILE *out_file_prt);
char *tja1145_reg_2_name (uint8_t reg_addr);
#endif /*GENERATED_PARSER_TJA1145_H*/