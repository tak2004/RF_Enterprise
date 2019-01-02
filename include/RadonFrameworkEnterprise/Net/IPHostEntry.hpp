#ifndef RFE_IPHOSTENTRY_HPP
#define RFE_IPHOSTENTRY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/IPAddress.hpp>
#include <RadonFramework/Collections/List.hpp>

namespace RadonFrameworkEnterprise::Net
{

class IPHostEntry
{
public:
    IPHostEntry(const RF_Type::String &Hostname);
    IPHostEntry(const RF_Type::String &Hostname,
                const RF_Collect::List<RF_Type::String> &Aliases,
                const RF_Collect::List<RF_Net::IPAddress>& AddressList);

    const RF_Type::String& Hostname()const;
    const RF_Collect::List<RF_Type::String>& Aliases() const;
    const RF_Collect::List<RF_Net::IPAddress>& AddressList() const;

    void AddAddress(const RF_Net::IPAddress& Address);
protected:
    RF_Type::String m_Hostname;
    RF_Collect::List<RF_Type::String> m_Aliases;
    RF_Collect::List<RF_Net::IPAddress> m_AddressList;
};

}

#ifndef RFE_SHORTHAND_NAMESPACE_NET
#define RFE_SHORTHAND_NAMESPACE_NET
namespace RFE_Net = RadonFrameworkEnterprise::Net;
#endif

#endif
