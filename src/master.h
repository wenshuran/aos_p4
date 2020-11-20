#pragma once

#include "mapreduce_spec.h"
#include "file_shard.h"
#include <vector>
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
		std::vector<std::string> buffer_files_;
};



/* CS6210_TASK: This is all the information your master will get from the framework.
	You can populate your other class data members here if you want */
Master::Master(const MapReduceSpec& mr_spec, const std::vector<FileShard>& file_shards)
	:mr_spec_(mr_spec), file_shards_(file_shards) {

	for (auto &address : mr_spec.addresses) {
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
		masterworker::MapperInfo request;
		masterworker::FileInfo *file_info;

		request.set_user_id(mr_spec_.user_id);
		for (auto& file : file_shards_[i].files) {
			file_info = request.add_file_infos();
			file_info->set_filename(file.filename);
			file_info->set_start(file.start);
			file_info->set_end(file.end);
			// file_info->set_size((*cmp_it)->offset);
		}

		auto& stub_ = worker_pool_[worker_pool_idx].stub;

		grpc::ClientContext context;
		grpc::CompletionQueue cq;
		std::unique_ptr<grpc::ClientAsyncResponseReader<masterworker::MapperReply>> rpc(
						stub_->PrepareAsyncmapper_work(&context, request, &cq));

		rpc->StartCall();
		
		masterworker::MapperReply reply;
		grpc::Status status;
		rpc->Finish(&reply, &status, (void*)1);
		
		void* got_tag;
		bool ok = false;
		cq.Next(&got_tag, &ok);
		if (ok && got_tag == (void*)1) {
			worker_pool_[worker_pool_idx].status = AVAILABLE;
			buffer_files_.push_back(reply.buffer_file().c_str());
		}
	}

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
		
		masterworker::ReducerInfo request;
		request.set_user_id(mr_spec_.user_id);
		request.set_buffer_file(buffer_file);
		request.set_output_dir(mr_spec_.output_dir);
		auto& stub_ = worker_pool_[worker_pool_idx].stub;

		grpc::ClientContext context;
		grpc::CompletionQueue cq;
		std::unique_ptr<grpc::ClientAsyncResponseReader<masterworker::ReducerReply>> rpc(
						stub_->PrepareAsyncreducer_work(&context, request, &cq));

		rpc->StartCall();
		
		masterworker::ReducerReply reply;
		grpc::Status status;
		rpc->Finish(&reply, &status, (void*)1);
		
		void* got_tag;
		bool ok = false;
		cq.Next(&got_tag, &ok);
		if (ok && got_tag == (void*)1) {
			worker_pool_[worker_pool_idx].status = AVAILABLE;
		}
	}
	

	return true;
}