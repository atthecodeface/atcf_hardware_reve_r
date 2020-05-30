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
    name = "csr"
    src_dir      = "cdl"
    tb_src_dir   = "tb_cdl"
    libraries = {"std":True}
    cdl_include_dirs = ["cdl"]
    export_dirs = cdl_include_dirs + [ src_dir ]
    modules = []
    modules += [ CdlModule("reve_r_csrs") ]
    modules += [ CdlModule("reve_r_csrs_machine_only",           cdl_filename="reve_r_csrs", constants=reve_r_machine_constants) ]
    modules += [ CdlModule("reve_r_csrs_machine_debug",          cdl_filename="reve_r_csrs", constants=reve_r_md_constants)      ]
    modules += [ CdlModule("reve_r_csrs_machine_debug_user",     cdl_filename="reve_r_csrs", constants=reve_r_mdu_constants)     ]
    modules += [ CdlModule("reve_r_csrs_machine_debug_user_irq", cdl_filename="reve_r_csrs", constants=reve_r_mdui_constants)    ]

    # The decode modules are also configured by machine, debug, user etc enable; numerous modules should be built, probably
    modules += [ CdlModule("reve_r_csrs_decode") ]
    pass

class DecodeModules(cdl_desc.Modules):
    name = "decode"
    src_dir      = "cdl"
    tb_src_dir   = "tb_cdl"
    libraries = {"std":True}
    cdl_include_dirs = ["cdl"]
    export_dirs = cdl_include_dirs + [ src_dir ]
    modules = []
    modules += [ CdlModule("reve_r_csrs_decode") ]
    modules += [ CdlModule("reve_r_i32_decode") ]
    modules += [ CdlModule("reve_r_e32_decode",                   cdl_filename="reve_r_i32_decode", constants={"rv_cfg_e32_force_enable":1}) ]
    modules += [ CdlModule("reve_r_i32c_decode") ]
    modules += [ CdlModule("reve_r_e32c_decode",                  cdl_filename="reve_r_i32c_decode", constants={"rv_cfg_e32_force_enable":1}) ]
    modules += [ CdlModule("reve_r_debug_decode") ]
    pass

class CoreModules(cdl_desc.Modules):
    name = "core"
    src_dir      = "cdl"
    tb_src_dir   = "tb_cdl"
    libraries = {"std":True}
    cdl_include_dirs = ["cdl"]
    export_dirs = cdl_include_dirs + [ src_dir ]
    modules = []
    modules += [ CdlModule("reve_r_alu") ]
    modules += [ CdlModule("reve_r_muldiv") ]
    pass

class PipelineModules(cdl_desc.Modules):
    name = "pipeline"
    src_dir      = "cdl"
    tb_src_dir   = "tb_cdl"
    libraries = {"std":True}
    cdl_include_dirs = ["cdl"]
    export_dirs = cdl_include_dirs + [ src_dir ]
    modules = []
    pass

class TraceModules(cdl_desc.Modules):
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

