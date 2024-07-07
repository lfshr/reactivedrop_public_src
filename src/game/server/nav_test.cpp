
#include "cbase.h"
#include "nav_test.h";

// NOTE: This has to be the last file included!
#include "nav.h"

#include "winlite.h"
#include "tier0/memdbgon.h"

CNavTest::CNavTest(void) :
	m_PathConnectAttributes(0)
{
	ListenForGameEvent("round_start");
}

CNavTest::~CNavTest()
{
	
}

void CNavTest::FireGameEvent(IGameEvent* event)
{
	
}

NavConnectAttributeTypeLookup TheNavConnectAttributeTable[] =
{
	{ "COMMONS_ONLY", NAV_CONNECT_COMMONS_ONLY },
	{ "INFECTED_ONLY", NAV_CONNECT_INFECTED_ONLY }
};

static int NavConnectAttributeAutocomplete( const char *input, char commands[ COMMAND_COMPLETION_MAXITEMS ][ COMMAND_COMPLETION_ITEM_LENGTH ])
{
	if (Q_strlen( input ) >= COMMAND_COMPLETION_ITEM_LENGTH)
	{
		return 0;
	}

	char command[ COMMAND_COMPLETION_ITEM_LENGTH+1 ];
	Q_strncpy(command, input, sizeof(command));

	// skip to start of argument
	char* partialArg = Q_strrchr(command, ' ');
	if(partialArg == NULL)
	{
		return 0;
	}

	*partialArg = '\000';
	++partialArg;

	int partialArgLength = Q_strlen(partialArg);
	int count = 0;
	for (unsigned int i = 0; TheNavConnectAttributeTable[i].name && count < COMMAND_COMPLETION_MAXITEMS; ++i)
	{
		if(!Q_strncmp(TheNavConnectAttributeTable[i].name, partialArg, partialArgLength))
		{
			// Add to the autocomplete array
			Q_snprintf(commands[count++], COMMAND_COMPLETION_ITEM_LENGTH, "%s %s", command, TheNavConnectAttributeTable[i].name);
		}
	}
	
	return count;
}

NavConnectAttributeType NameToNavConnectAttribute( const char *name )
{
	for(unsigned int i=0; TheNavConnectAttributeTable[i].name; ++i)
	{
		if (!Q_stricmp( TheNavConnectAttributeTable[i].name, name ))
		{
			return TheNavConnectAttributeTable[i].attribute;
		}
	}

	return (NavConnectAttributeType)0;
}

void CommandNavTestPathSetAttributes( const CCommand &args )
{
	int connectFlags = 0;

	// skip first arg
	for(int i = 1; i < args.ArgC(); ++i)
	{
		int attribute = NameToNavConnectAttribute(args[i]);
		connectFlags |= attribute;
	}

	TheNavTest->SetPathConnectAttributes(connectFlags);
	Msg("Set path connect test flags to %d\n", connectFlags);
}
static ConCommand NavTestPathSetAttribute("nav_test_path_set_attribute", CommandNavTestPathSetAttributes, "Set nav attributes for the path test", FCVAR_CHEAT, NavConnectAttributeAutocomplete);