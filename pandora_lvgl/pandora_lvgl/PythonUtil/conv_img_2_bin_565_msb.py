# -*- coding: UTF-8 -*-
from PIL import Image as image
from struct import *
import ntpath
import os
import click

def del_file(path):
    ls = os.listdir(path)
    for i in ls:
        c_path = os.path.join(path, i)
        if os.path.isdir(c_path):
            del_file(c_path)
        else:
            os.remove(c_path)
            
@click.command()
@click.option('-d', '--dir', default="picture_resource", prompt='picture resource directory',
              help='Input a directory which contains .jpg image files.')
def conv_img2bin(dir):
    """convert .jpg image file to .bin , format RGB565 MSB first ."""
    print("\n\t<<<Convert .jpg image files to .bin files>>>")
    #create a directory to contain .bin files
    dir_name = ''.join([dir, "_bin"])
    if os.path.exists(dir_name) is True:
        del_file(dir_name) # dir exit, delete all items in the folder
    else:
        os.makedirs(dir_name)  # dir not exit , create
    for root, dirs, files in os.walk(dir):
        for file in files:
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
            print ("<file path>:{:<70} <image Size>:{:<3} x {:<3}".format(file_path,w,h))
            
            #Create the output bin file
            target_file = '{0}{1}{2}'.format("img_" , file.split('.')[0] , ".bin")
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

    print("\n\t<<Generate user_data.bin and header info>>>")
    # if os.path.exists("./test") is True:
        # del_file("./test") # dir exit, delete all items in the folder
    # else:
        # os.makedirs("./test")  # dir not exit , create
        
    user_data_handle = open("user_data.bin", 'wb')  
    user_data_info_handle = open("user_data_info.h", 'w', encoding='utf8')
    
    prev_size = 0
    prev_symbol = "USER_DATA_RES_BASE_ADDR"
    
    for root, dirs, files in os.walk(dir_name):
        for file in files:
            if file.split('.')[1] != "bin":
                print("Warning: {} is not a image bin file!".format(file))
                continue
            file_path = os.path.join(root, file)
            file_size = os.path.getsize(file_path)
            temp_file_handle = open(file_path, 'rb')
            
            user_data_handle.write(temp_file_handle.read())
            print("<file> :{:<50}, <size> :{}".format(file, file_size))
            ##define     IMG_BPMODE_BG_ADDR_BIN    (USER_DATA_RES_BASE_ADDR + 0)
            file_symbol = file.replace('.', '_',1).upper()
            user_data_info_handle.write("#define     {0:<35}    ({1} + {2})\n".format(file_symbol, prev_symbol, prev_size))
            
            prev_size = file_size # save file size of prev file 
            prev_symbol = file_symbol
            
            temp_file_handle.close()
            
    user_data_handle.close()
    
    
if __name__ == '__main__':
    conv_img2bin()