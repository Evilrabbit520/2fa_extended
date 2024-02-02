# 2fa_extended (2FA 扩展)
Two Factor Authentication(2fa) extended.

扩展了双因素认证（2FA）

usage (使用方法) :

``` shell
./2fa [Option]... [name]...

./2fa -all
./2fa [-a] addName [-c] [-l] [-n]
./2fa -l
./2fa -n savedName
```

A two-factor key is a short, case-insensitive string consisting of the letters A-Z and the numbers 2-7. 2fa reads dual two-factor keys from standard input or a file.

By default, the key generates a 6-digit code.

-`./2fa -all` can list all saved key token values.

- `./2fa -a name` saves name and its authentication code (the keychain is stored unencrypted in a text file in the application root directory). If `-c` is specified, 2fa will also copy the code to the system clipboard.

- `./2fa -l` lists the names of all keys in the keychain.

- `./2fa -n name` searches the local key file for a given name and prints the two-factor authentication code corresponding to that name. If `-c` is specified, 2fa will also copy the code to the system clipboard.

- Without any arguments, 2fa asks for a time-based key from standard input, thereby printing a two-factor authentication code (prompting whether to save it, and if so, what name to save it with).

The default time-based authentication code is derived from a hash of the key and the current time, so it is important that the system clock is accurate to at least thirty seconds.

双因素密钥是由字母 A-Z 和数字 2-7 组成的不区分大小写的短字符串。2fa 可从标准输入或文件读取双两因素密钥。

默认情况下，密钥生成 6 位代码。

- `./2fa -l` 列出所有保存的密钥令牌的值。

- `./2fa -a name` 保存name及其身份验证代码（钥匙串未加密地存储在文本文件中，位于应用程序根目录中）。如果 `-c` 指定，2fa还会将代码复制到系统剪贴板。

- `./2fa -l` 列出钥匙串中所有钥匙的名称。

- `./2fa -n name` 从给定名称的本地密钥文件中查找打印该名称所对应的双因素身份验证代码。如果 `-c` 指定，2fa还会将代码复制到系统剪贴板。

不带任何参数，2fa要求从标准输入基于时间的密钥，从而打印双因素身份验证代码（过程中会提示是否保存，以及如是的保存名称）。

默认的基于时间的身份验证代码源自密钥和当前时间的哈希值，因此系统时钟的精度至少为三十秒非常重要。

### How to build and use (如何构建) :

`mkdir build` directory.

`mkdir build` 创建 build 目录。

``` shell
cmake..

make

./2fa
```

### Warnings and tips (敬告和提示) :

Please be sure to check your .gitignore or .gitignore_global files before pushing to ensure that they contain your personal key and system configuration file and are not uploaded. These files will not be detected by bots when they perform code reviews.

请您在 push 前务必检查您的 .gitignore 或 .gitignore_global 文件，确保它们包含您的个人密钥和系统配置文件，不被上传。机器人进行代码审查时它们不会检测出这些文件。

