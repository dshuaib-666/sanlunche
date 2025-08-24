#include "NRF.h"
#include "spi.h"



const uint8_t TX_ADDRESS[TX_ADR_WIDTH]={0x13,0x25,0x12,0x65,0x23}; //עַ̍֘
const uint8_t RX_ADDRESS[RX_ADR_WIDTH]={0x13,0x25,0x12,0x65,0x23}; //ޓ˕ַ֘
 uint8_t Receive[33]; 
/**                  
  * گ˽٦Ŝ: ιԮѐFlashׁȡдɫһٶؖޚ˽ߝҢޓ˕һٶؖޚ˽ߝ
  * ˤɫӎ˽: byteúսע̍˽ߝ
  * ׵ ܘ ֵ: uint8_túޓ˕սք˽ߝ
  * ˵    ķúϞ
  */
uint8_t SPIx_ReadWriteByte(SPI_HandleTypeDef* hspi,uint8_t byte)
{
  uint8_t d_read,d_send=byte;
  if(HAL_SPI_TransmitReceive(hspi,&d_send,&d_read,1,0xFF)!=HAL_OK)
  {
    d_read=0xFF;
  }
  return d_read; 
}
 
/**
  * گ˽٦Ŝ: ݬӢ24L01ˇرզ՚
  * ˤɫӎ˽: Ϟ
  * ׵ ܘ ֵ: 0ìԉ٦;1ìʧќ
  * ˵    ķúϞ          
  */ 
uint8_t NRF24L01_Check(void)
{
	uint8_t buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	uint8_t i;
   
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);//дɫ5ٶؖޚքַ֘.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5); //ׁԶдɫքַ֘  
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;   //ݬӢ24L01խϳ	
	return 0;		 	//ݬӢս24L01
}	
 
/**
  * گ˽٦Ŝ: SPIд݄զǷ
  * ˤɫӎ˽: Ϟ
  * ׵ ܘ ֵ: Ϟ
  * ˵    ķúreg:ָ݄֨զǷַ֘
  *           
  */ 
uint8_t NRF24L01_Write_Reg(uint8_t reg,uint8_t value)
{
    uint8_t status;	
  NRF24L01_SPI_CS_ENABLE();                 //ʹŜSPIԫˤ
  status =SPIx_ReadWriteByte(&hspi1,reg);   //ע݄̍զǷۅ 
  SPIx_ReadWriteByte(&hspi1,value);         //дɫ݄զǷքֵ
  NRF24L01_SPI_CS_DISABLE();                //޻ֹSPIԫˤ	   
  return(status);       			//׵ܘ״ֵ̬
}
 
/**
  * گ˽٦Ŝ: ׁȡSPI݄զǷֵ
  * ˤɫӎ˽: Ϟ
  * ׵ ܘ ֵ: Ϟ
  * ˵    ķúreg:Ҫׁք݄զǷ
  *           
  */ 
uint8_t NRF24L01_Read_Reg(uint8_t reg)
{
	uint8_t reg_val;	    
 	NRF24L01_SPI_CS_ENABLE();          //ʹŜSPIԫˤ		
  SPIx_ReadWriteByte(&hspi1,reg);   //ע݄̍զǷۅ
  reg_val=SPIx_ReadWriteByte(&hspi1,0XFF);//ׁȡ݄զǷŚɝ
  NRF24L01_SPI_CS_DISABLE();          //޻ֹSPIԫˤ		    
  return(reg_val);           //׵ܘ״ֵ̬
}		
 
/**
  * گ˽٦Ŝ: ՚ָ֨λ׃ׁԶָ֨Ӥ׈ք˽ߝ
  * ˤɫӎ˽: Ϟ
  * ׵ ܘ ֵ: ՋՎׁսք״̬݄զǷֵ 
  * ˵    ķúϞ
  *           
  */ 
uint8_t NRF24L01_Read_Buf(uint8_t reg,uint8_t *pBuf,uint8_t len)
{
	uint8_t status,uint8_t_ctr;	   
  
  NRF24L01_SPI_CS_ENABLE();           //ʹŜSPIԫˤ
  status=SPIx_ReadWriteByte(&hspi1,reg);//ע݄̍զǷֵ(λ׃),Ңׁȡ״ֵ̬   	   
 	for(uint8_t_ctr=0;uint8_t_ctr<len;uint8_t_ctr++)
  {
    pBuf[uint8_t_ctr]=SPIx_ReadWriteByte(&hspi1,0XFF);//ׁԶ˽ߝ
  }
  NRF24L01_SPI_CS_DISABLE();       //ژҕSPIԫˤ
  return status;        //׵ܘׁսք״ֵ̬
}
 
