//
// Created by ryan on 28/06/23.
//

#ifndef UART_H
#define UART_H

#include "hw_types.h"
#include "bbb_regs.h"

void putCh(char c);
char getCh();
int putString(char *str, unsigned int length);
int getString(char *buf, unsigned int length);

#endif //UART_H
