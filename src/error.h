#ifndef _ERROR_H_
#define _ERROR_H_

#include <stdio.h>
#include <stdlib.h>

// Find the specific error to be shown
void detectError(int errorCode, int line, char symbol);

#endif