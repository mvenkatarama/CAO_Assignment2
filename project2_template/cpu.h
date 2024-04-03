#ifndef CPU_H_
#define CPU_H_

#include <stdio.h>
/**
 * @brief definition of const variables
 * Note : You are free to edit this section according to your implementation
 */
#define NUM_REGISTERS 64
#define BYTE 8
#define MEM_SIZE 64*1024
#define CPU_COUNTERS 17

/**
 * @brief The definition of the CPU
 */
typedef struct CPU
{
    // 4 bytes integer registers
	int registers[NUM_REGISTERS];

	// CPU stats
    int stats[CPU_COUNTERS];

    // other informations needed to define here
} CPU_t;

#endif
