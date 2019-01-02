#ifndef RFE_NTPPACKETHEADER_HPP
#define RFE_NTPPACKETHEADER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Radon.hpp>
#include <RadonFramework/Core/Pattern/Service.hpp>

namespace RadonFrameworkEnterprise::Net::Time::NTP {

RF_ALIGN(1)
struct SNTPHeader
{
	enum class RF_Type::UInt8 LeapIndicator : 2
	{
		NoWarning=0,
		LastMinuteHas61Seconds=1,
		LastMinuteHas59Seconds=2,
		AlarmCondition=3
	};
	RF_Type::UInt8 VersionNumber : 3;
	enum class RF_Type::UInt8 Mode : 3
	{
		Reserved = 0,
			SymetricActive = 1,
			SymetricPassive = 2,
			Client = 3,
			Server = 4,
			Broadcast = 5,
			ReservedForNTPControlMessage = 6,
			ReservedForPrivateUser = 7
	};
	RF_Type::UInt8 Stratum;
	RF_Type::UInt8 Poll;
	RF_Type::UInt8 Precision;
	RF_Type::UInt32 RootDelay;
	RF_Type::UInt32 RootDispersion;
	RF_Type::UInt64 ReferenceTimestamp;
	RF_Type::UInt64 OriginateTimestamp;
	RF_Type::UInt64 ReceiveTimestamp;
	RF_Type::UInt64 TransmitTimestamp;
};

RF_ALIGN(1)
struct NTPFooter
{
	RF_Type::UInt32 KeyIdentifier;
	RF_Type::UInt8 MessageDigest[128];
};

RF_ALIGN(1)
struct NTPExtensionHeader
{
	RF_Type::UInt16 FieldType;
	RF_Type::UInt16 Length;
};

RF_ALIGN(1)
struct SNTPHeaderWithAuthentication : public SNTPHeader, public NTPFooter;

}

#ifndef RFE_NTP_HPP
#define RFE_NTP_HPP
namespace RFE_NTP = RadonFrameworkEnterprise::Net::Time::NTP;
#endif

#endif // RFE_NTPPACKETHEADER_HPP
