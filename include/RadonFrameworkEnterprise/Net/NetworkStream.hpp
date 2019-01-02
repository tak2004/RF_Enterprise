#ifndef RFE_NETWORK_NETWORKSTREAM_HPP
#define RFE_NETWORK_NETWORKSTREAM_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>

namespace RadonFramework::Net
{
class Socket;
}

namespace RadonFrameworkEnterprise::Net
{
class NetworkStream
{
public:
  using ByteBuffer = RF_Mem::AutoPointerArray<RF_Type::UInt8>;
  using Socket = RadonFramework::Net::Socket;

  explicit NetworkStream(const Socket& UseSocket);
  void Send(const ByteBuffer& Buffer,
            void (*Async)(const ByteBuffer&, Socket&));
  void Receive(ByteBuffer& Buffer, void (*Async)(ByteBuffer&, Socket&));

protected:
  Socket* m_Socket;
};
}  // namespace RadonFrameworkEnterprise::Net

#ifndef RFE_SHORTHAND_NAMESPACE_NET
#define RFE_SHORTHAND_NAMESPACE_NET
namespace RFE_Net = RadonFrameworkEnterprise::Net;
#endif

#endif