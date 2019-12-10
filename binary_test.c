#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <endian.h>

void init(char *opcodes[]);
void executeInstruction (char *opcodes[], char instruction[], u_int64_t registers_value[], u_int8_t memory[256], u_int8_t stack[32], int *flag, int *PC, int *EP, 
						int register_delay[32], int *ex_delay, int *mem_delay);
int setUpEnvironment(FILE *file, char instructions[][33]);

//ADD
//reg_one: first register to add
//reg_two: second register to add
int add(int reg_one, int reg_two){
	return reg_one + reg_two;
}

//ADDI
//reg: register to add value to
//immediate: integer value to add to reg
int addi(int reg, int immediate){
	return reg + immediate;
}

int and(int register_one, int register_two){
	return register_one & register_two;
}

int andi(int reg, int immediate){
	return reg & immediate;
}

//B.cond
//cond: string representation of branch conditional
//returns 1: if conditional is true, 0: if conditional is false
int b_cond(int cond, int register_to_compare){
	if(cond == 7 || cond == 6 || cond == 0){
		if(register_to_compare == 0){
			return 1;
		} else {
			return 0;
		}
	} else if(cond == 1){
		if(register_to_compare != 0){
			return 1;
		} else {
			return 0;
		}
	} else if(cond == 5 || cond == 2 || cond == 10){
		if(register_to_compare >= 0){
			return 1;
		} else {
			return 0;
		}
	} else if(cond == 4 || cond == 3 || cond == 11){
		if(register_to_compare < 0){
			return 1;
		} else {
			return 0;
		}
	} else if(cond == 8 || cond == 12){
		if(register_to_compare > 0){
			return 1;
		} else {
			return 0;
		}
	} else if(cond == 9 || cond == 13){
		if(register_to_compare <= 0){
			return 1;
		} else {
			return 0;
		}
	} else {
		return -1;
	}
}

//CBNZ
//if register_to_compare does NOT equal 0 then the statement is true, else it's false
//HANDLE BRANCHING
int cbnz(int register_to_compare){
	if(register_to_compare != 0){
		return 1;
	}
	return 0;
}

//CBNZ
//if register_to_compare DOES equal 0 then the statement is true, else it's false
//HANDLE BRANCHING
int cbz(int register_to_compare){
	if(register_to_compare == 0){
		return 1;
	}
	return 0;
}

//prints all registers, main memory, and the stack
void dump(u_int64_t registers_value[], u_int8_t memory[256], u_int8_t stack[32]){
	printf("\nREGISTERS\n");
	for(int i = 0; i < 32; i++){
		printf("X%d: %d\n", i, registers_value[i]);
	}
	
	printf("\nSTACK\n");
	for(int i = 0; i < 100; i++){
		printf("%d: %d\n", i, stack[i]);
	}
	
	// printf("\nMEMORY\n");
	// for(int i = 0; i < 1000; i++){
		// printf("%d: %d\n", i, memory[i]);
	// }
}

int eor(int register_one, int register_two){
	return register_one ^ register_two;
}

int eori(int register_one, int immediate){
	return register_one ^ immediate;
}

//returns the value at the offset index in the integer array
//CHANGE TO CHAR??
int ldur(int register_value, int offset){
	return register_value + (offset / 8);
}

//multiplies the registers value by 2^exponent
int lsl(int register_to_multiply, int exponent){
	return register_to_multiply * pow(2, exponent);
}

//divides the registers value by 2^exponent
int lsr(int register_to_divide, int exponent){
	return register_to_divide / pow(2, exponent);
}

//multiplies the register value by the factor
int mul(int register_to_multiply, int factor){
	return register_to_multiply * factor;
}

int orr(int register_one, int register_two){
	return register_one | register_two;
}

int orri(int register_one, int immediate){
	return register_one | immediate;
}

/*
prints a blank line
*/
void prnl(){
	printf("\n");
}

/*
prints the register and the value within the register
*/
void prnt(int register_to_print, int register_value_to_print){
	char hexstring[15];
	sprintf(hexstring, "0x%015x", register_value_to_print); //converts int to hex value
	printf("X%d: %s (%d)", register_to_print, hexstring, register_value_to_print); //prints format from first assignment
}

int stur(int register_value, int offset){
	return register_value + (offset / 8);
} 

//subtracts register two from register one
int sub(int register_one, int register_two){
	return register_one - register_two;
}

//subtracts immediate from register
int subi(int reg, int immediate){
	return reg - immediate;
}

