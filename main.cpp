//=================================================================================================
//
// Name Hunter
// Author : Kagaya
//
//=================================================================================================
#define _CRT_SECURE_NO_WARNINGS
#define SKILLPOINT1 (15)
#define SKILLPOINT2 (25)
#define SKILLPOINT3 (15)
#define SKILLPOINT4 (25)
#define SKILLPOINT5 (13)
#define SKILLPOINT6 (15)
#define SKILLPOINT7 (15)
#define SKILLPOINT8 (20)
#define SKILLPOINT9 (13)
#define SKILLPOINT10 (30)
#define SKILLPOINT11 (20)
#define SKILLPOINT12 (10)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <iostream>
#include <MMSystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;


//構造体の定義
typedef struct {
	char aName[15];    //名前

	int nHealth;       //体力
	int nMaxHealth;    //体力上限

	int nSkillPoint;   //スキルポイント

	int nAttack;       //攻撃力

	int nDefence;      //防御力
	int nDefenceSave;  //防御力保存
	int nDefenceUp;    //防御力上昇ターン
	int nDefenceDown;  //防御力減少ターン

	int nAgility;      //素早さ
	int nAgilitySave;  //素早さ保存
	int nAgilityUp;    //素早さ上昇ターン
	int nAgilityDown;  //素早さ減少ターン

	int nHitRate;      //命中率
	int nHitRateSave;  //命中率保存
	int nHitRateUp;    //命中率上昇ターン
	int nHitRateDown;  //命中率減少ターン

	int nCriticalRate;     //クリティカル率
	int nCriticalRateSave; //クリティカル率保存
	int nCriticalRateUp;   //クリティカル率上昇ターン
	int nCriticalRateDown; //クリティカル率減少ターン

	bool bShield;      //シールド(有無)

	int nPoison;       //毒(ターン)

	bool bOffenseTurn;  //攻撃のターンか否か
}Player;

//プロトタイプ宣言
void Attention(void);
void Title(void);
void MoveTitle(void);
int InputKey(void); //キー入力
void Menu(Player *pPlayer1, Player *pPlayer2);
void SetName(Player *pPlayer);                                      //名前ステータス設定
int Battle(Player *pPlayer1, Player *pPlayer2);                     //戦闘処理
void BattleInfo(Player *pPlayer1, int nTurn);     //ステータス表示
void BattleDisplay(Player *pOffense, Player *pDefense, Player *pPlayer1, int nTurn);            //戦闘画面
void Command(Player *pOffense, Player *pDefense, Player *pPlayer1, int *pCommand, int nTurn);    //コマンド処理
void HpSpControl(Player *pPlayer1, Player *pPlayer2);             //Health SkillPoint 管理
void StatusControl(Player *pPlayer1, Player *pPlayer2);             //ステータス管理
void StatusTurn(Player *pPlayer1, Player *pPlayer2, int nTurn);                //ステータスターン管理
void EndBattle(Player *pPlayer1, Player *pPlayer2, int nWinPlayer); //戦闘終了メッセージ表示

//グローバル宣言
CONSOLE_CURSOR_INFO cci;
HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

//===============================================
//メイン関数
//===============================================
int main(void) {
	COORD dwSize = { 149, 32 };
	SetConsoleScreenBufferSize(hConsoleOutput, dwSize);
	
	SMALL_RECT consoleWindow = { 0, 0, 148, 31 };
	SetConsoleWindowInfo(hConsoleOutput, true, &consoleWindow);

	GetConsoleCursorInfo(hConsoleOutput, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hConsoleOutput, &cci);

	srand((unsigned int)time(NULL));

	Player aPlayer[2];  //2人分のプレイヤーデータ
	
	Attention();

	Menu(&aPlayer[0], &aPlayer[1]);

	return 0;
}

//===============================================
//注意
//===============================================
void Attention(void) {

	Sleep(1000);

	PlaySound(TEXT("bgm//Warning.wav"), NULL, SND_FILENAME | SND_ASYNC);

	printf("\n\n\n\n					  ┌─────────────────────────────────────────────────┐\n");
	printf("			 		  │                   △ご注意                      │\n");
	printf("			 		  │           製作者の管理者の許諾なく              │\n");
	printf("			   		  │    インターネットを通じて配信、配布する行為、   │\n");
	printf("					  │     また、プログラムの改ざん、改造する行為は    │\n");
	printf("					  │               普通に固く禁じます。              │\n");
	printf("					  │  みなさまのご理解とご協力をおねがいいたします。 │\n");
	printf("					  └─────────────────────────────────────────────────┘\n");

	Sleep(4000);
}

//===============================================
//タイトル
//===============================================
void Title(void) {
	int nCount;
	char aTitle[18][150] = {"*****************************************************************************************************************************************************",
							"*                                                                                                                  ,----,                           *",
							"*             ,--.                           ____                        ,--,                         ,--.       ,/   .`|                           *",
							"*           ,--.'|    ,---,                ,'  , `.     ,---,.         ,--.'|                       ,--.'|     ,`   .'  :     ,---,. ,-.----.       *",
							"*       ,--,:  : |   '  .' \\            ,-+-,.' _ |   ,'  .' |      ,--,  | :          ,--,     ,--,:  : |   ;    ;     /   ,'  .' | \\    /  \\      *",
							"*    ,`--.'`|  ' :  /  ;    '.       ,-+-. ;   , || ,---.'   |   ,---.'|  : '        ,'_ /|  ,`--.'`|  ' : .'___,/    ,'  ,---.'   | ;   :    \\     *",
							"*    |   :  :  | | :  :       \\     ,--.'|'   |  ;| |   |   .'   |   | : _' |   .--. |  | :  |   :  :  | | |    :     |   |   |   .' |   | .\\ :     *",
							"*    :   |   \\ | : :  |   /\\   \\   |   |  ,', |  ': :   :  |-,   :   : |.'  | ,'_ /| :  . |  :   |   \\ | : ;    |.';  ;   :   :  |-, .   : |: |     *",
							"*    |   : '  '; | |  :  ' ;.   :  |   | /  | |  || :   |  ;/|   |   ' '  ; : |  ' | |  . .  |   : '  '; | `----'  |  |   :   |  ;/| |   |  \\ :     *",
							"*    '   ' ;.    ; |  |  ;/  \\   \\ '   | :  | :  |, |   :   .'   '   |  .'. | |  | ' |  | |  '   ' ;.    ;     '   :  ;   |   :   .' |   : .  /     *",
							"*    |   | | \\   | '  :  | \\  \\ ,' ;   . |  ; |--'  |   |  |-,   |   | :  | ' :  | | :  ' ;  |   | | \\   |     |   |  '   |   |  |-, ;   | |  \\     *",
							"*    '   : |  ; .' |  |  '  '--'   |   : |  | ,     '   :  ;/|   '   : |  : ; |  ; ' |  | '  '   : |  ; .'     '   :  |   '   :  ;/| |   | ;\\  \\    *",
							"*    |   | '`--'   |  :  :         |   : '  |/      |   |    \\   |   | '  ,/  :  | : ;  ; |  |   | '`--'       ;   |.'    |   |    \\ :   ' | \\.'    *",
							"*    '   : |       |  | ,'         ;   | |`-'       |   :   .'   ;   : ;--'   '  :  `--'   \\ '   : |           '---'      |   :   .' :   : :-'      *",
							"*    ;   |.'       `--''           |   ;/           |   | ,'     |   ,/       :  ,      .-./ ;   |.'                      |   | ,'   |   |.'        *",
							"*    '---'                         '---'            `----'       '---'         `--`----'     '---'                        `----'     `---'          *",
							"*                                                                                                                                                   *",
							"*****************************************************************************************************************************************************"};
	system("cls");

	for (nCount = 0; nCount < 18; nCount++) {
		printf("%s\n", &aTitle[nCount][0]);
	}

}

//===============================================
//動くタイトル
//===============================================
void MoveTitle(void) {
	int nCount;
	int nCount2;
	int nMinus;

	PlaySound(TEXT("bgm//TitleBgm.wav"), NULL, SND_FILENAME | SND_ASYNC);
	char aTitle[18][150] = {"*****************************************************************************************************************************************************",
							"*                                                                                                                  ,----,                           *",
							"*             ,--.                           ____                        ,--,                         ,--.       ,/   .`|                           *",
							"*           ,--.'|    ,---,                ,'  , `.     ,---,.         ,--.'|                       ,--.'|     ,`   .'  :     ,---,. ,-.----.       *",
							"*       ,--,:  : |   '  .' \\            ,-+-,.' _ |   ,'  .' |      ,--,  | :          ,--,     ,--,:  : |   ;    ;     /   ,'  .' | \\    /  \\      *",
							"*    ,`--.'`|  ' :  /  ;    '.       ,-+-. ;   , || ,---.'   |   ,---.'|  : '        ,'_ /|  ,`--.'`|  ' : .'___,/    ,'  ,---.'   | ;   :    \\     *",
							"*    |   :  :  | | :  :       \\     ,--.'|'   |  ;| |   |   .'   |   | : _' |   .--. |  | :  |   :  :  | | |    :     |   |   |   .' |   | .\\ :     *",
							"*    :   |   \\ | : :  |   /\\   \\   |   |  ,', |  ': :   :  |-,   :   : |.'  | ,'_ /| :  . |  :   |   \\ | : ;    |.';  ;   :   :  |-, .   : |: |     *",
							"*    |   : '  '; | |  :  ' ;.   :  |   | /  | |  || :   |  ;/|   |   ' '  ; : |  ' | |  . .  |   : '  '; | `----'  |  |   :   |  ;/| |   |  \\ :     *",
							"*    '   ' ;.    ; |  |  ;/  \\   \\ '   | :  | :  |, |   :   .'   '   |  .'. | |  | ' |  | |  '   ' ;.    ;     '   :  ;   |   :   .' |   : .  /     *",
							"*    |   | | \\   | '  :  | \\  \\ ,' ;   . |  ; |--'  |   |  |-,   |   | :  | ' :  | | :  ' ;  |   | | \\   |     |   |  '   |   |  |-, ;   | |  \\     *",
							"*    '   : |  ; .' |  |  '  '--'   |   : |  | ,     '   :  ;/|   '   : |  : ; |  ; ' |  | '  '   : |  ; .'     '   :  |   '   :  ;/| |   | ;\\  \\    *",
							"*    |   | '`--'   |  :  :         |   : '  |/      |   |    \\   |   | '  ,/  :  | : ;  ; |  |   | '`--'       ;   |.'    |   |    \\ :   ' | \\.'    *",
							"*    '   : |       |  | ,'         ;   | |`-'       |   :   .'   ;   : ;--'   '  :  `--'   \\ '   : |           '---'      |   :   .' :   : :-'      *",
							"*    ;   |.'       `--''           |   ;/           |   | ,'     |   ,/       :  ,      .-./ ;   |.'                      |   | ,'   |   |.'        *",
							"*    '---'                         '---'            `----'       '---'         `--`----'     '---'                        `----'     `---'          *",
							"*                                                                                                                                                   *",
							"*****************************************************************************************************************************************************" };

	system("cls");

	for (nCount = 0; nCount < 18; nCount++) {
		nMinus = 17;
		nMinus -= nCount;
		for (nCount2 = 0; nCount2 < nCount + 1; nCount2++) {
			printf("%s\n", &aTitle[0 + nMinus][0]);
			nMinus++;
		}
		Sleep(100);
		system("cls");
	}
}

