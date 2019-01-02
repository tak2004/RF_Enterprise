#include <RadonFramework/Radon.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Test/TestResultCollector.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/BriefProgressCollector.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/DebugCollector.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/JUnitOutput.hpp>
#include <RadonFramework/Diagnostics/Test/TestResult.hpp>
#include <RadonFramework/IO/Log.hpp>
#include <RadonFramework/IO/LogConsole.hpp>
#include <RadonFramework/Diagnostics/Appender.hpp>
#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/System/IO/FileSystem.hpp>
#include <RadonFramework/IO/Uri.hpp>
#include <RadonFramework/Threading/ThreadPool.hpp>

using namespace RadonFramework::IO;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Diagnostics;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework;
using namespace RadonFramework::System::IO;

enum class WebServiceScheme
{
	HTTP,
	HTTPS
};

RF_Type::UInt16 DefaultPortOfScheme(const WebServiceScheme Scheme)
{
	auto result = 0;
	switch(Scheme)
	{
	case WebServiceScheme::HTTP:
		result = 80;
		break;
	case WebServiceScheme::HTTPS:
		result = 443;
		break;
	}
	return result;
}

RF_Type::Bool GetWebSericeScheme(const RF_Type::String& Scheme, WebServiceScheme& Out)
{
	auto result = false;
	if (Scheme.ToLower() == "http"_rfs)
	{
		Out = WebServiceScheme::HTTP;
		result = true;
	}
	if (Scheme.ToLower() == "https"_rfs)
	{
		Out = WebServiceScheme::HTTPS;
		result = true;
	}
	return result;
}

// Faster check compared to the string version, because URI scheme must be lower case.
RF_Type::Bool GetWebSericeScheme(const RF_IO::Uri& URI, WebServiceScheme& Out)
{
	auto result = false;
	if (URI.Scheme() == "http"_rfs)
	{
		Out = WebServiceScheme::HTTP;
		result = true;
	}
	if (URI.Scheme() == "https"_rfs)
	{
		Out = WebServiceScheme::HTTPS;
		result = true;
	}
	return result;
}

int main(int argc, char** argv)
{
	Radon framework;

	AutoPointer<Appender> console(new LogConsole);
	AutoPointer<Appender> debugOut(new LogDebuggerOutput);
	Log::AddAppender(console);
	Log::AddAppender(debugOut);

	auto startingHTTP2 = R"(
	An HTTP/2 connection is an application-layer protocol running on top
    of a TCP connection. 

	$IsTCPConnection
	
	The client is the TCP connection initiator.

    HTTP/2 uses the same "http" and "https" URI schemes used by HTTP/1.1. 
    HTTP/2 shares the same default port numbers: {80} for "{http}" URIs and
    {443} for "{https}" URIs.  As a result, implementations processing       $CheckPortAssignment
    requests for target resource URIs like "{http://example.org/foo}" or
    "{https://example.com/bar}" are required to first discover whether the
    upstream server (the immediate peer to which the client wishes to
    establish a connection) supports HTTP/2.                               $SchemeOfURI

    The means by which support for HTTP/2 is determined is different for
    "http" and "https" URIs.  Discovery for "http" URIs is described in
    Section 3.2.  Discovery for "https" URIs is described in Section 3.3.
	)"_rfsp;
	startingHTTP2.AddFunction("IsTCPConnection"_rfs, [](const auto& Parameters) {

		return false;
	}); 
	startingHTTP2.AddFunction("CheckPortAssignment"_rfs, [](const auto& Parameters) {
		RF_Type::UInt16 defaultHTTPPort;
		RF_Type::UInt16 defaultHTTPSPort;
		RF_Type::Convert::ToUInt16(Parameters(0), defaultHTTPPort);
		RF_Type::Convert::ToUInt16(Parameters(2), defaultHTTPSPort);
		WebServiceScheme http, https;
		auto isValidScheme = GetWebSericeScheme(Parameters(1), http);
		isValidScheme = isValidScheme & GetWebSericeScheme(Parameters(3), https);
		return isValidScheme && 
			DefaultPortOfScheme(http) == defaultHTTPPort &&
			DefaultPortOfScheme(https) == defaultHTTPSPort;
	});
	startingHTTP2.AddFunction("SchemeOfURI"_rfs, [](const auto& Parameters) {
		RF_IO::Uri isHTTPURI(Parameters(0));		
		RF_IO::Uri isHTTPSURI(Parameters(1));
		WebServiceScheme http, https;
		auto isValidScheme = GetWebSericeScheme(isHTTPURI.Scheme(), http);
		isValidScheme = isValidScheme & GetWebSericeScheme(isHTTPSURI.Scheme(), https);
		return isValidScheme && http == WebServiceScheme::HTTP && https == WebServiceScheme::HTTPS;
	});
	if (startingHTTP2.IsSyntaxCorrect())
	{
		startingHTTP2.Test();
		RF_BDD::ConsoleOutput output;
		startingHTTP2.Generate(output);
	}

	auto HTTP2VersionIdentification = R"(
3.1. HTTP / 2 Version Identification

	The protocol defined in this document has two identifiers.

	o  The string "{h2}" identifies the protocol where HTTP / 2 uses
	   Transport Layer Security({TLS})[TLS12].This identifier is used
	   in the TLS application - layer protocol negotiation(ALPN) extension
	   [TLS - ALPN] field and in any place where HTTP / 2 over TLS is
	   identified.                                                         $NeedTLS

	   The "{h2}" string is serialized into an ALPN protocol identifier as
	   the two - octet sequence : {0x68}, {0x32}.                          $Serialized

	o  The string "h2c" identifies the protocol where HTTP / 2 is run over
	   cleartext TCP.This identifier is used in the HTTP / 1.1 Upgrade
	   header field and in any place where HTTP / 2 over TCP is identified. $

	   The "h2c" string is reserved from the ALPN identifier space but
	   describes a protocol that does not use TLS.

	Negotiating "h2" or "h2c" implies the use of the transport, security,
	framing, and message semantics described in this document.
	)"_rfsp;
	HTTP2VersionIdentification.AddFunction("IsTCPConnection"_rfs, [](const auto& Parameters) {

		return false;
	});
	RF_Pattern::Singleton<Threading::ThreadPool>::GetInstance().DisableAndWaitTillDone();
	return 0;
}