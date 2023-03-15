# Reliable Transfer Protocol Battle
对可靠传输协议进行比较
# 编译
udt的编译需要安装libudt.so
```bash
make
```
# tcp传输测试
```bash
# 服务端
cd tcp
./appserver_tcp 9000

# 客户端
./appclient_tcp localhost 9000 5
```
# udt传输测试
```bash
# 服务端
cd udt
./appserver_udt

# 客户端
./appclient_udt localhost 9000
```

# 清理
```bash
make clean
```