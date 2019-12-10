#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <endian.h>

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

//??
int and(int register_one, int register_two){
	return register_one & register_two;
}

//??
int andi(int reg, int immediate){
	return reg & immediate;
}

//B??

//B.cond
//cond: string representation of branch conditional
//returns 1: if conditional is true, 0: if conditional is false
int b_cond(char *cond, int register_to_compare){
	if(!strcmp(cond, "VC") || !strcmp(cond, "VS") || !strcmp(cond, "EQ")){
		if(register_to_compare == 0){
			return 1;
		} else {
			return 0;
		}
	} else if(!strcmp(cond, "NE")){
		if(register_to_compare != 0){
			return 1;
		} else {
			return 0;
		}
	} else if(!strcmp(cond, "PL") || !strcmp(cond, "HS") || !strcmp(cond, "GE")){
		if(register_to_compare >= 0){
			return 1;
		} else {
			return 0;
		}
	} else if(!strcmp(cond, "MI") || !strcmp(cond, "LO") || !strcmp(cond, "LT")){
		if(register_to_compare < 0){
			return 1;
		} else {
			return 0;
		}
	} else if(!strcmp(cond, "HI") || !strcmp(cond, "GT")){
		if(register_to_compare > 0){
			return 1;
		} else {
			return 0;
		}
	} else if(!strcmp(cond, "LS") || !strcmp(cond, "LE")){
		if(register_to_compare <= 0){
			return 1;
		} else {
			return 0;
		}
	} else {
		return -1;
	}
}

//BL??

//BR??

//CBNZ
//if register_to_compare does NOT equal 0 then the statement is true, else it's false
//HANDLE BRANCHING
int cbnz(int register_to_compare){
	if(register_to_compare != 0){
		return 1;
	}
	return 0;
}

//CBZ
//if register_to_compare DOES equal 0 then the statement is true, else it's false
//HANDLE BRANCHING
int cbz(int register_to_compare){
	if(register_to_compare == 0){
		return 1;
	}
	return 0;
}

void dump(){
	
}

int eor(int register_one, int register_two){
	return register_one ^ register_two;
}

int eori(int register_one, int immediate){
	return register_one ^ immediate;
}

void halt(){
	dump();
}

//returns the value at the offset index in the integer array
//CHANGE TO CHAR??
int ldur(int *register_to_pull_from, int offset){
	return register_to_pull_from[offset / 8];
}

//ldurb??

//ldurh??

//ldursw??

//multiplies the registers value by 2^exponent
double lsl(int register_to_multiply, int exponent){
	return register_to_multiply * pow(2, exponent);
}

