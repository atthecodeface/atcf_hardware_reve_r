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
 * @file   riscv_submodules.cdl
 * @brief  Submodule declarations for building RISC-V implementations
 *
 */

/*a Includes
 */
include "reve_r.h"
include "reve_r_pipeline_types.h"
include "reve_r_internal_types.h"

/*a Modules
 */
/*m reve_r_i32_decode  */
extern
module reve_r_i32_decode( input t_riscv_i32_inst instruction,
                         output t_riscv_i32_decode idecode,
                         input  t_riscv_config          riscv_config
)
{
    timing comb input instruction, riscv_config;
    timing comb output idecode;
}

/*m reve_r_i32c_decode  */
extern
module reve_r_i32c_decode( input t_riscv_i32_inst instruction,
                          output t_riscv_i32_decode idecode,
                          input  t_riscv_config          riscv_config
)
{
    timing comb input instruction, riscv_config;
    timing comb output idecode;
}

/*m reve_r_alu  */
extern
module reve_r_alu( input t_riscv_i32_decode      idecode,
                      input t_riscv_word            pc,
                      input t_riscv_word            rs1,
                      input t_riscv_word            rs2,
                      output t_riscv_i32_alu_result alu_result
)
{
    timing comb input  idecode, pc, rs1, rs2;
    timing comb output alu_result;
}

/*m reve_r_dmem_request */
extern module reve_r_dmem_request( input  t_riscv_i32_dmem_exec     dmem_exec,
                                      output t_riscv_i32_dmem_request  dmem_request
    )
{
    timing comb input  dmem_exec;
    timing comb output dmem_request;
}

/*m reve_r_dmem_read_data */
extern module reve_r_dmem_read_data( input t_riscv_i32_dmem_request dmem_request,
                                 input t_riscv_word             last_data,
                                 input t_riscv_mem_access_resp  dmem_access_resp,
                                 output t_riscv_word            dmem_read_data
    )
{
    timing comb input dmem_request, dmem_access_resp, last_data;
    timing comb output dmem_read_data;
}

/*m reve_r_muldiv */
extern module reve_r_muldiv( clock clk,
                         input bit reset_n,
                         input t_riscv_i32_coproc_controls  coproc_controls,
                         output t_riscv_i32_coproc_response coproc_response,
                         input t_riscv_config riscv_config
)
{
    timing to   rising clock clk coproc_controls, riscv_config;
    timing from rising clock clk coproc_response;
}
