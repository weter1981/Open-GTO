/*
	Created: 05.09.06
	Aurthor: Iain Gilbert
	Modified by ziggi
*/


#if defined _weapons_included
	#endinput
#endif

#define _weapons_included
#pragma library weapons


#include "base"

#define MAX_BULLETS				9000

new Ammunations[][CoordInfo] = {
	{295.3583, -80.1250, 1001.5156}, // LVammunation1
	{290.0941, -109.2533, 1001.5156}, // LSAmmunation2
	{296.1441, -37.7606, 1001.5156}, // LSAmmunation3
	{312.5029, -165.4625, 999.6010} // ����� �����
};

enum WeaponInfo {
	Weapon_ID, // id number of weapon
	Weapon_Name[MAX_NAME], // weapon name
	Weapon_Allowed, // is weapon allowed
	Weapon_IsFirearm, // is weapon is firearm
	Weapon_Cost, // cost per bullet
	Weapon_Level // player level required to buy this weapon
}

new Weapons[][WeaponInfo] = {
	{0,  "����������" 			, 0, 0, 0,     0},
	{1,  "������" 				, 1, 0, 600,   3},
	{2,  "������ ��� ������" 	, 1, 0, 600,   2},
	{3,  "Night Stick" 			, 0, 0, 1000,  18},
	{4,  "���" 					, 1, 0, 1000,  4},
	{5,  "����������� ����" 	, 1, 0, 1500,  7},
	{6,  "Shovel" 				, 0, 0, 100,   0},
	{7,  "���" 					, 1, 0, 100,   11},
	{8,  "��� ������" 			, 1, 0, 2000,  8},
	{9,  "���������" 			, 1, 0, 750,   6},
	{10, "��������� Dildo" 		, 0, 0, 500,   9},
	{11, "��������" 			, 1, 0, 500,   5},
	{12, "������� ����� Dildo" 	, 0, 0, 700,   15},
	{13, "�������� 2" 			, 1, 0, 500,   11},
	{14, "����� ������" 		, 1, 0, 100,   12},
	{15, "������" 				, 1, 0, 100,   8},
	{16, "�������" 				, 1, 1, 800,   43},
	{17, "������� ������" 		, 1, 1, 400,   5},
	{18, "�������� ��������" 	, 1, 1, 550,   35},
		 
	{19, "�����������" 			, 0, 0, 10,    25},
	{20, "�����������" 			, 0, 0, 10,    25},
	{21, "�����������" 			, 0, 0, 10,    25},
		 
	{22, "��������" 			, 1, 1, 10,    0},
	{23, "�������� � ����������", 1, 1, 10,    10},
	{24, "��������� ����" 		, 1, 1, 20,    12},
	{25, "��������" 			, 1, 1, 15,    5},
	{26, "��������� ��������" 	, 1, 1, 25,    25},
	{27, "������ ��������" 		, 1, 1, 40,    26},
	{28, "����� ���" 			, 1, 1, 20,    30},
	{29, "��5(��5)" 			, 1, 1, 25,    32},
	{30, "��47" 				, 1, 1, 40,    35},
	{31, "M4" 					, 1, 1, 40,    36},
	{32, "Tec9" 				, 1, 1, 30,    29},
	{33, "��������" 			, 1, 1, 150,   20},
	{34, "����������� ��������" , 1, 1, 400,   38},
	{35, "���������� ���" 		, 1, 1, 1000,  60},
	{36, "���������� �������� ���������", 0, 1, 1000, 52},
	{37, "�������" 				, 1, 1, 200,   28},
	{38, "������ �������(�������)", 0, 1, 100, 60},
		 
	{39, "���������� ������" 	, 0, 1, 500,   62},
	{40, "��������� � �������" 	, 0, 0, 1,     62},
		 
	{41, "��������� � �������" 	, 1, 1, 40,    5},
	{42, "������������" 		, 1, 1, 10,    5},
	{43, "����������" 			, 1, 1, 60,    24},
	{44, "���� ������� �������"	, 0, 0, 10,    0},
	{45, "�������� ����" 		, 0, 0, 10,    0},
	{46, "�������" 				, 1, 0, 500,   1},
	{47, "�����" 				, 1, 0, 200,   10}
};

