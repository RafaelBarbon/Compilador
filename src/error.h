#ifndef _ERROR_H_
#define _ERROR_H_

#include <stdio.h>
#include <stdlib.h>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

// Find the specific error to be shown
char detectError(int errorCode, int line, char symbol,Ui::MainWindow *ui);

#endif
