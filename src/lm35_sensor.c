#include "lm35_sensor.h"
#include "ADC.h"
#include "BLUETOOTH.h"
#include "motor.h"
uint8 HT[20] = "HIGH TEMPRATURE";

/*********************************************************************************************************************************************************************/

uint8 LM35_readtemp(void)
{

	uint8 temp_value = 0;     // a temporary variable to save the temperature value
    uint16 adc_value = 0;     // a temporary variable to save the adc readings
    float tempo = 0;

	adc_value = ADC_readChannel(SENSOR_CHANNEL_ID);// take the value read by the ADC

	temp_value = (uint8)(((uint32)adc_value*SENSOR_MAX_TEMPERATURE*ADC_V_REF)/(MAX_VALUE_ADC_REP*SENSOR_MAX_VOLT_VALUE));

	tempo = adc_value / 256 ;// i noticed that one degree on the sensor make the adc read the value 256 so our needed temp is the adc_value over 256.

	// interpolation equation used to obtain the temperature via the ADC readings
	return tempo;
}

/*******************************************************************************************************************************************************************/
void check()// this function is to check the temperature at any time by using it many times at the main.
{
	if(LM35_readtemp() >= 30)// if the temp exceeds 30
	{
		UART_SendString("HIGH TEMP \r\n");
		SET_BIT(PORTA,0);//light up
		SET_BIT(PORTA,1);
		SET_BIT(PORTA,2);
		Rotate(CW,50);
		_delay_ms(5000);
		Rotate(OFF,50);

		while(LM35_readtemp() >= 30);

	}
}

