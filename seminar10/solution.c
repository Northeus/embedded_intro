#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"

static const uint32_t PERIOD_333HZ = FTM1_TIMER_MODULO_VALUE;
static const uint32_t MS = PERIOD_333HZ / 3U;

int setServo(int angle) {
	const static int LIMIT = 60;

	angle *= -1;
	angle = angle < -LIMIT ? -LIMIT : angle;
	angle = angle > LIMIT ? LIMIT : angle;

	if (angle < -90 || 180 < angle) {
		return -1;
	}

	const static uint32_t OFFSET = 90U;
	const static uint32_t RANGE = 180u;

	uint32_t shifted = angle + OFFSET;
	uint32_t ms = (MS * shifted) / RANGE;

	FTM1->CONTROLS[kFTM_Chnl_1].CnV = MS + ms;
	FTM_SetSoftwareTrigger(FTM1, true);

	return 0;
}

volatile bool elapsed = false;

void PIT_DELAY_IRQHANDLER(void) {
  PIT_StopTimer(PIT_PERIPHERAL, PIT_DELAY);

  uint32_t intStatus = PIT_GetStatusFlags(PIT_PERIPHERAL, PIT_DELAY);
  PIT_ClearStatusFlags(PIT_PERIPHERAL, PIT_DELAY, intStatus);

  elapsed = true;

  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}

void delayUs(uint32_t us) {
	elapsed = false;

	PIT_StopTimer(PIT_PERIPHERAL, PIT_DELAY);
	PIT_SetTimerPeriod(PIT_PERIPHERAL, PIT_DELAY, 60 * us);
	PIT_StartTimer(PIT_PERIPHERAL, PIT_DELAY);

	while (!elapsed) {
		asm ("nop");
	}
}

uint16_t readADC() {
	  ADC16_SetChannelConfig(
		  ADC1_PERIPHERAL,
		  ADC1_CH0_CONTROL_GROUP,
		  ADC1_channelsConfig);

	  while ((ADC16_GetChannelStatusFlags(ADC1_PERIPHERAL, ADC1_CH0_CONTROL_GROUP)
			  & kADC16_ChannelConversionDoneFlag) == 0) {
		  asm ("nop");
	  }

	  return ADC16_GetChannelConversionValue(
			 ADC1_PERIPHERAL,
			 ADC1_CH0_CONTROL_GROUP);
}

void loadCam(uint16_t* data128) {
	GPIO_PinWrite(SHIELD_CAM_SI_GPIO, SHIELD_CAM_SI_PIN, 1);
	GPIO_PinWrite(SHIELD_CAM_CLK_GPIO, SHIELD_CAM_CLK_PIN, 1);
	GPIO_PinWrite(SHIELD_CAM_SI_GPIO, SHIELD_CAM_SI_PIN, 0);

	for (int i = 0; i < 128; i++) {
		GPIO_PinWrite(SHIELD_CAM_CLK_GPIO, SHIELD_CAM_CLK_PIN, 0);
		GPIO_PinWrite(SHIELD_CAM_CLK_GPIO, SHIELD_CAM_CLK_PIN, 1);

		data128[i] = readADC();
	}

	GPIO_PinWrite(SHIELD_CAM_CLK_GPIO, SHIELD_CAM_CLK_PIN, 0);
}

void readCam(uint16_t* data128, uint32_t exposition_ms) {
	loadCam(data128);
	delayUs(exposition_ms * 1000);
	loadCam(data128);
}

 schumacher(uint16_t* data128) {
	int biggest_rais_index = 0;
	uint16_t biggest_rais_value = 0;

	int biggest_fall_index = 0;
	uint16_t biggest_fall_value = 0;

	for (int i = 0; i < 127; i++){
		if (data128[i] > data128[i + 1]) {
			uint16_t diff = data128[i] - data128[i + 1];

			if (biggest_fall_value < diff) {
				biggest_fall_index = i;
				biggest_fall_value = diff;
			}
		}

		if (data128[i] < data128[i + 1]) {
			uint16_t diff = data128[i + 1] - data128[i];

			if (biggest_rais_value < diff) {
				biggest_rais_index = i;
				biggest_rais_value = diff;
			}
		}
	}

	if (biggest_fall_index > biggest_rais_index) {
		return 0;
	}

	float prumer = (biggest_fall_index + biggest_rais_index) / 2;


	return ((prumer / 128 - 0.5) * -2) * 450;
}

void printFrame(uint16_t* data128) {
	for (int i = 0; i < 128; i++) {
		PRINTF("%d ", data128[i]);
	}

	PRINTF("\r\n");
}

int main(void) {
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    BOARD_InitDebugConsole();
#endif

    uint16_t frame[128] = {0U};
    const static uint32_t EXPOSITION_MS = 5;

    while(1) {
    	readCam(frame, EXPOSITION_MS);
		int angle = schumacher(frame);
		setServo(angle);

		// Slow down the servo a bit
		delayUs(100 * 1000);
    }

    return 0 ;
}

