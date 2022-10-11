/*
 * main.c
 *
 *  Created on: Mar 12, 2022
 *      Author: hp
 */
#include "motor.h"
#include "PWM.h"
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdbool.h>
#include "types_macros.h"
#include "BLUETOOTH.h"
#include "lm35_sensor.h"
#include "ADC.h"
#include"timer.h"



//int main()
//{   SET_BIT(DDRA,0);// active the led pin
//		CLEAR_BIT(PORTA,0);
//	SET_BIT(DDRA,1);// active the led pin
//	    CLEAR_BIT(PORTA,1);
//	SET_BIT(DDRA,3);// active the led pin
//        CLEAR_BIT(PORTA,3);
//	char Data_in;
//	UART_init(9600);
//	 while(1)
//
//	    {
//		    char medo='x';
//	    	UART_TxChar(medo);
//			Data_in = UART_recieveByte();
//			if (Data_in == 'r')
//			{   UART_sendByte(medo);
//				TOGGLE_BIT(PORTA,0);
//			}
//
//			else if (Data_in == 'g')
//			{
//				TOGGLE_BIT(PORTA,1);
//			}
//			else if(Data_in == 'b')
//			{
//				TOGGLE_BIT(PORTA,3);
//			}
//
//			else if (Data_in == 'a')
//			{
//				TOGGLE_BIT(PORTA,0);
//				TOGGLE_BIT(PORTA,1);
//				TOGGLE_BIT(PORTA,3);
//			}
//
//	    }
//	}


 int main()
{   char Password[5];
    char cp;
    int k=2;
    bool confirm=true;
    bool Access=true;
    uint8 LED1=0;
    uint8 LED2=0;
    uint8 LED3=0;
    uint8 ALL=0;

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

	    Dc_voidInit();   //intalization  for the motor
	    ADC_init(); //intalization  for the sensor
	    label:
        confirm=true;
        UART_SendString("Create Password:  \r\n");
        for(int i=0;i<5;i++){
                Password[i] = UART_recieveByte();
        }
        UART_SendString("Confirm Password:  \r\n");
        for(int i=0; i<5;i++) {
            cp = UART_recieveByte();
            if(cp!=Password[i]) confirm=false;
        }
        if(!confirm) {UART_SendString("Not matched  \r\n");  goto label;}
        UART_SendString("Password created successfully  \r\n");
        label1:
        Access=true;
        UART_SendString("Enter Password:  \r\n");
       for(int i=0;i<5;i++){
                cp = UART_recieveByte();
            if(cp!=Password[i]) Access=false;
        }
        if (!Access){UART_SendString("Wrong Password remaining times: %d \r\n",k);
        k--;
        if(k==0){
            k=2;
            SET_BIT(PORTA,0);
            SET_BIT(PORTA,1);
            SET_BIT(PORTA,2);
            _delay_ms(60000);
            if (LED1==0) {CLEAR_BIT(PORTA,0);}
            if (LED2==0) {CLEAR_BIT(PORTA,1);}
            if (LED3==0) {CLEAR_BIT(PORTA,2);} }
        goto label1;}
	    UART_SendString("                       Welcome \r\n"); // send a string for the mobile
	    UART_SendString("To open or close led 1 just press 1  \r\n");
	    UART_SendString("To open or close led 2 just press 2  \r\n");
	    UART_SendString("To open or close led 3 just press 3  \r\n");
	    UART_SendString("To toggle all LEDs just press 4  \r\n");
	    UART_SendString("To open the door just press 5  \r\n");
	    UART_SendString("To stop the door just press 6  \r\n");
	    UART_SendString("To close the door just press 7  \r\n");
	    UART_SendString("To check the temperature  just press 8  \r\n");
	    UART_SendString("To logout the system  just press 8  \r\n");
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
	    						UART_SendString("LED 1 on \r\n");
	    					else
	    						UART_SendString("LED 1 off \r\n");
	    					LED1=!LED1;
	    				}

	    				else if (Data_in == '2')
	    				{
	    					TOGGLE_BIT(PORTA,1);
	    					if(LED2==0)
	    						UART_SendString("LED 2 on \r\n");
	    					else
	    						UART_SendString("LED 2 off \r\n");
	    					LED2=!LED2;
	    				}
	    				else if(Data_in == '3')
	    				{  	TOGGLE_BIT(PORTA,2);
	    					if(LED3==0)
	    						UART_SendString("LED 3 on \r\n");
	    					else
	    						UART_SendString("LED 3 off \r\n");
	    					LED3=!LED3;
	    				}

	    				else if (Data_in == '4')
	    				{
	    					TOGGLE_BIT(PORTA,0);
	    					TOGGLE_BIT(PORTA,1);
	    					TOGGLE_BIT(PORTA,2);
	    					if(ALL==0)
	    						UART_SendString("ALL Leds on \r\n");
	    					else
	    						UART_SendString("ALL Leds off \r\n");
	    					ALL=!ALL;
	    				}
	    				else if(Data_in == '5')
	  				    {   UART_SendString("Opening door \r\n");
	    					Rotate(CW,100);
	       				}
	    				else if(Data_in == '6')
	  				    {   UART_SendString("Stop door \r\n");
	    					Rotate(OFF,50);
	       				}
	    				else if(Data_in == '7')
	  				    {   UART_SendString("Close door \r\n");
	    					Rotate(CCW,100);
	       				}
	    				else if(Data_in == '8')
	  				    {
	  				        uint8 temp=LM35_readtemp();
	  				        if( temp>= 20 && temp<25 )
	  				        	UART_SendString("Temp is more than 20  \r\n ");
	  				        else if( temp>= 25 && temp<30 )
	  				        	UART_SendString("Temp is more than 25  \r\n");
	  				        else if( temp>= 15 && temp<20 )
	  				        	UART_SendString("Temp is more than 15 \r\n ");
	       				}
	       				else if(Data_in == '9') {
                            UART_SendString("Logout successfully  \r\n ");
                            goto label1;
	       				}
	    }
}
//	// some strings to the lcd .
//	uint8 in[16] = "ENTER PASSWORD.";
//	uint8 con[11] = "CONFIRMED.";
//	uint8 wor[10] = "WRONG.";
//	uint8 stl[16] = " ATTEMPTS LEFT.";
//	uint8 fir[11] = "ENTER NEW ";
//	uint8 sec[15] = "PLEASE CONFIRM";
//	uint8 it[3] = "IT";
//	uint8 is[4] = "IS ";
//	uint8 thir[10] = "UNMATCHED";
//	uint8 th[16] = "THEFT ATTEMPTED";
//	uint8 tem[16] = "THE TEMPERATURE";
//	uint8 o[5] = "'C";
//	uint8 wel[9] = "PASSWORD:";
//
//	// num1 array to get the password into it
//	uint8 num1[5] = { 5,5,5,5,5 };
//	// num2 array to compare it with num1 to confirm the password
//	uint8 num2[5] ;
//
//	Timer_ConfigType timer2 = {TIMER2 , NORMAL , F_CPU_1024_timer2 , 0 , 0 };// timer2 to open the door when the password is correct
//	Timer_ConfigType timer0 = {TIMER0 , NORMAL , F_CPU_1024 , 0 , 0 };// timer1 to set the alarms for the thieves
//
//	SET_BIT(DDRA,7);// make the leds of the high temperature as output
//	SET_BIT(DDRA,6);
//	SET_BIT(DDRA,5);
//
//	uint8 i = 0;
//	uint8 flag1 = 0;
//	uint8 flag2 = 0;
//	uint8 trick = 0;
//	uint8 temp = 0;
//	uint8 r = 0;
//	UART_sendByte(LM35_readtemp());
//	while(1){
//		UART_SendString("HIGH TEMP");
//        UART_SendString("TEMP IS: ");
//	}
//}