//===============================================
//キー入力
//===============================================
int InputKey(void) {
	int nKey;
	char aKey;

	while (1) {
		nKey = _getch();

		if (nKey == 97) { // a
			aKey = 'a';
		}
		else if (nKey == 98) { // b
			aKey = 'b';
		}
		else if (nKey == 99) { // c
			aKey = 'c';
		}
		else if (nKey == 100) { // d
			aKey = 'd';
		}
		else if (nKey == 101) { // e
			aKey = 'e';
		}
		else if (nKey == 102) { // f
			aKey = 'f';
		}
		else if (nKey == 103) { // g
			aKey = 'g';
		}
		else if (nKey == 104) { // h
			aKey = 'h';
		}
		else if (nKey == 105) { // i
			aKey = 'i';
		}
		else if (nKey == 106) { // j
			aKey = 'j';
		}
		else if (nKey == 107) { // k
			aKey = 'k';
		}
		else if (nKey == 108) { // l
			aKey = 'l';
		}
		else if (nKey == 109) { // m
			aKey = 'm';
		}
		else if (nKey == 110) { // n
			aKey = 'n';
		}
		else if (nKey == 111) { // o
			aKey = 'o';
		}
		else if (nKey == 112) { // p
			aKey = 'p';
		}
		else if (nKey == 113) { // q
			aKey = 'q';
		}
		else if (nKey == 114) { // r
			aKey = 'r';
		}
		else if (nKey == 115) { // s
			aKey = 's';
		}
		else if (nKey == 116) { // t
			aKey = 't';
		}
		else if (nKey == 117) { // u
			aKey = 'u';
		}
		else if (nKey == 118) { // v
			aKey = 'v';
		}
		else if (nKey == 119) { // w
			aKey = 'w';
		}
		else if (nKey == 120) { // x
			aKey = 'x';
		}
		else if (nKey == 121) { // y
			aKey = 'y';
		}
		else if (nKey == 122) { // z
			aKey = 'z';
		}
		//-------------------------------------------
		else if (nKey == 65) { // A
			aKey = 'A';
		}
		else if (nKey == 66) { // B
			aKey = 'B';
		}
		else if (nKey == 67) { // C
			aKey = 'C';
		}
		else if (nKey == 68) { // D
			aKey = 'D';
		}
		else if (nKey == 69) { // E
			aKey = 'E';
		}
		else if (nKey == 70) { // F
			aKey = 'F';
		}
		else if (nKey == 71) { // G
			aKey = 'G';
		}
		else if (nKey == 72) { // H
			aKey = 'H';
		}
		else if (nKey == 73) { // I
			aKey = 'I';
		}
		else if (nKey == 74) { // J
			aKey = 'J';
		}
		else if (nKey == 75) { // K
			aKey = 'K';
		}
		else if (nKey == 76) { // L
			aKey = 'L';
		}
		else if (nKey == 77) { // M
			aKey = 'M';
		}
		else if (nKey == 78) { // N
			aKey = 'N';
		}
		else if (nKey == 79) { // O
			aKey = 'O';
		}
		else if (nKey == 80) { // P
			aKey = 'P';
		}
		else if (nKey == 81) { // Q
			aKey = 'Q';
		}
		else if (nKey == 82) { // R
			aKey = 'R';
		}
		else if (nKey == 83) { // S
			aKey = 'S';
		}
		else if (nKey == 84) { // T
			aKey = 'T';
		}
		else if (nKey == 85) { // U
			aKey = 'U';
		}
		else if (nKey == 86) { // V
			aKey = 'V';
		}
		else if (nKey == 87) { // W
			aKey = 'W';
		}
		else if (nKey == 88) { // X
			aKey = 'X';
		}
		else if (nKey == 89) { // Y
			aKey = 'Y';
		}
		else if (nKey == 90) { // Z
			aKey = 'Z';
		}
		//-------------------------------------------
		else if (nKey == 49) { // 1
			aKey = '1';
		}
		else if (nKey == 50) { // 2
			aKey = '2';
		}
		else if (nKey == 51) { // 3
			aKey = '3';
		}
		else if (nKey == 52) { // 4
			aKey = '4';
		}
		else if (nKey == 53) { // 5
			aKey = '5';
		}
		else if (nKey == 54) { // 6
			aKey = '6';
		}
		else if (nKey == 55) { // 7
			aKey = '7';
		}
		else if (nKey == 56) { // 8
			aKey = '8';
		}
		else if (nKey == 57) { // 9
			aKey = '9';
		}
		else if (nKey == 48) { // 0
			aKey = '0';
		}
		else if (nKey == 8) { // BackSpace
			aKey = '/';
		}
		else if (nKey == 13) { // Enter
		aKey = '@';
}
		if ((97 <= nKey && nKey <= 122) || (65 <= nKey && nKey <= 90) || (48 <= nKey && nKey <= 57) || (nKey == 8) || (nKey == 13)) {
			break;
		}
	}

	return aKey;
}

