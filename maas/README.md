# How to netboot Mac Minis with MAAS

This was also pain...

This guide is a mainly a copy of this blog [post](https://blog.slys.dev/netbooting-macmini-over-maas/).

## DHCP snippets

With have to add two snippets to MAAS. Go to `Settings` &rarr; `DHCP Settings` and a snippet with
```
authoritative;
```
and one with
```
class "netboot" {
    match if substring (option vendor-class-identifier, 0, 9) = "AAPLBSDPC";
    option dhcp-parameter-request-list 1,3,17,43,60;

    if (option dhcp-message-type = 1) {
        option vendor-class-identifier "AAPLBSDPC";
        option vendor-encapsulated-options
            08:04:81:00:00:89;
    } elsif (option dhcp-message-type = 8) {
        option vendor-class-identifier "AAPLBSDPC";
        if (substring(option vendor-encapsulated-options, 0, 3) = 01:01:01) {
            option vendor-encapsulated-options
              01:01:01:04:02:80:00:07:04:81:00:00:89:09:0e:81:00:00:89:09:54:68:65:2d:49:6d:61:67:65;
        } else {
            option vendor-encapsulated-options
                01:01:02:08:04:81:00:00:89:82:09:54:68:65:2d:49:6d:61:67:65;

            if (substring(option vendor-class-identifier, 10, 4) = "i386") {
                next-server 192.168.111.2;
		filename "mactel64.efi";
            }
        }
    }
}
```
`next-server` has to be the IP of the MAAS server.
`filename` doesn't have to be changed.

## Create EFI

Create `grub.cfg`
```
insmod memdisk
insmod efi_gop
insmod efi_uga
insmod video_bochs
insmod video_cirrus
insmod all_video
set gfxpayload=keep
insmod gzio
insmod part_gpt
insmod ext2
insmod net
insmod efinet
insmod http
insmod linuxefi

net_bootp efinet0
set net_default_interface=efinet0_dhcp
export net_default_interface

set timeout=1
set default=0
set fallback=1
echo 'Loading Linux on Mac...'
echo ${net_default_mac}
set root=http,${net_efinet0_dhcp_next_server}:5248
configfile /grub/grub.cfg-${net_default_mac}
configfile /grub/grub.cfg-default-amd64
```

And create image
```
grub-mkimage -v -d /usr/lib/grub/x86_64-efi/ -O x86_64-efi -p '(tftp)/boot/grub' -o ./mactel64.efi -c ./grub/grub.cfg-mactel.efi normal configfile net efinet tftp http efi_gop efi_uga all_video gzio part_gpt ext2 echo linux linuxefi memdisk eval sfs regexp
```

## The big reveal

Normally one would copy the `mactel64.efi` to `/var/lib/maas/boot-resources/current/` but since we installed MAAS with `snap` (which is total shit) we have to copy it to the snap install

```
sudo cp mactel64.efi /var/snap/maas/common/maas/boot-resources/snapshot-20230412-203732/
```
