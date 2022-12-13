#include <lcd_mmr.h>

void lcd_ini(void){
	LCD_DDR|=DATA | (1<<RS) | (1<<E);
	
	
	_delay_ms(40);
	RS0;
	write(3);
	_delay_ms(5);
	write(3);
	_delay_us(150);
	write(3);
	_delay_us(50);
	write(2);
	_delay_us(50);
	
	
	send_byte(40,0);
	// DL 0/1 -4bit/8bit
	// N 0/1 -1/2
	// F 0/1 -5x7/5x11
	_delay_us(50);

	send_byte(12,0);// DISPLAY SWITCH 00001_D_C_B
	// D 0/1 - off/on display
	// C 0/1 - off/on cursor
	// B 0/1 - off/on blink
	
	_delay_us(50);
	
	send_byte(1,0);//
	_delay_ms(2);
	
	send_byte(6,0);// INPUT SET 000001_ID_S
	// ID 0/1
	// S 0/1 shift
	_delay_us(50);
	
	lcd_str("count=");
	lcd_pos(1,0);
	lcd_str("By M. Martynenko");
}

void write(uint8_t n){
	n<<=4;	E1;
	LCD_PORT&=~DATA;
	LCD_PORT|=n;
	asm("nop");
	E0;
}

void send_byte(uint8_t byte, uint8_t tip){
	if(tip) RS1;
	else RS0;
	write(byte>>4);
	write(byte);
}

void lcd_str(char* str){
	uint8_t n=0;
	while(str[n])
	{
		send_byte(str[n],1);
		n++;
	}
}

void lcd_pos(uint8_t line, uint8_t pos){
	uint8_t adress=(line*0x40+pos)|0x80;
	send_byte(adress,0);
	_delay_us(50);
}

void lcd_num(uint8_t num, uint8_t line, uint8_t pos) {
	char buf[4];
	
	utoa(num, buf, 10);
	lcd_pos(line, pos);
	lcd_str("   ");
	lcd_pos(line, pos);
	lcd_str(buf);
}