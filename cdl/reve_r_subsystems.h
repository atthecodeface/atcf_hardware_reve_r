/** @copyright (C) 2016-2018,  Gavin J Stark.  All rights reserved.
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
include "types/apb.h"
include "types/jtag.h"
include "utils/jtag_modules.h"
include "cpu/riscv/riscv.h"
include "cpu/riscv/riscv_internal_types.h"
include "srams.h"

/*a Implementations of CPUs with memories */
/*m reve_r_subsystem_generic  - Generic Reve-r implementation with pipeline length of 2+

 reve_r_config should be HARDWIRED (not off registers) to force logic to be
 discarded at synthesis

 alternatively submodules may be built with appropriate force's set to
 force discard of logic.
*/
extern
module reve_r_subsystem_generic( clock clk,
                                 input bit reset_n,
                                 input bit proc_reset_n,
                                 input t_riscv_irqs             irqs               "Interrupts in to the CPU",
                                 output t_riscv_mem_access_req  data_access_req,
                                 input  t_riscv_mem_access_resp data_access_resp,
                                 output t_apb_request           apb_request,
                                 input  t_apb_response          apb_response,
                                 input t_sram_access_req sram_access_req,
                                 output t_sram_access_resp sram_access_resp,
                                 input  t_riscv_debug_mst               debug_mst,
                                 output t_riscv_debug_tgt               debug_tgt,
                                 input  t_riscv_config          riscv_config,
                                 output t_riscv_i32_trace       trace
    )
{
    timing from rising clock clk apb_request;
    timing to   rising clock clk apb_response;
    timing from rising clock clk data_access_req;
    timing to   rising clock clk data_access_resp;
    timing to   rising clock clk sram_access_req;
    timing from rising clock clk sram_access_resp;
    timing to   rising clock clk riscv_config;
    timing to   rising clock clk debug_mst;
    timing from rising clock clk debug_tgt;
    timing to   rising clock clk irqs;
    timing from rising clock clk trace;
    timing comb input riscv_config;
    timing comb input data_access_resp;
    timing comb input apb_response;
    timing comb output trace;
    timing comb output debug_tgt;
}

/*m reve_r_subsystem_3  - same as reve_r_subsystem_generic

 This module includes a 2-stage Reve-r processor pipeline, with
 a simple shared 64kB SRAM for instructions and data at address 0.
 Peripherals are accessed at 1MB and above.

 The Reve-r processor clocks at most on every other cycle; instruction fetch 
 is performed during the second clock tick of a RISC-V processor cycle. Data
 writes are performed during the first clock tick; if data reads are required,
 or instruction fetches from unaligned memory locations are required, then
 the RISC-V processor may take be held for more clock ticks.

 riscv_config should be HARDWIRED (not off registers) to force logic to be
 discarded at synthesis

 alternatively submodules may be built with appropriate force's set to
 force discard of logic.
*/
extern
module reve_r_subsystem_3( clock clk,
                                  input bit reset_n,
                                  input bit proc_reset_n,
                                  input t_riscv_irqs             irqs               "Interrupts in to the CPU",
                                  output t_riscv_mem_access_req  data_access_req,
                                  input  t_riscv_mem_access_resp data_access_resp,
                                  output t_apb_request           apb_request,
                                  input  t_apb_response          apb_response,
                                  input t_sram_access_req sram_access_req,
                                  output t_sram_access_resp sram_access_resp,
                                  input  t_riscv_debug_mst               debug_mst,
                                  output t_riscv_debug_tgt               debug_tgt,
                                  input  t_riscv_config          riscv_config,
                                  output t_riscv_i32_trace       trace
    )
{
    timing from rising clock clk apb_request;
    timing to   rising clock clk apb_response;
    timing from rising clock clk data_access_req;
    timing to   rising clock clk data_access_resp;
    timing to   rising clock clk sram_access_req;
    timing from rising clock clk sram_access_resp;
    timing to   rising clock clk riscv_config;
    timing to   rising clock clk debug_mst;
    timing from rising clock clk debug_tgt;
    timing to   rising clock clk irqs;
    timing from rising clock clk trace;
    timing comb input riscv_config;
    timing comb input data_access_resp;
    timing comb input apb_response;
    timing comb output trace;
    timing comb output debug_tgt;
}

/*m reve_r_subsystem_5 - same as reve_r_subsystem_generic

 riscv_config should be HARDWIRED (not off registers) to force logic to be
 discarded at synthesis

 alternatively submodules may be built with appropriate force's set to
 force discard of logic.
*/
extern
module reve_r_subsystem_5( clock clk,
                                  input bit reset_n,
                                  input bit proc_reset_n,
                                  input t_riscv_irqs             irqs               "Interrupts in to the CPU",
                                  output t_riscv_mem_access_req  data_access_req,
                                  input  t_riscv_mem_access_resp data_access_resp,
                                  output t_apb_request           apb_request,
                                  input  t_apb_response          apb_response,
                                  input t_sram_access_req sram_access_req,
                                  output t_sram_access_resp sram_access_resp,
                                  input  t_riscv_debug_mst               debug_mst,
                                  output t_riscv_debug_tgt               debug_tgt,
                                  input  t_riscv_config          riscv_config,
                                  output t_riscv_i32_trace       trace
    )
{
    timing from rising clock clk apb_request;
    timing to   rising clock clk apb_response;
    timing from rising clock clk data_access_req;
    timing to   rising clock clk data_access_resp;
    timing to   rising clock clk sram_access_req;
    timing from rising clock clk sram_access_resp;
    timing to   rising clock clk riscv_config;
    timing to   rising clock clk debug_mst;
    timing from rising clock clk debug_tgt;
    timing to   rising clock clk irqs;
    timing from rising clock clk trace;
    timing comb input riscv_config;
    timing comb input data_access_resp;
    timing comb input apb_response;
    timing comb output trace;
    timing comb output debug_tgt;
}

