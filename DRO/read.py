import struct
import os
test  = '';
if __name__ == '__main__':
    filepath='/Users/zong/Code/unix/DRO/DataHandle/220723175319_0001_0587_00_00_6D1D_2048_1B1B_0000000000000000.bin'
    binfile = open(filepath, 'rb') #打开二进制文件
    size = os.path.getsize(filepath) #获得文件大小
    for i in range(size):
        data = binfile.read(2) #每次输出一个字节
        data = str(data)
        test += data;
    binfile.close()
    print(test)

