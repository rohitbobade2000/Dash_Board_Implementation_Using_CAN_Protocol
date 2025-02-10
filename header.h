typedef unsigned int u32;
typedef int s32;
typedef unsigned short int u16;
typedef short int s16;
typedef unsigned char u8;
typedef char s8;

typedef struct CAM2_msg
{
 	u32 ID;
	u8 RTR;
	u8 DLC;
	u32 BYTEA;
	u32 BYTEB;
} CAN2_ST;

#define sw1 ((IOPIN0>>15)&1)
 
#define TEMPERATURE_ID 0x22
#define SPEED_ID 0x33

#define HEADLIGHT_ID 0xDF
#define HEADLIGHT_ON 0XAA
#define HEADLIGHT_OFF 0XBB

//#define INDICATOR_ID_0N 0xDF
//#define INDICATOR_ID_0FF 0xDF  
#define INDICATOR_ID 0xAF
#define INDICATOR_RIGHT_ON 0xEE
#define INDICATOR_RIGHT_OFF 0xFF

#define INDICATOR_LEFT_ON 0xCC
#define INDICATOR_LEFT_OFF 0xDD


void lcd_data(s8);
void lcd_init(void);
void lcd_cmd(s8);
void lcd_string(s8 *);
void lcd_cgram(void);

void delay_ms(u32);

void can2_init(void);
void EN_CAN2_INTERRUPT(void);

