/*
 * (C) Copyright 2000-2009
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * Copy the startup prototype, previously defined in common.h
 * Copyright (C) 2018, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __INIT_H_
#define __INIT_H_	1

#ifndef __ASSEMBLY__		/* put C only stuff in this section */

/*
 * Function Prototypes
 */

/* common/board_f.c */
void board_init_f(ulong dummy);

/**
 * arch_cpu_init() - basic cpu-dependent setup for an architecture
 *
 * This is called after early malloc is available. It should handle any
 * CPU- or SoC- specific init needed to continue the init sequence. See
 * board_f.c for where it is called. If this is not provided, a default
 * version (which does nothing) will be used.
 *
 * @return: 0 on success, otherwise error
 */
int arch_cpu_init(void);

/**
 * arch_cpu_init_dm() - init CPU after driver model is available
 *
 * This is called immediately after driver model is available before
 * relocation. This is similar to arch_cpu_init() but is able to reference
 * devices
 *
 * @return 0 if OK, -ve on error
 */
int arch_cpu_init_dm(void);

/**
 * mach_cpu_init() - SoC/machine dependent CPU setup
 *
 * This is called after arch_cpu_init(). It should handle any
 * SoC or machine specific init needed to continue the init sequence. See
 * board_f.c for where it is called. If this is not provided, a default
 * version (which does nothing) will be used.
 *
 * @return: 0 on success, otherwise error
 */
int mach_cpu_init(void);

/**
 * arch_fsp_init() - perform firmware support package init
 *
 * Where U-Boot relies on binary blobs to handle part of the system init, this
 * function can be used to set up the blobs. This is used on some Intel
 * platforms.
 */
int arch_fsp_init(void);

int dram_init(void);

/**
 * dram_init_banksize() - Set up DRAM bank sizes
 *
 * This can be implemented by boards to set up the DRAM bank information in
 * gd->bd->bi_dram(). It is called just before relocation, after dram_init()
 * is called.
 *
 * If this is not provided, a default implementation will try to set up a
 * single bank. It will do this if CONFIG_NR_DRAM_BANKS and
 * CONFIG_SYS_SDRAM_BASE are set. The bank will have a start address of
 * CONFIG_SYS_SDRAM_BASE and the size will be determined by a call to
 * get_effective_memsize().
 *
 * @return 0 if OK, -ve on error
 */
int dram_init_banksize(void);

/**
 * Reserve all necessary stacks
 *
 * This is used in generic board init sequence in common/board_f.c. Each
 * architecture could provide this function to tailor the required stacks.
 *
 * On entry gd->start_addr_sp is pointing to the suggested top of the stack.
 * The callee ensures gd->start_add_sp is 16-byte aligned, so architectures
 * require only this can leave it untouched.
 *
 * On exit gd->start_addr_sp and gd->irq_sp should be set to the respective
 * positions of the stack. The stack pointer(s) will be set to this later.
 * gd->irq_sp is only required, if the architecture needs it.
 *
 * @return 0 if no error
 */
int arch_reserve_stacks(void);

int print_cpuinfo(void);
int timer_init(void);
int reserve_mmu(void);
int misc_init_f(void);
#if defined(CONFIG_DTB_RESELECT)
int embedded_dtb_select(void);
#endif

/* common/board_r.c */

#endif	/* __ASSEMBLY__ */
/* Put only stuff here that the assembler can digest */

#endif	/* __INIT_H_ */