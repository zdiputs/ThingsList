#include "main.h"
unsigned short AdcValue[2];
unsigned short AdDataOrig[SUMC][2];
//adc
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
{

  unsigned int i,j;
  unsigned int tmp[2]={0,0};
  for(j=0;j<2;j++)
  {
    tmp[j]=0;
    for(i=0;i<SUMC;i++)
    {
      tmp[j]=tmp[j]+AdDataOrig[i][j];
    }
    AdcValue[j]=tmp[j]/SUMC;


    tmp[j]=0;
  }

  return;
}
