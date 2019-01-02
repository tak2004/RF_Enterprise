#include "RadonFrameworkEnterprise/Net/Time/TimeService.hpp"

namespace RadonFrameworkEnterprise::Net::Time
{
TimeService::TimeService(const RF_Type::String& Name)
: RF_Pattern::Service(Name),
  m_CanUseAsyncDNS(false),
  m_UseAsyncDNS(true),
  m_FreezeConfig(false)
{
}

TimeService::~TimeService() {}

void TimeService::UseAsynchronousDNS(RF_Type::Bool Yes /*= true*/)
{
  if(!m_FreezeConfig)
  {
    m_UseAsyncDNS = Yes;
  }
}

void TimeService::Start()
{
  m_FreezeConfig = true;
}

void TimeService::Stop()
{
  m_FreezeConfig = false;
}

void TimeService::Update() {}

RF_Type::Bool TimeService::IsUsingAsynchronousDNS() const
{
  return m_UseAsyncDNS;
}

RF_Type::Bool TimeService::CanUseAsynchronousDNS() const
{
  return m_CanUseAsyncDNS;
}

RF_Type::Bool TimeService::SetPrimaryServer(const Hostname& Value)
{
  if(!m_FreezeConfig)
  {
    m_PrimaryServer = Value;
  }
  return !m_FreezeConfig;
}

RF_Type::Bool TimeService::AddAlternateServer(const Hostname& Value)
{
  if(!m_FreezeConfig)
  {
    m_AlternateServers.AddLast(Value);
  }
  return !m_FreezeConfig;
}

void TimeService::ClearAlternateServerList()
{
  if(!m_FreezeConfig)
  {
    m_AlternateServers.Clear();
  }
}

const Hostname& TimeService::GetPrimaryServer() const
{
  return m_PrimaryServer;
}

const RF_Collect::List<Hostname>&
TimeService::GetAlternateServers() const
{
  return m_AlternateServers;
}

RF_Type::Bool TimeService::IsRunning() const
{
  // the config is no longer changeable if the service is running
  return m_FreezeConfig;
}

}  // namespace RadonFrameworkEnterprise::Net::Time