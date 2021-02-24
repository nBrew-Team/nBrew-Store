/*
*   This file is part of Universal-Updater
*   Copyright (C) 2019-2020 Universal-Team
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#include "credits.hpp"

extern std::unique_ptr<Config> config;
extern bool touching(touchPosition touch, Structs::ButtonPos button);
// Spécial Thanks Page 1.

const std::vector<std::string> specialNames = {
	"CosmicStar3749"
};
const std::vector<std::string> specialDescriptions = {
	"For hosting files and adding games."
};

void Credits::Draw(void) const {
	std::string title = "nBrew Store - ";
	title += Lang::get("CREDITS");
	GFX::DrawTop();
	if (creditsPage != 4) {
		Gui::DrawStringCentered(0, config->useBars() ? 0 : 2, 0.7f, config->textColor(), title, 400);
		Gui::DrawStringCentered(0, 30, 0.7f, config->textColor(), Lang::get("DEVELOPED_BY"), 390);
		GFX::DrawSprite(sprites_stackZ_idx, 5, 85);
		GFX::DrawSprite(sprites_universal_core_idx, 200, 110);
		std::string currentVersion = Lang::get("CURRENT_VERSION");
		currentVersion += V_STRING;
		Gui::DrawString(395-Gui::GetStringWidth(0.70f, currentVersion), 219, 0.70f, config->textColor(), currentVersion, 400);
	} else {
		Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, 190));
		GFX::DrawSprite(sprites_discord_idx, 115, 35);
	}

	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
	DrawBottom();
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
}

void Credits::DrawBottom(void) const {
	std::string line1;
	std::string line2;

	GFX::DrawBottom();
	if (creditsPage == 0) {
		Gui::DrawStringCentered(0, -2, 0.7f, config->textColor(), "Special Thanks", 320);
		for(int i = 0; i < ENTRIES_PER_SCREEN && i < (int)specialNames.size(); i++) {
			Gui::Draw_Rect(0, 40+(i*57), 320, 45, config->unselectedColor());
			line1 = specialNames[screenPos + i];
			line2 = specialDescriptions[screenPos + i];
			if (screenPos + i == Selection) {
				Gui::drawAnimatedSelector(0, 40+(i*57), 320, 45, .060, TRANSPARENT, config->selectedColor());
			}
			Gui::DrawStringCentered(0, 38+(i*57), 0.7f, config->textColor(), line1, 320);
			Gui::DrawStringCentered(0, 62+(i*57), 0.7f, config->textColor(), line2, 320);
		}
	} else {
		Gui::DrawStringCentered(0, -2, 0.55f, config->textColor(), Lang::get("LINK"), 320);
	}
}


void Credits::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (keyRepeatDelay)	keyRepeatDelay--;
	// KEY_DOWN Logic. (SIZE)
	if (creditsPage == 0) {
		if ((hHeld & KEY_DOWN && !keyRepeatDelay)) {
			if (Selection < (int)specialNames.size()-1) {
				Selection++;
			} else {
				Selection = 0;
			}

			keyRepeatDelay = config->keyDelay();
		}
	}

	if ((hHeld & KEY_UP && !keyRepeatDelay)) {
		if (Selection > 0) {
			Selection--;
		} else {
			if (creditsPage == 0) {
			} else if (creditsPage == 1) {
				Selection = (int)specialNames.size()-1;
			}
		}

		keyRepeatDelay = config->keyDelay();
	}
	
		
	if ((hDown & KEY_L || hDown & KEY_LEFT)) {
		if (creditsPage > 0) {
			Selection = 0;
			creditsPage--;
		}
	}

	if ((hDown & KEY_R || hDown & KEY_RIGHT)) {
		if (creditsPage < 1) {
			Selection = 0;
			creditsPage++;
		}
	}

	if (hDown & KEY_B) {
		Gui::screenBack(config->screenFade());
		return;
	}

	if (Selection < screenPos) {
		screenPos = Selection;
	} else if (Selection > screenPos + ENTRIES_PER_SCREEN - 1) {
		screenPos = Selection - ENTRIES_PER_SCREEN + 1;
	}
}