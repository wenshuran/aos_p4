#pragma once

#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

/* CS6210_TASK: Create your data structure here for storing spec from the config file */
struct MapReduceSpec {
	int num_workers;
	std::vector<std::string> addresses;
	std::vector<std::string> input_files;
	std::string output_dir;
	int num_output_files;
	int map_kb;
	std::string user_id;
};


/* CS6210_TASK: Populate MapReduceSpec data structure with the specification from the config file */
inline bool read_mr_spec_from_config_file(const std::string& config_filename, MapReduceSpec& mr_spec) {
	FILE *fp = fopen(config_filename.c_str(), "r");
	if(!fp){
       printf("no such file!\n");
       return false; 
    }
	char num_workers[5];
	char address[100];
	char input_files[100];
	char output_dir[20];
	char num_output_files[5];
	char map_kb[10];
	char user_id[10];
	fgets(num_workers, 5, fp);
	mr_spec.num_workers = std::stoi(num_workers);

	fgets(address, 100, fp);
	std::stringstream addresses(address);
	std::string addr;
	while (std::getline(addresses, addr, ',')) {
		mr_spec.addresses.push_back(addr);
	}

	fgets(input_files, 100, fp);
	std::stringstream files(input_files);
	std::string filename;
	while (std::getline(files, filename, ',')) {
		mr_spec.input_files.push_back(filename);
	}

	fgets(output_dir, 20, fp);
	mr_spec.output_dir = output_dir;

	fgets(num_output_files, 5, fp);
	mr_spec.num_output_files = std::stoi(num_output_files);

	fgets(map_kb, 10, fp);
	mr_spec.map_kb = std::stoi(map_kb);

	fgets(user_id, 10, fp);
	mr_spec.user_id = user_id;

	fclose(fp);
	return true;
}


/* CS6210_TASK: validate the specification read from the config file */
inline bool validate_mr_spec(const MapReduceSpec& mr_spec) {
	if(mr_spec.num_workers != mr_spec.addresses.size()){
		return false;
	}
	return true;
}
