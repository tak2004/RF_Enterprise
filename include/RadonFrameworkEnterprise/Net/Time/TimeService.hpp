#ifndef RFE_TIMESERVICE_HPP
#define RFE_TIMESERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Radon.hpp>
#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFrameworkEnterprise/Net/Hostname.hpp>

namespace RadonFrameworkEnterprise::Net::Time {

class TimeService :public RF_Pattern::Service
{
public:
	TimeService(const RF_Type::String &Name);
	virtual ~TimeService() override;

	RF_Type::Bool IsUsingAsynchronousDNS()const;
  RF_Type::Bool CanUseAsynchronousDNS() const;
	virtual void UseAsynchronousDNS(RF_Type::Bool Yes = true);

	RF_Type::Bool SetPrimaryServer(const RFE_Net::Hostname& Value);
  RF_Type::Bool AddAlternateServer(const RFE_Net::Hostname& Value);
	void ClearAlternateServerList();
	const RFE_Net::Hostname& GetPrimaryServer()const;
  const RF_Collect::List<RFE_Net::Hostname>& GetAlternateServers() const;
  RF_Type::Bool IsRunning()const;

	virtual void Start();
	virtual void Stop();
	virtual void Update();
protected:
  RF_Type::Bool m_CanUseAsyncDNS;
  RF_Type::Bool m_UseAsyncDNS;
	RF_Type::Bool m_FreezeConfig;
  RFE_Net::Hostname m_PrimaryServer;
  RF_Collect::List<RFE_Net::Hostname> m_AlternateServers;
};

}

#ifndef RFE_TIMESERVICE_HPP
#define RFE_TIMESERVICE_HPP
namespace RFE_Time = RadonFrameworkEnterprise::Net::Time;
#endif

#endif // RFE_TIMESERVICE_HPP
