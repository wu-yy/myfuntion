import re

import os
import sys

if __name__=="__main__":
    fopen=open("english","r+")
    lines=fopen.readlines()

    s="\n"
    for line in lines:
        if(line!="\n"):
            line=line.replace("\n"," ")
            line=line.replace("- ","")
            s=s+line
        else:
            s=s+line
    fopen.close()
    f2=open("english","r+")
    f2.truncate()
    f2.close()

    print(s)
    fin=open("result.txt","a+")
    fin.write(s)
    fin.close()

