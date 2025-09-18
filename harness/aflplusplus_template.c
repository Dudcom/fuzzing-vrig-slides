#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <afl-fuzz.h>

#ifndef __AFL_FUZZ_TESTCASE_LEN


#include <stdio.h>
#include <stdint.h>

// If the target needs to be initialized once then put
// these calls in this function:
int LLVMFuzzerInitialize(int *argc, char ***argv) {
  return 0;
}

// This is the harness function, here you apply the mutated
// input in “data” with size “size” to the target function.
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // 1. Check first that “size” is the necessary length we
  // need and return otherwise

  // 2. Transform “data” of “size” to the necessary 
  // parameters of the target functions

  // 3. Call the initial functions necessary to set up the 
  // call you want to fuzz

  // 4. Call the target function with the mutated input

  // 5. Check return code and returned data validity

  // 6. If necessary, perform cleanup and reset the state.
  // Avoid memory leaks by any means!

  return 0;
}

ssize_t fuzz_len;
unsigned char fuzz_buf[1024000];

#define __AFL_FUZZ_TESTCASE_LEN fuzz_len
#define __AFL_FUZZ_TESTCASE_BUF fuzz_buf 
#define __AFL_FUZZ_INIT() void sync(void);
#define __AFL_LOOP(x) \
   ((fuzz_len = read(0, fuzz_buf, sizeof(fuzz_buf))) > 0 ? 1 : 0)
#define __AFL_INIT() sync()

#endif

__AFL_FUZZ_INIT();

#pragma clang optimize off
#pragma GCC optimize("O0")



int main(int argc, char **argv)
{
   (void)argc; (void)argv;
  
   ssize_t len;
   unsigned char *buf;

   __AFL_INIT();
   buf = __AFL_FUZZ_TESTCASE_BUF;
   while (__AFL_LOOP(INT_MAX)) {
       len = __AFL_FUZZ_TESTCASE_LEN;
       LLVMFuzzerTestOneInput(buf, (size_t)len);
   }
  
   return 0;
}

