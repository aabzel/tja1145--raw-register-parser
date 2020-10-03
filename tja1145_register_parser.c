
#include "tja1145_register_parser.h"

#include "convert.h"
#include "str_ops.h"

uint16_t proc_reg_cnt = 0;


static bool parse_tja1145_mode_control_register_1 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 1 == reg_addr ) {
        res = true;
    }
    code = (0x1f & (reg_val>>3));
    fprintf (out_file_prt,"\n    reg %02u bit 7-3: %u=0x%x  R reserved", reg_addr, code, code); 
    if(1==(0x7 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 2-0:1 RW Sleep mode", reg_addr); 
    }
    if(4==(0x7 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 2-0:4 RW Standby mode", reg_addr); 
    }
    if(7==(0x7 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 2-0:7 RW Normal mode", reg_addr); 
    }
    return res;
}

static bool parse_tja1145_main_status_register_3 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 3 == reg_addr ) {
        res = true;
    }
    if (0==(reg_val & (1<<7))) {
        fprintf (out_file_prt,"\n    reg %02u bit  7:0  R transition to Sleep mode triggered by an SPI command", reg_addr);
    }
    if (reg_val & (1<<7)) {
        fprintf (out_file_prt,"\n    reg %02u bit  7:1  R an undervoltage on VCC and/or VIO forced a transition to Sleep mode", reg_addr);
    }
    if (0==(reg_val & (1<<6))) {
        fprintf (out_file_prt,"\n    reg %02u bit  6:0  R IC temperature below overtemperature warning threshold", reg_addr);
    }
    if (reg_val & (1<<6)) {
        fprintf (out_file_prt,"\n    reg %02u bit  6:1  R IC temperature above overtemperature warning threshold", reg_addr);
    }
    if (0==(reg_val & (1<<5))) {
        fprintf (out_file_prt,"\n    reg %02u bit  5:0  R TJA1145 has entered Normal mode (after power-up)", reg_addr);
    }
    if (reg_val & (1<<5)) {
        fprintf (out_file_prt,"\n    reg %02u bit  5:1  R TJA1145 has powered up but has not yet switched to Normal mode", reg_addr);
    }
    code = (0x1f & (reg_val>>0));
    fprintf (out_file_prt,"\n    reg %02u bit 4-0: %u=0x%x  R reserved", reg_addr, code, code); 
    return res;
}

static bool parse_tja1145_system_event_capture_enable_register_4 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 4 == reg_addr ) {
        res = true;
    }
    code = (0x1f & (reg_val>>3));
    fprintf (out_file_prt,"\n    reg %02u bit 7-3: %u=0x%x  R reserved", reg_addr, code, code); 
    if (0==(reg_val & (1<<2))) {
        fprintf (out_file_prt,"\n    reg %02u bit  2:0  R overtemperature warning disabled", reg_addr);
    }
    if (reg_val & (1<<2)) {
        fprintf (out_file_prt,"\n    reg %02u bit  2:1  R overtemperature warning enabled", reg_addr);
    }
    if (0==(reg_val & (1<<1))) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:0  R SPI failure detection disabled", reg_addr);
    }
    if (reg_val & (1<<1)) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:1  R SPI failure detection enabled", reg_addr);
    }
    if (0==(reg_val & (1<<0))) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:0  R reserved", reg_addr);
    }
    if (reg_val & (1<<0)) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:1  R reserved", reg_addr);
    }
    return res;
}

static bool parse_tja1145_memory_0_register_6 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 6 == reg_addr ) {
        res = true;
    }
    return res;
}

static bool parse_tja1145_memory_1_register_7 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 7 == reg_addr ) {
        res = true;
    }
    return res;
}

static bool parse_tja1145_memory_2_register_8 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 8 == reg_addr ) {
        res = true;
    }
    return res;
}

static bool parse_tja1145_memory_3_register_9 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 9 == reg_addr ) {
        res = true;
    }
    return res;
}

