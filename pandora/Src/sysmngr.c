#include "sysmngr.h"
#include "stdio.h"
#include "stm32l4xx_ll_usart.h"

#define RX_BUFFER_SIZE                   10
uint8_t aRXBufferA[RX_BUFFER_SIZE];
uint8_t aRXBufferB[RX_BUFFER_SIZE];
__IO uint32_t uwNbReceivedChars = 0;
__IO uint32_t uwBufferReadyIndication = 0;
uint8_t *pBufferReadyForUser;
uint8_t *pBufferReadyForReception;


#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

extern UART_HandleTypeDef huart1;
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
  if (HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF)!= HAL_OK)
  {
      /*error handler*/
      __nop();
  }

  return ch;
}

void usr_system_init(void)
{
    pBufferReadyForReception = aRXBufferA;
    pBufferReadyForUser      = aRXBufferB;
    uwNbReceivedChars = 0;
    uwBufferReadyIndication = 0;
    LL_USART_EnableIT_RXNE(USART1);
    LL_USART_EnableIT_ERROR(USART1);
    
    printf("Hello pandora.\n\r");
    printf("a=%d, b=%03d, c=%c, d=%f\n\r", 1,2,'a',3.14);
}

void usr_system_ctrl_manager(void)
{
    if (button_pressed != 0)
    {
        if (button_pressed&KEY0_PRESSED)
        {
            led_toggle(LED_R);
            beep(OFF);
        }
        if (button_pressed&KEY1_PRESSED)
        {
            led_toggle(LED_G);
        }
        if (button_pressed&KEY2_PRESSED)
        {
            led_toggle(LED_B);
        }
        
        if (button_pressed&WK_UP_PRESSED)
        {
            beep(ON);
        }
        
        button_pressed = 0;
    }

    if (uwBufferReadyIndication == 1)
    {
        uwBufferReadyIndication = 0;
        HAL_UART_Transmit(&huart1, pBufferReadyForUser, RX_BUFFER_SIZE, 0xFFFF);
    }
}


void UART_CharReception_Callback(void)
{
  uint8_t *ptemp;

  /* Read Received character. RXNE flag is cleared by reading of RDR register */
  pBufferReadyForReception[uwNbReceivedChars++] = LL_USART_ReceiveData8(USART1);

  if (uwNbReceivedChars >= RX_BUFFER_SIZE)
  {
    uwBufferReadyIndication = 1;

    ptemp = pBufferReadyForUser;
    pBufferReadyForUser = pBufferReadyForReception;
    pBufferReadyForReception = ptemp;
    uwNbReceivedChars = 0;
  }
}

void UART_Error_Callback(void)
{
  __IO uint32_t isr_reg;

  /* Disable USARTx_IRQn */
  NVIC_DisableIRQ(USART1_IRQn);
  
  isr_reg = LL_USART_ReadReg(USART1, ISR);
  if (isr_reg & LL_USART_ISR_NE)
  {
    led_on(LED_R);
  }
  else
  {
    led_on(LED_G);
  }
}

void USART1_IRQHandler(void)
{
  /* Check RXNE flag value in ISR register */
  if(LL_USART_IsActiveFlag_RXNE(USART1) && LL_USART_IsEnabledIT_RXNE(USART1))
  {
    UART_CharReception_Callback();
  }

  if(LL_USART_IsEnabledIT_ERROR(USART1) && LL_USART_IsActiveFlag_NE(USART1))
  {
    UART_Error_Callback();
  }
}

