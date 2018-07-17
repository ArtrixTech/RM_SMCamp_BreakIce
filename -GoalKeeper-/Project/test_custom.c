#include "execute_task.h"
#include "can_device.h"
#include "uart_device.h"
#include "pid.h"
#include "sys.h"
#include <stdio.h>
#include <stdlib.h>


int16_t test_moto_speed = 0;
int16_t test_moto_current[4];
uint8_t test_servo;
uint8_t key1;

// Hardware definations
float CH_MAX = 660.0;

// Chanel mapping ratio
float MAPPING_RATIO = 19.0;

// Hit ball part
float hit_ball_threshold = 0.4;
float hit_axis_ratio = 0;

// Angle target-reaching judgement
int angle_judge_max_error=15;

// Global target angle
int hit_axis_target_angle = 0;
int hit_axis_current_angle=0;

int push_axis_target_angle = 0;
int push_axis_current_angle=0;

void motor_operations()
{
	
    // Hit axis -> ID 1
	// Push axis -> ID 2
	
	int hit_axis_current=pid_calc(&pid_hit_axis, hit_axis_current_angle, hit_axis_target_angle);
	int push_axis_current=pid_calc(&pid_push_axis, push_axis_current_angle, push_axis_target_angle);

	test_moto_current[0] = hit_axis_current; 
	test_moto_current[1] = push_axis_current;

	send_chassis_moto_current(test_moto_current);
}

void test_moto_control(void) // Main control part
{
	
	hit_axis_current_angle=moto_chassis[0].total_angle;
	push_axis_current_angle=moto_chassis[1].total_angle;
	
	//Target angle - calculated by the controller
	hit_axis_target_angle = -rc.ch3 / CH_MAX * MAPPING_RATIO * 140.0;
	push_axis_target_angle = -rc.ch2 / CH_MAX * MAPPING_RATIO * 250.0;

	motor_operations();
}

void test_moto_init(void)
{

	pid_init(&pid_hit_axis, 7000, 10, 2.4,1000000, 50);
   	pid_init(&pid_push_axis, 7000, 10, 2.4,1000000, 50);

}