//divides the registers value by 2^exponent
double lsr(int register_to_divide, double exponent){
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

//prnl??

void prnt(int register_to_print, int register_value_to_print){
	char hexstring[15];
	sprintf(hexstring, "0x%015x", register_value_to_print); //converts int to hex value
	printf("X%d: %s (%d)", register_to_print, hexstring, register_value_to_print); //prints format from first assignment
}

//RETURN INTEGER??
double sdiv(int register_to_divide, int factor){
	return register_to_divide / factor;
}

//smulh??

int stur(int *register_to_pull_from, int offset){
	return register_to_pull_from[offset / 8];
} 

//sturh??

//sturw??

//subtracts register two from register one
int sub(int register_one, int register_two){
	return register_one - register_two;
}

//subtracts immediate from register
int subi(int reg, int immediate){
	return reg - immediate;
}

//subis
//cond: string representation of branch conditional
//returns 1: if conditional is true, 0: if conditional is false
int subis(char *cond, int register_to_compare){
	if(!strcmp(cond, "VC") || !strcmp(cond, "VS") || !strcmp(cond, "EQ")){
		if(register_to_compare == 0){
			return 1;
		} else {
			return 0;
		}
	} else if(!strcmp(cond, "NE")){
		if(register_to_compare != 0){
			return 1;
		} else {
			return 0;
		}
	} else if(!strcmp(cond, "PL") || !strcmp(cond, "HS") || !strcmp(cond, "GE")){
		if(register_to_compare >= 0){
			return 1;
		} else {
			return 0;
		}
	} else if(!strcmp(cond, "MI") || !strcmp(cond, "LO") || !strcmp(cond, "LT")){
		if(register_to_compare < 0){
			return 1;
		} else {
			return 0;
		}
	} else if(!strcmp(cond, "HI") || !strcmp(cond, "GT")){
		if(register_to_compare > 0){
			return 1;
		} else {
			return 0;
		}
	} else if(!strcmp(cond, "LS") || !strcmp(cond, "LE")){
		if(register_to_compare <= 0){
			return 1;
		} else {
			return 0;
		}
	} else {
		return -1;
	}
}

//subs??

//divides factor from register_to_divide
//RETURN DOUBLE OR CONVERT TO INT??
double udiv(u_int64_t register_to_divide, u_int64_t factor){
	return register_to_divide / factor;
}

//umulh??

// char printable_char(uint8_t c)
// {
  // return isprint(c) ? c : '.';
// }

// void hexdump(FILE *f, int8_t *start, size_t size)
// {
  // size_t i;

  // for (i = 0; i < size - (size % 16); i += 16) {
    // fprintf(f,
            // "%08x "
            // " %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx "
            // " %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx "
            // " |%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c|\n",
            // (int32_t) i,
            // start[i +  0], start[i +  1], start[i +  2], start[i +  3],
            // start[i +  4], start[i +  5], start[i +  6], start[i +  7],
            // start[i +  8], start[i +  9], start[i + 10], start[i + 11],
            // start[i + 12], start[i + 13], start[i + 14], start[i + 15],
            // printable_char(start[i +  0]), printable_char(start[i +  1]),
            // printable_char(start[i +  2]), printable_char(start[i +  3]),
            // printable_char(start[i +  4]), printable_char(start[i +  5]),
            // printable_char(start[i +  6]), printable_char(start[i +  7]),
            // printable_char(start[i +  8]), printable_char(start[i +  9]),
            // printable_char(start[i + 10]), printable_char(start[i + 11]),
            // printable_char(start[i + 12]), printable_char(start[i + 13]),
            // printable_char(start[i + 14]), printable_char(start[i + 15]));
  // }
  // fprintf(f, "%08x\n", (int32_t) size);
// }

void init(char *opcodes[], char *conditionals[]){
	opcodes[0] = "10001011000";		//ADD
	opcodes[1] = "1001000100";		//ADDI
	opcodes[2] = "10001010000";		//AND
	opcodes[3] = "1001001000";		//ANDI
	opcodes[4] = "000101";			//B
	opcodes[5] = "01010100";		//B.cond
	opcodes[6] = "100101";			//BL
	opcodes[7] = "11010110000";		//BR
	opcodes[8] = "10110101";		//CBNZ
	opcodes[9] = "10110100";		//CBZ
	opcodes[10] = "11111111110";	//DUMP
	opcodes[11] = "11001010000";	//EOR
	opcodes[12] = "1101001000";		//EROI
	opcodes[13] = "11111111111";	//HALT
	opcodes[14] = "11111000010";	//LDUR
	opcodes[15] = "00111000010";	//LDURB
	opcodes[16] = "01111000010";	//LDURH
	opcodes[17] = "10111000100";	//LDURSW
	opcodes[18] = "11010011011";	//LSL
	opcodes[19] = "11010011010";	//LSR
	opcodes[20] = "10011011000";	//MUL
	opcodes[21] = "10101010000";	//ORR
	opcodes[22] = "1011001000";		//ORRI
	opcodes[23] = "11111111100";	//PRNL
	opcodes[24] = "1111111101";		//PRNT
	opcodes[25] = "10011010110";	//SDIV
	opcodes[26] = "10011011010";	//SMULH
	opcodes[27] = "11111000000";	//STUR
	opcodes[28] = "00111000000";	//STURB
	opcodes[29] = "01111000000";	//STURH
	opcodes[30] = "10111000000";	//STURW
	opcodes[31] = "11001011000";	//SUB
	opcodes[32] = "1101000100";		//SUBI
	opcodes[33] = "1111000100";		//SUBIS
	opcodes[34] = "11101011000";	//SUBS
	opcodes[35] = "10011010110";	//UDIV
	opcodes[36] = "10011011110"; 	//UMULH
	
	conditionals[0] = "?";			//EQ
	conditionals[1] = "?";			//NE
	conditionals[2] = "?";			//HS
	conditionals[3] = "?";			//LO
	conditionals[4] = "?";			//MI
	conditionals[5] = "?";			//PL
	conditionals[6] = "?";			//VS
	conditionals[7] = "?";			//VC	
	conditionals[8] = "?";			//HI
	conditionals[9] = "?";			//LS	
	conditionals[10] = "?";			//GE	
	conditionals[11] = "?";			//LT
	conditionals[12] = "?";			//GT
	conditionals[13] = "?";			//LE
}

int convertBinaryToDecimal(char *n)
{
    int decimalNumber = 0, exponent = 0;
	
    for(int i = (strlen(n) - 1); i > 0; i--){
		int x =  n[i] - '0';
        decimalNumber += x * pow(2, exponent);
		exponent++;
    }
    return decimalNumber;
}

void readFile(char *opcodes[], int registers_value[]){
	// char *chadDestination = "C:/Users/morro/Documents/College/COMS_321/Input.txt";
	char *chadUDestination = "/my.files.iastate.edu/Users/morrowc/Documents/Input.txt";
	//LOOP THROUGH STREAM OF BINARY VALUES AND FIGURE OUT WHAT COMMAND IT IS, THEN GET PARAMETERS. PASS THESE PARAMETERS INTO THE RESPECTIVE FUNCTIONS
	FILE *file = fopen(chadUDestination, "r");
	//holds the string binary values of the current command
	char *tempOpcode = "";
	int c;
	size_t n = 0;
	int notFound = 1;
	int done = 0;
	
	//if we can't find the file then close it and exit the program
	if(file != NULL){
		//allocated memory for storing the input characters
		tempOpcode = malloc(1000);
		
		//loop through the input file character by character
		while((c = fgetc(file)) != EOF && !done){
			printf("%c\n", (char) c);
			// tempOpcode[n++] = (char) c;
			// //loop through every opcode after concatenating the last value we added
			// for(int i = 0; i < 37 && notFound; i++){
				// //if tempOpcode is equal to any opcode command then perform an action
				// if(!strcmp(tempOpcode, opcodes[i])){
					// notFound = 1;
					// char *Rm = malloc(1000 * sizeof(char));
					// char *shamt = malloc(1000 * sizeof(char));
					// char *Rn = malloc(1000 * sizeof(char));
					// char *Rd = malloc(1000 * sizeof(char));
					// char *immediate = malloc(1000 * sizeof(char));
					// int Rm_int = 0, shamt_int = 0, Rn_int = 0, Rd_int = 0, immediate_int = 0;
					
					// // printf("%s\n", "It's working!");
					// switch(i){
						// case 0: //ADD
							// for(int i = 0; i < 5; i++){
								// Rm[i] = fgetc(file);
							// }
							// // printf("%s\n", Rm);
							// Rm_int = convertBinaryToDecimal(Rm);
							// // printf("%d\n", Rm_int);
							
							// for(int j = 0; j < 6; j++){
								// shamt[j] = fgetc(file);
							// }
							// // printf("%s\n", shamt);
							// shamt_int = convertBinaryToDecimal(shamt);
							// // printf("%d\n", shamt_int);
							
							// for(int k = 0; k < 5; k++){
								// Rn[k] = fgetc(file);
							// }
							// // printf("%s\n", Rn);
							// Rn_int = convertBinaryToDecimal(Rn);
							// // printf("%d\n", Rn_int);
							
							// for(int m = 0; m < 5; m++){
								// Rd[m] = fgetc(file);
							// }
							// // printf("%s\n", Rd);
							// Rd_int = convertBinaryToDecimal(Rd);
							// // printf("%d\n", Rd_int);
							
							// registers_value[Rd_int] = add(registers_value[Rn_int], registers_value[Rm_int]);
							// // printf("%d\n", registers_value[Rd_int]);
							// break;
						// case 1: //ADDI
							// for(int i = 0; i < 12; i++){
								// immediate[i] = fgetc(file);
							// }
							// // printf("%s\n", immediate);
							// immediate_int = convertBinaryToDecimal(immediate);
							// // printf("%d\n", immediate_int);
							
							// for(int j = 0; j < 5; j++){
								// Rn[j] = fgetc(file);
							// }
							// // printf("%s\n", Rn);
							// Rn_int = convertBinaryToDecimal(Rn);
							// // printf("%d\n", Rn_int);
							
							// for(int k = 0; k < 5; k++){
								// Rd[k] = fgetc(file);
							// }
							// // printf("%s\n", Rd);
							// Rd_int = convertBinaryToDecimal(Rd);
							// // printf("%d\n", Rd_int);
							
							// registers_value[Rd_int] = addi(registers_value[Rn_int], immediate_int);
							// break;
						// case 2:
							// for(int i = 0; i < 5; i++){
								// Rm[i] = fgetc(file);
							// }
							// // printf("%s\n", Rm);
							// Rm_int = convertBinaryToDecimal(Rm);
							// // printf("%d\n", Rm_int);
							
							// for(int j = 0; j < 6; j++){
								// shamt[j] = fgetc(file);
							// }
							// // printf("%s\n", shamt);
							// shamt_int = convertBinaryToDecimal(shamt);
							// // printf("%d\n", shamt_int);
							
							// for(int k = 0; k < 5; k++){
								// Rn[k] = fgetc(file);
							// }
							// // printf("%s\n", Rn);
							// Rn_int = convertBinaryToDecimal(Rn);
							// // printf("%d\n", Rn_int);
							
							// for(int m = 0; m < 5; m++){
								// Rd[m] = fgetc(file);
							// }
							// // printf("%s\n", Rd);
							// Rd_int = convertBinaryToDecimal(Rd);
							// // printf("%d\n", Rd_int);
							
							// registers_value[Rd_int] = and(registers_value[Rn_int], registers_value[Rm_int]);
							// // printf("%d\n", registers_value[Rd_int]);
							// break;
						// case 3:
							// for(int i = 0; i < 12; i++){
								// immediate[i] = fgetc(file);
							// }
							// // printf("%s\n", immediate);
							// immediate_int = convertBinaryToDecimal(immediate);
							// // printf("%d\n", immediate_int);
							
							// for(int j = 0; j < 5; j++){
								// Rn[j] = fgetc(file);
							// }
							// // printf("%s\n", Rn);
							// Rn_int = convertBinaryToDecimal(Rn);
							// // printf("%d\n", Rn_int);
							
							// for(int k = 0; k < 5; k++){
								// Rd[k] = fgetc(file);
							// }
							// // printf("%s\n", Rd);
							// Rd_int = convertBinaryToDecimal(Rd);
							// // printf("%d\n", Rd_int);
							
							// registers_value[Rd_int] = andi(registers_value[Rn_int], immediate_int);
							// break;
						// case 4:
						// break;
						// case 5:
						// break;
						// case 6:
						// break;
						// case 7:
						// break;
						// case 8:
						// break;
						// case 9:
						// break;
						// case 10: //DUMP
							// done = 1;
							// break;
						// case 11:
						// break;
						// case 12:
						// break;
						// case 13:
						// break;
						// case 14:
						// break;
						// case 15:
						// break;
						// case 16:
						// break;
						// case 17:
						// break;
						// case 18: //LSL //R type not I type??
						
							// registers_value[Rd_int] = lsl(registers_value[Rn_int], registers_value[Rm_int]);
							// break;
						// case 19: //LSR //R type not I type??
							// registers_value[Rd_int] = lsr(registers_value[Rn_int], registers_value[Rm_int]);
						// break;
						// case 20: //MUL //R type not I type??
						
							// registers_value[Rd_int] = mul(registers_value[Rn_int], registers_value[Rm_int]);
							// break;
						// case 21:
						// break;
						// case 22:
						// break;
						// case 23:
						// break;
						// case 24: //PRNT
							// //call print, don't know formatting
							// break;
						// case 25:
						// break;
						// case 26:
						// break;
						// case 27:
						// break;
						// case 28:
						// break;
						// case 29:
						// break;
						// case 30:
						// break;
						// case 31: //SUB
							// for(int i = 0; i < 5; i++){
								// Rm[i] = fgetc(file);
							// }
							// // printf("%s\n", Rm);
							// Rm_int = convertBinaryToDecimal(Rm);
							// // printf("%d\n", Rm_int);
							
							// for(int j = 0; j < 6; j++){
								// shamt[j] = fgetc(file);
							// }
							// // printf("%s\n", shamt);
							// shamt_int = convertBinaryToDecimal(shamt);
							// // printf("%d\n", shamt_int);
							
							// for(int k = 0; k < 5; k++){
								// Rn[k] = fgetc(file);
							// }
							// // printf("%s\n", Rn);
							// Rn_int = convertBinaryToDecimal(Rn);
							// // printf("%d\n", Rn_int);
							
							// for(int m = 0; m < 5; m++){
								// Rd[m] = fgetc(file);
							// }
							// // printf("%s\n", Rd);
							// Rd_int = convertBinaryToDecimal(Rd);
							// // printf("%d\n", Rd_int);
							
							// registers_value[Rd_int] = sub(registers_value[Rn_int], registers_value[Rm_int]);
							// // printf("%d\n", registers_value[Rd_int]);
							// break;
						// case 32: //SUBI
							// for(int i = 0; i < 12; i++){
								// immediate[i] = fgetc(file);
							// }
							// // printf("%s\n", immediate);
							// immediate_int = convertBinaryToDecimal(immediate);
							// // printf("%d\n", immediate_int);
							
							// for(int j = 0; j < 5; j++){
								// Rn[j] = fgetc(file);
							// }
							// // printf("%s\n", Rn);
							// Rn_int = convertBinaryToDecimal(Rn);
							// // printf("%d\n", Rn_int);
							
							// for(int k = 0; k < 5; k++){
								// Rd[k] = fgetc(file);
							// }
							// // printf("%s\n", Rd);
							// Rd_int = convertBinaryToDecimal(Rd);
							// // printf("%d\n", Rd_int);
							
							// registers_value[Rd_int] = subi(registers_value[Rn_int], immediate_int);
							// break;
						// case 33:
						// break;
						// case 34:
						// break;
						// case 35:
						// break;
						// case 36:
						// break;
						// default:
						// break;
					// }
					// // //Clear the array to restart the process on the next command
					// // tempOpcode = "";
				// }
			// }
		}
	} 
	// fclose(file);
}

int main(int argc, char *argv[]){
	char *opcodes[37];
	char *conditionals[14];
	//holds values of registers 0-31
	int registers_value[32] = {};
	//holds last computed register as the 'flagged' register for comparing on b.cond, CBZ and CBNZ calls
	int flagged_register = 0;
	
	init(opcodes, conditionals);
	
	readFile(opcodes, registers_value);
	printf("%d\n", registers_value[1]);
	
	return 0;
}
