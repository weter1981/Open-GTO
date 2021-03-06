/*
	Created by asturel based on business system, thx to Peter Steenbergen
	Modified by ZiGGi
*/

#if defined _housing_included
#endinput
#endif

#define _housing_included
#pragma library housing


#define SetPlayerToHouseID(%0,%1) SetPVarInt(%0, "HausID",%1)
#define GetPlayerToHouseID(%0) GetPVarInt(%0, "HausID")
new house_icon[ sizeof(Houses) ], Text3D:House3DTextLabel[ sizeof(Houses) ], Float:HouseDistanceOfShowLabel=20.0;

stock HousesLoadAll()
{
	if (ini_Exist(ConfigDB))
	{
		new file_housing_cfg = ini_Open(ConfigDB);
		ini_Get(file_housing_cfg, "Houses_DB", HousesDB);
		ini_GetFloat(file_housing_cfg, "House_DistanceOfShowLabel", HouseDistanceOfShowLabel);
		ini_Close(file_housing_cfg);
	}
	new file_housing, housesdbname[MAX_STRING];
	for (new i = 0; i < sizeof(Houses); i++)
	{
		format(housesdbname, sizeof(housesdbname), "%s%s"GTO_FILES_FORMAT, HousesDB, Houses[i][Houses_Name]);
		if (!ini_Exist(housesdbname)) continue;
		file_housing = ini_Open(housesdbname);
		ini_Get(file_housing, "Name", Houses[i][Houses_Name], MAX_NAME);
		ini_GetInt(file_housing, "Cost", Houses[i][Houses_Cost]);
		ini_Get(file_housing, "Owner", Houses[i][Houses_Owner], MAX_NAME);
		ini_Get(file_housing, "Gang", Houses[i][Houses_Gang], MAX_NAME);
		ini_GetInt(file_housing, "UpKeep", Houses[i][Houses_UpKeep]);
		ini_GetInt(file_housing, "UpKeepLeft", Houses[i][Houses_UpKeepLeft]);
		ini_GetInt(file_housing, "Buyout", Houses[i][Houses_Buyout]);
		ini_GetInt(file_housing, "Interior", Houses[i][Houses_Interior]);
		ini_GetInt(file_housing, "Car", Houses[i][Houses_Car]);
		ini_GetInt(file_housing, "Lock", Houses[i][Houses_Lock]);
		ini_GetInt(file_housing, "Rentabil", Houses[i][Houses_Rentabil]);
		ini_Get(file_housing, "RentName", Houses[i][Houses_RentName], MAX_NAME);
		ini_GetInt(file_housing, "RentCost", Houses[i][Houses_RentCost]);
		ini_GetInt(file_housing, "HealUpgrade", Houses[i][Houses_HealUpgrade]);
		ini_GetInt(file_housing, "ArmourUpgrade", Houses[i][Houses_ArmourUpgrade]);
		ini_GetFloat(file_housing, "Coord_X", Houses[i][Houses_EnterX]);
		ini_GetFloat(file_housing, "Coord_Y", Houses[i][Houses_EnterY]);
		ini_GetFloat(file_housing, "Coord_Z", Houses[i][Houses_EnterZ]);
		ini_Close(file_housing);
	}
	return;
}

stock HousesSaveAll()
{
	new file_housing = (!ini_Exist(ConfigDB)) ? ini_Create(ConfigDB) : ini_Open(ConfigDB);
	ini_Set(file_housing, "Houses_DB", HousesDB);
	ini_SetFloat(file_housing, "House_DistanceOfShowLabel", HouseDistanceOfShowLabel);
	ini_Close(file_housing);
	for (new housid = 0; housid < sizeof(Houses); housid++)
	{
		SaveHous(housid);
	}
	return 1;
}