static bool parse_tja1145_lock_control_register_10 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 10 == reg_addr ) {
        res = true;
    }
    if (0==(reg_val & (1<<7))) {
        fprintf (out_file_prt,"\n    reg %02u bit  7:0  R reserved", reg_addr);
    }
    if (reg_val & (1<<7)) {
        fprintf (out_file_prt,"\n    reg %02u bit  7:1  R reserved", reg_addr);
    }
    if (0==(reg_val & (1<<6))) {
        fprintf (out_file_prt,"\n    reg %02u bit  6:0  R SPI write-access enabled address area 0x68 to 0x6F", reg_addr);
    }
    if (reg_val & (1<<6)) {
        fprintf (out_file_prt,"\n    reg %02u bit  6:1  R SPI write-access disabled address area 0x68 to 0x6F", reg_addr);
    }
    if (0==(reg_val & (1<<5))) {
        fprintf (out_file_prt,"\n    reg %02u bit  5:0  R SPI write-access enabled address area 0x50 to 0x5F", reg_addr);
    }
    if (reg_val & (1<<5)) {
        fprintf (out_file_prt,"\n    reg %02u bit  5:1  R SPI write-access disabled address area 0x50 to 0x5F", reg_addr);
    }
    if (0==(reg_val & (1<<4))) {
        fprintf (out_file_prt,"\n    reg %02u bit  4:0  R SPI write-access enabled address area 0x40 to 0x4F", reg_addr);
    }
    if (reg_val & (1<<4)) {
        fprintf (out_file_prt,"\n    reg %02u bit  4:1  R SPI write-access disabled address area 0x40 to 0x4F", reg_addr);
    }
    if (0==(reg_val & (1<<3))) {
        fprintf (out_file_prt,"\n    reg %02u bit  3:0  R SPI write-access enabled address area 0x30 to 0x3F", reg_addr);
    }
    if (reg_val & (1<<3)) {
        fprintf (out_file_prt,"\n    reg %02u bit  3:1  R SPI write-access disabled address area 0x30 to 0x3F", reg_addr);
    }
    if (0==(reg_val & (1<<2))) {
        fprintf (out_file_prt,"\n    reg %02u bit  2:0  R SPI write-access enabled address area 0x20 to 0x2F", reg_addr);
    }
    if (reg_val & (1<<2)) {
        fprintf (out_file_prt,"\n    reg %02u bit  2:1  R SPI write-access disabled address area 0x20 to 0x2F", reg_addr);
    }
    if (0==(reg_val & (1<<1))) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:0  R SPI write-access enabled address area 0x10 to 0x1F", reg_addr);
    }
    if (reg_val & (1<<1)) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:1  R SPI write-access disabled address area 0x10 to 0x1F", reg_addr);
    }
    if (0==(reg_val & (1<<0))) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:0  R SPI write-access enabled area 0x06 to 0x09", reg_addr);
    }
    if (reg_val & (1<<0)) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:1  R SPI write-access disabled area 0x06 to 0x09", reg_addr);
    }
    return res;
}

static bool parse_tja1145_can_control_register_32 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 32 == reg_addr ) {
        res = true;
    }
    if (0==(reg_val & (1<<7))) {
        fprintf (out_file_prt,"\n    reg %02u bit  7:0  R reserved", reg_addr);
    }
    if (reg_val & (1<<7)) {
        fprintf (out_file_prt,"\n    reg %02u bit  7:1  R reserved", reg_addr);
    }
    if (0==(reg_val & (1<<6))) {
        fprintf (out_file_prt,"\n    reg %02u bit  6:0  RW CAN FD tolerance disabled", reg_addr);
    }
    if (reg_val & (1<<6)) {
        fprintf (out_file_prt,"\n    reg %02u bit  6:1  RW CAN FD tolerance enabled", reg_addr);
    }
    if (0==(reg_val & (1<<5))) {
        fprintf (out_file_prt,"\n    reg %02u bit  5:0  RW partial networking register configuration invalid (wake-up via standard wake-up pattern only)", reg_addr);
    }
    if (reg_val & (1<<5)) {
        fprintf (out_file_prt,"\n    reg %02u bit  5:1  RW partial networking registers configured successfully", reg_addr);
    }
    if (0==(reg_val & (1<<4))) {
        fprintf (out_file_prt,"\n    reg %02u bit  4:0  RW disable CAN selective wake-up", reg_addr);
    }
    if (reg_val & (1<<4)) {
        fprintf (out_file_prt,"\n    reg %02u bit  4:1  RW enable CAN selective wake-up", reg_addr);
    }
    code = (0x3 & (reg_val>>2));
    fprintf (out_file_prt,"\n    reg %02u bit 3-2: %u=0x%x  R reserved", reg_addr, code, code); 
    if(0==(0x3 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 1-0:0 RW Offline mode", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 1-0:1 RW Active mode (when the TJA1145 is in Normal mode); VCC 90 %% undervoltage detection active", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 1-0:2 RW Active mode (when the TJA1145 is in Normal mode); VCC undervoltage detection inactive; TJA1145 switches from Normal to Off mode when VBAT < Vuvd(CAN)", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 1-0:3 RW Listen-only mode", reg_addr); 
    }
    return res;
}

