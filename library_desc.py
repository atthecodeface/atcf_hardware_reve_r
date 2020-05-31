import cdl_desc
from cdl_desc import CdlModule, CdlSimVerilatedModule, CModel, CSrc

class Library(cdl_desc.Library):
    name="reve_r"
    pass

reve_r_machine_constants = {"rv_cfg_debug_force_disable":1, "rv_cfg_user_mode_enable":0, "rv_cfg_user_irq_mode_enable":0, "rv_cfg_supervisor_mode_enable":0, }
reve_r_md_constants      = {"rv_cfg_debug_force_disable":0, "rv_cfg_user_mode_enable":0, "rv_cfg_user_irq_mode_enable":0, "rv_cfg_supervisor_mode_enable":0, }
reve_r_mdu_constants     = {"rv_cfg_debug_force_disable":0, "rv_cfg_user_mode_enable":1, "rv_cfg_user_irq_mode_enable":0, "rv_cfg_supervisor_mode_enable":0, }
reve_r_mdui_constants    = {"rv_cfg_debug_force_disable":0, "rv_cfg_user_mode_enable":1, "rv_cfg_user_irq_mode_enable":1, "rv_cfg_supervisor_mode_enable":0, }

class CSRModules(cdl_desc.Modules):
    """
    These are CSR modules, which implement the decode of CSRs (which could be expanded by a user) and the CSRs themselves.

    The configuration of the CSR modules depends on the mode supported - for example, some CSRs do not exist in some configurations
    """
    name = "csr"
    src_dir      = "cdl"
    tb_src_dir   = "tb_cdl"
    libraries = {"std":True}
    cdl_include_dirs = ["cdl"]
    export_dirs = cdl_include_dirs + [ src_dir ]
    modules = []
    modules += [ CdlModule("reve_r_csrs") ]
    # modules += [ CdlModule("reve_r_csrs_machine_only",           cdl_filename="reve_r_csrs", constants=reve_r_machine_constants) ]
    # modules += [ CdlModule("reve_r_csrs_machine_debug",          cdl_filename="reve_r_csrs", constants=reve_r_md_constants)      ]
    # modules += [ CdlModule("reve_r_csrs_machine_debug_user",     cdl_filename="reve_r_csrs", constants=reve_r_mdu_constants)     ]
    # modules += [ CdlModule("reve_r_csrs_machine_debug_user_irq", cdl_filename="reve_r_csrs", constants=reve_r_mdui_constants)    ]

    # The decode modules are also configured by machine, debug, user etc enable; numerous modules should be built, probably
    # modules += [ CdlModule("reve_r_csrs_decode") ]
    pass

class DecodeModules(cdl_desc.Modules):
    """
    The instruction decode modules provide decode of RISC-V instructions (i32, i32c)
    """
    name = "decode"
    src_dir      = "cdl"
    tb_src_dir   = "tb_cdl"
    libraries = {"std":True}
    cdl_include_dirs = ["cdl"]
    export_dirs = cdl_include_dirs + [ src_dir ]
    modules = []
    # The following use reve_r_csrs_decode - so a specific instance could be selected based on config
    modules += [ CdlModule("reve_r_i32_decode") ]
    modules += [ CdlModule("reve_r_e32_decode",                   cdl_filename="reve_r_i32_decode", constants={"rv_cfg_e32_force_enable":1}) ]
    modules += [ CdlModule("reve_r_i32c_decode") ]
    modules += [ CdlModule("reve_r_e32c_decode",                  cdl_filename="reve_r_i32c_decode", constants={"rv_cfg_e32_force_enable":1}) ]
    # modules += [ CdlModule("reve_r_debug_decode") ] This has been removed; the code is in i32_decode
    pass

class CoreModules(cdl_desc.Modules):
    """
    These are processing modules used by the pipelines
    """
    name = "core"
    src_dir      = "cdl"
    tb_src_dir   = "tb_cdl"
    libraries = {"std":True}
    cdl_include_dirs = ["cdl"]
    export_dirs = cdl_include_dirs + [ src_dir ]
    modules = []
    modules += [ CdlModule("reve_r_alu") ]
    modules += [ CdlModule("reve_r_muldiv") ]
    modules += [ CdlModule("reve_r_dmem_request") ]
    modules += [ CdlModule("reve_r_dmem_read_data") ]
    pass

class PipelineModules(cdl_desc.Modules):
    """
    These are pipeline instances that use the decode, csrs and core modules
    They must be controlled by pipeline_control modules
    """
    name = "pipeline"
    src_dir      = "cdl"
    tb_src_dir   = "tb_cdl"
    libraries = {"std":True}
    cdl_include_dirs = ["cdl"]
    export_dirs = cdl_include_dirs + [ src_dir ]
    modules = []
    # The following includes decode (which is based on mode configs), and has a disableable compressed and coprocessor and e mode
    modules += [ CdlModule("reve_r_pipeline_dem_w") ]
    modules += [ CdlModule("reve_r_pipeline_d_e_m_w") ]
    pass

class PipelineControlModules(cdl_desc.Modules):
    """
    """
    name = "pipeline_control"
    src_dir      = "cdl"
    tb_src_dir   = "tb_cdl"
    libraries = {"std":True}
    cdl_include_dirs = ["cdl"]
    export_dirs = cdl_include_dirs + [ src_dir ]
    modules = []
    modules += [ CdlModule("reve_r_pipeline_control") ]
    modules += [ CdlModule("reve_r_pipeline_control_fetch_req") ]
    modules += [ CdlModule("reve_r_pipeline_control_fetch_data") ]
    modules += [ CdlModule("reve_r_pipeline_control_flow") ]
    modules += [ CdlModule("reve_r_pipeline_trap_interposer") ]
    modules += [ CdlModule("reve_r_pipeline_debug") ]
    pass

class SubsystemModules(cdl_desc.Modules):
    """
    Instantiation of a pipeline + control, debug, coprocessors,
    and trace, with 64kB SRAM and APB master interface
    """
    name = "subsystems"
    src_dir      = "cdl"
    tb_src_dir   = "tb_cdl"
    libraries = {"std":True}
    cdl_include_dirs = ["cdl"]
    export_dirs = cdl_include_dirs + [ src_dir ]
    modules = []
    modules += [ CdlModule("reve_r_subsystem_3") ]
    modules += [ CdlModule("reve_r_subsystem_5") ]
    pass

class TraceModules(cdl_desc.Modules):
    """
    The trace modules supply a standard interface out to provide trace information.
    There is also a simple standard trace compression supported.
    """
    name = "trace"
    src_dir      = "cdl"
    tb_src_dir   = "tb_cdl"
    libraries = {"std":True}
    cdl_include_dirs = ["cdl"]
    export_dirs = cdl_include_dirs + [ src_dir ]
    modules = []
    modules += [ CdlModule("reve_r_trace") ]
    modules += [ CdlModule("reve_r_trace_pack") ]
    modules += [ CdlModule("reve_r_trace_compression") ]
    modules += [ CdlModule("reve_r_trace_decompression") ]
    pass

