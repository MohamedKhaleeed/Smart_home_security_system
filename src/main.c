/*
 * main.c
 *
 *  Created on: Mar 12, 2022
 *      Author: hamed
 */
#include "motor.h"
#include "PWM.h"
#include <avr/io.h>
#include <util/delay.h>
#include "types_macros.h"
#include "BLUETOOTH.h"
#include "lm35_sensor.h"
#include "ADC.h"
#include"timer.h"

    uint8 LED1=0;
    uint8 LED2=0;
    uint8 LED3=0;
    uint8 ALL=0;
    uint8 x=0;


 int main()
{   uint8 Password[5];
    uint8 cp;
    uint8 k=3;
    uint8 confirm=1;
    uint8 Access=1;


	SET_BIT(SREG,7);// set the global interrupt flag because of the timers
	char Data_in;
    UART_init(9600);


	CLEAR_BIT(DDRA,3);// make the pin of the sensor as input

	SET_BIT(DDRA,0);// active the led pin
		CLEAR_BIT(PORTA,0);
	SET_BIT(DDRA,1);// active the led pin
	    CLEAR_BIT(PORTA,1);
	SET_BIT(DDRA,2);// active the led pin
	    CLEAR_BIT(PORTA,2);
	SET_BIT(DDRA,4);// active the led pin
	    CLEAR_BIT(PORTA,4);
	    Dc_voidInit();   //intalization  for the motor
	    ADC_init(); //intalization  for the sensor
	    label:
        confirm=1;
        UART_SendString("\r\n Create Password: ");
        for(int i=0;i<5;i++){
                Password[i] = UART_recieveByte();
                UART_SendString("*");
        }
        UART_SendString("\r\n");

        UART_SendString("Confirm Password: ");
        for(int i=0; i<5;i++) {
            cp = UART_recieveByte();
            UART_SendString("*");
            if(cp!=Password[i]) confirm=0;
        }
        UART_SendString("\r\n");

        if(!confirm) {UART_SendString("Not matched  \r\n");  goto label;}
        UART_SendString("Password created   \r\n");
        label1:
        Access=1;

        UART_SendString("Enter Password: ");
       for(int i=0;i<5;i++){
                cp = UART_recieveByte();
                UART_SendString("*");
            if(cp!=Password[i]) Access=0;
        }
       UART_SendString("\r\n");
        if (!Access){
                     UART_SendString("Wrong Password 7raamy   \r\n");
        k--;
        if(k==0){
            UART_SendString("POLICE CALLING 122  \r\n");

            k=3;
            SET_BIT(PORTA,0);
            SET_BIT(PORTA,1);
            SET_BIT(PORTA,2);
			SET_BIT(PORTA,4);

            _delay_ms(6000);
			CLEAR_BIT(PORTA,4);

            if (LED1==0) {CLEAR_BIT(PORTA,0);}
            if (LED2==0) {CLEAR_BIT(PORTA,1);}
            if (LED3==0) {CLEAR_BIT(PORTA,2);} }
        goto label1;}
	    UART_SendString("                       Welcome "); // send a string for the mobile
	    UART_SendString("\r\n");

	    UART_SendString("To ");
	    UART_SendString("control ");
	    UART_SendString("led ");
	    UART_SendString("1");
	    UART_SendString(" just press ");
	    UART_SendString("1");
	    UART_SendString("\r\n");


	    UART_SendString("To ");
	    UART_SendString("control ");
	    UART_SendString("led ");
	    UART_SendString("2");
	    UART_SendString(" just press ");
	    UART_SendString("2");
	    UART_SendString("\r\n");

	    UART_SendString("To ");
	    UART_SendString("control ");
	    UART_SendString("led ");
	    UART_SendString("3");
	    UART_SendString(" just press ");
	    UART_SendString("3");
	    UART_SendString("\r\n");


	    UART_SendString("To ");
	    UART_SendString("control ");
	    UART_SendString("buzzer ");
	    UART_SendString("  just press  ");
	    UART_SendString("4");
	    UART_SendString("\r\n");


	    UART_SendString("To ");
	    UART_SendString("open");
	    UART_SendString(" door");
	    UART_SendString(" just press ");
	    UART_SendString("5");
	    UART_SendString("\r\n");

	    UART_SendString("To ");
	    UART_SendString("stop");
	    UART_SendString(" door");
	    UART_SendString(" just press ");
	    UART_SendString("6");
	    UART_SendString("\r\n");


	    UART_SendString("To ");
	    UART_SendString("close");
	    UART_SendString(" door");
	    UART_SendString(" just press ");
	    UART_SendString("7");
	    UART_SendString("\r\n");

	    UART_SendString("To ");
	    UART_SendString("check temperature");
	    UART_SendString(" just press ");
	    UART_SendString("8");

	    UART_SendString("\r\n");

	    UART_SendString("To ");
	    UART_SendString("logout just press");
	    UART_SendString(" just press ");
	    UART_SendString("9");
	    UART_SendString("\r\n");

	    //some strings for instructions
	    Timer_ConfigType Timer_config = {TIMER1,COMPARE,F_CPU_1024,0,100};
	        	/* passing pointer to this struct to initialization function of Timer */
	        Timer_init(&Timer_config);
	    while(1)
	    {
	    	Data_in = UART_recieveByte();  //bluetooth input in a char
	    				if (Data_in == '1')
	    				{
	    					TOGGLE_BIT(PORTA,0);
	    					if(LED1==0)
	    				    {
	    					    UART_SendString("led ");
    						    UART_SendString("1 ");
	    					    UART_SendString("on\r\n");
	    						 }
	    					else
   						     {
	    					    UART_SendString("led ");
	    					     UART_SendString("1 ");
		    					    UART_SendString("off\r\n");
   						     }
	    					LED1=!LED1;
	    				}

						else if (Data_in == '2')
						{
						   TOGGLE_BIT(PORTA,1);
						   if(LED2==0)
							 {
								 UART_SendString("led ");
								 UART_SendString("2 ");
		    					    UART_SendString("on\r\n");
   						 }
	    					else
								 {
								 UART_SendString("led ");
								 UART_SendString("2 ");
		    					    UART_SendString("off\r\n");
								 }
							LED2=!LED2;
	    				}
	    		      else if(Data_in == '3')
	    				{
	    		    	    TOGGLE_BIT(PORTA,2);
	    					if(LED3==0)
								 {
									 UART_SendString("led ");
									 UART_SendString("3 ");
			    					    UART_SendString("on\r\n");
								 }
	    			        else
								 {
								 UART_SendString("led ");
								 UART_SendString("3 ");
		    					   UART_SendString("off\r\n");
								 }
	    					LED3=!LED3;
	    				}

	    				else if (Data_in == '4')
	    				{
//	    					TOGGLE_BIT(PORTA,0);
//	    					TOGGLE_BIT(PORTA,1);
//	    					TOGGLE_BIT(PORTA,2);
	    					TOGGLE_BIT(PORTA,4);
	    					if(ALL==0)
	    						UART_SendString("ALL  on \r\n");
	    					else
	    						UART_SendString("ALL  off \r\n");
	    					ALL=!ALL;
	    				}
	    				else if(Data_in == '5')
	  				    {   UART_SendString("Opening");
	  				        UART_SendString(" door");
	  				        UART_SendString("\r\n");
	    					Rotate(CW,100);
	       				}
	    				else if(Data_in == '6')
	  				    {   UART_SendString("Stopping");
  				            UART_SendString(" door");
  				            UART_SendString("\r\n");
	    					Rotate(OFF,0);
	       				}
	    				else if(Data_in == '7')
	  				    {   UART_SendString("Closing");
  				            UART_SendString(" door");
  				            UART_SendString("\r\n");
	    					Rotate(CCW,100);
	       				}
	    				else if(Data_in == '8')
	  				    {
	  				        uint8 temp=LM35_readtemp();
	  				        if( temp>= 20 && temp<25 )
	  				        	{
	  				        	UART_SendString("Temp is more than ");
	  				            UART_SendString("20");
	  				            UART_SendString("\r\n");
	  				        	}
	  				        else if( temp>= 25 && temp<30 )
  				        	    {
  				             	UART_SendString("Temp is more than ");
  				                UART_SendString("25");
  				                UART_SendString("\r\n");
  				        	    }
	  				        else if( temp>= 30 && temp<35 )
  				              	{
  				             	UART_SendString("Temp is more than ");
  				                UART_SendString("30");
  				                UART_SendString("\r\n");
  				             	}
	  				        else if( temp>= 35 && temp<40 )
				              	{
				             	UART_SendString("Temp is more than ");
				                UART_SendString("40");
				                UART_SendString("\r\n");
				             	}
	       			      	}
	       				else if(Data_in == '9') {
                         //   UART_SendString("Are u sure \r\n   press y to say yes and n to say no \r\n");
                            char q=UART_recieveByte();
                            if(q=='y')
                               {UART_SendString("Logged out \r\n"); goto label1;
                               }
                            else if(q=='n')
                            	UART_SendString("enjoy your stay <3 \r\n");
	       				     }
	       				else if(Data_in == 'h') {
                            UART_SendString("FAN ON HIGH  \r\n ");
	    					Rotate(CW,100);

	       				}
	       				else if(Data_in == 'm') {
                            UART_SendString("FAN ON mid  \r\n ");
	    					Rotate(CW,50);

	       				}
	       				else if(Data_in == 'l') {
                            UART_SendString("FAN ON low  \r\n ");
	    					Rotate(CW,25);

	       				}
	       				else if(Data_in == 'a') {
                            UART_SendString("FAN ON auto  \r\n ");
                            x=1;

	       				}
	       				else if(Data_in == 'o') {
                            UART_SendString("FAN OFF auto  \r\n ");
                            x=0;
	    					Rotate(OFF,0);


	       				}

	    }
}
