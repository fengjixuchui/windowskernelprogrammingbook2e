#include "pch.h"
#include "ExecutiveResource.h"

void ExecutiveResource::Init() {
	ExInitializeResourceLite(&m_res);
}

void ExecutiveResource::Delete() {
	ExDeleteResourceLite(&m_res);
}

void ExecutiveResource::Lock() {
	m_CritRegion = KeAreApcsDisabled();
	if(m_CritRegion)
		ExAcquireResourceExclusiveLite(&m_res, TRUE);
	else
		ExEnterCriticalRegionAndAcquireResourceExclusive(&m_res);
}

void ExecutiveResource::Unlock() {
	if (m_CritRegion)
		ExReleaseResourceLite(&m_res);
	else
		ExReleaseResourceAndLeaveCriticalRegion(&m_res);
}

void ExecutiveResource::LockShared() {
	m_CritRegion = KeAreApcsDisabled();
	if (m_CritRegion)
		ExAcquireResourceSharedLite(&m_res, TRUE);
	else
		ExEnterCriticalRegionAndAcquireResourceShared(&m_res);
}

void ExecutiveResource::UnlockShared() {
	Unlock();
}
