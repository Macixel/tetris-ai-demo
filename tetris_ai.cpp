/*
0:O
1:L
2:Z
3:S
4:J
5:L
6:T
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int keeplive(int g[20][10]);
double calculateScore(int step1Board[20][10], int xx, int x); 
int wide(int x, int y);
int layOut(int x, int x1, int g[20][10]);
int boom(int g[20][10]);

int main(void)
{
	int g[20][10] = {0};
	int h[20][10];
	int h1[20][10];
	int x, y, x1, y1;
	int sum = 0;
	FILE *fp = fopen("3.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "[ERROR] cannot open input file: 3.txt\n");
		return 1;
	}
	//time_t program_start_time = time(NULL);
	int timeout = 0;
	char X, Y;
	X = fgetc(fp);
	Y = fgetc(fp);

    switch(X) {
            case 'O': x = 0; break;
            case 'I': x = 1; break;
            case 'Z': x = 2; break;
            case 'S': x = 3; break;
            case 'J': x = 4; break;
            case 'L': x = 5; break;
            case 'T': x = 6; break;
        }
    switch(x) {
            case 0: y = 0; break;
            case 1: y = 1; break;
            case 2: y = 1; break;
            case 3: y = 1; break;
            case 4: y = 4; break;
            case 5: y = 4; break;
            case 6: y = 4; break;
        }
    while (!timeout && Y != 'X' && Y != 'E'){
        switch(Y) {
            case 'O': x1 = 0; break;
            case 'I': x1 = 1; break;
            case 'Z': x1 = 2; break;
            case 'S': x1 = 3; break;
            case 'J': x1 = 4; break;
            case 'L': x1 = 5; break;
            case 'T': x1 = 6; break;
        }
        switch(x1) {
            case 0: y1 = 0; break;
            case 1: y1 = 1; break;
            case 2: y1 = 1; break;
            case 3: y1 = 1; break;
            case 4: y1 = 4; break;
            case 5: y1 = 4; break;
            case 6: y1 = 4; break;
        }
        
        double score1, Fscore;
        score1 = Fscore = -100000; 
        int j1 = 0, y0 = 0, xx, y9, yy;
        
        for(int m = 0; m <= y ; m++)
        {
        	int p = wide(x, m);
        	for(int n = 0; n < p ; n++)
        	{
        		memcpy(h, g, sizeof(g));
        		xx = x * 10 + m;
        		layOut(xx, n, h);
        		for(int i = 0; i <= y1 ;i++)
		        {
		            int k = wide(x1, i);
		            for(int j = 0; j < k ; j++)
		            {
		                memcpy(h1, h, sizeof(h));
		                yy = x1 * 10 + i;
		                y9 = layOut(yy, j, h1);
		                y9 = 20 - y9;
		                if(!keeplive(h1))
		                {
		                	score1 = calculateScore(h1, yy, y9);
			                if (score1 >= Fscore) {
			                    Fscore = score1;
			                    j1 = n;
			                    y0 = m;
			                }
						}else{
							score1 = calculateScore(h1, yy, y9) - 1000;
			                if (score1 >= Fscore) {
			                    Fscore = score1;
			                    j1 = n;
			                    y0 = m;
			                }
						}
		            }
		        }
			}
		}
        int zz = x * 10 + y0;
        layOut(zz, j1, g);
        int sco = 0, scc = 0;
        sco = boom(g);
        switch(sco)
        {
            case 0: scc = 0; break;
            case 1: scc = 100; break;
            case 2: scc = 300; break;
            case 3: scc = 500; break;
            case 4: scc = 800; break;
        }

        sum += scc;
        //printf("%d %d\n%d\n", y0, j1, sum);
        fflush(stdout);
		
        /*for(int i = 0; i < 20 ; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                printf("%d ", g[i][j]);
            }
            printf("\n");
        }*/
        //time_t current_time = time(NULL);
	    /*if (difftime(current_time, program_start_time) >= 9.5) {
	        timeout = 1;
	        break;
	    }*/
		Y = fgetc(fp);
		x = x1;
    	y = y1;
    }
    x = x1;
    y = y1;
    int y9 = 0, xx = 0;
    int score1 = -100000, Fscore = -1000000;

        int j1 = 0, y0 = 0;
        for(int i = 0; i < y ;i++)
        {
            int k = wide(x, i);
            for(int j = 0; j < k ; j++)
            {
                memcpy(h, g, sizeof(g));
                int xx = x * 10 + y;
                y9 = layOut(xx, j, h);
                double score1 = calculateScore(h, xx, y9);
                if (score1 > Fscore) {
                    Fscore = score1;
                    j1 = j;
                    y0 = i;
                }
            }
        }

    int zz = x * 10 + y0;
    layOut(zz, j1, g);

    int sco = 0, scc = 0;
    sco = boom(g);

    switch(sco)
    {
        case 0: scc = 0; break;
        case 1: scc = 100; break;
        case 2: scc = 300; break;
        case 3: scc = 500; break;
        case 4: scc = 800; break;
    }

    sum += scc;
    printf("%d %d\n%d\n", y0, j1, sum);

    /*for(int i = 0; i < 20 ; i++)
    {
    	for(int j = 0; j < 10; j++)
    	{
    		printf("%d ", g[i][j]);
		}
		printf("\n");
	}*/

    fflush(stdout);
    fclose(fp);
	return 0;
}

