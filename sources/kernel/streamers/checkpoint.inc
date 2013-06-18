/*


*/

#if defined _checkpoint_stream_included
	#endinput
#endif

#define _checkpoint_stream_included
#pragma library checkpoint_stream

/*
enum info_CP {
	Float:CP_X,
	Float:CP_Y,
	Float:CP_Z,
	Float:CP_Size
}
static gCheckpoints[MAX_CP][info_CP];

stock cp_IsValid(cpid)
{
	if (gCheckpoints[cpid][CP_X] == 0.0 && gCheckpoints[cpid][CP_Y] == 0.0 && gCheckpoints[cpid][CP_Z] == 0.0 && gCheckpoints[cpid][CP_Size] == 0.0) {
		return 0;
	}
	return 1;
}

stock cp_GetFreeSlot()
{
	for (new cpid = 1; cpid <= MAX_ACTIVECP; cpid++) {
		if (!cp_IsValid(cpid)) {
			return cpid;
		}
	}
	return 0;
}

stock cp_Timer()
{
	foreach (new playerid : Player) {
		if (GetPlayerQuestID(playerid) == INVALID_QUEST_ID) {
			new cpid = cp_GetClosestId(playerid);
			if (cpid != 0) {
				cp_Active(playerid, cpid);
			} else {
				oDisablePlayerCheckpoint(playerid);
			}
		}
	}
}

stock cp_Add(Float:cpx, Float:cpy, Float:cpz, Float:cpsize)
{
	new cpid = cp_GetFreeSlot();
	if (cpid == 0) {
		Log_Error(_(CP_IS_MAX), MAX_CP);
		return 0;
	}
	gCheckpoints[cpid][CP_X] = cpx;
	gCheckpoints[cpid][CP_Y] = cpy;
	gCheckpoints[cpid][CP_Z] = cpz;
	gCheckpoints[cpid][CP_Size] = cpsize;
	return cpid;
}

stock cp_Remove(cpid)
{
	if (!cp_IsValid(cpid)) {
		return 0;
	}
	gCheckpoints[cpid][CP_X] = 0;
	gCheckpoints[cpid][CP_Y] = 0;
	gCheckpoints[cpid][CP_Z] = 0;
	gCheckpoints[cpid][CP_Size] = 0;
	return 1;
}

stock cp_GetIdByPos(Float:cpx, Float:cpy, Float:cpz)
{
	for (new cpid = 1; cpid <= MAX_CP; cpid++) {
		if (cpx == gCheckpoints[cpid][CP_X] && cpy == gCheckpoints[cpid][CP_X] && cpz == gCheckpoints[cpid][CP_Z]) {
			return cpid;
		}
	}
	return 0;
}

stock cp_Active(playerid, cpid)
{
	if (!IsPlayerConnected(playerid) || !cp_IsValid(cpid)) {
		return 0;
	}
	if (gPlayerCp[playerid][Coord_X] == gCheckpoints[cpid][CP_X] && gPlayerCp[playerid][Coord_Y] == gCheckpoints[cpid][CP_Y] && gPlayerCp[playerid][Coord_Z] == gCheckpoints[cpid][CP_Z]) {
		return 0;
	}
	oSetPlayerCheckpoint(playerid, gCheckpoints[cpid][CP_X], gCheckpoints[cpid][CP_Y], gCheckpoints[cpid][CP_Z], gCheckpoints[cpid][CP_Size]);
	return 1;
}

stock cp_GetClosestId(playerid)
{
 	new Float:mindist = CP_SHOW_DIST, Float:playerdist, retval = 0;
	for (new cpid = 1; cpid < MAX_CP; cpid++) {
		if (!cp_IsValid(cpid)) {
			continue;
		}
		playerdist = GetPlayerDistanceFromPoint(playerid, gCheckpoints[cpid][CP_X], gCheckpoints[cpid][CP_Y], gCheckpoints[cpid][CP_Z]);
		if (playerdist < gCheckpoints[cpid][CP_Size] && playerdist < mindist) {
			mindist = playerdist;
			retval = cpid;
		}
	}
	return retval;
}
*/
enum info_Checkpoint {
	Float:Coord_X,
	Float:Coord_Y,
	Float:Coord_Z
}
static Float:gPlayerCp[MAX_PLAYERS][info_Checkpoint];

stock cp_Set(playerid, Float:x, Float:y, Float:z, Float:size)
{
	/*DisablePlayerCheckpoint(playerid);
	SetPlayerCheckpoint(playerid, 0.0, 0.0, 0.0, size);
	DisablePlayerCheckpoint(playerid);*/
	gPlayerCp[playerid][Coord_X] = x;
	gPlayerCp[playerid][Coord_Y] = y;
	gPlayerCp[playerid][Coord_Z] = z;
	SetPlayerCheckpoint(playerid, x, y, z, size);
}

stock cp_Disable(playerid)
{
	gPlayerCp[playerid][Coord_X] = 0.0;
	gPlayerCp[playerid][Coord_Y] = 0.0;
	gPlayerCp[playerid][Coord_Z] = 0.0;
	DisablePlayerCheckpoint(playerid);
}

stock cp_IsIn(playerid, Float:dist, Float:cpx, Float:cpy, Float:cpz)
{
	if (cpx == gPlayerCp[playerid][Coord_X] && cpy == gPlayerCp[playerid][Coord_X] && cpz == gPlayerCp[playerid][Coord_Z]
		&& IsPlayerInRangeOfPoint(playerid, dist, cpx, cpy, cpz)) {
		return IsPlayerInCheckpoint(playerid);
	}
	return 0;
}

stock cp_GetPos(playerid, &Float:X, &Float:Y, &Float:Z)
{
	if (!cp_IsActive(playerid)) {
		return 0;
	}
	X = gPlayerCp[playerid][Coord_X];
	Y = gPlayerCp[playerid][Coord_Y];
	Z = gPlayerCp[playerid][Coord_Z];
	return 1;
}

stock cp_IsActive(playerid)
{
	if (gPlayerCp[playerid][Coord_X] == 0.0 && gPlayerCp[playerid][Coord_Y] == 0.0 && gPlayerCp[playerid][Coord_Z] == 0.0) {
		return 0;
	}
	return 1;
}