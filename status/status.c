#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include <wayland-server-core.h>

#include "status.h"

static char                    *s_out;
static size_t                   s_outlen;
static void                   (*s_notify)(void);
static struct wl_event_source  *s_timer;
static const StatusBlock       *s_blocks;
static size_t                   s_nblocks;
static unsigned int             s_interval;

const char *
run_command(const char *cmd)
{
	static char buf[STATUS_BUF];
	FILE *fp;
	char *p;

	fp = popen(cmd, "r");
	if (!fp)
		return NULL;

	p = fgets(buf, sizeof(buf) - 1, fp);
	pclose(fp);

	if (!p)
		return NULL;

	buf[strcspn(buf, "\n")] = '\0';
	return buf[0] ? buf : NULL;
}

const char *
cpu_perc(const char *unused)
{
	static char buf[STATUS_BUF];
	static long double a[7];
	long double b[7], sum;
	FILE *fp;

	memcpy(b, a, sizeof(b));

	fp = fopen("/proc/stat", "r");
	if (!fp)
		return NULL;
	if (fscanf(fp, "%*s %Lf %Lf %Lf %Lf %Lf %Lf %Lf",
	           &a[0], &a[1], &a[2], &a[3], &a[4], &a[5], &a[6]) != 7) {
		fclose(fp);
		return NULL;
	}
	fclose(fp);

	if (b[0] == 0)
		return NULL;

	sum = (b[0]+b[1]+b[2]+b[3]+b[4]+b[5]+b[6]) -
	      (a[0]+a[1]+a[2]+a[3]+a[4]+a[5]+a[6]);

	if (sum == 0)
		return NULL;

	snprintf(buf, sizeof(buf), "%d",
	    (int)(100 * ((b[0]+b[1]+b[2]+b[5]+b[6]) -
	                 (a[0]+a[1]+a[2]+a[5]+a[6])) / sum));
	return buf;
}

const char *
datetime(const char *fmt)
{
	static char buf[STATUS_BUF];
	time_t t = time(NULL);
	if (!strftime(buf, sizeof(buf), fmt, localtime(&t)))
		return NULL;
	return buf;
}

static char                     s_cache[64][STATUS_BUF];
static unsigned int             s_ticks = 0;

static int
tick(void *data)
{
	size_t i, len = 0;
	const char *res;
	int ret;

	s_out[0] = '\0';

	for (i = 0; i < s_nblocks; i++) {
		if (s_blocks[i].interval == 0 || s_ticks % s_blocks[i].interval == 0) {
			res = s_blocks[i].fn(s_blocks[i].arg);
			if (!res)
				res = "n/a";
			strncpy(s_cache[i], res, STATUS_BUF - 1);
			s_cache[i][STATUS_BUF - 1] = '\0';
		}

		ret = snprintf(s_out + len, s_outlen - len,
		               s_blocks[i].fmt, s_cache[i]);
		if (ret < 0 || (size_t)ret >= s_outlen - len)
			break;
		len += (size_t)ret;
	}

	s_notify();
	s_ticks++;
	wl_event_source_timer_update(s_timer, s_interval);
	return 0;
}

void
status_init(struct wl_event_loop *loop, char *out, size_t outlen,
            void (*notify)(void),
            const StatusBlock *blocks, size_t nblocks,
            unsigned int interval_ms)
{
	s_out      = out;
	s_outlen   = outlen;
	s_notify   = notify;
	s_blocks   = blocks;
	s_nblocks  = nblocks;
	s_interval = interval_ms;
	s_timer    = wl_event_loop_add_timer(loop, tick, NULL);
	tick(NULL);
	wl_event_source_timer_update(s_timer, s_interval);
}
