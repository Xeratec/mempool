// Copyright 2021 ETH Zurich and University of Bologna.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

/* This file will get processed by the precompiler to expand all macros. */

MEMORY {
  l1 (RW) : ORIGIN = 0x00000000, LENGTH = (NUM_EFF_CORES * BANKING_FACTOR * 0x400)-1 /* NUM_CORES * 4 * 1KiB per bank */
  l1_accel (RW) : ORIGIN = (NUM_EFF_CORES * BANKING_FACTOR * 0x400), LENGTH = ((NUM_CORES-NUM_EFF_CORES) * BANKING_FACTOR * 0x400)
  l2 (RWX)    : ORIGIN = L2_BASE   , LENGTH = L2_SIZE
  rom (R): ORIGIN = BOOT_ADDR , LENGTH = 0x00001000
}

SECTIONS {
  // Start end end of memories
  __l1_start = ORIGIN(l1);
  __l1_end = ORIGIN(l1) + LENGTH(l1);
  __l1_accel_start = ORIGIN(l1_accel);
  __l1_accel_end = ORIGIN(l1_accel) + LENGTH(l1_accel);
  __l2_start = ORIGIN(l2);
  __l2_end = ORIGIN(l2) + LENGTH(l2);
  __rom_start = ORIGIN(rom);
  __rom_end = ORIGIN(rom) + LENGTH(rom);

  // Stack size
  __stack_start = __l1_start;
  __stack_end = __l1_start + (NUM_EFF_CORES * STACK_SIZE);

  // Sequential region size
  __seq_start = __l1_start;
  __seq_end = __l1_start + (NUM_EFF_CORES * SEQ_MEM_SIZE);

  // Heap size (start address is re-assigned in link.ld)
  __heap_end = __l1_end;

  __accel_start = __l1_accel_start;
  __accel_end = __l1_accel_end;

  // Hardware register location
  eoc_reg                  = 0x40000000;
  wake_up_reg              = 0x40000004;
  wake_up_group_reg        = 0x40000008;
  tcdm_start_address_reg   = 0x4000000C;
  tcdm_end_address_reg     = 0x40000010;
  nr_cores_address_reg     = 0x40000014;
  ro_cache_enable          = 0x40000018;
  ro_cache_flush           = 0x4000001C;
  ro_cache_start_0         = 0x40000020;
  ro_cache_end_0           = 0x40000024;
  ro_cache_start_1         = 0x40000028;
  ro_cache_end_1           = 0x4000002C;
  ro_cache_start_2         = 0x40000030;
  ro_cache_end_2           = 0x40000034;
  ro_cache_start_3         = 0x40000038;
  ro_cache_end_3           = 0x4000003c;
  ita_state_0              = 0x40000040;
  ita_start_addr_0         = 0x40000044;
  ita_eps_mult_L_0         = 0x40000048;
  ita_eps_mult_H_0         = 0x4000004C;
  ita_right_shift_L_0      = 0x40000050;
  ita_right_shift_H_0      = 0x40000054;
  ita_add_L_0              = 0x40000058;
  ita_add_H_0              = 0x4000005C;
  ita_state_1              = 0x40000060;
  ita_start_addr_1         = 0x40000064;
  ita_eps_mult_L_1         = 0x40000068;
  ita_eps_mult_H_1         = 0x4000006C;
  ita_right_shift_L_1      = 0x40000070;
  ita_right_shift_H_1      = 0x40000074;
  ita_add_L_1              = 0x40000078;
  ita_add_H_1              = 0x4000007C;
  ita_state_2              = 0x40000080;
  ita_start_addr_2         = 0x40000084;
  ita_eps_mult_L_2         = 0x40000088;
  ita_eps_mult_H_2         = 0x4000008C;
  ita_right_shift_L_2      = 0x40000090;
  ita_right_shift_H_2      = 0x40000094;
  ita_add_L_2              = 0x40000098;
  ita_add_H_2              = 0x4000009C;
  ita_state_3              = 0x400000a0;
  ita_start_addr_3         = 0x400000a4;
  ita_eps_mult_L_3         = 0x400000A8;
  ita_eps_mult_H_3         = 0x400000AC;
  ita_right_shift_L_3      = 0x400000B0;
  ita_right_shift_H_3      = 0x400000B4;
  ita_add_L_3              = 0x400000B8;
  ita_add_H_3              = 0x400000BC;

  wake_up_tile_g0_reg      = 0x400000C0;
  wake_up_tile_g1_reg      = 0x400000C4;
  wake_up_tile_g2_reg      = 0x400000C8;
  wake_up_tile_g3_reg      = 0x400000CC;
  wake_up_tile_g4_reg      = 0x400000D0;
  wake_up_tile_g5_reg      = 0x400000D4;
  wake_up_tile_g6_reg      = 0x400000D8;
  wake_up_tile_g7_reg      = 0x400000DC;

  fake_uart              = 0xC0000000;
}
