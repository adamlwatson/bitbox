/*
 *    Debugging
 */

// Asumption is that the Tx pin on Serial3 is connected to a TTL Serial device Rx

int freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
 
void StreamPrint_progmem(Print &out,PGM_P format,...)
{
  // program memory version of printf - copy of format string and result share a buffer
  // so as to avoid too much memory use
  char formatString[128], *ptr;
  strncpy_P(formatString, format, sizeof(formatString)); // copy in from program mem
  // null terminate - leave last char since we might need it in worst case for result's \0
  formatString[ sizeof(formatString)-2 ]='\0';
  ptr=&formatString[ strlen(formatString)+1 ]; // our result buffer...
  va_list args;
  va_start (args,format);
  vsnprintf(ptr, sizeof(formatString)-1-strlen(formatString), formatString, args);
  va_end (args);
  formatString[ sizeof(formatString)-1 ]='\0';
  out.print(ptr);
}

// debug output to external serial console using "sprintf"-style formatting
#define dlog(format, ...) StreamPrint_progmem(Serial3,PSTR(format),##__VA_ARGS__)

// sprintf-style formatted string to any stream-capable device
#define stpr(stream,format, ...) StreamPrint_progmem(stream,PSTR(format),##__VA_ARGS__)

