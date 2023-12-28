#pragma once

struct GameState {
	bool Lose = false;
	bool Win = false;
	bool Started = false;
	bool EditMode = false;
	bool About = false;
	bool TextMode = false;

	void ClearOnEditor()
	{
		Lose = false;
		Win = false;
		Started = false;
		EditMode = true;
		About = false;
		TextMode = false;
	}
};
