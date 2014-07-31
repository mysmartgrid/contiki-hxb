#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/types.h>
#include <unistd.h>

#undef errno
extern int errno;

int _close(int file) {
	return -1;
}

char *__env[1] = { 0 };
char **environ = __env;

int _fork(void) {
	errno = EAGAIN;
	return -1;
}

int _fstat(int file, struct stat *st) {
	st->st_mode = S_IFCHR;
	return 0;
}

int _getpid(void) {
	return 1;
}

int _isatty(int file) {
	return 1;
}

int _kill(int pid, int sig) {
	errno = EINVAL;
	return -1;
}

int _link(const char *old, const char *new) {
	errno = EMLINK;
	return -1;
}

off_t _lseek(int file, off_t ptr, int dir) {
	return 0;
}

int _open(const char *name, int flags, int mode) {
	return -1;
}

void* _sbrk(ptrdiff_t incr) {
	extern char __heap_start__;
	extern char __heap_end__;

	static char *heap_end;

	char *prev_heap_end;

	if (heap_end == 0) {
		heap_end = &__heap_start__;
	}
	prev_heap_end = heap_end;

	char *stack = &__heap_end__;

	if (heap_end + incr > stack) {
		write(2, "Heap and stack collision", 25);
		errno = ENOMEM;
		return (void*) -1;
	}

	heap_end += incr;
	return (void*) prev_heap_end;
}

int _stat(const char *file, struct stat *st) {
	st->st_mode = S_IFCHR;
	return 0;
}

clock_t _times(struct tms *buf) {
	return -1;
}

int _unlink(const char *name) {
	errno = ENOENT;
	return -1;
}

int _wait(int *status) {
	errno = ECHILD;
	return -1;
}