//divides factor from register_to_divide
int udiv(unsigned int register_to_divide, unsigned int factor){
	return register_to_divide / factor;
}

int convertBinaryToDecimal(char *n)
{
    int decimalNumber = 0, exponent = 0;
	
    for(int i = (strlen(n) - 1); i >= 0; i--){
		int x =  n[i] - '0';
        decimalNumber += x * pow(2, exponent);
		exponent++;
    }
    return decimalNumber;
}

void update_all_register_stages(int register_delay[32]){
	for(int i = 0; i < 32; i++){
		register_delay[i] -= 1;
	}
}

void update_register_stage(int register_num, int register_delay[32]){
	register_delay[register_num] = 3;
}

void check_register_stage(int register_num, int register_delay[32], int *ex_delay, int *mem_delay){
	if(register_delay[register_num] == 2){
		*mem_delay += 2;
	} else if (register_delay[register_num] == 1) {
		*ex_delay += 1;
	}
	register_delay[register_num] = 0;
}

int main(int argc, char *argv[]) {
	int programCounter = 0;
	int endProgram = 0;
	char instructions[1000][33];
	//struct stat fileStat;
	FILE *file;
	//stat(argv[1],&fileStat);
	//int size = fileStat.st_size / 4;
	file = fopen(argv[1], "rb");

	programCounter = setUpEnvironment(file, instructions);

	char *opcodes[37];
	//holds values of registers 0-31
	u_int64_t registers_value[32] = {};
	init(opcodes);
	u_int8_t memory[256] = {};
	u_int8_t stack[32] = {};
	int register_delay[32] = {};
	int ex_delay = 0, mem_delay = 0;
	int flag_register = 0;

	for(int i = 0; i < programCounter; i++){
		printf("Instruction: %s\n", instructions[i]);
		executeInstruction(opcodes, instructions[i], registers_value, memory, stack, &flag_register, &i, &endProgram, register_delay, 
							&ex_delay, &mem_delay);
		if(endProgram == 1){
			return 0;
		}
	}

	printf("Unpipelined cycles: %d\n", programCounter);
	printf("Pipelined cycles: %d\n", programCounter*5);
	printf("Number of data hazards in 5-stage pipeline: %d\n", ex_delay);
	printf("Number of control hazards in 5-stage pipeline: %d\n", mem_delay);
	// printf("Number of cylces to execute on 5-stage-pipelined implementation with bypassing: %d\n", numCycles);
    return 0;
}

int setUpEnvironment(FILE *file, char instructions[][33]){
	int i = 0;
	int charCount = 1;
	char instruction[33];
	int c;
	int f = 0;
	int j = 0;

	while(!feof(file)){
		fread(&instructions[f], 1, 32, file);
		f++;
	}

	while(1){
		if(instructions[j][0] == '\0'){
			break;
		}
		j++;
	}
	return j;
}


