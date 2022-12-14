#include "DxLib.h"

int Key[256];

int updateKey()
{
	char tmpkey[256];
	GetHitKeyStateAll(tmpkey);
	for (int i = 0; i < 256; ++i)
	{
		if (tmpkey[i] != 0)
		{
			Key[i]++;
		}
		else {
			Key[i] = 0;
		}
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ChangeWindowMode(TRUE);
	SetAlwaysRunFlag(TRUE);
	//SetOutApplicationLogValidFlag(FALSE);
	SetWindowSizeChangeEnableFlag(TRUE);
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);
	SetWindowText("54HR HRアワーショー");
	SetWindowSizeExtendRate(0.5);
	SetGraphMode(1920, 1080, 32);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	int i = 0;
	int isWindowMode = FALSE;
	bool isScreenBlack = false;
	TCHAR moviePath[256];
	wsprintf(moviePath, TEXT("Movies/%d.mp4"), i);
	int movie = LoadGraph(moviePath);
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !updateKey())
	{
		if (Key[KEY_INPUT_ESCAPE] != 0)
		{
			break;
		}
		if (Key[KEY_INPUT_LSHIFT] != 0 || Key[KEY_INPUT_RSHIFT] != 0)
		{
			isWindowMode = (isWindowMode == TRUE) ? FALSE : TRUE;
			ChangeWindowMode(isWindowMode);
			wsprintf(moviePath, TEXT("Movies/%d.mp4"), i);
			movie = LoadGraph(moviePath);
		}
		if (Key[KEY_INPUT_RIGHT] == 1)
		{
			PauseMovieToGraph(movie);
			i++;
			wsprintf(moviePath, TEXT("Movies/%d.mp4"), i);
			movie = LoadGraph(moviePath);
		}
		if (Key[KEY_INPUT_LEFT] == 1)
		{
			PauseMovieToGraph(movie);
			i--;
			wsprintf(moviePath, TEXT("Movies/%d.mp4"), i);
			movie = LoadGraph(moviePath);
		}
		if (Key[KEY_INPUT_SPACE] == 1)
		{
			if (GetMovieStateToGraph(movie) == TRUE)
			{
				PauseMovieToGraph(movie);
			}
			else {
				PlayMovieToGraph(movie);
			}
		}
		if (Key[KEY_INPUT_B] == 1)
		{
			isScreenBlack = (isScreenBlack) ? false : true;
		}
	
		DrawGraph(0, 0, movie, FALSE);

		if (isScreenBlack)
			DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);

		if (Key[KEY_INPUT_D] != 0)
		{
			if (movie == -1)
				DrawFormatString(0, 20, GetColor(255, 255, 255), "Not Found");

			DrawFormatString(0, 0, GetColor(255, 255, 255), "i: %d", i);
		}
	}

	DxLib_End();
}