cmd_/root/os_science/codes/5/task1/write_to_disk.ko := ld -r  -EL  -maarch64linux -T ./scripts/module-common.lds -T ./arch/arm64/kernel/module.lds  --build-id  -o /root/os_science/codes/5/task1/write_to_disk.ko /root/os_science/codes/5/task1/write_to_disk.o /root/os_science/codes/5/task1/write_to_disk.mod.o ;  true
