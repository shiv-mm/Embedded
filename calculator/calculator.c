/*
 * File:   calculator.c
 * Author: Obiano Miracol
 *
 * Created on March 12, 2019, 1:32 PM
 */
#include <xlcd.h>
#include "config.c"
#include <delays.h>

#define ROWA LATBbits.LATB0
#define ROWB LATBbits.LATB1
#define ROWC LATBbits.LATB2
#define ROWD LATBbits.LATB3
#define COL1 PORTBbits.RB4
#define COL2 PORTBbits.RB5
#define COL3 PORTBbits.RB6
#define COL4 PORTBbits.RB7

/*
 * 
 */

void init_keypad(void);
char button_press_scan(void);
char keypad_scanner(void);
int char2num(char ch);
void result(int numb);

int j=0;

void init_XLCD(void);          //initialize LCD
void DelayFor18TCY(void);        //Delay for 18 instruction cycle
void DelayPORXLCD(void);         //Delay for 15ms
void DelayXLCD(void);            //Delay for 5ms
    
    
int main(void) {
    char key='n';           // Key char for keeping record of pressed key
    int leftnum,rightnum;
    char opp = '+';
    
    init_XLCD();
    while(BusyXLCD());
    SetDDRamAddr(0x00);
    putrsXLCD("GETTING    YOUR");
    SetDDRamAddr(0x40);
    putrsXLCD("CALCULATOR READY");
    for(int i=0;i<20;i++)__delay_ms(100);       //Delay for 2 seconds
    WriteCmdXLCD(0x01);
    init_keypad();
    SetDDRamAddr(0x00);
    while(1){
        START: WriteCmdXLCD(0x0E);
        key=button_press_scan();
        putcXLCD(key);
        leftnum = char2num(key);
        
        if(key == 'C'){
            WriteCmdXLCD(0x01);
            SetDDRamAddr(0x00);
            goto START;
        }
        if(leftnum == 0 || leftnum == 1 || leftnum == 2 || leftnum == 3 || leftnum == 4 || leftnum == 5 ||
                leftnum == 6 || leftnum == 7 || leftnum == 8 || leftnum == 9)
        {
            key = button_press_scan();
            putcXLCD(key);
            opp = key;
            
            if(key == '/' || key == 'X' || key == '+' || key == '-'){
                key = button_press_scan();
                putcXLCD(key);
                rightnum = char2num(key);
                if(rightnum == 0 || rightnum == 1 || rightnum == 2 || rightnum == 3 || rightnum == 4 || rightnum == 5 ||
                        rightnum == 6 || rightnum == 7 || rightnum == 8 || rightnum == 9){
                    key = button_press_scan();
                    putcXLCD(key);
                    if(key == '='){
                        switch(opp){
                            case '/': result(leftnum/rightnum);break;
                            case 'X': result(leftnum*rightnum);break;
                            case '+': result(leftnum+rightnum);break;
                            case '-': result(leftnum-rightnum);break;
                        }
                    }
                }
            }
        }
    }
}
void init_XLCD(void){
        OpenXLCD( FOUR_BIT & LINES_5X7 );
        while(BusyXLCD());
        WriteCmdXLCD(0x06);
        WriteCmdXLCD(0x0C);
    }
    void DelayFor18TCY(void){
        Delay10TCYx(20);
    }
    //Delay for 15ms
    void DelayPORXLCD(void){
        Delay1KTCYx(30);
    }
    //Delay for 5ms
    void DelayXLCD(void){
        Delay1KTCYx(10);
    }
    void init_keypad(void){
    LATB = 0x00;		// Set PORTB pin values zero
    PORTB=0x00;
	TRISB = 0xF0;		// PORTB4 to PORTB7 pins input, PORTB0 to PORTB3 pins output
	INTCON2bits.NOT_RBPU=0;		// Enable weak internal pull up on input pins
}
char keypad_scanner(void){
    ROWA=0; ROWB=1; ROWC=1; ROWD=1;
    if (COL1 == 0) { __delay_ms(100); while (COL1==0); return '7'; }
	if (COL2 == 0) { __delay_ms(100); while (COL2==0); return '8'; }
	if (COL3 == 0) { __delay_ms(100); while (COL3==0); return '9'; }
    if (COL4 == 0) { __delay_ms(100); while (COL4==0); return '/'; }
    
    ROWA=1; ROWB=0; ROWC=1; ROWD=1;
    if (COL1 == 0) { __delay_ms(100); while (COL1==0); return '4'; }
	if (COL2 == 0) { __delay_ms(100); while (COL2==0); return '5'; }
	if (COL3 == 0) { __delay_ms(100); while (COL3==0); return '6'; }
    if (COL4 == 0) { __delay_ms(100); while (COL4==0); return 'X'; }
    
    ROWA=1; ROWB=1; ROWC=0; ROWD=1;
    if (COL1 == 0) { __delay_ms(100); while (COL1==0); return '1'; }
	if (COL2 == 0) { __delay_ms(100); while (COL2==0); return '2'; }
	if (COL3 == 0) { __delay_ms(100); while (COL3==0); return '3'; }
    if (COL4 == 0) { __delay_ms(100); while (COL4==0); return '-'; }
    
    ROWA=1; ROWB=1; ROWC=1; ROWD=0;
    if (COL1 == 0) { __delay_ms(100); while (COL1==0); return 'C'; }
	if (COL2 == 0) { __delay_ms(100); while (COL2==0); return '0'; }
	if (COL3 == 0) { __delay_ms(100); while (COL3==0); return '='; }
    if (COL4 == 0) { __delay_ms(100); while (COL4==0); return '+'; }
    
    return 'n';
}
char button_press_scan(void){
    char key='n';
    while(key=='n'){
        key=keypad_scanner();
    }
    return key;
}
int char2num(char ch)         //convert char to int
{
	int num = 0;

	switch(ch)
	{
		case '0': num = 0; break;
		case '1': num = 1; break;
		case '2': num = 2; break;
		case '3': num = 3; break;
		case '4': num = 4; break;
		case '5': num = 5; break;
		case '6': num = 6; break;
		case '7': num = 7; break;
		case '8': num = 8; break;
		case '9': num = 9; break;
		//case 'C': WriteCmdXLCD(0x01);SetDDRamAddr(0x05); break;
    }
    return num;
}

void result(int numb)            //displays number on LCD
{	
	unsigned char UnitDigit  = 0;  //It will contain unit digit of numb
	unsigned char TenthDigit = 0;  //It will contain 10th position digit of numb

	if(numb<0)
	{
		numb = -1*numb;          // Make number positive
		putcXLCD('-');	 // Display a negative sign on LCD
	}

	TenthDigit = (numb/10);	                  // Findout Tenth Digit

	if( TenthDigit != 0)	                  // If it is zero, then don't display
		putcXLCD(TenthDigit+0x30);	  // Make Char of TenthDigit and then display it on LCD

	UnitDigit = numb - TenthDigit*10;

	putcXLCD(UnitDigit+0x30);	  // Make Char of UnitDigit and then display it on LCD
}