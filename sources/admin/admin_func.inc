//
// Created: 27.04.2010
// Aurthor: ZiGGi
//

#if defined _admin_func_included
	#endinput
#endif

#define _admin_func_included
#pragma library admin_func


stock SendClientMessageToAdmins(senderid, text[])
{
	new message[MAX_STRING], count = 0;
	format(message, sizeof(message), lang_texts[12][28], oGetPlayerName(senderid), senderid, text);
	foreach (Player, adminid)
	{
		if (IsPlayerAdm(adminid))
		{
			SendClientMessage(adminid, COLOUR_RED, message);
			count++;
		}
	}
	if (count == 0)
	{
		SendClientMessage(senderid, COLOUR_RED, lang_texts[12][29]);
		return 0;
	} 
	else 
	{
		format(message, sizeof(message), lang_texts[12][30], text);
		SendClientMessage(senderid, COLOUR_GREEN, message);
		return 0;
	}
}

stock admin_OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if (!IsPlayerAdm(playerid)) return 0;
	new vehicleid = GetPlayerVehicleID(playerid);
	if (vehicleid != 0)
	{
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		
		oSetVehiclePos(vehicleid, fX, fY, fZ);
		LinkVehicleToInterior(vehicleid, 0);
		SetVehicleVirtualWorld(vehicleid, 0);
		
		new trailerid = GetVehicleTrailer(vehicleid);
		if (trailerid != 0)
		{
			SetVehiclePos(trailerid, fX, fY, fZ);
			AttachTrailerToVehicle(trailerid, vehicleid);
		}
	}
	else
	{
		oSetPlayerPos(playerid, fX, fY, fZ);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
	}
	return 1;
}

stock admin_OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid)
{
	#pragma unused issuerid, amount, weaponid
	if (IsPlayerGodmod(playerid))
	{
		oSetPlayerHealth(playerid, 100.0);
	}
	return 1;
}
