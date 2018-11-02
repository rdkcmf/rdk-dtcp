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
 * @file   dtcpmgr.h
 * DTCP Manager Interface
 */

/**
 * @defgroup DTCP DTCP (Digital Transmission Content Protection)
 *
 * Digital Transmission Content Protection ("DTCP") technology protects high-value digital motion pictures,
 * television programs and audio against unauthorized interception and copying in the home and personal environment
 * (e.g., between a digital set top box and digital video recorder, or between a personal computer and a digital TV).
 *
 * @par Terminology
 * Code | Description
 * -----| -----------
 * DTCP | Digital Transmission Content Protection
 * DTCP-IP | Digital Transmission Content Protection Internet Protocol
 * AKE  | Authentication and Key Exchange
 * CCI  | Copy Control Information
 * SRM  | System Renewability Messages
 * DLNA | Digital Living Network Alliance
 * EMI  | Encryption Mode Indicator
 * E-EMI | Extended Encryption Mode Indicator
 * PCP  | Protected Content Packet
 * SPTS  | Single Program Transport Stream
 *
 * @par How does DTCP work?
 * A device enabled with DTCP determines whether it is connected to other devices that implement
 * the DTCP protection technology. Content encoded for DTCP protection is encrypted and securely transmitted
 * only to recording and display devices that implement DTCP.
 * The content carries information indicating whether and to what extent the content may be copied.
 * @par DTCP overview & FAQ
 * @see http://www.dtcp.com/documents/dtcp/dtcp-overview.pdf
 * @see http://www.dtcp.com/faq.aspx
 *
 * @par Filter elements for content encryption and decryption
 * There are two gstreamer filter elements are used for content encryption/decryption.
 * @n
 * - DTCP Encrypt: The "dtcpencrypt" is a gstreamer filter element which encrypts incomming MPEG2 SPTS
 * stream and pushes encrypted data to the source pad. DTCP encrypt requires initialization of DTCP libs done
 * in RMF applicaiton (e.g Media Streamer) which includes creating socket and listening for AKE request,
 * authenticate and send exchange key to Sink device upon DTCP request from sink EMO
 * @n It support Authentication and Key Exchange (AKE) from DTCP client.
 * It encrypts the video stream using DTCP Encryption Mode Indicator (EMI).
 * @n
 * - DTCP Decrypt: The "dtcpdecrypt" is a gstreamer filter element is used to decrypt the MPEG2 SPTS video streams.
 * It performs Authentication and Key Exchange (AKE) to DTCP server.
 *
 * @par DTCP Protection
 * All DTCP encryption and dcryption uses common set of provided gstreamer elements, The gstreamer elements
 * uses DTCP manager API. Each SoC provides binary DTCP encryption/decryption library to support the DTCP Manager API.
 *
 * @par DTCP Use Case: Live Playback using QAM Source
 * @image html dtcp_usecase.png
 * - The left side of the figure is considered for gateway device.
 * - The right side of the figure is considered for client device.
 * - In case of live stream the HTTPReqHandler will receive a request from client box and the MediaStreamer.
 * - will sets an pipeline between QAM Source and HN Sink.
 * - QAM Src element receives the data from the tuner and sends to the HN Sink.
 * - In the client side another pipeline has created between HNSrc and MediaPlayerSink.
 * - HNSrc receive the incoming data from HNSink and feeds to the MediaPlayerSink for live playback.
 * - DTCP encryption and decryption are used for protecting contents over network.
 *
 * @par How to enable/disable DTCP
 * @n
 * At first, user need to verify that the current build of the box supports to enable/disable DTCP.
 * @n If it's yes, following the next steps
 * @n
 * - Copy rmfconfig.ini under /etc to /opt
 * @code
 * cp /etc/rmfconfig.ini /opt
 * @endcode
 * @n
 * - Change the configuration parameter "FEATURE.DTCP.SUPPORT" value to TRUE or FALSE in file /opt/rmfconfig.ini
 * @code
 * vi /opt/rmfconfig.ini
 * @endcode
 * @n
 * Save the configuration file and reboot the box
 * @code
 * $ sync
 * $ reboot
 * @endcode
 * @n
 * Check AV for the box once it's up.
 *
 * @defgroup DTCPMGR_API DTCP Manager API
 * DTCP manager manages source/sink DTCP-IP sessions and performs encryption/decryption.
 *
 * DTCP-IP is a specification for copy protection of copyrighted content that is
 * transferred over digital interfaces in home IP networks.
 *
 * DTCP Manager sub-system performs data encryption and PCP packet decryption
 * with authenticated DTCP-IP sessions.
 * @ingroup DTCP
 *
 * @defgroup DTCPMGR_DS DTCP Manager Data Structure
 * @ingroup DTCP
 */


