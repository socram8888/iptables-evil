
#include <getopt.h>
#include <stdio.h>
#include <xtables.h>
#include "xt_evil.h"

static const struct option evil_mt_opts[] = {
	{ .name = "evil", .val = 'e' },
	{ NULL },
};

static void evil_mt_help(void) {
	printf(
		"Evil bit (RFC 3514) packet filtering:\n"
		"[!] --evil                      match evil packets\n"
	);
}

static int evil_mt_parse(int c, char ** argv, int invert, unsigned int * flags, const void * entry, struct xt_entry_match ** match) {
	struct xt_evil_mtinfo* info = (void *) (*match)->data;

	switch (c) {
		case 'e':
			if (*flags != 0) {
				xtables_error(PARAMETER_PROBLEM, "--evil specified multiple times");
				return 0;
			}

			*flags = 1;
			info->match_evil = !invert;
			return 1;

	}

	return 0;
}

static void evil_mt_check(unsigned int flags) {
	if (flags == 0) {
		xtables_error(PARAMETER_PROBLEM, "xt_evil: [!] --evil not specified.");
	}
}

static void evil_mt_save(const void * entry, const struct xt_entry_match * match) {
	const struct xt_evil_mtinfo *info = (const void *) match->data;

	if (!info->match_evil) {
		printf(" !");
	}

	printf(" --evil ");
}

static void evil_mt_print(const void * entry, const struct xt_entry_match * match, int numeric) {
	printf(" -m evil");
	evil_mt_save(entry, match);
}

static struct xtables_match evil_mt_reg = {
	.version       = XTABLES_VERSION,
	.name          = "evil",
	.revision      = 0,
	.family        = PF_INET,
	.size          = XT_ALIGN(sizeof(struct xt_evil_mtinfo)),
	.userspacesize = XT_ALIGN(sizeof(struct xt_evil_mtinfo)),
	.extra_opts    = evil_mt_opts,
	/* called when user execs "iptables -m evil -h" */
	.help          = evil_mt_help,
	/* called when user enters new rule */
	.parse         = evil_mt_parse,
	/* last chance for sanity checks after parse. */
	.final_check   = evil_mt_check,
	/* called when user execs "iptables -L" */
	.print         = evil_mt_print,
	/* called when user execs "iptables-save" */
	.save          = evil_mt_save,
};

static void _init(void) {
	xtables_register_match(&evil_mt_reg);
}