static bool parse_tja1145_transceiver_status_register_34 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 34 == reg_addr ) {
        res = true;
    }
    if (0==(reg_val & (1<<7))) {
        fprintf (out_file_prt,"\n    reg %02u bit  7:0  R CAN transceiver not in Active mode", reg_addr);
    }
    if (reg_val & (1<<7)) {
        fprintf (out_file_prt,"\n    reg %02u bit  7:1  R CAN transceiver in Active mode", reg_addr);
    }
    if (0==(reg_val & (1<<6))) {
        fprintf (out_file_prt,"\n    reg %02u bit  6:0  R no CAN partial networking error detected (PNFDE = 0 AND PNCOK = 1)", reg_addr);
    }
    if (reg_val & (1<<6)) {
        fprintf (out_file_prt,"\n    reg %02u bit  6:1  R    CAN partial networking error detected (PNFDE = 1 OR  PNCOK = 0); wake-up via standard wake-up pattern only", reg_addr);
    }
    if (0==(reg_val & (1<<5))) {
        fprintf (out_file_prt,"\n    reg %02u bit  5:0  R CAN partial networking configuration error detected (PNCOK = 0)", reg_addr);
    }
    if (reg_val & (1<<5)) {
        fprintf (out_file_prt,"\n    reg %02u bit  5:1  R CAN partial networking configuration OK (PNCOK = 1)", reg_addr);
    }
    if (0==(reg_val & (1<<4))) {
        fprintf (out_file_prt,"\n    reg %02u bit  4:0  R CAN partial networking oscillator not running at target frequency ", reg_addr);
    }
    if (reg_val & (1<<4)) {
        fprintf (out_file_prt,"\n    reg %02u bit  4:1  R CAN partial networking oscillator running at target frequency  ", reg_addr);
    }
    if (0==(reg_val & (1<<3))) {
        fprintf (out_file_prt,"\n    reg %02u bit  3:0  R CAN bus active (communication detected on bus)", reg_addr);
    }
    if (reg_val & (1<<3)) {
        fprintf (out_file_prt,"\n    reg %02u bit  3:1  R CAN bus inactive (for longer than tto(silence)", reg_addr);
    }
    if (0==(reg_val & (1<<2))) {
        fprintf (out_file_prt,"\n    reg %02u bit  2:0  R reserved", reg_addr);
    }
    if (reg_val & (1<<2)) {
        fprintf (out_file_prt,"\n    reg %02u bit  2:1  R reserved", reg_addr);
    }
    if (0==(reg_val & (1<<1))) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:0  R VCC is above the undervoltage detection threshold", reg_addr);
    }
    if (reg_val & (1<<1)) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:1  R VCC is below the undervoltage detection threshold", reg_addr);
    }
    if (0==(reg_val & (1<<0))) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:0  R no TXD dominant time-out event detected", reg_addr);
    }
    if (reg_val & (1<<0)) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:1  R CAN transmitter disabled due to a TXD dominant time-out event", reg_addr);
    }
    return res;
}

static bool parse_tja1145_transceiver_event_capture_enable_register_35 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 35 == reg_addr ) {
        res = true;
    }
    code = (0x7 & (reg_val>>5));
    fprintf (out_file_prt,"\n    reg %02u bit 7-5: %u=0x%x  R reserved", reg_addr, code, code); 
    if (0==(reg_val & (1<<4))) {
        fprintf (out_file_prt,"\n    reg %02u bit  4:0  RW CAN-bus silence detection disabled", reg_addr);
    }
    if (reg_val & (1<<4)) {
        fprintf (out_file_prt,"\n    reg %02u bit  4:1  RW CAN-bus silence detection enabled", reg_addr);
    }
    code = (0x3 & (reg_val>>2));
    fprintf (out_file_prt,"\n    reg %02u bit 3-2: %u=0x%x  R reserved", reg_addr, code, code); 
    if (0==(reg_val & (1<<1))) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:0  R CAN failure detection disabled", reg_addr);
    }
    if (reg_val & (1<<1)) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:1  R CAN failure detection enabled", reg_addr);
    }
    if (0==(reg_val & (1<<0))) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:0  R CAN wake-up detection disabled", reg_addr);
    }
    if (reg_val & (1<<0)) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:1  R CAN wake-up detection enabled", reg_addr);
    }
    return res;
}

static bool parse_tja1145_data_rate_register_38 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 38 == reg_addr ) {
        res = true;
    }
    code = (0x1f & (reg_val>>3));
    fprintf (out_file_prt,"\n    reg %02u bit 7-3: %u=0x%x  R reserved", reg_addr, code, code); 
    if(0==(0x7 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 2-0:0 RW 50 kbit/s", reg_addr); 
    }
    if(1==(0x7 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 2-0:1 RW 100 kbit/s", reg_addr); 
    }
    if(2==(0x7 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 2-0:2 RW 125 kbit/s", reg_addr); 
    }
    if(3==(0x7 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 2-0:3 RW 250 kbit/s", reg_addr); 
    }
    if(4==(0x7 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 2-0:4 RW 500 kbit/s", reg_addr); 
    }
    if(5==(0x7 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 2-0:5 RW 500 kbit/s", reg_addr); 
    }
    if(6==(0x7 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 2-0:6 RW 500 kbit/s", reg_addr); 
    }
    if(7==(0x7 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 2-0:7 RW 1000 kbit/s", reg_addr); 
    }
    return res;
}

static bool parse_tja1145_id_registers_0_register_39 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 39 == reg_addr ) {
        res = true;
    }
    code = (0xff & (reg_val>>0));
    fprintf (out_file_prt,"\n    reg %02u bit 7-0: %u=0x%x  RW ID7:ID0", reg_addr, code, code); 
    return res;
}

static bool parse_tja1145_id_registers_1_register_40 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 40 == reg_addr ) {
        res = true;
    }
    code = (0xff & (reg_val>>0));
    fprintf (out_file_prt,"\n    reg %02u bit 7-0: %u=0x%x  RW ID15:ID08", reg_addr, code, code); 
    return res;
}

static bool parse_tja1145_id_registers_2_register_41 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 41 == reg_addr ) {
        res = true;
    }
    code = (0x3f & (reg_val>>2));
    fprintf (out_file_prt,"\n    reg %02u bit 7-2: %u=0x%x  RW ID23:ID18", reg_addr, code, code); 
    code = (0x3 & (reg_val>>0));
    fprintf (out_file_prt,"\n    reg %02u bit 1-0: %u=0x%x  RW ID17:ID16", reg_addr, code, code); 
    return res;
}

static bool parse_tja1145_id_registers_3_register_42 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 42 == reg_addr ) {
        res = true;
    }
    code = (0x7 & (reg_val>>5));
    fprintf (out_file_prt,"\n    reg %02u bit 7-5: %u=0x%x  R reserved", reg_addr, code, code); 
    code = (0x1f & (reg_val>>0));
    fprintf (out_file_prt,"\n    reg %02u bit 4-0: %u=0x%x  RW ID28:ID24", reg_addr, code, code); 
    return res;
}

