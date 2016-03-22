#ifndef _INCLUDE_SPP_H_
#define _INCLUDE_SPP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
#include <io.h>
static int setenv( const char *k, const char *v, int overwrite ) {
       char buf[128];
       sprintf(buf,"%s=%s", k, getenv(k) && (!overwrite) ? (const char *)getenv(k) : v );
       _putenv(buf);
       return 0;
}
#define popen    _popen
#define pclose   _pclose
#define srandom  srand
#define snprintf _snprintf
#endif

#define VERSION "1.0"

#define MAXIFL 128

extern int ifl;
extern int echo[MAXIFL];
extern int lineno;

#define GET_ARG(x,y,i) if (y[i][2]) x = y[i]+2; else x = y[++i]

#define DEFAULT_PROC(x) \
struct Tag *tags = (struct Tag *)&x##_tags; \
struct Arg *args = (struct Arg *)&x##_args; \
struct Proc *proc = &x##_proc;

#define ARG_CALLBACK(x) int x (char *arg)
/* XXX swap arguments ?? */
#define TAG_CALLBACK(x) int x (char *buf, FILE *out)
#define PUT_CALLBACK(x) int x (FILE *out, char *buf)
#define IS_SPACE(x) ((x==' ')||(x=='\t')||(x=='\r')||(x=='\n'))

struct Tag {
	const char *name;
	TAG_CALLBACK((*callback));
};

struct Arg {
	const char *flag;
	const char *desc;
	int has_arg;
	ARG_CALLBACK((*callback));
};

struct Proc {
	const char *name;
	struct Tag **tags;
	struct Arg **args;
	TAG_CALLBACK ((*eof));
	PUT_CALLBACK ((*fputs));
	char *tag_pre;
	char *tag_post;
	char *token;
	char *multiline;
	int chop;
	int tag_begin;
	int default_echo;
};

int spp_file(const char *file, FILE *out);
void spp_run(char *buf, FILE *out);
void spp_eval(char *buf, FILE *out);
void spp_io(FILE *in, FILE *out);

void spp_proc_list();
void spp_proc_list_kw();
void spp_proc_set(struct Proc *p, char *arg, int fail);

#if DEBUG
#define D if (1)
#else
#define D if (0)
#endif

#endif
