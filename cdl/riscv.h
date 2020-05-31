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
 * @file   riscv.h
 * @brief  Types from the RISC-V specifications
 *
 */

/*a CSR */
/*t t_riscv_csr_addr
 *
 * RISC-V CSR addresses; the top bit indicates readable, next
 * writable; next two are the minimum privilege level to access
 * (00=user, 11=machine)
 *
 * From RISCV privileged spec v1.1
 */
typedef enum[12] {
    CSR_ADDR_READWRITE_MASK  = 12hc00,
    CSR_ADDR_READ_WRITE_A    = 12h000,
    CSR_ADDR_READ_WRITE_B    = 12h400,
    CSR_ADDR_READ_WRITE_C    = 12h800,
    CSR_ADDR_READ_ONLY       = 12hC00,

    CSR_ADDR_MODE_MASK       = 12h300,
    CSR_ADDR_USER_MODE       = 12h000,
    CSR_ADDR_SUPERVISOR_MODE = 12h100,
    CSR_ADDR_HYPERVISOR_MODE = 12h200,
    CSR_ADDR_MACHINE_MODE    = 12h300,

    // Read-write registers accessible from user mode (if provided)
    CSR_ADDR_USTATUS   = 12h000  "User status register, optional",
    // 1, 2, 3 are floating point (fflags, frm, fcsr)
    CSR_ADDR_UIE       = 12h004  "User interrupt enable register, optional",
    CSR_ADDR_UTVEC     = 12h005  "User trap handler base register, optional",

    CSR_ADDR_USCRATCH  = 12h040  "Scratch register for user trap handlers, only if user mode provided",
    CSR_ADDR_UEPC      = 12h041  "User exception program counter, only if user mode provided",
    CSR_ADDR_UCAUSE    = 12h042  "User trap cause register, only if user mode provided",
    CSR_ADDR_UTVAL     = 12h043  "User trap value register, only if user mode provided",
    CSR_ADDR_UIP       = 12h044  "User interrupt pending register, only if user mode interrupts provided",

    // Read-only registers accessible from user mode
    CSR_ADDR_CYCLE     = 12hC00  "Required register for RV32I, low 32-bits of cycle counter",
    CSR_ADDR_TIME      = 12hC01  "Required register for RV32I, low 32-bits of wall-clock timer",
    CSR_ADDR_INSTRET   = 12hC02  "Required register for RV32I, low 32-bits of instructions retired counter",
    // c03 to c1f are more high performance counters if required
    CSR_ADDR_CYCLEH    = 12hC80  "Required register for RV32I, high 32-bits of cycle counter - may be implemented in software with a trap",
    CSR_ADDR_TIMEH     = 12hC81  "Required register for RV32I, high 32-bits of wall-clock timer - may be implemented in software with a trap",
    CSR_ADDR_INSTRETH  = 12hC82  "Required register for RV32I, high 32-bits of instructions retired counter - may be implemented in software with a trap",
    // c83 to c9f are more high performance counters high 32 bits if required

    // Read-write registers accessible from system mode (if provided)
    CSR_ADDR_SSTATUS   = 12h100  "Supervisor status register, optional",
    CSR_ADDR_SEDELEG   = 12h102  "Supervisor exception delegation register, optional",
    CSR_ADDR_SIDELEG   = 12h103  "Supervisor interrupt delegation register, optional",
    CSR_ADDR_SIE       = 12h104  "Supervisor interrupt enable register, optional",
    CSR_ADDR_STVEC     = 12h105  "Supervisor trap handler base register, optional",
    CSR_ADDR_SCOUNTEREN = 12h106  "Supervisor counter enable, optional",
    CSR_ADDR_SSCRATCH  = 12h140  "Scratch register for supervisor trap handlers",
    CSR_ADDR_SEPC      = 12h141  "Supervisor exception program counter, optional",
    CSR_ADDR_SCAUSE    = 12h142  "Supervisor trap cause register, optional",
    CSR_ADDR_SBADADDR  = 12h143  "Supervisor trap value register, optional",
    CSR_ADDR_SIP       = 12h144  "Supervisor interrupt pending register, optional",
    CSR_ADDR_SPTBR     = 12h180  "Supervisor page-table base register, optional",

    // Read-write registers accessible from machine mode (if provided)
    CSR_ADDR_MSTATUS   = 12h300  "Machine status register, required",
    CSR_ADDR_MISA      = 12h301  "ISA and extensions, required - but may be hardwire to zero",
    CSR_ADDR_MEDELEG   = 12h302  "Machine exception delegation register, optional - tests require this to not be illegal",
    CSR_ADDR_MIDELEG   = 12h303  "Machine interrupt delegation register, optional - tests require this to not be illegal",
    CSR_ADDR_MIE       = 12h304  "Machine interrupt enable register, optional - tests require this to not be illegal",
    CSR_ADDR_MTVEC     = 12h305  "Machine trap handler base register, optional - tests require this to not be illegal",
    CSR_ADDR_MCOUNTEREN = 12h306  "Machine counter enable, optional",
    CSR_ADDR_MSCRATCH  = 12h340  "Scratch register for machine trap handlers",
    CSR_ADDR_MEPC      = 12h341  "Machine exception program counter",
    CSR_ADDR_MCAUSE    = 12h342  "Machine trap cause register",
    CSR_ADDR_MTVAL     = 12h343  "Machine trap value register",
    CSR_ADDR_MIP       = 12h344  "Machine interrupt pending register, optional",

    // Machine-mode only read-write registers that shadow other registers (read-only elsewhere)
    // Clarvi maps the following to Fxx, rather than the specs Bxx - hence the spec has them read/write
    CSR_ADDR_MCYCLE    = 12hB00  "Required register for RV32I, low 32-bits of cycle counter",
    CSR_ADDR_MINSTRET  = 12hB02  "Required register for RV32I, low 32-bits of instructions retired counter",
    CSR_ADDR_MCYCLEH   = 12hB80  "Required register for RV32I, high 32-bits of cycle counter - may be implemented in software with a trap",
    CSR_ADDR_MINSTRETH = 12hB82  "Required register for RV32I, high 32-bits of instructions retired counter - may be implemented in software with a trap",

    // Read-only registers, accesible from machine mode only
    CSR_ADDR_MVENDORID = 12hF11  "Vendor ID, required - but may be hardwired to zero for not implemented or non-commercial",
    CSR_ADDR_MARCHID   = 12hF12  "Architecture ID, required - but may be hardwired to zero for not implemented",
    CSR_ADDR_MIMPID    = 12hF13  "Implementation ID, required - but may be hardwired to zero for not implemented",
    CSR_ADDR_MHARTID   = 12hF14  "Hardware thread ID, required - but may be hardwired to zero (if only one thread in system)",

    // provisional debug, used across these RISC-V implementations
    CSR_ADDR_DCSR       = 12h7B0,
    CSR_ADDR_DEPC       = 12h7B1,
    CSR_ADDR_DSCRATCH0  = 12h7B2,
    CSR_ADDR_DSCRATCH1  = 12h7B3
} t_riscv_csr_addr;

