#ifndef COMPRITHMS
#define COMPRITHMS

#include "bitfstreams.h"
#include <iostream>

void mtfEncode(ibitfstream&, obitfstream&);
void mtfDecode(ibitfstream&, obitfstream&);
void huffEncode(ibitfstream&, obitfstream&);
void huffDecode(ibitfstream&, obitfstream&);
void lz77Encode(ibitfstream&, obitfstream&);
void lz77Decode(ibitfstream&, obitfstream&);

#endif