﻿/*
* Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License").
* You may not use this file except in compliance with the License.
* A copy of the License is located at
*
*  http://aws.amazon.com/apache2.0
*
* or in the "license" file accompanying this file. This file is distributed
* on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied. See the License for the specific language governing
* permissions and limitations under the License.
*/

#include <aws/core/utils/Outcome.h>
#include <aws/core/auth/AWSAuthSigner.h>
#include <aws/core/client/CoreErrors.h>
#include <aws/core/client/RetryStrategy.h>
#include <aws/core/http/HttpClient.h>
#include <aws/core/http/HttpResponse.h>
#include <aws/core/http/HttpClientFactory.h>
#include <aws/core/auth/AWSCredentialsProviderChain.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/utils/memory/stl/AWSStringStream.h>
#include <aws/core/utils/threading/Executor.h>
#include <aws/pinpoint/PinpointClient.h>
#include <aws/pinpoint/PinpointEndpoint.h>
#include <aws/pinpoint/PinpointErrorMarshaller.h>
#include <aws/pinpoint/model/CreateAppRequest.h>
#include <aws/pinpoint/model/CreateCampaignRequest.h>
#include <aws/pinpoint/model/CreateImportJobRequest.h>
#include <aws/pinpoint/model/CreateSegmentRequest.h>
#include <aws/pinpoint/model/DeleteApnsChannelRequest.h>
#include <aws/pinpoint/model/DeleteApnsSandboxChannelRequest.h>
#include <aws/pinpoint/model/DeleteAppRequest.h>
#include <aws/pinpoint/model/DeleteCampaignRequest.h>
#include <aws/pinpoint/model/DeleteEmailChannelRequest.h>
#include <aws/pinpoint/model/DeleteEventStreamRequest.h>
#include <aws/pinpoint/model/DeleteGcmChannelRequest.h>
#include <aws/pinpoint/model/DeleteSegmentRequest.h>
#include <aws/pinpoint/model/DeleteSmsChannelRequest.h>
#include <aws/pinpoint/model/GetApnsChannelRequest.h>
#include <aws/pinpoint/model/GetApnsSandboxChannelRequest.h>
#include <aws/pinpoint/model/GetAppRequest.h>
#include <aws/pinpoint/model/GetApplicationSettingsRequest.h>
#include <aws/pinpoint/model/GetAppsRequest.h>
#include <aws/pinpoint/model/GetCampaignRequest.h>
#include <aws/pinpoint/model/GetCampaignActivitiesRequest.h>
#include <aws/pinpoint/model/GetCampaignVersionRequest.h>
#include <aws/pinpoint/model/GetCampaignVersionsRequest.h>
#include <aws/pinpoint/model/GetCampaignsRequest.h>
#include <aws/pinpoint/model/GetEmailChannelRequest.h>
#include <aws/pinpoint/model/GetEndpointRequest.h>
#include <aws/pinpoint/model/GetEventStreamRequest.h>
#include <aws/pinpoint/model/GetGcmChannelRequest.h>
#include <aws/pinpoint/model/GetImportJobRequest.h>
#include <aws/pinpoint/model/GetImportJobsRequest.h>
#include <aws/pinpoint/model/GetSegmentRequest.h>
#include <aws/pinpoint/model/GetSegmentImportJobsRequest.h>
#include <aws/pinpoint/model/GetSegmentVersionRequest.h>
#include <aws/pinpoint/model/GetSegmentVersionsRequest.h>
#include <aws/pinpoint/model/GetSegmentsRequest.h>
#include <aws/pinpoint/model/GetSmsChannelRequest.h>
#include <aws/pinpoint/model/PutEventStreamRequest.h>
#include <aws/pinpoint/model/SendMessagesRequest.h>
#include <aws/pinpoint/model/UpdateApnsChannelRequest.h>
#include <aws/pinpoint/model/UpdateApnsSandboxChannelRequest.h>
#include <aws/pinpoint/model/UpdateApplicationSettingsRequest.h>
#include <aws/pinpoint/model/UpdateCampaignRequest.h>
#include <aws/pinpoint/model/UpdateEmailChannelRequest.h>
#include <aws/pinpoint/model/UpdateEndpointRequest.h>
#include <aws/pinpoint/model/UpdateEndpointsBatchRequest.h>
#include <aws/pinpoint/model/UpdateGcmChannelRequest.h>
#include <aws/pinpoint/model/UpdateSegmentRequest.h>
#include <aws/pinpoint/model/UpdateSmsChannelRequest.h>

using namespace Aws;
using namespace Aws::Auth;
using namespace Aws::Client;
using namespace Aws::Pinpoint;
using namespace Aws::Pinpoint::Model;
using namespace Aws::Http;
using namespace Aws::Utils::Json;

static const char* SERVICE_NAME = "mobiletargeting";
static const char* ALLOCATION_TAG = "PinpointClient";


PinpointClient::PinpointClient(const Client::ClientConfiguration& clientConfiguration) :
  BASECLASS(clientConfiguration,
    Aws::MakeShared<AWSAuthV4Signer>(ALLOCATION_TAG, Aws::MakeShared<DefaultAWSCredentialsProviderChain>(ALLOCATION_TAG),
        SERVICE_NAME, clientConfiguration.region),
    Aws::MakeShared<PinpointErrorMarshaller>(ALLOCATION_TAG)),
    m_executor(clientConfiguration.executor)
{
  init(clientConfiguration);
}

