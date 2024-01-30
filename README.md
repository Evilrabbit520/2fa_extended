# 2fa_extended
Two Factor Authentication(2fa) extended.

usage:

``` shell
./2fa [Option]... [name]...

./2fa [-a] addName [-c] [-l] [-n]
./2fa -l
./2fa -n savedName
```

A two-factor key is a short, case-insensitive string consisting of the letters A-Z and the numbers 2-7. 2fa reads dual two-factor keys from standard input or a file.

By default, the key generates a 6-digit code.

- `./2fa -a name` saves name and its authentication code (the keychain is stored unencrypted in a text file in the application root directory). If `-c` is specified, 2fa will also copy the code to the system clipboard.

- `./2fa -l` lists the names of all keys in the keychain.

- `./2fa -n name` searches the local key file for a given name and prints the two-factor authentication code corresponding to that name. If `-c` is specified, 2fa will also copy the code to the system clipboard.

- Without any arguments, 2fa asks for a time-based key from standard input, thereby printing a two-factor authentication code (prompting whether to save it, and if so, what name to save it with).

The default time-based authentication code is derived from a hash of the key and the current time, so it is important that the system clock is accurate to at least thirty seconds.

### How to build and use

`mkdir build` directory.

``` shell
cmake..

make

./2fa
```