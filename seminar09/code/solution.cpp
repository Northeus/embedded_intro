std::array<uint16_t, 128> readFrame() {
	std::array<uint16_t, 128> frame;

	GPIO_PinSI::set(1);
	GPIO_PinCLK::set(1);

	asm ("nop");
	GPIO_PinSI::set(0);

	for (auto &pixel : frame) {
		GPIO_PinCLK::set(0);

		asm ("nop");
		GPIO_PinCLK::set(1);

		pixel = ADC_read_polling();
	}

	GPIO_PinCLK::set(0);

	return frame;
}

std::array<uint16_t, 128> readCam(uint32_t exposition_us) {
	readFrame();

	delayUs(exposition_us);

	return readFrame();
}
