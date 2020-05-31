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
 * @file   riscv.h
 * @brief  Header file for RISC-V implementations
 *
 */

/*a Constants
 *
 * Constants for the RISC-V implementation; can be overridden in CDL
 * builds with a dc: option in the model_list
 */

// Only place we are allowed to include reve_r_config
include "reve_r_config.h"

/*a Basic types
 */
/*t t_reve_r_mode
 */
typedef enum[3] {
    rv_mode_user       = 3b000, // matches the encoding in table 1.1 of v1.10 privilege spec
    rv_mode_supervisor = 3b001, // matches the encoding in table 1.1 of v1.10 privilege spec
    rv_mode_machine    = 3b011, // matches the encoding in table 1.1 of v1.10 privilege spec
    rv_mode_debug      = 3b111, // all 1s so that it is a superset of machine mode
} t_reve_r_mode;

/*t t_reve_r_irqs
 *
 * Note that USIP and SSIP are local to the RISC-V hart
 *
 * Note that meip, seip and ueip are effectively three separate interrupt pins to the RISC-V
 *
 */
typedef struct {
    bit nmi;
    bit meip          "External interrupt pending 'for machine mode'";
    bit seip          "External interrupt pending 'for supervisor mode' - actually, it goes to machine mode";
    bit ueip          "External interrupt pending 'for user mode' - actually, it goes to machine mode";
    bit mtip          "Timer interrupt, set by memory-mapped timer";
    bit msip          "Read-write in a memory-mapped register";
    bit[64] time      "Global time concept; may be tied low if user time CSR is not required";
} t_reve_r_irqs;

/*t t_reve_r_config
 */
typedef struct {
    bit      i32c;
    bit      e32;
    bit      i32m;
    bit      i32m_fuse;
    bit      debug_enable;
    bit      coproc_disable;
    bit      unaligned_mem;   // if clear, trap on unaligned memory loads/stores
    bit      mem_abort_late;  // if clear memory aborts must occur in the first cycle
} t_reve_r_config;