void executeInstruction (char *opcodes[], char instruction[], u_int64_t registers_value[], u_int8_t memory[256], u_int8_t stack[32], int *flag, int *PC, int *EP, 
						int register_delay[32], int *ex_delay, int *mem_delay){
	char temp_opcode[33], Rm[6], shamt[7], Rn[6], Rd[6], alu_immediate[13], dt_address[10], op[3], 
		Rt[6], br_address[27], cond_flag[5], cond_br_address[20], cond[5];
	int Rm_int = 0, shamt_int = 0, Rn_int = 0, Rd_int = 0, immediate_int = 0, dt_address_int = 0, 
		op_int = 0, Rt_int = 0, br_address_int = 0, cond_br_address_int = 0, cond_flag_int = 0;
	int i,j;
	memset(Rm, 0, sizeof(Rm));
	memset(temp_opcode, 0, sizeof(temp_opcode));
	
	for(i = 0; i < 33; i++){
		strncat(temp_opcode, instruction, i);

		for(j = 0; j < 37; j++){
			if(strcmp(temp_opcode, opcodes[j]) == 0){
				//SEPARATES THE COMMANDS INTO TYPES TO ASSIGN VALUES TO ARRAYS AS NECESSARY
				if(j == 0 || j == 2 || j == 10 || j == 11 || j == 13 || j == 18 || j == 19 || j == 20 || j == 21 || j == 23 || j == 24 || j == 25 || j == 26 || j == 31 || j == 34 || j == 35 || j == 36){ //R type
					memcpy(Rm, &instruction[11], 5);
					Rm[5] = '\0';
					Rm_int = convertBinaryToDecimal(Rm);
					check_register_stage(Rm_int, register_delay, ex_delay, mem_delay);
					
					memcpy(shamt, &instruction[16], 6);
					shamt[6] = '\0';
					shamt_int = convertBinaryToDecimal(shamt);
					
					memcpy(Rn, &instruction[22], 5);
					Rn[5] = '\0';
					Rn_int = convertBinaryToDecimal(Rn);
					check_register_stage(Rn_int, register_delay, ex_delay, mem_delay);
					
					memcpy(Rd, &instruction[27], 5);
					Rd[5] = '\0';
					Rd_int = convertBinaryToDecimal(Rd);
					check_register_stage(Rd_int, register_delay, ex_delay, mem_delay);
					update_register_stage(Rd_int, register_delay);
				} 
				else if(j == 1 || j == 3 || j == 12 || j == 22 || j == 32 || j == 33){ //I type
					memcpy(alu_immediate, &instruction[10], 12);
					alu_immediate[12] = '\0';
					immediate_int = convertBinaryToDecimal(alu_immediate);
					
					memcpy(Rn, &instruction[22], 5);
					Rn[5] = '\0';
					Rn_int = convertBinaryToDecimal(Rn);
					check_register_stage(Rn_int, register_delay, ex_delay, mem_delay);
					
					memcpy(Rd, &instruction[27], 5);
					Rd[5] = '\0';
					Rd_int = convertBinaryToDecimal(Rd);
					check_register_stage(Rd_int, register_delay, ex_delay, mem_delay);
					update_register_stage(Rd_int, register_delay);
				} 
				else if(j == 4 || j == 6 || j == 7) { //B type				
					memcpy(br_address, &instruction[6], 26);
					br_address[26] = '\0';
					br_address_int = convertBinaryToDecimal(br_address);
				} 
				else if(j == 5 || j == 8 || j == 9){ //CB type
					memcpy(cond_br_address, &instruction[8], 19);
					cond_br_address[19] = '\0';
					cond_br_address_int = convertBinaryToDecimal(cond_br_address);
					
					memcpy(Rt, &instruction[27], 5);
					Rt[5] = '\0';
					Rt_int = convertBinaryToDecimal(Rt);
					check_register_stage(Rt_int, register_delay, ex_delay, mem_delay);
				} else if(j == 14 || j == 15 || j == 16 || j == 17 || j == 27 || j == 28 || j == 29 || j == 30){ //D type
					memcpy(dt_address, &instruction[11], 9);
					dt_address[9] = '\0';
					dt_address_int = convertBinaryToDecimal(dt_address);
					
					memcpy(op, &instruction[20], 2);
					op[3] = '\0';
					op_int = convertBinaryToDecimal(op);
					
					memcpy(Rn, &instruction[22], 5);
					Rn[5] = '\0';
					Rn_int = convertBinaryToDecimal(Rn);
					check_register_stage(Rn_int, register_delay, ex_delay, mem_delay);
					
					memcpy(Rt, &instruction[27], 5);
					Rt[5] = '\0';
					Rt_int = convertBinaryToDecimal(Rt);
					check_register_stage(Rt_int, register_delay, ex_delay, mem_delay);
					update_register_stage(Rt_int, register_delay);
				}
				
				update_all_register_stages(register_delay);
				
				switch(j){
						case 0:
							registers_value[Rd_int] = add(registers_value[Rn_int], registers_value[Rm_int]);
							break;
						case 1:
							registers_value[Rd_int] = addi(registers_value[Rn_int], immediate_int);
							break;
						case 2:
							registers_value[Rd_int] = and(registers_value[Rn_int], registers_value[Rm_int]);
							break;
						case 3:
							registers_value[Rd_int] = andi(registers_value[Rn_int], immediate_int);
							break;
						case 4:
							*PC += br_address_int;
							break;
						case 5:
							//Rt_int == decimal form of cond
							b_cond(Rt_int, registers_value[*flag]);
							break;
						case 6:
							*PC += br_address_int;
							registers_value[30] = *PC + 4;
							break;
						case 7:
							*PC += br_address_int;
							break;
						case 8:
							if(cbnz(registers_value[Rt_int]) == 1){
								*PC += cond_br_address_int;
							}
							break;
						case 9:
							if(cbz(registers_value[Rt_int]) == 1){
								*PC += cond_br_address_int;
							}
							break;
						case 10:
							dump(registers_value, memory, stack);
							break;
						case 11:
							registers_value[Rd_int] = eor(registers_value[Rn_int], registers_value[Rm_int]);
							break;
						case 12:
							registers_value[Rd_int] = eori(registers_value[Rn_int], immediate_int);
							break;
						case 13:
							dump(registers_value, memory, stack);
							*EP = 1;
							break;
						case 14:
							if(Rt_int == 28 || Rt_int == 29){ //user references SP or FP so use the stack
								registers_value[Rt_int] = stack[ldur(dt_address_int, registers_value[Rn_int])];
							} else { //user main mem
								registers_value[Rt_int] = memory[ldur(dt_address_int, registers_value[Rn_int])];
							}
							break;
						case 18:
							registers_value[Rd_int] = lsl(registers_value[Rn_int], shamt_int);
							break;
						case 19:
							registers_value[Rd_int] = lsr(registers_value[Rn_int], shamt_int);
							break;
						case 20:
							registers_value[Rd_int] = mul(registers_value[Rn_int], registers_value[Rm_int]);
							break;
						case 21:
							registers_value[Rd_int] = orr(registers_value[Rn_int], registers_value[Rm_int]);
							break;
						case 22:
							registers_value[Rd_int] = orri(registers_value[Rn_int], immediate_int);
							break;
						case 23:
							prnl();
							break;
						case 24:
							prnt(Rd_int, registers_value[Rd_int]);
							break;
						case 27:
							if(Rt_int == 28 || Rt_int == 29){ //user references SP or FP so use the stack
								stack[stur(dt_address_int, registers_value[Rn_int])] = registers_value[Rt_int];
							} else { //user main mem
								memory[stur(dt_address_int, registers_value[Rn_int])] = registers_value[Rt_int];
							}
							break;
						case 31:
							registers_value[Rd_int] = sub(registers_value[Rn_int], registers_value[Rm_int]);
							break;
						case 32:
							registers_value[Rd_int] = subi(registers_value[Rn_int], immediate_int);
							break;
						case 33:
							registers_value[Rd_int] = subi(registers_value[Rn_int], immediate_int);
							*flag = Rd_int;
							break;
						case 34:
							registers_value[Rd_int] = sub(registers_value[Rn_int], registers_value[Rm_int]);
							*flag = Rd_int;
							break;
						case 35:
							registers_value[Rd_int] = udiv(registers_value[Rn_int], registers_value[Rm_int]);
							break;
					}
				return;
			}
		}
		memset(temp_opcode, 0, sizeof(temp_opcode));
	}
}