PinpointClient::PinpointClient(const AWSCredentials& credentials, const Client::ClientConfiguration& clientConfiguration) :
  BASECLASS(clientConfiguration,
    Aws::MakeShared<AWSAuthV4Signer>(ALLOCATION_TAG, Aws::MakeShared<SimpleAWSCredentialsProvider>(ALLOCATION_TAG, credentials),
         SERVICE_NAME, clientConfiguration.region),
    Aws::MakeShared<PinpointErrorMarshaller>(ALLOCATION_TAG)),
    m_executor(clientConfiguration.executor)
{
  init(clientConfiguration);
}

PinpointClient::PinpointClient(const std::shared_ptr<AWSCredentialsProvider>& credentialsProvider,
  const Client::ClientConfiguration& clientConfiguration) :
  BASECLASS(clientConfiguration,
    Aws::MakeShared<AWSAuthV4Signer>(ALLOCATION_TAG, credentialsProvider,
         SERVICE_NAME, clientConfiguration.region),
    Aws::MakeShared<PinpointErrorMarshaller>(ALLOCATION_TAG)),
    m_executor(clientConfiguration.executor)
{
  init(clientConfiguration);
}

PinpointClient::~PinpointClient()
{
}

void PinpointClient::init(const ClientConfiguration& config)
{
  Aws::StringStream ss;
  ss << SchemeMapper::ToString(config.scheme) << "://";

  if(config.endpointOverride.empty())
  {
    ss << PinpointEndpoint::ForRegion(config.region, config.useDualStack);
  }
  else
  {
    ss << config.endpointOverride;
  }

  m_uri = ss.str();
}

CreateAppOutcome PinpointClient::CreateApp(const CreateAppRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_POST, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return CreateAppOutcome(CreateAppResult(outcome.GetResult()));
  }
  else
  {
    return CreateAppOutcome(outcome.GetError());
  }
}

CreateAppOutcomeCallable PinpointClient::CreateAppCallable(const CreateAppRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateAppOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateApp(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::CreateAppAsync(const CreateAppRequest& request, const CreateAppResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->CreateAppAsyncHelper( request, handler, context ); } );
}

void PinpointClient::CreateAppAsyncHelper(const CreateAppRequest& request, const CreateAppResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateApp(request), context);
}

CreateCampaignOutcome PinpointClient::CreateCampaign(const CreateCampaignRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/campaigns";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_POST, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return CreateCampaignOutcome(CreateCampaignResult(outcome.GetResult()));
  }
  else
  {
    return CreateCampaignOutcome(outcome.GetError());
  }
}

CreateCampaignOutcomeCallable PinpointClient::CreateCampaignCallable(const CreateCampaignRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateCampaignOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateCampaign(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::CreateCampaignAsync(const CreateCampaignRequest& request, const CreateCampaignResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->CreateCampaignAsyncHelper( request, handler, context ); } );
}

void PinpointClient::CreateCampaignAsyncHelper(const CreateCampaignRequest& request, const CreateCampaignResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateCampaign(request), context);
}

CreateImportJobOutcome PinpointClient::CreateImportJob(const CreateImportJobRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/jobs/import";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_POST, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return CreateImportJobOutcome(CreateImportJobResult(outcome.GetResult()));
  }
  else
  {
    return CreateImportJobOutcome(outcome.GetError());
  }
}

CreateImportJobOutcomeCallable PinpointClient::CreateImportJobCallable(const CreateImportJobRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateImportJobOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateImportJob(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::CreateImportJobAsync(const CreateImportJobRequest& request, const CreateImportJobResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->CreateImportJobAsyncHelper( request, handler, context ); } );
}

void PinpointClient::CreateImportJobAsyncHelper(const CreateImportJobRequest& request, const CreateImportJobResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateImportJob(request), context);
}

CreateSegmentOutcome PinpointClient::CreateSegment(const CreateSegmentRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/segments";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_POST, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return CreateSegmentOutcome(CreateSegmentResult(outcome.GetResult()));
  }
  else
  {
    return CreateSegmentOutcome(outcome.GetError());
  }
}

CreateSegmentOutcomeCallable PinpointClient::CreateSegmentCallable(const CreateSegmentRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateSegmentOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateSegment(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::CreateSegmentAsync(const CreateSegmentRequest& request, const CreateSegmentResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->CreateSegmentAsyncHelper( request, handler, context ); } );
}

void PinpointClient::CreateSegmentAsyncHelper(const CreateSegmentRequest& request, const CreateSegmentResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, CreateSegment(request), context);
}

DeleteApnsChannelOutcome PinpointClient::DeleteApnsChannel(const DeleteApnsChannelRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/channels/apns";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_DELETE, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return DeleteApnsChannelOutcome(DeleteApnsChannelResult(outcome.GetResult()));
  }
  else
  {
    return DeleteApnsChannelOutcome(outcome.GetError());
  }
}

DeleteApnsChannelOutcomeCallable PinpointClient::DeleteApnsChannelCallable(const DeleteApnsChannelRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteApnsChannelOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteApnsChannel(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::DeleteApnsChannelAsync(const DeleteApnsChannelRequest& request, const DeleteApnsChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->DeleteApnsChannelAsyncHelper( request, handler, context ); } );
}

void PinpointClient::DeleteApnsChannelAsyncHelper(const DeleteApnsChannelRequest& request, const DeleteApnsChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteApnsChannel(request), context);
}

DeleteApnsSandboxChannelOutcome PinpointClient::DeleteApnsSandboxChannel(const DeleteApnsSandboxChannelRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/channels/apns_sandbox";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_DELETE, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return DeleteApnsSandboxChannelOutcome(DeleteApnsSandboxChannelResult(outcome.GetResult()));
  }
  else
  {
    return DeleteApnsSandboxChannelOutcome(outcome.GetError());
  }
}

