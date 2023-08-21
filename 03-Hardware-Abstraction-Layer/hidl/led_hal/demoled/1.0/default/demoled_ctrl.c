#define LOG_TAG "Demoled"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <log/log.h>

#include "demoled_ctrl.h"

#define LED_PATH "/sys/devices/platform/demo_led/demo_led"

int get_led_status(struct demo_led_ctrl self)
{
	char stat[2];
	FILE *fstream;
	char *cmd;

	cmd = (char*)malloc(strlen(self.demoled_path) + 6);
	sprintf(cmd, "cat %s", self.demoled_path);

	fstream = popen(cmd, "r");
	if (fstream == NULL) {
		ALOGE("popen: failed\n");
		return -1;
	}
	free(cmd);
	if (fread(stat, 1, sizeof(stat), fstream) == 0) {
		ALOGE("fread: failed\n");
		pclose(fstream);
		return -1;
	}
	pclose(fstream);
	return atoi(stat);
}

void set_demo_led(struct demo_led_ctrl self, int value)
{
	FILE *fp;

	ALOGI("set_demo_led is called\n");
	fp = fopen(self.demoled_path, "w+");
	if (fp == NULL) {
		ALOGE("fopen failed\n");
		return;
	}
	if (fprintf(fp, "%d", value) < 0) {
		ALOGE("fprintf failed\n");
		fclose(fp);
		return;
	}
	fclose(fp);
}

struct demo_led_ctrl demo_led_init()
{
	struct demo_led_ctrl self;
	self.demoled_path = LED_PATH;
	self.get_led_status = demo_get_led_status;
	self.turn_on_led = demo_turn_on_led;
	self.turn_off_led = demo_turn_off_led;
	return self;
}

void demo_led_cleanup(struct demo_led_ctrl *self)
{
	self->demoled_path = NULL;
	self->get_led_status = NULL;
	self->turn_on_led = NULL;
	self->turn_off_led = NULL;
}

int demo_get_led_status(struct demo_led_ctrl self)
{
	return get_led_status(self);
}

void demo_turn_on_led(struct demo_led_ctrl self)
{
	int on = 1;
	ALOGI("demo_turn_on_led is called\n");
	set_demo_led(self, on);
}

void demo_turn_off_led(struct demo_led_ctrl self)
{
	int off = 0;
	set_demo_led(self, off);
}
