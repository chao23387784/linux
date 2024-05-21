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
		CCM->CCSR |= (1 << 2);//switch to soc
	}

	CCM_ANALOG->PLL_ARM &= ~(0x7F << 0);
	CCM_ANALOG->PLL_ARM |= 88;//set arm clk total freq

	CCM->CACRR &= ~(0x07 << 0);
	CCM->CACRR |= 0x01;//set devide value

	uint32_t reg = CCM_ANALOG->PFD_528;
	reg &= ~(0x1F << 0);
	reg |= (27 << 0);//PLL2 PFD0 352MHz

	reg &= ~(0x1F << 8);
	reg |= (16 << 8);//PLL2 PFD1 594MHz

	reg &= ~(0x1F << 16);
	reg |= (24 << 16);//PLL2 PFD2 396MHz

	reg &= ~(0x1F << 24);
	reg |= (48 << 24);//PLL2 PFD3 200MHz 48 out of range of 12-35!!!!!!!
	CCM_ANALOG->PFD_528 = reg;

	reg = CCM_ANALOG->PFD_480;
	reg &= ~(0x1F << 0);
	reg |= (12 << 0);//PLL3 PFD0 720MHz

	reg &= ~(0x1F << 8);
	reg |= (16 << 8);//PLL3 PFD1 540MHz

	reg &= ~(0x1F << 16);
	reg |= (17 << 16);//PLL3 PFD2 508.2MHz

	reg &= ~(0x1F << 24);
	reg |= (19 << 24);//PLL3 PFD3 454.7MHz	
	CCM_ANALOG->PFD_480 = reg;
}