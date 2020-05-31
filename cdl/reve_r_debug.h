/*t t_reve_r_debug_op
 */
typedef enum[4] {
    rv_debug_acknowledge "Acknowledge halt, breakpoint hit, status; removes attention signal",
    rv_debug_set_requests   "Set request bits for halt, resume, step (args[0..2])",
    rv_debug_read   "Request read of a GPR/CSR",
    rv_debug_write  "Request write of a GPR/CSR",
    rv_debug_execute "Execute instruction provided resumption of execution at dpc and in mode dcsr.prv",
    rv_debug_execute_progbuf "Execute instruction at 'progbuf' address X (if it is a jump and link it will return)",
} t_reve_r_debug_op;

/*t t_reve_r_debug_resp
 */
typedef enum[2] {
    rv_debug_resp_acknowledge,
    rv_debug_resp_read_write_complete
} t_reve_r_debug_resp;

/*t t_reve_r_debug_mst
 *
 * Debug module (DM) communication to (many) pipeline debug modules (PDMs)
 *
 * 
 *
 */
typedef struct {
    bit valid           "Asserted if op is valid; has no effect on mask and attention";
    bit[6] select       "PDM to select";
    bit[6] mask         "PDM attention mask (mask && id)==(mask&&select) -> drive attention on next cycle";
    t_reve_r_debug_op op "Operation for selected PDM to perform";
    bit[16] arg          "Argument for debug op";
    bit[32] data         "Data for writing or instruction execution";
} t_reve_r_debug_mst;

/*t t_reve_r_debug_tgt
 */
typedef struct {
    bit valid               "Asserted by a PDM if driving the bus";
    bit[6] selected         "Number of the PDM driving, or 0 if not driving the bus";
    bit halted              "Asserted by a PDM if it is selected and halted since last ack; 0 otherwise";
    bit resumed             "Asserted by a PDM if it is selected and has resumed since last ack; 0 otherwise";
    bit hit_breakpoint      "Asserted by a PDM if it is selected and has hit breakpoint since lask ack; 0 otherwise";
    bit op_was_none "Asserted if the response is not valid";
    t_reve_r_debug_resp resp "Response from a requested op - only one op should be requested for each response";
    bit[32] data             "Data from a completed transaction; 0 otherwise";

    bit attention           "Asserted by a PDM if it has unacknowledged halt, breakpoint hit, resumption";
    bit[6] mask             "Mask received by PDM that matches the acknowledge - all PDMs will drive the same value";
} t_reve_r_debug_tgt;

