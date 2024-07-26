// Copyright 2021 ETH Zurich and University of Bologna.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

// Author: Samuel Riedel, ETH Zurich

// ATTENTION: The DMA is in a very preliminary state and likely to cause issues.


#include "mempool_dma_frontend.h"
#include "dma.h"

void dma_memcpy_nonblocking(void *dest, const void *src, size_t len) {
  volatile uint32_t *_dma_src_reg =
      (volatile uint32_t *)(DMA_BASE +
                            MEMPOOL_DMA_FRONTEND_SRC_ADDR_REG_OFFSET);
  volatile uint32_t *_dma_dst_reg =
      (volatile uint32_t *)(DMA_BASE +
                            MEMPOOL_DMA_FRONTEND_DST_ADDR_REG_OFFSET);
  volatile uint32_t *_dma_len_reg =
      (volatile uint32_t *)(DMA_BASE +
                            MEMPOOL_DMA_FRONTEND_NUM_BYTES_REG_OFFSET);
  volatile uint32_t *_dma_id_reg =
      (volatile uint32_t *)(DMA_BASE + MEMPOOL_DMA_FRONTEND_NEXT_ID_REG_OFFSET);
  // Configure the DMA
  *_dma_src_reg = (uint32_t)src;
  *_dma_dst_reg = (uint32_t)dest;
  *_dma_len_reg = (uint32_t)len;
  // TODO: We need a fence here!
  asm volatile("" ::: "memory");
  mempool_wait(32);
  asm volatile("" ::: "memory");
  // Launch the transfer
  __sync_synchronize(); // Full memory barrier
  (void)*_dma_id_reg;
}

void dma_memcpy_blocking(void *dest, const void *src, size_t len) {
  dma_memcpy_nonblocking(dest, src, len);
  dma_wait();
}