/*t t_riscv_csr_select
 *
 * RISC-V CSR addresses; the top bit indicates readable, next
 * writable; next two are the minimum privilege level to access
 * (00=user, 11=machine)
 *
 * From RISCV privileged spec v1.1
 */
typedef enum[12] {
    riscv_csr_select_time_l   = 12h010,
    riscv_csr_select_time_h   = 12h011,
    riscv_csr_select_cycle_l  = 12h012,
    riscv_csr_select_cycle_h  = 12h013,
    riscv_csr_select_instret_l= 12h014,
    riscv_csr_select_instret_h= 12h015,

    riscv_csr_machine_isa     = 12h020,
    riscv_csr_machine_vendorid= 12h021,
    riscv_csr_machine_archid  = 12h022,
    riscv_csr_machine_impid   = 12h023,
    riscv_csr_machine_hartid  = 12h024,

    riscv_csr_user_status     = 12h040,
    riscv_csr_user_scratch    = 12h041,
    riscv_csr_user_ie         = 12h042,
    riscv_csr_user_ip         = 12h043,
    riscv_csr_user_tvec       = 12h044,
    riscv_csr_user_tval       = 12h045,
    riscv_csr_user_epc        = 12h046,
    riscv_csr_user_cause      = 12h047,

    riscv_csr_machine_status  = 12h080,
    riscv_csr_machine_scratch = 12h081,
    riscv_csr_machine_ie      = 12h082,
    riscv_csr_machine_ip      = 12h083,
    riscv_csr_machine_tvec    = 12h084,
    riscv_csr_machine_tval    = 12h085,
    riscv_csr_machine_epc     = 12h086,
    riscv_csr_machine_cause   = 12h087,

    riscv_csr_machine_edeleg  = 12h100,
    riscv_csr_machine_ideleg  = 12h101,

    riscv_csr_debug_pc        = 12h800,
    riscv_csr_debug_csr       = 12h801,
    riscv_csr_debug_scratch0  = 12h802,
    riscv_csr_debug_scratch1  = 12h803
} t_riscv_csr_select;

