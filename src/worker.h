#pragma once

#include <mr_task_factory.h>
#include "mr_tasks.h"
#include <fstream>
#include <sstream>
#include <iostream>


/* CS6210_TASK: Handle all the task a Worker is supposed to do.
	This is a big task for this project, will test your understanding of map reduce */
class Worker {

	public:
		/* DON'T change the function signature of this constructor */
		Worker(std::string ip_addr_port);

		/* DON'T change this function's signature */
		bool run();

		void map_work(ServerContext *context, const MapperInfo *request, InterimFile *reply){
			auto mapper = get_mapper_from_task_factory(request.user_id);
			for(auto& file_info : request.file_infos){
				int current_size = 0;
				std::ifstream is(file_info.filename);
				std::string buf;
				if (is.is_open()) {
					is.seekg(file_info.start);
					buf.resize(size);
					is.read(&buf[0], size);
					std::stringstream ss(buf);
					std::string line;
					while (std::getline(ss, line)) {
						mapper->map(line);
					}
				}
			}
			std::vector<std::pair<std::string, std::string>>& pairs = mapper->impl_->keyval_pair;

			//produce inter file
			std::ofstream intermediate_file;
			intermediate_file.open("intermediate_file", std::ios::app || std::ios::);
			if (intermediate_file.is_open()) {
				for (auto& pair : pairs) {
					intermediate_file << pair.first << "," << pair.second << "\n";
				}
				intermediate_file.close();
			}
			reply->set_worker_addr(address_);
		}

		void reduce_work(ServerContext *context, const InterimFile *request, OutputFile *reply){
			auto reducer = get_reducer_from_task_factory(request.user_id);
			reducer->reduce("dummy", std::vector<std::string>({"1", "1"}));
			std::ifstream file("intermediate_file");
			std::string line;

			std::string key_prev;
			std::vector<std::string> vals;
			while (std::getline(file, line)) {
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
		std::vector<std::pair<std::string, std::string> >& vec = reducer->impl_->keyval_pair;
		std::string output_filename("./output/output_" + ip_addr_port);
		std::ofstream output_file(output_filename);
		std::vector<std::pair<std::string, std::string> >::iterator it;
		if (output_file.is_open()) {
			for (it = vec.begin(); it != vec.end(); it++) {
				output_file << (*it).first << "," << (*it).second << "\n";
			}
			output_file.close();
		} else {
			std::cout << "failed to open file " << output_filename << "\n";
		}
		reply->set_worker_addr(ip_addr_port);
		reply->set_filename(output_filename);

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

extern std::shared_ptr<BaseMapper> get_mapper_from_task_factory(const std::string& user_id);
extern std::shared_ptr<BaseReducer> get_reducer_from_task_factory(const std::string& user_id);

/* CS6210_TASK: Here you go. once this function is called your woker's job is to keep looking for new tasks 
	from Master, complete when given one and again keep looking for the next one.
	Note that you have the access to BaseMapper's member BaseMapperInternal impl_ and 
	BaseReduer's member BaseReducerInternal impl_ directly, 
	so you can manipulate them however you want when running map/reduce tasks*/
bool Worker::run() {
	Mapper::AsyncService service;
	ServerBuilder builder;
	builder.AddListeningPort(address_, grpc::InsecureChannelCredentials());
	builder.RegisterAsyncService(&service);
	auto cq = builder.AddCompletionQueue();
	auto server = builder.BuildAndStart();

	ServerContext context;
	HelloRequest request;
	ServerAsyncResponseWriter<HelloReply> responder;
	service.RequestSayHello(&context, &request, &responder, &cq, &cq, (void*)1);

	HelloReply reply;
	Status status;
	void* got_tag;
	bool ok = false;
	cq.Next(&got_tag, &ok);
	if (ok && got_tag == (void*)1) {
		// set reply and status
		responder.Finish(reply, status, (void*)2);
	}

	void* got_tag;
	bool ok = false;
	cq.Next(&got_tag, &ok);
	if (ok && got_tag == (void*)2) {
		// clean up
	}
	/*  Below 5 lines are just examples of how you will call map and reduce
		Remove them once you start writing your own logic */ 
	std::cout << "worker.run(), I 'm not ready yet" <<std::endl;
	
	
	return true;
}