stock WeaponLoadAll()
{
	if (ini_Exist(ConfigDB))
	{
		new file_weapons_cfg = ini_Open(ConfigDB);
		ini_Get(file_weapons_cfg, "Weapon_DB", WeaponDB);
		ini_Close(file_weapons_cfg);
	}
	
	new file_weapons, weapondbname[MAX_STRING];
	for (new i = 0; i < sizeof(Weapons); i++)
	{
		format(weapondbname, sizeof(weapondbname), "%sid_%d"GTO_FILES_FORMAT, WeaponDB, Weapons[i][Weapon_ID]);
		if (!ini_Exist(weapondbname))
		{
			continue;
		}
		file_weapons = ini_Open(weapondbname);
		ini_Get(file_weapons, "Name", Weapons[i][Weapon_Name], MAX_NAME);
		ini_GetInt(file_weapons, "IsAllowed", Weapons[i][Weapon_Allowed]);
		ini_GetInt(file_weapons, "Level", Weapons[i][Weapon_Level]);
		ini_GetInt(file_weapons, "Price", Weapons[i][Weapon_Cost]);
		ini_Close(file_weapons);
	}
	return 1;
}

stock WeaponSaveAll()
{
	new file_weapons_cfg = (!ini_Exist(ConfigDB)) ? ini_Create(ConfigDB) : ini_Open(ConfigDB);
	ini_Set(file_weapons_cfg, "Weapon_DB", WeaponDB);
	ini_Close(file_weapons_cfg);
	
	new file_weapons, weapondbname[MAX_STRING];
	for (new i = 0; i < sizeof(Weapons); i++)
	{
		format(weapondbname, sizeof(weapondbname), "%sid_%d"GTO_FILES_FORMAT, WeaponDB, Weapons[i][Weapon_ID]);
		file_weapons = (!ini_Exist(weapondbname)) ? ini_Create(weapondbname) : ini_Open(weapondbname);
		ini_Set(file_weapons, "Name", Weapons[i][Weapon_Name]);
		ini_SetInt(file_weapons, "IsAllowed", Weapons[i][Weapon_Allowed]);
		ini_SetInt(file_weapons, "Level", Weapons[i][Weapon_Level]);
		ini_SetInt(file_weapons, "Price", Weapons[i][Weapon_Cost]);
		ini_Close(file_weapons);
	}
	return 1;
}

stock weapons_OnGameModeInit()
{
	for (new id = 0; id < sizeof(Ammunations); id++)
	{
		CreatePickup(1247, 1, Ammunations[id][Coord_X], Ammunations[id][Coord_Y], Ammunations[id][Coord_Z]);
		CreatePickupText("������", Ammunations[id][Coord_X], Ammunations[id][Coord_Y], Ammunations[id][Coord_Z]);
	}
	GameMSG("SERVER: Weapons module init");
}

stock weapons_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	#pragma unused oldkeys, newkeys
	weapons_ShowDialog_Select(playerid);
	return 1;
}

stock IsPlayerAtAmmunation(playerid)
{
	for (new id = 0; id < sizeof(Ammunations); id++)
	{
		if (IsPlayerInRangeOfPoint(playerid, 2, Ammunations[id][Coord_X], Ammunations[id][Coord_Y], Ammunations[id][Coord_Z]))
		{
			return id;
		}
	}
	return -1;
}

stock oGetWeaponName(weaponid)
{
	new name[MAX_NAME],
		lookupid = GetWeaponLookupID(weaponid);
	
	if (lookupid == -1)
	{
		return name;
	}
	set(name, Weapons[lookupid][Weapon_Name]);
	return name;
}

stock GetWeaponMaxAmmo(weaponid)
{
	new lookupid = GetWeaponLookupID(weaponid);
	if (lookupid == -1)
	{
		return 0;
	}
	if (Weapons[lookupid][Weapon_IsFirearm] == 1)
	{
		return MAX_BULLETS;
	}
	return 1;
}

