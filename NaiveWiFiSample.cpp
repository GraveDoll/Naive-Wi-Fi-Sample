
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <wlanapi.h>
#include <objbase.h>
#include <wtypes.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <wchar.h>

// Need to link with Wlanapi.lib and Ole32.lib
#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")

static bool bScanWait = true;


//Callback function for notification of wireess LAN
static void WlanNotification(WLAN_NOTIFICATION_DATA *wlanNotifData, VOID *p)
{

	WCHAR	wStrW[50];

	size_t wLen = 0;
	errno_t err = 0;

	//set your locale
	setlocale(LC_ALL, "japanese");
	WCHAR strReason[1024];

	if (wlanNotifData->NotificationSource == WLAN_NOTIFICATION_SOURCE_ACM) {
		PWLAN_CONNECTION_NOTIFICATION_DATA pConnNotifData = NULL;

		WCHAR *notificationMessage;
		switch (wlanNotifData->NotificationCode) {
		case wlan_notification_acm_start:
			notificationMessage = L"wlan_notification_acm_start";
			break;
		case wlan_notification_acm_autoconf_enabled:
			notificationMessage = L"wlan_notification_acm_autoconf_enabled";
			break;
		case wlan_notification_acm_autoconf_disabled:
			notificationMessage = L"wlan_notification_acm_autoconf_disabled";
			break;
		case wlan_notification_acm_background_scan_enabled:
			notificationMessage = L"wlan_notification_acm_background_scan_enabled";
			break;
		case wlan_notification_acm_background_scan_disabled:
			notificationMessage = L"wlan_notification_acm_start";
			break;
		case wlan_notification_acm_bss_type_change:
			notificationMessage = L"wlan_notification_acm_bss_type_change";
			break;
		case wlan_notification_acm_power_setting_change:
			notificationMessage = L"wlan_notification_acm_power_setting_change";
			break;
		case wlan_notification_acm_scan_complete:
			notificationMessage = L"wlan_notification_acm_scan_complete";
			break;
		case wlan_notification_acm_scan_fail:
			notificationMessage = L"wlan_notification_acm_scan_fail";
			break;
		case wlan_notification_acm_connection_start:
			notificationMessage = L"wlan_notification_acm_connection_start";
			break;
		case wlan_notification_acm_connection_complete:
			notificationMessage = L"wlan_notification_acm_connection_complete";
			break;
		case wlan_notification_acm_connection_attempt_fail:
			notificationMessage = L"wlan_notification_acm_connection_attempt_fail";
			break;
		case wlan_notification_acm_filter_list_change:
			notificationMessage = L"wlan_notification_acm_filter_list_change";
			break;
		case wlan_notification_acm_interface_arrival:
			notificationMessage = L"wlan_notification_acm_interface_arrival";
			break;
		case wlan_notification_acm_interface_removal:
			notificationMessage = L"wlan_notification_acm_interface_removal";
			break;
		case wlan_notification_acm_profile_change:
			notificationMessage = L"wlan_notification_acm_profile_change";
			break;
		case wlan_notification_acm_profile_name_change:
			notificationMessage = L"wlan_notification_acm_filter_list_change";
			break;
		case wlan_notification_acm_profiles_exhausted:
			notificationMessage = L"wlan_notification_acm_profiles_exhausted";
			break;
		case wlan_notification_acm_network_not_available:
			notificationMessage = L"wlan_notification_acm_network_not_available";
			break;
		case wlan_notification_acm_network_available:
			notificationMessage = L"wlan_notification_acm_network_available";
			break;
		case wlan_notification_acm_disconnecting:
			notificationMessage = L"wlan_notification_acm_disconnecting";
			break;
		case wlan_notification_acm_disconnected:
			notificationMessage = L"wlan_notification_acm_disconnected";
			break;
		case wlan_notification_acm_adhoc_network_state_change:
			notificationMessage = L"wlan_notification_acm_adhoc_network_state_change";
			break;
		case wlan_notification_acm_profile_unblocked:
			notificationMessage = L"wlan_notification_acm_profile_unblocked";
			break;
		case wlan_notification_acm_screen_power_change:
			notificationMessage = L"wlan_notification_acm_screen_power_change";
			break;
		case wlan_notification_acm_profile_blocked:
			notificationMessage = L"wlan_notification_acm_profile_blocked";
			break;
		case wlan_notification_acm_scan_list_refresh:
			notificationMessage = L"wlan_notification_acm_scan_list_refresh";
			break;
		case wlan_notification_acm_end:
			notificationMessage = L"wlan_notification_acm_end";
			break;
		default:
			notificationMessage = L"Unknown:";
			break;
		}

		wprintf(L"%ls\n", notificationMessage);

		if (wlanNotifData->NotificationCode == wlan_notification_acm_scan_complete)
		{
			bScanWait = false;
		}
		else if (wlanNotifData->NotificationCode == wlan_notification_acm_scan_fail)
		{
			pConnNotifData = (PWLAN_CONNECTION_NOTIFICATION_DATA)wlanNotifData->pData;
			if (pConnNotifData->wlanReasonCode != ERROR_SUCCESS) {
				bScanWait = false;

				WlanReasonCodeToString(pConnNotifData->wlanReasonCode, 1024, strReason, NULL);
				wprintf(L"ScanFailed Reason: %ls\n", strReason);

			}

		}

	}
	else if (wlanNotifData->NotificationSource == WLAN_NOTIFICATION_SOURCE_MSM) {
		PWLAN_MSM_NOTIFICATION_DATA pMsmNotifData = NULL;

		WCHAR *notificationMessage;
		switch (wlanNotifData->NotificationCode) {
		case wlan_notification_msm_start:
			notificationMessage = L"wlan_notification_msm_start";
			break;
		case wlan_notification_msm_associating:
			notificationMessage = L"wlan_notification_msm_associating";
			break;
		case wlan_notification_msm_associated:
			notificationMessage = L"wlan_notification_msm_associated";
			break;
		case wlan_notification_msm_authenticating:
			notificationMessage = L"wlan_notification_msm_authenticating";
			break;
		case wlan_notification_msm_connected:
			notificationMessage = L"wlan_notification_msm_connected";
			break;
		case wlan_notification_msm_roaming_start:
			notificationMessage = L"wlan_notification_msm_roaming_start";
			break;
		case wlan_notification_msm_roaming_end:
			notificationMessage = L"wlan_notification_msm_roaming_end";
			break;
		case wlan_notification_msm_radio_state_change:
			notificationMessage = L"wlan_notification_msm_radio_state_change";
			break;
		case wlan_notification_msm_signal_quality_change:
			notificationMessage = L"wlan_notification_msm_signal_quality_change";
			break;
		case wlan_notification_msm_disassociating:
			notificationMessage = L"wlan_notification_msm_disassociating";
			break;
		case wlan_notification_msm_disconnected:
			notificationMessage = L"wlan_notification_msm_disconnected";
			break;
		case wlan_notification_msm_peer_join:
			notificationMessage = L"wlan_notification_msm_peer_join";
			break;
		case wlan_notification_msm_peer_leave:
			notificationMessage = L"wlan_notification_msm_peer_leave";
			break;
		case wlan_notification_msm_adapter_removal:
			notificationMessage = L"wlan_notification_msm_adapter_removal";
			break;
		case wlan_notification_msm_adapter_operation_mode_change:
			notificationMessage = L"wlan_notification_msm_adapter_operation_mode_change";
			break;
		case wlan_notification_msm_end:
			notificationMessage = L"wlan_notification_msm_end";
			break;
		default:
			notificationMessage = L"Unknown";
			break;
		}

		wprintf(L"%ls\n", notificationMessage);

	}
}
bool connect(HANDLE hClient, const GUID *guid, LPCWSTR ssid, LPCWSTR securityKey) {
	DWORD dwMaxClient = 2;// Client version for Windows Vista and Windows Server 2008
	DWORD dwCurVersion = 0;
	DWORD dwResult = 0;
	DWORD dwReasonCode = 0;

	DOT11_SSID dot11Ssid = { 0 };
	WLAN_CONNECTION_PARAMETERS wlanConnectionParams;
	DWORD dwPrevNotif = 0;

	char *wStrC = new char[256];

	dot11Ssid.uSSIDLength = lstrlen(ssid);

	size_t wLen = 0;
	errno_t err = 0;

	wcstombs_s(&wLen, wStrC, 256, ssid, _TRUNCATE);
	memcpy(&dot11Ssid.ucSSID, wStrC, wLen);
	if (wStrC)
	{
		free(wStrC);
	}

	//Set connection params
	ZeroMemory(&wlanConnectionParams, sizeof(WLAN_CONNECTION_PARAMETERS));
	wlanConnectionParams.wlanConnectionMode = wlan_connection_mode_profile;
	wlanConnectionParams.strProfile = ssid;
	wlanConnectionParams.pDot11Ssid = &dot11Ssid;
	wlanConnectionParams.pDesiredBssidList = NULL;
	wlanConnectionParams.dot11BssType = dot11_BSS_type_infrastructure;
	wlanConnectionParams.dwFlags = 0;

	//Create profile
	if (securityKey != NULL) {
		wchar_t strXml[1024];
		LPCWSTR key = securityKey;
		wchar_t profileFormat[] = L"<?xml version=\"1.0\" encoding=\"US-ASCII\"?>"
			L"<WLANProfile xmlns=\"http://www.microsoft.com/networking/WLAN/profile/v1\">\n"
			L"<name>%s</name>\n"
			L"<SSIDConfig>\n"
			L"<SSID>\n"
			L"<name>%s</name>\n"
			L"</SSID>\n"
			L"</SSIDConfig>\n"
			L"<connectionType>ESS</connectionType>\n"
			L"<connectionMode>auto</connectionMode>\n"
			L"<autoSwitch>false</autoSwitch>\n"
			L"<MSM>\n"
			L"<security>\n"
			L"<authEncryption>\n"
			L"<authentication>WPA2PSK</authentication>\n"
			L"<encryption>AES</encryption>\n"
			L"<useOneX>false</useOneX>\n"
			L"</authEncryption>\n"
			L"<sharedKey>\n"
			L"<keyType>passPhrase</keyType>\n"
			L"<protected>false</protected>\n"
			L"<keyMaterial>%s</keyMaterial>\n"
			L"</sharedKey>\n"
			L"</security>\n"
			L"</MSM>\n"
			L"</WLANProfile>\n";
		_snwprintf_s(strXml, _countof(strXml), profileFormat, ssid, ssid, key);

		//Register created profile 
		dwResult = WlanSetProfile(hClient, guid, 0, strXml, 0, true, NULL, &dwReasonCode);
		if (dwResult != ERROR_SUCCESS) {
			switch (dwResult)
			{
			case ERROR_INVALID_HANDLE:
				printf("INVALID HANDLE\n");
				break;
			case ERROR_INVALID_PARAMETER:
				printf("INVALID PARAMETERS\n");
				break;
			}
			return false;
		}
	}

	//Conenct via created profile
	dwResult = WlanConnect(hClient, guid, &wlanConnectionParams, NULL);
	if (dwResult != ERROR_SUCCESS) {
		switch (dwResult)
		{
		case ERROR_INVALID_HANDLE:
			printf("INVALID HANDLE\n");
			break;
		case ERROR_ACCESS_DENIED:
			printf("NO PERMISSION TO CONNECT\n");
			break;
		case ERROR_INVALID_PARAMETER:
			printf("INVALID PARAMETERS\n");
			break;
		}
		return false;
	}

	return true;
}