DeleteApnsSandboxChannelOutcomeCallable PinpointClient::DeleteApnsSandboxChannelCallable(const DeleteApnsSandboxChannelRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteApnsSandboxChannelOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteApnsSandboxChannel(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::DeleteApnsSandboxChannelAsync(const DeleteApnsSandboxChannelRequest& request, const DeleteApnsSandboxChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->DeleteApnsSandboxChannelAsyncHelper( request, handler, context ); } );
}

void PinpointClient::DeleteApnsSandboxChannelAsyncHelper(const DeleteApnsSandboxChannelRequest& request, const DeleteApnsSandboxChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteApnsSandboxChannel(request), context);
}

DeleteAppOutcome PinpointClient::DeleteApp(const DeleteAppRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_DELETE, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return DeleteAppOutcome(DeleteAppResult(outcome.GetResult()));
  }
  else
  {
    return DeleteAppOutcome(outcome.GetError());
  }
}

DeleteAppOutcomeCallable PinpointClient::DeleteAppCallable(const DeleteAppRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteAppOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteApp(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::DeleteAppAsync(const DeleteAppRequest& request, const DeleteAppResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->DeleteAppAsyncHelper( request, handler, context ); } );
}

void PinpointClient::DeleteAppAsyncHelper(const DeleteAppRequest& request, const DeleteAppResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteApp(request), context);
}

DeleteCampaignOutcome PinpointClient::DeleteCampaign(const DeleteCampaignRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/campaigns/{campaign-id}";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_DELETE, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return DeleteCampaignOutcome(DeleteCampaignResult(outcome.GetResult()));
  }
  else
  {
    return DeleteCampaignOutcome(outcome.GetError());
  }
}

DeleteCampaignOutcomeCallable PinpointClient::DeleteCampaignCallable(const DeleteCampaignRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteCampaignOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteCampaign(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::DeleteCampaignAsync(const DeleteCampaignRequest& request, const DeleteCampaignResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->DeleteCampaignAsyncHelper( request, handler, context ); } );
}

void PinpointClient::DeleteCampaignAsyncHelper(const DeleteCampaignRequest& request, const DeleteCampaignResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteCampaign(request), context);
}

DeleteEmailChannelOutcome PinpointClient::DeleteEmailChannel(const DeleteEmailChannelRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/channels/email";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_DELETE, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return DeleteEmailChannelOutcome(DeleteEmailChannelResult(outcome.GetResult()));
  }
  else
  {
    return DeleteEmailChannelOutcome(outcome.GetError());
  }
}

DeleteEmailChannelOutcomeCallable PinpointClient::DeleteEmailChannelCallable(const DeleteEmailChannelRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteEmailChannelOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteEmailChannel(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::DeleteEmailChannelAsync(const DeleteEmailChannelRequest& request, const DeleteEmailChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->DeleteEmailChannelAsyncHelper( request, handler, context ); } );
}

void PinpointClient::DeleteEmailChannelAsyncHelper(const DeleteEmailChannelRequest& request, const DeleteEmailChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteEmailChannel(request), context);
}

DeleteEventStreamOutcome PinpointClient::DeleteEventStream(const DeleteEventStreamRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/eventstream";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_DELETE, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return DeleteEventStreamOutcome(DeleteEventStreamResult(outcome.GetResult()));
  }
  else
  {
    return DeleteEventStreamOutcome(outcome.GetError());
  }
}

DeleteEventStreamOutcomeCallable PinpointClient::DeleteEventStreamCallable(const DeleteEventStreamRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteEventStreamOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteEventStream(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::DeleteEventStreamAsync(const DeleteEventStreamRequest& request, const DeleteEventStreamResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->DeleteEventStreamAsyncHelper( request, handler, context ); } );
}

void PinpointClient::DeleteEventStreamAsyncHelper(const DeleteEventStreamRequest& request, const DeleteEventStreamResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteEventStream(request), context);
}

DeleteGcmChannelOutcome PinpointClient::DeleteGcmChannel(const DeleteGcmChannelRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/channels/gcm";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_DELETE, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return DeleteGcmChannelOutcome(DeleteGcmChannelResult(outcome.GetResult()));
  }
  else
  {
    return DeleteGcmChannelOutcome(outcome.GetError());
  }
}

DeleteGcmChannelOutcomeCallable PinpointClient::DeleteGcmChannelCallable(const DeleteGcmChannelRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteGcmChannelOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteGcmChannel(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::DeleteGcmChannelAsync(const DeleteGcmChannelRequest& request, const DeleteGcmChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->DeleteGcmChannelAsyncHelper( request, handler, context ); } );
}

void PinpointClient::DeleteGcmChannelAsyncHelper(const DeleteGcmChannelRequest& request, const DeleteGcmChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteGcmChannel(request), context);
}

DeleteSegmentOutcome PinpointClient::DeleteSegment(const DeleteSegmentRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/segments/{segment-id}";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_DELETE, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return DeleteSegmentOutcome(DeleteSegmentResult(outcome.GetResult()));
  }
  else
  {
    return DeleteSegmentOutcome(outcome.GetError());
  }
}

DeleteSegmentOutcomeCallable PinpointClient::DeleteSegmentCallable(const DeleteSegmentRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteSegmentOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteSegment(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::DeleteSegmentAsync(const DeleteSegmentRequest& request, const DeleteSegmentResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->DeleteSegmentAsyncHelper( request, handler, context ); } );
}

