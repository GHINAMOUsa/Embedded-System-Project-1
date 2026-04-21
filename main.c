/* Task 02 */
#define GPIO0DIR (*((volatile unsigned long *)0x50008000))
#define GPIO0DATA (*((volatile unsigned long *)0x50003FFC))
#define GPIO1DIR (*((volatile unsigned long *)0x50018000))
#define GPIO1DATA (*((volatile unsigned long *)0x50013FFC))

void TPMInterruptHandler(void) {}

int main() {
    GPIO1DIR |= 0xF0;
    GPIO0DIR &= ~0x06;
    
    unsigned long led_state = 0x10;
    GPIO1DATA = (GPIO1DATA & ~0xF0) | led_state;
    
    while (1) {
        // Shift Right (Button on GPIO0.1)
        if (GPIO0DATA & 0x02) {
            if (led_state == 0x80) {
                led_state = 0x10;
            } else {
                led_state <<= 1;
            }
            
            GPIO1DATA = (GPIO1DATA & ~0xF0) | led_state;
            
            while (GPIO0DATA & 0x02);
            
            volatile int i;
            for (i = 0; i < 10000; i++);
        }
        
        // Shift Left (Button on GPIO0.2)
        if (GPIO0DATA & 0x04) {
            if (led_state == 0x10) {
                led_state = 0x80;
            } else {
                led_state >>= 1;
            }
            
            GPIO1DATA = (GPIO1DATA & ~0xF0) | led_state;
            
            while (GPIO0DATA & 0x04);
            
            volatile int i;
            for (i = 0; i < 10000; i++);
        }
    }
}