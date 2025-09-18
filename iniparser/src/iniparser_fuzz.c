#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <afl-fuzz.h>

#ifndef __AFL_FUZZ_TESTCASE_LEN

#include "iniparser.h"
#include <stdio.h>
#include <stdint.h>

int LLVMFuzzerInitialize(int *argc, char ***argv) {
  return 0;
}


int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {


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

