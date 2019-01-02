#include "RadonFrameworkEnterprise/Net/DNS/SystemResolver.hpp"
#include "RadonFramework/System/Network/NetService.hpp"

namespace RadonFrameworkEnterprise::Net::DNS
{

IPHostEntry SystemResolver::Lookup(const Hostname& Value)
{
  
	return IPHostEntry(Value.RawName());
}

}