static bool parse_tja1145_id_mask_registers_0_register_43 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 43 == reg_addr ) {
        res = true;
    }
    code = (0xff & (reg_val>>0));
    fprintf (out_file_prt,"\n    reg %02u bit 7-0: %u=0x%x  RW M7:M0", reg_addr, code, code); 
    return res;
}

static bool parse_tja1145_id_mask_registers_1_register_44 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 44 == reg_addr ) {
        res = true;
    }
    code = (0xff & (reg_val>>0));
    fprintf (out_file_prt,"\n    reg %02u bit 7-0: %u=0x%x  RW M15:M8", reg_addr, code, code); 
    return res;
}

static bool parse_tja1145_id_mask_registers_2_register_45 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 45 == reg_addr ) {
        res = true;
    }
    code = (0x3f & (reg_val>>2));
    fprintf (out_file_prt,"\n    reg %02u bit 7-2: %u=0x%x  RW M23:M18", reg_addr, code, code); 
    code = (0x3 & (reg_val>>0));
    fprintf (out_file_prt,"\n    reg %02u bit 1-0: %u=0x%x  RW M17:M16", reg_addr, code, code); 
    return res;
}

static bool parse_tja1145_id_mask_registers_3_register_46 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 46 == reg_addr ) {
        res = true;
    }
    code = (0x7 & (reg_val>>5));
    fprintf (out_file_prt,"\n    reg %02u bit 7-5: %u=0x%x  R reserved", reg_addr, code, code); 
    code = (0x1f & (reg_val>>0));
    fprintf (out_file_prt,"\n    reg %02u bit 4-0: %u=0x%x  RW M28:M24", reg_addr, code, code); 
    return res;
}

