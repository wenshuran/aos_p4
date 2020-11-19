#pragma once

#include <vector>
#include <iostream>
#include <sys/stat.h>  

#include <math.h>
#include "mapreduce_spec.h"


/* CS6210_TASK: Create your own data structure here, where you can hold information about file splits,
     that your master would use for its own bookkeeping and to convey the tasks to the workers for mapping */
struct FileShard {
     std::vector<FileInfo> files;
};

struct FileInfo{
     std::string filename;
     int start;
     int end;
};



/* CS6210_TASK: Create fileshards from the list of input files, map_kilobytes etc. using mr_spec you populated  */ 
inline bool shard_files(const MapReduceSpec& mr_spec, std::vector<FileShard>& fileShards) {
     int num_files = mr_spec.input_files.size();
     std::string files[num_files];
     int file_size[num_files];
	int sum_size = 0;
	std::FILE *fp;
	for (int i = 0; i < num_files; i++) {
          std::string filename = mr_spec.input_files[i];
          struct stat statbuf;  
          stat(filename.c_str(),&statbuf);  
          int size=statbuf.st_size;  
          file_size[i] = size;
          sum_size += size;
	}
     int num_shards = (int)ceil((double)sum_size/mr_spec.map_kb);
     int file_index = 0;
     int current_file_start = 0;
     int current_file_end;
     for (int i = 0; i < num_shards; i++) {
          FileShard file_shard;
          int current_map_position = 0;
          int current_map_remain = mr_spec.map_kb; //16
          while(current_map_remain > 0){
               FileInfo info;
               info.filename = mr_spec.input_files[file_index];
               info.start = current_file_start;
               current_file_end = file_size[file_index]; //20
               if((current_file_end - current_file_start) >= current_map_remain){
                    info.end = current_map_remain;
                    file_shard.files.push_back(info);
                    current_file_start = current_map_remain;  //16
                    current_map_remain = 0;
                    continue;
               }
               else{ //4 16
                    info.end = current_file_end; //20
                    current_map_remain = current_map_remain - (current_file_end - current_file_start);//16-4=12
                    file_shard.files.push_back(info);
                    file_index++;/* condition */
                    if(file_index > num_files){
                         break;
                    }
                    current_file_start = 0;
               }
          }
          fileShards.push_back(file_shard);
     }
     return true;
}