stock SaveHous(housid)
{
	new housesdbname[MAX_STRING];
	format(housesdbname, sizeof(housesdbname), "%s%s"GTO_FILES_FORMAT, HousesDB, Houses[housid][Houses_Name]);
	new file_housing = (!ini_Exist(housesdbname)) ? ini_Create(housesdbname) : ini_Open(housesdbname);
	ini_Set(file_housing, "Name", Houses[housid][Houses_Name]);
	ini_SetInt(file_housing, "Cost", Houses[housid][Houses_Cost]);
	ini_Set(file_housing, "Owner", Houses[housid][Houses_Owner]);
	ini_Set(file_housing, "Gang", Houses[housid][Houses_Gang]);
	ini_SetInt(file_housing, "UpKeep", Houses[housid][Houses_UpKeep]);
	ini_SetInt(file_housing, "UpKeepLeft", Houses[housid][Houses_UpKeepLeft]);
	ini_SetInt(file_housing, "Buyout", Houses[housid][Houses_Buyout]);
	ini_SetInt(file_housing, "Interior", Houses[housid][Houses_Interior]);
	ini_SetInt(file_housing, "Car", Houses[housid][Houses_Car]);
	ini_SetInt(file_housing, "Lock", Houses[housid][Houses_Lock]);
	ini_SetInt(file_housing, "Rentabil", Houses[housid][Houses_Rentabil]);
	ini_Set(file_housing, "RentName", Houses[housid][Houses_RentName]);
	ini_SetInt(file_housing, "RentCost", Houses[housid][Houses_RentCost]);
	ini_SetInt(file_housing, "HealUpgrade", Houses[housid][Houses_HealUpgrade]);
	ini_SetInt(file_housing, "ArmourUpgrade", Houses[housid][Houses_ArmourUpgrade]);
	ini_SetFloat(file_housing, "Coord_X", Houses[housid][Houses_EnterX]);
	ini_SetFloat(file_housing, "Coord_Y", Houses[housid][Houses_EnterY]);
	ini_SetFloat(file_housing, "Coord_Z", Houses[housid][Houses_EnterZ]);
	ini_Close(file_housing);
	return 1;
}
stock housing_OnGameModeInit()
{
	HousesLoadAll();
	new string[MAX_STRING];
	for (new id = 0; id < sizeof(Houses); id++)
	{
		CreatePickup(1273, 1, Houses[id][Houses_PickupX], Houses[id][Houses_PickupY], Houses[id][Houses_PickupZ]+0.5);	//������� �����
		CreatePickup(1559, 1, Houses[id][Houses_EnterX], Houses[id][Houses_EnterY], Houses[id][Houses_EnterZ]+0.5, id+1);
		house_icon[id] = CreateStreamMapIcon(31, Houses[id][Houses_PickupX], Houses[id][Houses_PickupY], Houses[id][Houses_PickupZ]);
		format(string, sizeof(string), lang_texts[8][5], Houses[id][Houses_Name], Houses[id][Houses_Cost], Houses[id][Houses_Owner], Houses[id][Houses_Gang], Houses[id][Houses_RentName]);
		House3DTextLabel[id] = Create3DTextLabel(string, COLOUR_WHITE, Houses[id][Houses_PickupX], Houses[id][Houses_PickupY], Houses[id][Houses_PickupZ]+0.75, HouseDistanceOfShowLabel, 0, 1);
		Houses[id][Houses_VirtualWorld] = id+1;
	}
	GameMSG(lang_texts[8][0]);
}

stock IsPlayerAtHouse(playerid)
{
	for (new id = 0; id < sizeof(Houses); id++)
	{
		if (IsPlayerInRangeOfPoint(playerid, 2, Houses[id][Houses_PickupX], Houses[id][Houses_PickupY], Houses[id][Houses_PickupZ])
		   || IsPlayerInRangeOfPoint(playerid, 2, Houses[id][Houses_EnterX], Houses[id][Houses_EnterY], Houses[id][Houses_EnterZ]))
		{
			return 1;
		}
	}
	return 0;
}

stock IsPlayerRenter(playerid)
{
	new playername[MAX_PLAYER_NAME+1];
	GetPlayerName(playerid, playername, sizeof(playername));
	for (new id = 0; id < sizeof(Houses); id++)
	{
		if (!strcmp(Houses[id][Houses_RentName], playername, true))
		{
			return 1;
		}
	}
	return 0;
}

