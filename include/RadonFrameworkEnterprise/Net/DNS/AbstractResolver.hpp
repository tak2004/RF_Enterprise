#ifndef RFE_ABSTRACTRESOLVER_HPP
#define RFE_ABSTRACTRESOLVER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Radon.hpp>
#include <RadonFrameworkEnterprise/Net/IPHostEntry.hpp>
#include <RadonFrameworkEnterprise/Net/Hostname.hpp>

namespace RadonFrameworkEnterprise::Net::DNS
{

class AbstractResolver
{
public:
  virtual RFE_Net::IPHostEntry Lookup(const Hostname& Value) = 0;
};

}  // namespace RadonFrameworkEnterprise::Net::DNS

#ifndef RFE_SHORTHAND_NAMESPACE_DNS
#define RFE_SHORTHAND_NAMESPACE_DNS
namespace RFE_DNS = RadonFrameworkEnterprise::Net::DNS;
#endif

#endif  // RFE_ABSTRACTRESOLVER_HPP