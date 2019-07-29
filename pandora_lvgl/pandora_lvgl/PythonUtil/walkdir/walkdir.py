from PIL import Image as image
from struct import *
import sys
import ntpath
import os
'''
os.path.abspath(path) #返回绝对路径
os.path.basename(path) #返回文件名
os.path.commonprefix(list) #返回多个路径中，所有path共有的最长的路径。
os.path.dirname(path) #返回文件路径
os.path.exists(path)  #路径存在则返回True,路径损坏返回False
os.path.lexists  #路径存在则返回True,路径损坏也返回True
os.path.expanduser(path)  #把path中包含的"~"和"~user"转换成用户目录
os.path.expandvars(path)  #根据环境变量的值替换path中包含的”$name”和”${name}”
os.path.getatime(path)  #返回最后一次进入此path的时间。
os.path.getmtime(path)  #返回在此path下最后一次修改的时间。
os.path.getctime(path)  #返回path的大小
os.path.getsize(path)  #返回文件大小，如果文件不存在就返回错误
os.path.isabs(path)  #判断是否为绝对路径
os.path.isfile(path)  #判断路径是否为文件
os.path.isdir(path)  #判断路径是否为目录
os.path.islink(path)  #判断路径是否为链接
os.path.ismount(path)  #判断路径是否为挂载点（）
os.path.join(path1[, path2[, ...]])  #把目录和文件名合成一个路径
os.path.normcase(path)  #转换path的大小写和斜杠
os.path.normpath(path)  #规范path字符串形式
os.path.realpath(path)  #返回path的真实路径
os.path.relpath(path[, start])  #从start开始计算相对路径
os.path.samefile(path1, path2)  #判断目录或文件是否相同
os.path.sameopenfile(fp1, fp2)  #判断fp1和fp2是否指向同一文件
os.path.samestat(stat1, stat2)  #判断stat tuple stat1和stat2是否指向同一个文件
os.path.split(path)  #把路径分割成dirname和basename，返回一个元组
os.path.splitdrive(path)   #一般用在windows下，返回驱动器名和路径组成的元组
os.path.splitext(path)  #分割路径，返回路径名和文件扩展名的元组
os.path.splitunc(path)  #把路径分割为加载点与文件
os.path.walk(path, visit, arg)  #遍历path，进入每个目录都调用visit函数，visit函数必须有3个参数(arg, dirname, names)，dirname表示当前目录的目录名，names代表当前目录下的所有文件名，args则为walk的第三个参数
os.path.supports_unicode_filenames  #设置是否支持unicode路径名
'''
#os.path.exists(path)

for root, dirs, files in os.walk("."):
    for file in files:
        if file == "walkdir.py":
            continue
        #print(root) # get dir which file belong to 
        dir_name = root.replace("resource", "bin", 1)
        if os.path.exists(dir_name) is False:
            os.makedirs(dir_name) 
            
        # print(os.path.join(root, file)) # get file path 
        file_path = os.path.join(root, file)
        # Open image
        try:
          img = image.open(file_path)
        except IOError as ioe:
          print ("---ERROR:", ioe )
          print ("---ERROR: Try to convert the image to jpg format")
          continue
          
        (w,h) = img.size 
        data = list(img.getdata())
        print ("Size: ",  w, "x", h)
        
        #Create the output bin file
        target_file = "img_" + file.split('.')[0] + ".bin"
        target_file_path = os.path.join(dir_name, target_file)
        f_bin = open(target_file_path, 'wb')
        
        for px in data:
            try:
                r =  px[0] >> 3
                g =  px[1] >> 2
                b =  px[2] >> 3
                px_out = (r << 11) + (g << 5) + b
                px_out_msb = (px_out&0xFF) << 8 | px_out >> 8
                f_bin.write(pack('<H', px_out_msb))
            except TypeError as te:
                print ("---ERROR:", te )
                print ("---ERROR: Convert the image to jpg format and try again!")
                exit()
                
        f_bin.close()
        
# for root, dirs, files in os.walk("."):
    # for dir in dirs:
        # print(dir) # get dir name
        # print(os.path.join(root, dir)) # get path of dir 
        
# def get_file_path(root_path, file_list, dir_list):
    # # get all file names and dir names 
    # dir_or_files = os.listdir(root_path)
    # for dir_file in dir_or_files:
        # #get path of dir or file 
        # dir_file_path = os.path.join(root_path, dir_file)
        # #if os.path.isfile(dir_file_path):
        # if os.path.isdir(dir_file_path):
            # dir_list.append(dir_file_path)
            # # recursive calling
            # get_file_path(dir_file_path, file_list, dir_list)
        # else:
            # file_list.append(dir_file_path)
            
            
# if __name__ == "__main__":
    # #root path 
    # root_path = "."
    # file_list = []
    # dir_list = []
    # get_file_path(root_path, file_list, dir_list)
    # #print(file_list)
    # for item in file_list:
        # print(item)
    # #print(dir_list)