#ifndef _TK_MATRIX_H_
#define _TK_MATRIX_H_

#include "type.h"

/**
 * @brief 3*3µÄ¾ØÕó
 */
typedef struct _matrix33_t {
	float32_t m11;
	float32_t m12;
	float32_t m13;
	float32_t m21;
	float32_t m22;
	float32_t m23;
	float32_t m31;
	float32_t m32;
	float32_t m33;
} matrix33_t;

typedef struct _vector31_t {
	union {
		float32_t v[3];
		struct {
			float32_t x;
			float32_t y;
			float32_t z;
		};
	};
} vector31_t;

typedef union _vector21_t {
	float32_t v[2];
	struct {
		float32_t x;
		float32_t y;
	};
} vector21_t;

typedef struct _screen_point_t {
	int32_t x;
	int32_t y;
} screen_point_t;


#endif // _TK_MATRIX_H_