/**
  * گ˽٦Ŝ: ՚ָ֨λ׃дָ֨Ӥ׈ք˽ߝ
  * ˤɫӎ˽: Ϟ
  * ׵ ܘ ֵ: Ϟ
  * ˵    ķúreg:݄զǷ(λ׃)  *pBuf:˽ߝָ֫  len:˽ߝӤ׈
  *           
  */ 
uint8_t NRF24L01_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
	uint8_t status,uint8_t_ctr;	    
 	NRF24L01_SPI_CS_ENABLE();          //ʹŜSPIԫˤ
  status = SPIx_ReadWriteByte(&hspi1,reg);//ע݄̍զǷֵ(λ׃),Ңׁȡ״ֵ̬
  for(uint8_t_ctr=0; uint8_t_ctr<len; uint8_t_ctr++)
  {
    SPIx_ReadWriteByte(&hspi1,*pBuf++); //дɫ˽ߝ	 
  }
  NRF24L01_SPI_CS_DISABLE();       //ژҕSPIԫˤ
  return status;          //׵ܘׁսք״ֵ̬
}		
 
/**
  * گ˽٦Ŝ: Ǵ֯NRF24L01ע̍һՎ˽ߝ
  * ˤɫӎ˽: Ϟ
  * ׵ ܘ ֵ: ע̍Ϊԉ״࠶
  * ˵    ķútxbuf:սע̍˽ߝ˗ַ֘
  *           
  */ 
uint8_t NRF24L01_TxPacket(uint8_t *txbuf)
{
	uint8_t sta; 
	NRF24L01_CE_LOW();
    NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//д˽ߝսTX BUF  32ٶؖޚ
 	NRF24L01_CE_HIGH();//Ǵ֯ע̍	 
  
	while(NRF24L01_IRQ_PIN_READ()!=0);//ֈսע̍Ϊԉ
  
	sta=NRF24L01_Read_Reg(STATUS);  //ׁȡ״̬݄զǷքֵ	   
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //ȥԽTX_DSܲMAX_RTא׏Ҫ־
	if(sta&MAX_TX)//կսخճטעՎ˽
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);//ȥԽTX FIFO݄զǷ 
		return MAX_TX; 
	}
	if(sta&TX_OK)//ע̍Ϊԉ
	{
		return TX_OK;
	}
	return 0xff;//Ǥ̻ԭӲע̍ʧќ
}
 
/**
  * گ˽٦Ŝ:Ǵ֯NRF24L01ޓ˕һՎ˽ߝ
  * ˤɫӎ˽: Ϟ
  * ׵ ܘ ֵ: Ϟ
  * ˵    ķúϞ
  *           
  */ 
uint8_t NRF24L01_RxPacket(uint8_t *rxbuf)
{
	uint8_t sta;		 
	sta=NRF24L01_Read_Reg(STATUS);  //ׁȡ״̬݄զǷքֵ    	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //ȥԽTX_DSܲMAX_RTא׏Ҫ־
	if(sta&RX_OK)//ޓ˕ս˽ߝ
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//ׁȡ˽ߝ
		NRF24L01_Write_Reg(FLUSH_RX,0xff);//ȥԽRX FIFO݄զǷ 
		return 0; 
	}	   
	return 1;//û˕սɎێ˽ߝ
}			
 
/**
  * گ˽٦Ŝ: كگ˽ԵʼۯNRF24L01սRXģʽ
  * ˤɫӎ˽: Ϟ
  * ׵ ܘ ֵ: Ϟ
  * ˵    ķúϞ
  *           
  */ 
