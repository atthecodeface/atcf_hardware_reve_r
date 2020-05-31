include "reve_r.h" // for mode etc
include "riscv.h" // for riscv_csr_select

/*t t_reve_r_csr_access_type
 */
typedef enum[3] {
    reve_r_csr_access_none = 0,
    reve_r_csr_access_write = 1,
    reve_r_csr_access_read  = 2,
    reve_r_csr_access_rw    = 3,
    reve_r_csr_access_rs    = 6,
    reve_r_csr_access_rc   =  7,
} t_reve_r_csr_access_type;

/*t t_reve_r_csr_access
 */
typedef struct {
    t_reve_r_mode            mode "Used for decode and to determine legality";
    bit                     access_cancelled;
    t_reve_r_csr_access_type access;
    t_reve_r_csr_access_custom custom;
    bit[12]                 address "For internal use before select generation";
    t_riscv_csr_select      select;
    bit[32]            write_data     "Write data for the CSR access, later in the cycle than @csr_access possibly";
} t_reve_r_csr_access;

/*a CSR types */
/*t t_reve_r_csr_data
 */
typedef struct {
    bit[32]    read_data;
    bit             take_interrupt;
    t_reve_r_mode    interrupt_mode  "Mode to enter if take_interrupt is asserted";
    bit[4]          interrupt_cause "From table 3.6 in RV priv space 1.10";
} t_reve_r_csr_data;

/*t t_reve_r_i32_trap */
typedef struct {
    bit valid;
    t_reve_r_mode to_mode "If interrupt then this is the mode that whose pp/pie/epc should be set from current mode's";
    t_riscv_trap_cause cause;
    bit[32] pc;
    bit[32] value;
    bit ret;
    bit ebreak_to_dbg "Asserted if the trap is a breakpoint and pipeline_control.ebreak_to_dbg was set";
} t_reve_r_i32_trap;

/*t t_reve_r_csr_controls
 */
typedef struct {
    t_reve_r_mode exec_mode "Mode of instruction in the execution stage";
    bit retire;
    bit[64] timer_value;
    t_reve_r_i32_trap trap;
} t_reve_r_csr_controls;

/*t t_reve_r_csr_decode */
typedef struct {
    bit illegal_access;
    t_riscv_csr_select csr_select;
} t_reve_r_csr_decode;

/*t t_reve_r_csr_dcsr
 *
 * From Debug spec v?
 *
 */
typedef struct {
    bit[4] xdebug_ver "4 for conformant debug support, 0 otherwise";
    bit    ebreakm    "make ebreak instructions in machine mode enter debug mode";
    bit    ebreaks    "make ebreak instructions in system mode enter debug mode";
    bit    ebreaku    "make ebreak instructions in user mode enter debug mode";
    bit    stepie     "set to enable interrupts during stepping (may be hardwired to 0)";
    bit    stopcount  "set to stop cycle and instret incrementing on instructions executed in debug mode";
    bit    stoptime   "set to disable incrementing of hart-local timers when in debug mode";
    bit[3] cause      "1=ebreak, 2=trigger module, 3=debugger request, 4=single step as step was set";
    bit    mprven     "if clear ignore mstatus.mprv when in debug mode";
    bit    nmip       "asserted if an NMI is pending for the hart";
    bit    step       "when set enter debug mode after current instruction completes";
    bit[2] prv        "mode of execution prior to entry to debug mode, and to return to on dret";
} t_reve_r_csr_dcsr;

/*t t_reve_r_csr_mstatus
 *
 * From Priv spec v1.10
 *
 */
typedef struct {
    bit sd;
    bit tsr;
    bit tw;
    bit tvm;
    bit mxr;
    bit sum;
    bit mprv;
    bit[2] xs;
    bit[2] fs;
    bit[2] mpp;
    bit spp;
    bit mpie;
    bit spie;
    bit upie;
    bit mie;
    bit sie;
    bit uie;
} t_reve_r_csr_mstatus;

/*t t_reve_r_csr_mip
 *
 * From Priv spec v1.10
 *
 */
typedef struct {
    bit meip "Machine-external interrupt pending, mirroring the input pin";
    bit seip "System-external interrupt pending, mirroring the input pin";
    bit ueip "User-external interrupt pending, mirroring the input pin";
    bit seip_sw "System-external interrupt pending, mirroring the input pin";
    bit ueip_sw "User-external interrupt pending, mirroring the input pin";
    bit mtip "Machine timer interrupt pending, set by memory-mapped machine timer comparator meeting mtime";
    bit stip "System timer interrupt pending, set by software";
    bit utip "User timer interrupt pending, set by software";
    bit msip "Machine system interrupt pending, set by memory-mapped register if supported";
    bit ssip "System software interrupt pending, set by software";
    bit usip "User software interrupt pending, set by software";
} t_reve_r_csr_mip;

