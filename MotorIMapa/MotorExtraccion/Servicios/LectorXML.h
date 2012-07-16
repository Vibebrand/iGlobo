/*
 * LectorXML.h
 *
 *  Created on: 23/11/2011
 *      Author: LUIS.RANGEL
 */

#ifndef LECTORXML_H_
#define LECTORXML_H_

#include <stdlib.h>

typedef void (*CallbackFunction)(int tipo, int Depth, int NodeType, const char * name, int IsEmptyElement, int HasValue, int HasAttributes, const char * value);

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

extern void streamFile(const char *filename, CallbackFunction callback );

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* LECTORXML_H_ */
