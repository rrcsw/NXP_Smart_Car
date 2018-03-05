/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2016,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��179029047
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ����������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		SEEKFREE_7725.c
 * @brief      		С���(��ֵ������ͷ)������
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		Go For It(1325536866)
 * @version    		v1.0
 * @Software 		IAR 7.7 or MDK 5.17
 * @Target core		MK60DN512VLL10
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2016-02-25
 * @note
					OV7725���߶��壺
					------------------------------------ 
						ģ��ܽ�            ��Ƭ���ܽ�
						SDA                 C17
						SCL                 C16
						���ж�              C6
						�����ж�            C18           
						���ݿ�              C8-C15 
					------------------------------------ 
	
					Ĭ�Ϸֱ�����            160*120
					Ĭ��FPS                 50֡
 ********************************************************************************************************************/



#include "SEEKFREE_7725.h"



uint8 image_bin[OV7725_SIZE];                                   //����洢����ͼ�������
uint8 image_dec[OV7725_H][OV7725_W];

uint8 OV7725_IDCode = 0;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      С�������ͷ�ڲ��Ĵ�����ʼ��(�ڲ�ʹ�ã��û��������)
//  @param      NULL
//  @return     uint8			����0�����������1��ɹ�
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 ov7725_reg_init(void)
{
    
    simiic_write_reg ( OV7725_DEV_ADD, OV7725_COM7, 0x80 );	//��λ����ͷ
    systick_delay_ms(50);
	OV7725_IDCode = simiic_read_reg( OV7725_DEV_ADD, OV7725_VER ,SCCB);
    if( OV7725_IDCode != OV7725_ID )    return 0;			//У������ͷID��


    if(OV7725_IDCode == OV7725_ID)
    {
        //ID��ȷ������   Ȼ�����üĴ���
        simiic_write_reg(OV7725_DEV_ADD, OV7725_COM4         , 0xC1);  
        simiic_write_reg(OV7725_DEV_ADD, OV7725_CLKRC        , 0x01);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_COM2         , 0x03);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_COM3         , 0xD0);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_COM7         , 0x40);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_HSTART       , 0x3F);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_HSIZE        , 0x50);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_VSTRT        , 0x03);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_VSIZE        , 0x78);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_HREF         , 0x00);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_SCAL0        , 0x0A);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_AWB_Ctrl0    , 0xE0);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_DSPAuto      , 0xff);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_DSP_Ctrl2    , 0x0C);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_DSP_Ctrl3    , 0x00);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_DSP_Ctrl4    , 0x00);
      
      
        if(OV7725_W == 80)              simiic_write_reg(OV7725_DEV_ADD, OV7725_HOutSize    , 0x14);
        else if(OV7725_W == 160)        simiic_write_reg(OV7725_DEV_ADD, OV7725_HOutSize    , 0x28);
        else if(OV7725_W == 240)        simiic_write_reg(OV7725_DEV_ADD, OV7725_HOutSize    , 0x3c);
        else if(OV7725_W == 320)        simiic_write_reg(OV7725_DEV_ADD, OV7725_HOutSize    , 0x50);
		
        if(OV7725_H == 60)              simiic_write_reg(OV7725_DEV_ADD, OV7725_VOutSize    , 0x1E);
        else if(OV7725_H == 120)        simiic_write_reg(OV7725_DEV_ADD, OV7725_VOutSize    , 0x3c);
        else if(OV7725_H == 180)        simiic_write_reg(OV7725_DEV_ADD, OV7725_VOutSize    , 0x5a);
        else if(OV7725_H == 240)        simiic_write_reg(OV7725_DEV_ADD, OV7725_VOutSize    , 0x78);
      
      
        simiic_write_reg(OV7725_DEV_ADD, OV7725_REG28        , 0x01);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_EXHCH        , 0x10);
		simiic_write_reg(OV7725_DEV_ADD, OV7725_EXHCL        , 0x1F);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_GAM1         , 0x0c);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_GAM2         , 0x16);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_GAM3         , 0x2a);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_GAM4         , 0x4e);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_GAM5         , 0x61);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_GAM6         , 0x6f);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_GAM7         , 0x7b);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_GAM8         , 0x86);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_GAM9         , 0x8e);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_GAM10        , 0x97);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_GAM11        , 0xa4);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_GAM12        , 0xaf);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_GAM13        , 0xc5);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_GAM14        , 0xd7);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_GAM15        , 0xe8);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_SLOP         , 0x20);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_LC_RADI      , 0x00);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_LC_COEF      , 0x13);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_LC_XC        , 0x08);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_LC_COEFB     , 0x14);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_LC_COEFR     , 0x17);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_LC_CTR       , 0x05);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_BDBase       , 0x99);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_BDMStep      , 0x03);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_SDE          , 0x04);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_BRIGHT       , 0x00);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_CNST         , 0x40);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_SIGN         , 0x06);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_UVADJ0       , 0x11);
        simiic_write_reg(OV7725_DEV_ADD, OV7725_UVADJ1       , 0x02);
        return 1;
    }
    else        return 0;//����
    
}





