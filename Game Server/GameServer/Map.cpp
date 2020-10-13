#include "Server.h"
#include "protocol.h"

int map[Game_Width][Game_Height]{ 0 };
int Tile1[Game_Width][Game_Height]{ 0 };
int Tile2[Game_Width][Game_Height]{ 0 };

void read_map() {
	FILE *pFile = NULL;
	int x = 0, y = 0;
	pFile = fopen( "CollisionCheck_Data\\Tile1.txt", "r" );

	while ( !feof( pFile ) ) { 
		fscanf( pFile, "%d ", &map[x][y] );
		x += 1;
		if ( x >= Game_Width ) {
			x = 0;
			y += 1;
		}
	}
	fclose( pFile );
	x = 0, y = 0;
	pFile = fopen( "CollisionCheck_Data\\Tile2.txt", "r" );

	while ( !feof( pFile ) ) {
		fscanf( pFile, "%d ", &Tile1[x][y] );
		x += 1;
		if ( x >= Game_Width ) {
			x = 0;
			y += 1;
		}
	}
	fclose( pFile );
	x = 0, y = 0;
	pFile = fopen( "CollisionCheck_Data\\Tile3.txt", "r" );

	while ( !feof( pFile ) ) {
		fscanf( pFile, "%d ", &Tile2[x][y] );
		x += 1;
		if ( x >= Game_Width ) {
			x = 0;
			y += 1;
		}
	}
	fclose( pFile );

	std::cout << "맵을 성공적으로 불러왔습니다!" << std::endl;
}

bool CollisionCheck( int ci, int dir ) {
	int m_x = g_clients[ci].x, m_y = g_clients[ci].y;
	switch ( dir ) {
	case CS_UP:
		m_y--;
		break;
	case CS_DOWN:
		m_y++;
		break;
	case CS_LEFT:
		m_x--;
		break;
	case CS_RIGHT:
		m_x++;
		break;
	case CS_NPC:
		break;
	default:
		return false;
		break;
	}

	if ( high_resolution_clock::now() - g_clients[ci].last_move_time <= 1s && g_clients[ci].connect == true && MoveHACK == FALSE ) {
		return false;
	}

	if ( map[m_x][m_y] == 152  ) {
		return false;
	}

	if ( Tile1[m_x][m_y] != 0 ) {
		return false;
	}

	if ( Tile2[m_x][m_y] != 0 ) {
		return false;
	}
	else {
		return true;
	}

}