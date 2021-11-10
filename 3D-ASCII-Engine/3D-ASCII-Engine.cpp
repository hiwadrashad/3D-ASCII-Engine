
#include <iostream>
#include <Windows.h>

int nScreenWidth = 120;
int nScreenHeight = 40;

float fPlayerX = 0.0f;
float fplayerY = 0.0f;
float fPlayerA = 0.0f;

int nMapHeight = 16;
int nMapWidth = 16;

float fFOV = 3.24259 / 4.0;
float fDepth = 16.0f;

int main()
{
    wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    std::wstring map;

    map += L"################";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"################";


    while (1)
    {
        for (int x = 0; x < nScreenWidth; x++)
        {
            float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)nScreenWidth) * fFOV;

            float fDistanceToWall = 0;

            bool bHitWall = false;

            float fEyex = sinf(fRayAngle);
            float fEyeY = cosf(fRayAngle);

            while (!bHitWall && fDistanceToWall < fDepth)
            {
                fDistanceToWall += 0.1f;

                int nTestX = (int)(fPlayerX + fEyex * fDistanceToWall);
                int nTestY = (int)(fplayerY + fEyeY * fDistanceToWall);

                if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight)
                {
                    bHitWall = true;
                    fDistanceToWall = fDepth;
                }
                else
                {
                    if (map[nTestY * nMapWidth + nTestX] == "#")
                    {
                        bHitWall = true;
                    }
                }
            }
        }
        screen[nScreenWidth * nScreenHeight - 1] = '\0';
        WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
    }

    return 0;
}



