#include <map>
#include "Event.hpp"
#include "IMap.hpp"
#include "IGUI.hpp"
#include "IGfxLib.hpp"
#include "ITile.hpp"
#include "libLapin.hpp"

namespace arcade
{
	std::map<e_bunny_keysym, KeyboardKey> libLapin::m_keys =
	{
		{BKS_0, KB_0},
		{BKS_1, KB_1},
		{BKS_2, KB_2},
		{BKS_3, KB_3},
		{BKS_4, KB_4},
		{BKS_5, KB_5},
		{BKS_6, KB_6},
		{BKS_7, KB_7},
		{BKS_8, KB_8},
		{BKS_9, KB_9},
		{BKS_RIGHT, KB_ARROW_RIGHT},
		{BKS_LEFT, KB_ARROW_LEFT},
		{BKS_UP, KB_ARROW_UP},
		{BKS_DOWN, KB_ARROW_DOWN},
		{BKS_SPACE, KB_SPACE},
		{BKS_RETURN, KB_ENTER},
		{BKS_A, KB_A},
		{BKS_B, KB_B},
		{BKS_ESCAPE, KB_ESCAPE}

	};
}
