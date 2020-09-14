# anti_rev_auth


Simple authentication program simulation with several anti-reversing techniques.
1) The indirect calls are used to erase xrefs in IDA/ghidra/etc.
2) This program detects the debuggers
3) The binary file is stripped and packed with upx packer.

# How to build

``` 
git clone https://github.com/ChristophCadavercian/anti_rev_auth/

chmod +x build.sh

./build.sh 
```


