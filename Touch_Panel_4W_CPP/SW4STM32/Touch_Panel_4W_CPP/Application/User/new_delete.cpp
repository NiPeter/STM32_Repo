/*
 * NewDelete.cpp
 *
 *  Created on: 17 sie 2017
 *      Author: Peter
 */

#include <stddef.h>
#include "cmsis_os.h"

void *operator new(size_t size) {
  return pvPortMalloc(size);
}

void *operator new[](size_t size) {
  return pvPortMalloc(size);
}

void operator delete(void *p) {
	vPortFree(p);
}

void operator delete[](void *p) {
  vPortFree(p);
}
