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
 * @file   riscv_modules.h
 * @brief  Header file for RISC-V implementations
 *
 */

/*a Includes */
include "reve_r.h"
include "reve_r_pipeline_types.h"  // for pipeline control, response, fetch_data
include "reve_r_coprocessor.h" // for coproc controls and response
include "reve_r_debug.h" // for debug_mst/tgt
include "reve_r_fetch.h" // for fetch request/data
include "reve_r_trace.h" // for trace

/*a Implementations */
/*m reve_r_pipeline_demw
 */
extern
module reve_r_pipeline_demw( clock clk,
                            input bit reset_n,
                            input t_reve_r_pipeline_control    pipeline_control,
                            input t_reve_r_pipeline_fetch_data  pipeline_fetch_data,
                            input  t_reve_r_dmem_access_resp     dmem_access_resp,
                            output t_reve_r_pipeline_response   pipeline_response,
                            input t_reve_r_coproc_response  coproc_response,
                            input bit[32]                 csr_read_data,
                            input  t_reve_r_config              riscv_config
)
{
    timing from rising clock clk pipeline_response;
    timing to   rising clock clk dmem_access_resp, coproc_response, csr_read_data;
    timing to   rising clock clk riscv_config;
    timing comb input riscv_config;
    timing comb output pipeline_response;
}

/*m reve_r_pipeline_d_e_m_w
 */
extern
module reve_r_pipeline_d_e_m_w( clock clk,
                             input bit reset_n,
                             input t_reve_r_pipeline_control     pipeline_control,
                             output t_reve_r_pipeline_response   pipeline_response,
                             input t_reve_r_pipeline_fetch_data  pipeline_fetch_data,
                             input  t_reve_r_dmem_access_resp dmem_access_resp,
                             input t_reve_r_coproc_response   coproc_response,
                             input bit[32]                 csr_read_data,
                             input  t_reve_r_config          riscv_config
)
{
    timing from rising clock clk pipeline_response;
    timing to   rising clock clk dmem_access_resp, pipeline_control, pipeline_fetch_data, coproc_response, csr_read_data;
    timing to   rising clock clk riscv_config;
    timing comb input riscv_config;
    timing comb output pipeline_response;
}

