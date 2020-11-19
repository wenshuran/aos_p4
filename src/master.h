#pragma once

#include "mapreduce_spec.h"
#include "file_shard.h"
#include <vector>
#include <memory>

enum WorkerStatus{
	AVAILABLE, BUSY
}Status;

class WorkerInfo{
	std::string address;
	WorkerStatus status;
}

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
		std::vector<Mapper> mappers;
		const MapReduceSpec mr_spec_;
		const std::vector<FileShard> file_shards_;
		bool mapper_finished;
		std::vector<std::shared_ptr<Mapper::Stub>> stubs_; 

		
};



/* CS6210_TASK: This is all the information your master will get from the framework.
	You can populate your other class data members here if you want */
Master::Master(const MapReduceSpec& mr_spec, const std::vector<FileShard>& file_shards)
	:mr_spec_(mr_spec), file_shards_(file_shards) {
	for (auto &address : mr_spec.addresses) {
		std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(address, grpc::InsecureChannelCredentials());
		stubs_.pop_back(Mapper::NewStub(channel));
		
	}
	
}


/* CS6210_TASK: Here you go. once this function is called you will complete whole map reduce task and return true if succeeded */
bool Master::run() {
	return true;
}