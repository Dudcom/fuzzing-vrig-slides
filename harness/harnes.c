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