/**
* @defgroup dtcp
* @{
* @defgroup include
* @{
**/


#ifndef __DTCPMGR_H_
#define __DTCPMGR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @ingroup DTCPMGR_DS
 * @{
 */
/**
 * @brief DTCP Manager return codes.
 *
 * This enumartion lists DTCP Manager error return codes.
 * A non-zero value indicates an error.
 */
typedef enum {
	DTCP_SUCCESS                 = 0,  /**< Operation successful, no errors.     */
	DTCP_ERR_NOT_INITIALIZED     = -1, /**< DTCP Manager not initialized yet.    */
	DTCP_ERR_INVALID_PARAM       = -2, /**< Invalid parameter supplied.          */
	DTCP_ERR_GENERAL             = -3, /**< General unspecified error.           */
	DTCP_ERR_MEMORY_ALLOC        = -4, /**< Memory allocation failure.           */
	DTCP_ERR_OUT_OF_SESSIONS     = -5, /**< Too many active sessions.            */
	DTCP_ERR_INVALID_CERTIFICATE = -6, /**< Invalid certificate.                 */
	DTCP_ERR_AKE                 = -7, /**< Authorization/Key Exchange error.    */
	DTCP_ERR_CONT_KEY_REQ        = -8, /**< Content key error.                   */
	DTCP_ERR_INVALID_KEY_LABEL   = -9, /**< Invalid exchange key label supplied. */
	DTCP_ERR_INVALID_IP_ADDRESS	 = -10, /**< Invalid IP address supplied.         */  
	DTCP_ERR_SERVER_NOT_REACHABLE	= -11  /**< DTCP Server not reachable.           */
} dtcp_result_t;

typedef unsigned char  BOOLEAN;

/**
 * @brief DTCP-IP session handle.
 *
 * An opaque handle to a DTCP-IP source/sink session.
 */
typedef unsigned long long DTCP_SESSION_HANDLE;

/**
 * @brief DTCP-IP device types.
 *
 * This enumartion defines supported types of DTCP-IP devices.
 */    
typedef enum {
	DTCP_SOURCE,  /**< Source type.  */
	DTCP_SINK,    /**< Sink type.    */
	DTCP_UNKNOWN  /**< Unknown type. */
} DTCPDeviceType;    

/**
 * @brief DTCP-IP packet stucture.
 *
 * This structure defines a DTCP-IP PCP packet.
 */
typedef struct DTCPIP_Packet_s
{
    DTCP_SESSION_HANDLE session;    /**< (Input) The session to which this packet belongs.                      */
    uint32_t emi;                   /**< (Input for source, Output for sink) EMI value.                         */
    uint8_t *dataInPtr;             /**< (Input) Virtual data buffer, allocated by the caller.                  */
    uint8_t *dataInPhyPtr;          /**< (Input) Physical data buffer, allocated by the caller. 
                                         (Set to NULL if not available.)                                        */
    uint8_t *dataOutPtr;            /**< (Output) Virtual data buffer, allocated by DTCP Manager.
                                         (This will be same as dataInPtr if encrypt/decrypt was done in-place.) */
    uint8_t *dataOutPhyPtr;         /**< (Output) Physical data buffer, allocated by DTCP Manager.
                                         (This will be same as dataInPhyPtr if encrypt/decrypt was done in-place.) */
    uint32_t dataLength;            /**< (Input/Output) Length of the buffer. */
    BOOLEAN  isEOF;                 /**< (Input, source only) Flag specifying whether this is the last buffer for this session. */

    uint8_t *pcpHeader;             /**< (Output, source only) PCP packet header, NULL if no header.            */
    uint32_t pcpHeaderLength;       /**< (Output, source only) Length of pcpHeader in bytes, 0 if no header.    */
    int		 pcpHeaderOffset;       /**< (Output, source only) Byte offset into the buffer where header needs to be inserted. 
                                          (If < 0, no insertion to be done.)                                    */
} DTCPIP_Packet;

/**
 * @brief DTCP-IP session structure.
 *
 * This structure defines a DTCP-IP session.
 */    
typedef struct DTCPIP_Session_s
{
    DTCP_SESSION_HANDLE session_handle;  /**< Unique handle of the session.  */
    DTCPDeviceType device_type;          /**< Type of device (source/sink).  */
    char * remote_ip;                    /**< Remote source/sink IP address. */
    BOOLEAN uniqueKey;                   /**< Flag indicating unique key.    */
} DTCPIP_Session;

/** @} */ //End of Doxygen tag DTCPMGR_DS

/**
 * @ingroup DTCPMGR_API
 * @{
 */

/**
 * @brief Initializes the DTCP Manager.
 *
 * This function initializes the DTCP-IP Manager sub-system. It should be called during platform initialization.
 * 
 * @note This function can be called multiple times from the multiple contexts. Once it's initialized,
 * it will return DTCP_SUCCESS for all the subsequent calls.
 *
 * @param None.
 *
 * @return Error code.
 * @retval DTCP_SUCCESS    DTCP Manager successfully initialized.
 */
dtcp_result_t DTCPMgrInitialize(void);

/**
 * @brief Starts the DTCP-IP source.
 * 
 * This function start the DTCP-IP source and begins listening for AKE requests
 * on the specified interface and port number.
 *
 * @note Calling this function multiple times adds multiple listeners.
 *
 * @param[in] ifName   Interface name (e.g. "eth0").
 * @param[in] portNum  TCP/IP port number that the source listens for AKE requests.
 *
 * @return Error code.
 * @retval ::DTCP_SUCCESS    Successfully started the DTCP-IP source and/or added a listener.
 *
 * @par Example usage
 * @code
      dtcp_result_t result = DTCPMgrStartSource("eth0", 5000);
   @endcode
 */
dtcp_result_t DTCPMgrStartSource(char* ifName, int portNum);

/**
 * @brief Stops the DTCP-IP source.
 * 
 * This function stops the DTCP-IP source and removes all AKE request listeners
 * added with ::DTCPMgrStartSource().
 *
 * @return Error code.
 * @retval DTCP_SUCCESS Successfully stopped the DTCP-IP source and removed all listeners.
 */
dtcp_result_t DTCPMgrStopSource(void);

/**
 * @brief Creates a new DTCP-IP source session.
 * 
 * This function creates a new authenticated session with a remote DTCP-IP sink.
 *
 * @param[in] sinkIpAddress IP address of the remote DTCP-IP sink.
 * @param[in] key_label Exchange key label, if available from streaming request.
 * If provided, the stream will be encrypted with the session key.
 * @param [in] PCPPacketSize  Minimum size of a packet. If the buffer provided in DTCPMgrProcessPacket() is less
 * than @a PCPPacketSize, then the PCP packet is set to @a PCPPacketSize and fragmented across multiple DTCPIP_Packets.
 * @n This is for reducing PCP space and processing overheads for low latency low bit-rate transfers
 * where each buffer can be very small. @a PCPPacketSize of 0 would return every buffer as a PCP packet.
 * @n i.e. If @a PCPPacketSize is 64 KB and if the buffer size in DTCPMgrProcessPacket() is 1 KB, the first decrypted
 * buffer would be a PCP packet. And after first packet, decrypted buffer wouldn't have a PCP header until 64 KB.
 * @param [in] maxPacketSize  Maximum size of a packet.
 * @n If the @a DataLength provided in DTCPMgrProcessPacket() is more than @a MaxPacketSize,
 * the DTCP library can reject the process request.
 *
 * @param[out] handle The address of a location to hold the handle for the specified TCP/IP session on return.
 *
 * @return Error code.
 * @retval DTCP_SUCCESS Successfully created a DTCP-IP source session.
 */
dtcp_result_t DTCPMgrCreateSourceSession(char *sinkIpAddress, int key_label, int PCPPacketSize, int maxPacketSize, DTCP_SESSION_HANDLE *handle);

/**
 * @brief Creates a new DTCP-IP sink session.
 *
 * This function creates a new authenticated session with a remote DTCP-IP source.
 *
 * @param[in] srcIpAddress IP address of the remote DTCP-IP source.
 * @param[in] srcIpPort TCP/IP port of the remote DTCP-IP source.
 * @param[in] uniqueKey Flag to request unique exchange keys.
 * (Both server and client should have 'session exchange key' support.)
 * @param[in] maxPacketSize Maximum size of packet. If @a DataLength provided in DTCPMgrProcessPacket()
 * is more than @a MaxPacketSize, the DTCP library can reject the process request.
 * @param[out] handle The address of a location to hold the handle for the specified TCP/IP session on return.
 *
 * @return Error code.
 * @retval DTCP_SUCCESS Successfully created a DTCP-IP sink session.
 */
dtcp_result_t DTCPMgrCreateSinkSession(char *srcIpAddress, int srcIpPort, BOOLEAN uniqueKey, int maxPacketSize, DTCP_SESSION_HANDLE *handle);

/**
 * @brief Processes a DTCP-IP packet.
 *
 * This function processes a DTCP-IP packet - encrypts or decrypts buffers, depending on the session type:
 * - Source - encrypt the provided buffers and create a DTCP-IP packet.
 * - Sink - process the DTCP-IP packet and return decrypted buffers.
 *
 * @note All processing is done inside the ::DTCPIP_Packet data structure.
 *
 * @param[in] session Session handle.
 * @param[in,out] packet Address of the location of the of the processed DTCP-IP packet.
 *
 * @return Error code.
 * @retval DTCP_SUCCESS  Successfully processed the packet.
 */
dtcp_result_t DTCPMgrProcessPacket(DTCP_SESSION_HANDLE session, DTCPIP_Packet *packet);
    
/**
 * @brief Releases a processed DTCP-IP packet.
 * 
 * This function releases the DTCP-IP packet. The processed packet may contain DTCP Manager allocated/owned 
 * buffers/memory - this call frees up these resources.
 *
 * @param [in] packet Address of the location of the DTCP-IP packet.
 *
 * @return Error code.
 * @retval DTCP_SUCCESS Successfully released packet.
 */
dtcp_result_t DTCPMgrReleasePacket(DTCPIP_Packet *packet);

/**
 * @brief Deletes a DTCP-IP session.
 * 
 * This function stops an active DTCP-IP session.
 *
 * @param[in] session Session handle.
 *
 * @return Error code.
 * @retval DTCP_SUCCESS Successfully deleted the session.
 */
dtcp_result_t DTCPMgrDeleteDTCPSession(DTCP_SESSION_HANDLE session);
    
/**
 * @brief Gets the number of active sessions.
 * 
 * This function retrieves the total number of active sessions for the specified device type.
 *
 * @param[in] deviceType  DTCP-IP device type (source/sink).
 * DTCP_UNKNOWN returns total number of sessions of all types.
 *
 * @return Number of active sessions.
 *
 * @par Example usage
 * @code 
        int source_session_count = getNumDTCPSessions(DTCP_SOURCE); 
   @endcode
 */
int DTCPMgrGetNumSessions(DTCPDeviceType deviceType);
    
/**
 * @brief Gets session information.
 * 
 * This function retrieves information related to an active session.
 *
 * @param[in] handle DTCP-IP session handle.
 * @param[out] session The address of a location of the DTCP-IP session structure to fill on return.
 *
 * @return Error code.
 * @retval DTCP_SUCCESS Successfully returned the session info.
 */
dtcp_result_t DTCPMgrGetSessionInfo(DTCP_SESSION_HANDLE handle, DTCPIP_Session *session);
    
/**
 * @brief Sets log level.
 * 
 * This function sets DTCP Manager's logging verbosity level.
 *
 * @param [in] level Logging level.
 *
 * @return Error code.
 * @retval DTCP_SUCCESS  Logging level was set successfully.
 */
dtcp_result_t DTCPMgrSetLogLevel(int level);

/** @} */ /* End of DTCPMGR_API doxygen group */

#ifdef __cplusplus
}
#endif

#endif //__DTCPMGR_H_

