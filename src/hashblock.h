// Copyright (c) 2009-8888 Satoshi Nakamoto
// Copyright (c) 2009-8888 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef HASHBLOCK_H
#define HASHBLOCK_H

#include "uint256.h"
#include "crypto/sph_blake.h"
#include "crypto/sph_bmw.h"
#include "crypto/sph_groestl.h"
#include "crypto/sph_jh.h"
#include "crypto/sph_keccak.h"
#include "crypto/sph_skein.h"
#include "crypto/sph_luffa.h"
#include "crypto/sph_cubehash.h"
#include "crypto/sph_shavite.h"
#include "crypto/sph_simd.h"
#include "crypto/sph_echo.h"
#include "crypto/sph_hamsi.h"
#include "crypto/sph_fugue.h"
#include "crypto/sph_shabal.h"
#include "crypto/sph_whirlpool.h"
#include "crypto/sph_sha2.h"
#include "crypto/sph_haval.h"

#ifndef QT_NO_DEBUG
#include <string>

#endif

#ifdef GLOBALDEFINED
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL sph_blake512_context     z_blake;
GLOBAL sph_bmw512_context       z_bmw;
GLOBAL sph_groestl512_context   z_groestl;
GLOBAL sph_jh512_context        z_jh;
GLOBAL sph_keccak512_context    z_keccak;
GLOBAL sph_skein512_context     z_skein;
GLOBAL sph_luffa512_context     z_luffa;
GLOBAL sph_cubehash512_context  z_cubehash;
GLOBAL sph_shavite512_context   z_shavite;
GLOBAL sph_simd512_context      z_simd;
GLOBAL sph_echo512_context      z_echo;
GLOBAL sph_hamsi512_context     z_hamsi;
GLOBAL sph_fugue512_context     z_fugue;
GLOBAL sph_shabal512_context    z_shabal;
GLOBAL sph_whirlpool_context    z_whirlpool;
GLOBAL sph_sha512_context       z_sha2;
GLOBAL sph_haval256_5_context   z_haval;

#define fillz() do { \
    sph_blake512_init(&z_blake); \
    sph_bmw512_init(&z_bmw); \
    sph_groestl512_init(&z_groestl); \
    sph_jh512_init(&z_jh); \
    sph_keccak512_init(&z_keccak); \
    sph_skein512_init(&z_skein); \
    sph_luffa512_init(&z_luffa); \
    sph_cubehash512_init(&z_cubehash); \
    sph_shavite512_init(&z_shavite); \
    sph_simd512_init(&z_simd); \
    sph_echo512_init(&z_echo); \
    sph_hamsi512_init(&z_hamsi); \
    sph_fugue512_init(&z_fugue); \
    sph_shabal512_init(&z_shabal); \
    sph_whirlpool_init(&z_whirlpool); \
    sph_sha512_init(&z_sha2); \
    sph_haval256_5_init(&z_haval); \
    } while (0) 

#define ZBLAKE (memcpy(&ctx_blake, &z_blake, sizeof(z_blake)))
#define ZBMW (memcpy(&ctx_bmw, &z_bmw, sizeof(z_bmw)))
#define ZGROESTL (memcpy(&ctx_groestl, &z_groestl, sizeof(z_groestl)))
#define ZJH (memcpy(&ctx_jh, &z_jh, sizeof(z_jh)))
#define ZKECCAK (memcpy(&ctx_keccak, &z_keccak, sizeof(z_keccak)))
#define ZSKEIN (memcpy(&ctx_skein, &z_skein, sizeof(z_skein)))
#define ZWHIRLPOOL (memcpy(&ctx_whirlpool, &z_whirlpool, sizeof(z_whirlpool)))
#define ZFUGUE (memcpy(&ctx_fugue, &z_fugue, sizeof(z_fugue)))
#define ZHAMSI (memcpy(&ctx_hamsi, &z_hamsi, sizeof(z_hamsi)))
#define ZSHABAL (memcpy(&ctx_shabal, &z_shabal, sizeof(z_shabal))
#define ZSHA2 (memcpy(&ctx_sha2, &z_sha2, sizeof(z_sha2)))
#define ZHAVAL (memcpy(&ctx_haval, &z_haval, sizeof(z_haval)))

