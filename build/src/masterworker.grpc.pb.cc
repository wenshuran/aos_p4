// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: masterworker.proto

#include "masterworker.pb.h"
#include "masterworker.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace masterworker {

static const char* Worker_method_names[] = {
  "/masterworker.Worker/MapReduceWork",
};

std::unique_ptr< Worker::Stub> Worker::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Worker::Stub> stub(new Worker::Stub(channel));
  return stub;
}

Worker::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_MapReduceWork_(Worker_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Worker::Stub::MapReduceWork(::grpc::ClientContext* context, const ::masterworker::MapReduceInfo& request, ::masterworker::MapReduceReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_MapReduceWork_, context, request, response);
}

void Worker::Stub::experimental_async::MapReduceWork(::grpc::ClientContext* context, const ::masterworker::MapReduceInfo* request, ::masterworker::MapReduceReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_MapReduceWork_, context, request, response, std::move(f));
}

void Worker::Stub::experimental_async::MapReduceWork(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::masterworker::MapReduceReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_MapReduceWork_, context, request, response, std::move(f));
}

void Worker::Stub::experimental_async::MapReduceWork(::grpc::ClientContext* context, const ::masterworker::MapReduceInfo* request, ::masterworker::MapReduceReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_MapReduceWork_, context, request, response, reactor);
}

void Worker::Stub::experimental_async::MapReduceWork(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::masterworker::MapReduceReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_MapReduceWork_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::masterworker::MapReduceReply>* Worker::Stub::AsyncMapReduceWorkRaw(::grpc::ClientContext* context, const ::masterworker::MapReduceInfo& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::masterworker::MapReduceReply>::Create(channel_.get(), cq, rpcmethod_MapReduceWork_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::masterworker::MapReduceReply>* Worker::Stub::PrepareAsyncMapReduceWorkRaw(::grpc::ClientContext* context, const ::masterworker::MapReduceInfo& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::masterworker::MapReduceReply>::Create(channel_.get(), cq, rpcmethod_MapReduceWork_, context, request, false);
}

Worker::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Worker_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Worker::Service, ::masterworker::MapReduceInfo, ::masterworker::MapReduceReply>(
          [](Worker::Service* service,
             ::grpc_impl::ServerContext* ctx,
             const ::masterworker::MapReduceInfo* req,
             ::masterworker::MapReduceReply* resp) {
               return service->MapReduceWork(ctx, req, resp);
             }, this)));
}

Worker::Service::~Service() {
}

::grpc::Status Worker::Service::MapReduceWork(::grpc::ServerContext* context, const ::masterworker::MapReduceInfo* request, ::masterworker::MapReduceReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace masterworker