void NRF24L01_RX_Mode(void)
{
  NRF24L01_CE_LOW();	  
  NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0F);//Ƥ׃ܹѾ٤طģʽքӎ˽;PWR_UP,EN_CRC,16BIT_CRC 
  NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);    //ʹŜͨր0քؔ֯Ӧհ    
  NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);//ʹŜͨր0քޓ˕ַ֘  	 
  NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);	     //ʨ׃RFͨхƵÊ		  
  NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);//ʨ׃TXעʤӎ˽,0dbնӦ,2Mbps,֍իʹնӦߪǴ   
  NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//ѡձͨր0քԐЧ˽ߝ࠭׈ 	       
  NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(uint8_t*)RX_ADDRESS,RX_ADR_WIDTH);//дRXޚַ֣֘
  NRF24L01_CE_HIGH(); //CEΪٟ,޸ɫޓ˕ģʽ 
  HAL_Delay(1);
}	
 
/**
  * گ˽٦Ŝ: كگ˽ԵʼۯNRF24L01սTXģʽ
  * ˤɫӎ˽: Ϟ
  * ׵ ܘ ֵ: Ϟ
  * ˵    ķúϞ
  *           
  */ 
void NRF24L01_TX_Mode(void)
{														 
  NRF24L01_CE_LOW();	    
  NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(uint8_t*)TX_ADDRESS,TX_ADR_WIDTH);//дTXޚַ֣֘ 
  NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(uint8_t*)RX_ADDRESS,RX_ADR_WIDTH); //ʨ׃TXޚַ֣֘,׷ҪΪʹŜACK	  
  NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);     //ʹŜͨր0քؔ֯Ӧհ    
  NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01); //ʹŜͨր0քޓ˕ַ֘  
  NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0xff);//ʨ׃ؔ֯טעݤٴʱݤ:4000us + 86us;خճؔ֯טעՎ˽:15Վ
  NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);       //ʨ׃RFͨրΪ40
  NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);  //ʨ׃TXעʤӎ˽,0dbնӦ,2Mbps,֍իʹնӦߪǴ   
  NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);    //Ƥ׃ܹѾ٤طģʽքӎ˽;PWR_UP,EN_CRC,16BIT_CRC,ޓ˕ģʽ,ߪǴ̹Ԑא׏
  NRF24L01_CE_HIGH();//CEΪٟ,10us۳Ǵ֯ע̍
  HAL_Delay(1);
}
 
/**
  * گ˽٦Ŝ: كگ˽NRF24L01޸ɫ֍٦ۄģʽ
  * ˤɫӎ˽: Ϟ
  * ׵ ܘ ֵ: Ϟ
  * ˵    ķúϞ
  *           
  */
void NRF_LowPower_Mode(void)
{
	NRF24L01_CE_LOW();	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x00);		//Ƥ׃٤طģʽ:ִ֧ģʽ
}
char BUFF_NBR[5];
struct NRF_BUFFER NBF_BUFF;  //֨ӥһٶޡٹͥ4ޓ˕˽ߝ
int sa_NRF_START=0;
int sa_NRF_GUDINGYAW=0;
int sa_NRF_KEY6=0;
int sa_NRF_KEY6_SATUS=0;
extern float X_real,Y_real;
void NRF_dispose(void) //Ԧmޓ˕ڽ4ք˽ߝ
{
	
	
    if(NRF24L01_RxPacket(Receive)==0)
    {
       
	   } //ׁȡփսփֵ
	  if(Receive[30]==6) {
		  
		 
	      Receive[32]=0;//ݓɫؖػԮޡ˸ػ 
		for(int p=0;p<=5;p++)			
		{BUFF_NBR[p]=Receive[1+p];
		NBF_BUFF.one=BUFF_NBR[0]*20;
		NBF_BUFF.two=BUFF_NBR[1]*20;  
		}
	    NBF_BUFF.left_right=2;
	   
    }
	  
	if(Receive[30]==7)
	{	sa_NRF_START=7;
	
	    Receive[32]=0;//ݓɫؖػԮޡ˸ػ 
		for(int p=0;p<=5;p++)			
       {BUFF_NBR[p]=Receive[1+p];
	  
	    NBF_BUFF.three=BUFF_NBR[2]*20;
		NBF_BUFF.four=BUFF_NBR[3]*20;
	
		}
	   NBF_BUFF.left_right=1;
	   if(Receive[28]==1)
	   {NBF_BUFF.satus=1;}
       if(Receive[28]==2)
	   { NBF_BUFF.satus=2;
	   }
	   if(Receive[28]==3)
	   { NBF_BUFF.satus=3;
	   }
	   if(Receive[28]==4)
	   { NBF_BUFF.satus=4;
	   }
	}
	
	
}	
