#include <device.h>

// Video buffer gets its own SRAM to prevent bus contention.
// The user-facing buffer is in regular system RAM.
// This is set in the custom linker script (custom.ld).
uint8 buf[96][128], vbuf[96][128] __attribute__ ((section(".vram")));

// Now we set up the DMA to copy pixels from vbuf to the screen.
// For timing, we rely on the fact that it takes the DMA exactly
// 8 clocks to move each byte. After each line the DMA is updated
// to point to the next line in vbuf.
uint8 dma_chan, dma_td;
volatile int flag = 1;
CY_ISR(newline) {
    uint16 line = 805 - VERT_ReadCounter();
    if (line % 8 == 0) {
        if (line < 768) {
            CY_SET_REG16(CY_DMA_TDMEM_STRUCT_PTR[dma_td].TD1,
                         LO16((uint32) vbuf[line / 8]));
        } else if (line == 768 && flag) {  // refresh the buffer during vsync
            CyDmaChDisable(dma_chan);
            if (flag) {
                memcpy(*vbuf, *buf, 96 * 128);
                flag = 0;
            }
            CyDmaChEnable(dma_chan, 1);
        }
    }
}
inline void update() {
    flag = 1;
    while (flag);
}

void main() {
    // Initialize the DMA.
    dma_td = CyDmaTdAllocate();
    dma_chan = DMA_DmaInitialize(1, 0, HI16(CYDEV_SRAM_BASE), HI16(CYDEV_PERIPH_BASE));
    CyDmaTdSetConfiguration(dma_td, 128, dma_td, DMA__TD_TERMOUT_EN | TD_INC_SRC_ADR);
    CyDmaTdSetAddress(dma_td, 0, LO16((uint32) PIXEL_Control_PTR));
    CyDmaChSetInitialTd(dma_chan, dma_td);
    CyDmaChEnable(dma_chan, 1);
    
    // Start all of the timing counters and the UART.
    HORIZ_Start();
    VERT_Start();
    HSYNC_Start();
    VSYNC_Start();
    NEWLINE_StartEx(newline);
    UART_Start();
    CyGlobalIntEnable;
    
    int x = 0, y = 0, i, j;
    // Mode definition:
    // bit 7 may have an arbitrary value.
    // if bits 2-6 are zero, draw raster images at a resolution determined by bits 0-1.
    uint8 mode = 0;
    for(;;) {
        CyDelayUs(100);  // can't check UART too quickly or bus saturation causes graphics blips
        if (!(UART_ReadRxStatus() & UART_RX_STS_FIFO_NOTEMPTY)) continue;
        uint8 c = UART_GetByte();
        if (c & 0x80) {
            mode = c;
            x = y = 0;
        } else {
            int step = ((mode & 1) ? 1 : 2) * ((mode & 2) ? 1 : 4);
            for (i = 0; i < step; ++i) {
                for (j = 0; j < step; ++j) {
                    buf[y + i][x + j] = c & 0x3f;
                }
            }
            x += step;
            if (x == 128) {
                x = 0;
                y += step;
                if (y == 96) {
                    y = 0;
                    update();
                }
            }
        }
    }
}
