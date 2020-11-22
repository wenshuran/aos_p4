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
	std::ifstream config_file(config_filename);
	if (!config_file.is_open()){
		printf("no such file!\n");
       	return false; 
	}

	std::string line;
	while (std::getline(config_file, line)) {
		std::istringstream is_line(line);
		std::string name;
		if (std::getline(is_line, name, '=')) {
			std::string value;
			if (std::getline(is_line, value)) {
				if (name.compare("n_workers") == 0) {
					mr_spec.num_workers = std::stoi(value);
				} else if (name.compare("worker_ipaddr_ports") == 0) {
					std::stringstream addresses(value);
					std::string address;
					while (std::getline(addresses, address, ',')) {
						mr_spec.addresses.push_back(address);
					}
				} else if (name.compare("input_files") == 0) {
					std::stringstream files(value);
					std::string file;
					while (std::getline(files, file, ',')) {
						mr_spec.input_files.push_back(file);
					}
				} else if (name.compare("output_dir") == 0) {
					mr_spec.output_dir = value;
				} else if (name.compare("n_output_files") == 0) {
					mr_spec.num_output_files = std::stoi(value);
				} else if (name.compare("map_kilobytes") == 0) {
					mr_spec.map_kb = std::stoi(value);
				} else if (name.compare("user_id") == 0) {
					mr_spec.user_id = value;
				}
			}
		}
	}
	config_file.close();
	return true;
}


/* CS6210_TASK: validate the specification read from the config file */
inline bool validate_mr_spec(const MapReduceSpec& mr_spec) {
	if(mr_spec.num_workers != mr_spec.addresses.size()){
		return false;
	}
	return true;
}