//-------------------------------------------------------------------------------------------------------------------
//  @brief      С�������ͷ�ɼ������ʼ��(�ڲ�ʹ�ã��û��������)
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void ov7725_port_init(void)
{
    //DMAͨ��0��ʼ����OV7725_PCLK����Դ(Ĭ��������)��Դ��ַΪOV7725_DATAPORT��Ŀ�ĵ�ַΪ��image_bin��ÿ�δ���1Byte
    dma_portx2buff_init(OV7725_DMA_CH, (void *)&OV7725_DATAPORT, (void *)image_bin, OV7725_PCLK, DMA_BYTE1, OV7725_DMA_NUM, DADDR_KEEPON);

    DMA_DIS(OV7725_DMA_CH);
    disable_irq(INTERRUPT_NUNBERS);                             //�ر��ж�
    DMA_IRQ_CLEAN(OV7725_DMA_CH);                               //���ͨ�������жϱ�־λ
    DMA_IRQ_EN(OV7725_DMA_CH);

    port_init(OV7725_PCLK, ALT1 | DMA_FALLING | PULLDOWN );     //PCLK
    port_init(OV7725_VSYNC, ALT1 | IRQ_RISING  | PULLDOWN | PF);//���жϣ��������Ͻ��ش����жϣ����˲�

    enable_irq(INTERRUPT_NUNBERS);
	EnableInterrupts;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      С�������ͷ��ʼ��(����֮�����ú�����жϺ������ɲɼ�ͼ��)
//  @param      NULL
//  @return     0
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 ov7725_init(void)
{
	IIC_init();
	ov7725_reg_init();                                          //����ͷ�Ĵ�������
    ov7725_port_init();                                         //����ͷ�ж����ż�DMA����
    return 0;
}





//-------------------------------------------------------------------------------------------------------------------
//  @brief      С�������ͷ���ж�
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:					��isr.c�����ȴ�����Ӧ���жϺ�����Ȼ����øú���(֮�����������жϱ�־λ)
//-------------------------------------------------------------------------------------------------------------------
void ov7725_vsync(void) 
{
    uint8  n;                                                   //���ź�
	uint32 flag;
	
	flag = INTERRUPT_ISFR;
    INTERRUPT_ISFR  = 0xffffffff;                               //���жϱ�־λ
            
    n = VSYNC_CHANNEL;                                          //���ж�
    if(flag & (1 << n))                                         //�������ж�
    {
		INTERRUPT_ISFR = 1 <<  PCLK_CHANNEL;                    //���PCLK��־λ
        DMA0->TCD[OV7725_DMA_CH].DADDR = (uint32)image_bin;     //�ָ�DMA��ַ
        DMA_EN(OV7725_DMA_CH);                                  //ʹ��DMAͨ��CHn Ӳ������
    }

}

uint8 ov7725_finish_flag = 0;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      С�������ͷDMA����ж�
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:					��isr.c�����ȴ�����Ӧ���жϺ�����Ȼ����øú���(֮�����������жϱ�־λ)
//-------------------------------------------------------------------------------------------------------------------
void ov7725_dma(void)
{
    DMA_IRQ_CLEAN(OV7725_DMA_CH);                               //���ͨ�������жϱ�־λ
	ov7725_finish_flag = 1;										//�ɼ���ɱ�־λ
}       




//-------------------------------------------------------------------------------------------------------------------
//  @brief      С�������ͷ���ݽ�ѹ����
//  @param      *data1				Դ��ַ
//  @param      *data2				Ŀ�ĵ�ַ
//  @return     void
//  @since      v1.0
//  Sample usage:					Image_Decompression(da1,dat2[0]);//��һά����dat1�����ݽ�ѹ����ά����dat2��.
//-------------------------------------------------------------------------------------------------------------------
void Image_Decompression(uint8 *data1,uint8 *data2)
{
    uint8  temp[2] = {0,255};
    uint16 lenth = OV7725_SIZE;
    uint8  i = 8;

        
    while(lenth--)
    {
        i = 8;
        while(i--)
        {
            *data2++ = temp[(*data1 >> i) & 0x01];
        }
        data1++;
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      С�������ͷδ��ѹͼ��������λ���鿴ͼ��
//  @param      *imgaddr			ѹ��ͼ�����ݵ�ַ
//  @param      *imgsize			ͼ���С(ֱ����дOV7725_SIZE)
//  @return     void
//  @since      v1.0
//  Sample usage:					���øú���ǰ���ȳ�ʼ��uart2
//-------------------------------------------------------------------------------------------------------------------
void seekfree_sendimg_7725(void *imgaddr, uint32_t imgsize)
{
    uart_putchar(uart5, 0x00);uart_putchar(uart5, 0xff);uart_putchar(uart5, 0x01);uart_putchar(uart5, 0x01);//�����ĸ��ֽ�����
    uart_putbuff(uart5, (uint8_t *)imgaddr, imgsize);   //�ٷ���ͼ��
}



