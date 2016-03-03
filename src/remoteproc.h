#ifndef __REMOTEPROC_H__
#define __REMOTEPROC_H__

#include <stdint.h>
#include <stddef.h>


/**
 * These definitions come from <linux/remoteproc.h> and
 * may change as the remote processor interface is updated.
 * Make sure they match the ones used by your current kernel
 * source.
 */

struct fw_rsc_hdr {
	uint32_t type;
	uint8_t data[0];
} __attribute__ ((packed));

struct fw_rsc_carveout {
	uint32_t da;
	uint32_t pa;
	uint32_t len;
	uint32_t flags;
	uint32_t reserved;
	uint8_t name[32];
} __attribute__ ((packed));

struct fw_rsc_devmem {
	uint32_t da;
	uint32_t pa;
	uint32_t len;
	uint32_t flags;
	uint32_t reserved;
	uint8_t name[32];
} __attribute__ ((packed));

struct fw_rsc_trace {
	uint32_t da;
	uint32_t len;
	uint32_t reserved;
	uint8_t name[32];
} __attribute__ ((packed));

enum fw_resource_type {
	RSC_CARVEOUT = 0,
	RSC_DEVMEM = 1,
	RSC_TRACE = 2,
	RSC_VDEV = 3,
	RSC_INTMEM = 4,
	RSC_CUSTOM = 5,
	RSC_LAST = 6,
};

#endif
