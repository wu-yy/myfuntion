import os
import sys
import xlrd

import xlsxwriter

class XLW :
    def __init__(self,filename,worksheet):
        self.book = xlsxwriter.Workbook(filename)
        self.sh = self.book.add_worksheet(worksheet)
        self.idx =0


    def write_column (self,values):
        col =0
        # 写入一行文件
        for i in values:
            self.sh.write(self.idx, col, i)
            col +=1
        self.idx +=1

    def save(self):
        self.book.close()

