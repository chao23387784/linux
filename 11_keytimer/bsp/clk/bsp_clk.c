#include "bsp_clk.h"

void clk_enable(void)
{
	CCM->CCGR0 = 0XFFFFFFFF;
	CCM->CCGR1 = 0XFFFFFFFF;

	CCM->CCGR2 = 0XFFFFFFFF;
	CCM->CCGR3 = 0XFFFFFFFF;
	CCM->CCGR4 = 0XFFFFFFFF;
	CCM->CCGR5 = 0XFFFFFFFF;
	CCM->CCGR6 = 0XFFFFFFFF;
}

void imx6u_clkinit()
{
	/* init arm clk to 528MHz*/
	if((CCM->CCSR >> 2 & 0x01) == 0)//is arm clk switch to main?
	{
		CCM->CCSR &= ~(1 << 8);//switch step_clk to osc_clk
		CCM->CCSR |= (1 << 2);//switch pll1_sw_clk to step_clk
	}

	CCM_ANALOG->PLL_ARM &= ~(0x7F << 0);
	CCM_ANALOG->PLL_ARM |= 88;//set arm clk total freq
	CCM_ANALOG->PLL_ARM |= (1 << 13);//enable clock output

	CCM->CACRR &= ~(0x07 << 0);
	CCM->CACRR |= 0x01;//set devide value

	CCM->CCSR &= ~(2 << 0);//switch pll1_sw_clk to pll1_main_clk

	uint32_t reg = CCM_ANALOG->PFD_528;
	reg &= ~(0x3F << 0);
	reg |= (27 << 0);//PLL2 PFD0 352MHz

	reg &= ~(0x3F << 8);
	reg |= (16 << 8);//PLL2 PFD1 594MHz

	reg &= ~(0x3F << 16);
	reg |= (24 << 16);//PLL2 PFD2 396MHz

	reg &= ~(0x3F << 24);
	reg |= (32 << 24);//PLL2 PFD3 297MHz
	CCM_ANALOG->PFD_528 = reg;

	reg = CCM_ANALOG->PFD_480;
	reg &= ~(0x3F << 0);
	reg |= (12 << 0);//PLL3 PFD0 720MHz

	reg &= ~(0x3F << 8);
	reg |= (16 << 8);//PLL3 PFD1 540MHz

	reg &= ~(0x3F << 16);
	reg |= (17 << 16);//PLL3 PFD2 508.2MHz

	reg &= ~(0x3F << 24);
	reg |= (19 << 24);//PLL3 PFD3 454.7MHz	
	CCM_ANALOG->PFD_480 = reg;

	/* AHB_CLK_ROOT 132MHz */
	CCM->CBCMR &= ~(3 << 18);
	CCM->CBCMR |= (1 << 18); //select clk from pll2 pfd2

	CCM->CBCDR &= ~(1 << 25); //select clk from pll2
	while(CCM->CDHIPR & (1 << 5)){} //wait until not busy

	//while(CCM->CDHIPR & (1 << 1)){}
	//CCM->CBCDR &= ~(7 << 10);
	//CCM->CBCDR |= (2 << 10);

	/* IPG_CLK_ROOT 66MHz */
	CCM->CBCDR &= ~(3 << 8);
	CCM->CBCDR |= (1 << 8); //set devide value
	/* PERCLK_CLK_ROOT 66MHz */
	CCM->CSCMR1 &= ~(6 << 0); //select clk from ipg clk root
	CCM->CSCMR1 &= ~(0x3F << 0); //set devide value
}