/** @copyright (C) 2016-2020,  Gavin J Stark.  All rights reserved.
 *
 * @copyright
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *     http://www.apache.org/licenses/LICENSE-2.0.
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 * @file   reve_r_decode.h
 * @brief  Instruction decode for Reve-R
 *
 * The instruction decode is required by coprocessors, and so this must be
 * an externally visible header file
 *
 */

/*a includes */
include "reve_r.h"
include "reve_r_csr.h" // For csr_access

/*a I32 types */
/*t t_reve_r_mem_width */
typedef enum[2] {
    mw_byte,
    mw_half,
    mw_word
} t_reve_r_mem_width;

/*t t_reve_r_op - RISC-V decoded instruction operation class - no relationship to encodings */
typedef enum[4] {
    reve_r_op_branch,
    reve_r_op_jal,
    reve_r_op_jalr,
    reve_r_op_system,
    reve_r_op_csr,
    reve_r_op_misc_mem,
    reve_r_op_mem,
    reve_r_op_alu,
    reve_r_op_muldiv,
    reve_r_op_auipc,
    reve_r_op_lui,
    reve_r_op_custom_0, // for custom extensions
    reve_r_op_custom_1, // for custom extensions
    reve_r_op_custom_2, // for custom extensions
    reve_r_op_custom_3, // for custom extensions
    reve_r_op_illegal
} t_reve_r_op;

/*t t_reve_r_subop - RISC-V decoded instruciton operation class - mapping of f3 as much as possible */
typedef enum[4] {
    reve_r_subop_valid=0, // for op==illegal, really - means op==invalid is sufficient for illegal op
    reve_r_subop_illegal = 0xf, // for many of the ops...

    reve_r_subop_beq=0, // same as rvi_branch_f3
    reve_r_subop_bne=1,
    reve_r_subop_blt=2,
    reve_r_subop_bge=3,
    reve_r_subop_bltu=4,
    reve_r_subop_bgeu=5,

    reve_r_subop_add    = 0, // same as reve_r_op_f3, with bit[3] as the 'extra' ops
    reve_r_subop_sub    = 0+8,
    reve_r_subop_sll    = 1,  // => subop shift
    reve_r_subop_slt    = 2,
    reve_r_subop_sltu   = 3,
    reve_r_subop_xor    = 4,
    reve_r_subop_srla   = 5,    // => subop shift
    reve_r_subop_or     = 6,
    reve_r_subop_and    = 7,

    reve_r_subop_mull     = 0, // same as reve_r_op_f3
    reve_r_subop_mulhss   = 1,
    reve_r_subop_mulhsu   = 2,
    reve_r_subop_mulhu    = 3,
    reve_r_subop_divs     = 4,
    reve_r_subop_divu     = 5,
    reve_r_subop_rems     = 6,
    reve_r_subop_remu     = 7,

    reve_r_subop_lb  = 0, // same as rvi_f3_load
    reve_r_subop_lh  = 1,
    reve_r_subop_lw  = 2,
    reve_r_subop_lbu = 4,
    reve_r_subop_lhu = 5,
    reve_r_subop_sb  = 8, // same as rvi_f3_store but with bit[3] set
    reve_r_subop_sh  = 9,
    reve_r_subop_sw  = 10,
    reve_r_subop_atomic = 12,
    reve_r_subop_ls_store     = 8,
    reve_r_subop_ls_unsigned  = 4,
    reve_r_subop_ls_size_mask = 3,
    reve_r_subop_ls_byte      = 0,
    reve_r_subop_ls_half      = 1,
    reve_r_subop_ls_word      = 2,

    reve_r_subop_ecall  = 0,
    reve_r_subop_ebreak = 1,
    reve_r_subop_mret   = 2, // possibly need uret and sret - see table 6.1 in priv spec 1.10
    reve_r_subop_mwfi   = 3,

    reve_r_subop_fence   = 0, // to match riscv_op_f3
    reve_r_subop_fence_i = 1,

    reve_r_subop_csrrw   = 1, // to match riscv_op_f3
    reve_r_subop_csrrs   = 2,
    reve_r_subop_csrrc   = 3,
} t_reve_r_subop;

/*t t_reve_r_shift_op */
typedef enum[4] {
    reve_r_shift_op_left_logical_zeros  = 4b0000, // standard
    reve_r_shift_op_left_logical_ones   = 4b0001,
    reve_r_shift_op_left_rotate         = 4b0011,
    reve_r_shift_op_right_logical_zeros = 4b0100, // standard
    reve_r_shift_op_right_logical_ones  = 4b0101,
    reve_r_shift_op_right_arithmetic    = 4b0110, // standard
    reve_r_shift_op_right_rotate        = 4b0111,
    reve_r_shift_op_bit_insert          = 4b1000, // inserts must be a 'left'
    reve_r_shift_op_byte_insert         = 4b1001, // inserts must be a 'left'
    reve_r_shift_op_reverse             = 4b1100, // reverse cannot be a 'left'
    reve_r_shift_op_count               = 4b1010,

    reve_r_shift_op_mask_right           = 4b0100 // used to determine if shift amount to  be negated
} t_reve_r_shift_op;

/*t t_reve_r_inst_debug_op
 */
typedef enum[2] {
    rv_inst_debug_op_read_reg,
    rv_inst_debug_op_write_reg
} t_reve_r_inst_debug_op;

/*t t_reve_r_inst_debug
 */
typedef struct {
    bit valid;
    t_reve_r_inst_debug_op debug_op;
    bit[16]                   data     "For reading/writing a register, this is the register number";
} t_reve_r_inst_debug;

/*t t_reve_r_inst
 */
typedef struct {
    t_reve_r_mode mode;
    bit[32]      data;
    t_reve_r_inst_debug debug;
} t_reve_r_inst;

/*t t_reve_r_decode_ext
 *
 * A type that can be used to create an extended RISC-V, returned as part of the decode
 *
 */
typedef struct {
    bit dummy; // not used, but the struct must not be empty
} t_reve_r_decode_ext;

/*t t_reve_r_decode
 * Decoded reve_r instruction, used throughout a pipeline (decode onwards)
 */
typedef struct {
    bit[5]       rs1                   "Source register 1 that is required by the instruction";
    bit          rs1_valid             "Asserted if rs1 is valid; if deasserted then rs1 is not used - only used for blocking in pipelines";
    bit[5]       rs2                   "Source register 2 that is required by the instruction";
    bit          rs2_valid             "Asserted if rs2 is valid; if deasserted then rs2 is not used - only used for blocking in pipelines";
    bit[5]       rd                    "Destination register that is written by the instruction";
    bit          rd_written            "Asserted if Rd is written to (hence also Rd will be non-zero)";
    t_reve_r_csr_access     csr_access  "CSR access if valid and legal";
    bit[32]      immediate             "Immediate value decoded from the instruction";
    bit[5]       immediate_shift       "Immediate shift value decoded from the instruction";
    bit          immediate_valid       "Asserted if immediate data is valid and therefore to be used instead of source register 2";
    t_reve_r_op     op                  "Operation class of the instruction";
    t_reve_r_subop  subop               "Subclass of the operation class";
    t_reve_r_shift_op shift_op          "Only valid for shift operations (i.e. ignored if op is not alu and subop is not a shift)";
    bit[7]         funct7              "Options for subop only to be used by custom instructions (so it can be optimized out)";
    bit           illegal              "asserted if an illegal opcode";
    bit           is_compressed        "asserted if from an reve_r-c decode, clear otherwise (effects link register)";
    t_reve_r_decode_ext ext         "extended decode, not used by the main pipeline";
} t_reve_r_decode;

