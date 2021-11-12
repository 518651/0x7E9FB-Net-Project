#include "Un-main.h"


struct WaotoCry
{
	int process_break_sendbox;
	
	char process_new_path;
}WaotoCry;



int main() {
	if (determine()!=1) {
		exit(1);
	}
	WaotoCry.process_new_path = new_process_path();
	add_double_data(WaotoCry.process_new_path);
	increase(WaotoCry.process_new_path);
}