stock IsPlayerAllowedWeapon(playerid, weaponid)
{
	new lookupid = GetWeaponLookupID(weaponid);
	if (lookupid == -1 || Weapons[lookupid][Weapon_Allowed] == 0 || Weapons[lookupid][Weapon_Level] > GetPlayerLevel(playerid))
	{
		return 0;
	}
	return 1;
}

stock IsWeaponHandToHand(weaponid)
{
	new lookupid = GetWeaponLookupID(weaponid);
	if (lookupid == -1)
	{
		return 0;
	}
	if (Weapons[lookupid][Weapon_IsFirearm] == 0)
	{
		return 1;
	}
	return 0;
}

stock GetWeaponCost(weaponid)
{
	new lookupid = GetWeaponLookupID(weaponid);
	if (lookupid == -1)
	{
		return 0;
	}
	return Weapons[lookupid][Weapon_Cost];
}

stock GetWeaponLookupID(weaponid)
{
	for (new i = 0; i < sizeof(Weapons); i++)
	{
		if (weaponid == Weapons[i][Weapon_ID])
		{
			return i;
		}
	}
	return -1;
}

stock IsWeapon(weaponid)
{
	switch (weaponid)
	{
		case 0..46: return 1;
	}
	return 0;
}

stock BuyWeapon(playerid, weaponid, bullets)
{
	new string[MAX_STRING];
	if (weaponid < 0 || weaponid > 47) {
		SendClientMessage(playerid, COLOUR_RED, lang_texts[16][7]);
		return 0;
	}
	if (bullets < 1) {
		SendClientMessage(playerid, COLOUR_RED, lang_texts[16][8]);
		return 0;
	}
	if (weaponid > 0 && weaponid < 47) {
		new current_bullets = GetPlayerWeaponSlotBullet(playerid, GetWeaponSlot(weaponid));
		if (current_bullets >= MAX_BULLETS) {
			SendClientMessage(playerid, COLOUR_RED, lang_texts[16][1]);
			return 0;
		}
		if (current_bullets + bullets > MAX_BULLETS) {
			SendClientMessage(playerid, COLOUR_RED, lang_texts[16][1]);
			bullets = MAX_BULLETS - GetPlayerWeaponSlotBullet(playerid, GetWeaponSlot(weaponid));
			if (bullets < 1) {
				return 0;
			}
		}
	}
	if (IsPlayerAtAmmunation(playerid) == -1) {
		SendClientMessage(playerid, COLOUR_RED, lang_texts[16][9]);
		return 0;
	}
	if (!IsPlayerAllowedWeapon(playerid, weaponid)) {
		format(string, sizeof(string), lang_texts[16][10], oGetWeaponName(weaponid));
		SendClientMessage(playerid, COLOUR_RED, string);
		return 0;
	}
	new purchasecost = GetWeaponCost(weaponid) * bullets;
	if (purchasecost < 1) {
		format(string, sizeof(string), lang_texts[16][11], oGetWeaponName(weaponid));
		SendClientMessage(playerid, COLOUR_RED, string);
		return 0;
	}
	if (oGetPlayerMoney(playerid) < purchasecost) {
		format(string, sizeof(string), lang_texts[16][12], purchasecost);
		SendClientMessage(playerid, COLOUR_RED, string);
		return 0;
	}
	oGivePlayerMoney(playerid,-purchasecost, 1);
	switch (weaponid) {
		case 47: oSetPlayerArmour(playerid, 100.0);
		case 37: GivePlayerOwnedWeapon(playerid, weaponid, bullets * 10); // ���� ��� ���������� ������ �������
		default: GivePlayerOwnedWeapon(playerid, weaponid, bullets);
	}
	if (bullets > 1) {
		format(string, sizeof(string), lang_texts[16][13], bullets, oGetWeaponName(weaponid), purchasecost);
	} else {
		format(string, sizeof(string), lang_texts[16][14], oGetWeaponName(weaponid), purchasecost);
	}
	SendClientMessage(playerid, COLOUR_RED, string);
	SendClientMessage(playerid, COLOUR_RED, lang_texts[16][15]);
	return 1;
}

