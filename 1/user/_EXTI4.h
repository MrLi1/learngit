#ifndef ___EXTI4_H
#define ___EXTI4_H

#endif

#define Periph_BASE         0x40000000  // 外设基地址 Peripheral 
#define Periph_BB_BASE      0x42000000  // 外设别名区基地址 Peripheral bitband
#define Periph_BB(PeriphAddr, BitNumber)       *(__IO uint32_t *) (Periph_BB_BASE | ((PeriphAddr - Periph_BASE) << 5) | ((BitNumber) << 2))
#define Periph_SetBit_BB(PeriphAddr, BitNumber)     (*(__IO uint32_t *) (Periph_BB_BASE | ((PeriphAddr - Periph_BASE) << 5) | ((BitNumber) << 2)) = 1)
#define GETIBB        Periph_BB((uint32_t)&GPIOB->IDR, 7)
#define SETIBB        Periph_SetBit_BB((uint32_t)&GPIOB->IDR, 7)

void EXTIX_Init(void);
void NVIC_GroupConfig(void);