stock show_House_Menu(playerid)
{
	new id = GetPlayerToHouseID(playerid);
	new string[512], playername[MAX_PLAYER_NAME+1];
	GetPlayerName(playerid, playername, sizeof(playername));
	
	new head[MAX_STRING];
	format(head, sizeof(head), lang_texts[8][3], Houses[id][Houses_Name]);
	
	new isowner = !strcmp(Houses[id][Houses_Owner], playername, true);
	
	if (isowner)
	{
		strcat(string, lang_texts[8][7], sizeof(string));
	}
	else
	{
		strcat(string, lang_texts[8][8], sizeof(string));
	}
	
	strcat(string, lang_texts[8][9], sizeof(string));
	
	if (!isowner)
	{
		if (!strcmp(Houses[id][Houses_RentName], playername, true))
		{
			strcat(string, lang_texts[8][10], sizeof(string));
		}
		else
		{
			strcat(string, lang_texts[8][11], sizeof(string));
		}
	}
	else
	{
		if (!strcmp(Houses[id][Houses_RentName], "Unknown", true))
		{
			if (Houses[id][Houses_Rentabil] == 1)
			{
				strcat(string, lang_texts[8][12], sizeof(string));
			}
			else
			{
				strcat(string, lang_texts[8][13], sizeof(string));
			}
		}
		else
		{
			strcat(string, lang_texts[8][14], sizeof(string));
		}
	}
	
	if (isowner)
	{
		strcat(string, lang_texts[8][67], sizeof(string));
		
		if (Houses[id][Houses_Lock] == 1)
		{
			strcat(string, lang_texts[8][68], sizeof(string));
		}
		else
		{
			strcat(string, lang_texts[8][69], sizeof(string));
		}
			
		strcat(string, lang_texts[8][70], sizeof(string));
		
		strcat(string, lang_texts[8][76], sizeof(string));
	}

	return ShowPlayerDialog(playerid, houses_DialogID, DIALOG_STYLE_LIST,
		head,
		string,
		lang_texts[8][81], lang_texts[8][82]
	);
}

stock show_HouseSellAccept_Dialog(playerid)
{
	return ShowPlayerDialog(playerid, house_sell_accept_DialogID, DIALOG_STYLE_MSGBOX,
		"������� ���?",
		"�� ������������� ������ ������� ���� ���?",
		"�������", "�����"
	);
}

