#include "cpu.h"

void print_registers(int* registers);
void print_statistics(int stats[]);

CPU_t cpu;

int readFile(const char *filePath) {
    FILE *binaryFile;
    unsigned int instructionBuffer[1];
    instructionBuffer[0] = 0;

    // printf("FilePath : %s", filePath);
    binaryFile = fopen(filePath, "rb");

    if (binaryFile == NULL) {
        perror("Error opening the file");
        return 1;
    }

    int iteration = 50;
    unsigned int rx=0, ry=0, rz=0, imm_value1=0, imm_value2=0, first_byte=0, second_byte=0, temp = 0;
    int flag = 1;
    // printf("\nCheckpoint 1\n");
    while (fread(instructionBuffer, 1, 1, binaryFile) == 1 && flag==1) {
        // printf("\nRead Instruction %d: 0x%02X", i, instructionBuffer[0]);
        int number_of_operands = 0;
        cpu.stats[9]+=1;
	// printf("\n%d", instructionBuffer[0]);
        switch (instructionBuffer[0])
        {
        case 0x01:
            // printf(" - Set");

            fread(instructionBuffer, 1, 1, binaryFile);
            // printf("R%d = ",instructionBuffer[0]);
            rx = instructionBuffer[0];

            fread(instructionBuffer, 1, 1, binaryFile);
            first_byte = instructionBuffer[0];
            second_byte = first_byte << 8;
            fread(instructionBuffer, 1, 1, binaryFile);
            second_byte += instructionBuffer[0];
            imm_value1 = second_byte;

            // printf("%d",imm_value1);

            cpu.registers[rx] = imm_value1;
            cpu.stats[0]+=1;
            cpu.stats[6]+=1;
            break;

        case 0x10:
            // printf(" - Add 1");
            fread(instructionBuffer, 1, 1, binaryFile);
            rx = instructionBuffer[0];
            fread(instructionBuffer, 1, 1, binaryFile);
            ry = instructionBuffer[0];
            fread(instructionBuffer, 1, 1, binaryFile);
            rz = instructionBuffer[0];
            cpu.registers[rx] = cpu.registers[ry] + cpu.registers[rz];
            // printf("R%d = %d", rx, cpu.registers[rx]);
            cpu.stats[1]+=1;
            cpu.stats[6]+=1;
            break;

        case 0x50:
            // printf(" - Add 2");
            fread(instructionBuffer, 1, 1, binaryFile);
            rx = instructionBuffer[0];
            fread(instructionBuffer, 1, 1, binaryFile);
            ry = instructionBuffer[0];

            fread(instructionBuffer, 1, 1, binaryFile);
            first_byte = instructionBuffer[0];
            second_byte = first_byte << 8;
            fread(instructionBuffer, 1, 1, binaryFile);
            second_byte += instructionBuffer[0];
            imm_value1 = second_byte;

            cpu.registers[rx] = cpu.registers[ry] + imm_value1;
            // printf("R%d = %d", rx, cpu.registers[rx]);
            cpu.stats[1]+=1;
            cpu.stats[7]+=1;
            break;

        case 0x90:
            // printf(" - Add 3");
            fread(instructionBuffer, 1, 1, binaryFile);
            rx = instructionBuffer[0];

            fread(instructionBuffer, 1, 1, binaryFile);
            first_byte = instructionBuffer[0];
            second_byte = first_byte << 8;
            fread(instructionBuffer, 1, 1, binaryFile);
            second_byte += instructionBuffer[0];
            imm_value1 = second_byte;

            fread(instructionBuffer, 1, 1, binaryFile);
            first_byte = instructionBuffer[0];
            second_byte = first_byte << 8;
            fread(instructionBuffer, 1, 1, binaryFile);
            second_byte += instructionBuffer[0];
            imm_value2 = second_byte;

            cpu.registers[rx] = imm_value1 + imm_value2;
            // printf("R%d = %d", rx, cpu.registers[rx]);
            cpu.stats[1]+=1;
            cpu.stats[8]+=1;
            break;

        case 0x14:
            // printf(" - Sub 1");
            fread(instructionBuffer, 1, 1, binaryFile);
            rx = instructionBuffer[0];
            fread(instructionBuffer, 1, 1, binaryFile);
            ry = instructionBuffer[0];
            fread(instructionBuffer, 1, 1, binaryFile);
            rz = instructionBuffer[0];
            cpu.registers[rx] = cpu.registers[ry] - cpu.registers[rz];
            // printf("R%d = %d", rx, cpu.registers[rx]);
            cpu.stats[2]+=1;
            cpu.stats[6]+=1;
            break;

        case 0x54:
            // printf(" - Sub 2");
            fread(instructionBuffer, 1, 1, binaryFile);
            rx = instructionBuffer[0];
            fread(instructionBuffer, 1, 1, binaryFile);
            ry = instructionBuffer[0];
            
            fread(instructionBuffer, 1, 1, binaryFile);
            first_byte = instructionBuffer[0];
            second_byte = first_byte << 8;
            fread(instructionBuffer, 1, 1, binaryFile);
            second_byte += instructionBuffer[0];
            imm_value1 = second_byte;

            cpu.registers[rx] = cpu.registers[ry] - imm_value1;
            // printf("R%d = %d", rx, cpu.registers[rx]);
            cpu.stats[2]+=1;
            cpu.stats[7]+=1;
            break;

        case 0x94:
            // printf(" - Sub 3");
            fread(instructionBuffer, 1, 1, binaryFile);
            rx = instructionBuffer[0];

            fread(instructionBuffer, 1, 1, binaryFile);
            first_byte = instructionBuffer[0];
            second_byte = first_byte << 8;
            fread(instructionBuffer, 1, 1, binaryFile);
            second_byte += instructionBuffer[0];
            imm_value1 = second_byte;

            fread(instructionBuffer, 1, 1, binaryFile);
            first_byte = instructionBuffer[0];
            second_byte = first_byte << 8;
            fread(instructionBuffer, 1, 1, binaryFile);
            second_byte += instructionBuffer[0];
            imm_value2 = second_byte;

            cpu.registers[rx] = imm_value1 - imm_value2;
            // printf("R%d = %d", rx, cpu.registers[rx]);
            cpu.stats[2]+=1;
            cpu.stats[8]+=1;
            break;

        case 0x18:
            // printf(" - Mul 1");
            fread(instructionBuffer, 1, 1, binaryFile);
            rx = instructionBuffer[0];
            fread(instructionBuffer, 1, 1, binaryFile);
            ry = instructionBuffer[0];
            fread(instructionBuffer, 1, 1, binaryFile);
            rz = instructionBuffer[0];
            cpu.registers[rx] = cpu.registers[ry] * cpu.registers[rz];
            // printf("R%d = %d", rx, cpu.registers[rx]);
            cpu.stats[3]+=1;
            cpu.stats[6]+=1;
            break;

        case 0x58:
            // printf(" - Mul 2");
            fread(instructionBuffer, 1, 1, binaryFile);
            rx = instructionBuffer[0];
            fread(instructionBuffer, 1, 1, binaryFile);
            ry = instructionBuffer[0];

            fread(instructionBuffer, 1, 1, binaryFile);
            first_byte = instructionBuffer[0];
            second_byte = first_byte << 8;
            fread(instructionBuffer, 1, 1, binaryFile);
            second_byte += instructionBuffer[0];
            imm_value1 = second_byte;

            cpu.registers[rx] = cpu.registers[ry] * imm_value1;
            // printf("R%d = %d", rx, cpu.registers[rx]);
            cpu.stats[3]+=1;
            cpu.stats[7]+=1;
            break;
        
        case 0x98:
            // printf(" - Mul 3");
            fread(instructionBuffer, 1, 1, binaryFile);
            rx = instructionBuffer[0];

            fread(instructionBuffer, 1, 1, binaryFile);
            first_byte = instructionBuffer[0];
            second_byte = first_byte << 8;
            fread(instructionBuffer, 1, 1, binaryFile);
            second_byte += instructionBuffer[0];
            imm_value1 = second_byte;

            fread(instructionBuffer, 1, 1, binaryFile);
            first_byte = instructionBuffer[0];
            second_byte = first_byte << 8;
            fread(instructionBuffer, 1, 1, binaryFile);
            second_byte += instructionBuffer[0];
            imm_value2 = second_byte;

            cpu.registers[rx] = imm_value1 * imm_value2;
            // printf("R%d = %d", rx, cpu.registers[rx]);
            cpu.stats[3]+=1;
            cpu.stats[8]+=1;
            break;

        case 0x1C:
            // printf(" - Div 1");
            fread(instructionBuffer, 1, 1, binaryFile);
            rx = instructionBuffer[0];
            fread(instructionBuffer, 1, 1, binaryFile);
            ry = instructionBuffer[0];
            fread(instructionBuffer, 1, 1, binaryFile);
            rz = instructionBuffer[0];
            cpu.registers[rx] = cpu.registers[ry] / cpu.registers[rz];
            // printf("R%d = %d", rx, cpu.registers[rx]);
            cpu.stats[4]+=1;
            cpu.stats[6]+=1;
            break;

        case 0x5C:
            // printf(" - Div 2");
            fread(instructionBuffer, 1, 1, binaryFile);
            rx = instructionBuffer[0];
            fread(instructionBuffer, 1, 1, binaryFile);
            ry = instructionBuffer[0];

            fread(instructionBuffer, 1, 1, binaryFile);
            first_byte = instructionBuffer[0];
            second_byte = first_byte << 8;
            fread(instructionBuffer, 1, 1, binaryFile);
            second_byte += instructionBuffer[0];
            imm_value1 = second_byte;

            cpu.registers[rx] = cpu.registers[ry] / imm_value1;
            // printf("R%d = %d", rx, cpu.registers[rx]);
            cpu.stats[4]+=1;
            cpu.stats[7]+=1;
            break;
        
        case 0x9C:
            // printf(" - Div 3");
            fread(instructionBuffer, 1, 1, binaryFile);
            rx = instructionBuffer[0];

            fread(instructionBuffer, 1, 1, binaryFile);
            first_byte = instructionBuffer[0];
            second_byte = first_byte << 8;
            fread(instructionBuffer, 1, 1, binaryFile);
            second_byte += instructionBuffer[0];
            imm_value1 = second_byte;

            fread(instructionBuffer, 1, 1, binaryFile);
            first_byte = instructionBuffer[0];
            second_byte = first_byte << 8;
            fread(instructionBuffer, 1, 1, binaryFile);
            second_byte += instructionBuffer[0];
            imm_value2 = second_byte;

            cpu.registers[rx] = imm_value1 / imm_value2;
            // printf("R%d = %d", rx, cpu.registers[rx]);
            cpu.stats[4]+=1;
            cpu.stats[8]+=1;
            break;

        case 0x00:
            // printf(" - Ret");
            cpu.stats[5]+=1;
            cpu.stats[6]+=1;
            flag = 0;
            break;
        
        default:
            break;
        }
        
        iteration-=1;
    }

    // Close the file when done
    fclose(binaryFile);

    return 0;
}

