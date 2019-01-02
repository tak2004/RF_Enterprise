#ifndef RFE_SIMPLENETWORKTIMEPROTOCOL4SERVICE_HPP
#define RFE_SIMPLENETWORKTIMEPROTOCOL4SERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Radon.hpp>
#include <RadonFrameworkEnterprise/Net/Time/TimeService.hpp>

namespace RadonFrameworkEnterprise::Net::Time
{
class SimpleNetworkTimeProtocol4Service : public TimeService
{
public:
  SimpleNetworkTimeProtocol4Service(const RF_Type::String& Name);
  virtual ~SimpleNetworkTimeProtocol4Service() override;

  virtual void Start() override;
  virtual void Update() override;
  virtual void Stop() override;

protected:
  RF_Net::IPAddress m_Server;
};

}  // namespace RadonFrameworkEnterprise::Net::Time

#ifndef RFE_SHORTHAND_NAMESPACE_TIME
#define RFE_SHORTHAND_NAMESPACE_TIME
namespace RFE_Time = RadonFrameworkEnterprise::Net::Time;
#endif

#endif  // RFE_SIMPLENETWORKTIMEPROTOCOL4SERVICE_HPP