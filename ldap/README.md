# How to install LDAP client on our Ubuntu 22.04 Mac Minis
This was pain...

## Install packages

``sudo apt install libnss-ldap libpam-ldap ldap-utils nscd``

- Our URI is ``ldap://kinggeorge.maas`` (*.maas* since we installed our servers with MAAS)
- The DN should be ``dc=ldap,dc=kinggeorge,dc=local``
- LDAP version to use: 3
- Make local root Database admin: Yes
- Does the LDAP database require login? No
- LDAP account for root: ``cn=admin,dc=ldap,dc=kinggeorge,dc=local``
- LDAP root account password: see bitwarden

## Edit ``/etc/nsswitch.conf``

Add ``ldap`` to all entries
``
passwd:         files systemd ldap
group:          files systemd ldap
shadow:         compat ldap
gshadow		files ldap
``

## Edit ``/etc/pam.d/common-session``

Under ``session optional pam_ldap.so`` add
``session optional pam_mkhomedir.so skel=/etc/skel umask=077``

## Edit ``/etc/pam.d/common-password``

Remove ``use_authtok`` for ``pam_ldap.so`` entrie

## Test

``sudo login``

## Install ubuntu desktop

``sudo apt install ubuntu-desktop``
