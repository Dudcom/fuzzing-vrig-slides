// AFL_USE_ASAN=1 afl-clang-fast -g -O1 -fsanitize=address,undefined \
// iniparser_fuzz.c iniparser.c dictionary.c -o iniparser_fuzz

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <afl-fuzz.h>

#ifndef __AFL_FUZZ_TESTCASE_LEN

#include "iniparser.h"
#include <stdio.h>
#include <stdint.h>

static int silent_error_callback(const char *format, ...) {
    (void)format;
    return 0;
}

int LLVMFuzzerInitialize(int *argc, char ***argv) {
    iniparser_set_error_callback(silent_error_callback);
    return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }


    FILE *fp = fmemopen(null_terminated_data, size, "r");
    if (!fp) {
        free(null_terminated_data);
        return 0;
    }
    
    dictionary *dict = iniparser_load_file(fp, "fuzzed_file.ini");
    
    
    if (dict) {
        
        int nsec = iniparser_getnsec(dict);
        
        if (nsec > 0 && nsec < 100) { 
            for (int i = 0; i < nsec; i++) {
                const char *secname = iniparser_getsecname(dict, i);
                if (secname) {
                    
                    int nkeys = iniparser_getsecnkeys(dict, secname);
                    (void)nkeys; 
                    
                    iniparser_find_entry(dict, secname);
                }
            }
        }
        

        // test_keys = data[:data_len/2]
        // could do something like this and test the rest of the API calls if you really wanted to
        // for (size_t i = 0; i < sizeof(test_keys) / sizeof(test_keys[0]); i++) {
        //     iniparser_getstring(dict, test_keys[i], "default");
        //     iniparser_getint(dict, test_keys[i], 0);
        //     iniparser_getboolean(dict, test_keys[i], 0);
        //     iniparser_getdouble(dict, test_keys[i], 0.0);
        // }
        
        // iniparser_set(dict, "fuzz:test", "value");
        // iniparser_unset(dict, "fuzz:test");
        // iniparser_freedict(dict);
    }
    
    fclose(fp);
    free(null_terminated_data);
    
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