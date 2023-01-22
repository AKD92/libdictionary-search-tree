/*
 **************************************************************************
 *                                                                        *
 *          General Purpose Hash Function Algorithms Library              *
 *                                                                        *
 * Author: Arash Partow - 2002                                            *
 * URL: http://www.partow.net                                             *
 * URL: http://www.partow.net/programming/hashfunctions/index.html        *
 *                                                                        *
 * Copyright notice:                                                      *
 * Free use of the General Purpose Hash Function Algorithms Library is    *
 * permitted under the guidelines and in accordance with the MIT License. *
 * http://www.opensource.org/licenses/MIT                                 *
 *                                                                        *
 **************************************************************************
*/


#ifndef INCLUDE_GENERALHASHFUNCTION_C_H
#define INCLUDE_GENERALHASHFUNCTION_C_H




typedef unsigned int (*hash_function)(const unsigned char*, unsigned int len);


unsigned int  RSHash   (const unsigned char* str, unsigned int len);
unsigned int  JSHash   (const unsigned char* str, unsigned int len);
unsigned int  PJWHash  (const unsigned char* str, unsigned int len);
unsigned long PJWHash64(const unsigned char* str, unsigned int len);
unsigned int  ELFHash  (const unsigned char* str, unsigned int len);
unsigned int  BKDRHash (const unsigned char* str, unsigned int len);
unsigned int  SDBMHash (const unsigned char* str, unsigned int len);
unsigned int  DJBHash  (const unsigned char* str, unsigned int len);
unsigned int  DEKHash  (const unsigned char* str, unsigned int len);
unsigned int  BPHash   (const unsigned char* str, unsigned int len);
unsigned int  FNVHash  (const unsigned char* str, unsigned int len);
unsigned int  APHash   (const unsigned char* str, unsigned int len);

unsigned int  HashPJW  (const unsigned char* str, unsigned int len);
unsigned long HashPJW64(const unsigned char* str, unsigned int len);

#endif
