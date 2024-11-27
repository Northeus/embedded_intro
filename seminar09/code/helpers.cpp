template <uint32_t BASE, uint32_t PIN>
struct GPIO_Pin {
    static inline void set(bool value) {
        GPIO_PinWrite((GPIO_Type*) BASE, PIN, value);
    }

    static inline void toggle() {
        GPIO_PortToggle((GPIO_Type*) BASE, 1UL << PIN);
    }

    [[nodiscard]]
    static inline bool read() {
        return static_cast<bool>(GPIO_PinRead((GPIO_Type*) BASE, PIN));
    }
};

// TODO: update macros according to your config
using GPIO_PinCLK = GPIO_Pin<GPIOB_BASE, BOARD_CAMERA_CLK_PIN>;
using GPIO_PinSI = GPIO_Pin<GPIOB_BASE, BOARD_CAMERA_SI_PIN>;

//////////////////////////////////////////////////////////////////////////////

[[nodiscard]]
static inline uint16_t ADC_read_polling() {
	ADC16_SetChannelConfig(ADC1_PERIPHERAL, 0, &ADC1_channelsConfig[0]);

	while ((ADC16_GetChannelStatusFlags(ADC1_PERIPHERAL, 0)
			& kADC16_ChannelConversionDoneFlag) == 0) {
		asm ("nop");
	}

	return ADC16_GetChannelConversionValue(ADC1_PERIPHERAL, 0);
}

//////////////////////////////////////////////////////////////////////////////

volatile bool elapsed = false;

extern "C" {
	void PIT_DELAY_IRQHANDLER(void) {
		PIT_StopTimer(PIT_PERIPHERAL, PIT_DELAY);

		uint32_t intStatus;

		intStatus = PIT_GetStatusFlags(PIT_PERIPHERAL, PIT_DELAY);
		PIT_ClearStatusFlags(PIT_PERIPHERAL, PIT_DELAY, intStatus);

		elapsed = true;

		#if defined __CORTEX_M && (__CORTEX_M == 4U)
		__DSB();
		#endif
	}
}

void delayUs(uint32_t us) {
	PIT_StopTimer(PIT_PERIPHERAL, PIT_DELAY);
	elapsed = false;

	PIT_SetTimerPeriod(PIT_PERIPHERAL, PIT_DELAY, us * 60);
	PIT_StartTimer(PIT_PERIPHERAL, PIT_DELAY);

	while (!elapsed) {
		asm ("nop");
	}
}
