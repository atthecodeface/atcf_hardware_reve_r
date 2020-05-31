/*t t_reve_r_dmem_access_req_type
 *
 * For an implementation that does not support atomics only 2 bits are used
 *
 */
typedef enum[5] {
    rv_dmem_access_idle        = 5b00000,
    rv_dmem_access_read        = 5b00001,
    rv_dmem_access_write       = 5b00010,
    rv_dmem_access_atomic_lr   = 5b10000,
    rv_dmem_access_atomic_sc   = 5b10001,
    rv_dmem_access_atomic_swap = 5b10010,
    rv_dmem_access_atomic_and  = 5b10100,
    rv_dmem_access_atomic_or   = 5b10101,
    rv_dmem_access_atomic_xor  = 5b10110,
    rv_dmem_access_atomic_add  = 5b11000,
    rv_dmem_access_atomic_umin = 5b11100,
    rv_dmem_access_atomic_smin = 5b11101,
    rv_dmem_access_atomic_umax = 5b11110,
    rv_dmem_access_atomic_smax = 5b11111,
    rv_dmem_access_nonatomic_mask = 5b00011
} t_reve_r_dmem_access_req_type;

/*t t_reve_r_dmem_access_req
 *
 * add atomic_aq and atomic_rl bits for atomics
 * atomic_aq means that all memory requests *after* this atomic must only be observable after the atomic is observable
 * atomic_rl means that all memory requests *prior* to this atomic must be observable before the atomic is observable
 *
 */
typedef struct {
    bit valid              "Asserted if a valid access request";
    t_reve_r_mode mode      "Mode of the access - usually the same as the pipeline execution, but not necessarily";
    t_reve_r_dmem_access_req_type req_type "Type of request";
    bit[32]  address       "Address of transaction - aligned to a word for atomics";
    bit      sequential    "Asserted if the transaction is guaranteed to be to the next word after the last access - this is a hint only";
    bit[4]   byte_enable   "Byte enables for writes, should be ignored by atomics";
    bit[32]  write_data    "Data for writing, or to be used in the atomic";
} t_reve_r_dmem_access_req;

/*t t_reve_r_dmem_access_resp
 *
 * This structure contains the response to a memory request, and memory return data
 *
 * Each request must be acknowledged
 * In the cycle following an acknowledged request an abort may be raised, which will force a data trap
 *
 * Responses can include an error indication?
 * Responses for atomics are the original read data, or the result of an 'store conditional'
 *
 * Note that the response in some circumstances is defined to be valid in the same cycle as the request.
 * In other circumstances it is defined to be valid in the cycle following a request.
 *
 * The signals do not change.
 *
 * For example, a very simple fetch/execute RISC-V implementation
 * requires the read response in the same cycle as a data memory
 * request, since execute (which includes the full memory access) is a
 * single cycle.
 *
 * However, a deeper pipeline RISC-V implementation such as pipeline3
 * issues a request in the ALU cycle and provides a whole cycle for an
 * SRAM access to satisfy any data memory read. Here, then, the
 * response is valid one cycle after the request.
 *
 * Note that the wait signal is valid with the data; but it also
 * applies to a memory cycle that is a write; that is, a write memory
 * cycle cannot complete if wait is asserted. The next request is
 * already being presented when the wait is given in response to the
 * previous request, though.
 *
 */
typedef struct {
    bit                  ack_if_seq        "Asserted if a sequential access request (if valid) would be taken";
    bit                  ack               "Asserted if an access request (if valid) would be taken; if this is asserted, ack_if_seq should be asserted too";
    bit                  abort_req         "If asserted (in the cycle after an acked request) then the data transaction must abort. Can be configured to work until access_complete, in conjunction with may_still_abort";
    bit                  may_still_abort   "If asserted (starting in the cycle after an acked request) then the data transaction may yet assert abort_req in a subsequent cycle (this blocks the starting of the exec stage of the following instruction). If pipeline is configured to not support late aborts then this signal is ignored.";
    bit                  access_complete   "Valid in the same cycle as read_data; must be set on writes as well as reads, as it completes an access";
    bit[32]              read_data         "Data returned from reading the requested address";
} t_reve_r_dmem_access_resp;