stock housing_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == house_DialogID)
	{
		if (!response) return 1;
		show_House_Menu(playerid);
		return 1;
	}
	if (dialogid == house_sell_accept_DialogID) {
		if (!response) {
			return show_House_Menu(playerid);
		}
		return house_Sell(playerid);
	}
	if (dialogid == houses_DialogID)
	{
		if (!response) return 0;
		new id = GetPlayerToHouseID(playerid);
		new playername[MAX_PLAYER_NAME+1];
		GetPlayerName(playerid, playername, sizeof(playername));
		switch (listitem)
		{
			case 0:
			{
				if (!strcmp(Houses[id][Houses_Owner], playername, true))
				{
					show_HouseSellAccept_Dialog(playerid);
				}
				else
				{
					house_Buy(playerid);
				}
				return 1;
			}
			case 1:
			{
				if (Houses[id][Houses_Lock] == 1)
				{
					return SendClientMessage(playerid, COLOUR_LIGHTRED, lang_texts[8][56]);
				}
				SetPlayerPosEx(playerid, Houses[id][Houses_EnterX], Houses[id][Houses_EnterY], Houses[id][Houses_EnterZ], 0, Houses[id][Houses_Interior], Houses[id][Houses_VirtualWorld]);
				SendClientMessage(playerid, COLOUR_GREEN, lang_texts[8][73]);
				return 1;
			}
			case 2:
			{
				if (strcmp(Houses[id][Houses_Owner], playername, true))
				{
					if (!strcmp(Houses[id][Houses_RentName], playername, true))
					{
						DeleteRenter(playerid);
					}
					else
					{
						RentRoom(playerid);
					}
				}
				else
				{
					if (!strcmp(Houses[id][Houses_RentName], "Unknown", true))
					{
						if (Houses[id][Houses_Rentabil] == 1)
						{
							Houses[id][Houses_Rentabil] = 0;
							SendClientMessage(playerid, COLOUR_GREEN, lang_texts[8][75]);
						}
						else
						{
							Houses[id][Houses_Rentabil] = 1;
							SendClientMessage(playerid, COLOUR_GREEN, lang_texts[8][74]);
						}
					}
					else
					{
						DeleteRenter(playerid);
					}
				}
				return 1;
			}
			case 3:
			{
				new string[MAX_STRING];
				format(string, sizeof(string), lang_texts[8][38], Houses[id][Houses_RentCost]);
				return ShowPlayerDialog(playerid, houses_setrent_DialogID, DIALOG_STYLE_INPUT,
					lang_texts[8][39],
					string,
					lang_texts[8][81], lang_texts[8][82]
				);
			}
			case 4:
			{
				if (Houses[id][Houses_Lock] == 1)
				{
					Houses[id][Houses_Lock] = 0;
					SendClientMessage(playerid, COLOUR_GREEN, lang_texts[8][85]);
				}
				else
				{
					Houses[id][Houses_Lock] = 1;
					SendClientMessage(playerid, COLOUR_GREEN, lang_texts[8][86]);
				}
				return 1;
			}
			case 5:
			{
				return ShowPlayerDialog(playerid, houses_upgrades_DialogID, DIALOG_STYLE_LIST,
					lang_texts[8][83],
					lang_texts[8][84],
					lang_texts[8][81], lang_texts[8][82]
				);
			}
			case 6:
			{
				return house_Keep(playerid);
			}
		}
		return 1;
	}
	if (dialogid == houses_setrent_DialogID)
	{
		if (!response)
		{
			return show_House_Menu(playerid);
		}
		
		new rentcost = strval(inputtext);
		if (rentcost < 1)
		{
			return show_Msg_Dialog(playerid, lang_texts[8][39], lang_texts[8][71], lang_texts[8][87]);
		}
		
		Houses[ GetPlayerToHouseID(playerid) ][Houses_RentCost] = rentcost;
		new string[MAX_STRING];
		format(string, sizeof(string), lang_texts[8][72], rentcost);
		show_Msg_Dialog(playerid, lang_texts[8][39], string, lang_texts[8][87]);
		return 1;
	}
	if (dialogid == houses_upgrades_DialogID)
	{
		if (!response)
		{
			return show_House_Menu(playerid);
		}
		new id = GetPlayerToHouseID(playerid);
		switch (listitem)
		{
			case 0:
			{
				if (Houses[id][Houses_HealUpgrade] == 1)
				{
					oSetPlayerHealth(playerid, GetMaxHealth(playerid));
					return 1;
				}
				if (oGetPlayerMoney(playerid) < HOUSE_UPGRADE_HEALTH_COST)
				{
					new string[MAX_STRING];
					format(string, sizeof(string), lang_texts[8][63], HOUSE_UPGRADE_HEALTH_COST);
					return show_Msg_Dialog(playerid, lang_texts[8][88], string, lang_texts[8][87]);
				}
				
				Houses[id][Houses_HealUpgrade] = 1;
				oGivePlayerMoney(playerid,-HOUSE_UPGRADE_HEALTH_COST, 0);
				show_Msg_Dialog(playerid, lang_texts[8][83], lang_texts[8][64], lang_texts[8][87]);
				return 1;
			}
			case 1:
			{
				if (Houses[id][Houses_ArmourUpgrade] == 1)
				{
					oSetPlayerArmour(playerid, 100);
					return 1;
				}
				if (oGetPlayerMoney(playerid) < HOUSE_UPGRADE_ARMOUR_COST)
				{
					new string[MAX_STRING];
					format(string, sizeof(string), lang_texts[8][63], HOUSE_UPGRADE_ARMOUR_COST);
					return show_Msg_Dialog(playerid, lang_texts[8][89], string, lang_texts[8][87]);
				}

				Houses[id][Houses_ArmourUpgrade] = 1;
				oGivePlayerMoney(playerid,-HOUSE_UPGRADE_ARMOUR_COST, 0);
				show_Msg_Dialog(playerid, lang_texts[8][83], lang_texts[8][64], lang_texts[8][87]);
				return 1;
			}
		}
		return 1;
	}
	return 1;
}

