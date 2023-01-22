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


#include "general_hash_functions.h"
#include <limits.h>


unsigned int RSHash(const unsigned char* str, unsigned int len)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = hash * a + (*str);
      a    = a * b;
   }

   return hash;
}
/* End Of RS Hash Function */


unsigned int JSHash(const unsigned char* str, unsigned int len)
{
   unsigned int hash = 1315423911;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash ^= ((hash << 5) + (*str) + (hash >> 2));
   }

   return hash;
}
/* End Of JS Hash Function */


unsigned int PJWHash(const unsigned char* str, unsigned int len)
{
   const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
   const unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
   const unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
   const unsigned int HighBits          = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
   unsigned int hash              = 0;
   unsigned int test              = 0;
   unsigned int i                 = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = (hash << OneEighth) + (*str);

      if((test = hash & HighBits)  != 0)
      {
         hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
      }
   }

   return hash;
}
/* End Of  P. J. Weinberger Hash Function */

// 64-bit variant of PJWHash
unsigned long PJWHash64(const unsigned char* str, unsigned int len)
{
  const unsigned long BitsInUnsignedLong = (unsigned long)(sizeof(unsigned long) * 8);
  const unsigned long ThreeQuarters      = (unsigned long)((BitsInUnsignedLong  * 3) / 4);
  const unsigned long OneEighth          = (unsigned long)(BitsInUnsignedLong / 8);
  const unsigned long HighBits           = (unsigned long)(0xFFFFFFFF) << (BitsInUnsignedLong - OneEighth);
  unsigned long hash              = 0;
  unsigned long test              = 0;
  unsigned long i                 = 0;

  for(i = 0; i < len; str++, i++)
    {
      hash = (hash << OneEighth) + (*str);

      if((test = hash & HighBits) != 0)
        {
          hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

  return hash;
}

// Alternative implementation from http://www.drdobbs.com/database/hashing-rehashed/184409859.
#define BITS_IN_int     ( sizeof(int) * CHAR_BIT )
#define THREE_QUARTERS  ((int) ((BITS_IN_int * 3) / 4))
#define ONE_EIGHTH      ((int) (BITS_IN_int / 8))
#define HIGH_BITS       ( ~((unsigned int)(~0) >> ONE_EIGHTH ))
unsigned int HashPJW(const unsigned char* str, unsigned int len)
{
    unsigned int i          = 0;
    unsigned int hash_value = 0;
    unsigned int tmp;
    for(i = 0; i < len; str++, i++)
    {
        hash_value = ( hash_value << ONE_EIGHTH ) + *str;
        if (( tmp = hash_value & HIGH_BITS ) != 0 )
            hash_value =
                ( hash_value ^ ( tmp >> THREE_QUARTERS )) &
                        ~HIGH_BITS;
    }
    return ( hash_value );
}

// 64-bit variant of HashPJW.
#define BITS_IN_long     ( sizeof(long) * CHAR_BIT )
#define THREE_QUARTERS_LONG  ((int) ((BITS_IN_long * 3) / 4))
#define ONE_EIGHTH_LONG      ((int) (BITS_IN_long / 8))
#define HIGH_BITS_LONG       ( ~((unsigned long)(~0L) >> ONE_EIGHTH_LONG ))
unsigned long HashPJW64(const unsigned char* str, unsigned int len)
{
    unsigned long i          = 0;
    unsigned long hash_value = 0;
    unsigned long tmp;
    for(i = 0; i < len; str++, i++)
    {
        hash_value = ( hash_value << ONE_EIGHTH_LONG ) + *str;
        if (( tmp = hash_value & HIGH_BITS_LONG ) != 0 )
            hash_value =
                ( hash_value ^ ( tmp >> THREE_QUARTERS_LONG )) &
                        ~HIGH_BITS_LONG;
    }
    return ( hash_value );
}


unsigned int ELFHash(const unsigned char* str, unsigned int len)
{
   unsigned int hash = 0;
   unsigned int x    = 0;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = (hash << 4) + (*str);
      if((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }
      hash &= ~x;
   }

   return hash;
}
/* End Of ELF Hash Function */


unsigned int BKDRHash(const unsigned char* str, unsigned int len)
{
   unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
   unsigned int hash = 0;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = (hash * seed) + (*str);
   }

   return hash;
}
/* End Of BKDR Hash Function */


unsigned int SDBMHash(const unsigned char* str, unsigned int len)
{
   unsigned int hash = 0;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = (*str) + (hash << 6) + (hash << 16) - hash;
   }

   return hash;
}
/* End Of SDBM Hash Function */


unsigned int DJBHash(const unsigned char* str, unsigned int len)
{
   unsigned int hash = 5381;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = ((hash << 5) + hash) + (*str);
   }

   return hash;
}
/* End Of DJB Hash Function */


unsigned int DEKHash(const unsigned char* str, unsigned int len)
{
   unsigned int hash = len;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
   }
   return hash;
}
/* End Of DEK Hash Function */


unsigned int BPHash(const unsigned char* str, unsigned int len)
{
   unsigned int hash = 0;
   unsigned int i    = 0;
   for(i = 0; i < len; str++, i++)
   {
      hash = hash << 7 ^ (*str);
   }

   return hash;
}
/* End Of BP Hash Function */


unsigned int FNVHash(const unsigned char* str, unsigned int len)
{
   const unsigned int fnv_prime = 0x811C9DC5;
   unsigned int hash      = 0;
   unsigned int i         = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash *= fnv_prime;
      hash ^= (*str);
   }

   return hash;
}
/* End Of FNV Hash Function */


unsigned int APHash(const unsigned char* str, unsigned int len)
{
   unsigned int hash = 0xAAAAAAAA;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ (*str) * (hash >> 3)) :
                               (~((hash << 11) + ((*str) ^ (hash >> 5))));
   }

   return hash;
}
/* End Of AP Hash Function */