int wmain()
{

	// Declare and initialize variables.

	HANDLE hClient = NULL;
	DWORD dwMaxClient = 2;      //    
	DWORD dwCurVersion = 0;
	DWORD dwResult = 0;
	DWORD dwRetVal = 0;
	int iRet = 0;

	WCHAR GuidString[39] = { 0 };

	unsigned int i, j, k;

	/* variables used for WlanEnumInterfaces  */

	PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
	PWLAN_INTERFACE_INFO pIfInfo = NULL;

	PWLAN_AVAILABLE_NETWORK_LIST pBssList = NULL;
	PWLAN_AVAILABLE_NETWORK pBssEntry = NULL;

	int iRSSI = 0;

	DWORD dwPrevNotif = 0;
	bScanWait = true;

	dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);
	if (dwResult != ERROR_SUCCESS) {
		wprintf(L"WlanOpenHandle failed with error: %u\n", dwResult);
		return 1;
		// You can use FormatMessage here to find out why the function failed
	}

	dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList);
	if (dwResult != ERROR_SUCCESS) {
		wprintf(L"WlanEnumInterfaces failed with error: %u\n", dwResult);
		return 1;
		// You can use FormatMessage here to find out why the function failed
	}
	else {
		wprintf(L"Num Entries: %lu\n", pIfList->dwNumberOfItems);
		wprintf(L"Current Index: %lu\n", pIfList->dwIndex);
		for (i = 0; i < (int)pIfList->dwNumberOfItems; i++) {
			pIfInfo = (WLAN_INTERFACE_INFO *)&pIfList->InterfaceInfo[i];
			wprintf(L"  Interface Index[%u]:\t %lu\n", i, i);
			iRet = StringFromGUID2(pIfInfo->InterfaceGuid, (LPOLESTR)&GuidString,
				sizeof(GuidString) / sizeof(*GuidString));
			// For c rather than C++ source code, the above line needs to be
			// iRet = StringFromGUID2(&pIfInfo->InterfaceGuid, (LPOLESTR) &GuidString, 
			//     sizeof(GuidString)/sizeof(*GuidString)); 
			if (iRet == 0)
				wprintf(L"StringFromGUID2 failed\n");
			else {
				wprintf(L"  InterfaceGUID[%d]: %ws\n", i, GuidString);
			}
			wprintf(L"  Interface Description[%d]: %ws", i,
				pIfInfo->strInterfaceDescription);
			wprintf(L"\n");
			wprintf(L"  Interface State[%d]:\t ", i);
			switch (pIfInfo->isState) {
			case wlan_interface_state_not_ready:
				wprintf(L"Not ready\n");
				break;
			case wlan_interface_state_connected:
				wprintf(L"Connected\n");
				break;
			case wlan_interface_state_ad_hoc_network_formed:
				wprintf(L"First node in a ad hoc network\n");
				break;
			case wlan_interface_state_disconnecting:
				wprintf(L"Disconnecting\n");
				break;
			case wlan_interface_state_disconnected:
				wprintf(L"Not connected\n");
				break;
			case wlan_interface_state_associating:
				wprintf(L"Attempting to associate with a network\n");
				break;
			case wlan_interface_state_discovering:
				wprintf(L"Auto configuration is discovering settings for the network\n");
				break;
			case wlan_interface_state_authenticating:
				wprintf(L"In process of authenticating\n");
				break;
			default:
				wprintf(L"Unknown state %ld\n", pIfInfo->isState);
				break;
			}
			wprintf(L"\n");

			//Register the callback
			dwResult = WlanRegisterNotification(hClient, WLAN_NOTIFICATION_SOURCE_ACM | WLAN_NOTIFICATION_SOURCE_MSM, FALSE, (WLAN_NOTIFICATION_CALLBACK)WlanNotification, NULL, NULL, &dwPrevNotif);
			if (dwResult != ERROR_SUCCESS) {
				wprintf(L"WlanRegisterNotification failed with error: %u\n", dwResult);
				return 1;
			}

			//Scan available netoworks
			dwResult = WlanScan(hClient, &pIfInfo->InterfaceGuid, NULL, NULL, NULL);
			if (dwResult != ERROR_SUCCESS) {
				wprintf(L"WlanScan failed with error: %u\n", dwResult);
				return 1;
			}

			while (bScanWait) {
				Sleep(100);
			}

			dwResult = WlanGetAvailableNetworkList(hClient,
				&pIfInfo->InterfaceGuid,
				0,
				NULL,
				&pBssList);

			if (dwResult != ERROR_SUCCESS) {
				wprintf(L"WlanGetAvailableNetworkList failed with error: %u\n",
					dwResult);
				dwRetVal = 1;
				// You can use FormatMessage to find out why the function failed
			}
			else {
				wprintf(L"WLAN_AVAILABLE_NETWORK_LIST for this interface\n");

				wprintf(L"  Num Entries: %lu\n\n", pBssList->dwNumberOfItems);

				for (j = 0; j < pBssList->dwNumberOfItems; j++) {
					pBssEntry =
						(WLAN_AVAILABLE_NETWORK *)& pBssList->Network[j];

					wprintf(L"  Profile Name[%u]:  %ws\n", j, pBssEntry->strProfileName);

					wprintf(L"  SSID[%u]:\t\t ", j);
					if (pBssEntry->dot11Ssid.uSSIDLength == 0)
						wprintf(L"\n");
					else {
						for (k = 0; k < pBssEntry->dot11Ssid.uSSIDLength; k++) {
							wprintf(L"%c", (int)pBssEntry->dot11Ssid.ucSSID[k]);
						}
						wprintf(L"\n");
					}

					wprintf(L"  BSS Network type[%u]:\t ", j);
					switch (pBssEntry->dot11BssType) {
					case dot11_BSS_type_infrastructure:
						wprintf(L"Infrastructure (%u)\n", pBssEntry->dot11BssType);
						break;
					case dot11_BSS_type_independent:
						wprintf(L"Infrastructure (%u)\n", pBssEntry->dot11BssType);
						break;
					default:
						wprintf(L"Other (%lu)\n", pBssEntry->dot11BssType);
						break;
					}

					wprintf(L"  Number of BSSIDs[%u]:\t %u\n", j, pBssEntry->uNumberOfBssids);

					wprintf(L"  Connectable[%u]:\t ", j);
					if (pBssEntry->bNetworkConnectable)
						wprintf(L"Yes\n");
					else {
						wprintf(L"No\n");
						wprintf(L"  Not connectable WLAN_REASON_CODE value[%u]:\t %u\n", j,
							pBssEntry->wlanNotConnectableReason);
					}

					wprintf(L"  Number of PHY types supported[%u]:\t %u\n", j, pBssEntry->uNumberOfPhyTypes);

					if (pBssEntry->wlanSignalQuality == 0)
						iRSSI = -100;
					else if (pBssEntry->wlanSignalQuality == 100)
						iRSSI = -50;
					else
						iRSSI = -100 + (pBssEntry->wlanSignalQuality / 2);

					wprintf(L"  Signal Quality[%u]:\t %u (RSSI: %i dBm)\n", j,
						pBssEntry->wlanSignalQuality, iRSSI);

					wprintf(L"  Security Enabled[%u]:\t ", j);
					if (pBssEntry->bSecurityEnabled)
						wprintf(L"Yes\n");
					else
						wprintf(L"No\n");

					wprintf(L"  Default AuthAlgorithm[%u]: ", j);
					switch (pBssEntry->dot11DefaultAuthAlgorithm) {
					case DOT11_AUTH_ALGO_80211_OPEN:
						wprintf(L"802.11 Open (%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
						break;
					case DOT11_AUTH_ALGO_80211_SHARED_KEY:
						wprintf(L"802.11 Shared (%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
						break;
					case DOT11_AUTH_ALGO_WPA:
						wprintf(L"WPA (%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
						break;
					case DOT11_AUTH_ALGO_WPA_PSK:
						wprintf(L"WPA-PSK (%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
						break;
					case DOT11_AUTH_ALGO_WPA_NONE:
						wprintf(L"WPA-None (%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
						break;
					case DOT11_AUTH_ALGO_RSNA:
						wprintf(L"RSNA (%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
						break;
					case DOT11_AUTH_ALGO_RSNA_PSK:
						wprintf(L"RSNA with PSK(%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
						break;
					default:
						wprintf(L"Other (%lu)\n", pBssEntry->dot11DefaultAuthAlgorithm);
						break;
					}

					wprintf(L"  Default CipherAlgorithm[%u]: ", j);
					switch (pBssEntry->dot11DefaultCipherAlgorithm) {
					case DOT11_CIPHER_ALGO_NONE:
						wprintf(L"None (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
						break;
					case DOT11_CIPHER_ALGO_WEP40:
						wprintf(L"WEP-40 (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
						break;
					case DOT11_CIPHER_ALGO_TKIP:
						wprintf(L"TKIP (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
						break;
					case DOT11_CIPHER_ALGO_CCMP:
						wprintf(L"CCMP (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
						break;
					case DOT11_CIPHER_ALGO_WEP104:
						wprintf(L"WEP-104 (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
						break;
					case DOT11_CIPHER_ALGO_WEP:
						wprintf(L"WEP (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
						break;
					default:
						wprintf(L"Other (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
						break;
					}

					wprintf(L"  Flags[%u]:\t 0x%x", j, pBssEntry->dwFlags);
					if (pBssEntry->dwFlags) {
						if (pBssEntry->dwFlags & WLAN_AVAILABLE_NETWORK_CONNECTED)
							wprintf(L" - Currently connected");
						if (pBssEntry->dwFlags & WLAN_AVAILABLE_NETWORK_CONNECTED)
							wprintf(L" - Has profile");
					}
					wprintf(L"\n");

					wprintf(L"\n");
				}
			}
		}

	}

	wprintf(L"Enter SSID\n");
	wchar_t ssid[36];
	wscanf_s(L"%ls", ssid, 36);

	wprintf(L"Enter security key\n");
	wchar_t securityKey[36];
	wscanf_s(L"%ls", securityKey, 36);

	connect(hClient, &pIfInfo->InterfaceGuid, ssid, securityKey);

	system("pause");

	if (hClient != NULL) {
		dwResult = WlanRegisterNotification(hClient, WLAN_NOTIFICATION_SOURCE_NONE, TRUE, NULL, NULL, NULL, &dwPrevNotif);
		if (dwResult != ERROR_SUCCESS) {
			dwRetVal = 1;
		}
	}
	if (pBssList != NULL) {
		WlanFreeMemory(pBssList);
		pBssList = NULL;
	}

	if (pIfList != NULL) {
		WlanFreeMemory(pIfList);
		pIfList = NULL;
	}

	return dwRetVal;
}
