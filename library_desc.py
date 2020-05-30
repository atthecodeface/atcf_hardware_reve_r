import cdl_desc
from cdl_desc import CdlModule, CdlSimVerilatedModule, CModel, CSrc

class Library(cdl_desc.Library):
    name="reve_r"
    pass

class PipelineModules(cdl_desc.Modules):
    name = "pipeline"
    src_dir      = "cdl"
    tb_src_dir   = "tb_cdl"
    libraries = {"std":True, "utils":True}
    cdl_include_dirs = ["cdl"]
    export_dirs = cdl_include_dirs + [ src_dir ]
    reve_r_machine_constants = {"rv_cfg_debug_force_disable":1, "rv_cfg_user_mode_enable":0, "rv_cfg_user_irq_mode_enable":0, "rv_cfg_supervisor_mode_enable":0, }
    reve_r_md_constants      = {"rv_cfg_debug_force_disable":0, "rv_cfg_user_mode_enable":0, "rv_cfg_user_irq_mode_enable":0, "rv_cfg_supervisor_mode_enable":0, }
    reve_r_mdu_constants     = {"rv_cfg_debug_force_disable":0, "rv_cfg_user_mode_enable":1, "rv_cfg_user_irq_mode_enable":0, "rv_cfg_supervisor_mode_enable":0, }
    reve_r_mdui_constants    = {"rv_cfg_debug_force_disable":0, "rv_cfg_user_mode_enable":1, "rv_cfg_user_irq_mode_enable":1, "rv_cfg_supervisor_mode_enable":0, }
    modules = []
    modules += [ CdlModule("reve_r_alu") ]
    modules += [ CdlModule("reve_r_csrs") ]
    modules += [ CdlModule("reve_r_csrs_machine_only",           cdl_filename="reve_r_csrs", constants=reve_r_machine_constants) ]
    modules += [ CdlModule("reve_r_csrs_machine_debug",          cdl_filename="reve_r_csrs", constants=reve_r_md_constants)      ]
    modules += [ CdlModule("reve_r_csrs_machine_debug_user",     cdl_filename="reve_r_csrs", constants=reve_r_mdu_constants)     ]
    modules += [ CdlModule("reve_r_csrs_machine_debug_user_irq", cdl_filename="reve_r_csrs", constants=reve_r_mdui_constants)    ]
    modules += [ CdlModule("reve_r_csrs_decode") ]
    modules += [ CdlModule("reve_r_i32_decode") ]
    modules += [ CdlModule("reve_r_e32_decode",                   cdl_filename="reve_r_i32_decode", constants={"rv_cfg_e32_force_enable":1}) ]
    modules += [ CdlModule("reve_r_i32c_decode") ]
    modules += [ CdlModule("reve_r_e32c_decode",                  cdl_filename="reve_r_i32c_decode", constants={"rv_cfg_e32_force_enable":1}) ]
    modules += [ CdlModule("reve_r_debug_decode") ]
    modules += [ CdlModule("reve_r_muldiv") ]
    pass