//	if(LM35_readtemp() >= 30)// if the temp exceeds 30
//
//		{Rotate(CW,50);
//		while(LM35_readtemp() >= 30){
//			TOGGLE_BIT(PORTA,0);//light up
//			SET_BIT(PORTA,1);
//			SET_BIT(PORTA,5);
//		}}
//	else
//	{      Rotate(OFF,50);
//				CLEAR_BIT(PORTA,0);//light up
//				CLEAR_BIT(PORTA,1);
//				CLEAR_BIT(PORTA,5);
//			}
//}}
//	while(1)
//	{  if(LM35_readtemp() >= 30)// if the temp exceeds 30
//				{while(1)
//					{SET_BIT(PORTA,0);//light up
//					SET_BIT(PORTA,1);
//					SET_BIT(PORTA,5);
//				}}
//			else
//			{
//						CLEAR_BIT(PORTA,0);//light up
//						CLEAR_BIT(PORTA,1);
//						CLEAR_BIT(PORTA,5);
//			}
//	}
//}
//
//
////       if(LM35_readtemp()>=30)
//       { Rotate(CW,50);
//    	   UART_SendString("HIGH TEMP");
//           UART_SendString("TEMP IS: ");
//		while(LM35_readtemp()>30) 		// check high temperature
//		{   UART_sendByte(LM35_readtemp());
//			SET_BIT(PORTA,0);
//			TOGGLE_BIT(PORTA,1);
//			TOGGLE_BIT(PORTA,2);
//			_delay_ms(500);
//		}
//       }
//
//       x=UART_recieveByte();
//        if(x==0)
//                     {
//        	Rotate(CW,50);
//                     }
//       else if(x==1)
//                     {
//    	   Rotate(CCW,50);
//                     }
//       else if(x==2)
//       {
//		    TOGGLE_BIT(PORTA,0);
//
//       }
//       else if(x==3)
//              {
//       		    TOGGLE_BIT(PORTA,0);
//
//              }
//       else if(x==4)
//              {
//       		    TOGGLE_BIT(PORTA,0);
//
//              }
//	}
//}

