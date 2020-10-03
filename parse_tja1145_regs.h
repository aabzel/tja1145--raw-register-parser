#ifndef PARSE_TJA1145_REGS_H
#define PARSE_TJA1145_REGS_H

#include "custom_type.h"

#include <stdio.h>

#define UNDEF_REG_NAME "Undef_REG_NAME"
#define TJA1145_REG_NUM 36U

typedef struct xRegChip8bit_t {
    uint8_t reg_val;
    char reg_name[100];
    bool valid;
} reg_chip8bit_t;

extern reg_chip8bit_t tja1145RegMap[255];

bool parse_tja1145_regs_file (char *in_file_name, char *out_file_name);

#endif /* PARSE_TJA1145_REGS_H */