stock RentRoom(playerid)
{
	new id = GetPlayerToHouseID(playerid), string[MAX_STRING];
	if (id <= -1 || IsPlayerRenter(playerid))
	{
		return 1;
	}
	
	if (Houses[id][Houses_Rentabil] == 0)
	{
		return SendClientMessage(playerid, COLOUR_RED, lang_texts[8][66]);
	}
	
	if (strlen(GetPlayerGangName(playerid)) > 0)
	{
		return SendClientMessage(playerid, COLOUR_RED, lang_texts[8][79]);
	}
	
	if (!strcmp(Houses[id][Houses_RentName], "Unknown", true))
	{
		if (oGetPlayerMoney(playerid) < Houses[id][Houses_RentCost])
		{
			return SendClientMessage(playerid, COLOUR_RED, lang_texts[8][57]);
		}
		set(Houses[id][Houses_RentName], oGetPlayerName(playerid));
		oGivePlayerMoney(playerid, -Houses[id][Houses_RentCost], 0);
		
		// ���������� ������ � ���� ���������
		new owner_id = -1;
		foreach (Player, pid) {
			if ( !strcmp(Houses[id][Houses_Owner], oGetPlayerName(pid)) ) {
				owner_id = pid;
				break;
			}
		}
		if (owner_id != -1) {
			GivePlayerBankMoney(owner_id, Houses[id][Houses_RentCost]);
		} else {
			new filename_player[MAX_STRING];
			format(filename_player, sizeof(filename_player), "%s%s"GTO_FILES_FORMAT, PlayerDB, Houses[id][Houses_Owner]);
			new file_player = ini_Open(filename_player);
			new bank_money;
			ini_GetInt(file_player, "BankMoney", bank_money);
			ini_SetInt(file_player, "BankMoney", bank_money + Houses[id][Houses_RentCost]);
			ini_Close(file_player);
		}
		
		format(string, sizeof(string), "%s%s"GTO_FILES_FORMAT, HousesDB, Houses[id][Houses_Name]);
		new file_housing = ini_Open(string);
		ini_SetInt(file_housing, "Rentabil", 1);
		ini_Set(file_housing, "RentName", oGetPlayerName(playerid));
		ini_Close(file_housing);
		SendClientMessage(playerid, COLOUR_GREEN, lang_texts[8][55]);
		UpdatePlayerStreamMapIcon(playerid, house_icon[id]);
	}
	else
	{
		format(string, sizeof(string), lang_texts[8][54], Houses[id][Houses_RentName]);
		SendClientMessage(playerid, COLOUR_RED, string);
	}
	return 1;
}

stock DeleteRenter(playerid)
{
	new id = GetPlayerToHouseID(playerid);
	if (!strcmp(Houses[id][Houses_Owner], oGetPlayerName(playerid), true)) 
	{
		SendClientMessage(playerid, COLOUR_WHITE, lang_texts[8][58]);
		foreach (Player, i)
		{
			if (!strcmp(Houses[id][Houses_RentName], oGetPlayerName(i), true))
			{
				SendClientMessage(i, COLOUR_LIGHTRED, lang_texts[8][60]);
				UpdatePlayerStreamMapIcon(playerid, house_icon[id]);
			}
		}
	}
	else if (!strcmp(Houses[id][Houses_RentName], oGetPlayerName(playerid), true))
	{
		SendClientMessage(playerid, COLOUR_LIGHTRED, lang_texts[8][59]);
	}
	if (id > -1)
	{
		set(Houses[id][Houses_RentName], "Unknown");
	}
	return 1;
}

