#include "parse_tja1145_regs.h"
#include "tja1145_register_parser.h"

#include "convert.h"
#include "parse_regs.h"
#include "str_ops.h"
#include "utils.h"
#include "bit_utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

reg_chip8bit_t tja1145RegMap[255];

static bool init_tja1145_reg (void) {
    for(int reg_addr = 0 ; reg_addr < 255; reg_addr++) {
    	tja1145RegMap[reg_addr].reg_val = 0;
        tja1145RegMap[reg_addr].valid = false;
        strncpy(tja1145RegMap[reg_addr].reg_name,"Reserved", sizeof(tja1145RegMap[reg_addr].reg_name));
    }
    return true;
}

static bool load_tja1145_reg (uint8_t reg_addr, uint8_t reg_val) {
    bool res = false;
    tja1145RegMap[reg_addr].valid = true;
    tja1145RegMap[reg_addr].reg_val = reg_val;
    strcpy (tja1145RegMap[reg_addr].reg_name, tja1145_reg_2_name(reg_addr));
    return res;
}

bool parse_tja1145_regs_file (char *in_file_name, char *out_file_name) {
    printf ("\n%s()\n", __FUNCTION__);
    char curFileStr[500];
    bool res = false;
    init_tja1145_reg ();
    FILE *inFilePrt = NULL;
    printf ("\n>In file: [%s]", in_file_name);
    inFilePrt = fopen (in_file_name, "r");
    if (inFilePrt) {
        int line = 0;
        while (NULL != fgets (curFileStr, sizeof (curFileStr), inFilePrt)) {

#if DEBUG_IN_FILE_STR
            printf ("\n>[%s]", curFileStr);
#endif
            if ((REG_ADDR_LEN + REG_VAL16_LEN) < strlen (curFileStr)) {
                uint8_t reg8bitAddr;
                uint8_t reg8_bit_val;
                res = parse_8bit_reg_addr (curFileStr, strlen (curFileStr), &reg8bitAddr);
                if (true == res) {
                    res = try_canch_hex_uint8 (curFileStr, strlen (curFileStr), &reg8_bit_val);
                    if (true == res) {
                        load_tja1145_reg (reg8bitAddr, reg8_bit_val);
                    } else {
                        printf ("\n Unable to parse 16 bit reg val in [%s]", curFileStr);
                    }
                } else {
                    printf ("\n Unable to parse 8 bit reg addr in [%s]", curFileStr);
                }
            }
#if DEBUG_IN_FILE_STR
            printf ("\n[%x] [%x]", reg_addr, reg_val);
#endif
            line++;
        }
        fclose (inFilePrt);
        res = true;
    } else {
        printf ("\nUnable to open file [%s]", in_file_name);
    }

    FILE *out_file_prt = NULL;
    out_file_prt = fopen (out_file_name, "w");
    if (out_file_prt) {
        if (true == res) {
            uint8_t reg_8bit_addr;
            for (reg_8bit_addr = 0; reg_8bit_addr <= 31; reg_8bit_addr++) {
                parse_tja1145_reg (reg_8bit_addr, out_file_prt);
            }

            printf ("\n processed %u/%u registers %f%% remain %u registers",  proc_reg_cnt, TJA1145_REG_NUM,
                    cacl_percent ((float)proc_reg_cnt, TJA1145_REG_NUM), TJA1145_REG_NUM - proc_reg_cnt);
            printf ("\n processed %u/496 bits %7.2f%%", proc_reg_cnt * 8,
                    cacl_percent ((float)proc_reg_cnt * 8.0, TJA1145_REG_NUM * 8.0));

            fprintf (out_file_prt, "\n\n Support: aabzele@gmail.com Alexander Barunin");
            fclose (out_file_prt);
        }
    }

    return res;
}
