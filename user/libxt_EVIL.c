
#include <getopt.h>
#include <stdio.h>
#include <xtables.h>

static void markevil_tg_help(void) {
	printf(
		"Evil bit (RFC 3514) setting. It takes no options.\n"
	);
}

static int markevil_tg4_parse(int c, char ** argv, int invert, unsigned int * flags, const void * entry, struct xt_entry_target ** match) {
	return 0;
}

static void markevil_tg_check(unsigned int flags) {
}

static struct xtables_target markevil_tg_reg = {
	.version       = XTABLES_VERSION,
	.name          = "EVIL",
	.revision      = 0,
	.family        = PF_INET,
	.help          = markevil_tg_help,
	.parse         = markevil_tg4_parse,
	.final_check   = markevil_tg_check,
};

static void __attribute__((constructor)) init(void) {
	xtables_register_target(&markevil_tg_reg);
}