stock house_Buy(playerid) 
{
	new playername[MAX_PLAYER_NAME+1], pl_houses=0;
	GetPlayerName(playerid, playername, sizeof(playername));
	for (new i = 0; i < sizeof(Houses); i++)
	{
		if (!strcmp(Houses[i][Houses_Owner], playername, true))
		{
			pl_houses++;
			if (pl_houses >= MAX_PLAYER_HOUSES)
			{
				return SendClientMessage(playerid, COLOUR_RED, lang_texts[8][78]);
			}
		}
	}
	new temp[MAX_STRING];
	new id = GetPlayerToHouseID(playerid);
	if (id <= -1)
		return SendClientMessage(playerid, COLOUR_RED, lang_texts[8][21]);
	
	if (GetPlayerGangID(playerid) == 0)
		return SendClientMessage(playerid, COLOUR_RED, lang_texts[8][19]);

	new price = Houses[id][Houses_Cost] + Houses[id][Houses_Buyout];
	if (oGetPlayerMoney(playerid) < price)
		return SendClientMessage(playerid, COLOUR_RED, lang_texts[8][18]);

	if (!strcmp(Houses[id][Houses_Owner], playername, true))
	{
		SendClientMessage(playerid, COLOUR_RED, lang_texts[8][16]);
	}
#if !defined BUY_ALL_HOUSES
	else if (strcmp(Houses[id][Houses_Owner], "Unknown", true))
	{
		SendClientMessage(playerid, COLOUR_RED, lang_texts[8][77]);
	}
#endif
	else
	{
	#if defined BUY_ALL_HOUSES
		foreach (Player, ownerid)
		{
			if (!strcmp(Houses[id][Houses_Owner], oGetPlayerName(ownerid), true))
			{
				format(temp, sizeof(temp), lang_texts[8][17], oGetPlayerName(playerid), Houses[id][Houses_Name]);
				SendClientMessage(ownerid, COLOUR_RED, temp);
				oGivePlayerMoney(ownerid, price, 1);
				break;
			}
		}
	#endif
		oGivePlayerMoney(playerid,-price, 1);
		set(Houses[id][Houses_Owner], playername);
		set(Houses[id][Houses_Gang], GetPlayerGangName(playerid));
		Houses[id][Houses_Buyout] = 0;
		// ���� ����� ����� ���� ������ ���, �� ������ ����� � ����
		if (pl_houses == 0)
		{
			SetPlayerSpawnHouseID(playerid, id);
		}
		UpdateStreamMapIcon(house_icon[id]);
		format(temp, sizeof(temp), lang_texts[8][17], Houses[id][Houses_Name]);
		SendClientMessage(playerid, COLOUR_GREEN, temp);
		GameMSG("player: %s(%d): bought the '%s' (house)", playername, playerid, Houses[id][Houses_Name]);
	}
	return 1;
}

stock house_Sell(playerid) 
{
	house_Keep(playerid);
	new id = GetPlayerToHouseID(playerid);
	if (id <= -1)
	{
		return SendClientMessage(playerid, COLOUR_RED, lang_texts[8][28]);
	}

	if (strcmp(Houses[id][Houses_Owner], oGetPlayerName(playerid), true))
	{
		SendClientMessage(playerid, COLOUR_RED, lang_texts[8][23]);
	}
	else
	{
		new price = ((Houses[id][Houses_Cost] + Houses[id][Houses_Buyout]) * 85) / 100;
		oGivePlayerMoney(playerid, price, 1);
		house_Free(id);
		new gangid = GetPlayerGangID(playerid);
		if (gang_GetHouse(gangid) == id)
		{
			gang_SetHouse(gangid, -1);
		}
		SetPlayerSpawnHouseID(playerid, SPAWN_HOUSE_NONE);
		new temp[MAX_STRING];
		format(temp, sizeof(temp), lang_texts[8][24], Houses[id][Houses_Name]);
		SendClientMessage(playerid, COLOUR_GREEN, temp);
		SendClientMessage(playerid, COLOUR_GREEN, lang_texts[8][25]);
		GameMSG("player: %s(%d): sold the '%s' (house)", oGetPlayerName(playerid), playerid, Houses[id][Houses_Name]);
	}
	return 1;
}

