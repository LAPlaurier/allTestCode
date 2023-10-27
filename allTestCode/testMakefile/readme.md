### 学习makefile的使用

make 和 makefile 搭配进行 **自动化编译**
makefile 是一个**工程文件的编译规则**，记录了原始码如何编译的详细信息、**描述了整个工程的编译链接规则**。
make 是一个**命令工具**，解释makefile中的指令

makefile语法：
```c
target（目标文件）: 文件1 文件2（依赖文件列表）     // 依赖关系
<Tab>  gcc -o 欲建立的执行文件 目标文件1 目标文件2  // 依赖方法
    command
```

##### 理解依赖关系和依赖方法
只有依赖文件存在，才能有目标文件。通过依赖文件产生目标文件的方法就是依赖方法。

在<u>依赖关系</u>中，若是目标文件依赖的文件不存在，就将这个<u>依赖方法</u>入栈，转到下一组依赖关系。直到找到一条依赖关系，该关系中目标文件的依赖文件存在。此时开始出栈，依次执行依赖方法[1]。所以Makefile的规则看起来是反着的。


##### 伪目标
`.PHONY` 是一个伪目标，Makefile中将 `.PHONY` 放在一个目标前指明这个目标是 [伪文件目标]。作用是防止在Makefile中 定义的执行命令的目标 和 工作目录下的实际文件 出现名字冲突[3]。
如果不用 `.PHONY` 指明clean是伪目标，当目录中有名为clean的文件时，make clean命令失效。


##### make工作原理
make扫描Makefile文件时，默认执行**第一组**依赖关系和依赖方法。

**多次执行make指令不会重复执行的原理**：make比较 依赖文件 与 目标文件 的生成时间，判断依赖文件是否修改过，是否要重新生成[1]。
（可以使用`stat`指令查看文件的ACM时间，一般是比较Modify时间）




[1]:https://juejin.cn/post/7205777393453170748
[2]:https://juejin.cn/post/7279295129348751418
[3]:https://blog.csdn.net/qq_41709234/article/details/123968462?ops_request_misc=&request_id=&biz_id=102&utm_term=.PHONY&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-123968462.nonecase&spm=1018.2226.3001.4187