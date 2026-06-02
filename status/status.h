#ifndef STATUS_H
#define STATUS_H

#include <stddef.h>
#include <wayland-server-core.h>

#define STATUS_BUF 256

typedef struct {
	const char *(*fn)(const char *);
	const char *fmt;
	const char *arg;
	unsigned int interval;
} StatusBlock;

const char *run_command(const char *cmd);
const char *cpu_perc(const char *unused);
const char *datetime(const char *fmt);

void status_init(struct wl_event_loop *loop, char *out, size_t outlen,
                 void (*notify)(void),
                 const StatusBlock *blocks, size_t nblocks,
                 unsigned int interval_ms);
void status_cleanup(void);

#endif
