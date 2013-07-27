/*
	
	About: random weather changer
	Author: ziggi
	
*/

#if defined _weather_included
	#endinput
#endif

#define _weather_included
#pragma library weather


static weather_update_time = WEATHER_UPDATE_TIME;

stock weather_OnGameModeInit()
{
	log_Game(_(WEATHER_INIT));
}

stock weather_LoadConfig(file_cfg)
{
	ini_getInteger(file_cfg, "weather_update_time", weather_update_time);
	return 1;
}

stock weather_SaveConfig(file_cfg)
{
	ini_setInteger(file_cfg, "weather_update_time", weather_update_time);
	return 1;
}

stock weather_Update()
{
	if (weather_update_time == 0) {
		return 0;
	}
	
	static timer_ticks;
	timer_ticks++;
	
	if (timer_ticks >= weather_update_time) {
		timer_ticks = 0;
		
		new weatherid;
		switch ( random(2) ) {
			case 0: weatherid = mathrandom(0, 7);
			case 1: weatherid = mathrandom(9, 18);
		}
		SetWeather(weatherid);
		
		log_Game(_(WEATHER_CHANGED), weatherid);
	}
	return 1;
}