//将当前放置方块自上而下遍历插入游戏盘中并返回插入位置左下角纵坐标
int layOut(int x, int x1, int g[20][10])
{
    int y1 = 3;
    switch(x) {
        case 0:
            while (g[y1][x1] + g[y1][x1 + 1] == 0) {
                y1++;
                if(y1 == 20){
                	break;
				}
            }
            y1--;
            g[y1][x1] = 1;
            g[y1][x1 + 1] = 1;
            g[y1 - 1][x1] = 1;
            g[y1 - 1][x1 + 1] = 1;
            break;

        case 10:
            while (g[y1][x1] + g[y1][x1 + 1] + g[y1][x1 + 2] + g[y1][x1 + 3] == 0) {
                y1++;
                if(y1 == 20){
                	break;
				}
            }
            y1--;
            g[y1][x1] = 1;
            g[y1][x1 + 1] = 1;
            g[y1][x1 + 2] = 1;
            g[y1][x1 + 3] = 1;
            break;

        case 11:
            while (g[y1][x1]== 0) {
                y1++;
                if(y1 == 20){
                	break;
				}
            }
            y1--;
            g[y1][x1] = 1;
            g[y1 - 1][x1] = 1;
            g[y1 - 2][x1] = 1;
            g[y1 - 3][x1] = 1;
            break;

        case 20:
            while (g[y1][x1 + 2] + g[y1][x1 + 1] + g[y1 - 1][x1] == 0) {
                y1++;
                if(y1 == 20){
                	break;
				}
            }
            y1--;
            g[y1 - 1][x1] = 1;
            g[y1 - 1][x1 + 1] = 1;
            g[y1][x1 + 1] = 1;
            g[y1][x1 + 2] = 1;
            break;

        case 21:
            while (g[y1][x1] + g[y1 - 1][x1 + 1] == 0) {
                y1++;
                if(y1 == 20){
                	break;
				}
            }
            y1--;
            g[y1][x1] = 1;
            g[y1 - 2][x1 + 1] = 1;
            g[y1 - 1][x1 + 1] = 1;
            g[y1 - 1][x1] = 1;
            break;

        case 30:
            while (g[y1][x1] + g[y1][x1 + 1] + g[y1 - 1][x1 + 2] == 0) {
                y1++;
                if(y1 == 20){
                	break;
				}
            }
            y1--;
            g[y1][x1] = 1;
            g[y1][x1 + 1] = 1;
            g[y1 - 1][x1 + 1] = 1;
            g[y1 - 1][x1 + 2] = 1;
            break;

        case 31:
            while (g[y1 - 1][x1] + g[y1][x1 + 1] == 0) {
                y1++;
                if(y1 == 20){
                	break;
				}
            }
            y1--;
            g[y1 - 1][x1] = 1;
            g[y1 - 2][x1] = 1;
            g[y1][x1 + 1] = 1;
            g[y1 - 1][x1 + 1] = 1;
            break;

        case 40:
            while (g[y1][x1] + g[y1][x1 + 1] + g[y1][x1 + 2] == 0) {
                y1++;
                if(y1 == 20){
                	break;
				}
            }
            y1--;
            g[y1][x1] = 1;
            g[y1 - 1][x1] = 1;
            g[y1][x1 + 1] = 1;
            g[y1][x1 + 2] = 1;
            break;

        case 41:
            while (g[y1][x1] + g[y1 - 2][x1 + 1] == 0) {
                y1++;
                if(y1 == 20){
                	break;
				}
            }
            y1--;
            g[y1][x1] = 1;
            g[y1 - 1][x1] = 1;
            g[y1 - 2][x1] = 1;
            g[y1 - 2][x1 + 1] = 1;
            break;

        case 42:
            while (g[y1 - 1][x1] + g[y1 - 1][x1 + 1] + g[y1][x1 + 2] == 0) {
                y1++;
                if(y1 == 20){
                	break;
				}
            }
            y1--;
            g[y1 - 1][x1] = 1;
            g[y1 - 1][x1 + 1] = 1;
            g[y1 - 1][x1 + 2] = 1;
            g[y1][x1 + 2] = 1;
            break;

        case 43:
            while (g[y1][x1] + g[y1][x1 + 1] == 0) {
                y1++;
                if(y1 == 20){
                	break;
				}
            }
            y1--;
            g[y1][x1] = 1;
            g[y1][x1 + 1] = 1;
            g[y1 - 1][x1 + 1] = 1;
            g[y1 - 2][x1 + 1] = 1;
            break;

        case 50:
            while (g[y1][x1] + g[y1][x1 + 1] + g[y1][x1 + 2] == 0) {
                y1++;
                if(y1 == 20){
                	break;
				}
            }
            y1--;
            g[y1][x1] = 1;
            g[y1][x1 + 1] = 1;
            g[y1][x1 + 2] = 1;
            g[y1 - 1][x1 + 2] = 1;
            break;

        case 51:
            while (g[y1][x1] + g[y1][x1 + 1] == 0) {
                y1++;
                if(y1 == 20){
                	break;
				}
            }
            y1--;
            g[y1][x1] = 1;
            g[y1 - 1][x1] = 1;
            g[y1][x1 + 1] = 1;
            g[y1 - 2][x1] = 1;
            break;

        case 52:
            while (g[y1][x1] + g[y1 - 1][x1 + 1] + g[y1 - 1][x1 + 2] == 0) {
                y1++;
                if(y1 == 20){
                	break;
				}
            }
            y1--;
            g[y1][x1] = 1;
            g[y1 - 1][x1 + 1] = 1;
            g[y1 - 1][x1 + 2] = 1;
            g[y1 - 1][x1] = 1;
            break;

        case 53:
            while (g[y1 - 2][x1] + g[y1][x1 + 1] + g[y1 - 1][x1 + 1] + g[y1 - 2][x1 + 1] == 0) {
                y1++;
                if(y1 == 20){
                	break;
				}
            }
            y1--;
            g[y1 - 2][x1] = 1;
            g[y1][x1 + 1] = 1;
            g[y1 - 1][x1 + 1] = 1;
            g[y1 - 2][x1 + 1] = 1;
            break;

        case 60:
            while (g[y1][x1] + g[y1][x1 + 1] + g[y1][x1 + 2] == 0) {
                y1++;
                if(y1 == 20){
                	break;
				}
            }
            y1--;
            g[y1][x1] = 1;
            g[y1][x1 + 1] = 1;
            g[y1][x1 + 2] = 1;
            g[y1 - 1][x1 + 1] = 1;
            break;

        case 61:
            while (g[y1][x1] + g[y1 - 1][x1 + 1] == 0) {
                y1++;
                if(y1 == 20){
                	break;
				}
            }
            y1--;
            g[y1][x1] = 1;
            g[y1 - 1][x1 + 1] = 1;
            g[y1 - 1][x1] = 1;
            g[y1 - 2][x1] = 1;
            break;

        case 62:
            while (g[y1 - 1][x1] + g[y1][x1 + 1] + g[y1 - 1][x1 + 2] == 0) {
                y1++;
                if(y1 == 20){
                	break;
				}
            }
            y1--;
            g[y1 - 1][x1] = 1;
            g[y1][x1 + 1] = 1;
            g[y1 - 1][x1 + 2] = 1;
            g[y1 - 1][x1 + 1] = 1;
            break;

        case 63:
            while (g[y1 - 1][x1] + g[y1][x1 + 1] == 0) {
                y1++;
                if(y1 == 20){
                	break;
				}
            }
            y1--;
            g[y1 - 1][x1] = 1;
            g[y1][x1 + 1] = 1;
            g[y1 - 1][x1 + 1] = 1;
            g[y1 - 2][x1 + 1] = 1;
            break;
    }
    return y1;
}

