read -p "Input password: " password
dd if=pass.des3 | openssl des3 -d -k $password | dd of=pass.tar.gz
tar -zxvf pass.tar.gz
mv .ssh ~/.ssh
rm -f pass.tar.gz
