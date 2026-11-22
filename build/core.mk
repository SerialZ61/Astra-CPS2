# CPS2 emulation library. Paths are relative to the project root.
PI = vendor/pifba
BURN = $(PI)/burn
CPS = $(BURN)/capcom
CORE_INCLUDES = -Iengine -I$(BURN) -I$(CPS) -I$(PI)/cpu/cyclone -I$(PI)/cpu/z80 -I$(PI)/cpu/cz80 -I$(PI)/rpi
CORE_FLAGS = -DASTRA_CPS2 -DOOPSWARE_FIX -D__cdecl= -D__fastcall= -D_T= -fno-strict-aliasing -fwrapv -fno-delete-null-pointer-checks
CORE_C = $(BURN)/ym2151.c $(PI)/cpu/cz80/cz80.c $(PI)/rpi/unzip.c
CORE_ASM = $(PI)/cpu/cyclone/cyclone.s engine/wait_branch.s
CORE_CPP = engine/cps2.cpp engine/catalog.cpp engine/romzip.cpp $(PI)/cpu/z80/z80.cpp $(PI)/cpu/z80/z80daisy.cpp \
  $(addprefix $(BURN)/,burn.cpp load.cpp sek.cpp zet.cpp burn_sound.cpp burn_sound_c.cpp burn_ym2151.cpp eeprom_93cxx.cpp msm6295.cpp timer.cpp) \
  $(addprefix $(CPS)/,cps.cpp cps_draw.cpp cps_mem.cpp cps_obj.cpp cps_pal.cpp cps_run.cpp cps_rw.cpp cps_scr.cpp cpsr.cpp cpsrd.cpp cpst.cpp ctv.cpp dc_input.cpp ps.cpp ps_m.cpp ps_z.cpp qs.cpp qs_c.cpp qs_z.cpp cps2_crpt.cpp)
CORE_CPP += engine/wait_loops.cpp engine/revisions.cpp
CORE_CPP += $(addprefix $(CPS)/, \
  dc_1944.cpp dc_19xx.cpp dc_armwar.cpp dc_avsp.cpp dc_batcir.cpp dc_choko.cpp dc_csclub.cpp \
  dc_cyb.cpp dc_ddsom.cpp dc_ddtod.cpp dc_dimahoo.cpp dc_dstlk.cpp dc_ecofghtr.cpp dc_gigawing.cpp \
  dc_hsf2.cpp dc_jyangoku.cpp dc_megaman2.cpp dc_mmatrix.cpp dc_mpang.cpp dc_msh.cpp dc_mshvsf.cpp \
  dc_mvsc.cpp dc_nwarr.cpp dc_progear.cpp dc_pzloop2.cpp dc_qnd.cpp dc_ringdest.cpp dc_sfa.cpp \
  dc_sfa2.cpp dc_sfa3.cpp dc_sgemf.cpp dc_spf.cpp dc_ssf2.cpp dc_ssf2t.cpp dc_vhunt2.cpp \
  dc_vsav.cpp dc_vsav2.cpp dc_xmcota.cpp dc_xmvsf.cpp)
