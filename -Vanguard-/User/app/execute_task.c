#include "execute_task.h"
#include "can_device.h"
#include "uart_device.h"
#include "cmsis_os.h"
#include "calibrate.h"
#include "pid.h"
#include "sys.h"

#define LED_R_ON   write_led_io(LED_R, LED_ON);
#define LED_R_OFF  write_led_io(LED_R, LED_OFF);

//uint8_t test_key_value;
extern uint8_t test_servo;

//uint16_t servo_angle = 1000;





void execute_task(const void* argu)
{
   test_moto_init();
	
   while(1)
  {
		
    test_moto_control();		
		
		if(rc.sw2 == 3)
			{
		   test_servo=1;
			}
  
    osDelay(5);
  }
}
