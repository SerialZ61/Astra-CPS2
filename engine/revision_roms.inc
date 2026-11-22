// Physical chip metadata: MAME CPS2 (see qa/unregistered-source.md).

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_1944dRomDesc[] = {
    {"nffud.03", 0x080000, 0x28e8aae4, 1 | BRF_ESS | BRF_PRG},
    {"nff.04", 0x080000, 0xdba1c66e, 1 | BRF_ESS | BRF_PRG},
    {"nffu.05", 0x080000, 0xea813eb7, 1 | BRF_ESS | BRF_PRG},
    {"nff.13m", 0x400000, 0xc9fca741, 3 | BRF_GRA},
    {"nff.15m", 0x400000, 0xf809d898, 3 | BRF_GRA},
    {"nff.17m", 0x400000, 0x15ba4507, 3 | BRF_GRA},
    {"nff.19m", 0x400000, 0x3dd41b8c, 3 | BRF_GRA},
    {"nff.14m", 0x100000, 0x3fe3a54b, 3 | BRF_GRA},
    {"nff.16m", 0x100000, 0x565cd231, 3 | BRF_GRA},
    {"nff.18m", 0x100000, 0x63ca5988, 3 | BRF_GRA},
    {"nff.20m", 0x100000, 0x21eb8f3b, 3 | BRF_GRA},
    {"nff.01", 0x020000, 0xd2e44318, 4 | BRF_ESS | BRF_PRG},
    {"nff.11m", 0x400000, 0x243e4e05, 5 | BRF_SND},
    {"nff.12m", 0x400000, 0x4fcf1600, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_1944d, BurnDrvCps1944, "1944d", "1944: The Loop Master (USA 000620 Phoenix Edition)", "1944", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_19xxdRomDesc[] = {
    {"19xud.03", 0x080000, 0xf81b60e5, 1 | BRF_ESS | BRF_PRG},
    {"19xud.04", 0x080000, 0xcc44638c, 1 | BRF_ESS | BRF_PRG},
    {"19xud.05", 0x080000, 0x33a168de, 1 | BRF_ESS | BRF_PRG},
    {"19xud.06", 0x080000, 0xe0111282, 1 | BRF_ESS | BRF_PRG},
    {"19x.07", 0x080000, 0x61c0296c, 1 | BRF_ESS | BRF_PRG},
    {"19x.13m", 0x080000, 0x427aeb18, 3 | BRF_GRA},
    {"19x.15m", 0x080000, 0x63bdbf54, 3 | BRF_GRA},
    {"19x.17m", 0x080000, 0x2dfe18b5, 3 | BRF_GRA},
    {"19x.19m", 0x080000, 0xcbef9579, 3 | BRF_GRA},
    {"19x.14m", 0x200000, 0xe916967c, 3 | BRF_GRA},
    {"19x.16m", 0x200000, 0x6e75f3db, 3 | BRF_GRA},
    {"19x.18m", 0x200000, 0x2213e798, 3 | BRF_GRA},
    {"19x.20m", 0x200000, 0xab9d5b96, 3 | BRF_GRA},
    {"19x.01", 0x020000, 0xef55195e, 4 | BRF_ESS | BRF_PRG},
    {"19x.11m", 0x200000, 0xd38beef3, 5 | BRF_SND},
    {"19x.12m", 0x200000, 0xd47c96e2, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_19xxd, BurnDrvCps19xx, "19xxd", "19XX: The War Against Destiny (USA 951207 Phoenix Edition)", "19xx", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_armwar1dRomDesc[] = {
    {"pwged.03b", 0x080000, 0x496bd483, 1 | BRF_ESS | BRF_PRG},
    {"pwged.04b", 0x080000, 0x9bd6a38f, 1 | BRF_ESS | BRF_PRG},
    {"pwged.05a", 0x080000, 0x4c11d30f, 1 | BRF_ESS | BRF_PRG},
    {"pwg.06", 0x080000, 0x87a60ce8, 1 | BRF_ESS | BRF_PRG},
    {"pwg.07", 0x080000, 0xf7b148df, 1 | BRF_ESS | BRF_PRG},
    {"pwg.08", 0x080000, 0xcc62823e, 1 | BRF_ESS | BRF_PRG},
    {"pwg.09", 0x080000, 0xddc85ca6, 1 | BRF_ESS | BRF_PRG},
    {"pwg.10", 0x080000, 0x07c4fb28, 1 | BRF_ESS | BRF_PRG},
    {"pwg.13m", 0x400000, 0xae8fe08e, 3 | BRF_GRA},
    {"pwg.15m", 0x400000, 0xdb560f58, 3 | BRF_GRA},
    {"pwg.17m", 0x400000, 0xbc475b94, 3 | BRF_GRA},
    {"pwg.19m", 0x400000, 0x07439ff7, 3 | BRF_GRA},
    {"pwg.14m", 0x100000, 0xc3f9ba63, 3 | BRF_GRA},
    {"pwg.16m", 0x100000, 0x815b0e7b, 3 | BRF_GRA},
    {"pwg.18m", 0x100000, 0x0109c71b, 3 | BRF_GRA},
    {"pwg.20m", 0x100000, 0xeb75ffbe, 3 | BRF_GRA},
    {"pwg.01", 0x020000, 0x18a5c0e4, 4 | BRF_ESS | BRF_PRG},
    {"pwg.02", 0x020000, 0xc9dfffa6, 4 | BRF_ESS | BRF_PRG},
    {"pwg.11m", 0x200000, 0xa78f7433, 5 | BRF_SND},
    {"pwg.12m", 0x200000, 0x77438ed0, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_armwar1d, BurnDrvCpsArmwar, "armwar1d", "Armored Warriors (Europe 941011 Phoenix Edition)", "armwar", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_armwaru1RomDesc[] = {
    {"pwgu.03a", 0x080000, 0x73d397b1, 1 | BRF_ESS | BRF_PRG},
    {"pwgu.04a", 0x080000, 0x1f1de215, 1 | BRF_ESS | BRF_PRG},
    {"pwgu.05a", 0x080000, 0x835fbe73, 1 | BRF_ESS | BRF_PRG},
    {"pwg.06", 0x080000, 0x87a60ce8, 1 | BRF_ESS | BRF_PRG},
    {"pwg.07", 0x080000, 0xf7b148df, 1 | BRF_ESS | BRF_PRG},
    {"pwg.08", 0x080000, 0xcc62823e, 1 | BRF_ESS | BRF_PRG},
    {"pwg.09", 0x080000, 0xddc85ca6, 1 | BRF_ESS | BRF_PRG},
    {"pwg.10", 0x080000, 0x07c4fb28, 1 | BRF_ESS | BRF_PRG},
    {"pwg.13m", 0x400000, 0xae8fe08e, 3 | BRF_GRA},
    {"pwg.15m", 0x400000, 0xdb560f58, 3 | BRF_GRA},
    {"pwg.17m", 0x400000, 0xbc475b94, 3 | BRF_GRA},
    {"pwg.19m", 0x400000, 0x07439ff7, 3 | BRF_GRA},
    {"pwg.14m", 0x100000, 0xc3f9ba63, 3 | BRF_GRA},
    {"pwg.16m", 0x100000, 0x815b0e7b, 3 | BRF_GRA},
    {"pwg.18m", 0x100000, 0x0109c71b, 3 | BRF_GRA},
    {"pwg.20m", 0x100000, 0xeb75ffbe, 3 | BRF_GRA},
    {"pwg.01", 0x020000, 0x18a5c0e4, 4 | BRF_ESS | BRF_PRG},
    {"pwg.02", 0x020000, 0xc9dfffa6, 4 | BRF_ESS | BRF_PRG},
    {"pwg.11m", 0x200000, 0xa78f7433, 5 | BRF_SND},
    {"pwg.12m", 0x200000, 0x77438ed0, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_armwaru1, BurnDrvCpsArmwar, "armwaru1", "Armored Warriors (USA 940920)", "armwar", 0)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_avspdRomDesc[] = {
    {"avped.03d", 0x080000, 0x66aa8aad, 1 | BRF_ESS | BRF_PRG},
    {"avped.04d", 0x080000, 0x579306c2, 1 | BRF_ESS | BRF_PRG},
    {"avp.05d", 0x080000, 0xfbfb5d7a, 1 | BRF_ESS | BRF_PRG},
    {"avpd.06", 0x080000, 0x63094539, 1 | BRF_ESS | BRF_PRG},
    {"avp.13m", 0x200000, 0x8f8b5ae4, 3 | BRF_GRA},
    {"avp.15m", 0x200000, 0xb00280df, 3 | BRF_GRA},
    {"avp.17m", 0x200000, 0x94403195, 3 | BRF_GRA},
    {"avp.19m", 0x200000, 0xe1981245, 3 | BRF_GRA},
    {"avp.14m", 0x200000, 0xebba093e, 3 | BRF_GRA},
    {"avp.16m", 0x200000, 0xfb228297, 3 | BRF_GRA},
    {"avp.18m", 0x200000, 0x34fb7232, 3 | BRF_GRA},
    {"avp.20m", 0x200000, 0xf90baa21, 3 | BRF_GRA},
    {"avp.01", 0x020000, 0x2d3b4220, 4 | BRF_ESS | BRF_PRG},
    {"avp.11m", 0x200000, 0x83499817, 5 | BRF_SND},
    {"avp.12m", 0x200000, 0xf4110d49, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_avspd, BurnDrvCpsAvsp, "avspd", "Alien vs. Predator (Europe 940520 Phoenix Edition)", "avsp", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_batcirdRomDesc[] = {
    {"btced.03", 0x080000, 0x0737db6d, 1 | BRF_ESS | BRF_PRG},
    {"btced.04", 0x080000, 0xef1a8823, 1 | BRF_ESS | BRF_PRG},
    {"btced.05", 0x080000, 0x20bdbb14, 1 | BRF_ESS | BRF_PRG},
    {"btced.06", 0x080000, 0xb4d8f5bc, 1 | BRF_ESS | BRF_PRG},
    {"btc.07", 0x080000, 0x7322d5db, 1 | BRF_ESS | BRF_PRG},
    {"btc.08", 0x080000, 0x6aac85ab, 1 | BRF_ESS | BRF_PRG},
    {"btc.09", 0x080000, 0x1203db08, 1 | BRF_ESS | BRF_PRG},
    {"btc.13m", 0x400000, 0xdc705bad, 3 | BRF_GRA},
    {"btc.15m", 0x400000, 0xe5779a3c, 3 | BRF_GRA},
    {"btc.17m", 0x400000, 0xb33f4112, 3 | BRF_GRA},
    {"btc.19m", 0x400000, 0xa6fcdb7e, 3 | BRF_GRA},
    {"btc.01", 0x020000, 0x1e194310, 4 | BRF_ESS | BRF_PRG},
    {"btc.02", 0x020000, 0x01aeb8e6, 4 | BRF_ESS | BRF_PRG},
    {"btc.11m", 0x200000, 0xc27f2229, 5 | BRF_SND},
    {"btc.12m", 0x200000, 0x418a2e33, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_batcird, BurnDrvCpsBatcir, "batcird", "Battle Circuit (Europe 970319 Phoenix Edition)", "batcir", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_csclubRomDesc[] = {
    {"csce.03a", 0x080000, 0x824082be, 1 | BRF_ESS | BRF_PRG},
    {"csce.04a", 0x080000, 0x74e6a4fe, 1 | BRF_ESS | BRF_PRG},
    {"csce.05a", 0x080000, 0x8ae0df19, 1 | BRF_ESS | BRF_PRG},
    {"csce.06a", 0x080000, 0x51f2f0d3, 1 | BRF_ESS | BRF_PRG},
    {"csce.07a", 0x080000, 0x003968fd, 1 | BRF_ESS | BRF_PRG},
    {"csc.73", 0x080000, 0x335f07c3, 3 | BRF_GRA},
    {"csc.63", 0x080000, 0x3711b8ca, 3 | BRF_GRA},
    {"csc.83", 0x080000, 0x0750d12a, 3 | BRF_GRA},
    {"csc.93", 0x080000, 0xa756c7f7, 3 | BRF_GRA},
    {"csc.74", 0x080000, 0xab215357, 3 | BRF_GRA},
    {"csc.64", 0x080000, 0x828a06d8, 3 | BRF_GRA},
    {"csc.84", 0x080000, 0x90a92f39, 3 | BRF_GRA},
    {"csc.94", 0x080000, 0xfb7ccc73, 3 | BRF_GRA},
    {"csc.75", 0x080000, 0xa2367381, 3 | BRF_GRA},
    {"csc.65", 0x080000, 0x86ee4569, 3 | BRF_GRA},
    {"csc.85", 0x080000, 0xd08ab012, 3 | BRF_GRA},
    {"csc.95", 0x080000, 0x4d014297, 3 | BRF_GRA},
    {"csc.76", 0x080000, 0x728aac1f, 3 | BRF_GRA},
    {"csc.66", 0x080000, 0xc24f577f, 3 | BRF_GRA},
    {"csc.86", 0x080000, 0x41652583, 3 | BRF_GRA},
    {"csc.96", 0x080000, 0x6754b1ef, 3 | BRF_GRA},
    {"csc.01", 0x020000, 0xee162111, 4 | BRF_ESS | BRF_PRG},
    {"csc.51", 0x080000, 0x5a52afd5, 5 | BRF_SND},
    {"csc.52", 0x080000, 0x1408a811, 5 | BRF_SND},
    {"csc.53", 0x080000, 0x4fb9f57c, 5 | BRF_SND},
    {"csc.54", 0x080000, 0x9a8f40ec, 5 | BRF_SND},
    {"csc.55", 0x080000, 0x91529a91, 5 | BRF_SND},
    {"csc.56", 0x080000, 0x9a345334, 5 | BRF_SND},
    {"csc.57", 0x080000, 0xaedc27f2, 5 | BRF_SND},
    {"csc.58", 0x080000, 0x2300b7b3, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_csclub, BurnDrvCpsCsclub, "csclub_rev", "Capcom Sports Club (Europe 971017)", nullptr, 0)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_csclubjrRomDesc[] = {
    {"cscj.03", 0x080000, 0xec4ddaa2, 1 | BRF_ESS | BRF_PRG},
    {"cscj.04", 0x080000, 0x60c632bb, 1 | BRF_ESS | BRF_PRG},
    {"cscj.05", 0x080000, 0xad042003, 1 | BRF_ESS | BRF_PRG},
    {"cscj.06", 0x080000, 0x169e4d40, 1 | BRF_ESS | BRF_PRG},
    {"csc.07", 0x080000, 0x01b05caa, 1 | BRF_ESS | BRF_PRG},
    {"csc.73", 0x080000, 0x335f07c3, 3 | BRF_GRA},
    {"csc.63", 0x080000, 0x3711b8ca, 3 | BRF_GRA},
    {"csc.83", 0x080000, 0x0750d12a, 3 | BRF_GRA},
    {"csc.93", 0x080000, 0xa756c7f7, 3 | BRF_GRA},
    {"csc.74", 0x080000, 0xab215357, 3 | BRF_GRA},
    {"csc.64", 0x080000, 0x828a06d8, 3 | BRF_GRA},
    {"csc.84", 0x080000, 0x90a92f39, 3 | BRF_GRA},
    {"csc.94", 0x080000, 0xfb7ccc73, 3 | BRF_GRA},
    {"csc.75", 0x080000, 0xa2367381, 3 | BRF_GRA},
    {"csc.65", 0x080000, 0x86ee4569, 3 | BRF_GRA},
    {"csc.85", 0x080000, 0xd08ab012, 3 | BRF_GRA},
    {"csc.95", 0x080000, 0x4d014297, 3 | BRF_GRA},
    {"csc.76", 0x080000, 0x728aac1f, 3 | BRF_GRA},
    {"csc.66", 0x080000, 0xc24f577f, 3 | BRF_GRA},
    {"csc.86", 0x080000, 0x41652583, 3 | BRF_GRA},
    {"csc.96", 0x080000, 0x6754b1ef, 3 | BRF_GRA},
    {"csc.01", 0x020000, 0xee162111, 4 | BRF_ESS | BRF_PRG},
    {"csc.51", 0x080000, 0x5a52afd5, 5 | BRF_SND},
    {"csc.52", 0x080000, 0x1408a811, 5 | BRF_SND},
    {"csc.53", 0x080000, 0x4fb9f57c, 5 | BRF_SND},
    {"csc.54", 0x080000, 0x9a8f40ec, 5 | BRF_SND},
    {"csc.55", 0x080000, 0x91529a91, 5 | BRF_SND},
    {"csc.56", 0x080000, 0x9a345334, 5 | BRF_SND},
    {"csc.57", 0x080000, 0xaedc27f2, 5 | BRF_SND},
    {"csc.58", 0x080000, 0x2300b7b3, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_csclubjr, BurnDrvCpsCsclubj, "csclubjy", "Capcom Sports Club (Japan 970722, yellow case)", "csclub", 0)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_ddsomudRomDesc[] = {
    {"dd2ud.03g", 0x080000, 0x816f695a, 1 | BRF_ESS | BRF_PRG},
    {"dd2ud.04g", 0x080000, 0x7cc81c6b, 1 | BRF_ESS | BRF_PRG},
    {"dd2.05g", 0x080000, 0x5eb1991c, 1 | BRF_ESS | BRF_PRG},
    {"dd2.06g", 0x080000, 0xc26b5e55, 1 | BRF_ESS | BRF_PRG},
    {"dd2.07", 0x080000, 0x909a0b8b, 1 | BRF_ESS | BRF_PRG},
    {"dd2.08", 0x080000, 0xe53c4d01, 1 | BRF_ESS | BRF_PRG},
    {"dd2.09", 0x080000, 0x5f86279f, 1 | BRF_ESS | BRF_PRG},
    {"dd2d.10", 0x080000, 0x0c172f8f, 1 | BRF_ESS | BRF_PRG},
    {"dd2.13m", 0x400000, 0xa46b4e6e, 3 | BRF_GRA},
    {"dd2.15m", 0x400000, 0xd5fc50fc, 3 | BRF_GRA},
    {"dd2.17m", 0x400000, 0x837c0867, 3 | BRF_GRA},
    {"dd2.19m", 0x400000, 0xbb0ec21c, 3 | BRF_GRA},
    {"dd2.14m", 0x200000, 0x6d824ce2, 3 | BRF_GRA},
    {"dd2.16m", 0x200000, 0x79682ae5, 3 | BRF_GRA},
    {"dd2.18m", 0x200000, 0xacddd149, 3 | BRF_GRA},
    {"dd2.20m", 0x200000, 0x117fb0c0, 3 | BRF_GRA},
    {"dd2.01", 0x020000, 0x99d657e5, 4 | BRF_ESS | BRF_PRG},
    {"dd2.02", 0x020000, 0x117a3824, 4 | BRF_ESS | BRF_PRG},
    {"dd2.11m", 0x200000, 0x98d0c325, 5 | BRF_SND},
    {"dd2.12m", 0x200000, 0x5ea2e7fa, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_ddsomud, BurnDrvCpsDdsom, "ddsomud", "Dungeons & Dragons: Shadow over Mystara (USA 960619 Phoenix Edition)", "ddsom", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_ddtoddRomDesc[] = {
    {"daded.03c", 0x080000, 0x843330f4, 1 | BRF_ESS | BRF_PRG},
    {"daded.04c", 0x080000, 0x306f14fc, 1 | BRF_ESS | BRF_PRG},
    {"daded.05c", 0x080000, 0x8c6b8328, 1 | BRF_ESS | BRF_PRG},
    {"dad.06a", 0x080000, 0x6225495a, 1 | BRF_ESS | BRF_PRG},
    {"dadd.07a", 0x080000, 0x0f0df6cc, 1 | BRF_ESS | BRF_PRG},
    {"dad.13m", 0x200000, 0xda3cb7d6, 3 | BRF_GRA},
    {"dad.15m", 0x200000, 0x92b63172, 3 | BRF_GRA},
    {"dad.17m", 0x200000, 0xb98757f5, 3 | BRF_GRA},
    {"dad.19m", 0x200000, 0x8121ce46, 3 | BRF_GRA},
    {"dad.14m", 0x100000, 0x837e6f3f, 3 | BRF_GRA},
    {"dad.16m", 0x100000, 0xf0916bdb, 3 | BRF_GRA},
    {"dad.18m", 0x100000, 0xcef393ef, 3 | BRF_GRA},
    {"dad.20m", 0x100000, 0x8953fe9e, 3 | BRF_GRA},
    {"dad.01", 0x020000, 0x3f5e2424, 4 | BRF_ESS | BRF_PRG},
    {"dad.11m", 0x200000, 0x0c499b67, 5 | BRF_SND},
    {"dad.12m", 0x200000, 0x2f0b5a4e, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_ddtodd, BurnDrvCpsDdtod, "ddtodd", "Dungeons & Dragons: Tower of Doom (Europe 940412 Phoenix Edition)", "ddtod", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_ddtodjRomDesc[] = {
    {"dadj.03c", 0x080000, 0x0b1b5798, 1 | BRF_ESS | BRF_PRG},
    {"dadj.04c", 0x080000, 0xc6a2fbc8, 1 | BRF_ESS | BRF_PRG},
    {"dadj.05c", 0x080000, 0x189b15fe, 1 | BRF_ESS | BRF_PRG},
    {"dad.06a", 0x080000, 0x6225495a, 1 | BRF_ESS | BRF_PRG},
    {"dad.07a", 0x080000, 0xb3480ec3, 1 | BRF_ESS | BRF_PRG},
    {"dad.13m", 0x200000, 0xda3cb7d6, 3 | BRF_GRA},
    {"dad.15m", 0x200000, 0x92b63172, 3 | BRF_GRA},
    {"dad.17m", 0x200000, 0xb98757f5, 3 | BRF_GRA},
    {"dad.19m", 0x200000, 0x8121ce46, 3 | BRF_GRA},
    {"dad.14m", 0x100000, 0x837e6f3f, 3 | BRF_GRA},
    {"dad.16m", 0x100000, 0xf0916bdb, 3 | BRF_GRA},
    {"dad.18m", 0x100000, 0xcef393ef, 3 | BRF_GRA},
    {"dad.20m", 0x100000, 0x8953fe9e, 3 | BRF_GRA},
    {"dad.01", 0x020000, 0x3f5e2424, 4 | BRF_ESS | BRF_PRG},
    {"dad.11m", 0x200000, 0x0c499b67, 5 | BRF_SND},
    {"dad.12m", 0x200000, 0x2f0b5a4e, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_ddtodj, BurnDrvCpsDdtodj, "ddtodj_rev", "Dungeons & Dragons: Tower of Doom (Japan 940412)", "ddtod", 0)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_dimahooRomDesc[] = {
    {"gmde.03", 0x080000, 0x968fcecd, 1 | BRF_ESS | BRF_PRG},
    {"gmd.04", 0x080000, 0x37485567, 1 | BRF_ESS | BRF_PRG},
    {"gmd.05", 0x080000, 0xda269ffb, 1 | BRF_ESS | BRF_PRG},
    {"gmd.06", 0x080000, 0x55b483c9, 1 | BRF_ESS | BRF_PRG},
    {"gmd.13m", 0x400000, 0x80dd19f0, 3 | BRF_GRA},
    {"gmd.15m", 0x400000, 0xdfd93a78, 3 | BRF_GRA},
    {"gmd.17m", 0x400000, 0x16356520, 3 | BRF_GRA},
    {"gmd.19m", 0x400000, 0xdfc33031, 3 | BRF_GRA},
    {"gmd.01", 0x020000, 0x3f9bc985, 4 | BRF_ESS | BRF_PRG},
    {"gmd.02", 0x020000, 0x3fd39dde, 4 | BRF_ESS | BRF_PRG},
    {"gmd.11m", 0x400000, 0x06a65542, 5 | BRF_SND},
    {"gmd.12m", 0x400000, 0x50bc7a31, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_dimahoo, BurnDrvCpsDimahoo, "dimahoo_rev", "Dimahoo (Europe 000121)", nullptr, 0)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_dimahoudRomDesc[] = {
    {"gmdud.03", 0x080000, 0x12888435, 1 | BRF_ESS | BRF_PRG},
    {"gmd.04", 0x080000, 0x37485567, 1 | BRF_ESS | BRF_PRG},
    {"gmd.05", 0x080000, 0xda269ffb, 1 | BRF_ESS | BRF_PRG},
    {"gmdud.06", 0x080000, 0xd825efda, 1 | BRF_ESS | BRF_PRG},
    {"gmd.13m", 0x400000, 0x80dd19f0, 3 | BRF_GRA},
    {"gmd.15m", 0x400000, 0xdfd93a78, 3 | BRF_GRA},
    {"gmd.17m", 0x400000, 0x16356520, 3 | BRF_GRA},
    {"gmd.19m", 0x400000, 0xdfc33031, 3 | BRF_GRA},
    {"gmd.01", 0x020000, 0x3f9bc985, 4 | BRF_ESS | BRF_PRG},
    {"gmd.02", 0x020000, 0x3fd39dde, 4 | BRF_ESS | BRF_PRG},
    {"gmd.11m", 0x400000, 0x06a65542, 5 | BRF_SND},
    {"gmd.12m", 0x400000, 0x50bc7a31, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_dimahoud, BurnDrvCpsDimahoo, "dimahoud", "Dimahoo (USA 000121 Phoenix Edition)", "dimahoo", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_dstlku1dRomDesc[] = {
    {"vamud.03a", 0x080000, 0x47b7a680, 1 | BRF_ESS | BRF_PRG},
    {"vamud.04a", 0x080000, 0x3b7a4939, 1 | BRF_ESS | BRF_PRG},
    {"vamu.05a", 0x080000, 0x673ed50a, 1 | BRF_ESS | BRF_PRG},
    {"vamu.06a", 0x080000, 0xf2377be7, 1 | BRF_ESS | BRF_PRG},
    {"vamu.07a", 0x080000, 0xd8f498c4, 1 | BRF_ESS | BRF_PRG},
    {"vamu.08a", 0x080000, 0xe6a8a1a0, 1 | BRF_ESS | BRF_PRG},
    {"vamud.09a", 0x080000, 0x8b333a19, 1 | BRF_ESS | BRF_PRG},
    {"vamu.10a", 0x080000, 0xc1a3d9be, 1 | BRF_ESS | BRF_PRG},
    {"vam.13m", 0x400000, 0xc51baf99, 3 | BRF_GRA},
    {"vam.15m", 0x400000, 0x3ce83c77, 3 | BRF_GRA},
    {"vam.17m", 0x400000, 0x4f2408e0, 3 | BRF_GRA},
    {"vam.19m", 0x400000, 0x9ff60250, 3 | BRF_GRA},
    {"vam.14m", 0x100000, 0xbd87243c, 3 | BRF_GRA},
    {"vam.16m", 0x100000, 0xafec855f, 3 | BRF_GRA},
    {"vam.18m", 0x100000, 0x3a033625, 3 | BRF_GRA},
    {"vam.20m", 0x100000, 0x2bff6a89, 3 | BRF_GRA},
    {"vam.01", 0x020000, 0x64b685d5, 4 | BRF_ESS | BRF_PRG},
    {"vam.02", 0x020000, 0xcf7c97c7, 4 | BRF_ESS | BRF_PRG},
    {"vam.11m", 0x200000, 0x4a39deb2, 5 | BRF_SND},
    {"vam.12m", 0x200000, 0x1a3e5c03, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_dstlku1d, BurnDrvCpsDstlk, "dstlku1d", "Darkstalkers: The Night Warriors (USA 940705 Phoenix Edition)", "dstlk", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_ecofghtuRomDesc[] = {
    {"uecu.03a", 0x080000, 0x22d88a4d, 1 | BRF_ESS | BRF_PRG},
    {"uecu.04a", 0x080000, 0x6436cfcd, 1 | BRF_ESS | BRF_PRG},
    {"uecu.05a", 0x080000, 0x336f121b, 1 | BRF_ESS | BRF_PRG},
    {"uecu.06a", 0x080000, 0x6f99d984, 1 | BRF_ESS | BRF_PRG},
    {"uec.13m", 0x200000, 0xdcaf1436, 3 | BRF_GRA},
    {"uec.15m", 0x200000, 0x2807df41, 3 | BRF_GRA},
    {"uec.17m", 0x200000, 0x8a708d02, 3 | BRF_GRA},
    {"uec.19m", 0x200000, 0xde7be0ef, 3 | BRF_GRA},
    {"uec.14m", 0x100000, 0x1a003558, 3 | BRF_GRA},
    {"uec.16m", 0x100000, 0x4ff8a6f9, 3 | BRF_GRA},
    {"uec.18m", 0x100000, 0xb167ae12, 3 | BRF_GRA},
    {"uec.20m", 0x100000, 0x1064bdc2, 3 | BRF_GRA},
    {"uec.01", 0x020000, 0xc235bd15, 4 | BRF_ESS | BRF_PRG},
    {"uec.11m", 0x200000, 0x81b25d39, 5 | BRF_SND},
    {"uec.12m", 0x200000, 0x27729e52, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_ecofghtu, BurnDrvCpsEcofghtu, "ecofghtru", "Eco Fighters (USA 940215)", "ecofghtr", 0)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_gwingbRomDesc[] = {
    {"ggwb.03", 0x080000, 0xa1f8a448, 1 | BRF_ESS | BRF_PRG},
    {"ggwb.04", 0x080000, 0x6a423e76, 1 | BRF_ESS | BRF_PRG},
    {"ggw.05", 0x080000, 0x3239d642, 1 | BRF_ESS | BRF_PRG},
    {"ggw.13m", 0x400000, 0x105530a4, 3 | BRF_GRA},
    {"ggw.15m", 0x400000, 0x9e774ab9, 3 | BRF_GRA},
    {"ggw.17m", 0x400000, 0x466e0ba4, 3 | BRF_GRA},
    {"ggw.19m", 0x400000, 0x840c8dea, 3 | BRF_GRA},
    {"ggw.01", 0x020000, 0x4c6351d5, 4 | BRF_ESS | BRF_PRG},
    {"ggw.11m", 0x400000, 0xe172acf5, 5 | BRF_SND},
    {"ggw.12m", 0x400000, 0x4bee4e8f, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_gwingb, BurnDrvCpsGigawing, "gigawingb", "Giga Wing (Brazil 990222)", "gigawing", 0)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_gwingjdRomDesc[] = {
    {"ggwjd.03a", 0x080000, 0xcb1c756e, 1 | BRF_ESS | BRF_PRG},
    {"ggwjd.04a", 0x080000, 0xfa158e04, 1 | BRF_ESS | BRF_PRG},
    {"ggwjd.05a", 0x080000, 0x1c5bc4e7, 1 | BRF_ESS | BRF_PRG},
    {"ggw.13m", 0x400000, 0x105530a4, 3 | BRF_GRA},
    {"ggw.15m", 0x400000, 0x9e774ab9, 3 | BRF_GRA},
    {"ggw.17m", 0x400000, 0x466e0ba4, 3 | BRF_GRA},
    {"ggw.19m", 0x400000, 0x840c8dea, 3 | BRF_GRA},
    {"ggw.01", 0x020000, 0x4c6351d5, 4 | BRF_ESS | BRF_PRG},
    {"ggw.11m", 0x400000, 0xe172acf5, 5 | BRF_SND},
    {"ggw.12m", 0x400000, 0x4bee4e8f, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_gwingjd, BurnDrvCpsGigawing, "gigawingjd", "Giga Wing (Japan 990223 Phoenix Edition)", "gigawing", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_hsf2dRomDesc[] = {
    {"hs2ad.03", 0x080000, 0x0153d371, 1 | BRF_ESS | BRF_PRG},
    {"hs2ad.04", 0x080000, 0x0276b78a, 1 | BRF_ESS | BRF_PRG},
    {"hs2.05", 0x080000, 0xdde34a35, 1 | BRF_ESS | BRF_PRG},
    {"hs2.06", 0x080000, 0xf4e56dda, 1 | BRF_ESS | BRF_PRG},
    {"hs2.07", 0x080000, 0xee4420fc, 1 | BRF_ESS | BRF_PRG},
    {"hs2.08", 0x080000, 0xc9441533, 1 | BRF_ESS | BRF_PRG},
    {"hs2.09", 0x080000, 0x3fc638a8, 1 | BRF_ESS | BRF_PRG},
    {"hs2.10", 0x080000, 0x20d0f9e4, 1 | BRF_ESS | BRF_PRG},
    {"hs2.13m", 0x800000, 0xa6ecab17, 3 | BRF_GRA},
    {"hs2.15m", 0x800000, 0x10a0ae4d, 3 | BRF_GRA},
    {"hs2.17m", 0x800000, 0xadfa7726, 3 | BRF_GRA},
    {"hs2.19m", 0x800000, 0xbb3ae322, 3 | BRF_GRA},
    {"hs2.01", 0x020000, 0xc1a13786, 4 | BRF_ESS | BRF_PRG},
    {"hs2.02", 0x020000, 0x2d8794aa, 4 | BRF_ESS | BRF_PRG},
    {"hs2.11m", 0x800000, 0x0e15c359, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_hsf2d, BurnDrvCpsHsf2, "hsf2d", "Hyper Street Fighter II: The Anniversary Edition (Asia 040202 Phoenix Edition)", "hsf2", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_megamn2dRomDesc[] = {
    {"rm2ud.03", 0x080000, 0xd3635f25, 1 | BRF_ESS | BRF_PRG},
    {"rm2ud.04", 0x080000, 0x768a1705, 1 | BRF_ESS | BRF_PRG},
    {"rm2.05", 0x080000, 0x02ee9efc, 1 | BRF_ESS | BRF_PRG},
    {"rm2.14m", 0x200000, 0x9b1f00b4, 3 | BRF_GRA},
    {"rm2.16m", 0x200000, 0xc2bb0c24, 3 | BRF_GRA},
    {"rm2.18m", 0x200000, 0x12257251, 3 | BRF_GRA},
    {"rm2.20m", 0x200000, 0xf9b6e786, 3 | BRF_GRA},
    {"rm2.01a", 0x020000, 0xd18e7859, 4 | BRF_ESS | BRF_PRG},
    {"rm2.02", 0x020000, 0xc463ece0, 4 | BRF_ESS | BRF_PRG},
    {"rm2.11m", 0x200000, 0x2106174d, 5 | BRF_SND},
    {"rm2.12m", 0x200000, 0x546c1636, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_megamn2d, BurnDrvCpsMegaman2, "megamn2d", "Mega Man 2: The Power Fighters (USA 960708 Phoenix Edition)", "megaman2", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_mmancp2uRomDesc[] = {
    {"rcmu.03b", 0x080000, 0xc39f037f, 1 | BRF_ESS | BRF_PRG},
    {"rcmu.04b", 0x080000, 0xcd6f5e99, 1 | BRF_ESS | BRF_PRG},
    {"rcm.05b", 0x080000, 0x4376ea95, 1 | BRF_ESS | BRF_PRG},
    {"rcm.73", 0x080000, 0x774c6e04, 3 | BRF_GRA},
    {"rcm.63", 0x080000, 0xacad7c62, 3 | BRF_GRA},
    {"rcm.83", 0x080000, 0x6af30499, 3 | BRF_GRA},
    {"rcm.93", 0x080000, 0x7a5a5166, 3 | BRF_GRA},
    {"rcm.74", 0x080000, 0x004ec725, 3 | BRF_GRA},
    {"rcm.64", 0x080000, 0x65c0464e, 3 | BRF_GRA},
    {"rcm.84", 0x080000, 0xfb3097cc, 3 | BRF_GRA},
    {"rcm.94", 0x080000, 0x2e16557a, 3 | BRF_GRA},
    {"rcm.75", 0x080000, 0x70a73f99, 3 | BRF_GRA},
    {"rcm.65", 0x080000, 0xecedad3d, 3 | BRF_GRA},
    {"rcm.85", 0x080000, 0x3d6186d8, 3 | BRF_GRA},
    {"rcm.95", 0x080000, 0x8c7700f1, 3 | BRF_GRA},
    {"rcm.76", 0x080000, 0x89a889ad, 3 | BRF_GRA},
    {"rcm.66", 0x080000, 0x1300eb7b, 3 | BRF_GRA},
    {"rcm.86", 0x080000, 0x6d974ebd, 3 | BRF_GRA},
    {"rcm.96", 0x080000, 0x7da4cd24, 3 | BRF_GRA},
    {"rcm.01", 0x020000, 0xd60cf8a3, 4 | BRF_ESS | BRF_PRG},
    {"rcm.51", 0x080000, 0xb6d07080, 5 | BRF_SND},
    {"rcm.52", 0x080000, 0xdfddc493, 5 | BRF_SND},
    {"rcm.53", 0x080000, 0x6062ae3a, 5 | BRF_SND},
    {"rcm.54", 0x080000, 0x08c6f3bf, 5 | BRF_SND},
    {"rcm.55", 0x080000, 0xf97dfccc, 5 | BRF_SND},
    {"rcm.56", 0x080000, 0xade475bc, 5 | BRF_SND},
    {"rcm.57", 0x080000, 0x075effb3, 5 | BRF_SND},
    {"rcm.58", 0x080000, 0xf6c1f87b, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_mmancp2u, BurnDrvCpsMegaman2, "mmancp2u", "Mega Man: The Power Battle (CPS2, USA 951006, SAMPLE Version)", nullptr, 0)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_mmatrixdRomDesc[] = {
    {"mmxud.03", 0x080000, 0x36711e60, 1 | BRF_ESS | BRF_PRG},
    {"mmxud.04", 0x080000, 0x4687226f, 1 | BRF_ESS | BRF_PRG},
    {"mmxud.05", 0x080000, 0x52124398, 1 | BRF_ESS | BRF_PRG},
    {"mmx.13m", 0x400000, 0x04748718, 3 | BRF_GRA},
    {"mmx.15m", 0x400000, 0x38074f44, 3 | BRF_GRA},
    {"mmx.17m", 0x400000, 0xe4635e35, 3 | BRF_GRA},
    {"mmx.19m", 0x400000, 0x4400a3f2, 3 | BRF_GRA},
    {"mmx.14m", 0x400000, 0xd52bf491, 3 | BRF_GRA},
    {"mmx.16m", 0x400000, 0x23f70780, 3 | BRF_GRA},
    {"mmx.18m", 0x400000, 0x2562c9d5, 3 | BRF_GRA},
    {"mmx.20m", 0x400000, 0x583a9687, 3 | BRF_GRA},
    {"mmx.01", 0x020000, 0xc57e8171, 4 | BRF_ESS | BRF_PRG},
    {"mmx.11m", 0x400000, 0x4180b39f, 5 | BRF_SND},
    {"mmx.12m", 0x400000, 0x95e22a59, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_mmatrixd, BurnDrvCpsMarsMatrix, "mmatrixd", "Mars Matrix: Hyper Solid Shooting (USA 000412 Phoenix Edition)", "mmatrix", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_mpangRomDesc[] = {
    {"mpne.03c", 0x080000, 0xfe16fc9f, 1 | BRF_ESS | BRF_PRG},
    {"mpne.04c", 0x080000, 0x2cc5ec22, 1 | BRF_ESS | BRF_PRG},
    {"mpn-simm.01c", 0x200000, 0x388db66b, 11 | BRF_GRA},
    {"mpn-simm.01d", 0x200000, 0xaff1b494, 11 | BRF_GRA},
    {"mpn-simm.01a", 0x200000, 0xa9c4857b, 11 | BRF_GRA},
    {"mpn-simm.01b", 0x200000, 0xf759df22, 11 | BRF_GRA},
    {"mpn-simm.03c", 0x200000, 0xdec6b720, 11 | BRF_GRA},
    {"mpn-simm.03d", 0x200000, 0xf8774c18, 11 | BRF_GRA},
    {"mpn-simm.03a", 0x200000, 0xc2aea4ec, 11 | BRF_GRA},
    {"mpn-simm.03b", 0x200000, 0x84d6dc33, 11 | BRF_GRA},
    {"mpn.01", 0x020000, 0x90c7adb6, 4 | BRF_ESS | BRF_PRG},
    {"mpn-simm.05a", 0x200000, 0x318a2e21, 13 | BRF_SND},
    {"mpn-simm.05b", 0x200000, 0x5462f4e8, 13 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_mpang, BurnDrvCpsMPangj, "mpang_rev", "Mighty! Pang (Europe 001010)", nullptr, 0)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_mshudRomDesc[] = {
    {"mshud.03", 0x080000, 0xc1d8c4c6, 1 | BRF_ESS | BRF_PRG},
    {"mshud.04", 0x080000, 0xe73dda16, 1 | BRF_ESS | BRF_PRG},
    {"mshud.05", 0x080000, 0x3b493e84, 1 | BRF_ESS | BRF_PRG},
    {"msh.06b", 0x080000, 0x803e3fa4, 1 | BRF_ESS | BRF_PRG},
    {"msh.07a", 0x080000, 0xc45f8e27, 1 | BRF_ESS | BRF_PRG},
    {"msh.08a", 0x080000, 0x9ca6f12c, 1 | BRF_ESS | BRF_PRG},
    {"msh.09a", 0x080000, 0x82ec27af, 1 | BRF_ESS | BRF_PRG},
    {"msh.10b", 0x080000, 0x8d931196, 1 | BRF_ESS | BRF_PRG},
    {"msh.13m", 0x400000, 0x09d14566, 3 | BRF_GRA},
    {"msh.15m", 0x400000, 0xee962057, 3 | BRF_GRA},
    {"msh.17m", 0x400000, 0x604ece14, 3 | BRF_GRA},
    {"msh.19m", 0x400000, 0x94a731e8, 3 | BRF_GRA},
    {"msh.14m", 0x400000, 0x4197973e, 3 | BRF_GRA},
    {"msh.16m", 0x400000, 0x438da4a0, 3 | BRF_GRA},
    {"msh.18m", 0x400000, 0x4db92d94, 3 | BRF_GRA},
    {"msh.20m", 0x400000, 0xa2b0c6c0, 3 | BRF_GRA},
    {"msh.01", 0x020000, 0xc976e6f9, 4 | BRF_ESS | BRF_PRG},
    {"msh.02", 0x020000, 0xce67d0d9, 4 | BRF_ESS | BRF_PRG},
    {"msh.11m", 0x200000, 0x37ac6d30, 5 | BRF_SND},
    {"msh.12m", 0x200000, 0xde092570, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_mshud, BurnDrvCpsMsh, "mshud", "Marvel Super Heroes (USA 951024 Phoenix Edition)", "msh", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_mvscudRomDesc[] = {
    {"mvcud.03d", 0x080000, 0x75cde3e5, 1 | BRF_ESS | BRF_PRG},
    {"mvcud.04d", 0x080000, 0xb32ea484, 1 | BRF_ESS | BRF_PRG},
    {"mvc.05a", 0x080000, 0x2d8c8e86, 1 | BRF_ESS | BRF_PRG},
    {"mvc.06a", 0x080000, 0x8528e1f5, 1 | BRF_ESS | BRF_PRG},
    {"mvcd.07", 0x080000, 0x205293e9, 1 | BRF_ESS | BRF_PRG},
    {"mvc.08", 0x080000, 0xbc002fcd, 1 | BRF_ESS | BRF_PRG},
    {"mvc.09", 0x080000, 0xc67b26df, 1 | BRF_ESS | BRF_PRG},
    {"mvc.10", 0x080000, 0x0fdd1e26, 1 | BRF_ESS | BRF_PRG},
    {"mvc.13m", 0x400000, 0xfa5f74bc, 3 | BRF_GRA},
    {"mvc.15m", 0x400000, 0x71938a8f, 3 | BRF_GRA},
    {"mvc.17m", 0x400000, 0x92741d07, 3 | BRF_GRA},
    {"mvc.19m", 0x400000, 0xbcb72fc6, 3 | BRF_GRA},
    {"mvc.14m", 0x400000, 0x7f1df4e4, 3 | BRF_GRA},
    {"mvc.16m", 0x400000, 0x90bd3203, 3 | BRF_GRA},
    {"mvc.18m", 0x400000, 0x67aaf727, 3 | BRF_GRA},
    {"mvc.20m", 0x400000, 0x8b0bade8, 3 | BRF_GRA},
    {"mvc.01", 0x020000, 0x41629e95, 4 | BRF_ESS | BRF_PRG},
    {"mvc.02", 0x020000, 0x963abf6b, 4 | BRF_ESS | BRF_PRG},
    {"mvc.11m", 0x400000, 0x850fe663, 5 | BRF_SND},
    {"mvc.12m", 0x400000, 0x7ccb1896, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_mvscud, BurnDrvCpsMvsc, "mvscud", "Marvel Vs. Capcom: Clash of Super Heroes (USA 980123 Phoenix Edition)", "mvsc", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_nwarrudRomDesc[] = {
    {"vphud.03f", 0x080000, 0x20d4d5a8, 1 | BRF_ESS | BRF_PRG},
    {"vphud.04c", 0x080000, 0x61be9b42, 1 | BRF_ESS | BRF_PRG},
    {"vphud.05e", 0x080000, 0x1ba906d8, 1 | BRF_ESS | BRF_PRG},
    {"vphu.06c", 0x080000, 0x08c04cdb, 1 | BRF_ESS | BRF_PRG},
    {"vphu.07b", 0x080000, 0xb5a5ab19, 1 | BRF_ESS | BRF_PRG},
    {"vphu.08b", 0x080000, 0x51bb20fb, 1 | BRF_ESS | BRF_PRG},
    {"vphu.09b", 0x080000, 0x41a64205, 1 | BRF_ESS | BRF_PRG},
    {"vphud.10b", 0x080000, 0x9619adad, 1 | BRF_ESS | BRF_PRG},
    {"vph.13m", 0x400000, 0xc51baf99, 3 | BRF_GRA},
    {"vph.15m", 0x400000, 0x3ce83c77, 3 | BRF_GRA},
    {"vph.17m", 0x400000, 0x4f2408e0, 3 | BRF_GRA},
    {"vph.19m", 0x400000, 0x9ff60250, 3 | BRF_GRA},
    {"vph.14m", 0x400000, 0x7a0e1add, 3 | BRF_GRA},
    {"vph.16m", 0x400000, 0x2f41ca75, 3 | BRF_GRA},
    {"vph.18m", 0x400000, 0x64498eed, 3 | BRF_GRA},
    {"vph.20m", 0x400000, 0x17f2433f, 3 | BRF_GRA},
    {"vph.01", 0x020000, 0x5045dcac, 4 | BRF_ESS | BRF_PRG},
    {"vph.02", 0x020000, 0x86b60e59, 4 | BRF_ESS | BRF_PRG},
    {"vph.11m", 0x200000, 0xe1837d33, 5 | BRF_SND},
    {"vph.12m", 0x200000, 0xfbd3cd90, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_nwarrud, BurnDrvCpsNwarr, "nwarrud", "Night Warriors: Darkstalkers' Revenge (USA 950406 Phoenix Edition)", "nwarr", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_progerjdRomDesc[] = {
    {"pgaj_bl.03", 0x080000, 0x4fef676c, 1 | BRF_ESS | BRF_PRG},
    {"pgaj_bl.04", 0x080000, 0xa069bd3b, 1 | BRF_ESS | BRF_PRG},
    {"pga-simm.01c", 0x200000, 0x452f98b0, 11 | BRF_GRA},
    {"pga-simm.01d", 0x200000, 0x9e672092, 11 | BRF_GRA},
    {"pga-simm.01a", 0x200000, 0xae9ddafe, 11 | BRF_GRA},
    {"pga-simm.01b", 0x200000, 0x94d72d94, 11 | BRF_GRA},
    {"pga-simm.03c", 0x200000, 0x48a1886d, 11 | BRF_GRA},
    {"pga-simm.03d", 0x200000, 0x172d7e37, 11 | BRF_GRA},
    {"pga-simm.03a", 0x200000, 0x9ee33d98, 11 | BRF_GRA},
    {"pga-simm.03b", 0x200000, 0x848dee32, 11 | BRF_GRA},
    {"pga.01", 0x020000, 0xbdbfa992, 4 | BRF_ESS | BRF_PRG},
    {"pga-simm.05a", 0x200000, 0xc0aac80c, 13 | BRF_SND},
    {"pga-simm.05b", 0x200000, 0x37a65d86, 13 | BRF_SND},
    {"pga-simm.06a", 0x200000, 0xd3f1e934, 13 | BRF_SND},
    {"pga-simm.06b", 0x200000, 0x8b39489a, 13 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_progerjd, BurnDrvCpsProgear, "progearjbl", "Progear no Arashi (Japan 010117) (decrypted bootleg)", "progear", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_ringdstdRomDesc[] = {
    {"smbed.03b", 0x080000, 0xf6fba4cd, 1 | BRF_ESS | BRF_PRG},
    {"smbed.04b", 0x080000, 0x193bc493, 1 | BRF_ESS | BRF_PRG},
    {"smbed.05b", 0x080000, 0x168cccbb, 1 | BRF_ESS | BRF_PRG},
    {"smbed.06b", 0x080000, 0x04673262, 1 | BRF_ESS | BRF_PRG},
    {"smb.07", 0x080000, 0xb9a11577, 1 | BRF_ESS | BRF_PRG},
    {"smb.08", 0x080000, 0xf931b76b, 1 | BRF_ESS | BRF_PRG},
    {"smb.13m", 0x200000, 0xd9b2d1de, 3 | BRF_GRA},
    {"smb.15m", 0x200000, 0x9a766d92, 3 | BRF_GRA},
    {"smb.17m", 0x200000, 0x51800f0f, 3 | BRF_GRA},
    {"smb.19m", 0x200000, 0x35757e96, 3 | BRF_GRA},
    {"smb.14m", 0x200000, 0xe5bfd0e7, 3 | BRF_GRA},
    {"smb.16m", 0x200000, 0xc56c0866, 3 | BRF_GRA},
    {"smb.18m", 0x200000, 0x4ded3910, 3 | BRF_GRA},
    {"smb.20m", 0x200000, 0x26ea1ec5, 3 | BRF_GRA},
    {"smb.21m", 0x080000, 0x0a08c5fc, 3 | BRF_GRA},
    {"smb.23m", 0x080000, 0x0911b6c4, 3 | BRF_GRA},
    {"smb.25m", 0x080000, 0x82d6c4ec, 3 | BRF_GRA},
    {"smb.27m", 0x080000, 0x9b48678b, 3 | BRF_GRA},
    {"smb.01", 0x020000, 0x0abc229a, 4 | BRF_ESS | BRF_PRG},
    {"smb.02", 0x020000, 0xd051679a, 4 | BRF_ESS | BRF_PRG},
    {"smb.11m", 0x200000, 0xc56935f9, 5 | BRF_SND},
    {"smb.12m", 0x200000, 0x955b0782, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_ringdstd, BurnDrvCpsRingdest, "ringdstd", "Ring of Destruction: Slammasters II (Europe 940902 Phoenix Edition)", "ringdest", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_rmancp2jRomDesc[] = {
    {"rcmj.03a", 0x080000, 0x30559f60, 1 | BRF_ESS | BRF_PRG},
    {"rcmj.04a", 0x080000, 0x5efc9366, 1 | BRF_ESS | BRF_PRG},
    {"rcm.05a", 0x080000, 0x517ccde2, 1 | BRF_ESS | BRF_PRG},
    {"rcm.73", 0x080000, 0x774c6e04, 3 | BRF_GRA},
    {"rcm.63", 0x080000, 0xacad7c62, 3 | BRF_GRA},
    {"rcm.83", 0x080000, 0x6af30499, 3 | BRF_GRA},
    {"rcm.93", 0x080000, 0x7a5a5166, 3 | BRF_GRA},
    {"rcm.74", 0x080000, 0x004ec725, 3 | BRF_GRA},
    {"rcm.64", 0x080000, 0x65c0464e, 3 | BRF_GRA},
    {"rcm.84", 0x080000, 0xfb3097cc, 3 | BRF_GRA},
    {"rcm.94", 0x080000, 0x2e16557a, 3 | BRF_GRA},
    {"rcm.75", 0x080000, 0x70a73f99, 3 | BRF_GRA},
    {"rcm.65", 0x080000, 0xecedad3d, 3 | BRF_GRA},
    {"rcm.85", 0x080000, 0x3d6186d8, 3 | BRF_GRA},
    {"rcm.95", 0x080000, 0x8c7700f1, 3 | BRF_GRA},
    {"rcm.76", 0x080000, 0x89a889ad, 3 | BRF_GRA},
    {"rcm.66", 0x080000, 0x1300eb7b, 3 | BRF_GRA},
    {"rcm.86", 0x080000, 0x6d974ebd, 3 | BRF_GRA},
    {"rcm.96", 0x080000, 0x7da4cd24, 3 | BRF_GRA},
    {"rcm.01", 0x020000, 0xd60cf8a3, 4 | BRF_ESS | BRF_PRG},
    {"rcm.51", 0x080000, 0xb6d07080, 5 | BRF_SND},
    {"rcm.52", 0x080000, 0xdfddc493, 5 | BRF_SND},
    {"rcm.53", 0x080000, 0x6062ae3a, 5 | BRF_SND},
    {"rcm.54", 0x080000, 0x08c6f3bf, 5 | BRF_SND},
    {"rcm.55", 0x080000, 0xf97dfccc, 5 | BRF_SND},
    {"rcm.56", 0x080000, 0xade475bc, 5 | BRF_SND},
    {"rcm.57", 0x080000, 0x075effb3, 5 | BRF_SND},
    {"rcm.58", 0x080000, 0xf6c1f87b, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_rmancp2j, BurnDrvCpsMegaman2, "rmancp2j", "Rockman: The Power Battle (CPS2, Japan 950922)", nullptr, 0)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_sfa2RomDesc[] = {
    {"sz2e.03", 0x080000, 0x1061e6bb, 1 | BRF_ESS | BRF_PRG},
    {"sz2e.04", 0x080000, 0x22d17b26, 1 | BRF_ESS | BRF_PRG},
    {"sz2.05", 0x080000, 0x4b442a7c, 1 | BRF_ESS | BRF_PRG},
    {"sz2.06", 0x080000, 0x5b1d49c0, 1 | BRF_ESS | BRF_PRG},
    {"sz2.07", 0x080000, 0x8e184246, 1 | BRF_ESS | BRF_PRG},
    {"sz2.08", 0x080000, 0x0fe8585d, 1 | BRF_ESS | BRF_PRG},
    {"sz2.13m", 0x400000, 0x4d1f1f22, 3 | BRF_GRA},
    {"sz2.15m", 0x400000, 0x19cea680, 3 | BRF_GRA},
    {"sz2.17m", 0x400000, 0xe01b4588, 3 | BRF_GRA},
    {"sz2.19m", 0x400000, 0x0feeda64, 3 | BRF_GRA},
    {"sz2.14m", 0x100000, 0x0560c6aa, 3 | BRF_GRA},
    {"sz2.16m", 0x100000, 0xae940f87, 3 | BRF_GRA},
    {"sz2.18m", 0x100000, 0x4bc3c8bc, 3 | BRF_GRA},
    {"sz2.20m", 0x100000, 0x39e674c0, 3 | BRF_GRA},
    {"sz2.01a", 0x020000, 0x1bc323cf, 4 | BRF_ESS | BRF_PRG},
    {"sz2.02a", 0x020000, 0xba6a5013, 4 | BRF_ESS | BRF_PRG},
    {"sz2.11m", 0x200000, 0xaa47a601, 5 | BRF_SND},
    {"sz2.12m", 0x200000, 0x2237bc53, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_sfa2, BurnDrvCpsSfa2, "sfa2_rev", "Street Fighter Alpha 2 (Europe 960229)", nullptr, 0)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_sfa3RomDesc[] = {
    {"sz3e.03c", 0x080000, 0x9762b206, 1 | BRF_ESS | BRF_PRG},
    {"sz3e.04c", 0x080000, 0x5ad3f721, 1 | BRF_ESS | BRF_PRG},
    {"sz3.05c", 0x080000, 0x57fd0a40, 1 | BRF_ESS | BRF_PRG},
    {"sz3.06c", 0x080000, 0xf6305f8b, 1 | BRF_ESS | BRF_PRG},
    {"sz3.07c", 0x080000, 0x6eab0f6f, 1 | BRF_ESS | BRF_PRG},
    {"sz3.08c", 0x080000, 0x910c4a3b, 1 | BRF_ESS | BRF_PRG},
    {"sz3.09c", 0x080000, 0xb29e5199, 1 | BRF_ESS | BRF_PRG},
    {"sz3.10b", 0x080000, 0xdeb2ff52, 1 | BRF_ESS | BRF_PRG},
    {"sz3.13m", 0x400000, 0x0f7a60d9, 3 | BRF_GRA},
    {"sz3.15m", 0x400000, 0x8e933741, 3 | BRF_GRA},
    {"sz3.17m", 0x400000, 0xd6e98147, 3 | BRF_GRA},
    {"sz3.19m", 0x400000, 0xf31a728a, 3 | BRF_GRA},
    {"sz3.14m", 0x400000, 0x5ff98297, 3 | BRF_GRA},
    {"sz3.16m", 0x400000, 0x52b5bdee, 3 | BRF_GRA},
    {"sz3.18m", 0x400000, 0x40631ed5, 3 | BRF_GRA},
    {"sz3.20m", 0x400000, 0x763409b4, 3 | BRF_GRA},
    {"sz3.01", 0x020000, 0xde810084, 4 | BRF_ESS | BRF_PRG},
    {"sz3.02", 0x020000, 0x72445dc4, 4 | BRF_ESS | BRF_PRG},
    {"sz3.11m", 0x400000, 0x1c89eed1, 5 | BRF_SND},
    {"sz3.12m", 0x400000, 0xf392b13a, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_sfa3, BurnDrvCpsSfa3, "sfa3_rev", "Street Fighter Alpha 3 (Europe 980904)", nullptr, 0)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_sfa3udRomDesc[] = {
    {"sz3ud.03c", 0x080000, 0x6db8add7, 1 | BRF_ESS | BRF_PRG},
    {"sz3ud.04c", 0x080000, 0xd9c65a26, 1 | BRF_ESS | BRF_PRG},
    {"sz3.05c", 0x080000, 0x57fd0a40, 1 | BRF_ESS | BRF_PRG},
    {"sz3.06c", 0x080000, 0xf6305f8b, 1 | BRF_ESS | BRF_PRG},
    {"sz3.07c", 0x080000, 0x6eab0f6f, 1 | BRF_ESS | BRF_PRG},
    {"sz3.08c", 0x080000, 0x910c4a3b, 1 | BRF_ESS | BRF_PRG},
    {"sz3.09c", 0x080000, 0xb29e5199, 1 | BRF_ESS | BRF_PRG},
    {"sz3.10b", 0x080000, 0xdeb2ff52, 1 | BRF_ESS | BRF_PRG},
    {"sz3.13m", 0x400000, 0x0f7a60d9, 3 | BRF_GRA},
    {"sz3.15m", 0x400000, 0x8e933741, 3 | BRF_GRA},
    {"sz3.17m", 0x400000, 0xd6e98147, 3 | BRF_GRA},
    {"sz3.19m", 0x400000, 0xf31a728a, 3 | BRF_GRA},
    {"sz3.14m", 0x400000, 0x5ff98297, 3 | BRF_GRA},
    {"sz3.16m", 0x400000, 0x52b5bdee, 3 | BRF_GRA},
    {"sz3.18m", 0x400000, 0x40631ed5, 3 | BRF_GRA},
    {"sz3.20m", 0x400000, 0x763409b4, 3 | BRF_GRA},
    {"sz3.01", 0x020000, 0xde810084, 4 | BRF_ESS | BRF_PRG},
    {"sz3.02", 0x020000, 0x72445dc4, 4 | BRF_ESS | BRF_PRG},
    {"sz3.11m", 0x400000, 0x1c89eed1, 5 | BRF_SND},
    {"sz3.12m", 0x400000, 0xf392b13a, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_sfa3ud, BurnDrvCpsSfa3, "sfa3ud", "Street Fighter Alpha 3 (USA 980904 Phoenix Edition)", "sfa3", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_sfadRomDesc[] = {
    {"sfzed.03d", 0x080000, 0xa1a54827, 1 | BRF_ESS | BRF_PRG},
    {"sfz.04b", 0x080000, 0x8b73b0e5, 1 | BRF_ESS | BRF_PRG},
    {"sfz.05a", 0x080000, 0x0810544d, 1 | BRF_ESS | BRF_PRG},
    {"sfz.06", 0x080000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG},
    {"sfz.14m", 0x200000, 0x90fefdb3, 3 | BRF_GRA},
    {"sfz.16m", 0x200000, 0x5354c948, 3 | BRF_GRA},
    {"sfz.18m", 0x200000, 0x41a1e790, 3 | BRF_GRA},
    {"sfz.20m", 0x200000, 0xa549df98, 3 | BRF_GRA},
    {"sfz.01", 0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG},
    {"sfz.02", 0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG},
    {"sfz.11m", 0x200000, 0xc4b093cd, 5 | BRF_SND},
    {"sfz.12m", 0x200000, 0x8bdbc4b4, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_sfad, BurnDrvCpsSfa, "sfad", "Street Fighter Alpha: Warriors' Dreams (Europe 950727 Phoenix Edition)", "sfa", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_sfz2adRomDesc[] = {
    {"sz2ad.03a", 0x080000, 0x017f8fab, 1 | BRF_ESS | BRF_PRG},
    {"sz2ad.04a", 0x080000, 0xf50e5ea2, 1 | BRF_ESS | BRF_PRG},
    {"sz2.05a", 0x080000, 0x98e8e992, 1 | BRF_ESS | BRF_PRG},
    {"sz2.06", 0x080000, 0x5b1d49c0, 1 | BRF_ESS | BRF_PRG},
    {"sz2a.07a", 0x080000, 0x0aed2494, 1 | BRF_ESS | BRF_PRG},
    {"sz2.08", 0x080000, 0x0fe8585d, 1 | BRF_ESS | BRF_PRG},
    {"sz2.13m", 0x400000, 0x4d1f1f22, 3 | BRF_GRA},
    {"sz2.15m", 0x400000, 0x19cea680, 3 | BRF_GRA},
    {"sz2.17m", 0x400000, 0xe01b4588, 3 | BRF_GRA},
    {"sz2.19m", 0x400000, 0x0feeda64, 3 | BRF_GRA},
    {"sz2.14m", 0x100000, 0x0560c6aa, 3 | BRF_GRA},
    {"sz2.16m", 0x100000, 0xae940f87, 3 | BRF_GRA},
    {"sz2.18m", 0x100000, 0x4bc3c8bc, 3 | BRF_GRA},
    {"sz2.20m", 0x100000, 0x39e674c0, 3 | BRF_GRA},
    {"sz2.01a", 0x020000, 0x1bc323cf, 4 | BRF_ESS | BRF_PRG},
    {"sz2.02a", 0x020000, 0xba6a5013, 4 | BRF_ESS | BRF_PRG},
    {"sz2.11m", 0x200000, 0xaa47a601, 5 | BRF_SND},
    {"sz2.12m", 0x200000, 0x2237bc53, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_sfz2ad, BurnDrvCpsSfa2, "sfz2ad", "Street Fighter Zero 2 (Asia 960227 Phoenix Edition)", "sfa2", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_sfz2aldRomDesc[] = {
    {"szaad.03", 0x080000, 0x89f9483b, 1 | BRF_ESS | BRF_PRG},
    {"szaad.04", 0x080000, 0xaef27ae5, 1 | BRF_ESS | BRF_PRG},
    {"szaa.05", 0x080000, 0xf053a55e, 1 | BRF_ESS | BRF_PRG},
    {"szaa.06", 0x080000, 0xcfc0e7a8, 1 | BRF_ESS | BRF_PRG},
    {"szaa.07", 0x080000, 0x5feb8b20, 1 | BRF_ESS | BRF_PRG},
    {"szaa.08", 0x080000, 0x6eb6d412, 1 | BRF_ESS | BRF_PRG},
    {"sz2.13m", 0x400000, 0x4d1f1f22, 3 | BRF_GRA},
    {"sz2.15m", 0x400000, 0x19cea680, 3 | BRF_GRA},
    {"sz2.17m", 0x400000, 0xe01b4588, 3 | BRF_GRA},
    {"sz2.19m", 0x400000, 0x0feeda64, 3 | BRF_GRA},
    {"sz2.14m", 0x100000, 0x0560c6aa, 3 | BRF_GRA},
    {"sz2.16m", 0x100000, 0xae940f87, 3 | BRF_GRA},
    {"sz2.18m", 0x100000, 0x4bc3c8bc, 3 | BRF_GRA},
    {"sz2.20m", 0x100000, 0x39e674c0, 3 | BRF_GRA},
    {"sz2.01a", 0x020000, 0x1bc323cf, 4 | BRF_ESS | BRF_PRG},
    {"sz2.02a", 0x020000, 0xba6a5013, 4 | BRF_ESS | BRF_PRG},
    {"sz2.11m", 0x200000, 0xaa47a601, 5 | BRF_SND},
    {"sz2.12m", 0x200000, 0x2237bc53, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_sfz2ald, BurnDrvCpsSfz2aj, "sfz2ald", "Street Fighter Zero 2 Alpha (Asia 960826 Phoenix Edition)", "sfz2al", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_sgemfdRomDesc[] = {
    {"pcfud.03", 0x080000, 0x8b83674a, 1 | BRF_ESS | BRF_PRG},
    {"pcfd.04", 0x080000, 0xb58f1d03, 1 | BRF_ESS | BRF_PRG},
    {"pcf.05", 0x080000, 0x215655f6, 1 | BRF_ESS | BRF_PRG},
    {"pcf.06", 0x080000, 0xea6f13ea, 1 | BRF_ESS | BRF_PRG},
    {"pcf.07", 0x080000, 0x5ac6d5ea, 1 | BRF_ESS | BRF_PRG},
    {"pcf.13m", 0x400000, 0x22d72ab9, 3 | BRF_GRA},
    {"pcf.15m", 0x400000, 0x16a4813c, 3 | BRF_GRA},
    {"pcf.17m", 0x400000, 0x1097e035, 3 | BRF_GRA},
    {"pcf.19m", 0x400000, 0xd362d874, 3 | BRF_GRA},
    {"pcf.14m", 0x100000, 0x0383897c, 3 | BRF_GRA},
    {"pcf.16m", 0x100000, 0x76f91084, 3 | BRF_GRA},
    {"pcf.18m", 0x100000, 0x756c3754, 3 | BRF_GRA},
    {"pcf.20m", 0x100000, 0x9ec9277d, 3 | BRF_GRA},
    {"pcf.01", 0x020000, 0x254e5f33, 4 | BRF_ESS | BRF_PRG},
    {"pcf.02", 0x020000, 0x6902f4f9, 4 | BRF_ESS | BRF_PRG},
    {"pcf.11m", 0x400000, 0xa5dea005, 5 | BRF_SND},
    {"pcf.12m", 0x400000, 0x4ce235fe, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_sgemfd, BurnDrvCpsSgemf, "sgemfd", "Super Gem Fighter: Mini Mix (USA 970904 Phoenix Edition)", "sgemf", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_spf2xjdRomDesc[] = {
    {"pzfjd.03a", 0x080000, 0x5e85ed08, 1 | BRF_ESS | BRF_PRG},
    {"pzf.04", 0x080000, 0xb80649e2, 1 | BRF_ESS | BRF_PRG},
    {"pzf.14m", 0x100000, 0x2d4881cb, 3 | BRF_GRA},
    {"pzf.16m", 0x100000, 0x4b0fd1be, 3 | BRF_GRA},
    {"pzf.18m", 0x100000, 0xe43aac33, 3 | BRF_GRA},
    {"pzf.20m", 0x100000, 0x7f536ff1, 3 | BRF_GRA},
    {"pzf.01", 0x020000, 0x600fb2a3, 4 | BRF_ESS | BRF_PRG},
    {"pzf.02", 0x020000, 0x496076e0, 4 | BRF_ESS | BRF_PRG},
    {"pzf.11m", 0x200000, 0x78442743, 5 | BRF_SND},
    {"pzf.12m", 0x200000, 0x399d2c7b, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_spf2xjd, BurnDrvCpsSpf2t, "spf2xjd", "Super Puzzle Fighter II X (Japan 960531 Phoenix Edition)", "spf2t", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_ssf2tbdRomDesc[] = {
    {"ssfed.3tc", 0x080000, 0x5d86caf8, 1 | BRF_ESS | BRF_PRG},
    {"ssfed.4tc", 0x080000, 0xf6e1f98d, 1 | BRF_ESS | BRF_PRG},
    {"ssfed.5t", 0x080000, 0x75c651ef, 1 | BRF_ESS | BRF_PRG},
    {"ssfed.6tb", 0x080000, 0x9adac7d7, 1 | BRF_ESS | BRF_PRG},
    {"ssfed.7t", 0x080000, 0x84f54db3, 1 | BRF_ESS | BRF_PRG},
    {"ssf.13m", 0x200000, 0xcf94d275, 3 | BRF_GRA},
    {"ssf.15m", 0x200000, 0x5eb703af, 3 | BRF_GRA},
    {"ssf.17m", 0x200000, 0xffa60e0f, 3 | BRF_GRA},
    {"ssf.19m", 0x200000, 0x34e825c5, 3 | BRF_GRA},
    {"ssf.14m", 0x100000, 0xb7cc32e7, 3 | BRF_GRA},
    {"ssf.16m", 0x100000, 0x8376ad18, 3 | BRF_GRA},
    {"ssf.18m", 0x100000, 0xf5b1b336, 3 | BRF_GRA},
    {"ssf.20m", 0x100000, 0x459d5c6b, 3 | BRF_GRA},
    {"ssf.01", 0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG},
    {"ssf.q01", 0x080000, 0xa6f9da5c, 5 | BRF_SND},
    {"ssf.q02", 0x080000, 0x8c66ae26, 5 | BRF_SND},
    {"ssf.q03", 0x080000, 0x695cc2ca, 5 | BRF_SND},
    {"ssf.q04", 0x080000, 0x9d9ebe32, 5 | BRF_SND},
    {"ssf.q05", 0x080000, 0x4770e7b7, 5 | BRF_SND},
    {"ssf.q06", 0x080000, 0x4e79c951, 5 | BRF_SND},
    {"ssf.q07", 0x080000, 0xcdd14313, 5 | BRF_SND},
    {"ssf.q08", 0x080000, 0x6f5a088c, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_ssf2tbd, BurnDrvCpsSsf2tb, "ssf2tbd", "Super Street Fighter II: The Tournament Battle (World 931119 Phoenix Edition)", "ssf2", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_ssf2udRomDesc[] = {
    {"ssfud.03a", 0x080000, 0xfad5daf8, 1 | BRF_ESS | BRF_PRG},
    {"ssfud.04a", 0x080000, 0x0d31af65, 1 | BRF_ESS | BRF_PRG},
    {"ssfud.05", 0x080000, 0x75c651ef, 1 | BRF_ESS | BRF_PRG},
    {"ssfud.06", 0x080000, 0x85c3ec00, 1 | BRF_ESS | BRF_PRG},
    {"ssfud.07", 0x080000, 0x247e2504, 1 | BRF_ESS | BRF_PRG},
    {"ssf.13m", 0x200000, 0xcf94d275, 3 | BRF_GRA},
    {"ssf.15m", 0x200000, 0x5eb703af, 3 | BRF_GRA},
    {"ssf.17m", 0x200000, 0xffa60e0f, 3 | BRF_GRA},
    {"ssf.19m", 0x200000, 0x34e825c5, 3 | BRF_GRA},
    {"ssf.14m", 0x100000, 0xb7cc32e7, 3 | BRF_GRA},
    {"ssf.16m", 0x100000, 0x8376ad18, 3 | BRF_GRA},
    {"ssf.18m", 0x100000, 0xf5b1b336, 3 | BRF_GRA},
    {"ssf.20m", 0x100000, 0x459d5c6b, 3 | BRF_GRA},
    {"ssf.01", 0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG},
    {"ssf.q01", 0x080000, 0xa6f9da5c, 5 | BRF_SND},
    {"ssf.q02", 0x080000, 0x8c66ae26, 5 | BRF_SND},
    {"ssf.q03", 0x080000, 0x695cc2ca, 5 | BRF_SND},
    {"ssf.q04", 0x080000, 0x9d9ebe32, 5 | BRF_SND},
    {"ssf.q05", 0x080000, 0x4770e7b7, 5 | BRF_SND},
    {"ssf.q06", 0x080000, 0x4e79c951, 5 | BRF_SND},
    {"ssf.q07", 0x080000, 0xcdd14313, 5 | BRF_SND},
    {"ssf.q08", 0x080000, 0x6f5a088c, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_ssf2ud, BurnDrvCpsSsf2, "ssf2ud", "Super Street Fighter II: The New Challengers (USA 930911 Phoenix Edition)", "ssf2", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_ssf2xjdRomDesc[] = {
    {"sfxjd.03c", 0x080000, 0x316de996, 1 | BRF_ESS | BRF_PRG},
    {"sfxjd.04a", 0x080000, 0x9bf3bb2e, 1 | BRF_ESS | BRF_PRG},
    {"sfxjd.05", 0x080000, 0xc63358d0, 1 | BRF_ESS | BRF_PRG},
    {"sfxjd.06a", 0x080000, 0xccb29808, 1 | BRF_ESS | BRF_PRG},
    {"sfxjd.07", 0x080000, 0x61f94982, 1 | BRF_ESS | BRF_PRG},
    {"sfxjd.08", 0x080000, 0xd399c36c, 1 | BRF_ESS | BRF_PRG},
    {"sfxd.09", 0x080000, 0x0b3a6196, 1 | BRF_ESS | BRF_PRG},
    {"sfx.13m", 0x200000, 0xcf94d275, 3 | BRF_GRA},
    {"sfx.15m", 0x200000, 0x5eb703af, 3 | BRF_GRA},
    {"sfx.17m", 0x200000, 0xffa60e0f, 3 | BRF_GRA},
    {"sfx.19m", 0x200000, 0x34e825c5, 3 | BRF_GRA},
    {"sfx.14m", 0x100000, 0xb7cc32e7, 3 | BRF_GRA},
    {"sfx.16m", 0x100000, 0x8376ad18, 3 | BRF_GRA},
    {"sfx.18m", 0x100000, 0xf5b1b336, 3 | BRF_GRA},
    {"sfx.20m", 0x100000, 0x459d5c6b, 3 | BRF_GRA},
    {"sfx.21m", 0x100000, 0xe32854af, 3 | BRF_GRA},
    {"sfx.23m", 0x100000, 0x760f2927, 3 | BRF_GRA},
    {"sfx.25m", 0x100000, 0x1ee90208, 3 | BRF_GRA},
    {"sfx.27m", 0x100000, 0xf814400f, 3 | BRF_GRA},
    {"sfx.01", 0x020000, 0xb47b8835, 4 | BRF_ESS | BRF_PRG},
    {"sfx.02", 0x020000, 0x0022633f, 4 | BRF_ESS | BRF_PRG},
    {"sfx.11m", 0x200000, 0x9bdbd476, 5 | BRF_SND},
    {"sfx.12m", 0x200000, 0xa05e3aab, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_ssf2xjd, BurnDrvCpsSsf2t, "ssf2xjr1d", "Super Street Fighter II X: Grand Master Challenge (Japan 940223 Phoenix Edition)", "ssf2", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_vsavdRomDesc[] = {
    {"vm3ed.03d", 0x080000, 0x97d805e3, 1 | BRF_ESS | BRF_PRG},
    {"vm3ed.04d", 0x080000, 0x5e07fdce, 1 | BRF_ESS | BRF_PRG},
    {"vm3.05a", 0x080000, 0x4118e00f, 1 | BRF_ESS | BRF_PRG},
    {"vm3.06a", 0x080000, 0x2f4fd3a9, 1 | BRF_ESS | BRF_PRG},
    {"vm3.07b", 0x080000, 0xcbda91b8, 1 | BRF_ESS | BRF_PRG},
    {"vm3.08a", 0x080000, 0x6ca47259, 1 | BRF_ESS | BRF_PRG},
    {"vm3.09b", 0x080000, 0xf4a339e3, 1 | BRF_ESS | BRF_PRG},
    {"vm3.10b", 0x080000, 0xfffbb5b8, 1 | BRF_ESS | BRF_PRG},
    {"vm3.13m", 0x400000, 0xfd8a11eb, 3 | BRF_GRA},
    {"vm3.15m", 0x400000, 0xdd1e7d4e, 3 | BRF_GRA},
    {"vm3.17m", 0x400000, 0x6b89445e, 3 | BRF_GRA},
    {"vm3.19m", 0x400000, 0x3830fdc7, 3 | BRF_GRA},
    {"vm3.14m", 0x400000, 0xc1a28e6c, 3 | BRF_GRA},
    {"vm3.16m", 0x400000, 0x194a7304, 3 | BRF_GRA},
    {"vm3.18m", 0x400000, 0xdf9a9f47, 3 | BRF_GRA},
    {"vm3.20m", 0x400000, 0xc22fc3d9, 3 | BRF_GRA},
    {"vm3.01", 0x020000, 0xf778769b, 4 | BRF_ESS | BRF_PRG},
    {"vm3.02", 0x020000, 0xcc09faa1, 4 | BRF_ESS | BRF_PRG},
    {"vm3.11m", 0x400000, 0xe80e956e, 5 | BRF_SND},
    {"vm3.12m", 0x400000, 0x9cd71557, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_vsavd, BurnDrvCpsVsav, "vsavd", "Vampire Savior: The Lord of Vampire (Europe 970519 Phoenix Edition)", "vsav", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_xmcotadRomDesc[] = {
    {"xmned.03e", 0x080000, 0xbef56003, 1 | BRF_ESS | BRF_PRG},
    {"xmned.04e", 0x080000, 0xb1a21fa6, 1 | BRF_ESS | BRF_PRG},
    {"xmn.05a", 0x080000, 0xac0d7759, 1 | BRF_ESS | BRF_PRG},
    {"xmn.06a", 0x080000, 0x1b86a328, 1 | BRF_ESS | BRF_PRG},
    {"xmn.07a", 0x080000, 0x2c142a44, 1 | BRF_ESS | BRF_PRG},
    {"xmn.08a", 0x080000, 0xf712d44f, 1 | BRF_ESS | BRF_PRG},
    {"xmn.09a", 0x080000, 0x9241cae8, 1 | BRF_ESS | BRF_PRG},
    {"xmn.10a", 0x080000, 0x53c0eab9, 1 | BRF_ESS | BRF_PRG},
    {"xmn.13m", 0x400000, 0xbf4df073, 3 | BRF_GRA},
    {"xmn.15m", 0x400000, 0x4d7e4cef, 3 | BRF_GRA},
    {"xmn.17m", 0x400000, 0x513eea17, 3 | BRF_GRA},
    {"xmn.19m", 0x400000, 0xd23897fc, 3 | BRF_GRA},
    {"xmn.14m", 0x400000, 0x778237b7, 3 | BRF_GRA},
    {"xmn.16m", 0x400000, 0x67b36948, 3 | BRF_GRA},
    {"xmn.18m", 0x400000, 0x015a7c4c, 3 | BRF_GRA},
    {"xmn.20m", 0x400000, 0x9dde2758, 3 | BRF_GRA},
    {"xmn.01a", 0x020000, 0x40f479ea, 4 | BRF_ESS | BRF_PRG},
    {"xmn.02a", 0x020000, 0x39d9b5ad, 4 | BRF_ESS | BRF_PRG},
    {"xmn.11m", 0x200000, 0xc848a6bc, 5 | BRF_SND},
    {"xmn.12m", 0x200000, 0x729c188f, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_xmcotad, BurnDrvCpsXmcota, "xmcotar1d", "X-Men: Children of the Atom (Europe 950105 Phoenix Edition)", "xmcota", HARDWARE_CAPCOM_CPS2_PHOENIX)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_xmcotajRomDesc[] = {
    {"xmnj.03d", 0x080000, 0x79086d62, 1 | BRF_ESS | BRF_PRG},
    {"xmnj.04d", 0x080000, 0x38eed613, 1 | BRF_ESS | BRF_PRG},
    {"xmn.05", 0x080000, 0xc3ed62a2, 1 | BRF_ESS | BRF_PRG},
    {"xmn.06", 0x080000, 0xf03c52e1, 1 | BRF_ESS | BRF_PRG},
    {"xmn.07", 0x080000, 0x325626b1, 1 | BRF_ESS | BRF_PRG},
    {"xmn.08", 0x080000, 0x7194ea10, 1 | BRF_ESS | BRF_PRG},
    {"xmn.09", 0x080000, 0xae946df3, 1 | BRF_ESS | BRF_PRG},
    {"xmn.10", 0x080000, 0x32a6be1d, 1 | BRF_ESS | BRF_PRG},
    {"xmn.13m", 0x400000, 0xbf4df073, 3 | BRF_GRA},
    {"xmn.15m", 0x400000, 0x4d7e4cef, 3 | BRF_GRA},
    {"xmn.17m", 0x400000, 0x513eea17, 3 | BRF_GRA},
    {"xmn.19m", 0x400000, 0xd23897fc, 3 | BRF_GRA},
    {"xmn.14m", 0x400000, 0x778237b7, 3 | BRF_GRA},
    {"xmn.16m", 0x400000, 0x67b36948, 3 | BRF_GRA},
    {"xmn.18m", 0x400000, 0x015a7c4c, 3 | BRF_GRA},
    {"xmn.20m", 0x400000, 0x9dde2758, 3 | BRF_GRA},
    {"xmn.01a", 0x020000, 0x40f479ea, 4 | BRF_ESS | BRF_PRG},
    {"xmn.02a", 0x020000, 0x39d9b5ad, 4 | BRF_ESS | BRF_PRG},
    {"xmn.11m", 0x200000, 0xc848a6bc, 5 | BRF_SND},
    {"xmn.12m", 0x200000, 0x729c188f, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_xmcotaj, BurnDrvCpsXmcotaj, "xmcotaj1_rev", "X-Men: Children of the Atom (Japan 941222)", "xmcota", 0)

#ifndef ASTRA_REVISION_REGISTRY_ONLY
static BurnRomInfo AstraRev_xmvsfu1dRomDesc[] = {
    {"xvsud.03h", 0x080000, 0x4e2e76b7, 1 | BRF_ESS | BRF_PRG},
    {"xvsud.04h", 0x080000, 0x290c61a7, 1 | BRF_ESS | BRF_PRG},
    {"xvs.05a", 0x080000, 0x7db6025d, 1 | BRF_ESS | BRF_PRG},
    {"xvs.06a", 0x080000, 0xe8e2c75c, 1 | BRF_ESS | BRF_PRG},
    {"xvs.07", 0x080000, 0x08f0abed, 1 | BRF_ESS | BRF_PRG},
    {"xvs.08", 0x080000, 0x81929675, 1 | BRF_ESS | BRF_PRG},
    {"xvs.09", 0x080000, 0x9641f36b, 1 | BRF_ESS | BRF_PRG},
    {"xvs.13m", 0x400000, 0xf6684efd, 3 | BRF_GRA},
    {"xvs.15m", 0x400000, 0x29109221, 3 | BRF_GRA},
    {"xvs.17m", 0x400000, 0x92db3474, 3 | BRF_GRA},
    {"xvs.19m", 0x400000, 0x3733473c, 3 | BRF_GRA},
    {"xvs.14m", 0x400000, 0xbcac2e41, 3 | BRF_GRA},
    {"xvs.16m", 0x400000, 0xea04a272, 3 | BRF_GRA},
    {"xvs.18m", 0x400000, 0xb0def86a, 3 | BRF_GRA},
    {"xvs.20m", 0x400000, 0x4b40ff9f, 3 | BRF_GRA},
    {"xvs.01", 0x020000, 0x3999e93a, 4 | BRF_ESS | BRF_PRG},
    {"xvs.02", 0x020000, 0x101bdee9, 4 | BRF_ESS | BRF_PRG},
    {"xvs.11m", 0x200000, 0x9cadcdbc, 5 | BRF_SND},
    {"xvs.12m", 0x200000, 0x7b11e460, 5 | BRF_SND},
};
#endif
ASTRA_REVISION(AstraRev_xmvsfu1d, BurnDrvCpsXmvsf, "xmvsfu1d", "X-Men Vs. Street Fighter (USA 961004 Phoenix Edition)", "xmvsf", HARDWARE_CAPCOM_CPS2_PHOENIX)
