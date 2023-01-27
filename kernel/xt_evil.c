
#include <linux/ip.h>
#include <linux/module.h>
#include <linux/netfilter/x_tables.h>
#include "xt_evil.h"

static bool evil_mt(const struct sk_buff * skb, struct xt_action_param * par) {
	const struct xt_evil_mtinfo * info = par->matchinfo;
	const struct iphdr * iph = ip_hdr(skb);

	bool is_evil = ntohs(iph->frag_off) & 0x8000;
	return is_evil == info->match_evil;
}

static struct xt_match evil_mt_reg[] __read_mostly = {
	{
		.name      = "evil",
		.revision  = 0,
		.family    = NFPROTO_IPV4,
		.match     = evil_mt,
		.matchsize = XT_ALIGN(sizeof(struct xt_evil_mtinfo)),
		.me        = THIS_MODULE,
	},
};

static int __init evil_mt_init(void) {
	return xt_register_matches(evil_mt_reg, ARRAY_SIZE(evil_mt_reg));
}

static void __exit evil_mt_exit(void) {
	xt_unregister_matches(evil_mt_reg, ARRAY_SIZE(evil_mt_reg));
}

module_init(evil_mt_init);
module_exit(evil_mt_exit);
MODULE_DESCRIPTION("Xtables: evil bit (RFC 3514) matching");
MODULE_LICENSE("GPL");
