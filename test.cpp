#include "seh.h"

#include <stdio.h>
#include <stdlib.h>

void main1() {
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

  printf(handler_executed ? "OK\n" : "NOT OK\n");
}

void main2() {
  main1();

  bool handler_executed = false;
  __try {
    int two = atoi("2");
    int result = 1 / two;
  }
  __except(GetExceptionCode() == STATUS_INTEGER_DIVIDE_BY_ZERO ?
	   EXCEPTION_EXECUTE_HANDLER :
	   EXCEPTION_CONTINUE_SEARCH) {
    handler_executed = true;
  }

  printf(handler_executed ? "NOT OK\n" : "OK\n");
}

int main() {
  main2();

  bool handler_executed = false;

  __try {
    __leave;
    int result = 1 / atoi("0");
  }
  __except(GetExceptionCode() == STATUS_INTEGER_DIVIDE_BY_ZERO ?
	   EXCEPTION_EXECUTE_HANDLER :
	   EXCEPTION_CONTINUE_SEARCH) {
    handler_executed = true;
  }

  printf(handler_executed ? "NOT OK\n" : "OK\n");
}
