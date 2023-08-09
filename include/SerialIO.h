#ifndef SERIALIO_H
#define SERIALIO_H

#include <stdio.h>
#include <stdarg.h>
#include <Print.h>

void SerialPrintf(Print* printable, const char *s, ...);
void SerialPrintf(const char *s, ...);

#endif