
#include <linux/ip.h>
#include <linux/module.h>
#include <linux/netfilter/x_tables.h>

static unsigned int markevil_tg(struct sk_buff * skb, const struct xt_action_param * par) {
	struct iphdr * iph;
	__be16 orig_frag;

	if (skb_ensure_writable(skb, sizeof(*iph))) {
		return NF_DROP;
	}

	iph = ip_hdr(skb);
	orig_frag = iph->frag_off;
	iph->frag_off = orig_frag | htons(0x8000);
	csum_replace2(&iph->check, orig_frag, iph->frag_off);

	return XT_CONTINUE;
}

static struct xt_target markevil_tg_reg[] __read_mostly = {
	{
		.name      = "EVIL",
		.revision  = 0,
		.family    = NFPROTO_IPV4,
		.target    = markevil_tg,
		.me        = THIS_MODULE,
	},
};

static int __init markevil_tg_init(void) {
	return xt_register_targets(markevil_tg_reg, ARRAY_SIZE(markevil_tg_reg));
}

static void __exit markevil_tg_exit(void) {
	xt_unregister_targets(markevil_tg_reg, ARRAY_SIZE(markevil_tg_reg));
}

module_init(markevil_tg_init);
module_exit(markevil_tg_exit);
MODULE_DESCRIPTION("Xtables: evil bit (RFC 3514) setting");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_MARKEVIL");
