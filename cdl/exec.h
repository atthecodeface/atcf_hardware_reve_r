include "reve_r.h"
include "reve_r_dmem.h"
include "reve_r_decode.h"
include "reve_r_csr.h"

/*t t_alu_result
 *
 * Result of i32 ALU operation
 */
typedef struct {
    bit[32] result       "Result of ALU operation, dependent on subop";
    bit[32] arith_result "Use for mem_address";
    bit     branch_condition_met;
    bit[32] branch_target;
    t_reve_r_csr_access csr_access;
} t_alu_result;

/*a Dmem access */
/*t t_dmem_exec */
typedef struct {
    bit                 valid;
    t_reve_r_mode       mode;
    t_reve_r_decode     idecode "Exec stage idecode";
    bit[32]             arith_result;
    bit[32]             rs2;
    bit                 first_cycle;
} t_dmem_exec;

/*t t_dmem_request */
typedef struct {
    t_reve_r_dmem_access_req access;
    bit load_address_misaligned  "Asserted only for valid instructions, for loads not aligned to the alignment of the access";
    bit store_address_misaligned "Asserted only for valid instructions, for stores not aligned to the alignment of the access";
    bit    reading;
    bit[2] read_data_rotation;
    bit[4] read_data_byte_clear;
    bit[4] read_data_byte_enable;
    bit    sign_extend_byte;
    bit    sign_extend_half;
    bit    multicycle;
} t_dmem_request;