//返回当前放置方块及角度能放置的横坐标
int wide(int x, int y)
{
    int t = x * 10 + y;
    switch(t)
    {
        case 0: return 9;
        case 10: return 7;
        case 11: return 10;
        case 20: return 8;
        case 21: return 9;
        case 30: return 8;
        case 31: return 9;
        case 40: return 8;
        case 41: return 9;
        case 42: return 8;
        case 43: return 9;
        case 50: return 8;
        case 51: return 9;
        case 52: return 8;
        case 53: return 9;
        case 60: return 8;
        case 61: return 9;
        case 62: return 8;
        case 63: return 9;
    }
    return 0;
}

//返回方块高度-1模拟重心（单纯的不会算重心以及懒得用浮点数，感觉也没差什么）
int height(int x)
{
    switch(x)
    {
        case 0: return 1 ;
        case 10: return 1;
        case 11: return 3;
        case 20: return 1;
        case 21: return 2;
        case 30: return 1;
        case 31: return 2;
        case 40: return 1;
        case 41: return 2;
        case 42: return 1;
        case 43: return 2;
        case 50: return 1;
        case 51: return 2;
        case 52: return 1;
        case 53: return 2;
        case 60: return 1;
        case 61: return 2;
        case 62: return 1;
        case 63: return 2;
    }
    return 0;
}