void init(char *opcodes[]){
	opcodes[0] = "10001011000";		//ADD //R
	opcodes[1] = "1001000100";		//ADDI //I
	opcodes[2] = "10001010000";		//AND //R
	opcodes[3] = "1001001000";		//ANDI //I
	opcodes[4] = "000101";			//B //B
	opcodes[5] = "01010100";		//B.cond //B
	opcodes[6] = "100101";			//BL //B
	opcodes[7] = "11010110000";		//BR //B
	opcodes[8] = "10110101";		//CBNZ //CB
	opcodes[9] = "10110100";		//CBZ //CB
	opcodes[10] = "11111111110";	//DUMP //R
	opcodes[11] = "11001010000";	//EOR //R
	opcodes[12] = "1101001000";		//EROI //I
	opcodes[13] = "11111111111";	//HALT //R
	opcodes[14] = "11111000010";	//LDUR //D
	opcodes[15] = "00111000010";	//LDURB //D
	opcodes[16] = "01111000010";	//LDURH //D
	opcodes[17] = "10111000100";	//LDURSW //D
	opcodes[18] = "11010011011";	//LSL //R
	opcodes[19] = "11010011010";	//LSR //R
	opcodes[20] = "10011011000";	//MUL //R
	opcodes[21] = "10101010000";	//ORR //R
	opcodes[22] = "1011001000";		//ORRI //I
	opcodes[23] = "11111111100";	//PRNL //R
	opcodes[24] = "1111111101";		//PRNT //R
	opcodes[25] = "10011010110";	//SDIV //R
	opcodes[26] = "10011011010";	//SMULH //R
	opcodes[27] = "11111000000";	//STUR //D
	opcodes[28] = "00111000000";	//STURB //D
	opcodes[29] = "01111000000";	//STURH //D
	opcodes[30] = "10111000000";	//STURW //D
	opcodes[31] = "11001011000";	//SUB //R
	opcodes[32] = "1101000100";		//SUBI //I
	opcodes[33] = "1111000100";		//SUBIS //I
	opcodes[34] = "11101011000";	//SUBS //R
	opcodes[35] = "10011010110";	//UDIV //R
	opcodes[36] = "10011011110"; 	//UMULH //R
}
