#pragma once
#include "cbase.h"
#include "GameEventListener.h"
#include "nav.h"

struct NavConnectAttributeTypeLookup
{
	const char* name;
	NavConnectAttributeType attribute;
};

class CNavTest : public CGameEventListener
{
public:
	CNavTest(void);
	virtual ~CNavTest();

	virtual void FireGameEvent(IGameEvent* event);

	FORCEINLINE void SetPathConnectAttributes(int attributes) { m_PathConnectAttributes = attributes; }
	FORCEINLINE int GetPathConnectAttributes() const { return m_PathConnectAttributes; }

private:
	int m_PathConnectAttributes;

};

CNavTest* TheNavTest;