template<typename T1>
inline uint256 HMQ1725(const T1 pbegin, const T1 pend)

{
    sph_blake512_context     ctx_blake;
    sph_bmw512_context       ctx_bmw;
    sph_groestl512_context   ctx_groestl;
    sph_jh512_context        ctx_jh;
    sph_keccak512_context    ctx_keccak;
    sph_skein512_context     ctx_skein;
    sph_luffa512_context      ctx_luffa;
    sph_cubehash512_context   ctx_cubehash;
    sph_shavite512_context    ctx_shavite;
    sph_simd512_context       ctx_simd;
    sph_echo512_context       ctx_echo;
    sph_hamsi512_context      ctx_hamsi;
    sph_fugue512_context      ctx_fugue;
    sph_shabal512_context     ctx_shabal;
    sph_whirlpool_context     ctx_whirlpool;
    sph_sha512_context        ctx_sha2;
    sph_haval256_5_context    ctx_haval;
    
    static unsigned char pblank[1];

#ifndef QT_NO_DEBUG
#endif
    uint512 mask = 24;
    uint512 zero = 0;
    
    uint512 hash[25];
    
    sph_bmw512_init(&ctx_bmw);
    sph_bmw512 (&ctx_bmw, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[0]));

    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool (&ctx_whirlpool, static_cast<const void*>(&hash[0]), 64);
    sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[1]));

    if ((hash[1] & mask) != zero)
    {
        sph_groestl512_init(&ctx_groestl);
        sph_groestl512 (&ctx_groestl, static_cast<const void*>(&hash[1]), 64);
        sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[2]));
    }
    else
    {
        sph_skein512_init(&ctx_skein);
        sph_skein512 (&ctx_skein, static_cast<const void*>(&hash[1]), 64);
        sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[2]));
    }


    sph_jh512_init(&ctx_jh);
    sph_jh512 (&ctx_jh, static_cast<const void*>(&hash[2]), 64);
    sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[3]));
    
    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, static_cast<const void*>(&hash[3]), 64);
    sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[4]));

if ((hash[4] & mask) != zero)
    {
        sph_blake512_init(&ctx_blake);
        sph_blake512 (&ctx_blake, static_cast<const void*>(&hash[4]), 64);
        sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[5]));
    }
    else
    {
        sph_bmw512_init(&ctx_bmw);
        sph_bmw512 (&ctx_bmw, static_cast<const void*>(&hash[4]), 64);
        sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[5]));
    }

    sph_luffa512_init(&ctx_luffa);
    sph_luffa512 (&ctx_luffa, static_cast<void*>(&hash[5]), 64);
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[6]));
    
    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512 (&ctx_cubehash, static_cast<const void*>(&hash[6]), 64);
    sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[7]));
 
if ((hash[7] & mask) != zero)
    {
        sph_keccak512_init(&ctx_keccak);
        sph_keccak512 (&ctx_keccak, static_cast<const void*>(&hash[7]), 64);
        sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[8]));
    }
    else
    {
        sph_jh512_init(&ctx_jh);
        sph_jh512 (&ctx_jh, static_cast<const void*>(&hash[7]), 64);
        sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[8]));
    }

    sph_shavite512_init(&ctx_shavite);
    sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[8]), 64);
    sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[9]));
        
    sph_simd512_init(&ctx_simd);
    sph_simd512 (&ctx_simd, static_cast<const void*>(&hash[9]), 64);
    sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[10]));

