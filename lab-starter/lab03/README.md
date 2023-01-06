## Note

```
java -jar tools/venus.jar . -dm
```


* `srli`和`srai`的区别 - 符号位

* 没有`>=`或者`<=` - 最小化指令集

* 函数调用
    * 需要把参数存放在`a{x}`
    * 需要保存当前的上下文 - 存到栈`stack`里
    * 需要记住`pc`的位置

* `jal rd offset` / `jalr rd rs (offset)`
    * 两种改变pc的办法
    * rd <- pc+4
    * pc <- pc+offset / pc <- rs+offset
    * 如果`rd`不是`x0`, 一定要记得保存到栈里

* 函数返回
    * 返回值放在`a0` - lab里也建议开始就放在a0
    * 释放栈的空间, 还原上一层的params & local variable
    * pc <- rd