stock weapons_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch (dialogid)
	{
		case weapons_Select_DialogID: // �������� ������ �� ������
		{
			if (!response)
			{
				return 0;
			}
			new weaponid = GetSelectedWeaponID(playerid, listitem);
			SetPVarInt(playerid, "Buy_Weapon_ID", weaponid);
			weapons_ShowDialog_Buy(playerid, weaponid);
			return 1;
		}
		case weapons_Buy_DialogID: // ��������, ������ �������
		{
			if (!response)
			{
				return weapons_ShowDialog_Select(playerid);
			}
			new bullets = strval(inputtext);
			if (GetPVarInt(playerid, "weapons_Buy_One_Bullet") == 1)
			{
				bullets = 1;
				DeletePVar(playerid, "weapons_Buy_One_Bullet");
			}
			BuyWeapon(playerid, GetPVarInt(playerid, "Buy_Weapon_ID"), bullets);
			weapons_ShowDialog_Select(playerid);
			return 1;
		}
	}
	return 1;
}

stock weapons_ShowDialog_Select(playerid)
{
	new string[ sizeof(Weapons) * (MAX_NAME + 12 + 4) ];
	for (new weaponid = 1; weaponid < sizeof(Weapons); weaponid++)
	{
		if (!IsPlayerAllowedWeapon(playerid, weaponid))
		{
			continue;
		}
		format(string, sizeof(string), "%s%s, ���� $%d\n", string, oGetWeaponName(weaponid), GetWeaponCost(weaponid));
	}
	return ShowPlayerDialog(playerid, weapons_Select_DialogID, DIALOG_STYLE_LIST,
		"���� ������",
		string,
		"�������", "�����"
	);
}

stock weapons_ShowDialog_Buy(playerid, weaponid)
{
	new string[MAX_STRING], dialog_style = DIALOG_STYLE_INPUT;
	if (Weapons[ GetWeaponLookupID(weaponid) ][Weapon_IsFirearm] == 0)
	{
		format(string, sizeof(string), "������: %s\n����: $%d", oGetWeaponName(weaponid), GetWeaponCost(weaponid));
		dialog_style = DIALOG_STYLE_MSGBOX;
		SetPVarInt(playerid, "weapons_Buy_One_Bullet", 1);
	}
	else if (Weapons[ GetWeaponLookupID(weaponid) ][Weapon_IsFirearm] == 1)
	{
		format(string, sizeof(string),
			"������: %s\n���� �� 1 ������: $%d\n����� ����� ������ �� %d ������\n\n������� ���������� ������:",
			oGetWeaponName(weaponid), GetWeaponCost(weaponid), oGetPlayerMoney(playerid) / GetWeaponCost(weaponid)
		);
	}
	return ShowPlayerDialog(playerid, weapons_Buy_DialogID, dialog_style,
		"������� ������",
		string,
		"������", "�����"
	);
}

// ����� �� ������ �� ������� � �������
stock GetSelectedWeaponID(playerid, listitem)
{
	new k = 0;
	for (new weaponid = 1; weaponid < sizeof(Weapons); weaponid++)
	{
		if (IsPlayerAllowedWeapon(playerid, weaponid))
		{
			k++;
			if (listitem+1 == k)
			{
				return weaponid;
			}
		}
	}
	return 0;
}
//

// ���������� ��������� ������ �� ������
stock ShowWeaponsOnLevel(playerid, newlevel, oldlevel)
{
	new string[MAX_STRING],
		wepfound = 0;
	
	for (new weaponid = 1; weaponid < sizeof(Weapons); weaponid++)
	{
		new lookupid = GetWeaponLookupID(weaponid);
		if (lookupid == -1 || Weapons[lookupid][Weapon_Allowed] == 0)
		{
			continue;
		}
		if (Weapons[lookupid][Weapon_Level] > oldlevel && Weapons[lookupid][Weapon_Level] <= newlevel)
		{
			if (wepfound == 0)
			{
				SendClientMessage(playerid, COLOUR_GREEN, lang_texts[9][24]);
				wepfound = 1;
			}
			format(string, sizeof(string), lang_texts[9][25], oGetWeaponName(weaponid), GetWeaponCost(weaponid));
			SendClientMessage(playerid, COLOUR_MISC, string);
		}
	}
	return 1;
}
//