/*a RISC-V instruction decode types */
/*t t_riscv_opc (I32) enumeration - from inst[5;2] - see table 19.1 in RISC-V spec v2.2
 */
typedef enum[5] {
    riscv_opc_load     =  0, // rv32i (lb, lh, lw, lbu, lhu); rv64i (lwu, ld)
    riscv_opc_load_fp  =  1, // rv32f (flw)
    riscv_opc_custom_0 =  2,
    riscv_opc_misc_mem =  3, // rv32i (fence, fence.i)
    riscv_opc_op_imm   =  4, // rv32i (addi, slti, sltiu, xori, ori, andi); rv64i (slli, srli, srai)
    riscv_opc_auipc    =  5, // rv32i (auipc)
    riscv_opc_op_imm32 =  6, // rv64i (addiw, slliw, srliw, sraiw)
    riscv_opc_store    =  8, // rv32i (sb, sh, sw); rv64i (sd)
    riscv_opc_store_fp =  9, // rv32f (fsw)
    riscv_opc_custom_1 = 10,
    riscv_opc_amo      = 11, // rv32a (lr.w, sc.w, amoswap.w, amoadd.w, amoxor.w, amoand.w, amoor.w, amomin.w, amomax.w, amomaxu.w) (+rv64a)
    riscv_opc_op       = 12, // rv32i (add, sub, sll, slt, sltu, xor, srl, sra, or, and); rv32m (mul, mulh, mulhsu, mulhu, div, divu, rem, remu)
    riscv_opc_lui      = 13, // rv32i
    riscv_opc_op32     = 14, // rv64i (addw, subw, sllw, srlw, sraw)
    riscv_opc_madd     = 16, // rv32f (fmadd.s)
    riscv_opc_msub     = 17, // rv32f (fmsub.s)
    riscv_opc_nmsub    = 18, // rv32f (fnmsub.s)
    riscv_opc_nmadd    = 19, // rv32f (fnmadd.s)
    riscv_opc_op_fp    = 20, // rv32f (fadd.s, fsub.s, fmul.s, fdiv.s, fsqrt.s, fsgnj.s, fsgnjn.s, fsgnjx.s, fmin.s, ... fmv.s.x)
    riscv_opc_resvd_0  = 21,
    riscv_opc_custom_2 = 22,
    riscv_opc_branch   = 24, // rv32i (beq, bne, blt, bge, bltu, bgeu)
    riscv_opc_jalr     = 25, // rv32i (jalr)
    riscv_opc_resvd_1  = 26,
    riscv_opc_jal      = 27, // rv32i (jal)
    riscv_opc_system   = 28, // rv32i (ecall, ebreak, csrrw, csrrs, csrrc, csrrwi, csrrsi, csrrci)
    riscv_opc_resvd_2  = 29,
    riscv_opc_custom_3 = 30
} t_riscv_opc_rv32;

/*t t_riscv_opcc (I32C) enumeration
 */
typedef enum[3] {
    riscv_opcc0_addi4spn =  0,
    riscv_opcc0_lw       =  2,
    riscv_opcc0_sw       =  6,
    riscv_opcc1_addi     =  0,
    riscv_opcc1_jal      =  1,
    riscv_opcc1_li       =  2,
    riscv_opcc1_lui      =  3,
    riscv_opcc1_arith    =  4,
    riscv_opcc1_j        =  5,
    riscv_opcc1_beqz     =  6,
    riscv_opcc1_bnez     =  7,
    riscv_opcc2_slli     =  0,
    riscv_opcc2_lwsp     =  2,
    riscv_opcc2_misc_alu =  4,
    riscv_opcc2_swsp     =  6,

} t_riscv_opc_rv32c;

/*t t_riscv_f12- see RISC-V spec 2.1 table 9.2
 */
typedef enum[12] {
    riscv_f12_ecall   = 12h0, // originally scall
    riscv_f12_ebreak  = 12h1, // originally sbreak

    riscv_f12_mret  = 12h302, // from RISC-V privileged spec
    riscv_f12_mwfi  = 12h105, // from RISC-V privileged spec

} t_riscv_system_f12;

