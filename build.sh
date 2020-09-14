#!/bin/bash
echo "Deleting old version"
rm anti_rev_auth anti_rev_auth_packed 2>/dev/null
echo "BUILDING anti_rev_auth...."
apt-get install upx
gcc -s -static -o anti_rev_auth anti_rev_auth.c
echo "anti_rev_auth built successfully"
echo "packing anti_rev_auth with upx..."
upx -o anti_rev_auth_packed anti_rev_auth
echo "Successfully packed"
echo "Now you can start using it"
echo "Usage: ./anti_rev_auth_packed"
