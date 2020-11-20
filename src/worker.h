#pragma once

#include <mr_task_factory.h>
#include "mr_tasks.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <masterworker.grpc.pb.h>
#include <grpcpp/grpcpp.h>


extern std::shared_ptr<BaseMapper> get_mapper_from_task_factory(const std::string& user_id);
extern std::shared_ptr<BaseReducer> get_reducer_from_task_factory(const std::string& user_id);

/* CS6210_TASK: Handle all the task a Worker is supposed to do.
	This is a big task for this project, will test your understanding of map reduce */
class Worker {

	public:
		/* DON'T change the function signature of this constructor */
		Worker(std::string ip_addr_port);

		/* DON'T change this function's signature */
		bool run();

		void map_work(grpc::ServerContext *context, const masterworker::MapperInfo *request, masterworker::MapperReply *reply){
			auto mapper = get_mapper_from_task_factory(request->user_id());
			for(masterworker::FileInfo file_info : request->file_infos()){
				int current_size = 0;
				std::ifstream is(file_info.filename());
				std::string buf;
				if (is.is_open()) {
					is.seekg(file_info.start());
					buf.resize(file_info.end() - file_info.start());
					is.read(&buf[0], file_info.end() - file_info.start());
					std::stringstream ss(buf);
					std::string line;
					while (std::getline(ss, line)) {
						mapper->map(line);
					}
				}
			}
			std::vector<std::pair<std::string, std::string>>& pairs = mapper->impl_->keyval_pair;

			//produce inter file
			std::ofstream os;
			std::string buffer_filename("mapper " + address_);
			os.open(buffer_filename, std::ios::app);
			if (os.is_open()) {
				for (auto& pair : pairs) {
					os << pair.first << "," << pair.second << "\n";
				}
				os.close();
			}
			reply->set_address(address_);
			reply->set_buffer_file(buffer_filename);
		}

		void reduce_work(grpc::ServerContext *context, const masterworker::ReducerInfo *request, masterworker::ReducerReply *reply){
			auto reducer = get_reducer_from_task_factory(request->user_id());
			std::ifstream is(request->buffer_file());
			std::string line;

			std::string key_prev;
			std::vector<std::string> vals;
			while (std::getline(is, line)) {
				std::istringstream line_stream(line);
				std::string key;
				if (std::getline(line_stream, key, ',')) {
					std::string value;
					if (std::getline(line_stream, value)) {
						if (key_prev.compare("") == 0 || key.compare(key_prev) == 0) {
							vals.push_back(value);
							key_prev = key;
						} else {
							reducer->reduce(key_prev, vals);
							key_prev = key;
							vals.clear();
							vals.push_back(value);
						}
					}
				}
			}
			std::vector<std::pair<std::string, std::string> >& pairs = reducer->impl_->keyval_pair;

			std::ofstream os(request->output_dir()+ address_);
			std::vector<std::pair<std::string, std::string> >::iterator it;
			if (os.is_open()) {
				for (auto& pair : pairs) {
						os << pair.first << " " << pair.second << "\n";
					}
				os.close();
			} 
			reply->set_address(address_);

		}

	private:
		/* NOW you can add below, data members and member functions as per the need of your implementation*/
		std::string address_;
		
};


/* CS6210_TASK: ip_addr_port is the only information you get when started.
	You can populate your other class data members here if you want */
Worker::Worker(std::string ip_addr_port)
	:address_(ip_addr_port) {

}


/* CS6210_TASK: Here you go. once this function is called your woker's job is to keep looking for new tasks 
	from Master, complete when given one and again keep looking for the next one.
	Note that you have the access to BaseMapper's member BaseMapperInternal impl_ and 
	BaseReduer's member BaseReducerInternal impl_ directly, 
	so you can manipulate them however you want when running map/reduce tasks*/
bool Worker::run() {
	masterworker::Worker::AsyncService service;
	grpc::ServerBuilder builder;
	builder.AddListeningPort(address_, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);
	auto cq = builder.AddCompletionQueue();
	auto server = builder.BuildAndStart();

	std::cout << "Address " << address_ << " is working!" << std::endl;
	
	
	return true;
}
