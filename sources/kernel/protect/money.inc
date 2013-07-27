/*

	About: money anti cheat
	Author: ziggi

*/

#if defined _money_included
	#endinput
#endif

#define _money_included
#pragma library money


new bool:protect_money_enabled = PROTECT_MONEY_ENABLED;

stock money_LoadConfig(file_cfg)
{
	ini_getInteger(file_cfg, "protect_money_enabled", protect_money_enabled);
	return 1;
}

stock money_SaveConfig(file_cfg)
{
	ini_setInteger(file_cfg, "protect_money_enabled", protect_money_enabled);
	return 1;
}

stock money_Check(playerid)
{
	if (!protect_money_enabled) {
		return 0;
	}
	new clientmoney = GetPlayerMoney(playerid);
	new servermoney = player_GetMoney(playerid);
	
	if (clientmoney > servermoney) {
		player_SetMoney(playerid, servermoney);
	} else if (clientmoney < servermoney) {
		gPlayer[playerid][Money] = clientmoney;
	}
	return 1;
}