/*t t_reve_r_csr_mie
 *
 * From Priv spec v1.10
 *
 */
typedef struct {
    bit meip "Enable for machine-external interrupt pending";
    bit seip "Enable for system-external interrupt pending";
    bit ueip "Enable for user-external interrupt pending";
    bit mtip "Enable for machine timer interrupt pending";
    bit stip "Enable for system timer interrupt pending";
    bit utip "Enable for user timer interrupt pending";
    bit msip "Enable for machine system interrupt pending";
    bit ssip "Enable for system software interrupt pending";
    bit usip "Enable for user software interrupt pending";
} t_reve_r_csr_mie;

/*t t_reve_r_csr_tvec
 */
typedef struct {
    bit[30] base;
    bit     vectored;
} t_reve_r_csr_tvec;

/*t t_reve_r_csrs
 *
 * Minimal set of RISC-V CSRs - actually not minimal... but some are hardwired 0 if minimal
 *
 * mstatus    - see above
 * medeleg    - sync exceptions delegation - must be 0 if machine mode only
 * mideleg    - interrupt delegation       - must be 0 if machine mode only
 * mie        - interrupt enable           - meie, mtie, msie as a minimum
 * mtvec      - can be hardwired to 0
 * mcounteren - counter permissions     - should be 0 if machine mode only
 * mcause     - cause of interrupt/trap    - top bit set if interrupt, bottom bits indicate trap/irq
 * mscratch
 * mepc
 * mtval
 * mip        - interrupt pending          - meip, mtip, msip as a minimum
 *
 * dcsr       - see above
 * dpc        - address of ebreak, or of instruction to be executed after (single step or halt)
 * dscratch
 *
 */
typedef struct {
    bit[64] cycles    "Number of cycles since reset";
    bit[64] instret   "Number of instructions retired";
    bit[64] time      "Mirror of irqs.time - may be tied to 0 if only machine mode is supported";

    bit[32] mscratch  "Scratch register for exception routines";
    bit[32] mepc      "PC at last exception";
    bit[32] mcause    "Cause of last exception";
    bit[32] mtval     "Value associated with last exception";
    t_reve_r_csr_tvec    mtvec     "Trap vector, can be hardwired or writable";
    t_reve_r_csr_mstatus mstatus     "";
    t_reve_r_csr_mip     mip         "";
    t_reve_r_csr_mie     mie         "";

    // for N (User mode IRQs)
    bit[32] uscratch  "Scratch register for exception routines";
    bit[32] uepc      "PC at last exception";
    bit[32] ucause    "Cause of last exception";
    bit[32] utval     "Value associated with last exception";
    t_reve_r_csr_tvec   utvec     "Trap vector, can be hardwired or writable";
    //  ustatus is a User-mode view on mstatus bits
    //  uip     is a User-mode view on mstatus bits
    //  uie     is a User-mode view on mstatus bits

    t_reve_r_csr_dcsr    dcsr        "Debug control/status, if debug enabled (otherwise 0)";
    bit[32] depc;
    bit[32] dscratch0;
    bit[32] dscratch1;
} t_reve_r_csrs;

/*m reve_r_csrs_decode  */
extern
module reve_r_csrs_decode( input t_reve_r_csr_access csr_access,
                           output t_reve_r_csr_decode csr_decode )
{
    timing comb input csr_access;
    timing comb output csr_decode;
}

/*a CSR modules */
/*m reve_r_csrs - generic, may not be built  */
extern
module reve_r_csrs( clock clk                                   "RISC-V clock",
                   clock riscv_clk                             "Clk gated by riscv_clk_enable - provide for single clock gate outside the module",
                   input bit reset_n                           "Active low reset",
                   input bit riscv_clk_enable,
                   input t_reve_r_irqs       irqs               "Interrupts in to the CPU",
                   input t_reve_r_csr_access csr_access         "RISC-V CSR access, combinatorially decoded",
                   output t_reve_r_csr_data csr_data            "CSR response (including take interrupt and read data), from the current @a csr_access",
                   input t_reve_r_csr_controls csr_controls     "Control signals to update the CSRs",
                   output t_reve_r_csrs        csrs            "CSR values"
    )
{
    timing to   rising clock clk riscv_clk_enable;
    timing to   rising clock riscv_clk csr_access, csr_controls, irqs;
    timing from rising clock riscv_clk csr_data, csrs;
    timing comb input csr_access;
    timing comb output csr_data;
}

