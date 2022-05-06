# unix编程

## 1、文件io

### 1）open & close

​	文件描述符：为了一个进程能够操作多个函数

​	`int open(const char *pathname,int flags)`

​	`int open (const char *pathname,int flags,mode);`

​	path:路径—>绝对路径或者相对路径

​	flags:操作权限and 其他设置

​		`O_RDONLY,O_WRONLY,ORDWR` 读写权限

​		`O_CREAT` 创建

​	mode：0777 0775 自己算

### 2）read & write

