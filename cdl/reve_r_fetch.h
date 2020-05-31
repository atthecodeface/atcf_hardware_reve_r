include "reve_r.h"
/*t t_reve_r_fetch_req_type
 *
 *
 *
 */
typedef enum[3] {
    rv_fetch_none           = 3b000, // address is invalid - next non-none request MUST be nonsequential
    rv_fetch_nonsequential  = 3b001, // address is anything, and will be valid late in the cycle
    rv_fetch_sequential_32  = 3b010, // address=+4 from last cycle
    rv_fetch_repeat         = 3b011, // address will be same as last cycle
    rv_fetch_sequential_16  = 3b110, // address=+2 from last cycle
} t_reve_r_fetch_req_type;

/*t t_reve_r_fetch_req
 *
 * Fetch request comes from the start of pipeline control and
 * is delivered to the pipeline fetch data through any prefetch
 * mechanism.
 * The fetch request type indicates what data is needed next in
 * conjunction with the address
 *
 */
typedef struct {
    bit      flush_pipeline         "Asserted if prefetch should flush any pipeline";
    t_reve_r_fetch_req_type req_type "Request type - none, nonseq, seq, repeat; if flush only none, nonseq";
    bit[32]  address;
    t_reve_r_mode mode;
} t_reve_r_fetch_req;

/*t t_reve_r_fetch_resp
 */
typedef struct {
    bit      valid;
    bit[32]  data;
    bit[2]   error "One bit per 16-bits of the data";
} t_reve_r_fetch_resp;

