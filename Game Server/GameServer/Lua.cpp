#include "Server.h"

extern "C" {
#include "LUA\lua.h"
#include "LUA\lauxlib.h"
#include "LUA\lualib.h"
}

int print_LUA( lua_State *L ) {
	int my_id = (int)lua_tonumber( L, -3 );
	int level = (int)lua_tonumber( L, -2 );
	int hp = (int)lua_tonumber( L, -1 );
	lua_pop( L, 4 );

	std::cout << "id : " << my_id << " HP : " << hp << " Level : " << level<< std::endl;
	return 0;
}

int API_get_x( lua_State *L ) {
	int oid = (int)lua_tonumber( L, -1 );
	lua_pop( L, 2 );
	lua_pushnumber( L, g_clients[oid].x );
	return 1;
}

int API_get_y( lua_State *L ) {
	int oid = (int)lua_tonumber( L, -1 );
	lua_pop( L, 2 );
	lua_pushnumber( L, g_clients[oid].y );
	return 1;
}

int API_get_hp( lua_State *L ) {
	int oid = (int)lua_tonumber( L, -1 );
	lua_pop( L, 2 );
	lua_pushnumber( L, g_clients[oid].hp );
	return 1;
}

int API_Send_Message( lua_State *L ) {
	int target_client = (int)lua_tonumber( L, -3 );
	int my_id = (int)lua_tonumber( L, -2 );
	char *mess = (char *)lua_tostring( L, -1 );
	lua_pop( L, 4 );

	size_t wlen, len = strlen( mess ) + 1;
	wchar_t wmess[MAX_STR_SIZE];
	len = (MAX_STR_SIZE - 1 < len) ? MAX_STR_SIZE - 1 : len;
	mbstowcs_s( &wlen, wmess, len, mess, _TRUNCATE );
	wmess[MAX_STR_SIZE - 1] = (wchar_t)0;
	SendChatPacket( target_client, my_id, wmess );
	return 0;
}

// 일반 캐릭터문자와 멀티바이트 캐릭터 문자 바꿔주는 프로그램

char * ConvertWCtoC( wchar_t* str ) {
	char* pStr;
	int strSize = WideCharToMultiByte( CP_ACP, 0, str, -1, NULL, 0, NULL, NULL );
	pStr = new char[strSize];
	WideCharToMultiByte( CP_ACP, 0, str, -1, pStr, strSize, 0, 0 );
	return pStr;
}

wchar_t* ConverCtoWC( char* str ) {
	wchar_t* pStr;
	int strSize = MultiByteToWideChar( CP_ACP, 0, str, -1, NULL, NULL );
	pStr = new WCHAR[strSize];
	MultiByteToWideChar( CP_ACP, 0, str, strlen( str ) + 1, pStr, strSize );
	return pStr;
}