static bool parse_tja1145_frame_control_register_47 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 47 == reg_addr ) {
        res = true;
    }
    if (0==(reg_val & (1<<7))) {
        fprintf (out_file_prt,"\n    reg %02u bit  7:0  RW standard frame format (11-bit)", reg_addr);
    }
    if (reg_val & (1<<7)) {
        fprintf (out_file_prt,"\n    reg %02u bit  7:1  RW extended frame format (29-bit)", reg_addr);
    }
    if (0==(reg_val & (1<<6))) {
        fprintf (out_file_prt,"\n    reg %02u bit  6:0  R data length code and data field are ‘don’t care’ for wake-up", reg_addr);
    }
    if (reg_val & (1<<6)) {
        fprintf (out_file_prt,"\n    reg %02u bit  6:1  R data length code and data field are evaluated at wake-up", reg_addr);
    }
    code = (0x3 & (reg_val>>4));
    fprintf (out_file_prt,"\n    reg %02u bit 5-4: %u=0x%x  R reserved", reg_addr, code, code); 
    if(0==(0xf & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-0:0 RW 0 bytes in CAN frame", reg_addr); 
    }
    if(1==(0xf & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-0:1 RW 1 bytes in CAN frame", reg_addr); 
    }
    if(2==(0xf & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-0:2 RW 2 bytes in CAN frame", reg_addr); 
    }
    if(3==(0xf & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-0:3 RW 3 bytes in CAN frame", reg_addr); 
    }
    if(4==(0xf & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-0:4 RW 4 bytes in CAN frame", reg_addr); 
    }
    if(5==(0xf & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-0:5 RW 5 bytes in CAN frame", reg_addr); 
    }
    if(6==(0xf & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-0:6 RW 6 bytes in CAN frame", reg_addr); 
    }
    if(7==(0xf & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-0:7 RW 7 bytes in CAN frame", reg_addr); 
    }
    if(8==(0xf & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-0:8 RW 8 bytes in CAN frame", reg_addr); 
    }
    if(9==(0xf & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-0:9 RW tolerated, 8 bytes expected; DM0 ignored", reg_addr); 
    }
    if(1==(0xf & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-0:1 RW tolerated, 8 bytes expected; DM0 ignored", reg_addr); 
    }
    if(1==(0xf & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-0:1 RW tolerated, 8 bytes expected; DM0 ignored", reg_addr); 
    }
    if(1==(0xf & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-0:1 RW tolerated, 8 bytes expected; DM0 ignored", reg_addr); 
    }
    if(1==(0xf & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-0:1 RW tolerated, 8 bytes expected; DM0 ignored", reg_addr); 
    }
    if(1==(0xf & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-0:1 RW tolerated, 8 bytes expected; DM0 ignored", reg_addr); 
    }
    if(1==(0xf & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-0:1 RW tolerated, 8 bytes expected; DM0 ignored", reg_addr); 
    }
    return res;
}

static bool parse_tja1145_wake_status_register_75 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 75 == reg_addr ) {
        res = true;
    }
    code = (0x3f & (reg_val>>2));
    fprintf (out_file_prt,"\n    reg %02u bit 7-2: %u=0x%x  R reserved", reg_addr, code, code); 
    if (0==(reg_val & (1<<1))) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:0  R voltage on WAKE pin below switching threshold (Vth(sw))", reg_addr);
    }
    if (reg_val & (1<<1)) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:1  R voltage on WAKE pin above switching threshold (Vth(sw))", reg_addr);
    }
    if (0==(reg_val & (1<<0))) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:0  R reserved", reg_addr);
    }
    if (reg_val & (1<<0)) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:1  R reserved", reg_addr);
    }
    return res;
}

static bool parse_tja1145_wake_pin_event_capture_enable_register_76 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 76 == reg_addr ) {
        res = true;
    }
    code = (0x3f & (reg_val>>2));
    fprintf (out_file_prt,"\n    reg %02u bit 7-2: %u=0x%x  R reserved", reg_addr, code, code); 
    if (0==(reg_val & (1<<1))) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:0  R rising-edge detection on WAKE pin disabled", reg_addr);
    }
    if (reg_val & (1<<1)) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:1  R rising-edge detection on WAKE pin enabled", reg_addr);
    }
    if (0==(reg_val & (1<<0))) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:0  R falling-edge detection on WAKE pin disabled", reg_addr);
    }
    if (reg_val & (1<<0)) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:1  R falling-edge detection on WAKE pin enabled", reg_addr);
    }
    return res;
}

static bool parse_tja1145_global_event_status_register_96 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 96 == reg_addr ) {
        res = true;
    }
    code = (0xf & (reg_val>>4));
    fprintf (out_file_prt,"\n    reg %02u bit 7-4: %u=0x%x  R reserved", reg_addr, code, code); 
    if (0==(reg_val & (1<<3))) {
        fprintf (out_file_prt,"\n    reg %02u bit  3:0  R no pending WAKE pin event", reg_addr);
    }
    if (reg_val & (1<<3)) {
        fprintf (out_file_prt,"\n    reg %02u bit  3:1  R WAKE pin event pending at address 0x64", reg_addr);
    }
    if (0==(reg_val & (1<<2))) {
        fprintf (out_file_prt,"\n    reg %02u bit  2:0  R no pending transceiver event", reg_addr);
    }
    if (reg_val & (1<<2)) {
        fprintf (out_file_prt,"\n    reg %02u bit  2:1  R transceiver event pending at address 0x63", reg_addr);
    }
    if (0==(reg_val & (1<<1))) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:0  R reserved", reg_addr);
    }
    if (reg_val & (1<<1)) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:1  R reserved", reg_addr);
    }
    if (0==(reg_val & (1<<0))) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:0  R no pending system event", reg_addr);
    }
    if (reg_val & (1<<0)) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:1  R system event pending at address 0x61", reg_addr);
    }
    return res;
}

static bool parse_tja1145_system_event_status_register_97 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 97 == reg_addr ) {
        res = true;
    }
    code = (0x7 & (reg_val>>5));
    fprintf (out_file_prt,"\n    reg %02u bit 7-5: %u=0x%x  R reserved", reg_addr, code, code); 
    if (0==(reg_val & (1<<4))) {
        fprintf (out_file_prt,"\n    reg %02u bit  4:0  RW no recent battery power-on", reg_addr);
    }
    if (reg_val & (1<<4)) {
        fprintf (out_file_prt,"\n    reg %02u bit  4:1  RW the TJA1145 has left Off mode after battery power-on", reg_addr);
    }
    if (0==(reg_val & (1<<3))) {
        fprintf (out_file_prt,"\n    reg %02u bit  3:0  R reserved", reg_addr);
    }
    if (reg_val & (1<<3)) {
        fprintf (out_file_prt,"\n    reg %02u bit  3:1  R reserved", reg_addr);
    }
    if (0==(reg_val & (1<<2))) {
        fprintf (out_file_prt,"\n    reg %02u bit  2:0  RW overtemperature not detected", reg_addr);
    }
    if (reg_val & (1<<2)) {
        fprintf (out_file_prt,"\n    reg %02u bit  2:1  RW the global chip temperature has exceeded the overtemperature warning threshold (Tth(warn)otp)", reg_addr);
    }
    if (0==(reg_val & (1<<1))) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:0  RW no SPI failure detected", reg_addr);
    }
    if (reg_val & (1<<1)) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:1  RW SPI failure detected", reg_addr);
    }
    if (0==(reg_val & (1<<0))) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:0  R reserved", reg_addr);
    }
    if (reg_val & (1<<0)) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:1  R reserved", reg_addr);
    }
    return res;
}