//===============================================
//メニュー
//===============================================
void Menu(Player* pPlayer1, Player* pPlayer2) {
	int nWinPlayer;
	int nKey;
	int nCount;
	int nEnter = 1;
	int nSelect = 1;
	char aText[2][10] = { "  START  ",
						 "EXIT GAME" };
	bool bEndGame = false;
	// ─ │ ┌ ┐ └ ┘ ├ ┤ ┬ ┴ ┼
	do {

		MoveTitle();

		while (1) {

			Title();

			if (nSelect == 1) {
				printf("\x1b[38;5;172m");
			}
			printf("\n\n\n								┌──────────────┐\n");
			printf("								│   %s  │\n", &aText[0][0]);
			printf("								└──────────────┘\x1b[0m\n");
			if (nSelect == 2) {
				printf("\x1b[38;5;172m");
			}
			printf("\n								┌──────────────┐\n");
			printf("								│   %s  │\n", &aText[1][0]);
			printf("								└──────────────┘\x1b[0m\n");

			for (nCount = 0; nCount < nEnter; nCount++) {
				if (_kbhit()) {
					nEnter++;

					_getch();
				}
			}

			rewind(stdin);
			nKey = _getch();

			if (nKey == 119 && nSelect > 1) { // w
				nSelect -= 1;
			}
			else if (nKey == 115 && nSelect < 2) { // s
				nSelect += 1;
			}
			else if (nKey == 13) {
				PlaySound(TEXT("bgm//Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (nSelect == 1) {

					SetName(pPlayer1);

					nWinPlayer = Battle(pPlayer1, pPlayer2);

					EndBattle(pPlayer1, pPlayer2, nWinPlayer);
					break;
				}
				else if (nSelect == 2) {
					bEndGame = true;
					break;
				}
			}
		}
	} while (bEndGame == false);
}

//===============================================
//名前ステータス設定
//===============================================
void SetName(Player* pPlayer) {
	int nCount;
	int nCount2;
	int nCount3;
	int nCount4;
	int nKey;
	int nMenuSelect;
	char aTemp;
	char aName[15] = { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_' };
	bool bNameError;

	for (nCount = 0; nCount < 2; nCount++, pPlayer++) {
		while (1) {
			bNameError = false;

			system("cls");

			printf("\n\n\n					  		   ┌─ プレイヤー%d─────────┐\n", nCount + 1);

			for (nCount3 = 0; nCount3 < 10; nCount3++) {

				aName[nCount3] = '_';
			}

			printf("							   │  ");
			for (nCount2 = 0; nCount2 < 10; nCount2++) {
				printf("%c ", aName[nCount2]);
			}
			printf("│\n							   └──────────────────────┘\n");
			printf("\n							  \x1b[38;5;240m┌─────────┐    ┌─────────┐\n");
			printf("							  │   決定  │    │  再入力 │\n");
			printf("							  └─────────┘    └─────────┘\x1b[0m\n");

			nCount3 = 0;

			while (1) {
				aTemp = InputKey();

				system("cls");

				if (aTemp == '/') { // BackSpace
					PlaySound(TEXT("bgm//keyback.wav"), NULL, SND_FILENAME | SND_ASYNC);
					nCount3 -= 1;
					aName[nCount3] = '_';
					nCount3 -= 1;

					if (nCount3 < 0) {
						nCount3 = -1;
					}
				}
				else if (aTemp == '@') { // Enter
					if (strcmp(&aName[0], "__________") == 0) {
						system("cls");
						PlaySound(TEXT("bgm//No.wav"), NULL, SND_FILENAME | SND_ASYNC);
						nCount3--;
						bNameError = true;
					}
					else {
						PlaySound(TEXT("bgm//Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
						for (nCount4 = 0; nCount4 < (10 - nCount3); nCount4++) {
							aName[(nCount3)+nCount4] = ' ';
						}



						printf("\n\n\n					  		   ┌─ プレイヤー%d─────────┐\n", nCount + 1);

						printf("							   │  ");
						for (nCount2 = 0; nCount2 < 10; nCount2++) {
							printf("%c ", aName[nCount2]);
						}
						printf("│\n							   └──────────────────────┘\n");
						printf("\n							  \x1b[38;5;240m┌─────────┐    ┌─────────┐\n");
						printf("							  │   決定  │    │  再入力 │\n");
						printf("							  └─────────┘    └─────────┘\x1b[0m\n");
						break;
					}
				}
				else {
					if (nCount3 < 10) {
						PlaySound(TEXT("bgm//NameKey.wav"), NULL, SND_FILENAME | SND_ASYNC);
						aName[nCount3] = aTemp;
					}
				}

				printf("\n\n\n					  		   ┌─ プレイヤー%d─────────┐\n", nCount + 1);

				printf("							   │  ");
				for (nCount2 = 0; nCount2 < 10; nCount2++) {
					printf("%c ", aName[nCount2]);
				}
				printf("│\n							   └──────────────────────┘\n");
				printf("\n							  \x1b[38;5;240m┌─────────┐    ┌─────────┐\n");
				printf("							  │   決定  │    │  再入力 │\n");
				printf("							  └─────────┘    └─────────┘\x1b[0m\n");

				if (bNameError == true) {
					printf("                                                               \x1b[38;5;009m入力してください\x1b[0m");
				}

				nCount3++;
				
				if (nCount3 > 10) {
					nCount3 = 10;
				}
			}

			nMenuSelect = 1;

			while (1) {
				system("cls");

				if (nMenuSelect == 1) {
					printf("\n\n\n					  		   ┌─ プレイヤー%d─────────┐\n", nCount + 1);

					printf("							   │  ");
					for (nCount2 = 0; nCount2 < 10; nCount2++) {
						printf("%c ", aName[nCount2]);
					}
					printf("│\n							   └──────────────────────┘\n");
					printf("\n							  \x1b[38;5;172m┌─────────┐\x1b[0m    ┌─────────┐\n");
					printf("							  \x1b[38;5;172m│   決定  │\x1b[0m    │  再入力 │\n");
					printf("							  \x1b[38;5;172m└─────────┘\x1b[0m    └─────────┘\n");
				}
				else if (nMenuSelect == 2) {
					printf("\n\n\n					  		   ┌─ プレイヤー%d─────────┐\n", nCount + 1);

					printf("							   │  ");
					for (nCount2 = 0; nCount2 < 10; nCount2++) {
						printf("%c ", aName[nCount2]);
					}
					printf("│\n							   └──────────────────────┘\n");
					printf("\n							  ┌─────────┐    \x1b[38;5;172m┌─────────┐\x1b[0m\n");
					printf("							  │   決定  │    \x1b[38;5;172m│  再入力 │\x1b[0m\n");
					printf("							  └─────────┘    \x1b[38;5;172m└─────────┘\x1b[0m\n");
				}

				rewind(stdin);
				nKey = _getch();

				if (nKey == 97 && nMenuSelect > 1) {

					nMenuSelect -= 1;
					PlaySound(TEXT("bgm//menumove.wav"), NULL, SND_FILENAME | SND_ASYNC);
				}
				else if (nKey == 100 && nMenuSelect < 2) {
					nMenuSelect += 1;
					PlaySound(TEXT("bgm//menumove.wav"), NULL, SND_FILENAME | SND_ASYNC);
				}
				else if (nKey == 13) {
					break;
				}

			}

			if (nMenuSelect == 1) {
				PlaySound(TEXT("bgm//Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
				break;
			}
			else if (nMenuSelect == 2) {
				PlaySound(TEXT("bgm//EnterBack.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
		}

		aName[nCount3] = '\0';

		strcpy(&pPlayer->aName[0], &aName[0]);

		pPlayer->nHealth = 500;
		pPlayer->nMaxHealth = 500;

		pPlayer->nSkillPoint = 70;

		pPlayer->nAttack = rand() % 16 + 20;   // 20～35

		pPlayer->nDefence = rand() % 11 + 15; // 15～25
		pPlayer->nDefenceSave = pPlayer->nDefence;
		pPlayer->nDefenceUp = 0;
		pPlayer->nDefenceDown = 0;

		pPlayer->nAgility = rand() % 4 + 5; // 5～8
		pPlayer->nAgilitySave = pPlayer->nAgility;
		pPlayer->nAgilityUp = 0;
		pPlayer->nAgilityDown = 0;

		pPlayer->nHitRate = rand() % 8 + 88;  // 88～95
		pPlayer->nHitRateSave = pPlayer->nHitRate;
		pPlayer->nHitRateUp = 0;
		pPlayer->nHitRateDown = 0;

		pPlayer->nCriticalRate = rand() % 9 + 5; // 5～13
		pPlayer->nCriticalRateSave = pPlayer->nCriticalRate;
		pPlayer->nCriticalRateUp = 0;
		pPlayer->nCriticalRateDown = 0;

		pPlayer->bShield = false;

		pPlayer->nPoison = 0;

		pPlayer->bOffenseTurn = false;
		rewind(stdin);
	}
}

//===============================================
//戦闘処理
//===============================================
int Battle(Player* pPlayer1, Player* pPlayer2) {
	int nTurn;   //攻撃ターン
	int nWinPlayer;    // [1:プレイヤー1][2:プレイヤー2]
	int nEnter;
	int nDisaster;
	int nRandomDamage;

	//最初のターンを設定する
	nTurn = 0;

	//戦闘処理
	while (1) {
		nTurn += 1;

		pPlayer1->nSkillPoint += 10;
		pPlayer2->nSkillPoint += 10;

		system("cls");
		BattleInfo(pPlayer1, nTurn);

		PlaySound(TEXT("bgm//SPup.wav"), NULL, SND_FILENAME | SND_ASYNC);
		printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
		printf("\n                                ターン%d\n                         スキルポイントが10回復した\n\n", nTurn);
		printf("└────────────────────────────────────────────────────────────────────────────┘\n");

		do {
			nEnter = _getch();
			rewind(stdin);
		} while (nEnter != 13);

		if (nTurn % 10 == 0) {
			system("cls");
			BattleInfo(pPlayer1, nTurn);

			while (1) {
				nDisaster = rand() % 8 + 1;
				if (nDisaster == 1) {
					PlaySound(TEXT("bgm//alert.wav"), NULL, SND_FILENAME | SND_ASYNC);
					printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
					printf("                             \x1b[38;5;184m*** 災害警報 ***\x1b[0m\n                                  \x1b[38;5;231m-吹雪-\x1b[0m\n                 ターン終了後すべてのプレイヤーの命中率が下がる\n");
					printf("└────────────────────────────────────────────────────────────────────────────┘\n");
					break;
				}
				else if (nDisaster == 2) {
					PlaySound(TEXT("bgm//alert.wav"), NULL, SND_FILENAME | SND_ASYNC);
					printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
					printf("                             \x1b[38;5;184m*** 災害警報 ***\x1b[0m\n                                  \x1b[38;5;123m-津波-\x1b[0m\n                 ターン終了後すべてのプレイヤーの素早さが下がる\n");
					printf("└────────────────────────────────────────────────────────────────────────────┘\n");
					break;
				}
				else if (nDisaster == 3) {
					PlaySound(TEXT("bgm//alert.wav"), NULL, SND_FILENAME | SND_ASYNC);
					printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
					printf("                             \x1b[38;5;184m*** 災害警報 ***\x1b[0m\n                                  \x1b[38;5;243m-隕石-\x1b[0m\n                  ターン終了後すべてのプレイヤーにダメージを与える\n");
					printf("└────────────────────────────────────────────────────────────────────────────┘\n");
					break;
				}
				else if (nDisaster == 4 && nTurn >= 20) {
					PlaySound(TEXT("bgm//alert.wav"), NULL, SND_FILENAME | SND_ASYNC);
					printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
					printf("                             \x1b[38;5;184m*** 害獣襲来警報 ***\x1b[0m\n                                   \x1b[38;5;200m-山上智-\x1b[0m\n          ターン終了後すべてのプレイヤーのバフ効果をデバフ効果に変える\n");
					printf("└────────────────────────────────────────────────────────────────────────────┘\n");
					break;
				}
				else if (nDisaster == 5) {
					PlaySound(TEXT("bgm//alert.wav"), NULL, SND_FILENAME | SND_ASYNC);
					printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
					printf("                             \x1b[38;5;184m*** 害獣襲来警報 ***\x1b[0m\n                                    \x1b[38;5;040m-魔女-\x1b[0m\n                  ターン終了後すべてのプレイヤーに毒を与える\n");
					printf("└────────────────────────────────────────────────────────────────────────────┘\n");
					break;
				}
				else if (nDisaster == 6 && nTurn >= 20) {
					PlaySound(TEXT("bgm//alert.wav"), NULL, SND_FILENAME | SND_ASYNC);
					printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
					printf("                             \x1b[38;5;184m*** 害獣襲来警報 ***\x1b[0m\n                                    \x1b[38;5;097m-悪魔-\x1b[0m\n                 ターン終了後すべてのプレイヤーの体力を半分にする\n");
					printf("└────────────────────────────────────────────────────────────────────────────┘\n");
					break;
				}
				else if (nDisaster == 7) {
					PlaySound(TEXT("bgm//alert.wav"), NULL, SND_FILENAME | SND_ASYNC);
					printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
					printf("                             \x1b[38;5;184m*** 害獣襲来警報 ***\x1b[0m\n                                   \x1b[38;5;200m-山上清-\x1b[0m\n                  ターン終了後すべてのプレイヤーのSPが消える\n");
					printf("└────────────────────────────────────────────────────────────────────────────┘\n");
					break;
				}
				else if (nDisaster == 8) {
					PlaySound(TEXT("bgm//alert.wav"), NULL, SND_FILENAME | SND_ASYNC);
					printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
					printf("                             \x1b[38;5;184m*** 害獣襲来警報 ***\x1b[0m\n                                  \x1b[38;5;200m-山上里美-\x1b[0m\n                  ターン終了後すべてのプレイヤーの防御力が下がる\n");
					printf("└────────────────────────────────────────────────────────────────────────────┘\n");
					break;
				}
			}

			do {
				nEnter = _getch();
				rewind(stdin);
			} while (nEnter != 13);
			PlaySound(nullptr, nullptr, 0);
		}

		if (pPlayer1->nAgility >= pPlayer2->nAgility) {
			BattleDisplay(pPlayer1, pPlayer2, pPlayer1, nTurn);
			if (pPlayer1->nHealth == 0 && pPlayer2->nHealth == 0) {
				//引きわけ
				nWinPlayer = 0;
				break;
			}
			else if (pPlayer1->nHealth == 0) {
				//プレイヤー2の勝利
				nWinPlayer = 2;
				break;
			}
			else if (pPlayer2->nHealth == 0) {
				//プレイヤー1の勝利
				nWinPlayer = 1;
				break;
			}
			BattleDisplay(pPlayer2, pPlayer1, pPlayer1, nTurn);
		}
		else if (pPlayer1->nAgility < pPlayer2->nAgility) {
			BattleDisplay(pPlayer2, pPlayer1, pPlayer1, nTurn);
			if (pPlayer1->nHealth == 0 && pPlayer2->nHealth == 0) {
				//引きわけ
				nWinPlayer = 0;
				break;
			}
			else if (pPlayer1->nHealth == 0) {
				//プレイヤー2の勝利
				nWinPlayer = 2;
				break;
			}
			else if (pPlayer2->nHealth == 0) {
				//プレイヤー1の勝利
				nWinPlayer = 1;
				break;
			}
			BattleDisplay(pPlayer1, pPlayer2, pPlayer1, nTurn);
		}

		if (pPlayer1->nHealth == 0 && pPlayer2->nHealth == 0) {
			//引きわけ
			nWinPlayer = 0;
			break;
		}
		else if (pPlayer1->nHealth == 0) {
			//プレイヤー2の勝利
			nWinPlayer = 2;
			break;
		}
		else if (pPlayer2->nHealth == 0) {
			//プレイヤー1の勝利
			nWinPlayer = 1;
			break;
		}

		StatusTurn(pPlayer1, pPlayer2, nTurn);

		if (pPlayer1->nHealth == 0 && pPlayer2->nHealth == 0) {
			//引きわけ
			nWinPlayer = 0;
			break;
		}
		else if (pPlayer1->nHealth == 0) {
			//プレイヤー2の勝利
			nWinPlayer = 2;
			break;
		}
		else if (pPlayer2->nHealth == 0) {
			//プレイヤー1の勝利
			nWinPlayer = 1;
			break;
		}

		if (nTurn % 10 == 0) {
			system("cls");
			BattleInfo(pPlayer1, nTurn);

			if (nDisaster == 1) {
				PlaySound(TEXT("bgm//Blizzard.wav"), NULL, SND_FILENAME | SND_ASYNC);
				printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
				printf("                             \x1b[38;5;160m*** 災害通知 ***\x1b[0m\n                                  \x1b[38;5;231m-吹雪-\x1b[0m\n                      すべてのプレイヤーの命中率が下がった\n");
				printf("└────────────────────────────────────────────────────────────────────────────┘\n");
				pPlayer1->nHitRateDown += 3;
				pPlayer2->nHitRateDown += 3;
			}
			else if (nDisaster == 2) {
				PlaySound(TEXT("bgm//Tsunami.wav"), NULL, SND_FILENAME | SND_ASYNC);
				printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
				printf("                              \x1b[38;5;160m*** 災害通知 ***\x1b[0m\n                                   \x1b[38;5;123m-津波-\x1b[0m\n                      すべてのプレイヤーの素早さが下がった\n");
				printf("└────────────────────────────────────────────────────────────────────────────┘\n");
				pPlayer1->nAgilityDown += 3;
				pPlayer2->nAgilityDown += 3;
			}
			else if (nDisaster == 3) {
				PlaySound(TEXT("bgm//Meteorite.wav"), NULL, SND_FILENAME | SND_ASYNC);
				nRandomDamage = rand() % 31 + 50; // 50～80
				printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
				printf("                             \x1b[38;5;160m*** 災害通知 ***\x1b[0m\n                                  \x1b[38;5;243m-隕石-\x1b[0m\n                        すべてのプレイヤーに%dのダメージ\n", nRandomDamage);
				printf("└────────────────────────────────────────────────────────────────────────────┘\n");
				pPlayer1->nHealth -= nRandomDamage;
				pPlayer2->nHealth -= nRandomDamage;
				HpSpControl(pPlayer1, pPlayer2);
			}
			else if (nDisaster == 4 && nTurn >= 20) {
				PlaySound(TEXT("bgm//Satoshi.wav"), NULL, SND_FILENAME | SND_ASYNC);
				printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
				printf("                             \x1b[38;5;160m*** 害獣襲来通知 ***\x1b[0m\n                                   \x1b[38;5;200m-山上智-\x1b[0m\n               すべてのプレイヤーのバフ効果がデバフ効果に変わった\n");
				printf("└────────────────────────────────────────────────────────────────────────────┘\n");

				pPlayer1->nDefenceDown = pPlayer1->nDefenceUp + 10;
				pPlayer1->nAgilityDown = pPlayer1->nAgilityUp + 10;
				pPlayer1->nHitRateDown = pPlayer1->nHitRateUp + 10;
				pPlayer1->nCriticalRateDown = pPlayer1->nCriticalRateUp + 10;

				pPlayer1->nDefenceUp = 0;
				pPlayer1->nAgilityUp = 0;
				pPlayer1->nHitRateUp = 0;
				pPlayer1->nCriticalRateUp = 0;

				pPlayer2->nDefenceDown = pPlayer2->nDefenceUp + 10;
				pPlayer2->nAgilityDown = pPlayer2->nAgilityUp + 10;
				pPlayer2->nHitRateDown = pPlayer2->nHitRateUp + 10;
				pPlayer2->nCriticalRateDown = pPlayer2->nCriticalRateUp + 10;

				pPlayer2->nDefenceUp = 0;
				pPlayer2->nAgilityUp = 0;
				pPlayer2->nHitRateUp = 0;
				pPlayer2->nCriticalRateUp = 0;
			}
			else if (nDisaster == 5) {
				PlaySound(TEXT("bgm//Witch.wav"), NULL, SND_FILENAME | SND_ASYNC);
				printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
				printf("                             \x1b[38;5;160m*** 害獣襲来通知 ***\x1b[0m\n                                    \x1b[38;5;040m-魔女-\x1b[0m\n                         すべてのプレイヤーが毒を受けた\n");
				printf("└────────────────────────────────────────────────────────────────────────────┘\n");
				pPlayer1->nPoison = 99;
				pPlayer2->nPoison = 99;
			}
			else if (nDisaster == 6 && nTurn >= 20) {
				PlaySound(TEXT("bgm//Devil.wav"), NULL, SND_FILENAME | SND_ASYNC);
				printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
				printf("                             \x1b[38;5;160m*** 害獣襲来通知 ***\x1b[0m\n                                    \x1b[38;5;097m-悪魔-\x1b[0m\n                  すべてのプレイヤーの体力が半分になった\n");
				printf("└────────────────────────────────────────────────────────────────────────────┘\n");
				pPlayer1->nHealth -= pPlayer1->nHealth / 2;
				pPlayer2->nHealth -= pPlayer2->nHealth / 2;
			}
			else if (nDisaster == 7) {
				PlaySound(TEXT("bgm//Kiyoshi.wav"), NULL, SND_FILENAME | SND_ASYNC);
				printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
				printf("                             \x1b[38;5;160m*** 害獣襲来通知 ***\x1b[0m\n                                   \x1b[38;5;200m-山上清-\x1b[0m\n                         すべてのプレイヤーのSPが消えた\n");
				printf("└────────────────────────────────────────────────────────────────────────────┘\n");
				pPlayer1->nSkillPoint = 0;
				pPlayer2->nSkillPoint = 0;
			}
			else if (nDisaster == 8) {
				PlaySound(TEXT("bgm//Satomi.wav"), NULL, SND_FILENAME | SND_ASYNC);
				printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
				printf("                             \x1b[38;5;160m*** 害獣襲来通知 ***\x1b[0m\n                                  \x1b[38;5;200m-山上里美-\x1b[0m\n                     すべてのプレイヤーの防御力が下がった\n");
				printf("└────────────────────────────────────────────────────────────────────────────┘\n");
				pPlayer1->nDefenceDown = 5;
				pPlayer2->nDefenceDown = 5;
			}


			do {
				nEnter = _getch();
				rewind(stdin);
			} while (nEnter != 13);
			PlaySound(nullptr, nullptr, 0);


			if (pPlayer1->nHealth == 0 && pPlayer2->nHealth == 0) {
				//引きわけ
				nWinPlayer = 0;
				break;
			}
			else if (pPlayer1->nHealth == 0) {
				//プレイヤー2の勝利
				nWinPlayer = 2;
				break;
			}
			else if (pPlayer2->nHealth == 0) {
				//プレイヤー1の勝利
				nWinPlayer = 1;
				break;
			}

		}
	}

	system("cls");

	BattleInfo(pPlayer1, nTurn);

	return nWinPlayer;
}

//===============================================
//ステータス表示
//===============================================
void BattleInfo(Player *pPlayer1, int nTurn) {
	int nCount;
	int nSpace = 146;
	int nSpace2 = 2;
	int nTemp = 1;
	int nLength;

	printf("┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\n");

	printf("│  %dターン目", nTurn);
	if (0 <= nTurn && nTurn < 10) {
		for (nCount = 0; nCount < 135; nCount++) {
			printf(" ");
		}
	}
	else if (10 <= nTurn && nTurn < 100) {
		for (nCount = 0; nCount < 134; nCount++) {
			printf(" ");
		}
	}
	printf("│\n");
	printf("├──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤\n");

	printf("│");
	if (pPlayer1->bOffenseTurn == true) {
		printf("\x1b[38;5;172m");
	}
	printf(" ┌─────────────────────┐\x1b[0m                                                                                                                          │\n");
	printf("│");
	if (pPlayer1->bOffenseTurn == true) {
		printf("\x1b[38;5;172m");
	}
	printf(" │\x1b[0m   ");
	if (pPlayer1->bShield == true) {
		printf("\x1b[48;5;140m");
	}
	printf("%s\x1b[0m", &pPlayer1->aName[0]);
	
	nLength = (int)strlen(&pPlayer1->aName[0]);

	for (nCount = 0; nCount < (18 - nLength); nCount++) {
		printf(" ");
	}
	if (pPlayer1->bOffenseTurn == true) {
		printf("\x1b[38;5;172m");
	}
	printf("│\x1b[0m                                                                                                                          │\n");
	printf("│ ");
	if (pPlayer1->bOffenseTurn == true) {
		printf("\x1b[38;5;172m");
	}
	printf("│\x1b[0m  ");
	if (pPlayer1->nPoison > 0) {
		printf("\x1b[48;5;040m\x1b[38;5;000m");
	}
	printf("HP %d/%d\x1b[0m", pPlayer1->nHealth, pPlayer1->nMaxHealth);
	if (10 <= pPlayer1->nHealth && pPlayer1->nHealth < 100) {
		nSpace2 += 1;
	}
	else if (0 <= pPlayer1->nHealth && pPlayer1->nHealth < 10) {
		nSpace2 += 2;
	}

	printf(" SP %d", pPlayer1->nSkillPoint);
	if (10 <= pPlayer1->nSkillPoint && pPlayer1->nSkillPoint < 100) {
		nSpace2 += 1;
	}
	else if (0 <= pPlayer1->nSkillPoint && pPlayer1->nSkillPoint < 10) {
		nSpace2 += 2;
	}

	for (nCount = 0; nCount < nSpace2; nCount++) {
		printf(" ");
	}
	if (pPlayer1->bOffenseTurn == true) {
		printf("\x1b[38;5;172m");
	}
	printf("│\x1b[0m                                                                                                                          │\n");
	printf("│ ");
	if (pPlayer1->bOffenseTurn == true) {
		printf("\x1b[38;5;172m");
	}
	printf("└─────────────────────┘\x1b[0m                                                                                                                          │\n");
	printf("│");
	if (pPlayer1->nDefenceUp > 0) {
		printf("[\x1b[48;5;006m防御アップ:%d\x1b[0m] ", pPlayer1->nDefenceUp);
		if (pPlayer1->nDefenceUp >= 10) {
			nTemp = 2;
		}
		nSpace -= 14 + nTemp;
	}
	if (pPlayer1->nDefenceDown > 0) {
		printf("[\x1b[48;5;052m防御ダウン:%d\x1b[0m] ", pPlayer1->nDefenceDown);
		if (pPlayer1->nDefenceDown >= 10) {
			nTemp = 2;
		}
		nSpace -= 14 + nTemp;
	}
	if (pPlayer1->nAgilityUp > 0) {
		printf("[\x1b[48;5;006m素早さアップ:%d\x1b[0m] ", pPlayer1->nAgilityUp);
		if (pPlayer1->nAgilityUp >= 10) {
			nTemp = 2;
		}
		nSpace -= 16 + nTemp;
	}
	if (pPlayer1->nAgilityDown > 0) {
		printf("[\x1b[48;5;052m素早さダウン:%d\x1b[0m] ", pPlayer1->nAgilityDown);
		if (pPlayer1->nAgilityDown >= 10) {
			nTemp = 2;
		}
		nSpace -= 16 + nTemp;
	}
	if (pPlayer1->nHitRateUp > 0) {
		printf("[\x1b[48;5;006m命中率アップ:%d\x1b[0m] ", pPlayer1->nHitRateUp);
		if (pPlayer1->nHitRateUp >= 10) {
			nTemp = 2;
		}
		nSpace -= 16 + nTemp;
	}
	if (pPlayer1->nHitRateDown > 0) {
		printf("[\x1b[48;5;052m命中率ダウン:%d\x1b[0m] ", pPlayer1->nHitRateDown);
		if (pPlayer1->nHitRateDown >= 10) {
			nTemp = 2;
		}
		nSpace -= 16 + nTemp;
	}
	if (pPlayer1->nCriticalRateUp > 0) {
		printf("[\x1b[48;5;006mクリティカル率アップ:%d\x1b[0m] ", pPlayer1->nCriticalRateUp);
		if (pPlayer1->nCriticalRateUp >= 10) {
			nTemp = 2;
		}
		nSpace -= 24 + nTemp;
	}
	if (pPlayer1->nCriticalRateDown > 0) {
		printf("[\x1b[48;5;052mクリティカル率ダウン:%d\x1b[0m] ", pPlayer1->nCriticalRateDown);
		if (pPlayer1->nCriticalRateDown >= 10) {
			nTemp = 2;
		}
		nSpace -= 24 + nTemp;
	}
	if (pPlayer1->nPoison > 0) {
		printf("[\x1b[38;5;040m毒:%d\x1b[0m] ", pPlayer1->nPoison);
		if (pPlayer1->nPoison >= 10) {
			nTemp = 2;
		}
		nSpace -= 6 + nTemp;
	}
	if (pPlayer1->bShield == true) {
		printf("[\x1b[38;5;140mシールド\x1b[0m] ");
		nSpace -= 10 + nTemp;
	}
	for (nCount = 0; nCount < nSpace; nCount++) {
		printf(" ");
	}
	printf("│\n");
	printf("├──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤\n");
	printf("│                                                                                                                          ");
	if ((pPlayer1 + 1)->bOffenseTurn == true) {
		printf("\x1b[38;5;172m");
	}
	printf("┌─────────────────────┐\x1b[0m │\n");
	printf("│                                                                                                                          ");
	if ((pPlayer1 + 1)->bOffenseTurn == true) {
		printf("\x1b[38;5;172m");
	}
	printf("│\x1b[0m   ");
	if ((pPlayer1 + 1)->bShield == true) {
		printf("\x1b[48;5;140m");
	}
	printf("%s\x1b[0m", &(pPlayer1 + 1)->aName[0]);

	nLength = (int)strlen(&(pPlayer1 + 1)->aName[0]);

	for (nCount = 0; nCount < (18 - nLength); nCount++) {
		printf(" ");
	}
	if ((pPlayer1 + 1)->bOffenseTurn == true) {
		printf("\x1b[38;5;172m");
	}
	printf("│\x1b[0m");
	printf(" │\n│                                                                                                                          ");
	if ((pPlayer1 + 1)->bOffenseTurn == true) {
		printf("\x1b[38;5;172m");
	}
	printf("│\x1b[0m  ");

	nSpace2 = 2;

	if ((pPlayer1 + 1)->nPoison > 0) {
		printf("\x1b[48;5;040m\x1b[38;5;000m");
	}
	printf("HP %d/%d\x1b[0m", (pPlayer1 + 1)->nHealth, (pPlayer1 + 1)->nMaxHealth);
	if (10 <= (pPlayer1 + 1)->nHealth && (pPlayer1 + 1)->nHealth < 100) {
		nSpace2 += 1;
	}
	else if (0 <= (pPlayer1 + 1)->nHealth && (pPlayer1 + 1)->nHealth < 10) {
		nSpace2 += 2;
	}

	printf(" SP %d", (pPlayer1 + 1)->nSkillPoint);
	if (10 <= (pPlayer1 + 1)->nSkillPoint && (pPlayer1 + 1)->nSkillPoint < 100) {
		nSpace2 += 1;
	}
	else if (0 <= (pPlayer1 + 1)->nSkillPoint && (pPlayer1 + 1)->nSkillPoint < 10) {
		nSpace2 += 2;
	}

	for (nCount = 0; nCount < nSpace2; nCount++) {
		printf(" ");
	}
	if ((pPlayer1 + 1)->bOffenseTurn == true) {
		printf("\x1b[38;5;172m");
	}
	printf("│\x1b[0m");
	printf(" │\n");


	printf("│                                                                                                                          ");
	if ((pPlayer1 + 1)->bOffenseTurn == true) {
		printf("\x1b[38;5;172m");
	}
	printf("└─────────────────────┘\x1b[0m │\n");
	printf("│");

	nSpace = 146;

	if ((pPlayer1 + 1)->nDefenceUp > 0) {
		if ((pPlayer1 + 1)->nDefenceUp >= 10) {
			nTemp = 2;
		}
		nSpace -= 14 + nTemp;
	}
	if ((pPlayer1 + 1)->nDefenceDown > 0) {
		if ((pPlayer1 + 1)->nDefenceDown >= 10) {
			nTemp = 2;
		}
		nSpace -= 14 + nTemp;
	}
	if ((pPlayer1 + 1)->nAgilityUp > 0) {
		if ((pPlayer1 + 1)->nAgilityUp >= 10) {
			nTemp = 2;
		}
		nSpace -= 16 + nTemp;
	}
	if ((pPlayer1 + 1)->nAgilityDown > 0) {
		if ((pPlayer1 + 1)->nAgilityDown >= 10) {
			nTemp = 2;
		}
		nSpace -= 16 + nTemp;
	}
	if ((pPlayer1 + 1)->nHitRateUp > 0) {
		if ((pPlayer1 + 1)->nHitRateUp >= 10) {
			nTemp = 2;
		}
		nSpace -= 16 + nTemp;
	}
	if ((pPlayer1 + 1)->nHitRateDown > 0) {
		if ((pPlayer1 + 1)->nHitRateDown >= 10) {
			nTemp = 2;
		}
		nSpace -= 16 + nTemp;
	}
	if ((pPlayer1 + 1)->nCriticalRateUp > 0) {
		if ((pPlayer1 + 1)->nCriticalRateUp >= 10) {
			nTemp = 2;
		}
		nSpace -= 24 + nTemp;
	}
	if ((pPlayer1 + 1)->nCriticalRateDown > 0) {
		if ((pPlayer1 + 1)->nCriticalRateDown >= 10) {
			nTemp = 2;
		}
		nSpace -= 24 + nTemp;
	}
	if ((pPlayer1 + 1)->nPoison > 0) {
		if ((pPlayer1 + 1)->nPoison>= 10) {
			nTemp = 2;
		}
		nSpace -= 6 + nTemp;
	}
	if ((pPlayer1 + 1)->bShield == true) {
		nSpace -= 10 + nTemp;
	}

	for (nCount = 0; nCount < nSpace; nCount++) {
		printf(" ");
	}

	if ((pPlayer1 + 1)->nDefenceUp > 0) {
		printf(" [\x1b[48;5;006m防御アップ:%d\x1b[0m]", (pPlayer1 + 1)->nDefenceUp);
	}
	if ((pPlayer1 + 1)->nDefenceDown > 0) {
		printf(" [\x1b[48;5;052m防御ダウン:%d\x1b[0m]", (pPlayer1 + 1)->nDefenceDown);
	}
	if ((pPlayer1 + 1)->nAgilityUp > 0) {
		printf(" [\x1b[48;5;006m素早さアップ:%d\x1b[0m]", (pPlayer1 + 1)->nAgilityUp);
	}
	if ((pPlayer1 + 1)->nAgilityDown > 0) {
		printf(" [\x1b[48;5;052m素早さダウン:%d\x1b[0m]", (pPlayer1 + 1)->nAgilityDown);
	}
	if ((pPlayer1 + 1)->nHitRateUp > 0) {
		printf(" [\x1b[48;5;006m命中率アップ:%d\x1b[0m]", (pPlayer1 + 1)->nHitRateUp);
	}
	if ((pPlayer1 + 1)->nHitRateDown > 0) {
		printf(" [\x1b[48;5;052m命中率ダウン:%d\x1b[0m]", (pPlayer1 + 1)->nHitRateDown);
	}
	if ((pPlayer1 + 1)->nCriticalRateUp > 0) {
		printf(" [\x1b[48;5;006mクリティカル率アップ:%d\x1b[0m]", (pPlayer1 + 1)->nCriticalRateUp);
	}
	if ((pPlayer1 + 1)->nCriticalRateDown > 0) {
		printf(" [\x1b[48;5;052mクリティカル率ダウン:%d\x1b[0m]", (pPlayer1 + 1)->nCriticalRateDown);
	}
	if ((pPlayer1 + 1)->nPoison > 0) {
		printf(" [\x1b[38;5;040m毒:%d\x1b[0m]", (pPlayer1 + 1)->nPoison);
	}
	if ((pPlayer1 + 1)->bShield == true) {
		printf(" [\x1b[38;5;140mシールド\x1b[0m]");
	}

	printf("│\n");
	printf("└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n");
}

//===============================================
//戦闘画面
//===============================================
void BattleDisplay(Player* pOffense, Player* pDefense, Player *pPlayer1, int nTurn) {
	system("cls");

	int nCount;
	int nRand;
	char aCommand[3][512];
	int nCommandDiff[3];
	int nSelect = 1;
	int nSkillPoint[3];
	int nEnter;
	int nKey;
	bool bSkillOn[12] = {false, false, false, false, false, false, false, false, false, false, false, false};


	pOffense->bOffenseTurn = true;

	// 小:30～40 中:41～55 大:56～75 超大:100 

	//コマンド振り分け
	for (nCount = 0; nCount < 3; nCount++) {
		while (1) {
			nRand = rand() % 120 + 1;
			if (1 <= nRand && nRand <= 10 && bSkillOn[0] == false) {
				strcpy(&aCommand[nCount][0], "[\x1b[38;5;230mブレードストーム\x1b[0m] +スキルコスト:15+ -威力:小～中-\n   ・相手に防御\x1b[38;5;230m貫通ダメージ\x1b[0mを与える");
				nCommandDiff[nCount] = 1;
				nSkillPoint[nCount] = SKILLPOINT1;
				bSkillOn[0] = true;
				break;
			}

			else if (11 <= nRand && nRand <= 20 && bSkillOn[1] == false) {
				strcpy(&aCommand[nCount][0], "[\x1b[38;5;128mデバウアー\x1b[0m] +スキルコスト:25+ -威力:中-\n   ・相手に\x1b[38;5;128mダメージを与え回復\x1b[0mする");
				nCommandDiff[nCount] = 2;
				nSkillPoint[nCount] = SKILLPOINT2;
				bSkillOn[1] = true;
				break;
			}

			else if (21 <= nRand && nRand <= 30 && bSkillOn[2] == false) {
				strcpy(&aCommand[nCount][0], "[\x1b[38;5;040mポイズンクラウド\x1b[0m] +スキルポイント:15+ =ターン:3=\n   ・相手に\x1b[38;5;040m毒を付与\x1b[0mする (ターン終了時にダメージを受ける)");
				nCommandDiff[nCount] = 3;
				nSkillPoint[nCount] = SKILLPOINT3;
				bSkillOn[2] = true;
				break;
			}

			else if (31 <= nRand && nRand <= 40 && bSkillOn[3] == false) {
				strcpy(&aCommand[nCount][0], "[\x1b[38;5;178mツール・ド・フォース\x1b[0m] +スキルコスト:25+ -威力:中～大- =ターン:2=\n   ・相手に\x1b[38;5;178mダメージを与え,素早さを下げる\x1b[0m");
				nCommandDiff[nCount] = 4;
				nSkillPoint[nCount] = SKILLPOINT4;
				bSkillOn[3] = true;
				break;
			}

			else if (41 <= nRand && nRand <= 50 && bSkillOn[4] == false) {
				strcpy(&aCommand[nCount][0], "[\x1b[38;5;196mアーマースワップ\x1b[0m] +スキルコスト:13+ =ターン:2=\n   ・相手の\x1b[38;5;196m防御力を下げ\x1b[0m自分の\x1b[38;5;196m防御力を上げる\x1b[0m");
				nCommandDiff[nCount] = 5;
				nSkillPoint[nCount] = SKILLPOINT5;
				bSkillOn[4] = true;
				break;
			}

			else if (51 <= nRand && nRand <= 60 && bSkillOn[5] == false) {
				strcpy(&aCommand[nCount][0], "[\x1b[38;5;033mグラヴィネット\x1b[0m] +スキルコスト:15+ =ターン:4=\n   ・相手の\x1b[38;5;033m命中率と素早さを下げる\x1b[0m");
				nCommandDiff[nCount] = 6;
				nSkillPoint[nCount] = SKILLPOINT6;
				bSkillOn[5] = true;
				break;
			}

			else if (61 <= nRand && nRand <= 70 && bSkillOn[6] == false) {
				strcpy(&aCommand[nCount][0], "[\x1b[38;5;148mギャンブル\x1b[0m] +スキルコスト:15+ -威力:超大-\n   ・\x1b[38;5;148mダメージが高いが当たるかはわからない\x1b[0m");
				nCommandDiff[nCount] = 7;
				nSkillPoint[nCount] = SKILLPOINT7;
				bSkillOn[6] = true;
				break;
			}

			else if (71 <= nRand && nRand <= 80 && bSkillOn[7] == false) {
				strcpy(&aCommand[nCount][0], "[\x1b[38;5;117mヒーリングオーブ\x1b[0m] +スキルコスト:20+\n   ・自分の\x1b[38;5;117m体力とスキルポイントを回復\x1b[0mさせる");
				nCommandDiff[nCount] = 8;
				nSkillPoint[nCount] = SKILLPOINT8;
				bSkillOn[7] = true;
				break;
			}

			else if (81 <= nRand && nRand <= 90 && bSkillOn[8] == false) {
				strcpy(&aCommand[nCount][0], "[\x1b[38;5;014mハイギア\x1b[0m] +スキルコスト:13+ =ターン:4=\n   ・自分の\x1b[38;5;014m素早さが上がる\x1b[0m");
				nCommandDiff[nCount] = 9;
				nSkillPoint[nCount] = SKILLPOINT9;
				bSkillOn[8] = true;
				break;
			}

			else if (91 <= nRand && nRand <= 100 && bSkillOn[9] == false) {
				strcpy(&aCommand[nCount][0], "[\x1b[38;5;140mダブルタップ\x1b[0m] +スキルコスト:30+\n   ・自分に\x1b[38;5;140mシールドを付与\x1b[0mする (\x1b[38;5;140m相手のすべての攻撃を無効化\x1b[0mする) **\x1b[31m重複不可\x1b[0m**");
				nCommandDiff[nCount] = 10;
				nSkillPoint[nCount] = SKILLPOINT10;
				bSkillOn[9] = true;
				break;
			}
			else if (101 <= nRand && nRand <= 110 && bSkillOn[10] == false) {
				strcpy(&aCommand[nCount][0], "[\x1b[38;5;213mハートの貝殻\x1b[0m] +スキルコスト:20+\n   ・自分についている\x1b[38;5;213mデバフ効果をすべて回復\x1b[0mさせる");
				nCommandDiff[nCount] = 11;
				nSkillPoint[nCount] = SKILLPOINT11;
				bSkillOn[10] = true;
				break;
			}
			else if (111 <= nRand && nRand <= 120 && bSkillOn[11] == false) {
				strcpy(&aCommand[nCount][0], "[\x1b[38;5;047mドキドキ涙\x1b[0m] +スキルコスト:10+\n   ・自分の\x1b[38;5;047m体力が回復する, もしくはダメージを受ける\x1b[0m");
				nCommandDiff[nCount] = 12;
				nSkillPoint[nCount] = SKILLPOINT12;
				bSkillOn[11] = true;
				break;
			}
		}
	}

	//戦闘画面
	system("cls");
	BattleInfo(pPlayer1, nTurn);
	PlaySound(TEXT("bgm//OffenseTurn.wav"), NULL, SND_FILENAME | SND_ASYNC);
	printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
	printf("\n                                %sのターン\n                         \n\n", &pOffense->aName[0]);
	printf("└────────────────────────────────────────────────────────────────────────────┘\n");

	do {
		nEnter = _getch();
		rewind(stdin);
	} while (nEnter != 13);
	
	while (1) {
		system("cls");

		BattleInfo(pPlayer1, nTurn);

		if (nSelect == 1) {
			printf("\x1b[38;5;172m");
		}
		printf("┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\x1b[0m\n");
		printf("  %s\n", &aCommand[0][0]);
		if (nSelect == 1) {
			printf("\x1b[38;5;172m");
		}
		printf("└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\x1b[0m\n");
		if (nSelect == 2) {
			printf("\x1b[38;5;172m");
		}
		printf("┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\x1b[0m\n");
		printf("  %s\n", &aCommand[1][0]);
		if (nSelect == 2) {
			printf("\x1b[38;5;172m");
		}
		printf("└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\x1b[0m\n");
		if (nSelect == 3) {
			printf("\x1b[38;5;172m");
		}
		printf("┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\x1b[0m\n");
		printf("  %s\n", &aCommand[2][0]);
		if (nSelect == 3) {
			printf("\x1b[38;5;172m");
		}
		printf("└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\x1b[0m\n");
		if (nSelect == 4) {
			printf("\x1b[38;5;172m");
		}
		printf("┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\x1b[0m\n");
		printf("  [\x1b[38;5;225m休憩\x1b[0m]\n   ・自分の\x1b[38;5;225mスキルポイントを回復\x1b[0mさせる\n");
		if (nSelect == 4) {
			printf("\x1b[38;5;172m");
		}
		printf("└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\x1b[0m\n");

		nKey = _getch();
		if (nKey == 119 && nSelect > 1) { // w
			nSelect -= 1;
			PlaySound(TEXT("bgm//menumove.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		else if (nKey == 115 && nSelect < 4) { // s
			nSelect += 1;
			PlaySound(TEXT("bgm//menumove.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		else if (nKey == 13) { // Enter
			if (nSelect == 1) { // 1
				if (pOffense->nSkillPoint >= nSkillPoint[0]) {
					Command(pOffense, pDefense, pPlayer1, &nCommandDiff[0], nTurn);
					break;
				}
				else {
					PlaySound(TEXT("bgm//SPlow.wav"), NULL, SND_FILENAME | SND_ASYNC);
					system("cls");

					BattleInfo(pPlayer1, nTurn);

					printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
					printf("\n  \x1b[38;5;001mスキルポイントが足りません\x1b[0m\n\n");
					printf("└────────────────────────────────────────────────────────────────────────────┘\n");

					do {
						nEnter = _getch();
						rewind(stdin);
					} while (nEnter != 13);
				}
			}
			else if (nSelect == 2) { // 2
				if (pOffense->nSkillPoint >= nSkillPoint[1]) {
					Command(pOffense, pDefense, pPlayer1, &nCommandDiff[1], nTurn);
					break;
				}
				else {
					PlaySound(TEXT("bgm//SPlow.wav"), NULL, SND_FILENAME | SND_ASYNC);
					system("cls");

					BattleInfo(pPlayer1, nTurn);

					printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
					printf("\n  \x1b[38;5;001mスキルポイントが足りません\x1b[0m\n\n");
					printf("└────────────────────────────────────────────────────────────────────────────┘\n");

					do {
						nEnter = _getch();
						rewind(stdin);
					} while (nEnter != 13);
				}
			}
			else if (nSelect == 3) { // 3
				if (pOffense->nSkillPoint >= nSkillPoint[2]) {
					Command(pOffense, pDefense, pPlayer1, &nCommandDiff[2], nTurn);
					break;
				}
				else {
					PlaySound(TEXT("bgm//SPlow.wav"), NULL, SND_FILENAME | SND_ASYNC);
					system("cls");

					BattleInfo(pPlayer1, nTurn);

					printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
					printf("\n  \x1b[38;5;001mスキルポイントが足りません\x1b[0m\n\n");
					printf("└────────────────────────────────────────────────────────────────────────────┘\n");

					do {
						nEnter = _getch();
						rewind(stdin);
					} while (nEnter != 13);
				}
			}
			else if (nSelect == 4) { // 4
				PlaySound(TEXT("bgm//break.wav"), NULL, SND_FILENAME | SND_ASYNC);
				system("cls");

				pOffense->nSkillPoint += 15;

				BattleInfo(pPlayer1, nTurn);

				printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
				printf("\n  [%s]\n  [\x1b[38;5;225m休憩\x1b[0m]\n", &pOffense->aName[0]);
				printf("  スキルポイントが15回復した\n\n");
				printf("└────────────────────────────────────────────────────────────────────────────┘\n");

				do {
					nEnter = _getch();
					rewind(stdin);
				} while (nEnter != 13);
				break;
			}
		}
	}
	pOffense->bOffenseTurn = false;
}

//===============================================
//コマンド処理
//===============================================
void Command(Player* pOffense, Player* pDefense, Player *pPlayer1, int* pCommand, int nTurn) {
	bool bHit = true;
	int nRand;
	int nHitRate;
	int nTemp, nTemp2;
	int nCriticalRate = 1;
	int nEnter;

	system("cls");

	StatusControl(pPlayer1, (pPlayer1 +1));

	//命中率計算
	nHitRate = pOffense->nHitRate - pDefense->nAgility;

	nRand = rand() % 100 + 1;
	if (1 <= nRand && nRand <= nHitRate) {
		bHit = true;
	}
	else if (nHitRate < nRand && nRand <= 100) {
		bHit = false;
	}

	//クリティカル率計算
	nRand = rand() % 100 + 1;
	if (1 <= nRand && nRand <= pOffense->nCriticalRate) {
		nCriticalRate = 2;
	}

	BattleInfo(pPlayer1, nTurn);
	printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
	printf("   [%sの行動]\n", &pOffense->aName[0]);

	if (*pCommand == 1) {
		printf("  [\x1b[38;5;230mブレードストーム\x1b[0m]\n");

		if (bHit == true) {
			if (pDefense->bShield == true) {
				PlaySound(TEXT("bgm//ShieldBreak.wav"), NULL, SND_FILENAME | SND_ASYNC);
				printf("  攻撃を防がれた\n\n");
				pDefense->bShield = false;
			}
			else if (pDefense->bShield == false) {
				PlaySound(TEXT("bgm//BLADESTORM.wav"), NULL, SND_FILENAME | SND_ASYNC);
				nRand = rand() % 26 + 30;

				nTemp = (pOffense->nAttack + nRand) * nCriticalRate;
				pDefense->nHealth -= nTemp;
				if (nCriticalRate == 2) {
					printf("  *\x1b[38;5;011mクリティカル\x1b[0m*\n");
				}
				printf("  相手に%dのダメージ\n\n", nTemp);
			}
		}
		else if (bHit == false) {
			printf("  攻撃がかわされた\n\n");
			PlaySound(TEXT("bgm//Dodge.wav"), NULL, SND_FILENAME | SND_ASYNC);
			pDefense->nSkillPoint += 13;
		}

		pOffense->nSkillPoint -= SKILLPOINT1;

	}

	else if (*pCommand == 2) {
		printf("  [\x1b[38;5;128mデバウアー\x1b[0m]\n");

		if (bHit == true) {
			if (pDefense->bShield == true) {
				PlaySound(TEXT("bgm//ShieldBreak.wav"), NULL, SND_FILENAME | SND_ASYNC);
				printf("  攻撃を防がれた\n\n");
				pDefense->bShield = false;
			}
			else if (pDefense->bShield == false) {
				PlaySound(TEXT("bgm//DEVOUR.wav"), NULL, SND_FILENAME | SND_ASYNC);
				nRand = rand() % 15 + 41;

				nTemp = ((pOffense->nAttack + nRand) - pDefense->nDefence) * nCriticalRate;
				if (nTemp <= 0) {
					nTemp = 0;
				}
				pDefense->nHealth -= nTemp;

				nTemp2 = (nTemp / 2) + 5;

				pOffense->nHealth += nTemp2;
				if (nCriticalRate == 2) {
					printf("  *\x1b[38;5;011mクリティカル\x1b[0m*\n");
				}
				printf("  相手に%dのダメージ\n 自分の体力が%d回復した\n", nTemp, nTemp2);
			}
		}
		else if (bHit == false) {
			printf("  攻撃がかわされた\n\n");
			PlaySound(TEXT("bgm//Dodge.wav"), NULL, SND_FILENAME | SND_ASYNC);
			pDefense->nSkillPoint += 13;
		}

		pOffense->nSkillPoint -= SKILLPOINT2;

	}

	else if (*pCommand == 3) {
		printf("  [\x1b[38;5;040mポイズンクラウド\x1b[0m]\n");

		if (bHit == true) {
			if (pDefense->bShield == true) {
				PlaySound(TEXT("bgm//ShieldBreak.wav"), NULL, SND_FILENAME | SND_ASYNC);
				printf("  毒を防がれた\n\n");
				pDefense->bShield = false;
			}
			else if (pDefense->bShield == false) {
				PlaySound(TEXT("bgm//POISONCLOUD.wav"), NULL, SND_FILENAME | SND_ASYNC);
				pDefense->nPoison += 3;

				printf("  相手に毒を付与した\n\n");
			}
		}
		else if (bHit == false) {
			PlaySound(TEXT("bgm//Dodge.wav"), NULL, SND_FILENAME | SND_ASYNC);
			printf("  毒がかわされた\n\n");
			pDefense->nSkillPoint += 13;
		}

		pOffense->nSkillPoint -= SKILLPOINT3;

	}

	else if (*pCommand == 4) {
		printf("  [\x1b[38;5;178mツール・ド・フォース\x1b[0m]\n");

		if (bHit == true) {
			if (pDefense->bShield == true) {
				PlaySound(TEXT("bgm//ShieldBreak.wav"), NULL, SND_FILENAME | SND_ASYNC);
				printf("  攻撃を防がれた\n\n");
				pDefense->bShield = false;
			}
			else if (pDefense->bShield == false) {
				PlaySound(TEXT("bgm//TOURDEFORCE.wav"), NULL, SND_FILENAME | SND_ASYNC);
				nRand = rand() % 35 + 41;

				nTemp = ((pOffense->nAttack + nRand) - pDefense->nDefence) * nCriticalRate;
				if (nTemp <= 0) {
					nTemp = 0;
				}
				pDefense->nHealth -= nTemp;
				pDefense->nAgilityDown += 2;
				if (nCriticalRate == 2) {
					printf("  *\x1b[38;5;011mクリティカル\x1b[0m*\n");
				}
				printf("  相手に%dのダメージ\n 相手の防御力が下がった\n", nTemp);
			}
		}
		else if (bHit == false) {
			PlaySound(TEXT("bgm//Dodge.wav"), NULL, SND_FILENAME | SND_ASYNC);
			printf("  攻撃がかわされた\n\n");
			pDefense->nSkillPoint += 13;
		}

		pOffense->nSkillPoint -= SKILLPOINT4;

	}

	else if (*pCommand == 5) {
		printf("  [\x1b[38;5;196mアーマースワップ\x1b[0m]\n");

		if (bHit == true) {
			if (pDefense->bShield == true) {
				PlaySound(TEXT("bgm//ShieldBreak.wav"), NULL, SND_FILENAME | SND_ASYNC);
				printf("  スキルを防がれた\n\n");
				pDefense->bShield = false;
			}
			else if (pDefense->bShield == false) {
				PlaySound(TEXT("bgm//ARMORSWAP.wav"), NULL, SND_FILENAME | SND_ASYNC);
				pDefense->nDefenceDown += 2;
				pOffense->nDefenceUp += 2;

				printf("  相手の防御力が下がった\n 自分の防御力が上がった\n");
			}
		}
		else if (bHit == false) {
			PlaySound(TEXT("bgm//Dodge.wav"), NULL, SND_FILENAME | SND_ASYNC);
			printf(" スキルがかわされた\n\n");
			pDefense->nSkillPoint += 13;
		}

		pOffense->nSkillPoint -= SKILLPOINT5;

	}

	else if (*pCommand == 6) {
		printf("  [\x1b[38;5;033mグラヴィネット\x1b[0m]\n");

		if (bHit == true) {
			if (pDefense->bShield == true) {
				PlaySound(TEXT("bgm//ShieldBreak.wav"), NULL, SND_FILENAME | SND_ASYNC);
				printf("  スキルを防がれた\n\n");
				pDefense->bShield = false;
			}
			else if (pDefense->bShield == false) {
				PlaySound(TEXT("bgm//GRAVNET.wav"), NULL, SND_FILENAME | SND_ASYNC);
				pDefense->nHitRateDown += 4;
				pDefense->nAgilityDown += 4;

				printf("  相手の命中率が下がった\n 相手の素早さが下がった\n");
			}
		}
		else if (bHit == false) {
			PlaySound(TEXT("bgm//Dodge.wav"), NULL, SND_FILENAME | SND_ASYNC);
			printf("  スキルがかわされた\n\n");
			pDefense->nSkillPoint += 13;
		}

		pOffense->nSkillPoint -= SKILLPOINT6;

	}

	else if (*pCommand == 7) {
		printf("  [\x1b[38;5;148mギャンブル\x1b[0m]\n");

		if (bHit == true) {
			if (pDefense->bShield == true) {
				PlaySound(TEXT("bgm//ShieldBreak.wav"), NULL, SND_FILENAME | SND_ASYNC);
				printf("  攻撃を防がれた\n\n");
				pDefense->bShield = false;
			}
			else if (pDefense->bShield == false) {
				nRand = rand() % 100 + 1;
				if (1 <= nRand && nRand <= 30) {
					PlaySound(TEXT("bgm//GAMBLING.wav"), NULL, SND_FILENAME | SND_ASYNC);

					nTemp = (pOffense->nAttack + 100) * nCriticalRate;
					pDefense->nHealth -= nTemp;
					if (nCriticalRate == 2) {
						printf("  *\x1b[38;5;011mクリティカル\x1b[0m*\n");
					}
					printf("  相手に%dのダメージ\n\n", nTemp);
				}
				else {
					PlaySound(TEXT("bgm//Dodge.wav"), NULL, SND_FILENAME | SND_ASYNC);
					printf("  攻撃がかわされた\n\n");
					pDefense->nSkillPoint += 13;
				}
			}
		}
		else if (bHit == false) {
			PlaySound(TEXT("bgm//Dodge.wav"), NULL, SND_FILENAME | SND_ASYNC);
			printf("  攻撃がかわされた\n\n");
			pDefense->nSkillPoint += 13;
		}

		pOffense->nSkillPoint -= SKILLPOINT7;

	}

	else if (*pCommand == 8) {
	PlaySound(TEXT("bgm//HEALINGORB.wav"), NULL, SND_FILENAME | SND_ASYNC);
		printf("  [\x1b[38;5;117mヒーリングオーブ\x1b[0m]\n");
		nTemp = rand() % 46 + 30;

		pOffense->nHealth += nTemp;

		nTemp2 = rand() % 11 + 10;

		pOffense->nSkillPoint += nTemp2;

		printf("  体力が%d回復した\n スキルポイントが%d回復した\n", nTemp, nTemp2);

		pOffense->nSkillPoint -= SKILLPOINT8;

	}

	else if (*pCommand == 9) {
	PlaySound(TEXT("bgm//HIGHGEAR.wav"), NULL, SND_FILENAME | SND_ASYNC);
		printf("  [\x1b[38;5;014mハイギア\x1b[0m]\n");
		pOffense->nAgilityUp += 4;

		printf("  素早さが上がった\n\n");

		pOffense->nSkillPoint -= SKILLPOINT9;
	}

	else if (*pCommand == 10) {
		PlaySound(TEXT("bgm//ShieldOn.wav"), NULL, SND_FILENAME | SND_ASYNC);
		printf("  [\x1b[38;5;140mダブルタップ\x1b[0m]\n");
		pOffense->bShield = true;
		
		printf("  シールドを付与した\n\n");

		pOffense->nSkillPoint -= SKILLPOINT10;
	}

	else if (*pCommand == 11) {
	PlaySound(TEXT("bgm//HEARTSHELLS.wav"), NULL, SND_FILENAME | SND_ASYNC);
		printf("  [\x1b[38;5;213mハートの貝殻\x1b[0m]\n");
		pOffense->nDefenceDown = 0;
		pOffense->nAgilityDown = 0;
		pOffense->nHitRateDown = 0;
		pOffense->nCriticalRateDown = 0;
		pOffense->nPoison = 0;

		printf("  デバフ効果がきえた\n\n");

		pOffense->nSkillPoint -= SKILLPOINT11;

	}

	else if (*pCommand == 12) {
		printf("  [\x1b[38;5;047mドキドキ涙\x1b[0m]\n");
		nRand = rand() % 2 + 1;

		if (nRand == 1) {
			PlaySound(TEXT("bgm//HEALINGORB.wav"), NULL, SND_FILENAME | SND_ASYNC);
			pOffense->nHealth += 20;
			printf("  体力が回復した\n\n");
		}

		else if (nRand == 2) {

			if (pOffense->bShield == true) {
				PlaySound(TEXT("bgm//ShieldBreak.wav"), NULL, SND_FILENAME | SND_ASYNC);
				printf("  自分の攻撃を防いだ\n\n");
				pOffense->bShield = false;
			}
			else if (pOffense->bShield == false) {
				PlaySound(TEXT("bgm//Damage.wav"), NULL, SND_FILENAME | SND_ASYNC);
				pOffense->nHealth -= 20;
				printf("  ダメージを受けた\n\n");
			}
		}
		
		pOffense->nSkillPoint -= SKILLPOINT12;
	}

	printf("└────────────────────────────────────────────────────────────────────────────┘\n");
	HpSpControl(pPlayer1, (pPlayer1 +1));

	

	do {
		nEnter = _getch();
		rewind(stdin);
	} while (nEnter != 13);
}

//===============================================
//Healtn SkillPoint管理
//===============================================
void HpSpControl(Player *pPlayer1, Player *pPlayer2) {
	//Health管理
	if (pPlayer1->nHealth < 0) {
		pPlayer1->nHealth = 0;
	}
	if (pPlayer2->nHealth < 0) {
		pPlayer2->nHealth = 0;
	}

	if (pPlayer1->nHealth > pPlayer1->nMaxHealth) {
		pPlayer1->nHealth = pPlayer2->nMaxHealth;
	}
	if (pPlayer2->nHealth > pPlayer2->nMaxHealth) {
		pPlayer2->nHealth = pPlayer2->nMaxHealth;
	}

	//スキルポイント管理
	if (pPlayer1->nSkillPoint < 0) {
		pPlayer1->nSkillPoint = 0;
	}
	if (pPlayer2->nSkillPoint < 0) {
		pPlayer2->nSkillPoint = 0;
	}
}

//===============================================
//ステータス管理
//===============================================
void StatusControl(Player* pPlayer1, Player* pPlayer2) {
	//防御力
	pPlayer1->nDefence = pPlayer1->nDefenceSave;
	pPlayer2->nDefence = pPlayer2->nDefenceSave;

	if (pPlayer1->nDefenceUp > 0) {
		pPlayer1->nDefence = pPlayer1->nDefenceSave + 25;
	}
	if (pPlayer1->nDefenceDown > 0) {
		pPlayer1->nDefence = pPlayer1->nDefenceSave - 20;
	}

	if (pPlayer2->nDefenceUp > 0) {
		pPlayer2->nDefence = pPlayer2->nDefenceSave + 25;
	}
	if (pPlayer2->nDefenceDown > 0) {
		pPlayer2->nDefence = pPlayer2->nDefenceSave - 20;
	}

	if (pPlayer1->nDefence < 0) {
		pPlayer1->nDefence = 0;
	}
	if (pPlayer1->nDefence > 100) {
		pPlayer1->nDefence = 100;
	}

	if (pPlayer2->nDefence < 0) {
		pPlayer2->nDefence = 0;
	}
	if (pPlayer2->nDefence > 100) {
		pPlayer2->nDefence = 100;
	}

	//素早さ
	pPlayer1->nAgility = pPlayer1->nAgilitySave;
	pPlayer2->nAgility = pPlayer2->nAgilitySave;

	if (pPlayer1->nAgilityUp > 0) {
		pPlayer1->nAgility = pPlayer1->nAgilitySave + 5;
	}
	if (pPlayer1->nAgilityDown > 0) {
		pPlayer1->nAgility = pPlayer1->nAgilitySave - 5;
	}

	if (pPlayer2->nAgilityUp > 0) {
		pPlayer2->nAgility = pPlayer2->nAgilitySave + 5;
	}
	if (pPlayer2->nAgilityDown > 0) {
		pPlayer2->nAgility = pPlayer2->nAgilitySave - 5;
	}

	if (pPlayer1->nAgility < 0) {
		pPlayer1->nAgility = 0;
	}
	if (pPlayer1->nAgility > 100) {
		pPlayer1->nAgility = 100;
	}
	
	if (pPlayer2->nAgility < 0) {
		pPlayer2->nAgility = 0;
	}
	if (pPlayer2->nAgility > 100) {
		pPlayer2->nAgility = 100;
	}

	//命中率
	pPlayer1->nHitRate = pPlayer1->nHitRateSave;
	pPlayer2->nHitRate = pPlayer2->nHitRateSave;

	if (pPlayer1->nHitRateUp > 0) {
		pPlayer1->nHitRate = pPlayer1->nHitRateSave + 5;
	}
	if (pPlayer1->nHitRateDown > 0) {
		pPlayer1->nHitRate = pPlayer1->nHitRateSave - 10;
	}

	if (pPlayer2->nHitRateUp > 0) {
		pPlayer2->nHitRate = pPlayer2->nHitRateSave + 5;
	}
	if (pPlayer2->nHitRateDown > 0) {
		pPlayer2->nHitRate = pPlayer2->nHitRateSave - 10;
	}

	if (pPlayer1->nHitRate < 0) {
		pPlayer1->nHitRate = 0;
	}
	if (pPlayer1->nHitRate > 100) {
		pPlayer1->nHitRate = 100;
	}

	if (pPlayer2->nHitRate < 0) {
		pPlayer2->nHitRate = 0;
	}
	if (pPlayer2->nHitRate > 100) {
		pPlayer2->nHitRate = 100;
	}

	//クリティカル率
	pPlayer1->nCriticalRate = pPlayer1->nCriticalRateSave;
	pPlayer2->nCriticalRate = pPlayer2->nCriticalRateSave;

	if (pPlayer1->nCriticalRateUp > 0) {
		pPlayer1->nCriticalRate = pPlayer1->nCriticalRateSave + 13;
	}
	if (pPlayer1->nCriticalRateDown > 0) {
		pPlayer1->nCriticalRate = pPlayer1->nCriticalRateSave - 5;
	}

	if (pPlayer2->nCriticalRateUp > 0) {
		pPlayer2->nCriticalRate = pPlayer2->nCriticalRateSave + 13;
	}
	if (pPlayer2->nCriticalRateDown > 0) {
		pPlayer2->nCriticalRate = pPlayer2->nCriticalRateSave - 5;
	}

	if (pPlayer1->nCriticalRate < 0) {
		pPlayer1->nCriticalRate = 0;
	}
	if (pPlayer1->nCriticalRate > 100) {
		pPlayer1->nCriticalRate = 100;
	}

	if (pPlayer2->nCriticalRate < 0) {
		pPlayer2->nCriticalRate = 0;
	}
	if (pPlayer2->nCriticalRate > 100) {
		pPlayer2->nCriticalRate = 100;
	}

	//毒
	if (pPlayer1->nPoison < 0) {
		pPlayer1->nPoison = 0;
	}
	if (pPlayer1->nPoison > 100) {
		pPlayer1->nPoison = 100;
	}

	if (pPlayer2->nPoison < 0) {
		pPlayer2->nPoison = 0;
	}
	if (pPlayer2->nPoison > 100) {
		pPlayer2->nPoison = 100;
	}
}

//===============================================
//ステータスターン管理
//===============================================
void StatusTurn(Player *pPlayer1, Player *pPlayer2, int nTurn) {
	int nEnter;

	//防御力
	if (pPlayer1->nDefenceUp > 0) {
		pPlayer1->nDefenceUp -= 1;
	}
	if (pPlayer1->nDefenceDown > 0) {
		pPlayer1->nDefenceDown -= 1;
	}

	if (pPlayer2->nDefenceUp > 0) {
		pPlayer2->nDefenceUp -= 1;
	}
	if (pPlayer2->nDefenceDown > 0) {
		pPlayer2->nDefenceDown -= 1;
	}

	//素早さ
	if (pPlayer1->nAgilityUp > 0) {
		pPlayer1->nAgilityUp -= 1;
	}
	if (pPlayer1->nAgilityDown > 0) {
		pPlayer1->nAgilityDown -= 1;
	}

	if (pPlayer2->nAgilityUp > 0) {
		pPlayer2->nAgilityUp -= 1;
	}
	if (pPlayer2->nAgilityDown > 0) {
		pPlayer2->nAgilityDown -= 1;
	}

	//命中率
	if (pPlayer1->nHitRateUp > 0) {
		pPlayer1->nHitRateUp -= 1;
	}
	if (pPlayer1->nHitRateDown > 0) {
		pPlayer1->nHitRateDown -= 1;
	}

	if (pPlayer2->nHitRateUp > 0) {
		pPlayer2->nHitRateUp -= 1;
	}
	if (pPlayer2->nHitRateDown > 0) {
		pPlayer2->nHitRateDown -= 1;
	}

	//クリティカル率
	if (pPlayer1->nCriticalRateUp > 0) {
		pPlayer1->nCriticalRateUp -= 1;
	}
	if (pPlayer1->nCriticalRateDown > 0) {
		pPlayer1->nCriticalRateDown -= 1;
	}

	if (pPlayer2->nCriticalRateUp > 0) {
		pPlayer2->nCriticalRateUp -= 1;
	}
	if (pPlayer2->nCriticalRateDown > 0) {
		pPlayer2->nCriticalRateDown -= 1;
	}

	//毒
	if (pPlayer1->nPoison > 0 || pPlayer2->nPoison > 0) {
		PlaySound(TEXT("bgm//POISONCLOUD.wav"), NULL, SND_FILENAME | SND_ASYNC);
		system("cls");

		BattleInfo(pPlayer1, nTurn);
		printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
		
		if (pPlayer1->nPoison > 0) {
			pPlayer1->nPoison -= 1;
			pPlayer1->nHealth -= 15;
			printf("  %sは毒でダメージを受けた\n\n\n\n", &pPlayer1->aName[0]);
		}

		if (pPlayer2->nPoison > 0) {
			pPlayer2->nPoison -= 1;
			pPlayer2->nHealth -= 15;
			printf("  %sは毒でダメージを受けた\n\n\n\n", &pPlayer2->aName[0]);
		}
		
		printf("└────────────────────────────────────────────────────────────────────────────┘\n");
		do {
			nEnter = _getch();
			rewind(stdin);
		} while (nEnter != 13);
		
	}

	HpSpControl(pPlayer1, pPlayer2);
}

//===============================================
//戦闘終了メッセージ表示
//===============================================
void EndBattle(Player* pPlayer1, Player* pPlayer2, int nWinPlayer) {
	int nEnter;

	//戦闘終了メッセージ表示

	PlaySound(TEXT("bgm//End.wav"), NULL, SND_FILENAME | SND_ASYNC);

	if (nWinPlayer == 0) {
		printf("┌────────────────────────────────────────────────────────────────────────────┐\n\n");
		printf("\n                                引き分け\n\n\n");
		printf("\n└────────────────────────────────────────────────────────────────────────────┘\n");
	}
	else if (nWinPlayer == 1) {
		printf("┌────────────────────────────────────────────────────────────────────────────┐\n\n");
		printf("\n                                %sの勝利\n\n\n", &pPlayer1->aName[0]);
		printf("\n└────────────────────────────────────────────────────────────────────────────┘\n");
	}
	else if (nWinPlayer == 2) {
		printf("┌────────────────────────────────────────────────────────────────────────────┐\n\n");
		printf("\n                                %sの勝利\n\n\n", &pPlayer2->aName[0]);
		printf("\n└────────────────────────────────────────────────────────────────────────────┘\n");
	}
	do {
		nEnter = _getch();
		rewind(stdin);
	} while (nEnter != 13);
}