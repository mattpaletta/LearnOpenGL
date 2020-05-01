#include "stddef.h"
struct Res {
	const char *data;
	const size_t size;
};
asm(
	".const_data\n"
	".align 8\n"
	"data: .incbin \"/Users/matthew/Projects/LearnOpenGL/breakout/src/sprite.vert\"\n"
	"end_data:\n"
);
extern const char data[];
extern const char end_data[];
struct Res sprite_vert(void) {
	struct Res r = { data, end_data - data };
	return r;
}