static bool parse_tja1145_transceiver_event_status_register_99 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 99 == reg_addr ) {
        res = true;
    }
    code = (0x3 & (reg_val>>6));
    fprintf (out_file_prt,"\n    reg %02u bit 7-6: %u=0x%x  R reserved", reg_addr, code, code); 
    if (0==(reg_val & (1<<5))) {
        fprintf (out_file_prt,"\n    reg %02u bit  5:0  RW no partial networking frame detection error detected", reg_addr);
    }
    if (reg_val & (1<<5)) {
        fprintf (out_file_prt,"\n    reg %02u bit  5:1  RW partial networking frame detection error detected", reg_addr);
    }
    if (0==(reg_val & (1<<4))) {
        fprintf (out_file_prt,"\n    reg %02u bit  4:0  RW CAN-bus active", reg_addr);
    }
    if (reg_val & (1<<4)) {
        fprintf (out_file_prt,"\n    reg %02u bit  4:1  RW no activity on CAN-bus for tto(silence)", reg_addr);
    }
    code = (0x3 & (reg_val>>2));
    fprintf (out_file_prt,"\n    reg %02u bit 3-2: %u=0x%x  R reserved", reg_addr, code, code); 
    if (0==(reg_val & (1<<1))) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:0  RW no CAN failure detected", reg_addr);
    }
    if (reg_val & (1<<1)) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:1  RW CAN failure event detected", reg_addr);
    }
    if (0==(reg_val & (1<<0))) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:0  RW no CAN wake-up event detected", reg_addr);
    }
    if (reg_val & (1<<0)) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:1  RW CAN wake-up event detected", reg_addr);
    }
    return res;
}

static bool parse_tja1145_wake_pin_event_status_register_100 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 100 == reg_addr ) {
        res = true;
    }
    code = (0x3f & (reg_val>>2));
    fprintf (out_file_prt,"\n    reg %02u bit 7-2: %u=0x%x  R reserved", reg_addr, code, code); 
    if (0==(reg_val & (1<<1))) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:0  RW no rising edge detected on WAKE pin", reg_addr);
    }
    if (reg_val & (1<<1)) {
        fprintf (out_file_prt,"\n    reg %02u bit  1:1  RW rising edge detected on WAKE pin", reg_addr);
    }
    if (0==(reg_val & (1<<0))) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:0  RW no falling edge detected on WAKE pin", reg_addr);
    }
    if (reg_val & (1<<0)) {
        fprintf (out_file_prt,"\n    reg %02u bit  0:1  RW falling edge detected on WAKE pin", reg_addr);
    }
    return res;
}

static bool parse_tja1145_data_mask_0_register_104 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 104 == reg_addr ) {
        res = true;
    }
    code = (0xff & (reg_val>>0));
    fprintf (out_file_prt,"\n    reg %02u bit 7-0: %u=0x%x  RW data mask 0 configuration", reg_addr, code, code); 
    return res;
}

static bool parse_tja1145_data_mask_1_register_105 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 105 == reg_addr ) {
        res = true;
    }
    code = (0xff & (reg_val>>0));
    fprintf (out_file_prt,"\n    reg %02u bit 7-0: %u=0x%x  RW data mask 1 configuration", reg_addr, code, code); 
    return res;
}

static bool parse_tja1145_data_mask_2_register_106 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 106 == reg_addr ) {
        res = true;
    }
    code = (0xff & (reg_val>>0));
    fprintf (out_file_prt,"\n    reg %02u bit 7-0: %u=0x%x  RW data mask 2 configuration", reg_addr, code, code); 
    return res;
}

static bool parse_tja1145_data_mask_3_register_107 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 107 == reg_addr ) {
        res = true;
    }
    code = (0xff & (reg_val>>0));
    fprintf (out_file_prt,"\n    reg %02u bit 7-0: %u=0x%x  RW data mask 3 configuration", reg_addr, code, code); 
    return res;
}

static bool parse_tja1145_data_mask_4_register_108 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 108 == reg_addr ) {
        res = true;
    }
    code = (0xff & (reg_val>>0));
    fprintf (out_file_prt,"\n    reg %02u bit 7-0: %u=0x%x  RW data mask 4 configuration", reg_addr, code, code); 
    return res;
}

static bool parse_tja1145_data_mask_5_register_109 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 109 == reg_addr ) {
        res = true;
    }
    code = (0xff & (reg_val>>0));
    fprintf (out_file_prt,"\n    reg %02u bit 7-0: %u=0x%x  RW data mask 5 configuration", reg_addr, code, code); 
    return res;
}

static bool parse_tja1145_data_mask_6_register_110 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 110 == reg_addr ) {
        res = true;
    }
    code = (0xff & (reg_val>>0));
    fprintf (out_file_prt,"\n    reg %02u bit 7-0: %u=0x%x  RW data mask 6 configuration", reg_addr, code, code); 
    return res;
}