/*t t_riscv_f3_alu
 */
typedef enum[3] {
    riscv_f3_addsub = 0, // sub has f7[5] set, add has it clear
    riscv_f3_sll    = 1,
    riscv_f3_slt    = 2,
    riscv_f3_sltu   = 3,
    riscv_f3_xor    = 4,
    riscv_f3_srlsra = 5, // sra has f7[5] set, srl has it clear
    riscv_f3_or     = 6,
    riscv_f3_and    = 7,
} t_riscv_f3_alu;

/*t t_riscv_f3_muldiv
 */
typedef enum[3] {
    riscv_f3_mul    = 0,
    riscv_f3_mulh   = 1,
    riscv_f3_mulhsu = 2,
    riscv_f3_mulhu  = 3,
    riscv_f3_div    = 4,
    riscv_f3_divu   = 5,
    riscv_f3_rem    = 6,
    riscv_f3_remu   = 7
} t_riscv_f3_muldiv;

/*t t_riscv_f3_branch
 */
typedef enum[3] {
    riscv_f3_beq  = 0,
    riscv_f3_bne  = 1,
    riscv_f3_blt  = 4,
    riscv_f3_bge  = 5,
    riscv_f3_bltu = 6,
    riscv_f3_bgeu = 7
} t_riscv_f3_branch;

/*t t_riscv_f3_load
 */
typedef enum[3] {
    riscv_f3_lb  = 0,
    riscv_f3_lh  = 1,
    riscv_f3_lw  = 2,
    riscv_f3_lbu = 4,
    riscv_f3_lhu = 5,
} t_riscv_f3_load;

/*t t_riscv_f3_store
 */
typedef enum[3] {
    riscv_f3_sb  = 0,
    riscv_f3_sh  = 1,
    riscv_f3_sw  = 2,
} t_riscv_f3_store;

/*t t_riscv_f3_misc_mem
 */
typedef enum[3] {
    riscv_f3_fence   = 0,
    riscv_f3_fence_i = 1,
} t_riscv_f3_misc_mem;

/*t t_riscv_f3_system
 */
typedef enum[3] {
    riscv_f3_privileged = 0,
    riscv_f3_csrrw = 1,
    riscv_f3_csrrs = 2,
    riscv_f3_csrrc = 3,
    riscv_f3_csrrwi = 5,
    riscv_f3_csrrsi = 6,
    riscv_f3_csrrci = 7,
} t_riscv_f3_system;

/*t t_riscv_mcause
 * Non-interrupt MCAUSE reasons, from the spec
 */
typedef enum[8] {
    riscv_mcause_instruction_misaligned = 0,
    riscv_mcause_instruction_fault      = 1,
    riscv_mcause_illegal_instruction    = 2,
    riscv_mcause_breakpoint             = 3,
    riscv_mcause_load_misaligned        = 4,
    riscv_mcause_load_fault             = 5,
    riscv_mcause_store_misaligned       = 6,
    riscv_mcause_store_fault            = 7,
    riscv_mcause_uecall                 = 8,
    riscv_mcause_secall                 = 9,
    riscv_mcause_mecall                 = 11,
} t_riscv_mcause;

/*t t_riscv_trap_cause
 */
typedef enum[5] {
    riscv_trap_cause_instruction_misaligned = 0,
    riscv_trap_cause_instruction_fault      = 1,
    riscv_trap_cause_illegal_instruction    = 2,
    riscv_trap_cause_breakpoint             = 3,
    riscv_trap_cause_load_misaligned        = 4,
    riscv_trap_cause_load_fault             = 5,
    riscv_trap_cause_store_misaligned       = 6,
    riscv_trap_cause_store_fault            = 7,
    riscv_trap_cause_uecall                 = 8,
    riscv_trap_cause_secall                 = 9,
    riscv_trap_cause_mecall                 = 11,
    riscv_trap_cause_interrupt              = 16,
    riscv_trap_cause_ret_mret               = 0,
    riscv_trap_cause_ret_sret               = 1,
    riscv_trap_cause_ret_uret               = 2,
    riscv_trap_cause_ret_dret               = 3,
} t_riscv_trap_cause;

/*a RISC-V ABI register names - known by 'c' decode */
typedef enum[5] {
    riscv_abi_zero = 0,
    riscv_abi_link = 1,
    riscv_abi_sp   = 2
} t_riscv_abi;

/*a Constants
 */
constant integer RV32I_EBREAK=0x00100073;

