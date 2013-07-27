/*
	
	About: jetpack protect
	Author: ziggi
	
*/

#if defined _jetpack_included
	#endinput
#endif

#define _jetpack_included
#pragma library jetpack


new bool:protect_jetpack_enabled = PROTECT_JETPACK_ENABLED;

stock jetpack_LoadConfig(file_cfg)
{
	ini_getInteger(file_cfg, "protect_jetpack_enabled", protect_jetpack_enabled);
	return 1;
}

stock jetpack_SaveConfig(file_cfg)
{
	ini_setInteger(file_cfg, "protect_jetpack_enabled", protect_jetpack_enabled);
	return 1;
}

stock jetpack_Check(playerid)
{
	if (!protect_jetpack_enabled) {
		return 0;
	}
	if (GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK) {
		player_Kick(playerid, _(JETPACK_USING));
	}
	return 1;
}