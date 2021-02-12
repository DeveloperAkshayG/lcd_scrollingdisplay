#include "lcd.h"		  //LCD header file


void LCD_Init(void)
{
	LCD_Command_Dir = 0xFF;  //intialise command port as output
	LCD_Data_Dir = 0xFF;	 //intialise data port as output	
	_delay_ms(20);			
	
	LCD_Command (0x38);		//initialize in 8-bit mode
	_delay_ms(1);
	LCD_Command (0x0C);		//display on cursor off
	_delay_ms(1);
	LCD_Command (0x06);		//autoincrement cursor
	_delay_ms(1);
	LCD_Command (0x01);		//clear screen
	_delay_ms(1);
	LCD_Command (0x80);     //cursor at starting point
	_delay_ms(1);
}

void LCD_Clear(void)		/* LCD function to clear display */
{
	LCD_Command (0x01);		/* clear display */
	_delay_ms(1);
	LCD_Command (0x80);		/* cursor at home position */
	_delay_ms(1);
}

void LCD_Command(unsigned char cmnd)	/* LCD function to send command */ 
{
	LCD_Data_Port= cmnd;
	LCD_Command_Port &= ~(1<<RS);	/* RS=0 command reg. */
	_delay_ms(1);
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 Write operation */
	_delay_ms(1);
	LCD_Command_Port |= (1<<EN);	/* Enable pulse */
	_delay_ms(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(1);
}

void LCD_Char (unsigned char char_data)	/* LCD data write function */
{
	LCD_Data_Port= char_data;
	LCD_Command_Port |= (1<<RS);	/* RS=1 Data reg. */
	_delay_ms(1);
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 write operation */
	_delay_ms(1);
	LCD_Command_Port |= (1<<EN);	/* Enable Pulse */
	_delay_ms(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(1);
}

void LCD_String (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}

void LCD_String_xy (char row, char pos, char *str)/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	LCD_String(str);		/* Call LCD string function */
}

int main()
{
	int shift,i;
	LCD_Init();	
//	LCD_String_XY("NETELINDIA");/* Write string on 1st line of LCD*/

	shift = 15;	/* Number of time shifts count=15 */
	while(1)
	{
		for(i=0;i<shift;i++)
		{
			LCD_String_xy (0,1,"NETEL INDIA");
			LCD_String_xy (1,1,"WELCOMES YOU");
			LCD_Command(0x1c);/* shift entire display right */
			_delay_ms(50);
		}			
	//	shift=15;/* number of time shifts 30 */
			
		/*for(i=0;i<shift;i++)
		{
			LCD_String_xy (1,1,"WELCOMES YOU");
			LCD_Command(0x18);// shift entire display left 
			_delay_ms(100);
		}*/
	}
	
	return 0;
}