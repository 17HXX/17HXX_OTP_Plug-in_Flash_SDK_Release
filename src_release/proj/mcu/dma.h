
#pragma once

#include "../mcu/register.h"

static inline void dma_init(){
	reg_dma_chn_irq_msk =
			(RF_RX_USE_DMA_IRQ ? FLD_DMA_RF_RX : 0) | (RF_TX_USE_DMA_IRQ ? FLD_DMA_RF_TX : 0);
}

static inline void dma_irq_clear(){
	reg_dma_chn_irq_msk = 0;
}

static inline void dma_channel_enable_all(){
	reg_dma_chn_en = 0xff;
}

static inline void dma_channel_disable_all(){
	reg_dma_chn_en = 0;
}

