/*
 *	Interval Reminder
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>
#include<signal.h>

#include<X11/Xlib.h>
#include<X11/keysym.h>

long int
parse_interval(const char *s)
{
	long int interval = 0;
	static const long int units[256] = {
		['s'] = 1,
		['m'] = 60,
		['h'] = 3600
	};

	while (*s) {
		char *unit = NULL;
		long int n = strtol(s, &unit, 10);
		if (!units[(int)*unit]) {
			return -1;
		} else {
			interval += n * units[(int)*unit];
		}

		s = unit + 1;
	}
	return interval;
}

Display *gDisplay = NULL;

void
do_exit(int signo) {
	(void)signo;
	XCloseDisplay(gDisplay);
	exit(0);
}

void
do_prompt(Display *display) {
	int screen = DefaultScreen(display);

	Window window = XCreateSimpleWindow(display, DefaultRootWindow(display),
					    0, 0, 320, 240, 0,
					    None,
					    BlackPixel(display, screen));

	XSelectInput(display, window,
		     ExposureMask | KeyPressMask | StructureNotifyMask);

	XSetForeground(display, DefaultGC(display, screen),
		       WhitePixel(display, screen));
	XSetBackground(display, DefaultGC(display, screen),
		       BlackPixel(display, screen));

	XMapWindow(display, window);

	for (int disappear = 0; !disappear;) {
		XEvent event;
		XNextEvent(display, &event);

		if (event.type == Expose) {
			const char *msg = "Press c to continue.";
			XDrawString(display, window, DefaultGC(display, screen),
				    100, 110, msg, strlen(msg));
		} else if (event.type == KeyPress) {
			if (XLookupKeysym((XKeyEvent*)&event, 0) == XK_c) {
				XDestroyWindow(display, window);
			}
		} else if (event.type == DestroyNotify) {
			disappear = 1;
		}
	}

	fputs("window closed, continue waiting...\n", stderr);
	return;
}

int
main(int argc, const char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage:\n\t%s interval\n", argv[0]);
		return -1;
	}

	long int interval = parse_interval(argv[1]);
	if (interval < 0) {
		fprintf(stderr, "Illegal interval %s\n", argv[1]);
		return -1;
	}

	Display *display = XOpenDisplay(NULL);
	if (!display) {
		fputs("Cannot open display\n", stderr);
		return -1;
	}

	gDisplay = display;

	struct sigaction sig = { .sa_handler = do_exit };
	if (sigaction(SIGINT, &sig, NULL)) {
		perror("Failed to register SIGINT handler");
		return -1;
	}

	while (1) {
		sleep(interval);
		do_prompt(display);
	}

	return 0;
}
