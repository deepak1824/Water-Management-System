	 

#include"BuildAuto.h"
  



#define buz	PORTCbits.RC2

#define motor PORTBbits.RB5
 
#define l1 PORTAbits.RA0
#define l2 PORTAbits.RA1
#define l3 PORTAbits.RA2

#define rs PORTEbits.RE1
#define en PORTEbits.RE0

#define data PORTD
void cmd_wrt(unsigned int m)
{

	
	data=m&0xF0;
	rs=0;
	en=1;
	Delay10KTCYx(10);
	en=0;
	
	data&=(0x0F);
	data=(m<<4)&0xF0;
	rs=0;
	en=1;
	Delay10KTCYx(10);
	en=0;
}
void data_wrt(unsigned char n)
{
	data=n&0xF0;
	rs=1;
	en=1;
	Delay10KTCYx(10);
	en=0;

	data&=0x0F;
	data=(n<<4)&0xF0;
	rs=1;
	en=1;
	Delay10KTCYx(10);
	en=0;

}






 void main()
  {
	unsigned char msgtype=0;
    unsigned int k,z=0; 
	unsigned char msgstatus1=0,msgstatus2=0,msgstatus3=0,t_sta=0,l_sta=0;
	 unsigned char m_status=0,m_status1=0;

unsigned char a[15]="  WATER MNGMNT ";
unsigned char b[15]="     SYSTEM    ";
unsigned char c[15]=" INSUFFNT WTR  ";
unsigned char d[15]="   MOTOR ON    ";
unsigned char e[15]="  SUFFCNT WTR  ";
unsigned char f[15]="   MOTOR OFF   ";
unsigned char g[15]="W1    W2    W3 ";
	 ADCON1=0x0F;
	 TRISA=0xFF; TRISB=0x00;  TRISC=0x00;TRISD=0x00; TRISE=0x00;
	 
	 	     buz=0;

	
cmd_wrt(0x28);
cmd_wrt(0x0C);
cmd_wrt(0x06);
cmd_wrt(0x01);
cmd_wrt(0x80);

	Delay10KTCYx(10);

	 
	  cmd_wrt(0x01);
	  for(k=0;k<15;k++)
			{
			data_wrt(a[k]);
			}
	  	  
	  cmd_wrt(0xc0);	
	  for(k=0;k<15;k++)
			{
			data_wrt(b[k]);
			}
	  

	
 start:
      

	Delay10KTCYx(200);Delay10KTCYx(200);Delay10KTCYx(200);Delay10KTCYx(200);
	  cmd_wrt(0x1);
	 for(k=0;k<15;k++)
			{
			data_wrt(g[k]);
			}
	  
   
while(1)
{	
	 	 Delay10KTCYx(200);	 Delay10KTCYx(200);

	cmd_wrt(0xc0);
	  if(l1 == 0)
	  {
	 data_wrt('1');
	  
	  }
	  else
	  {
	  data_wrt('0');
	    
	  }
	  
	  	

	  cmd_wrt(0xc6);
	  if(l2 == 0)
	  {
	  data_wrt('1');
	 
	  }
	  else
	  {
	  data_wrt('0');
	    
	  }
	  

	  	
	 cmd_wrt(0xcc);
	  if(l3 == 0)
	  {
	  data_wrt('1');
	 
	  }
	  else
	  {
	  data_wrt('0');

buz=1;

	 Delay10KTCYx(500);

    	   	
buz=0;
	    
	  }	

	if((l1 == 1)&&(l2 == 1)&&(l3==1))
    {
	 motor=1;
	 cmd_wrt(1);
	  for(k=0;k<15;k++)
			{
			data_wrt(c[k]);
			}
	 cmd_wrt(0XC0);
 for(k=0;k<15;k++)
			{
			data_wrt(d[k]);
			}
	 Delay10KTCYx(500);
 goto start;
	 }
        
	

	if((l1 == 0)&&(l2 == 0)&&(l3==0))
     {
	
         cmd_wrt(1);
	  for(k=0;k<15;k++)
			{
			data_wrt(e[k]);
			}
	 cmd_wrt(0XC0);
	 for(k=0;k<15;k++)
			{
			data_wrt(f[k]);
			}

	 motor=0;
	 	 goto start;
	 }
	
	
  

}
}		   	  