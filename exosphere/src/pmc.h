#ifndef EXOSPHERE_PMC_H
#define EXOSPHERE_PMC_H

#include <stdint.h>
#include "memory_map.h"

/* Exosphere register definitions for the Tegra X1 PMC. */

static inline uintptr_t get_pmc_base(void) {
    return MMIO_GET_DEVICE_ADDRESS(MMIO_DEVID_RTC_PMC) + 0x400ull;
}

#define PMC_BASE (get_pmc_base())

#define APBDEV_PMC_DPD_ENABLE_0 (*((volatile uint32_t *)(PMC_BASE + 0x24)))

#define APBDEV_PMC_PWRGATE_TOGGLE_0 (*((volatile uint32_t *)(PMC_BASE + 0x30)))
#define APBDEV_PMC_PWRGATE_STATUS_0 (*((volatile uint32_t *)(PMC_BASE + 0x38)))

#define APBDEV_PMC_SCRATCH0_0 (*((volatile uint32_t *)(PMC_BASE + 0x50)))

#define APBDEV_PMC_CRYPTO_OP_0 (*((volatile uint32_t *)(PMC_BASE + 0xF4)))

#define APBDEV_PM_0 (*((volatile uint32_t *)(PMC_BASE + 0x14)))
#define APBDEV_PMC_WAKE2_STATUS_0 (*((volatile uint32_t *)(PMC_BASE + 0x168)))
#define APBDEV_PMC_CNTRL2_0 (*((volatile uint32_t *)(PMC_BASE + 0x440)))

#define APBDEV_PMC_SCRATCH43_0 (*((volatile uint32_t *)(PMC_BASE + 0x22C)))
#define APBDEV_PMC_SEC_DISABLE8_0 (*((volatile uint32_t *)(PMC_BASE + 0x5C0)))
#define APBDEV_PMC_SECURE_SCRATCH112_0 (*((volatile uint32_t *)(PMC_BASE + 0xB18)))
#define APBDEV_PMC_SECURE_SCRATCH113_0 (*((volatile uint32_t *)(PMC_BASE + 0xB1C)))
#define APBDEV_PMC_SECURE_SCRATCH114_0 (*((volatile uint32_t *)(PMC_BASE + 0xB20)))
#define APBDEV_PMC_SECURE_SCRATCH115_0 (*((volatile uint32_t *)(PMC_BASE + 0xB24)))

#define APBDEV_PMC_SCRATCH200_0 (*((volatile uint32_t *)(PMC_BASE + 0x840)))



#endif