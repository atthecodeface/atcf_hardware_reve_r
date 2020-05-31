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

/*a Modules
 */
/*m reve_r_i32_decode  */
extern
module reve_r_i32_decode( input t_reve_r_inst instruction,
                         output t_reve_r_decode idecode,
                         input  t_reve_r_config          riscv_config
)
{
    timing comb input instruction, riscv_config;
    timing comb output idecode;
}

/*m reve_r_i32c_decode  */
extern
module reve_r_i32c_decode( input t_reve_r_inst instruction,
                          output t_reve_r_decode idecode,
                          input  t_reve_r_config          riscv_config
)
{
    timing comb input instruction, riscv_config;
    timing comb output idecode;
}

/*m reve_r_alu  */
extern
module reve_r_alu( input t_reve_r_decode      idecode,
                      input bit[32]            pc,
                      input bit[32]            rs1,
                      input bit[32]            rs2,
                      output t_alu_result alu_result
)
{
    timing comb input  idecode, pc, rs1, rs2;
    timing comb output alu_result;
}

/*m reve_r_dmem_request */
extern module reve_r_dmem_request( input  t_dmem_exec     dmem_exec,
                                   output t_dmem_request  dmem_request
    )
{
    timing comb input  dmem_exec;
    timing comb output dmem_request;
}

/*m reve_r_dmem_read_data */
extern module reve_r_dmem_read_data( input t_dmem_request dmem_request,
                                 input bit[32]             last_data,
                                 input t_reve_r_dmem_access_resp  dmem_access_resp,
                                 output bit[32]            dmem_read_data
    )
{
    timing comb input dmem_request, dmem_access_resp, last_data;
    timing comb output dmem_read_data;
}