static bool parse_tja1145_data_mask_7_register_111 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 111 == reg_addr ) {
        res = true;
    }
    code = (0xff & (reg_val>>0));
    fprintf (out_file_prt,"\n    reg %02u bit 7-0: %u=0x%x  RW data mask 7 configuration", reg_addr, code, code); 
    return res;
}

static bool parse_tja1145_identification_register_126 (uint8_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 126 == reg_addr ) {
        res = true;
    }
    code = (0xff & (reg_val>>0));
    fprintf (out_file_prt,"\n    reg %02u bit 7-0: %u=0x%x  R device identification code", reg_addr, code, code); 
    return res;
}

bool parse_tja1145_reg (uint8_t reg_addr, FILE *out_file_prt) {
    bool res = false;
    if (false == tja1145RegMap[reg_addr].valid) {
    	return false;
    }
    uint8_t reg_val = tja1145RegMap[reg_addr].reg_val;
    fprintf (out_file_prt, "\n\nReg: [%s] reg_addr: 0x%02x val: 0x%02x 0b_%s", tja1145RegMap[reg_addr].reg_name, reg_addr, reg_val, utoa_bin8 (reg_val));
    switch ( reg_addr ) {
        case 1: 
            proc_reg_cnt++;
            res = parse_tja1145_mode_control_register_1 (reg_val, out_file_prt, reg_addr);
            break;
        case 3: 
            proc_reg_cnt++;
            res = parse_tja1145_main_status_register_3 (reg_val, out_file_prt, reg_addr);
            break;
        case 4: 
            proc_reg_cnt++;
            res = parse_tja1145_system_event_capture_enable_register_4 (reg_val, out_file_prt, reg_addr);
            break;
        case 6: 
            proc_reg_cnt++;
            res = parse_tja1145_memory_0_register_6 (reg_val, out_file_prt, reg_addr);
            break;
        case 7: 
            proc_reg_cnt++;
            res = parse_tja1145_memory_1_register_7 (reg_val, out_file_prt, reg_addr);
            break;
        case 8: 
            proc_reg_cnt++;
            res = parse_tja1145_memory_2_register_8 (reg_val, out_file_prt, reg_addr);
            break;
        case 9: 
            proc_reg_cnt++;
            res = parse_tja1145_memory_3_register_9 (reg_val, out_file_prt, reg_addr);
            break;
        case 10: 
            proc_reg_cnt++;
            res = parse_tja1145_lock_control_register_10 (reg_val, out_file_prt, reg_addr);
            break;
        case 32: 
            proc_reg_cnt++;
            res = parse_tja1145_can_control_register_32 (reg_val, out_file_prt, reg_addr);
            break;
        case 34: 
            proc_reg_cnt++;
            res = parse_tja1145_transceiver_status_register_34 (reg_val, out_file_prt, reg_addr);
            break;
        case 35: 
            proc_reg_cnt++;
            res = parse_tja1145_transceiver_event_capture_enable_register_35 (reg_val, out_file_prt, reg_addr);
            break;
        case 38: 
            proc_reg_cnt++;
            res = parse_tja1145_data_rate_register_38 (reg_val, out_file_prt, reg_addr);
            break;
        case 39: 
            proc_reg_cnt++;
            res = parse_tja1145_id_registers_0_register_39 (reg_val, out_file_prt, reg_addr);
            break;
        case 40: 
            proc_reg_cnt++;
            res = parse_tja1145_id_registers_1_register_40 (reg_val, out_file_prt, reg_addr);
            break;
        case 41: 
            proc_reg_cnt++;
            res = parse_tja1145_id_registers_2_register_41 (reg_val, out_file_prt, reg_addr);
            break;
        case 42: 
            proc_reg_cnt++;
            res = parse_tja1145_id_registers_3_register_42 (reg_val, out_file_prt, reg_addr);
            break;
        case 43: 
            proc_reg_cnt++;
            res = parse_tja1145_id_mask_registers_0_register_43 (reg_val, out_file_prt, reg_addr);
            break;
        case 44: 
            proc_reg_cnt++;
            res = parse_tja1145_id_mask_registers_1_register_44 (reg_val, out_file_prt, reg_addr);
            break;
        case 45: 
            proc_reg_cnt++;
            res = parse_tja1145_id_mask_registers_2_register_45 (reg_val, out_file_prt, reg_addr);
            break;
        case 46: 
            proc_reg_cnt++;
            res = parse_tja1145_id_mask_registers_3_register_46 (reg_val, out_file_prt, reg_addr);
            break;
        case 47: 
            proc_reg_cnt++;
            res = parse_tja1145_frame_control_register_47 (reg_val, out_file_prt, reg_addr);
            break;
        case 75: 
            proc_reg_cnt++;
            res = parse_tja1145_wake_status_register_75 (reg_val, out_file_prt, reg_addr);
            break;
        case 76: 
            proc_reg_cnt++;
            res = parse_tja1145_wake_pin_event_capture_enable_register_76 (reg_val, out_file_prt, reg_addr);
            break;
        case 96: 
            proc_reg_cnt++;
            res = parse_tja1145_global_event_status_register_96 (reg_val, out_file_prt, reg_addr);
            break;
        case 97: 
            proc_reg_cnt++;
            res = parse_tja1145_system_event_status_register_97 (reg_val, out_file_prt, reg_addr);
            break;
        case 99: 
            proc_reg_cnt++;
            res = parse_tja1145_transceiver_event_status_register_99 (reg_val, out_file_prt, reg_addr);
            break;
        case 100: 
            proc_reg_cnt++;
            res = parse_tja1145_wake_pin_event_status_register_100 (reg_val, out_file_prt, reg_addr);
            break;
        case 104: 
            proc_reg_cnt++;
            res = parse_tja1145_data_mask_0_register_104 (reg_val, out_file_prt, reg_addr);
            break;
        case 105: 
            proc_reg_cnt++;
            res = parse_tja1145_data_mask_1_register_105 (reg_val, out_file_prt, reg_addr);
            break;
        case 106: 
            proc_reg_cnt++;
            res = parse_tja1145_data_mask_2_register_106 (reg_val, out_file_prt, reg_addr);
            break;
        case 107: 
            proc_reg_cnt++;
            res = parse_tja1145_data_mask_3_register_107 (reg_val, out_file_prt, reg_addr);
            break;
        case 108: 
            proc_reg_cnt++;
            res = parse_tja1145_data_mask_4_register_108 (reg_val, out_file_prt, reg_addr);
            break;
        case 109: 
            proc_reg_cnt++;
            res = parse_tja1145_data_mask_5_register_109 (reg_val, out_file_prt, reg_addr);
            break;
        case 110: 
            proc_reg_cnt++;
            res = parse_tja1145_data_mask_6_register_110 (reg_val, out_file_prt, reg_addr);
            break;
        case 111: 
            proc_reg_cnt++;
            res = parse_tja1145_data_mask_7_register_111 (reg_val, out_file_prt, reg_addr);
            break;
        case 126: 
            proc_reg_cnt++;
            res = parse_tja1145_identification_register_126 (reg_val, out_file_prt, reg_addr);
            break;
        default:
            fprintf (out_file_prt, "\n Lack of parser for reg %s addr 0x%x val 0x%x", tja1145_reg_2_name(reg_addr), reg_addr, reg_val);
        break;
    }
    return res;
}

