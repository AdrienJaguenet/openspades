/*
 Copyright (c) 2013 yvt
 
 This file is part of OpenSpades.
 
 OpenSpades is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 OpenSpades is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with OpenSpades.  If not, see <http://www.gnu.org/licenses/>.
 
 */

#pragma once

#include <Core/CpuID.h>

#if defined(__i386__) || defined(_M_IX86)
#define ENABLE_MMX	0 // FIXME: move this to the proper place
#define ENABLE_SSE	1 // FIXME: move this to the proper place
#define ENABLE_SSE2	1 // FIXME: move this to the proper place
#endif

#if ENABLE_SSE
#include <xmmintrin.h>
#endif
#if ENABLE_SSE2
#include <emmintrin.h>
#endif

#include <algorithm>
#include <Core/ConcurrentDispatch.h>
#include <Core/Debug.h>

namespace spades {
	namespace draw {
		enum class SWFeatureLevel {
			None,
#if ENABLE_MMX
			MMX,
#endif
#if ENABLE_SSE
			SSE,
#endif
#if ENABLE_SSE2
			SSE2,
#endif
		};
		
		static inline bool operator > (SWFeatureLevel a, SWFeatureLevel b) {
			return static_cast<int>(a) > static_cast<int>(b);
		}
		static inline bool operator >= (SWFeatureLevel a, SWFeatureLevel b) {
			return static_cast<int>(a) >= static_cast<int>(b);
		}
		
		SWFeatureLevel DetectFeatureLevel();
		
		
#if ENABLE_SSE // assume SSE availability (no checks!)
		static inline float fastDiv(float a, float b) {
			union {
				float tmp;
				__m128 mtmp;
			};
			tmp = b;
			mtmp = _mm_rcp_ss(mtmp);
			return a * tmp;
		}
		static inline float fastRcp(float b) {
			union {
				float tmp;
				__m128 mtmp;
			};
			tmp = b;
			mtmp = _mm_rcp_ss(mtmp);
			return tmp;
		}
		static inline float fastRSqrt(float v) {
			union {
				float tmp;
				__m128 mtmp;
			};
			tmp = v;
			mtmp = _mm_rsqrt_ss(mtmp);
			return tmp;
		}
#else
		static inline float fastDiv(float a, float b) {
			return a / b;
		}
		static inline float fastRcp(float b) {
			return 1.f / b;
		}
		static inline float fastRSqrt(float b) {
			return 1.f / sqrtf(b);
		}
#endif
		
		
	}
}