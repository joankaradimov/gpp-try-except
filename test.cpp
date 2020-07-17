#include "seh.h"
#include <stdio.h>

int main() {
  bool handler_executed = false;
  __try {
    int zero = atoi("0");
    int result = 1 / zero;
  }
  __except(GetExceptionCode() == STATUS_INTEGER_DIVIDE_BY_ZERO ?
	   EXCEPTION_EXECUTE_HANDLER :
	   EXCEPTION_CONTINUE_SEARCH) {
    handler_executed = true;
  }
  __except_end

  printf("%d\n", handler_executed);
}
