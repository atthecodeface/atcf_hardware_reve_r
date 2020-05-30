/** @copyright (C) 2017-20,  Gavin J Stark.  All rights reserved.
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
 * @file   reve_r_trace.h
 * @brief  Header file for Reve-R trace types
 *
 */
/*a Includes */
include "reve_r.h"

/*a Types */
/*t t_reve_r_trace
 */
typedef struct {
    // Following are valid at commit stage of pipeline
    bit                instr_valid;
    t_riscv_mode       mode          "Mode of instruction";
    bit[32]            instr_pc      "Program counter of the instruction";
    bit[32]            instruction   "Instruction word being decoded - without debug";
    bit                branch_taken  "Asserted if a branch is being taken";
    bit[32]            branch_target "Target of branch if being taken";
    bit                trap          "Asserted if a trap is taken (including interrupt) - nonseq";
    bit                ret           "Asserted if an [m]ret instruction is taken - nonseq";
    bit                jalr          "Asserted if a jalr instruction is taken - nonseq";
    // Following are valid at rfw stage of pipeline
    bit                rfw_retire "Asserted if an instruction is being retired";
    bit                rfw_data_valid;
    bit[5]             rfw_rd;
    bit[32]            rfw_data   "Result of ALU/memory operation for the instruction";
    // Following are anywhere
    bit                bkpt_valid;
    bit[4]             bkpt_reason;
    // Needs tag?
} t_reve_r_trace;

/*t t_reve_r_packed_trace_control
 */
typedef struct {
    bit enable     "Global enable";
    bit enable_control;
    bit enable_pc;
    bit enable_rfd;
    bit enable_breakpoint;
    bit valid;
} t_reve_r_packed_trace_control;

/*t t_reve_r_packed_trace
  The packed trace takes an i32 trace
*/
typedef struct {
    bit                seq_valid;
    bit[3]             seq;

    bit                nonseq_valid;
    bit[2]             nonseq;

    bit                bkpt_valid;
    bit[4]             bkpt;

    bit                data_valid;
    bit                data_reason;
    bit[40]            data;

    bit[3]             compressed_data_nybble "Nybble at which data nybbles will start in compressed stream, if required";
    bit[4]             compressed_data_num_bytes "Extra";
} t_reve_r_packed_trace;

/*t t_reve_r_compressed_trace
  The compressed trace is designed to come out as a sequence of nybbles.

  The nybbles are:

  0000   => skip
  0SSS   => SSS (1 to 7 sequential executions)
  10RR   => RR non-sequential reason (trap, ret, jalr, other branch); PC should come next
  1100 RNNN {DDDD}2N => Reason R 2N nybbles of data DDDD+
    R => PC, rfw + data [future? , data mem address, access, data]
  1101 NNNN  => breakpoint
  111x       => reserved

  The actual trace from the compression currently comes out as four separate fields

  sequential - three bits plus a valid bit

  nonsequential reason - two bits plus a valid bit

  breakpoint reason - four bits plus a valid bit

  eiter address or data - two reason bits, 4 bits of # bytes, and 64 bits of data, plus a valid bit


  A nybble stream should be constructed from:
    a valid 0SSS sequential nybble (if necessary)
    a valid 10RR nonsequential reason (if necessary)
    a valid 1101 NNNN breakpoint reason (if necessary)
    a valid data starting with 1100, then RNNN, then the required number of nybbles

  In a single clock tick one may need 1 seq nybble, 1 nonseq nybble, 2 breakpoint nybbles, and 12 data nybbles
  Total is 16 nybbles or 64 bits (for 40-bit data)

  A decompressor can take a nybble stream and produce a corresponding
  trace - but the timing is lost in this process.
 */
typedef struct {
    bit[5]  valid;
    bit[64] data;
} t_reve_r_compressed_trace;

/*t t_reve_r_decompressed_trace
  The decompressed trace undoes the trace compression
 */
typedef struct {
    bit                seq_valid;
    bit[3]             seq;
    
    bit                branch_taken "Asserted if a branch is being taken";
    bit                trap          "Asserted if a trap is taken (including interrupt) - nonseq";
    bit                ret           "Asserted if an [m]ret instruction is taken - nonseq";
    bit                jalr          "Asserted if a jalr instruction is taken - nonseq";

    bit                pc_valid;
    bit[32]            pc            "PC if pc_valid";

    bit                rfw_data_valid;
    bit[5]             rfw_rd;
    bit[32]            rfw_data   "Result of ALU/memory operation for the instruction";

    bit                bkpt_valid;
    bit[4]             bkpt_reason;
} t_reve_r_decompressed_trace;


