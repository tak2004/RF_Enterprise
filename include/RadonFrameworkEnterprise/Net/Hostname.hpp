#ifndef RFE_HOSTNAME_HPP
#define RFE_HOSTNAME_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/IPAddress.hpp>

namespace RadonFrameworkEnterprise::Net
{

class Hostname
{
public:
  /// Create an instance if the specified Hostname is valid or represent an IP.
  static RF_Mem::AutoPointer<Hostname> Create(const RF_Type::String WithHostname);

  /// Will create an instance which is using "localhost" as hostname.
  Hostname();
  /// Will create an instance which use the IP address as hostname.
  explicit Hostname(const RF_Net::IPAddress& IP);

  RF_Type::String CanonicalName() const;
  const RF_Type::String& RawName() const;
private:
  RF_Type::String m_Name;
};

}

#ifndef RFE_SHORTHAND_NAMESPACE_NET
#define RFE_SHORTHAND_NAMESPACE_NET
namespace RFE_Net = RadonFrameworkEnterprise::Net;
#endif

#endif