stock house_Keep(playerid) 
{
	new id = GetPlayerToHouseID(playerid);
	if (id <= -1)
	{
		return SendClientMessage(playerid, COLOUR_RED, lang_texts[8][50]);
	}
	
	if (strcmp(Houses[id][Houses_Gang], GetPlayerGangName(playerid), true))
	{
		return SendClientMessage(playerid, COLOUR_RED, lang_texts[8][47]);
	}
	
	if (oGetPlayerMoney(playerid) < Houses[id][Houses_UpKeepLeft])
	{
		return SendClientMessage(playerid, COLOUR_RED, lang_texts[8][46]);
	}

	if (Houses[id][Houses_UpKeepLeft] <= 0)
	{
		return SendClientMessage(playerid, COLOUR_RED, lang_texts[8][45]);
	}

	oGivePlayerMoney(playerid, -Houses[id][Houses_UpKeepLeft], 0);
	SendClientMessage(playerid, COLOUR_GREEN, lang_texts[8][44]);
	Houses[id][Houses_UpKeepLeft] = 0;
	return 1;
}

stock SetPlayerPosToHouse(playerid, i)
{
	SetPlayerPosEx(playerid, Houses[i][Houses_PickupX], Houses[i][Houses_PickupY], Houses[i][Houses_PickupZ]+0.5, 0, 0, 0);
}

stock HouseKeepUp()
{
	new upkeepamount, upkeep, upkeepleft;
	for (new id = 0; id <  sizeof(Houses); id++)
	{
		if (!strcmp(Houses[id][Houses_Owner], "Unknown", true))
		{
			continue;
		}
		
		upkeep = Houses[id][Houses_UpKeep];
		upkeepleft = Houses[id][Houses_UpKeepLeft];
		upkeepamount = upkeep + upkeepleft;
		if (upkeepamount < upkeep*2800) 
		{
			Houses[id][Houses_UpKeepLeft] = upkeepamount;
		} 
		else 
		{
			house_Free(id);
		}
	}
}

stock housing_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	#pragma unused oldkeys, newkeys
	new player_vw = GetPlayerVirtualWorld(playerid);
	for (new id = 0; id < sizeof(Houses); id++)
	{
		SetPlayerToHouseID(playerid, id);
		if (IsPlayerInRangeOfPoint(playerid, 3, Houses[id][Houses_PickupX], Houses[id][Houses_PickupY], Houses[id][Houses_PickupZ]+0.5))
		{
			new head[MAX_STRING], string[512];
			format(head, sizeof(head), lang_texts[8][3], Houses[id][Houses_Name]);
			new price = Houses[id][Houses_Cost] + Houses[id][Houses_Buyout],
				UpKeep = Houses[id][Houses_UpKeep];
			if (strcmp(Houses[id][Houses_Owner], "Unknown", true) && strcmp(Houses[id][Houses_Gang], "Unknown", true))
			{
				if (strcmp(Houses[id][Houses_Owner], oGetPlayerName(playerid), true))
				{
					format(string, sizeof(string),
						lang_texts[8][1],
						price, UpKeep, Houses[id][Houses_UpKeepLeft], UpKeep*2800, Houses[id][Houses_Gang], Houses[id][Houses_Owner]
					);
					
					new buf[MAX_STRING];
					if (!strcmp(Houses[id][Houses_RentName], "Unknown", true))
					{
						format(buf, sizeof(buf), lang_texts[8][53], Houses[id][Houses_RentCost]);
					}
					else
					{
						format(buf, sizeof(buf), lang_texts[8][52], Houses[id][Houses_RentName]);
					}
					
					strcat(string, buf, sizeof(string));
					return ShowPlayerDialog(playerid, house_DialogID, DIALOG_STYLE_MSGBOX, head, string, lang_texts[8][80], lang_texts[8][82]);
				}
				else
				{
					format(string, sizeof(string), lang_texts[8][6], price, UpKeep, Houses[id][Houses_UpKeepLeft], UpKeep*2800);
					
					new buf[MAX_STRING];
					if (!strcmp(Houses[id][Houses_RentName], "Unknown", true))
						format(buf, sizeof(buf), lang_texts[8][53], Houses[id][Houses_RentCost]);
					else
						format(buf, sizeof(buf), lang_texts[8][52], Houses[id][Houses_RentName]);
					
					strcat(string, buf, sizeof(string));
					return ShowPlayerDialog(playerid, house_DialogID, DIALOG_STYLE_MSGBOX, head, string, lang_texts[8][80], lang_texts[8][82]);
				}
			}
			else
			{
				format(string, sizeof(string), lang_texts[8][15], Houses[id][Houses_Cost], Houses[id][Houses_UpKeep]);
				
				return ShowPlayerDialog(playerid, house_DialogID, DIALOG_STYLE_MSGBOX, head, string, lang_texts[8][80], lang_texts[8][82]);
			}
		}
		else if (IsPlayerInRangeOfPoint(playerid, 2, Houses[id][Houses_EnterX], Houses[id][Houses_EnterY], Houses[id][Houses_EnterZ]) && player_vw == Houses[id][Houses_VirtualWorld])
		{
			SetPlayerPosToHouse(playerid, id);
			SetPlayerToHouseID(playerid,-1);
			return 1;
		}
		SetPlayerToHouseID(playerid,-1);
	}
	return 1;
}

