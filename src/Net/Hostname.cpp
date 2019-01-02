#include "RadonFramework/precompiled.hpp"
#include "RadonFrameworkEnterprise/Net/Hostname.hpp"

namespace RadonFrameworkEnterprise::Net
{

RF_Mem::AutoPointer<Hostname>
Hostname::Create(const RF_Type::String WithHostname)
{
  RF_Mem::AutoPointer<Hostname> result;
  if(RF_Net::IPAddress ip; RF_Net::IPAddress::IsValidIP(WithHostname) ||
                           RF_Net::IPAddress::Resolve(WithHostname, ip))
  {
    result.Reset(new Hostname());
    result->m_Name = WithHostname;
  }
  return result;
}

Hostname::Hostname() : m_Name("localhost"_rfs) {}

Hostname::Hostname(const RF_Net::IPAddress& IP)
{
  m_Name = IP.ToString();
}

RF_Type::String Hostname::CanonicalName() const
{
  return RF_Type::String();
}

const RF_Type::String& Hostname::RawName() const
{
  return m_Name;
}

}  // namespace RadonFrameworkEnterprise::Net