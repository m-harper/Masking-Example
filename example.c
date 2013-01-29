#include <stdio.h> 

/*
Sample Solution-1 for Lab-1, Problem-4
Add your own INPUT/OUTPUT code to test it.
*/

unsigned int input;  
unsigned int output;  
enum inputs {DOS, DSBF, ER, DC, KIC, DLC, BP, CM};
//enum inputs {CM, BP, DLC, KIC, DC, ER, DSBF, DOS};
enum outputs {BELL, DLA, BA};

//For input interface implementation
inline void read_inputs_from_ip_if(){
	const int NUM_SENSORS = 8;
	FILE *infile = fopen("sensors.txt", "r");
	int buffer[NUM_SENSORS];
	
	void write_inputs(enum inputs where, int value) {
		if (value)
			input = input | (value << where);
		else 
			input = input & ~(1 << where);
	}
	
	if (infile != NULL) {
		int i;
		for(i = 0; i < NUM_SENSORS; i++) {
			buffer[i] = fgetc(infile) - 48;
			write_inputs(i, buffer[i]);
		}
	}
	
	fclose(infile);
}

//For output interface implementation
inline void write_output_to_op_if(){
	int read_out(enum outputs where) {
		return output & (1 << where);
	}
	int read_inputs(enum inputs where) {
		return input & (1 << where);
	} 
	
	printf("BELL = %d\n", read_out(BELL));
	printf("DLA = %d\n", read_out(DLA));
	printf("BA = %d\n", read_out(BA));
	printf("\n");
}

//The code segment which implements the decision logic
inline void control_action(){

	//Reset output
	output = 0;
	
	//Requirement 1, 2, 3
	printf("input&0xf:%d\n",input & 0xf);

	switch (input & 0xf)
	{
		case 5:
		case 7:
		case 13:
			output =  0x1;
			break;
	}

	//Requirement 4
	switch (input & 0x31)
	{
		case 32:
		case 49:
		case 51:
		case 53:
		case 55:
		case 57:
		case 59:
		case 61:
		case 63:
			output = output | 0x2;
			break;
	}

	//Requirement 5
	if ((input & 0xc0) == 0xc0) 
			output = output | 0x4;
}


//The main program
int main(int argc, char *argv[])
{
	
	/*The main control loop which keeps the system alive and responsive for ever, 
	until the system is powered off */
	for (; ; )
	{
		read_inputs_from_ip_if();
		control_action();
		write_output_to_op_if();

	}
	
	return 0;
}
