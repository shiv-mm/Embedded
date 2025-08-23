#include <LPC214x.H>                       
unsigned char dig[] = {0x88,0xeb,0x4c,0x49,0x2b,0x19,0x18,0xcb,0x8,0x9,0xa,0x38,0x9c,0x68,0x1c,0x1e};

void delay(unsigned int count) {
  int j = 0, i = 0;
  for (j = 0; j < count; j++) {
    for (i = 0; i < 120; i++);
  }
}

int main(void) {
  unsigned char count = 0;
  unsigned int i = 0;

  IO0DIR |= (1 << 10) | (1 << 11) | (1 << 12) | (1 << 13);  // Set control lines for 1st, 2nd, 3rd, and 4th displays as outputs
  IO0DIR |= 0x007F8000;  // Set segment lines as outputs

  while (1) {
    count++;
    if (count == 16) count = 0;

    for (i = 0; i < 15; i++) {
      IO0CLR = 0x007F8000;  // Clear the current segment outputs
      IO0SET = (dig[count] << 15);  // Set the new digit

      // Activate the third display
      IO0CLR = (1 << 10) | (1 << 11) | (1 << 13);  // Deactivate other displays
      IO0SET = (1 << 12);  // Activate third display
      delay(200);

      // OR, to activate the fourth display, use:
      // IO0CLR = (1 << 10) | (1 << 11) | (1 << 12);
      // IO0SET = (1 << 13);
    }
  }
}
