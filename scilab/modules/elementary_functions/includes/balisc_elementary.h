/* Balisc (https://github.com/rdbyk/balisc/)
 * 
 * Copyright (C) 2017 - 2018 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 
 * 02110-1301, USA.
 */
 
#ifndef __BALISC_ELEMENTARY_H__
#define __BALISC_ELEMENTARY_H__

#include <math.h>
#include <sleef.h>

#define balisc_acos_d     Sleef_acos_u35
#define balisc_asin_d     Sleef_asin_u35
#define balisc_atan_d     atan
#define balisc_atan2_d    Sleef_atan2_u35
#define balisc_copysign_d copysign
#define balisc_cos_d      cos
#define balisc_exp_d      exp
#define balisc_fabs_d     fabs
#define balisc_hypot_d    Sleef_hypot_u35
#define balisc_log_d      Sleef_log_u35
#define balisc_log10_d    log10
#define balisc_round_d    round
#define balisc_sin_d      sin
#define balisc_sqrt_d     sqrt
#define balisc_tan_d      tan

#if defined(__SSE4_1__) || defined(__SSE4_2__)

#define balisc_acos_m128d  Sleef_acosd2_u35sse4
#define balisc_asin_m128d  Sleef_asind2_u35sse4
#define balisc_atan_m128d  Sleef_atand2_u35sse4
#define balisc_atan2_m128d Sleef_atan2d2_u35sse4
#define balisc_cos_m128d   Sleef_cosd2_u35sse4
#define balisc_exp_m128d   Sleef_expd2_u10sse4
#define balisc_hypot_m128d Sleef_hypotd2_u35sse4
#define balisc_log_m128d   Sleef_logd2_u35sse4
#define balisc_log10_m128d Sleef_log10d2_u10sse4
#define balisc_sin_m128d   Sleef_sind2_u35sse4
#define balisc_round_m128d Sleef_roundd2_sse4
#define balisc_tan_m128d   Sleef_tand2_u35sse4 // not really fast

#elif defined(__SSE2__)

#define balisc_acos_m128d  Sleef_acosd2_u35sse2
#define balisc_asin_m128d  Sleef_asind2_u35sse2
#define balisc_atan_m128d  Sleef_atand2_u35sse2
#define balisc_atan2_m128d Sleef_atan2d2_u35sse2
#define balisc_cos_m128d   Sleef_cosd2_u35sse2
#define balisc_exp_m128d   Sleef_expd2_u10sse2
#define balisc_hypot_m128d Sleef_hypotd2_u35sse2
#define balisc_log_m128d   Sleef_logd2_u35sse2
#define balisc_log10_m128d Sleef_log10d2_u10sse2
#define balisc_sin_m128d   Sleef_sind2_u35sse2
#define balisc_round_m128d Sleef_roundd2_sse2
#define balisc_tan_m128d   Sleef_tand2_u35sse2 // not really fast

#endif

#if defined(__AVX__)

#define balisc_acos_m256d Sleef_acosd4_u35avx
#define balisc_cos_m256d  Sleef_cosd4_u35avx
#define balisc_sin_m256d  Sleef_sind4_u35avx
#define balisc_tan_m256d  Sleef_tand4_u35avx

#endif

#endif /* __BALISC_ELEMENTARY_H__ */
