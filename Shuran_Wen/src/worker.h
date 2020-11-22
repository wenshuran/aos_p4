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
class Worker final : public masterworker::Worker::Service{

	public:
		/* DON'T change the function signature of this constructor */
		Worker(std::string ip_addr_port);

		/* DON'T change this function's signature */
		bool run();


		masterworker::Worker::AsyncService service_;
		std::unique_ptr<grpc::ServerCompletionQueue> cq_;
		std::unique_ptr<grpc::Server> server_;

		void HandleRpcs(std::string address) {
			new CallData(&service_, cq_.get(), address);
			// std::cout << "in" << std::endl;
			void* tag;  // uniquely identifies a request.
			bool ok;
			while (true) {
				cq_->Next(&tag, &ok);
				// std::cout << "get" << std::endl;
				GPR_ASSERT(ok);
				static_cast<CallData*>(tag)->Proceed();
			}
		}	


	private:
		/* NOW you can add below, data members and member functions as per the need of your implementation*/
		std::string address_;

		
		class CallData {
			private:
				masterworker::Worker::AsyncService* service_;
				grpc::ServerCompletionQueue* cq_;
				grpc::ServerContext ctx_;
				masterworker::MapReduceInfo request_;
				masterworker::MapReduceReply reply_;
				std::string address_;

				enum CallStatus { CREATE, PROCESS, FINISH };
				CallStatus status_;

				grpc::ServerAsyncResponseWriter<masterworker::MapReduceReply> responder_;
				
				
			public:
				CallData(masterworker::Worker::AsyncService* service, grpc::ServerCompletionQueue* cq, std::string& address)
					: service_(service), cq_(cq), responder_(&ctx_), status_(CREATE), address_(address) {
						Proceed();
				}

				void mapper_work(){
					std::cout << "Start Mapper" << std::endl;
					auto mapper = get_mapper_from_task_factory(request_.user_id());
					
					for(masterworker::FileInfo file_info : request_.file_infos()){
						int current_size = 0;
						std::cout << "Current Mapper input: " << file_info.filename() << " start: " << file_info.start() << " end: " << file_info.end() << std::endl;
						std::ifstream is(file_info.filename());
						std::string buf;
						if (is.is_open()) {
							is.seekg(file_info.start()*1024);
							buf.resize((file_info.end() - file_info.start())*1024);
							is.read(&buf[0], (file_info.end() - file_info.start())*1024);
							std::stringstream ss(buf);
							std::string line;
							while (std::getline(ss, line)) {
								mapper->map(line);
							}
						}
					}
					std::vector<std::pair<std::string, std::string>>& pairs = mapper->impl_->outputs_;

					//produce inter file
					std::ofstream os;
					std::string buffer_filename("Intermediate");
					os.open(buffer_filename, std::ios::app);
					if (os.is_open()) {
						std::cout << "Current Mapper output: " << buffer_filename << std::endl;
						for (auto& pair : pairs) {
							os << pair.first << "," << pair.second << "\n";
						}
						os.close();
					}
					reply_.set_address(address_);
					reply_.set_buffer_file(buffer_filename);
				}

				void reducer_work(){
					std::cout << "Start Reducer" << std::endl;
					auto reducer = get_reducer_from_task_factory(request_.user_id());
					std::ifstream is(request_.buffer_file());
					std::string line;

					std::map<std::string, std::vector<std::string>> key_value_map;
					while (std::getline(is, line)) {
						std::istringstream line_stream(line);
						std::string key;
						if (std::getline(line_stream, key, ',')) {
							std::string value;
							if (std::getline(line_stream, value)) {
								key_value_map[key].push_back(value);
							}	
						}
					}

					for (auto& key_value : key_value_map) {
						reducer->reduce(key_value.first, key_value.second);
					}
					std::vector<std::pair<std::string, std::string> >& pairs = reducer->impl_->outputs_;

					std::ofstream os;
					// std::string output_folder("./"+request_.output_dir());
					std::string output_filename("./"+request_.output_dir() + "/output");
					std::cout << "Bufferfile: " << request_.buffer_file() << " output path: " << output_filename << std::endl;
					os.open(output_filename, std::ios::app);
					if (os.is_open()) {
						// std::cout << "output open" << std::endl;
						for (auto& pair : pairs) {
								os << pair.first << " " << pair.second << "\n";
							}
						os.close();
					} 
					reply_.set_address(address_);
				}


				void Proceed() {
					if (status_ == CREATE) {
						service_->RequestMapReduceWork(&ctx_, &request_, &responder_, cq_, cq_, this);
						status_ = PROCESS;
					} else if (status_ == PROCESS) {
						new CallData(service_, cq_, address_);

						if(request_.is_map_work()){
							mapper_work();
						}
						else{
							reducer_work();
						}

						responder_.Finish(reply_, grpc::Status::OK, this);
						status_ = FINISH;
					} else {
						GPR_ASSERT(status_ == FINISH);
						delete this;
					}
				}
		};
		

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
	
	grpc::ServerBuilder builder;
	builder.AddListeningPort(address_, grpc::InsecureServerCredentials());
	builder.RegisterService(&service_);
	cq_ = builder.AddCompletionQueue();
	server_ = builder.BuildAndStart();

	std::cout << "Address " << address_ << " is working!" << std::endl;
	
	HandleRpcs(address_);
	
	return true;
}
