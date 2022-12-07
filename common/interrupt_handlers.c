//static uint8_t fh_buf[16];
static
void Fault_Handler() {
//    struct {
//        uint32_t r0;
//        uint32_t r1;
//        uint32_t r2;
//        uint32_t r3;
//        uint32_t r12;
//        uint32_t lr;
//        uint32_t pc;
//        uint32_t psr;
//    } *stack_ptr; //Указатель на текущее значение стека(SP)
//
//    asm(
//            "TST lr, #4 \n" //Тестируем 3ий бит указателя стека(побитовое И)
//            "ITE EQ \n"   //Значение указателя стека имеет бит 3?
//            "MRSEQ %[ptr], MSP  \n"  //Да, сохраняем основной указатель стека
//            "MRSNE %[ptr], PSP  \n"  //Нет, сохраняем указатель стека процесса
//            : [ptr] "=r"(stack_ptr)
//    );
//
//    display_fill_screen(0x0000);
//    display_write_string(0, 0, "***HardFault***", Font_7x10, 0xFFFF, 0x0000);
//    display_write_string(0, 10, "CFSR: 0x", Font_7x10, 0xFFFF, 0x0000);
//    sprintf(fh_buf, "%08X", SCB->CFSR);
//    display_write_string(7*8, 10, fh_buf, Font_7x10, 0xFFFF, 0x0000);
//    if (SCB->CFSR == 0x82) {
//        display_write_string(0, 20, "Nullptr?", Font_7x10, 0xFFFF, 0x0000);
//    }
//    display_update_no_dma();

    __disable_irq();

    /* Go into an infinite loop */
    for (;;);
}