//返回放置方块重心高度
int calculateLandingHeight(int g[20][10], int xx, int x) 
{
	int w1 = height(xx);
	int maxHeight = w1 + x;
    //printf("maxHeight: %d %d %d %d ", maxHeight, w1, x, xx);
    return maxHeight;
}

//查看当前消除的行里（如果有）新放的块占了几个格子（纯纯的史啊伙计们）
int calculateValuableblock(int g[20][10], int xx, int y0)
{
    int cot = 0, a[4] = {0};
    for (int i = 19; i >= 0; i--) {
        int is_full = 1, k = 0;
        for (int j = 0; j < 10; j++) {
            if (g[i][j] != 1) {
                is_full = 0;
                break;
            }
        }
        if (is_full) {
            cot++;
            a[k] = i;
            k++;
        }
    }
    switch(xx)
    {
        case 0: return 2 * cot * cot;
        case 10: return 4 * cot;
        case 11: return cot * cot;
        case 20: return 2 * cot;
        case 21: if (cot == 1) return 2;
                    else if (cot == 2) return 6;
                    else return 0;
        case 30: return 2 * cot;
        case 31: if (cot == 1) return 2;
                    else if (cot == 2) return 6;
                    else return 0;
        case 40: return 3 * cot;
        case 41: if (cot == 1 && (20 - a[0] == y0+2)) return 2;
                    else if (cot == 1) return 1;
                    else if (cot == 2 && (20 - a[0] == y0 + 2 | 20 - a[1] == y0 + 2)) return 6;
                    else if (cot == 2) return 4;
                    else if (cot == 3) return 12;
                    else return 0;
        case 42: if(cot == 1 && (20 - a[0] == y0)) return 1;
                    else if (cot == 1) return 3;
                    else if (cot == 2) return 8;
                    else return 0;
        case 43: if(cot == 1) return 2;
                    else if (cot == 2) return 6;
                    else if (cot == 3) return 12;
                    else return 0;
        case 50: if(cot == 1) return 6;
                    else if (cot == 2) return 8;
                    else return 0;
        case 51: if(cot == 1) return 2;
                    else if (cot == 2) return 6;
                    else if (cot == 3) return 12;
                    else return 0;
        case 52: if(cot == 1 && (20 - a[0] == y0)) return 1;
                    else if (cot == 1) return 3;
                    else if (cot == 2) return 8;
                    else return 0;
        case 53: if (cot == 1 && (20 - a[0] == y0+2)) return 2;
                    else if (cot == 1) return 1;
                    else if (cot == 2 && (20 - a[0] == y0 + 2 | 20 - a[1] == y0 + 2)) return 6;
                    else if (cot == 2) return 4;
                    else if (cot == 3) return 12;
                    else return 0;
        case 60: return 3 * cot;
        case 61: if (cot == 1 && (20 - a[0] == y0)) return 1;
                    else if (cot == 1) return 2;
                    else if (cot == 2) return 6;
                    else return 0;
        case 62: if (cot == 1 && (20 - a[0] == y0)) return 1;
                    else if (cot == 1) return 3;
                    else if (cot == 2) return 8;
                    else return 0;
        case 63: if (cot == 1 && (20 - a[0] == y0)) return 1;
                    else if (cot == 1) return 2;
                    else if (cot == 2) return 6;
                    else return 0;
    }
}

