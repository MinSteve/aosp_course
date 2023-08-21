#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define LED_PATH "/sys/devices/platform/demo_led/demo_led"

int get_led_status()
{
	char stat[2];
	FILE *fstream;
	char *cmd;

	cmd = (char*)malloc(strlen(LED_PATH) + 6);
	sprintf(cmd, "cat %s", LED_PATH);

	fstream = popen(cmd, "r");
	if (fstream == NULL) {
		perror("popen: failed\n");
		return -1;
	}
	free(cmd);
	if (fread(stat, 1, sizeof(stat), fstream) == 0) {
		perror("fread: failed\n");
		return -1;
	}
	return atoi(stat);
}

int main () {
	FILE * fp;
	int off = 0;
	int on = 1;
	char val[2];


	fp = fopen (LED_PATH, "w+");
	//Get LED status
	fread(val, 1, sizeof(val), fp);
	printf("LED status: %s\n", val);
	sleep(1);
	//Turn On LED
	printf("Turn LED on\n");
	fprintf(fp, "%d", on);
	//Get LED status
	fread(val, 1, sizeof(val), fp);
	printf("LED status: %s\n", val);
	printf("LED status use shell cmd: %d\n", get_led_status());
	sleep(1);
	//Turn off LED
	printf("Turn LED off\n");
	fprintf(fp, "%d", off);
	//Get LED status
	fgets(val, sizeof(val), fp);
	printf("LED status: %s\n", val);
		    
	fclose(fp);
	return(0);
}

