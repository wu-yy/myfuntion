编译 binary simples
nvcc .o

	nflags: 

 	 -std=c++14 -Xcompiler -fPIC -Xcompiler -march=native  -Xcompiler -fdiagnostics-color=always  -I/home/wuyongyu/leetcode/leetcode/src  -DHAS_CUDA -I'/usr/local/cuda/include'  -O2  -x cu --cudart=shared -ccbin='/usr/bin/g++'        --use_fast_math  -w  -I'/home/wuyongyu/leetcode/leetcode/extern/cuda/inc'

   cc: /usr/local/cuda/bin/nvcc


g++ .o
	nflags :
 	-Wall -Werror -Wunused-function -Wno-unknown-pragmas -std=c++14
    -fPIC -march=native  -fdiagnostics-color=always  -I/home/w
    uyongyu/leetcode/leetcode/src  -DHAS_CUDA -I'/usr/local/cuda/include'  -O2
	cc : g++

lto_flags: 

input : files
obe_files: output files

运行: f"{cc} {input} {nflags} -c {lto_flags} -o {obj_file}"

   


编译 .so
link: -lstdc++ -ldl -shared  -lcudart -L'/usr/local/cuda/lib64'

lto_flags:
flags:
  -Wall -Werror -Wunused-function -Wno-unknown-pragmas -std=c++14 -f
    PIC -march=native  -fdiagnostics-color=always -I/home/wuy
    ongyu/leetcode/leetcode/src  -DHAS_CUDA -I'/usr/local/cuda/include' -O2
compiler: g++

运行：f"{compiler} {' '.join(obj_files)} {flags} {lto_flags} {link} -o {output}"

编译 c++ binary
g++ main.cpp   -Wall -Wunused-function -unused-variable -Wformat-security -Wno-unknown-pragmas -std=c++14 -fPIC -march=native  -fdiagnostics-color=always  -I/home/wuyongyu/example  -DHAS_CUDA -I'/usr/local/cuda/include'  -O2 -c -o main.o

编译执行main
g++ main.o -Wall  -Wunused-function -Wno-unknown-pragmas -std=c++14 -fPIC -march=native  -fdiagnostics-color=always -I/home/wuyongyu/example  -DHAS_CUDA -I'/usr/local/cuda/include' -O2 -lstdc++ -ldl -shared  -lcudart -L'/usr/local/cuda/lib64' -o main


例如nvcc binary:

nvcc example.cu  -std=c++14 -Xcompiler -fPIC -Xcompiler -march=native  -Xcompiler -fdiagnostics-color=always  -I/home/wuyongyu/example  -DHAS_CUDA -I'/usr/local/cuda/include'  -O2  -x cu --cudart=shared -ccbin='/usr/bin/g++' --use_fast_math  -w   -c -o example_cuda.o


编译可执行程序


g++ example_cuda.o -Wall -Werror -Wunused-function -Wno-unknown-pragmas -std=c++14 -fPIC -march=native  -fdiagnostics-color=always -I/home/wuyongyu/example  -DHAS_CUDA -I'/usr/local/cuda/include' -O2 -lstdc++ -ldl -shared  -lcudart -L'/usr/local/cuda/lib64' -o example



nvcc example.cu  -std=c++14 -Xcompiler -fPIC -Xcompiler -march=native  -Xcompiler -fdiagnostics-color=always  -I/home/wuyongyu/example  -DHAS_CUDA -I'/usr/local/cuda/include'  -O2  -x cu --cudart=shared -ccbin='/usr/bin/g++' --use_fast_math  -w   -c -o example.o

g++ example.o  -DHAS_CUDA -I'/usr/local/cuda/include' -O2 -lstdc++ -ldl -shared  -lcudart -L'/usr/local/cuda/lib64' -o example

  
