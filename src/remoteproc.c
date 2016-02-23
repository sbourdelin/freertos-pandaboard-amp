#include <stddef.h>

#include "board.h"
#include "remoteproc.h"

#define FW_RSC_NUM 4
struct resource_table {
	uint32_t version;
	uint32_t num;
	uint32_t reserved[2];
	uint32_t offset[FW_RSC_NUM]; /* Should match 'num' in actual definition */
	struct fw_rsc_hdr text_hdr;
	struct fw_rsc_carveout text_carveout;
	struct fw_rsc_hdr data_hdr;
	struct fw_rsc_carveout data_carveout;
	struct fw_rsc_hdr l4_cfg_hdr;
	struct fw_rsc_devmem l4_cfg_devmem;
	struct fw_rsc_hdr l4_per_hdr;
	struct fw_rsc_devmem l4_per_devmem;

} __attribute__ ((packed));

__attribute__ ((section(".resource_table")))
struct resource_table resources = {
	.version = 1,
	.num = FW_RSC_NUM,
	.reserved = {
		0, 0
	},
	.offset = {
		offsetof(struct resource_table, text_hdr),
		offsetof(struct resource_table, data_hdr),
		offsetof(struct resource_table, l4_cfg_hdr),
		offsetof(struct resource_table, l4_per_hdr),
	},
	.text_hdr = {
		RSC_CARVEOUT
	},
	.text_carveout = {
		IPU_MEM_TEXT_BASE, /* virtual address */
		0x0, /* physical address is not relevant here */
		IPU_MEM_TEXT_SIZE,
		0x0,
		0x0,
		IPU_MEM_TEXT_NAME
	},
	.data_hdr = {
		RSC_CARVEOUT
	},
	.data_carveout = {
		IPU_MEM_DATA_BASE,
		0x0,
		IPU_MEM_DATA_SIZE,
		0x0,
		0x0,
		IPU_MEM_DATA_NAME
	},
	.l4_cfg_hdr = {
		RSC_DEVMEM
	},
	.l4_cfg_devmem = {
		IPU_PERIPHERAL_L4CFG_BASE,
		L4_PERIPHERAL_L4CFG_BASE,
		IPU_PERIPHERAL_L4CFG_SIZE,
		0x0,
		0x0,
		IPU_PERIPHERAL_L4CFG_NAME
	},
	.l4_per_hdr = {
		RSC_DEVMEM
	},
	.l4_per_devmem = {
		IPU_PERIPHERAL_L4PER_BASE,
		L4_PERIPHERAL_L4PER_BASE,
		IPU_PERIPHERAL_L4PER_SIZE,
		0x0,
		0x0,
		IPU_PERIPHERAL_L4PER_NAME
	},
};
