cmd_/root/os_science/codes/1/main.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -T ./scripts/module-common.lds  --build-id  -o /root/os_science/codes/1/main.ko /root/os_science/codes/1/main.o /root/os_science/codes/1/main.mod.o ;  true