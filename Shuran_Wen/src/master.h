#pragma once

#include "mapreduce_spec.h"
#include "file_shard.h"
#include <vector>
#include <set>
#include <memory>
#include "masterworker.grpc.pb.h"
#include <grpcpp/grpcpp.h>

enum WorkerStatus{
	AVAILABLE, BUSY
}Status;

struct WorkerInfo{
	std::string address;
	WorkerStatus status;
	std::shared_ptr<masterworker::Worker::Stub> stub;
};

/* CS6210_TASK: Handle all the bookkeeping that Master is supposed to do.
	This is probably the biggest task for this project, will test your understanding of map reduce */
class Master {

	public:
		/* DON'T change the function signature of this constructor */
		Master(const MapReduceSpec&, const std::vector<FileShard>&);

		/* DON'T change this function's signature */
		bool run();

	private:
		/* NOW you can add below, data members and member functions as per the need of your implementation*/
		const MapReduceSpec mr_spec_;
		const std::vector<FileShard> file_shards_;
		std::vector<WorkerInfo> worker_pool_;
		std::set<std::string> buffer_files_;

		class MapperClient{
			private:
				std::shared_ptr<masterworker::Worker::Stub> stub_;

			public:
				MapperClient(std::shared_ptr<masterworker::Worker::Stub> stub) : stub_(stub) {}

				std::string mapper_work(const MapReduceSpec& mr_spec, const FileShard& file_shard) {
					masterworker::MapReduceInfo request;
					masterworker::FileInfo *file_info;

					request.set_user_id(mr_spec.user_id);
					request.set_is_map_work(true);
					for (auto& file : file_shard.files) {
						file_info = request.add_file_infos();
						file_info->set_filename(file.filename);
						file_info->set_start(file.start);
						file_info->set_end(file.end);
						std::cout << "Filename: " << file.filename << " start: " << file.start << " end: " << file.end << std::endl;
					}

					grpc::ClientContext context;
					masterworker::MapReduceReply reply;
					grpc::Status status;
					grpc::CompletionQueue cq;
					std::unique_ptr<grpc::ClientAsyncResponseReader<masterworker::MapReduceReply>> rpc(
						stub_->PrepareAsyncMapReduceWork(&context, request, &cq));
					rpc->StartCall();

  					rpc->Finish(&reply, &status, (void*)1);
					
					void* got_tag;
  					bool ok = false;
  					cq.Next(&got_tag, &ok);
  					if (ok && got_tag == (void*)1) {
						std::cout << "Mapper buffer: " << reply.buffer_file() << std::endl;
						return reply.buffer_file();
  					}
					return "";
				}
		};


		class ReducerClient{
			private:
				std::shared_ptr<masterworker::Worker::Stub> stub_;

			public:
				ReducerClient(std::shared_ptr<masterworker::Worker::Stub> stub) : stub_(stub) {}

				void reducer_work(const MapReduceSpec& mr_spec, const std::string& buffer_file) {
					masterworker::MapReduceInfo request;
					request.set_user_id(mr_spec.user_id);
					request.set_buffer_file(buffer_file);
					request.set_output_dir(mr_spec.output_dir);
					request.set_is_map_work(false);

					std::cout << "Bufferfile: " << buffer_file << " output dir: " << mr_spec.output_dir << std::endl;

					grpc::ClientContext context;
					masterworker::MapReduceReply reply;
					grpc::Status status;
					grpc::CompletionQueue cq;
					std::unique_ptr<grpc::ClientAsyncResponseReader<masterworker::MapReduceReply>> rpc(
									stub_->PrepareAsyncMapReduceWork(&context, request, &cq));

					rpc->StartCall();
					
					rpc->Finish(&reply, &status, (void*)1);
					
					void* got_tag;
					bool ok = false;
					cq.Next(&got_tag, &ok);
					if (ok && got_tag == (void*)1) {
						std::cout << " Worker address: " << reply.address() << std::endl;
					}

				}
		};
};



/* CS6210_TASK: This is all the information your master will get from the framework.
	You can populate your other class data members here if you want */
Master::Master(const MapReduceSpec& mr_spec, const std::vector<FileShard>& file_shards)
	:mr_spec_(mr_spec), file_shards_(file_shards) {

	for (auto &address : mr_spec.addresses) {
		// std::cout << "address: " << address << std::endl;
		std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(address, grpc::InsecureChannelCredentials());
		WorkerInfo worker_info;
		worker_info.address = address;
		worker_info.status = AVAILABLE;
		worker_info.stub = masterworker::Worker::NewStub(channel);
		worker_pool_.push_back(worker_info);
	}
}


/* CS6210_TASK: Here you go. once this function is called you will complete whole map reduce task and return true if succeeded */
bool Master::run() {
	//Mapper
	int worker_pool_idx = 0;
	for(int i=0; i<file_shards_.size(); i++){
		FileShard file_shard = file_shards_[i];
		while(worker_pool_[worker_pool_idx].status == BUSY){
			worker_pool_idx++;
			if(worker_pool_idx > worker_pool_.size()){
				worker_pool_idx = 0;
			}
		}
		worker_pool_[worker_pool_idx].status = BUSY;
		MapperClient mapper_client(worker_pool_[worker_pool_idx].stub);
		buffer_files_.insert(mapper_client.mapper_work(mr_spec_, file_shard));
		worker_pool_[worker_pool_idx].status = AVAILABLE;
	}

	std::cout << "Mapper Done!" << std::endl;
	worker_pool_idx = 0;

	//Mapper done, do Reducer
	for (auto& buffer_file : buffer_files_) {
		while(worker_pool_[worker_pool_idx].status == BUSY){
			worker_pool_idx++;
			if(worker_pool_idx > worker_pool_.size()){
				worker_pool_idx = 0;
			}
		}
		worker_pool_[worker_pool_idx].status = BUSY;
		ReducerClient reducer_client(worker_pool_[worker_pool_idx].stub);
		reducer_client.reducer_work(mr_spec_, buffer_file);
		worker_pool_[worker_pool_idx].status = AVAILABLE;
	}
	std::cout << "Reducer Done!" << std::endl;
	
	return true;
}