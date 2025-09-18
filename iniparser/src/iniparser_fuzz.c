// AFL_USE_ASAN=1 afl-clang-lto -g -O1 -fsanitize=address,undefined \
// iniparser_fuzz.c iniparser.c dictionary.c -o iniparser_fuzz
// clang -DNO_MAIN -g -O2 -fsanitize=fuzzer iniparser_fuzz.c iniparser.c dictionary.c -o iniparser_fuzz


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

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
    size_t first_half = (size * 3) / 4;


    FILE *fp = fmemopen((void *)data, first_half, "r");
    if (!fp) {
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
        
        size_t start = (size * 3) / 4;
        const uint8_t *keys_data = data + start;
        size_t keys_len = size - start;
        size_t i = 0;
        size_t max_keys = 64;
        size_t parsed = 0;
        while (i < keys_len && parsed < max_keys) {
            while (i < keys_len && (keys_data[i] == '\n' || keys_data[i] == '\r' || keys_data[i] == '\t' || keys_data[i] == ' ')) i++;
            if (i >= keys_len) break;
            size_t j = i;
            while (j < keys_len && keys_data[j] != '\n' && keys_data[j] != '\r' && keys_data[j] != '\t' && keys_data[j] != ' ') j++;
            size_t tok_len = j - i;
            if (tok_len > 0) {
                if (tok_len > 256) tok_len = 256;
                char *key = (char *)malloc(tok_len + 1);
                if (!key) break;
                memcpy(key, keys_data + i, tok_len);
                key[tok_len] = '\0';
                (void)iniparser_getstring(dict, key, "default");
                (void)iniparser_getint(dict, key, 0);
                (void)iniparser_getboolean(dict, key, 0);
                (void)iniparser_getdouble(dict, key, 0.0);
                free(key);
                parsed++;
            }
            i = j + 1;
        }
    }
    
    fclose(fp);
    
    return 0;
}

#ifndef __AFL_FUZZ_TESTCASE_LEN
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