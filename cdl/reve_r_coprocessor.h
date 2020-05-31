/** @copyright (C) 2016-2017,  Gavin J Stark.  All rights reserved.
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
 * @file   reve_r_coprocessor.h
 * @brief  Types for Reve-r coprocessors
 *
 */

/*a Includes */
include "reve_r.h"
include "reve_r_decode.h"

/*a Types */
/*t t_reve_r_coproc_controls
 */
typedef struct {
    bit                     dec_idecode_valid "Mid-cycle: validates dec_idecode";
    t_reve_r_decode      dec_idecode "Mid-cycle: Idecode for the next cycle";
    bit                     dec_to_alu_blocked "Late in the cycle: if set, ALU will not take decode; note that ALU flush overpowers this";
    bit[32]            alu_rs1     "Early in cycle (after some muxes)";
    bit[32]            alu_rs2     "Early in cycle (after some muxes)";
    bit                     alu_flush_pipeline "Late in cycle: If asserted, flush everything prior to alu; will only be asserted during a cycle if first cycle if ALU instruction - or if alu_cannot_start";
    bit                     alu_cannot_start "Late in cycle: If asserted, alu_idecode may be valid but rs1/rs2 are not; once deasserted it remains deasserted until a new ALU instruction starts";
    bit                     alu_data_not_ready   "Early in cycle (independent of coprocessors): If asserted, alu_idecode may be valid but rs1/rs2 are not; once deasserted it remains deasserted until a new ALU instruction starts";
    bit                     alu_cannot_complete "Late in cycle: If asserted, alu cannot complete because it is still working on its operation";
} t_reve_r_coproc_controls;

/*t t_reve_r_coproc_response
 */
typedef struct {
    bit          cannot_start "If asserted, block start of the ALU stage - the instruction is then tried again in the next cycle, but can be interrupted";
    bit[32] result;
    bit          result_valid "Early in cycle, if asserted then coproc overcomes the ALU result";
    bit          cannot_complete "Early in cycle: if deasserted the module is performing a calculation that has not produced a valid result yet (feeds back in to controls alu_cannot_complete)";
} t_reve_r_coproc_response;

/*m reve_r_muldiv */
extern module reve_r_muldiv( clock clk,
                         input bit reset_n,
                         input t_reve_r_coproc_controls  coproc_controls,
                         output t_reve_r_coproc_response coproc_response,
                         input t_reve_r_config riscv_config
)
{
    timing to   rising clock clk coproc_controls, riscv_config;
    timing from rising clock clk coproc_response;
}