char *tja1145_reg_2_name (uint8_t reg_addr) {
    char *reg_name = "Undef";
    switch ( reg_addr ) {
        case 0x01: 
            reg_name = "mode_control";
            break;
        case 0x03: 
            reg_name = "main_status";
            break;
        case 0x04: 
            reg_name = "system_event_capture_enable";
            break;
        case 0x06: 
            reg_name = "memory_0";
            break;
        case 0x07: 
            reg_name = "memory_1";
            break;
        case 0x08: 
            reg_name = "memory_2";
            break;
        case 0x09: 
            reg_name = "memory_3";
            break;
        case 0x0a: 
            reg_name = "lock_control";
            break;
        case 0x20: 
            reg_name = "can_control";
            break;
        case 0x22: 
            reg_name = "transceiver_status";
            break;
        case 0x23: 
            reg_name = "transceiver_event_capture_enable";
            break;
        case 0x26: 
            reg_name = "data_rate";
            break;
        case 0x27: 
            reg_name = "id_registers_0";
            break;
        case 0x28: 
            reg_name = "id_registers_1";
            break;
        case 0x29: 
            reg_name = "id_registers_2";
            break;
        case 0x2a: 
            reg_name = "id_registers_3";
            break;
        case 0x2b: 
            reg_name = "id_mask_registers_0";
            break;
        case 0x2c: 
            reg_name = "id_mask_registers_1";
            break;
        case 0x2d: 
            reg_name = "id_mask_registers_2";
            break;
        case 0x2e: 
            reg_name = "id_mask_registers_3";
            break;
        case 0x2f: 
            reg_name = "frame_control";
            break;
        case 0x4b: 
            reg_name = "wake_status";
            break;
        case 0x4c: 
            reg_name = "wake_pin_event_capture_enable";
            break;
        case 0x60: 
            reg_name = "global_event_status";
            break;
        case 0x61: 
            reg_name = "system_event_status";
            break;
        case 0x63: 
            reg_name = "transceiver_event_status";
            break;
        case 0x64: 
            reg_name = "wake_pin_event_status";
            break;
        case 0x68: 
            reg_name = "data_mask_0";
            break;
        case 0x69: 
            reg_name = "data_mask_1";
            break;
        case 0x6a: 
            reg_name = "data_mask_2";
            break;
        case 0x6b: 
            reg_name = "data_mask_3";
            break;
        case 0x6c: 
            reg_name = "data_mask_4";
            break;
        case 0x6d: 
            reg_name = "data_mask_5";
            break;
        case 0x6e: 
            reg_name = "data_mask_6";
            break;
        case 0x6f: 
            reg_name = "data_mask_7";
            break;
        case 0x7e: 
            reg_name = "identification";
            break;
        default:
            reg_name = "Reserved";
        break;
    }
    return reg_name;
}

 // Support: aabzele@gmail.com Alexander Barunin