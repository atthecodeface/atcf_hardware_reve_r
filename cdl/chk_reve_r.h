/** @copyright (C) 2019,  Gavin J Stark.  All rights reserved.
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
 * @file   chk_riscv.h
 * @brief  Header file for RISC-V checkers
 *
 */

/*a Includes */
include "reve_r_fetch.h"
include "reve_r_trace.h"

/*a Risc-V instruction checkers */
/*m chk_reve_r_ifetch */
extern module chk_reve_r_ifetch( clock clk,
                                input t_reve_r_fetch_req  fetch_req,
                                input t_reve_r_fetch_resp fetch_resp,
                                output bit error_detected,
                                output bit[32] cycle )
{
    timing to   rising clock clk fetch_req, fetch_resp;
    timing from rising clock clk error_detected, cycle;
}

/*m chk_reve_r_trace */
extern module chk_reve_r_trace( clock clk,
                               input t_reve_r_trace trace,
                                output bit error_detected,
                                output bit[32] cycle )
{
    timing to   rising clock clk trace;
    timing from rising clock clk error_detected, cycle;
}