int main(int argc, char const *argv[])
{
	// CPU_t cpu;
	// Step1: initialization registers in the CPU, as well as other essential variables
	// initialize registers
    for (int i = 0; i < NUM_REGISTERS; ++i) {
        cpu.registers[i] = 0;
    }

	// initialize stats
    for (int i = 0; i < CPU_COUNTERS; ++i) {
        cpu.stats[i] = 0;
    }

    // printf("%d\n", argc);
    // printf("%s\n", argv[0]);
    // printf("%s\n", argv[1]);

    readFile(argv[1]);

    printf("\n------ Registers ------\n");
	print_registers(cpu.registers);
	print_statistics(cpu.stats);

	// Step2: read bits from the text area of memory

    // Step3: decode bits into instruction

    // Step4: execute the instruction

    // continue until the last instruction is executed or a Ret instruction is met, print the output, register info and the statistics required
    printf("\n");
}

/**
 * @brief print the statistics of the instructions and CPU cycle
 * @param stats 
 * Note : You are NOT supposed to edit this function
 */
void print_statistics(int stats[]) {
    printf("\n------ CPU Stats ------\n");

    printf("Number of Set instructions: %d\n", stats[0]);
    printf("Number of Add instructions: %d\n", stats[1]);
    printf("Number of Sub instructions: %d\n", stats[2]);
    printf("Number of Mul instructions: %d\n", stats[3]);
    printf("Number of Div instructions: %d\n", stats[4]);
	printf("Number of LD instructions: %d\n", stats[5]);
    printf("Number of SD instructions: %d\n", stats[6]);
    printf("Number of BEZ instructions: %d\n", stats[7]);
    printf("Number of BGTZ instructions: %d\n", stats[8]);
    printf("Number of BLTZ instructions: %d\n", stats[9]);
	printf("Number of RET instructions: %d\n", stats[10]);

    printf("Number of 3Bytes instructions: %d\n", stats[11]);
    printf("Number of 4Bytes instructions: %d\n", stats[12]);
    printf("Number of 5Bytes instructions: %d\n", stats[13]);
    printf("Number of 6Bytes instructions: %d\n", stats[14]);

    printf("Total Number of instructions: %d\n", stats[15]);
    printf("Total execution time (Total number of cycles): %d\n", stats[16]);
}

/**
 * @brief print register vector
 * @param registers 
 *  Note : You are NOT supposed to edit this function
 */
void print_registers(int* registers) {
    for (int i = 0; i < NUM_REGISTERS; ++i) {
        printf("[R%d]:%d ", i, registers[i]);
    }
    printf("\n");
}


//  gcc cpu.c -o cpu
//  ./cpu

// make
// ./sim mem1.in