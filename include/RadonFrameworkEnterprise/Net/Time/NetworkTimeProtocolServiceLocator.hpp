#ifndef RFE_NETWORKTIMEPROTOCOLSERVICELOCATOR_HPP
#define RFE_NETWORKTIMEPROTOCOLSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFrameworkEnterprise/Net/Time/TimeService.hpp>

namespace RadonFrameworkEnterprise::Net::Time {

class NullTimeService :public TimeService
{
public:
	NullTimeService(const RF_Type::String &Name)
	:TimeService(Name)
	{
	}
};

typedef Core::Pattern::Locator<TimeService, NullTimeService> TimeServiceLocator;

}

#ifndef RFE_SHORTHAND_NAMESPACE_TIME
#define RFE_SHORTHAND_NAMESPACE_TIME
namespace RFE_Time = RadonFrameworkEnterprise::Net::Time;
#endif

#endif // RFE_NETWORKTIMEPROTOCOLSERVICELOCATOR_HPP
