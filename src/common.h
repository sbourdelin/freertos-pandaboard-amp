#ifndef __COMMON_H
#define __COMMON_H

#include <stdint.h>

#define SZ_256K				0x00040000
#define SZ_1M				0x00100000
#define SZ_16M                          0x01000000

#define BIT_SET(REG, BIT)		(*((uint32_t *)REG) |= (1 << BIT))
#define BIT_GET(REG, BIT)		(*((uint32_t *)REG) &  (1 << BIT))
#define BIT_CLEAR(REG, BIT)		(*((uint32_t *)REG) &= ~(1 << BIT))
#define BIT_TOGGLE(REG, BIT)		(*((uint32_t *)REG) ^= (1 << BIT))
#define write32(ADDR, VAL)		(*((uint32_t *)ADDR) = (uint32_t)(VAL))
#define read32(ADDR)			(*((uint32_t *)ADDR))

#endif
