# -*- coding: UTF-8 -*-
import os
import click


def del_file(dir):
    items = os.listdir(dir)
    for item in items:
        item_path = os.path.join(dir, item)
        if os.path.isdir(item_path): #item is a dir
            del_file(item_path)
            os.rmdir(item_path)
        else: # item is a file
            os.remove(item_path)

@click.command()
@click.option('-d', '--dir',  prompt='delete item in the directory',
              help='del all files in the dir')
def delete_dir(dir):
    del_file(dir)
    #for root, dirs, files in os.walk(dir):

if __name__ == "__main__":
    delete_dir()
    