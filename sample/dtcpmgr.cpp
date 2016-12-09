/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/


/**
* @defgroup dtcp
* @{
* @defgroup sample
* @{
**/


#include <iostream>
#include <stdio.h>
#include "dtcpmgr.h"

static int started = 0;
static int initialized = 0;
typedef struct
{
	int id;
}sessionHandle;


dtcp_result_t DTCPMgrInitialize(void)
{
	printf("Entered fucntion %s\n",__PRETTY_FUNCTION__);
	if (initialized == 0)
	{
		printf("initialized Manager\n");
		initialized = 1;
	}
	else
	{
		printf("Already initialized\n");
	}
	return DTCP_SUCCESS;
}
	
dtcp_result_t DTCPMgrStartSource(char* ifName, int portNum)
{
	printf("Entered fucntion %s\n",__PRETTY_FUNCTION__);
	printf("invoked start source with IFNAME: %s , port number: %d\n",ifName,portNum);
	return DTCP_SUCCESS;
}

dtcp_result_t DTCPMgrStopSource(void)
{
	printf("Entered fucntion %s\n",__PRETTY_FUNCTION__);
	if (initialized == 1)
	{
		printf("stopped DTCP Manager\n");
		initialized = 0;
	}
	else
	{
		printf ("Already stopped\n");
	}
	return DTCP_SUCCESS;
}


dtcp_result_t DTCPMgrCreateSourceSession(char *sinkIpAddress,
                                         int key_label, 
                                         int PCPPacketSize, 
                                         int maxPacketSize, 
                                         DTCP_SESSION_HANDLE *handle) 
{ 
	printf("Entered fucntion %s\n",__PRETTY_FUNCTION__);
	printf("invoked create source session with sinkIP: %s ; key label: %d,PCPPacketSize = %d, MaxPAcketSize = %d\n", 
		sinkIpAddress,
		key_label,
		PCPPacketSize,
		maxPacketSize);
	sessionHandle* lochandle = new sessionHandle;
	lochandle->id = 1;
	handle = (DTCP_SESSION_HANDLE*)(lochandle);
	return DTCP_SUCCESS;
}

dtcp_result_t DTCPMgrCreateSinkSession(char *srcIpAddress, 
                                       int srcIpPort, 
                                       BOOLEAN uniqueKey, 
                                       int maxPacketSize, 
                                       DTCP_SESSION_HANDLE *handle)
{
	printf("Entered fucntion %s\n",__PRETTY_FUNCTION__);
	printf("invoked create sink session with srcIP: %s ; srcIpPort: %d,uniqueKey = %c, MaxPAcketSize = %d\n", 
		srcIpAddress,
		srcIpPort,
		uniqueKey,
		maxPacketSize);
	sessionHandle* lochandle = new sessionHandle;
	lochandle->id = 2;
	handle = (DTCP_SESSION_HANDLE*)lochandle;
	return DTCP_SUCCESS;
}


dtcp_result_t DTCPMgrProcessPacket(DTCP_SESSION_HANDLE session, DTCPIP_Packet *packet)
{
	printf("Entered fucntion %s\n",__PRETTY_FUNCTION__);
	sessionHandle* locHandle = (sessionHandle*)&session;
	printf("Enetered with sessionId = %d\n",locHandle->id);
	return DTCP_SUCCESS;
}


dtcp_result_t DTCPMgrReleasePacket(DTCPIP_Packet *packet)
{
	printf("Entered fucntion %s\n",__PRETTY_FUNCTION__);
	return DTCP_SUCCESS;
}

dtcp_result_t DTCPMgrDeleteDTCPSession(DTCP_SESSION_HANDLE session)
{
	printf("Entered fucntion %s\n",__PRETTY_FUNCTION__);
	sessionHandle* locHandle = (sessionHandle*) &session;
	delete locHandle;
	return DTCP_SUCCESS;
}


int DTCPMgrGetNumSessions(DTCPDeviceType deviceType)
{
	printf("Entered fucntion %s\n",__PRETTY_FUNCTION__);
	return 1;
}


dtcp_result_t DTCPMgrGetSessionInfo(DTCP_SESSION_HANDLE handle, DTCPIP_Session *session)
{
	printf("Entered fucntion %s\n",__PRETTY_FUNCTION__);
	sessionHandle* locHandle = new sessionHandle;
	session = new DTCPIP_Session;
	session->session_handle = handle;
	return DTCP_SUCCESS;
}

dtcp_result_t DTCPMgrSetLogLevel(int level)
{
	printf("Entered fucntion %s\n",__PRETTY_FUNCTION__);
	return DTCP_SUCCESS;
} 


/** @} */
/** @} */