if ((hash[10] & mask) != zero)
    {
    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool (&ctx_whirlpool, static_cast<const void*>(&hash[10]), 64);
    sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[11]));
    }
    else
    {
    sph_haval256_5_init(&ctx_haval);
    sph_haval256_5 (&ctx_haval, static_cast<const void*>(&hash[10]), 64);
    sph_haval256_5_close(&ctx_haval, static_cast<void*>(&hash[11]));
    }

    sph_echo512_init(&ctx_echo);
    sph_echo512 (&ctx_echo, static_cast<const void*>(&hash[11]), 64);
    sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[12]));

    sph_blake512_init(&ctx_blake);
    sph_blake512 (&ctx_blake, static_cast<const void*>(&hash[12]), 64);
    sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[13]));

if ((hash[13] & mask) != zero)
    {
    sph_shavite512_init(&ctx_shavite);
    sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[13]), 64);
    sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[14]));
    }
    else
    {
    sph_luffa512_init(&ctx_luffa);
    sph_luffa512 (&ctx_luffa, static_cast<void*>(&hash[13]), 64);
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[14]));
    }

    sph_hamsi512_init(&ctx_hamsi);
    sph_hamsi512 (&ctx_hamsi, static_cast<const void*>(&hash[14]), 64);
    sph_hamsi512_close(&ctx_hamsi, static_cast<void*>(&hash[15]));

    sph_fugue512_init(&ctx_fugue);
    sph_fugue512 (&ctx_fugue, static_cast<const void*>(&hash[15]), 64);
    sph_fugue512_close(&ctx_fugue, static_cast<void*>(&hash[16]));

if ((hash[16] & mask) != zero)
    {
    sph_echo512_init(&ctx_echo);
    sph_echo512 (&ctx_echo, static_cast<const void*>(&hash[16]), 64);
    sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[17]));
    }
    else
    {
    sph_simd512_init(&ctx_simd);
    sph_simd512 (&ctx_simd, static_cast<const void*>(&hash[16]), 64);
    sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[17]));
    }

    sph_shabal512_init(&ctx_shabal);
    sph_shabal512 (&ctx_shabal, static_cast<const void*>(&hash[17]), 64);
    sph_shabal512_close(&ctx_shabal, static_cast<void*>(&hash[18]));

    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool (&ctx_whirlpool, static_cast<const void*>(&hash[18]), 64);
    sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[19]));

if ((hash[19] & mask) != zero)
    {
    sph_fugue512_init(&ctx_fugue);
    sph_fugue512 (&ctx_fugue, static_cast<const void*>(&hash[19]), 64);
    sph_fugue512_close(&ctx_fugue, static_cast<void*>(&hash[20]));
    }
    else
    {
    sph_sha512_init(&ctx_sha2);
    sph_sha512 (&ctx_sha2, static_cast<const void*>(&hash[19]), 64);
    sph_sha512_close(&ctx_sha2, static_cast<void*>(&hash[20]));
    }

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, static_cast<const void*>(&hash[20]), 64);
    sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[21]));

    sph_sha512_init(&ctx_sha2);
    sph_sha512 (&ctx_sha2, static_cast<const void*>(&hash[21]), 64);
    sph_sha512_close(&ctx_sha2, static_cast<void*>(&hash[22]));

if ((hash[22] & mask) != zero)
    {
    sph_haval256_5_init(&ctx_haval);
    sph_haval256_5 (&ctx_haval, static_cast<const void*>(&hash[22]), 64);
    sph_haval256_5_close(&ctx_haval, static_cast<void*>(&hash[23]));
    }
    else
    {
    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool (&ctx_whirlpool, static_cast<const void*>(&hash[22]), 64);
    sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[23]));
    }

    sph_bmw512_init(&ctx_bmw);
    sph_bmw512 (&ctx_bmw, static_cast<const void*>(&hash[23]), 64);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[24]));

    return hash[24].trim256();
}

#endif // HASHBLOCK_H
