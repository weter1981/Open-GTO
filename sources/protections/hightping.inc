/*
	Author:	ZiGGi
*/

new AntiHightPingEnabled = ANTI_HIGHT_PING_ENABLED,
	MAX_PING = MAXIMAL_PING;

stock AntiHightPingLoadConfig()
{
	if (!ini_Exist(ConfigDB)) return 0;
	new file_ahp = ini_Open(ConfigDB);
	ini_GetInt(file_ahp,"Anti_Hight_Ping_Enabled", AntiHightPingEnabled);
	ini_GetInt(file_ahp,"Anti_Hight_Ping_MAX_PING", MAX_PING);
	ini_Close(file_ahp);
	return 1;
}

stock AntiHightPingSaveConfig()
{
	new file_ahp = (!ini_Exist(ConfigDB)) ? ini_Create(ConfigDB) : ini_Open(ConfigDB);
	ini_SetInt(file_ahp,"Anti_Hight_Ping_Enabled", AntiHightPingEnabled);
	ini_SetInt(file_ahp,"Anti_Hight_Ping_MAX_PING", MAX_PING);
	ini_Close(file_ahp);
	return 1;
}

stock antihightping_OnGameModeInit()
{
	AntiHightPingLoadConfig();
	if (AntiHightPingEnabled != 1) return 0;
	GameMSG("SERVER: (protections)AntiHightPing module init");
	return 1;
}

stock CheckPing(playerid)
{
	if (AntiHightPingEnabled != 1) return 0;
	if (GetPlayerPing(playerid) > MAX_PING)
	{
		new string[MAX_STRING];
		format(string, sizeof(string), lang_texts[11][4], MAX_PING);
		KickPlayer(playerid, string);
	}
	return 1;
}
