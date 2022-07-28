import struct
import os
if __name__ == '__main__':
    filepath='/Users/zong/Code/SLR_Work/DRO/5.bin'
    binfile = open(filepath, 'rb') #打开二进制文件
    size = os.path.getsize(filepath) #获得文件大小
    for i in range(size):
        data = binfile.read(2) #每次输出一个字节
    print(data)
    binfile.close()

