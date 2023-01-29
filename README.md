
iptables-evil
=============

Evil bit ([RFC 3514](https://www.rfc-editor.org/rfc/rfc3514)) filtering and setting.

Checking other's evilness
-------------------------

Packets can be tested for evilness by using the built-in `u32` module. The evil bit is the bit 15 in the second 32-bit word of the [IPv4 header](https://en.wikipedia.org/wiki/Internet_Protocol_version_4#Header).

IPv6's design is flawed and does not have this incredibly useful bit. However that does not really pose much of a problem since nobody uses IPv6 anyway.

### Drop if evil

To comply with RFC 3514, one can drop all evil packets like:
```bash
iptables -I INPUT -m u32 --u32 "4 & 0x8000 = 0x8000" -j DROP
```

### Accept if good

It is also possible to allow passthrough of all non-evil packets by inverting the condition:
```bash
iptables -I INPUT -m u32 --u32 "4 & 0x8000 = 0x8000" -j DROP
```

### Checking from the application

One can also set the TCP's `SO_MARK` option like so:
```bash
iptables -I INPUT -m u32 --u32 "4 & 0x8000 = 0x8000" -j MARK --set-mark 666
```
These TCP marks can be later checked by the application to test the packet's inherent evilness. I developed an Apache module ([mod_mark](https://github.com/socram8888/mod_mark)) for this very purpose.

Please note that applications will fail to access the Xtables-set marks unless the `tcp_fwmark_accept` flag is set. This change can be made temporarily for testing via:
```bash
sysctl net.ipv4.tcp_fwmark_accept=1
```

If desired, it can be made persistent by creating a configuration file:
```bash
cat <<'EOF' | sudo tee /etc/sysctl.d/50-accept-fwmark.conf
# Allow getsockopt(SO_MARK) to fetch netfilter-assigned marks
net.ipv4.tcp_fwmark_accept = 1
EOF
sudo sysctl -p /etc/sysctl.d/50-accept-fwmark.conf
```

Proclaiming your evilness
-------------------------

IPtables does not have any built-in filter equivalent to `u32` to set arbitrary bits, so you'll need to install the modules and libraries in this repository.

### Installation

The code currently lacks DKMS compilation, so you'll have to manually build it for each kernel upgrade, which is certainly suboptimal.

You'd the kernel headers, the Xtables development headers and a compiler installed. On Debian/Ubuntu these can be installed using:
```bash
sudo apt install linux-headers libxtables-dev build-essential
```

Then you'd need to make and install both the user-land and kernel-land parts:
```bash
cd kernel
make
sudo make install
cd ..

cd user
make
sudo make install
cd ..
```

And that's it.

### Setting the bit

The simplest choice is to set it always. This can be accomplished by adding the a branch to `EVIL` target in the `mangle`'s `POSTROUTING` step:
```bash
iptables -t mangle -A POSTROUTING -j EVIL
```
