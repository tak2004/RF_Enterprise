#include "RadonFrameworkEnterprise/Net/DNS/ServerResolver.hpp"
#include "RadonFramework/System/Network/NetService.hpp"

namespace RadonFrameworkEnterprise::Net::DNS
{

IPHostEntry ServerResolver::Lookup(const Hostname& Value)
{
  return IPHostEntry(Value.RawName());
}

}  // namespace RadonFrameworkEnterprise::Net::DNS