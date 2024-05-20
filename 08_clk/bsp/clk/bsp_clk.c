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
	if((CCM->CCSR >> 2 & 0x01) == 0)
	{
		CCM->CCSR |= (1 << 2);
	}

	CCM_ANALOG->PLL_ARM &= ~(0x7F << 0);
	CCM_ANALOG->PLL_ARM |= 88;

	CCM->CACRR &= ~(0x07 << 0);
	CCM->CACRR |= 0x01;

	uint32_t reg = CCM_ANALOG->PFD_528;
	reg &= ~(0x1F << 0);
	reg |= 27;//PLL2 PFD0 352MHz

	reg &= ~(0x1F << 8);
}