void PinpointClient::DeleteSegmentAsyncHelper(const DeleteSegmentRequest& request, const DeleteSegmentResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteSegment(request), context);
}

DeleteSmsChannelOutcome PinpointClient::DeleteSmsChannel(const DeleteSmsChannelRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/channels/sms";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_DELETE, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return DeleteSmsChannelOutcome(DeleteSmsChannelResult(outcome.GetResult()));
  }
  else
  {
    return DeleteSmsChannelOutcome(outcome.GetError());
  }
}

DeleteSmsChannelOutcomeCallable PinpointClient::DeleteSmsChannelCallable(const DeleteSmsChannelRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteSmsChannelOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteSmsChannel(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::DeleteSmsChannelAsync(const DeleteSmsChannelRequest& request, const DeleteSmsChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->DeleteSmsChannelAsyncHelper( request, handler, context ); } );
}

void PinpointClient::DeleteSmsChannelAsyncHelper(const DeleteSmsChannelRequest& request, const DeleteSmsChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, DeleteSmsChannel(request), context);
}

GetApnsChannelOutcome PinpointClient::GetApnsChannel(const GetApnsChannelRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/channels/apns";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetApnsChannelOutcome(GetApnsChannelResult(outcome.GetResult()));
  }
  else
  {
    return GetApnsChannelOutcome(outcome.GetError());
  }
}

