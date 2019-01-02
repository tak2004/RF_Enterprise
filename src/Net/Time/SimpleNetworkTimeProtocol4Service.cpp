#include "RadonFrameworkEnterprise/Net/Time/SimpleNetworkTimeProtocol4Service.hpp"
#include "RadonFrameworkEnterprise/Net/DNS/ServerResolver.hpp"
#include "RadonFrameworkEnterprise/Net/DNS/SystemResolver.hpp"

namespace RadonFrameworkEnterprise::Net::Time
{

SimpleNetworkTimeProtocol4Service::SimpleNetworkTimeProtocol4Service(
    const RF_Type::String& Name)
: TimeService(Name)
{
}

SimpleNetworkTimeProtocol4Service::~SimpleNetworkTimeProtocol4Service() {}

void SimpleNetworkTimeProtocol4Service::Start()
{
  TimeService::Start();
  RFE_DNS::SystemResolver solver;
  auto entry = solver.Lookup(m_PrimaryServer);
  if(!entry.Aliases().IsEmpty())
  {
    m_Server = entry.AddressList()[0];
  }
  else
  {
  }
  RFE_DNS::ServerResolver remoteSolver;
  //	auto entries = remoteSolver.Lookup(m_AlternateServers);
}

void SimpleNetworkTimeProtocol4Service::Update()
{
  TimeService::Update();
}

void SimpleNetworkTimeProtocol4Service::Stop()
{
  TimeService::Stop();
}

}  // namespace RadonFrameworkEnterprise::Net::Time