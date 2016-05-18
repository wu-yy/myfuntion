struct inode{

union{  //包含不同文件系统特定inode信息的union成员变量
struct device   _devices_info;   //设备文件系统的内存inode信息
struct sfs_inode     _sfs_inode_info;//SFS文件系统的内存inode信息
}in_info;


enum{  //此inode 所属的文件系统类型
  inode_type_device_info=0x1234,
  inode_type_sfs_inode_info,  
}in_type;

};
