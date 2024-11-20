PRINTF("PWM Seminar.\r\n");

uint32_t PERIOD_333HZ = FTM1_TIMER_MODULO_VALUE;
uint32_t MS = PERIOD_333HZ / 3;

while(1) {
PRINTF("Enter servo angle from range [0, 180]:\r\n");
uint32_t angle = 0;
int input_count = SCANF("%u", &angle);

if (input_count != 1 || angle > 180) {
	PRINTF("Invalid input.\r\n");
	angle = 90;
}

FTM1->CONTROLS[kFTM_Chnl_1].CnV = MS + (MS * angle) / 180;
FTM_SetSoftwareTrigger(FTM1, true);

PRINTF("Servo is updated.\r\n");