GetApnsChannelOutcomeCallable PinpointClient::GetApnsChannelCallable(const GetApnsChannelRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetApnsChannelOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetApnsChannel(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetApnsChannelAsync(const GetApnsChannelRequest& request, const GetApnsChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetApnsChannelAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetApnsChannelAsyncHelper(const GetApnsChannelRequest& request, const GetApnsChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetApnsChannel(request), context);
}

GetApnsSandboxChannelOutcome PinpointClient::GetApnsSandboxChannel(const GetApnsSandboxChannelRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/channels/apns_sandbox";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetApnsSandboxChannelOutcome(GetApnsSandboxChannelResult(outcome.GetResult()));
  }
  else
  {
    return GetApnsSandboxChannelOutcome(outcome.GetError());
  }
}

GetApnsSandboxChannelOutcomeCallable PinpointClient::GetApnsSandboxChannelCallable(const GetApnsSandboxChannelRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetApnsSandboxChannelOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetApnsSandboxChannel(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetApnsSandboxChannelAsync(const GetApnsSandboxChannelRequest& request, const GetApnsSandboxChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetApnsSandboxChannelAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetApnsSandboxChannelAsyncHelper(const GetApnsSandboxChannelRequest& request, const GetApnsSandboxChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetApnsSandboxChannel(request), context);
}

GetAppOutcome PinpointClient::GetApp(const GetAppRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetAppOutcome(GetAppResult(outcome.GetResult()));
  }
  else
  {
    return GetAppOutcome(outcome.GetError());
  }
}

GetAppOutcomeCallable PinpointClient::GetAppCallable(const GetAppRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetAppOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetApp(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetAppAsync(const GetAppRequest& request, const GetAppResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetAppAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetAppAsyncHelper(const GetAppRequest& request, const GetAppResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetApp(request), context);
}

GetApplicationSettingsOutcome PinpointClient::GetApplicationSettings(const GetApplicationSettingsRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/settings";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetApplicationSettingsOutcome(GetApplicationSettingsResult(outcome.GetResult()));
  }
  else
  {
    return GetApplicationSettingsOutcome(outcome.GetError());
  }
}

GetApplicationSettingsOutcomeCallable PinpointClient::GetApplicationSettingsCallable(const GetApplicationSettingsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetApplicationSettingsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetApplicationSettings(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetApplicationSettingsAsync(const GetApplicationSettingsRequest& request, const GetApplicationSettingsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetApplicationSettingsAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetApplicationSettingsAsyncHelper(const GetApplicationSettingsRequest& request, const GetApplicationSettingsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetApplicationSettings(request), context);
}

GetAppsOutcome PinpointClient::GetApps(const GetAppsRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetAppsOutcome(GetAppsResult(outcome.GetResult()));
  }
  else
  {
    return GetAppsOutcome(outcome.GetError());
  }
}

GetAppsOutcomeCallable PinpointClient::GetAppsCallable(const GetAppsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetAppsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetApps(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetAppsAsync(const GetAppsRequest& request, const GetAppsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetAppsAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetAppsAsyncHelper(const GetAppsRequest& request, const GetAppsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetApps(request), context);
}

GetCampaignOutcome PinpointClient::GetCampaign(const GetCampaignRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/campaigns/{campaign-id}";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetCampaignOutcome(GetCampaignResult(outcome.GetResult()));
  }
  else
  {
    return GetCampaignOutcome(outcome.GetError());
  }
}

GetCampaignOutcomeCallable PinpointClient::GetCampaignCallable(const GetCampaignRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetCampaignOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetCampaign(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetCampaignAsync(const GetCampaignRequest& request, const GetCampaignResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetCampaignAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetCampaignAsyncHelper(const GetCampaignRequest& request, const GetCampaignResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetCampaign(request), context);
}

GetCampaignActivitiesOutcome PinpointClient::GetCampaignActivities(const GetCampaignActivitiesRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/campaigns/{campaign-id}/activities";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetCampaignActivitiesOutcome(GetCampaignActivitiesResult(outcome.GetResult()));
  }
  else
  {
    return GetCampaignActivitiesOutcome(outcome.GetError());
  }
}

GetCampaignActivitiesOutcomeCallable PinpointClient::GetCampaignActivitiesCallable(const GetCampaignActivitiesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetCampaignActivitiesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetCampaignActivities(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetCampaignActivitiesAsync(const GetCampaignActivitiesRequest& request, const GetCampaignActivitiesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetCampaignActivitiesAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetCampaignActivitiesAsyncHelper(const GetCampaignActivitiesRequest& request, const GetCampaignActivitiesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetCampaignActivities(request), context);
}

GetCampaignVersionOutcome PinpointClient::GetCampaignVersion(const GetCampaignVersionRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/campaigns/{campaign-id}/versions/";
  ss << request.GetVersion();
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetCampaignVersionOutcome(GetCampaignVersionResult(outcome.GetResult()));
  }
  else
  {
    return GetCampaignVersionOutcome(outcome.GetError());
  }
}

GetCampaignVersionOutcomeCallable PinpointClient::GetCampaignVersionCallable(const GetCampaignVersionRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetCampaignVersionOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetCampaignVersion(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetCampaignVersionAsync(const GetCampaignVersionRequest& request, const GetCampaignVersionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetCampaignVersionAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetCampaignVersionAsyncHelper(const GetCampaignVersionRequest& request, const GetCampaignVersionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetCampaignVersion(request), context);
}

GetCampaignVersionsOutcome PinpointClient::GetCampaignVersions(const GetCampaignVersionsRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/campaigns/{campaign-id}/versions";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetCampaignVersionsOutcome(GetCampaignVersionsResult(outcome.GetResult()));
  }
  else
  {
    return GetCampaignVersionsOutcome(outcome.GetError());
  }
}

GetCampaignVersionsOutcomeCallable PinpointClient::GetCampaignVersionsCallable(const GetCampaignVersionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetCampaignVersionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetCampaignVersions(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetCampaignVersionsAsync(const GetCampaignVersionsRequest& request, const GetCampaignVersionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetCampaignVersionsAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetCampaignVersionsAsyncHelper(const GetCampaignVersionsRequest& request, const GetCampaignVersionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetCampaignVersions(request), context);
}

GetCampaignsOutcome PinpointClient::GetCampaigns(const GetCampaignsRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/campaigns";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetCampaignsOutcome(GetCampaignsResult(outcome.GetResult()));
  }
  else
  {
    return GetCampaignsOutcome(outcome.GetError());
  }
}

GetCampaignsOutcomeCallable PinpointClient::GetCampaignsCallable(const GetCampaignsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetCampaignsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetCampaigns(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetCampaignsAsync(const GetCampaignsRequest& request, const GetCampaignsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetCampaignsAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetCampaignsAsyncHelper(const GetCampaignsRequest& request, const GetCampaignsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetCampaigns(request), context);
}

GetEmailChannelOutcome PinpointClient::GetEmailChannel(const GetEmailChannelRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/channels/email";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetEmailChannelOutcome(GetEmailChannelResult(outcome.GetResult()));
  }
  else
  {
    return GetEmailChannelOutcome(outcome.GetError());
  }
}

GetEmailChannelOutcomeCallable PinpointClient::GetEmailChannelCallable(const GetEmailChannelRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetEmailChannelOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetEmailChannel(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetEmailChannelAsync(const GetEmailChannelRequest& request, const GetEmailChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetEmailChannelAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetEmailChannelAsyncHelper(const GetEmailChannelRequest& request, const GetEmailChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetEmailChannel(request), context);
}

GetEndpointOutcome PinpointClient::GetEndpoint(const GetEndpointRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/endpoints/{endpoint-id}";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetEndpointOutcome(GetEndpointResult(outcome.GetResult()));
  }
  else
  {
    return GetEndpointOutcome(outcome.GetError());
  }
}

GetEndpointOutcomeCallable PinpointClient::GetEndpointCallable(const GetEndpointRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetEndpointOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetEndpoint(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetEndpointAsync(const GetEndpointRequest& request, const GetEndpointResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetEndpointAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetEndpointAsyncHelper(const GetEndpointRequest& request, const GetEndpointResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetEndpoint(request), context);
}

GetEventStreamOutcome PinpointClient::GetEventStream(const GetEventStreamRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/eventstream";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetEventStreamOutcome(GetEventStreamResult(outcome.GetResult()));
  }
  else
  {
    return GetEventStreamOutcome(outcome.GetError());
  }
}

GetEventStreamOutcomeCallable PinpointClient::GetEventStreamCallable(const GetEventStreamRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetEventStreamOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetEventStream(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetEventStreamAsync(const GetEventStreamRequest& request, const GetEventStreamResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetEventStreamAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetEventStreamAsyncHelper(const GetEventStreamRequest& request, const GetEventStreamResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetEventStream(request), context);
}

GetGcmChannelOutcome PinpointClient::GetGcmChannel(const GetGcmChannelRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/channels/gcm";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetGcmChannelOutcome(GetGcmChannelResult(outcome.GetResult()));
  }
  else
  {
    return GetGcmChannelOutcome(outcome.GetError());
  }
}

GetGcmChannelOutcomeCallable PinpointClient::GetGcmChannelCallable(const GetGcmChannelRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetGcmChannelOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetGcmChannel(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetGcmChannelAsync(const GetGcmChannelRequest& request, const GetGcmChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetGcmChannelAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetGcmChannelAsyncHelper(const GetGcmChannelRequest& request, const GetGcmChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetGcmChannel(request), context);
}

GetImportJobOutcome PinpointClient::GetImportJob(const GetImportJobRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/jobs/import/{job-id}";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetImportJobOutcome(GetImportJobResult(outcome.GetResult()));
  }
  else
  {
    return GetImportJobOutcome(outcome.GetError());
  }
}

GetImportJobOutcomeCallable PinpointClient::GetImportJobCallable(const GetImportJobRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetImportJobOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetImportJob(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetImportJobAsync(const GetImportJobRequest& request, const GetImportJobResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetImportJobAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetImportJobAsyncHelper(const GetImportJobRequest& request, const GetImportJobResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetImportJob(request), context);
}

GetImportJobsOutcome PinpointClient::GetImportJobs(const GetImportJobsRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/jobs/import";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetImportJobsOutcome(GetImportJobsResult(outcome.GetResult()));
  }
  else
  {
    return GetImportJobsOutcome(outcome.GetError());
  }
}

GetImportJobsOutcomeCallable PinpointClient::GetImportJobsCallable(const GetImportJobsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetImportJobsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetImportJobs(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetImportJobsAsync(const GetImportJobsRequest& request, const GetImportJobsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetImportJobsAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetImportJobsAsyncHelper(const GetImportJobsRequest& request, const GetImportJobsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetImportJobs(request), context);
}

GetSegmentOutcome PinpointClient::GetSegment(const GetSegmentRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/segments/{segment-id}";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetSegmentOutcome(GetSegmentResult(outcome.GetResult()));
  }
  else
  {
    return GetSegmentOutcome(outcome.GetError());
  }
}

GetSegmentOutcomeCallable PinpointClient::GetSegmentCallable(const GetSegmentRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetSegmentOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetSegment(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetSegmentAsync(const GetSegmentRequest& request, const GetSegmentResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetSegmentAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetSegmentAsyncHelper(const GetSegmentRequest& request, const GetSegmentResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetSegment(request), context);
}

GetSegmentImportJobsOutcome PinpointClient::GetSegmentImportJobs(const GetSegmentImportJobsRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/segments/{segment-id}/jobs/import";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetSegmentImportJobsOutcome(GetSegmentImportJobsResult(outcome.GetResult()));
  }
  else
  {
    return GetSegmentImportJobsOutcome(outcome.GetError());
  }
}

GetSegmentImportJobsOutcomeCallable PinpointClient::GetSegmentImportJobsCallable(const GetSegmentImportJobsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetSegmentImportJobsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetSegmentImportJobs(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetSegmentImportJobsAsync(const GetSegmentImportJobsRequest& request, const GetSegmentImportJobsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetSegmentImportJobsAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetSegmentImportJobsAsyncHelper(const GetSegmentImportJobsRequest& request, const GetSegmentImportJobsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetSegmentImportJobs(request), context);
}

GetSegmentVersionOutcome PinpointClient::GetSegmentVersion(const GetSegmentVersionRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/segments/{segment-id}/versions/";
  ss << request.GetVersion();
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetSegmentVersionOutcome(GetSegmentVersionResult(outcome.GetResult()));
  }
  else
  {
    return GetSegmentVersionOutcome(outcome.GetError());
  }
}

GetSegmentVersionOutcomeCallable PinpointClient::GetSegmentVersionCallable(const GetSegmentVersionRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetSegmentVersionOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetSegmentVersion(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetSegmentVersionAsync(const GetSegmentVersionRequest& request, const GetSegmentVersionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetSegmentVersionAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetSegmentVersionAsyncHelper(const GetSegmentVersionRequest& request, const GetSegmentVersionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetSegmentVersion(request), context);
}

GetSegmentVersionsOutcome PinpointClient::GetSegmentVersions(const GetSegmentVersionsRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/segments/{segment-id}/versions";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetSegmentVersionsOutcome(GetSegmentVersionsResult(outcome.GetResult()));
  }
  else
  {
    return GetSegmentVersionsOutcome(outcome.GetError());
  }
}

GetSegmentVersionsOutcomeCallable PinpointClient::GetSegmentVersionsCallable(const GetSegmentVersionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetSegmentVersionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetSegmentVersions(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetSegmentVersionsAsync(const GetSegmentVersionsRequest& request, const GetSegmentVersionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetSegmentVersionsAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetSegmentVersionsAsyncHelper(const GetSegmentVersionsRequest& request, const GetSegmentVersionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetSegmentVersions(request), context);
}

GetSegmentsOutcome PinpointClient::GetSegments(const GetSegmentsRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/segments";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetSegmentsOutcome(GetSegmentsResult(outcome.GetResult()));
  }
  else
  {
    return GetSegmentsOutcome(outcome.GetError());
  }
}

GetSegmentsOutcomeCallable PinpointClient::GetSegmentsCallable(const GetSegmentsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetSegmentsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetSegments(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetSegmentsAsync(const GetSegmentsRequest& request, const GetSegmentsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetSegmentsAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetSegmentsAsyncHelper(const GetSegmentsRequest& request, const GetSegmentsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetSegments(request), context);
}

GetSmsChannelOutcome PinpointClient::GetSmsChannel(const GetSmsChannelRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/channels/sms";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_GET, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return GetSmsChannelOutcome(GetSmsChannelResult(outcome.GetResult()));
  }
  else
  {
    return GetSmsChannelOutcome(outcome.GetError());
  }
}

GetSmsChannelOutcomeCallable PinpointClient::GetSmsChannelCallable(const GetSmsChannelRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetSmsChannelOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetSmsChannel(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::GetSmsChannelAsync(const GetSmsChannelRequest& request, const GetSmsChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->GetSmsChannelAsyncHelper( request, handler, context ); } );
}

void PinpointClient::GetSmsChannelAsyncHelper(const GetSmsChannelRequest& request, const GetSmsChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, GetSmsChannel(request), context);
}

PutEventStreamOutcome PinpointClient::PutEventStream(const PutEventStreamRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/eventstream";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_POST, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return PutEventStreamOutcome(PutEventStreamResult(outcome.GetResult()));
  }
  else
  {
    return PutEventStreamOutcome(outcome.GetError());
  }
}

PutEventStreamOutcomeCallable PinpointClient::PutEventStreamCallable(const PutEventStreamRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< PutEventStreamOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->PutEventStream(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::PutEventStreamAsync(const PutEventStreamRequest& request, const PutEventStreamResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->PutEventStreamAsyncHelper( request, handler, context ); } );
}

void PinpointClient::PutEventStreamAsyncHelper(const PutEventStreamRequest& request, const PutEventStreamResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, PutEventStream(request), context);
}

SendMessagesOutcome PinpointClient::SendMessages(const SendMessagesRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/messages";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_POST, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return SendMessagesOutcome(SendMessagesResult(outcome.GetResult()));
  }
  else
  {
    return SendMessagesOutcome(outcome.GetError());
  }
}

SendMessagesOutcomeCallable PinpointClient::SendMessagesCallable(const SendMessagesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< SendMessagesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->SendMessages(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::SendMessagesAsync(const SendMessagesRequest& request, const SendMessagesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->SendMessagesAsyncHelper( request, handler, context ); } );
}

void PinpointClient::SendMessagesAsyncHelper(const SendMessagesRequest& request, const SendMessagesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, SendMessages(request), context);
}

UpdateApnsChannelOutcome PinpointClient::UpdateApnsChannel(const UpdateApnsChannelRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/channels/apns";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_PUT, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return UpdateApnsChannelOutcome(UpdateApnsChannelResult(outcome.GetResult()));
  }
  else
  {
    return UpdateApnsChannelOutcome(outcome.GetError());
  }
}

UpdateApnsChannelOutcomeCallable PinpointClient::UpdateApnsChannelCallable(const UpdateApnsChannelRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< UpdateApnsChannelOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->UpdateApnsChannel(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::UpdateApnsChannelAsync(const UpdateApnsChannelRequest& request, const UpdateApnsChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->UpdateApnsChannelAsyncHelper( request, handler, context ); } );
}

void PinpointClient::UpdateApnsChannelAsyncHelper(const UpdateApnsChannelRequest& request, const UpdateApnsChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, UpdateApnsChannel(request), context);
}

UpdateApnsSandboxChannelOutcome PinpointClient::UpdateApnsSandboxChannel(const UpdateApnsSandboxChannelRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/channels/apns_sandbox";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_PUT, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return UpdateApnsSandboxChannelOutcome(UpdateApnsSandboxChannelResult(outcome.GetResult()));
  }
  else
  {
    return UpdateApnsSandboxChannelOutcome(outcome.GetError());
  }
}

UpdateApnsSandboxChannelOutcomeCallable PinpointClient::UpdateApnsSandboxChannelCallable(const UpdateApnsSandboxChannelRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< UpdateApnsSandboxChannelOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->UpdateApnsSandboxChannel(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::UpdateApnsSandboxChannelAsync(const UpdateApnsSandboxChannelRequest& request, const UpdateApnsSandboxChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->UpdateApnsSandboxChannelAsyncHelper( request, handler, context ); } );
}

void PinpointClient::UpdateApnsSandboxChannelAsyncHelper(const UpdateApnsSandboxChannelRequest& request, const UpdateApnsSandboxChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, UpdateApnsSandboxChannel(request), context);
}

UpdateApplicationSettingsOutcome PinpointClient::UpdateApplicationSettings(const UpdateApplicationSettingsRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/settings";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_PUT, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return UpdateApplicationSettingsOutcome(UpdateApplicationSettingsResult(outcome.GetResult()));
  }
  else
  {
    return UpdateApplicationSettingsOutcome(outcome.GetError());
  }
}

UpdateApplicationSettingsOutcomeCallable PinpointClient::UpdateApplicationSettingsCallable(const UpdateApplicationSettingsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< UpdateApplicationSettingsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->UpdateApplicationSettings(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::UpdateApplicationSettingsAsync(const UpdateApplicationSettingsRequest& request, const UpdateApplicationSettingsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->UpdateApplicationSettingsAsyncHelper( request, handler, context ); } );
}

void PinpointClient::UpdateApplicationSettingsAsyncHelper(const UpdateApplicationSettingsRequest& request, const UpdateApplicationSettingsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, UpdateApplicationSettings(request), context);
}

UpdateCampaignOutcome PinpointClient::UpdateCampaign(const UpdateCampaignRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/campaigns/{campaign-id}";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_PUT, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return UpdateCampaignOutcome(UpdateCampaignResult(outcome.GetResult()));
  }
  else
  {
    return UpdateCampaignOutcome(outcome.GetError());
  }
}

UpdateCampaignOutcomeCallable PinpointClient::UpdateCampaignCallable(const UpdateCampaignRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< UpdateCampaignOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->UpdateCampaign(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::UpdateCampaignAsync(const UpdateCampaignRequest& request, const UpdateCampaignResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->UpdateCampaignAsyncHelper( request, handler, context ); } );
}

void PinpointClient::UpdateCampaignAsyncHelper(const UpdateCampaignRequest& request, const UpdateCampaignResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, UpdateCampaign(request), context);
}

UpdateEmailChannelOutcome PinpointClient::UpdateEmailChannel(const UpdateEmailChannelRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/channels/email";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_PUT, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return UpdateEmailChannelOutcome(UpdateEmailChannelResult(outcome.GetResult()));
  }
  else
  {
    return UpdateEmailChannelOutcome(outcome.GetError());
  }
}

UpdateEmailChannelOutcomeCallable PinpointClient::UpdateEmailChannelCallable(const UpdateEmailChannelRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< UpdateEmailChannelOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->UpdateEmailChannel(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::UpdateEmailChannelAsync(const UpdateEmailChannelRequest& request, const UpdateEmailChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->UpdateEmailChannelAsyncHelper( request, handler, context ); } );
}

void PinpointClient::UpdateEmailChannelAsyncHelper(const UpdateEmailChannelRequest& request, const UpdateEmailChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, UpdateEmailChannel(request), context);
}

UpdateEndpointOutcome PinpointClient::UpdateEndpoint(const UpdateEndpointRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/endpoints/{endpoint-id}";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_PUT, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return UpdateEndpointOutcome(UpdateEndpointResult(outcome.GetResult()));
  }
  else
  {
    return UpdateEndpointOutcome(outcome.GetError());
  }
}

UpdateEndpointOutcomeCallable PinpointClient::UpdateEndpointCallable(const UpdateEndpointRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< UpdateEndpointOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->UpdateEndpoint(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::UpdateEndpointAsync(const UpdateEndpointRequest& request, const UpdateEndpointResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->UpdateEndpointAsyncHelper( request, handler, context ); } );
}

void PinpointClient::UpdateEndpointAsyncHelper(const UpdateEndpointRequest& request, const UpdateEndpointResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, UpdateEndpoint(request), context);
}

UpdateEndpointsBatchOutcome PinpointClient::UpdateEndpointsBatch(const UpdateEndpointsBatchRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/endpoints";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_PUT, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return UpdateEndpointsBatchOutcome(UpdateEndpointsBatchResult(outcome.GetResult()));
  }
  else
  {
    return UpdateEndpointsBatchOutcome(outcome.GetError());
  }
}

UpdateEndpointsBatchOutcomeCallable PinpointClient::UpdateEndpointsBatchCallable(const UpdateEndpointsBatchRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< UpdateEndpointsBatchOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->UpdateEndpointsBatch(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::UpdateEndpointsBatchAsync(const UpdateEndpointsBatchRequest& request, const UpdateEndpointsBatchResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->UpdateEndpointsBatchAsyncHelper( request, handler, context ); } );
}

void PinpointClient::UpdateEndpointsBatchAsyncHelper(const UpdateEndpointsBatchRequest& request, const UpdateEndpointsBatchResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, UpdateEndpointsBatch(request), context);
}

UpdateGcmChannelOutcome PinpointClient::UpdateGcmChannel(const UpdateGcmChannelRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/channels/gcm";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_PUT, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return UpdateGcmChannelOutcome(UpdateGcmChannelResult(outcome.GetResult()));
  }
  else
  {
    return UpdateGcmChannelOutcome(outcome.GetError());
  }
}

UpdateGcmChannelOutcomeCallable PinpointClient::UpdateGcmChannelCallable(const UpdateGcmChannelRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< UpdateGcmChannelOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->UpdateGcmChannel(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::UpdateGcmChannelAsync(const UpdateGcmChannelRequest& request, const UpdateGcmChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->UpdateGcmChannelAsyncHelper( request, handler, context ); } );
}

void PinpointClient::UpdateGcmChannelAsyncHelper(const UpdateGcmChannelRequest& request, const UpdateGcmChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, UpdateGcmChannel(request), context);
}