//		// check high temperature
//
////			UART_SendString(fir);
////			UART_SendString(wel);
////
////			for(uint8 i=0 ; i<5 ; i++) // for loop of five to insert five digits.
////			{
////				check();// check high temperature
////				num1[i] = UART_recieveByte();
////				if(i==0)
////					LCD_SendCommand(DISPLAY_CLEAR);// first clear the lcd.
////				else
////					LCD_SendCommand(CURSOR_SHIFT_RIGHT);// after that every time after inserting a new digit shift right.
////				_delay_ms(20);
////				LCD_PrintCharacter(num1[i] + 48);// display the number.
////				_delay_ms(500);
////			}
////			// after that show the next string
////			LCD_SendCommand(DISPLAY_CLEAR);
////			_delay_ms(20);
////			LCD_PrintString(sec);
////			_delay_ms(20);
////			LCD_SendCommand(NEXT_LINE);
////			_delay_ms(20);
////			LCD_PrintString(it);
////			_delay_ms(20);
////
////			for(i=0 ; i<5 ; i++)// in this for loop we repeat the previous loop but for num2 to confirm
////			{
////				check();// check high temperature
////				num2[i] = get_Value();// get the value of the keypad
////				if(i==0)
////					LCD_SendCommand(DISPLAY_CLEAR);// clear the lcd at first
////				else
////					LCD_SendCommand(CURSOR_SHIFT_RIGHT);// shift after each insertion
////				_delay_ms(20);
////				LCD_PrintCharacter(num2[i] + 48);// display the number on the lcd
////				_delay_ms(500);
////			}
////
////			for(i=0 ; i<5 ; i++)// here we compare num1 and num2
////			{
////				if(num1[i] != num2[i])
////				{
////					check();
////					LCD_SendCommand(DISPLAY_CLEAR);
////					_delay_ms(20);
////					LCD_PrintString(thir);// the string unmatched.
////					_delay_ms(1000);
////					flag1 = 0;
////					break;
////				}
////				else
////					flag1 = 1;
////			}
////
////			if(flag1 == 1)// if num1 == num2 break from while
////				break;
////		}
////		/****************************************************************************************************************************************************************************************/
////		LCD_SendCommand(DISPLAY_CLEAR);
////		_delay_ms(20);
////		LCD_PrintString(con);// string confirmed
////		_delay_ms(2000);
////		/******************************************   AFTER THE CONFIRMATION OF THE PW NOW WE ASK FOR THE RIGHT PW    ***************************************************************************/
////		while(1)
////		{
////			check();// check high temperature
////			LCD_SendCommand(DISPLAY_CLEAR);
////			_delay_ms(20);
////			LCD_PrintString(in);// the string enter password
////			_delay_ms(20);
////			// the r for loop to dedicate the wrong pw times
////			for(r=0 ; r<3 ;r++)
////			{
////				check();
////				//the i for loop to receive the input password from the user
////				for(i=0 ; i<5 ; i++)
////				{
////					check();
////					num2[i] = get_Value();
////					if(i==0)
////						LCD_SendCommand(DISPLAY_CLEAR);
////					else
////						LCD_SendCommand(CURSOR_SHIFT_RIGHT);
////					_delay_ms(20);
////					LCD_PrintCharacter(num2[i] + 48);
////					_delay_ms(500);
////				}
////				//the next for loop to compare the input with the right password
////				for(i=0 ; i<5 ; i++)
////				{
////					if(num1[i] != num2[i])
////					{
////						LCD_SendCommand(DISPLAY_CLEAR);
////						_delay_ms(20);
////						LCD_PrintString(wor);
////						_delay_ms(1000);
////						LCD_SendCommand(DISPLAY_CLEAR);
////						_delay_ms(20);
////						LCD_PrintCharacter((2-r) + 48 );
////						LCD_SendCommand(CURSOR_SHIFT_RIGHT);
////						LCD_PrintString(stl);
////						flag2 = 0;// if there is any miss match clear the flag and break the loop
////						break;
////					}
////					else if(i==4)
////					{
////						flag2 = 1; // if the counter reach 4 set the flag and break the loop.
////						break;
////					}
////				}
////				/***************************************************************************************************************************/
////				if(flag2 == 1)// as soon as the flag is one break the bigger loop
////				{break;}
////				else if(flag2==0 && r==2)// if the flag is clear and the counter of the bigger loop is 2 break the loop
////				{break;}
////			}
////			if(flag2 == 0)// if wrong password
////			{
////				check();
////				Timer_init(&timer0);
////				LCD_SendCommand(DISPLAY_CLEAR);
////				_delay_ms(20);
////				LCD_PrintString(th);// the string theft attempted
////				while(trick<23)//hang the system for 30 seconds , 23 is an approximate number to reach 30 seconds in real time.
////				{// this delay is used to keep the string "theft attempted" displayed on the lcd
////					_delay_ms(1000);
////					trick++;
////				}
////				trick = 0;
////			}
////			else if(flag2 == 1)// if true password
////			{
////				temp = LM35_readtemp();// read the temperature
////				Timer_init(&timer2);// init the timer to open the door
////				LCD_SendCommand(DISPLAY_CLEAR);
////				_delay_ms(20);
////				LCD_PrintString(tem);// the string the temperature
////				_delay_ms(20);
////				LCD_SendCommand(NEXT_LINE);//go to the next line
////				_delay_ms(20);
////				LCD_PrintString(is);// print is
////				_delay_ms(20);
////				LCD_intgerToString(temp);// print the degree
////				_delay_ms(20);
////				LCD_PrintString(o);// print 'C
////				while(trick<5)//hang the system for 5 seconds till the door is closed.
////				{// this delay is used to keep the string of the temperature displayed on the lcd
////					_delay_ms(1000);
////					trick++;
////				}
////				trick = 0;
////			}
////		}
////
////
////
////	}
////}
//}
//}