//行变换计数 
int calculateRowTransitions(int g[20][10]) 
{
    int rowTransitions = 0;
    for (int row = 0; row < 20; row++) {
        if(g[row][0] != 1) {
            rowTransitions++;
        }
        if(g[row][9] != 1) {
            rowTransitions++;
        }
        for (int col = 1; col < 10; col++) {
            if (g[row][col] != g[row][col-1]) {
                rowTransitions++;
            }
        }
        if(g[row][9] != g[row][0]) rowTransitions++;
    }
    //printf("rowTransitions: %d ", rowTransitions);
    return rowTransitions;
}

//列变换计数
int calculateColumnTransitions(int g[20][10]) 
{
    int colTransitions = 0, i = 0;
    for(int col = 0; col < 10; col++) {
        if(g[19][col] != 1) {
            colTransitions++;
        }
    }
    for (int col = 0; col < 10; col++) {
        for (int row = 1; row < 20; row++) {
            if (g[row][col] != g[row-1][col]) {
                colTransitions++;
            }
        }
        i = 0;
    }
    //printf("colTransitions: %d ", colTransitions);
    return colTransitions;
}

//数洞 
int calculateNumberOfHoles(int g[20][10]) 
{
    int holes = 0;
    int blockFound = 0;
    for(int i = 0; i < 10 ; i++)
    {
    	int j = 0;
    	for(; j < 20 ; j++)
    	{
    		if(g[j][i] == 1)
    		{
    			j++;
    			break;
			}
		}
		for(; j < 20 ; j++)
		{
			if(g[j][i] == 0)
			{
				holes++;
			}
		}
	}
    //printf("holes: %d ", holes);
    return holes;
}

//嘻嘻，我一定要活下去 
int keeplive(int g[20][10])
{
	int kkk = 0;
	for(int i = 0 ; i < 10 ; i++)
	{
	    for(int j = 0; j < 20 ; j++)
	    {
	    	if(g[j][i] && j < 5)
	    	{
	    		kkk = 1;
	    		break;
			}
		}
		if(kkk) break;
	}
	return kkk;
}
//查井深 
int calculateWellSums(int g[20][10]) 
{
    int wellSums = 0, deep = 0;
    for(int row = 0 ; row < 20 ; row++)
    {
    	if(g[row][0] == 0 && g[row][1] == 1)
    	{
    		deep++;
    		wellSums += deep;
		}else{
			deep = 0;
		}
	}
    for (int col = 1; col < 9; col++) {
        for (int row = 0; row < 20; row++) {
            if (g[row][col] == 0 && g[row][col-1] == 1 && g[row][col+1] == 1) {
                deep++;
                wellSums += deep;
            }else{
                deep = 0;
            }
        }
    }
    for(int row = 0 ; row < 20 ; row++)
    {
    	if(g[row][9] == 0 && g[row][8] == 1)
    	{
    		deep++;
    		wellSums += deep;
		}else{
			deep = 0;
		}
	}
    //printf("wellSums: %d ", wellSums);
    return wellSums;
}

//清算时刻！
double calculateScore(int g[20][10], int xx, int x) 
{
    double score = 0.0;

    double landingHeight = calculateLandingHeight(g, xx, x);
    int rowsEliminated = calculateValuableblock(g, xx, x);
    int rowTransitions = calculateRowTransitions(g);
    int colTransitions = calculateColumnTransitions(g);
    int numberOfHoles = calculateNumberOfHoles(g);
    int wellSums = calculateWellSums(g);

    score = -45 * landingHeight 
			+ 34 * rowsEliminated 
			- 32 * rowTransitions 
			- 93 * colTransitions 
			- 79 * numberOfHoles 
			- 34 * wellSums;
    //printf("score: %lf\n", score);
    return score;
}

//boom!清行并返回清除了几行（理论上能传参简化但是算了）
int boom(int g[20][10]) 
{
    int cot = 0;
    for (int i = 19; i >= 0; i--) {
        int is_full = 1;
        for (int j = 0; j < 10; j++) {
            if (g[i][j] != 1) {
                is_full = 0;
                break;
            }
        }

        if (is_full) {
            cot++;
            for (int k = i; k > 0; k--) {
                memcpy(g[k], g[k-1], sizeof(g[0]));
            }
            memset(g[0], 0, sizeof(g[0]));
            i++;
        }
    }
    return cot;
}
