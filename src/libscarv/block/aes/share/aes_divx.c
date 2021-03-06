/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#include <scarv/block/aes/aes_divx.h>

#if defined( LIBSCARV_CONF_AES_DIVX_PRECOMP )
uint8_t AES_DIVX[] = { 
  0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 
  0x04, 0x04, 0x05, 0x05, 0x06, 0x06, 0x07, 0x07, 
  0x08, 0x08, 0x09, 0x09, 0x0A, 0x0A, 0x0B, 0x0B, 
  0x0C, 0x0C, 0x0D, 0x80, 0x0E, 0x0E, 0x0F, 0x82, 
  0x10, 0x10, 0x11, 0x11, 0x12, 0x12, 0x13, 0x13, 
  0x14, 0x14, 0x15, 0x15, 0x16, 0x16, 0x17, 0x17, 
  0x18, 0x18, 0x19, 0x19, 0x1A, 0x1A, 0x1B, 0x1B, 
  0x1C, 0x1C, 0x1D, 0x90, 0x1E, 0x1E, 0x1F, 0x92, 
  0x20, 0x20, 0x21, 0x21, 0x22, 0x22, 0x23, 0x23, 
  0x24, 0x24, 0x25, 0x25, 0x26, 0x26, 0x27, 0x27, 
  0x28, 0x28, 0x29, 0x29, 0x2A, 0x2A, 0x2B, 0x2B, 
  0x2C, 0x2C, 0x2D, 0xA0, 0x2E, 0x2E, 0x2F, 0xA2, 
  0x30, 0x30, 0x31, 0x31, 0x32, 0x32, 0x33, 0x33, 
  0x34, 0x34, 0x35, 0x35, 0x36, 0x36, 0x37, 0x37, 
  0x38, 0x38, 0x39, 0x39, 0x3A, 0x3A, 0x3B, 0x3B, 
  0x3C, 0x3C, 0x3D, 0xB0, 0x3E, 0x3E, 0x3F, 0xB2, 
  0x40, 0x40, 0x41, 0x41, 0x42, 0x42, 0x43, 0x43, 
  0x44, 0x44, 0x45, 0x45, 0x46, 0x46, 0x47, 0x47, 
  0x48, 0x48, 0x49, 0x49, 0x4A, 0x4A, 0x4B, 0x4B, 
  0x4C, 0x4C, 0x4D, 0xC0, 0x4E, 0x4E, 0x4F, 0xC2, 
  0x50, 0x50, 0x51, 0x51, 0x52, 0x52, 0x53, 0x53, 
  0x54, 0x54, 0x55, 0x55, 0x56, 0x56, 0x57, 0x57, 
  0x58, 0x58, 0x59, 0x59, 0x5A, 0x5A, 0x5B, 0x5B, 
  0x5C, 0x5C, 0x5D, 0xD0, 0x5E, 0x5E, 0x5F, 0xD2, 
  0x60, 0x60, 0x61, 0x61, 0x62, 0x62, 0x63, 0x63, 
  0x64, 0x64, 0x65, 0x65, 0x66, 0x66, 0x67, 0x67, 
  0x68, 0x68, 0x69, 0x69, 0x6A, 0x6A, 0x6B, 0x6B, 
  0x6C, 0x6C, 0x6D, 0xE0, 0x6E, 0x6E, 0x6F, 0xE2, 
  0x70, 0x70, 0x71, 0x71, 0x72, 0x72, 0x73, 0x73, 
  0x74, 0x74, 0x75, 0x75, 0x76, 0x76, 0x77, 0x77, 
  0x78, 0x78, 0x79, 0x79, 0x7A, 0x7A, 0x7B, 0x7B, 
  0x7C, 0x7C, 0x7D, 0xF0, 0x7E, 0x7E, 0x7F, 0xF2
}; 
#endif
