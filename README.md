# GIM Compiler

## 快速上手
<!-- ### docker 模拟 arm32v7 环境
* 前置条件：已安装 docker

国内可能比较慢需要换源
在 `/etc/docker/daemon.json` 文件中添加 docker 国内镜像源。再用 `sudo systemctl daemon-reload` 和 `sudo systemctl restart docker` 重启一下即可。 -->
<!-- ```json
{
        "registry-mirrors": [
                "https://hub.atomgit.com/"
        ]       
} 
```
[参考文章](https://blog.csdn.net/weixin_44259233/article/details/139507437?utm_medium=distribute.pc_feed_404.none-task-blog-2~default~BlogCommendFromBaidu~PayColumn-1-139507437-blog-null.262^v1^pc_404_mixedpudn&depth_1-utm_source=distribute.pc_feed_404.none-task-blog-2~default~BlogCommendFromBaidu~PayColumn-1-139507437-blog-null.262^v1^pc_404_mixedpud) -->

### cmake 构建
```bash
cmake -Bbuild                                       # 创建 build 文件夹
cd build
make gimc_ir                                        # 构建 ir 样例 
./gimc_ir                                           # 执行输出 llvm 文件
cat tmp_outputIR.ll                                 # 查看输出的 LLVM 代码
llvm-link tmp_outputIR.ll ../IR/lib.ll -S -o out.ll # 生成链接后的 llvm 文件
clang++ out.ll                                      # 生成可执行文件 a.out
./a.out
echo $?                                             # 打印输出
```

