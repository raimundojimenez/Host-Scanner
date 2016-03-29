#include "OpSysIdentifier.h"
#include "UbuntuIdentifier.h"
#include "DebianIdentifier.h"
#include "EnterpriseLinuxIdentifier.h"
#include "FedoraIdentifier.h"

using namespace std;

bool OpSysIdentifier::AutoProcess(Host* host)
{
	// Ubuntu is tried first, since some distributions tag them as
	// "Debian-Ubuntu", which might trigger a false-positive with
	// DebianIdentifier, if not ruled out by UbuntuIdentifier first

	static UbuntuIdentifier ubuntu;

	if (ubuntu.Scan(host))
	{
		return true;
	}

	// as OpenSSH in Debian has a DebianBanner feature added, which is
	// on by default, Debian is the easiest to map based on SSH version

	static DebianIdentifier debian;

	if (debian.Scan(host))
	{
		return true;
	}

	// if everything failed so far, try RHEL/CentOS, however these
	// cannot be mapped with 100% certainty by the SSH version alone

	static EnterpriseLinuxIdentifier rhel;

	if (rhel.Scan(host))
	{
		return true;
	}

	// lastly try Fedora, however since most packages overlap in
	// Fedora, the identified distribution may not be completely
	// accurate, depending on the update/upgrade habits of the admin

	static FedoraIdentifier fedora;

	if (fedora.Scan(host))
	{
		return true;
	}

	return false;
}

OpSysIdentifier::~OpSysIdentifier()
{
}
