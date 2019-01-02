#ifndef RFE_SERVERRESOLVER_HPP
#define RFE_SERVERRESOLVER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Radon.hpp>
#include <RadonFrameworkEnterprise/Net/DNS/AbstractResolver.hpp>

namespace RadonFrameworkEnterprise::Net::DNS {

class ServerResolver : public AbstractResolver
{
public:
	virtual IPHostEntry Lookup(const Hostname& Value) override;
};

}

#ifndef RFE_SHORTHAND_NAMESPACE_DNS
#define RFE_SHORTHAND_NAMESPACE_DNS
namespace RFE_DNS = RadonFrameworkEnterprise::Net::DNS;
#endif

#endif // RFE_SERVERRESOLVER_HPP