stock housing_Update3DTextLabelText()
{
	new string[MAX_STRING];
	for (new id = 0; id < sizeof(Houses); id++)
	{
		format(string, sizeof(string), lang_texts[8][5], Houses[id][Houses_Name], Houses[id][Houses_Cost], Houses[id][Houses_Owner], Houses[id][Houses_Gang], Houses[id][Houses_RentName]);
		Update3DTextLabelText(House3DTextLabel[id], COLOUR_WHITE, string);
	}
	return 1;
}

stock housing_RenameOwner(old_name[MAX_PLAYER_NAME+1], new_name[MAX_PLAYER_NAME+1])
{
	for (new i = 0; i < sizeof(Houses); i++)
	{
		if (!strcmp(Houses[i][Houses_Owner], old_name, true))
		{
			set(Houses[i][Houses_Owner], new_name);
			return 1;
		}
	}
	return 0;
}

stock CheckHousesOwners()
{
	new filename_account[MAX_STRING], file_account, account_lastlogin[32], idx,
		year, month, day, account_year, account_month, account_day;
	
	getdate(year, month, day);
	for (new i = 0; i < sizeof(Houses); i++)
	{
		if (!strcmp(Houses[i][Houses_Owner], "Unknown", false))
		{
			continue;
		}
		
		format(filename_account, sizeof(filename_account), "%s%s"GTO_FILES_FORMAT, AccountDB, Houses[i][Houses_Owner]);
		if (!ini_Exist(filename_account))
		{
			continue;
		}
		
		file_account = ini_Open(filename_account);
		ini_Get(file_account, "Last_Login", account_lastlogin);
		ini_Close(file_account);
		
		idx = 0;
		account_day = strval( strcharsplit(account_lastlogin, idx, '.') );
		account_month = strval( strcharsplit(account_lastlogin, idx, '.') );
		account_year = strval( strcharsplit(account_lastlogin, idx, ',') );
		
		if (DateToNum(year, month, day) > DateToNum(account_year, account_month, account_day) + HOUSE_UNLOGIN_SELL_DAYS * 24 * 60 * 60)
		{
			GameMSG("House has been free. Owner '%s'. HOUSE_UNLOGIN_SELL_DAYS = %d",
				Houses[i][Houses_Owner], HOUSE_UNLOGIN_SELL_DAYS
			);
			GameMSG("\tcurrent date[%02d.%02d.%d]: %d, last login[%02d.%02d.%d]: %d",
				day, month, year, DateToNum(year, month, day),
				account_day, account_month, account_year, DateToNum(account_year, account_month, account_day)
			);
			
			house_Free(i);
		}
		
	}
}

stock house_Free(houseid)
{
	set(Houses[houseid][Houses_Owner], "Unknown");
	set(Houses[houseid][Houses_Gang], "Unknown");
	Houses[houseid][Houses_Buyout] = 0;
	Houses[houseid][Houses_Lock] = 0;
	Houses[houseid][Houses_UpKeepLeft] = 0;
	UpdateStreamMapIcon(house_icon[houseid]);
}