UpdateSegmentOutcome PinpointClient::UpdateSegment(const UpdateSegmentRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/segments/{segment-id}";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_PUT, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return UpdateSegmentOutcome(UpdateSegmentResult(outcome.GetResult()));
  }
  else
  {
    return UpdateSegmentOutcome(outcome.GetError());
  }
}

UpdateSegmentOutcomeCallable PinpointClient::UpdateSegmentCallable(const UpdateSegmentRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< UpdateSegmentOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->UpdateSegment(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::UpdateSegmentAsync(const UpdateSegmentRequest& request, const UpdateSegmentResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->UpdateSegmentAsyncHelper( request, handler, context ); } );
}

void PinpointClient::UpdateSegmentAsyncHelper(const UpdateSegmentRequest& request, const UpdateSegmentResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, UpdateSegment(request), context);
}

UpdateSmsChannelOutcome PinpointClient::UpdateSmsChannel(const UpdateSmsChannelRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/apps/{application-id}/channels/sms";
  uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_PUT, Aws::Auth::SIGV4_SIGNER);
  if(outcome.IsSuccess())
  {
    return UpdateSmsChannelOutcome(UpdateSmsChannelResult(outcome.GetResult()));
  }
  else
  {
    return UpdateSmsChannelOutcome(outcome.GetError());
  }
}

UpdateSmsChannelOutcomeCallable PinpointClient::UpdateSmsChannelCallable(const UpdateSmsChannelRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< UpdateSmsChannelOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->UpdateSmsChannel(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void PinpointClient::UpdateSmsChannelAsync(const UpdateSmsChannelRequest& request, const UpdateSmsChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context](){ this->UpdateSmsChannelAsyncHelper( request, handler, context ); } );
}

void PinpointClient::UpdateSmsChannelAsyncHelper(const UpdateSmsChannelRequest& request, const UpdateSmsChannelResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  handler(this, request, UpdateSmsChannel(request), context);
}

