#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <glut.h>
#include <time.h>
#include<malloc.h>
#include<WinSock2.h>
#include<stdlib.h>
//////////////////
#define pi 3.14
#define colorCar if(colorCarplayer==1)glColor3f(1.0f, 1.6f, 0.0f);if(colorCarplayer==2)glColor3f(0, 0,  0);if(colorCarplayer==3)glColor3f(0.30, 0.30, 1.00);if(colorCarplayer==5)glColor3f(1.00, 0.11, 0.68);if(colorCarplayer==4)glColor3f(0.137255 , 0.556863, 0.419608);
//////////////
//סטרקט המדרכות
struct kob {
    float x, z;
    int direction;
    int color;
};
// סטרקט האוטו של השחקן
struct car {
    float x = 0, z = 0, y = 0;
};
//סטרקט המוכנית החונים במשחק 
struct c_parking {
    float x, z;
};
int root = 0;//סיבוב המכניות במסכים 
             ////////////////
             // משתנה המסך 
int screen = 0;
//////////////
bool flag_level = false;//משתנה בוליאני הבודק אם עבר השחקן השלב 
int levelstage = 1; // מעדכן השלב הנכחי בתןך המשחק בזמן נוכחי 
                    /////////////////
int LEFT = 0; // סיבוב הרכב לשמאל   
int RIGHT = -180; // סביב הרכב לימין 
float RADIUS = 0.0; // סבוב במגרש 
float speed = 0.01; // מהירות הרכב 
                    /////////////////////
time_t t1, t2; //T1  זמן התחלה //T2 זמן הנוכחי 
int TimerEnd = 60;
int flagCarUp = 1, flagCarDown = 0;// דגלים עזרה לשלב 4ו3 במשחק 
int flagCarUp2 = 0, flagCarDown2 = 1;// דגלים עזרה לשלב 4 במשחק 
int colorCarplayer = 2; // בחירת צבע המוכנית 
int v = 0; // אנדקס עזרה לציור מדרכות 
char life[2] = "3"; // ניקוד 
char timeprint[3] = ""; // הדפסת הזמן 

                        //////////////
FILE* f2;// מצביע לקובץ
bool name = false, pass = false; // בחירת איזור כתיבה 
char strOfUserName[20] = "";// מחרוזת שם המשתמש 
char strOfUserNamepass[20] = "";//מחרוזת הסיסמה של משתמש
char strOfUserlevel[2] = "1";//מחרוזת של השלבים
int indexOfUserName = 0;
int indexOfUserNamePass = 0;
//////////////
car car1; // מוכנית השחקן 
car car2; // המוכנית בשלב שני שעולה ויורדת 
car car3; // המוכנית בשלב שני שחונה באמצע החניון 
car cars[15]; // מערך המוכניות החונות בתוך המגרש 
kob arr[2000]; // מערלך המדרכות 
c_parking parking1; // החנייה הנדרשת 
                    ///////////////
void OpenFile(int status); //פונקציה פתיחת קובץ 
void timePrintOnScreen();// פונקציה מדפיסה הזמן בתוך מסך המשחק 
int car_Accident(); // נגישות עם רכביבם 
void Reset_level();

int KopAccident() // פונקציה נגישות הרכב עם המדרכות 
{

    for (int j = 0; arr[j].x != NULL; j++)
    {


        if ((RADIUS >= 60 && RADIUS <= 120 || RADIUS <= -60 && RADIUS >= -120) || (RADIUS >= 240 && RADIUS <= 300 || RADIUS <= -240 && RADIUS >= -300))
        {
            if (car1.x >= arr[j].x - 3.3 && car1.x <= arr[j].x + 3.3 && car1.z + 35.0 >= arr[j].z - 2.3 && car1.z+ 35.0 <= arr[j].z + 2.3)
            {
                printf("kop");
                return 0;
            }
        }

        if (((RADIUS >= 0 && RADIUS <60 || RADIUS > -360 && RADIUS < -300) || (RADIUS <= -0 && RADIUS > -60 || RADIUS < 360 && RADIUS > 300)) ||
            (RADIUS >= 120 && RADIUS < 240 || RADIUS < -120 && RADIUS > -240))
        {
            if (car1.x >= arr[j].x - 2.3 && car1.x <= arr[j].x + 2.3 && car1.z + 35.0 >= arr[j].z - 3.3 && car1.z + 35.0 <= arr[j].z + 3.3)
            {
                printf("kop");
                return 0;
            }
        }
    }
    return 1;
}
int car_move_Accident();// המוכנית בשלב שני 
void car_parking();// פונקציה הבודקת אם הרכב חנה במקום הנדרש 
void mouse(int btn, int state, int x, int y)// פונקציה להשתמש בעכבר 
{
    if (screen == 7) {
        // בליחצה על הכפתור השמאלי בעכבר יכולים להזין שם משתמש וגם סיסמה 
        if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {

            if ((x <= 408 && x >= 222) && (y <= 177 && y >= 148))
            {
                name = true;
                pass = false;
            }
            else
            {
                name = false;

            }
            if ((x <= 444 && x >= 222) && (y <= 211 && y >= 187))
            {
                name = false;
                pass = true;
            }
            else
            {
                pass = false;
            }
            if ((x <= 636 && x >= 545) && (y <= 444 && y >= 413))
            {
                OpenFile(2);
            }
        }
    }
    if (screen == 5) // בליחצה על הכפתור השמאלי בעכבר יכולים להזין שם משתמש וגם סיסמה 

    {
        if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {

            if ((x <= 412 && x >= 220) && (y <= 138 && y >= 105))
            {
                name = true;
                pass = false;
            }
            else
            {
                name = false;

            }
            if ((x <= 444 && x >= 220) && (y <= 177 && y >= 148))
            {
                name = false;
                pass = true;
            }
            else
            {
                pass = false;
            }
            if ((x <= 636 && x >= 545) && (y <= 444 && y >= 413))
            {
                OpenFile(1);
            }


        }
    }
    if (screen == 8) // בליחצה על הכפתור השמאלי בעכבר יכולים לבחור צבע הרכב שרוצים לשחק 

    {
        if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {

            if ((x <= 623 && x >= 575) && (y <= 624 && y >= 593))
            {
                colorCarplayer = 1;

            }
            if ((x <= 500 && x >= 450) && (y <= 624 && y >= 592))
            {
                colorCarplayer = 2;
            }

            if ((x <= 559 && x >= 513) && (y <= 625 && y >= 559))
            {
                colorCarplayer = 3;

            }
            if ((x <= 687 && x >= 638) && (y <= 623 && y >= 593))
            {
                colorCarplayer = 4;

            }

            if ((x <= 748 && x >= 701) && (y <= 624 && y >= 592))
            {
                colorCarplayer = 5;

            }

        }
    }
    glutPostRedisplay();
}
void OpenFile(int status)//פונקציה לפתיחת קובץ לשמירת ניתוני המשחק 
{
    FILE* file; //מצביע על הקובץ
    char str_compare[255]; //מחרוזת שולפת מחרזות מתוך הקובץ ועושה בדיקה עם המחרוזת הנקלטה מהמשתמש 
    if (status == 1) // מצב של משתמש חדש 
    {
        int compare, compare1; //variable to hold the result of comparing both strings
        compare = strcmp("", strOfUserName);
        compare1 = strcmp("", strOfUserNamepass);
        if (compare != 0 && compare1 != 0) {

            file = fopen(strOfUserName, "w+");
            strOfUserNamepass[indexOfUserNamePass] = '\n';
            strOfUserNamepass[++indexOfUserNamePass] = '\0';
            fputs(strOfUserNamepass, file);
            fputs(strOfUserlevel, file);
            fclose(file);
            screen = 8;
        }
        else // לשגיות חסר שם משתמש או סיסמה 
        {
            screen = 9;
            glutPostRedisplay();
            strcpy(strOfUserName, "");
            strcpy(strOfUserNamepass, "");
        }
    }
    //משתמש קיים 
    if (status == 2)
    {
        file = fopen(strOfUserName, "r"); // מחפשים על הקובץ של המשתמש 
        if (file == NULL)
        {

            screen = 9;
            return;
        }
        else
        {
            //אם השם משתמש קיים בודק הסיסמה 
         
            int k;
            k=fscanf(file, "%s", str_compare);
            //בדיקת שתי מחרזות ומחזירה 0 אם אין הבדל בין מחרוזות  

            if (strcmp(str_compare, strOfUserNamepass) == 0)
            {
               k=fscanf(file, "%s", strOfUserlevel);

                screen = 8;

            }
            else
            {
                screen = 9;
                glutPostRedisplay();
                strcpy(strOfUserName, "");
                strcpy(strOfUserNamepass, "");

            }

        }
        //closing file
        fclose(file);
    }
}
void specialKeyFunc(int key, int x, int y)// גישה למסכים
{
    if (screen == 0)//במסך הפתיחה החצים לשימוש הזזת האוטו כדי לראות אותה 
    {
        if (key == GLUT_KEY_RIGHT) { root++; }
        if (key == GLUT_KEY_LEFT) { root--; }
    }

    if (screen == 8)//החצים לשימוש הזזת האוטו כדי לראות אותה
    {

        if (key == GLUT_KEY_RIGHT) { root++; }
        if (key == GLUT_KEY_LEFT) { root--; }

    }
    if (screen == 2)//לחיצה F1 
    {
        if (key == GLUT_KEY_F1)screen = 0;
    }
    if (screen == 9)//לחיצה F1 F2
    {
        if (key == GLUT_KEY_F1)screen = 0;
        if (key == GLUT_KEY_F2)screen = 6;
    }
    if (screen == 1)
    {
        if (key == GLUT_KEY_F1)screen = 0;
    }
    if (screen == 5)
    {
        if (key == GLUT_KEY_F2)
        {

            screen = 6;
            strcpy(strOfUserName, "");
            strcpy(strOfUserNamepass, "");

        }
        if (key == GLUT_KEY_F1)
        {

            screen = 0;
            strcpy(strOfUserName, "");
            strcpy(strOfUserNamepass, "");

        }
    }
    if (screen == 7)
    {
        if (key == GLUT_KEY_F2)
        {

            screen = 6;
            strcpy(strOfUserName, "");
            strcpy(strOfUserNamepass, "");

        }
        if (key == GLUT_KEY_F1)
        {

            screen = 0;
            strcpy(strOfUserName, "");
            strcpy(strOfUserNamepass, "");

        }
    }
    if (screen == 6)
    {
        if (key == GLUT_KEY_RIGHT) { root++; }
        if (key == GLUT_KEY_LEFT) { root--; }
        if (key == GLUT_KEY_F1)
        {
            screen = 0;
        }

    }

    if (screen == 3 || screen == 11 || screen == 12 || screen == 16)
    {



        if (key == GLUT_KEY_UP)//לחצה על החץ למעלה האוטו מתקדם 
        {                        /*1*/

            if (KopAccident() == 1)
            {
                if (RADIUS <= 10 && RADIUS >= 0)
                {
                    speed += 0.0007;
                    car1.z -= speed;
                }
                if (RADIUS >= -360 && RADIUS <= -350)
                {
                    speed += 0.0007;
                    car1.z -= speed;
                }
                if ((RADIUS >= -10 && RADIUS <= 0))
                {
                    speed += 0.0007;
                    car1.z -= speed;
                }
                if (RADIUS <= 360 && RADIUS >= 350)
                {
                    speed += 0.0007;
                    car1.z -= speed;
                }
                /*2*/
                if (RADIUS >= 10 && RADIUS <= 30)
                {
                    speed += 0.00056;
                    car1.z -= speed;
                    car1.x -= 0.056;
                }
                if (RADIUS <= -330 && RADIUS >= -350)
                {
                    speed += 0.00056;
                    car1.z -= speed;
                    car1.x -= 0.056;
                }
                if (RADIUS <= -10 && RADIUS >= -30)
                {
                    speed += 0.00056;
                    car1.z -= speed;
                    car1.x += 0.056;
                }
                if (RADIUS >= 330 && RADIUS <= 350)
                {
                    speed += 0.00056;
                    car1.z -= speed;
                    car1.x += 0.056;
                }
                /*3*/
                if (RADIUS <= -310 && RADIUS >= -330)
                {
                    speed += 0.00042;
                    car1.z -= speed;
                    car1.x -= 0.07;
                }
                if (RADIUS >= 30 && RADIUS <= 50)
                {
                    speed += 0.00042;
                    car1.z -= speed;
                    car1.x -= 0.07;
                }
                if (RADIUS >= 310 && RADIUS <= 330)
                {
                    speed += 0.00042;
                    car1.z -= speed;
                    car1.x += 0.042;
                }
                if (RADIUS <= -30 && RADIUS >= -50)
                {
                    speed += 0.00042;
                    car1.z -= speed;
                    car1.x += 0.042;
                }
                /*4*/
                if (RADIUS <= -290 && RADIUS >= -310)
                {
                    speed += 0.00042;
                    car1.z -= speed;
                    car1.x -= 0.075;
                }
                if (RADIUS >= 50 && RADIUS <= 70)
                {
                    speed += 0.00042;
                    car1.z -= speed;
                    car1.x -= 0.075;
                }
                if (RADIUS >= 290 && RADIUS <= 310)
                {
                    speed += 0.00028;
                    car1.z -= speed;
                    car1.x += 0.075;
                }
                if (RADIUS <= -50 && RADIUS >= -70)
                {
                    speed += 0.00028;
                    car1.z -= speed;
                    car1.x += 0.075;
                }
                /*5*/
                if (RADIUS <= -280 && RADIUS >= -290)
                {
                    speed += 0.00014;
                    car1.z -= speed;
                    car1.x -= 0.09;
                }
                if (RADIUS >= 70 && RADIUS <= 80)
                {
                    speed += 0.00014;
                    car1.z -= speed;
                    car1.x -= 0.09;
                }
                if (RADIUS <= 280 && RADIUS >= 290)
                {
                    speed += 0.0001;
                    car1.z -= speed;
                    car1.x += 0.091;
                }
                if (RADIUS <= -70 && RADIUS >= -80)
                {
                    speed += 0.0001;
                    car1.z -= speed;
                    car1.x += 0.091;
                }
                /*6*/
                if (RADIUS <= -260 && RADIUS >= -280)
                {
                    car1.x -= 0.14;

                }
                if (RADIUS >= 80 && RADIUS <= 100)
                {
                    car1.x -= 0.14;
                }
                /*7*/
                if (RADIUS >= 260 && RADIUS <= 280)
                {
                    car1.x += 0.14;

                }
                if (RADIUS <= -80 && RADIUS >= -100)
                {
                    car1.x += 0.14;

                }
                /*8*/
                if (RADIUS <= -240 && RADIUS >= -260)
                {
                    speed += 0.00014;
                    car1.z += speed;
                    car1.x -= 0.091;
                }
                if (RADIUS >= 100 && RADIUS <= 120)
                {
                    speed += 0.00014;
                    car1.z += speed;
                    car1.x -= 0.091;
                }
                if (RADIUS >= 240 && RADIUS <= 260)
                {
                    speed += 0.00014;
                    car1.z += speed;
                    car1.x += 0.091;
                }
                if (RADIUS <= -100 && RADIUS >= -120)
                {
                    speed += 0.00014;
                    car1.z += speed;
                    car1.x += 0.091;
                }
                /*9*/
                if (RADIUS <= -220 && RADIUS >= -240)
                {
                    speed += 0.00028;
                    car1.z += speed;
                    car1.x -= 0.076;
                }
                if (RADIUS >= 120 && RADIUS <= 140)
                {
                    speed += 0.00028;
                    car1.z += speed;
                    car1.x -= 0.076;
                }
                if (RADIUS >= 220 && RADIUS <= 240)
                {
                    speed += 0.00028;
                    car1.z += speed;
                    car1.x += 0.078;
                }
                if (RADIUS <= -120 && RADIUS >= -140)
                {
                    speed += 0.00028;
                    car1.z += speed;
                    car1.x += 0.078;
                }
                /*10*/
                if (RADIUS <= -200 && RADIUS >= -220)
                {
                    speed += 0.00042;
                    car1.z += speed;
                    car1.x -= 0.07;
                }
                if (RADIUS >= 140 && RADIUS <= 160)
                {
                    speed += 0.00042;
                    car1.z += speed;
                    car1.x -= 0.07;
                }
                if (RADIUS <= -140 && RADIUS >= -160)
                {
                    speed += 0.00042;
                    car1.z += speed;
                    car1.x += 0.07;
                }
                if (RADIUS >= 200 && RADIUS <= 220)
                {
                    speed += 0.00042;
                    car1.z += speed;
                    car1.x += 0.07;
                }
                /*11*/
                if (RADIUS <= -190 && RADIUS >= -200)
                {
                    speed += 0.00056;
                    car1.z += speed;
                    car1.x -= 0.056;
                }
                if (RADIUS >= 160 && RADIUS <= 170)
                {
                    speed += 0.00056;
                    car1.z += speed;
                    car1.x -= 0.056;
                }
                if (RADIUS >= 190 && RADIUS <= 200)
                {
                    speed += 0.00056;
                    car1.z += speed;
                    car1.x += 0.056;
                }
                if (RADIUS <= -160 && RADIUS >= -170)
                {
                    speed += 0.00056;
                    car1.z += speed;
                    car1.x += 0.056;
                }
                /*12*/
                if (RADIUS <= -170 && RADIUS >= -190)
                {
                    speed += 0.00056;
                    car1.z += speed;
                }
                if (RADIUS >= 170 && RADIUS <= 190)
                {
                    speed += 0.00056;
                    car1.z += speed;
                }
                glutPostRedisplay();

            }
            if (KopAccident() == 0 || (car_Accident() == 0))//תנאי התנגשית כדי לחשב הניקידות של שחקן
            {
                life[0]--;
                if (life[0] >= '1')//מגיע ל 0 מפסיד 
                {
                    screen = 15;

                }

            }
            car_parking();
            if (car_move_Accident() == 0)
            {
                life[0]--;
                if (life[0] >= '1')
                {
                    screen = 15;

                }
            }
        }
        if (key == GLUT_KEY_DOWN)
        {
            speed = 0.05;
            if (KopAccident() == 1)
            {
                if (RADIUS <= 10 && RADIUS >= 0)
                {
                    speed += 0.0007;
                    car1.z += speed;
                }
                if (RADIUS >= -360 && RADIUS <= -350)
                {
                    speed += 0.0007;
                    car1.z += speed;
                }

                if (RADIUS >= -10 && RADIUS <= 0)
                {
                    speed += 0.0007;
                    car1.z += speed;
                }
                if (RADIUS <= 360 && RADIUS >= 350)
                {
                    speed += 0.0007;
                    car1.z += speed;
                }
                /*2*/
                if (RADIUS >= 10 && RADIUS <= 30)
                {
                    speed += 0.00056;
                    car1.z += speed;
                    car1.x += 0.056;
                }
                if (RADIUS <= -330 && RADIUS >= -350)
                {
                    speed += 0.00056;
                    car1.z += speed;
                    car1.x += 0.056;
                }
                if (RADIUS <= -10 && RADIUS >= -30)
                {
                    speed += 0.00056;
                    car1.z += speed;
                    car1.x -= 0.056;
                }
                if (RADIUS >= 330 && RADIUS <= 350)
                {
                    speed += 0.00056;
                    car1.z += speed;
                    car1.x -= 0.056;
                }
                /*3*/
                if (RADIUS >= 30 && RADIUS <= 50)
                {
                    speed += 0.00042;
                    car1.z += speed;
                    car1.x += 0.042;
                }
                if (RADIUS <= -310 && RADIUS >= -330)
                {
                    speed += 0.00042;
                    car1.z += speed;
                    car1.x += 0.042;
                }
                if (RADIUS >= 310 && RADIUS <= 330)
                {
                    speed += 0.00042;
                    car1.z += speed;
                    car1.x -= 0.07;
                }
                if (RADIUS <= -30 && RADIUS >= -50)
                {
                    speed += 0.00042;
                    car1.z += speed;
                    car1.x -= 0.07;
                }
                /*4*/
                if (RADIUS >= 50 && RADIUS <= 70)
                {
                    speed += 0.0002;
                    car1.z += speed;
                    car1.x += 0.07;
                }
                if (RADIUS <= -290 && RADIUS >= -310)
                {
                    speed += 0.0002;
                    car1.z += speed;
                    car1.x += 0.07;
                }
                if (RADIUS <= -50 && RADIUS >= -70)
                {
                    speed += 0.00028;
                    car1.z += speed;
                    car1.x -= 0.098;
                }
                if (RADIUS >= 290 && RADIUS <= 310)
                {
                    speed += 0.00028;
                    car1.z += speed;
                    car1.x -= 0.098;
                }
                /*5*/
                if (RADIUS >= 70 && RADIUS <= 80)
                {
                    speed += 0.00014;
                    car1.z += speed;
                    car1.x += 0.09;
                }
                if (RADIUS <= -280 && RADIUS >= -290)
                {
                    speed += 0.00014;
                    car1.z += speed;
                    car1.x += 0.09;
                }
                if (RADIUS <= -70 && RADIUS >= -80)
                {
                    speed += 0.00014;
                    car1.z += speed;
                    car1.x -= 0.09;
                }
                if (RADIUS <= 280 && RADIUS >= 290)
                {
                    speed += 0.00014;
                    car1.z += speed;
                    car1.x -= 0.09;
                }
                /*6*/
                if (RADIUS >= 80 && RADIUS <= 100)
                {
                    car1.x += 0.14;

                }
                if (RADIUS <= -260 && RADIUS >= -280)
                {
                    car1.x += 0.14;

                }
                /*7*/
                if (RADIUS <= -80 && RADIUS >= -100)
                {
                    car1.x -= 0.14;

                }
                if (RADIUS <= -80 && RADIUS >= -100)
                {
                    car1.x -= 0.14;

                }
                /*8*/
                if (RADIUS >= 100 && RADIUS <= 120)
                {
                    speed += 0.00014;
                    car1.z -= speed;
                    car1.x += 0.09;
                }
                if (RADIUS <= -240 && RADIUS >= -260)
                {
                    speed += 0.00014;
                    car1.z -= speed;
                    car1.x += 0.09;
                }
                if (RADIUS <= -100 && RADIUS >= -120)
                {
                    speed += 0.00014;
                    car1.z -= speed;
                    car1.x -= 0.09;
                }
                if (RADIUS >= 240 && RADIUS <= 260)
                {
                    speed += 0.00014;
                    car1.z -= speed;
                    car1.x -= 0.09;
                }
                /*9*/
                if (RADIUS >= 120 && RADIUS <= 140)
                {
                    speed += 0.00028;
                    car1.z -= speed;
                    car1.x += 0.07;
                }
                if (RADIUS <= -220 && RADIUS >= -240)
                {
                    speed += 0.00028;
                    car1.z -= speed;
                    car1.x += 0.07;
                }
                if (RADIUS <= -120 && RADIUS >= -140)
                {
                    speed += 0.00028;
                    car1.z -= speed;
                    car1.x -= 0.07;
                }
                if (RADIUS >= 220 && RADIUS <= 240)
                {
                    speed += 0.00028;
                    car1.z -= speed;
                    car1.x -= 0.07;
                }
                /*10*/
                if (RADIUS >= 140 && RADIUS <= 160)
                {
                    speed += 0.00042;
                    car1.z -= speed;
                    car1.x += 0.07;
                }
                if (RADIUS <= -200 && RADIUS >= -220)
                {
                    speed += 0.00042;
                    car1.z -= speed;
                    car1.x += 0.07;
                }
                if (RADIUS <= -140 && RADIUS >= -160)
                {
                    speed += 0.00042;
                    car1.z -= speed;
                    car1.x -= 0.07;
                }
                if (RADIUS >= 200 && RADIUS <= 220)
                {
                    speed += 0.00042;
                    car1.z -= speed;
                    car1.x -= 0.07;
                }
                /*11*/
                if (RADIUS >= 160 && RADIUS <= 170)
                {
                    speed += 0.00056;
                    car1.z -= speed;
                    car1.x += 0.056;
                }
                if (RADIUS <= -190 && RADIUS >= -200)
                {
                    speed += 0.00056;
                    car1.z -= speed;
                    car1.x += 0.056;
                }
                if (RADIUS >= 190 && RADIUS <= 200)
                {
                    speed += 0.00056;
                    car1.z -= speed;
                    car1.x -= 0.056;
                }
                if (RADIUS <= -160 && RADIUS >= -170)
                {
                    speed += 0.00056;
                    car1.z -= speed;
                    car1.x -= 0.056;
                }
                /*12*/
                if (RADIUS >= 170 && RADIUS <= 190)
                {
                    speed += 0.0007;
                    car1.z -= speed;
                }
                if (RADIUS <= -170 && RADIUS >= -190)
                {
                    speed += 0.0007;
                    car1.z -= speed;
                }
                glutPostRedisplay();
            }
            if (KopAccident() == 0 || (car_Accident() == 0))
            {
                life[0]--;
                if (life[0] >= '1')
                {
                    screen = 15;

                }

            }
            car_parking();


        }
        if (key == GLUT_KEY_LEFT)
        {
            speed = 0.01;
            if (KopAccident() == 1)
            {
                car1.x = car1.x + ((3 * (cos((LEFT - 1.0) * pi / 180))) - (3 * (cos(LEFT * pi / 180))));
                car1.z = car1.z + ((3 * (sin((LEFT - 1.0) * pi / 180))) - (3 * (sin(LEFT * pi / 180))));
                LEFT -= 1;
                RADIUS += 1;
                RIGHT -= 1;
                glutPostRedisplay();

            }
            if (KopAccident() == 0 || (car_Accident() == 0))
            {
                life[0]--;
                if (life[0] >= '1')
                {
                    screen = 15;

                }

            }
            car_parking();

        }
        if (key == GLUT_KEY_RIGHT)
        {
            speed = 0.01;
            if (KopAccident() == 1)
            {
                car1.x = car1.x - ((3 * (cos((RIGHT - 1.0) * pi / 180))) - (3 * (cos(RIGHT * pi / 180))));
                car1.z = car1.z - ((3 * (sin((RIGHT - 1.0) * pi / 180))) - (3 * (sin(RIGHT * pi / 180))));
                RADIUS -= 1;
                RIGHT += 1;
                LEFT += 1;
                glutPostRedisplay();

            }
            if (KopAccident() == 0 || (car_Accident() == 0))
            {
                life[0]--;
                if (life[0] >= '1')
                {
                    screen = 15;

                }

            }
            car_parking();

        }
        if (RADIUS == 360 || RADIUS == -360)
        {
            RADIUS = 0;
        }
    }





}
void keyboard(unsigned char key, int x, int y) //פונקציה לוח המקשים להעברה בין מסכים 
{
    if (screen == 15)
    {
        t1 = time(NULL);
        car1.z = 0;
        car1.x = 0;
        RADIUS = 0; //setting car rotation straight
        LEFT = 0; //left angel direction
        RIGHT = -180; //used to help turn the car left and right 
        v = 0.005;
        if (key == '\r')
        {
            if (levelstage == 1)
            {
                screen = 3;
            }
            if (levelstage == 2)
            {
                screen = 11;
            }
            if (levelstage == 3)
            {
                screen = 12;
            }
            if (levelstage == 4)
            {
                screen = 16;
            }
        }


    }
    if (screen == 10)
    {
        if (key == '\r')
        {
            screen = 8;
        }
    }
    if (screen == 4)
    {
        t1 = time(NULL);

        if (key == '\r')
        {
            if (strOfUserlevel[0] == '2')
            {

                flag_level = false;
                screen = 11;

            }
            if (strOfUserlevel[0] == '3')
            {
                car2.x = 22.5;
                car2.z = 16;
                flag_level = false;
                screen = 12;

            }
            if (strOfUserlevel[0] == '4')
            {
                flag_level = false;
                car2.x = -28.3;
                car2.z = 16;
                screen = 16;

            }
            if (strOfUserlevel[0] == '4')
            {
                flag_level = false;
                car3.x = -12.5;
                car3.z = -5;
                screen = 16;

            }
        }

        if (key == '2')screen = 3;
    }


    if (screen == 0)
    {
        if (key == '\r')screen = 6;
        if (key == '1')screen = 1;
    }


    if (screen == 6)
    {
        if (key == '2')screen = 5;
        if (key == '1')screen = 7;
    }
    if (screen == 8)
    {
        if (key == '1')
        {
            Reset_level();
            t1 = time(NULL);
            car1.z = 0;
            car1.x = 0;
            RADIUS = 0; //setting car rotation straight
            LEFT = 0; //left angel direction
            RIGHT = -180; //used to help turn the car left and right 
            v = 0.005;

            flag_level = false;
            screen = 3;


        }
        if (key == '2')
        {
            t1 = time(NULL);
            car1.z = 0;
            car1.x = 0;
            RADIUS = 0; //setting car rotation straight
            LEFT = 0; //left angel direction
            RIGHT = -180; //used to help turn the car left and right 
            v = 0.005;
            if (strOfUserlevel[0] == '1')
            {
                screen = 3;
            }
            if (strOfUserlevel[0] == '2')
            {
                screen = 11;
            }
            if (strOfUserlevel[0] == '3')
            {

                car2.x = 22.5;
                car2.z = 16;
                screen = 12;
            }
            if (strOfUserlevel[0] == '4')
            {

                car2.x = -28.3;
                car2.z = 16;
                car3.x = -12.5;
                car3.z = -5;
                screen = 16;
            }

        }
        if (key == '3')
        {
            screen = 14;
        }
    }
    if (name == true)
    {
        if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '1' && key <= '9'))
            if (indexOfUserName < 10) {
                strOfUserName[indexOfUserName++] = key;

                strOfUserName[indexOfUserName] = '\0';
            }
    }
    if (pass == true)
    {
        if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '1' && key <= '9'))
            if (indexOfUserNamePass < 10) {
                strOfUserNamepass[indexOfUserNamePass++] = key;
                strOfUserNamepass[indexOfUserNamePass] = '\0';
            }
    }

    if (screen == 5)
    {
        if (key == '\r')
        {
            OpenFile(1);
        }

    }
    if (screen == 7)
    {
        if (key == '\r')
        {
            OpenFile(2);
        }
    }


    if (key == 27) exit(1);

    glutPostRedisplay();
}
void compileStrings(float x, float y, const char* str)//פונקציה כתיבת מחרוזת 
{
    int len, i;
    glColor3f(1, 0, 1);
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }
}
void car_parking()//פונקציה הבודקת אם הרכב חנה במקום המובקש כדי לעבור לשבל הבא 
{
    if (car1.x >= parking1.x - 1.5 && car1.x <= parking1.x + 1.5 && car1.z+ 35.0 >= parking1.z - 1.5 && car1.z+ 35.0 <= parking1.z + 1.5)
    {
        if (screen == 3)
        {
            screen = 4;
            levelstage = 2;
        }
        if (screen == 11)
        {
            screen = 4;
        }
        if (screen == 12)
        {
            screen = 4;
        }
        if (screen == 16)
        {
            screen = 13;
        }
    }



}
int car_Accident()//פונקציה בודק פגיעות מחזירה 0 אם נגע 1 לא נגע 
{
    for (int j = 0; j < 13; j++)
    {

        if ((RADIUS >= 60 && RADIUS <= 120 || RADIUS <= -60 && RADIUS >= -120) || (RADIUS >= 240 && RADIUS <= 300 || RADIUS <= -240 && RADIUS >= -300))
        {
            if (car1.x >= cars[j].x - 5.2 && car1.x <= cars[j].x + 5.2 && car1.z+ 35.0 >= cars[j].z - 3.5 && car1.z+ 35.0 <= cars[j].z + 3.5) {

                return 0;
            }
        }

        if (((RADIUS >= 0 && RADIUS <60 || RADIUS > -360 && RADIUS < -300) || (RADIUS <= -0 && RADIUS > -60 || RADIUS < 360 && RADIUS > 300)) ||
            (RADIUS >= 120 && RADIUS < 240 || RADIUS < -120 && RADIUS > -240))
        {
            if (car1.x >= cars[j].x - 4 && car1.x <= cars[j].x + 4 && car1.z + 35 >= cars[j].z - 6 && car1.z + 35 <= cars[j].z + 6) {


                return 0;
            }

        }
    }
    return 1;
}
int car_move_Accident()// פונקציה מתאימה לשלב 3 ו 4 יש רכביים הם זזו לעקב חניה המוכנית
{
    if ((RADIUS >= 60 && RADIUS <= 120 || RADIUS <= -60 && RADIUS >= -120) || (RADIUS >= 240 && RADIUS <= 300 || RADIUS <= -240 && RADIUS >= -300))
    {
        if (screen == 12 || screen == 16)
        {
            if (car1.x >= car2.x - 5.2 && car1.x <= car2.x + 5.2 && car1.z + 35 >= car2.z - 5 && car1.z + 35 <= car2.z + 5)
                return 0;
        }
        if ((RADIUS >= 60 && RADIUS <= 120 || RADIUS <= -60 && RADIUS >= -120) || (RADIUS >= 240 && RADIUS <= 300 || RADIUS <= -240 && RADIUS >= -300))
            if (screen == 16)
            {
                if (car1.x >= car3.x - 5.2 && car1.x <= car3.x + 5.2 && car1.z + 35 >= car3.z - 5 && car1.z + 35 <= car3.z + 5)
                    return 0;
            }

    }


    return 1;
}
void Reset_level()
{
    FILE* file;//מצביע לקובץ
    strOfUserlevel[0] = '1';
    strOfUserlevel[1] = '\0';
    file = fopen(strOfUserName, "a");
    remove("file");
    file = fopen(strOfUserName, "w+");
    strOfUserNamepass[indexOfUserNamePass] = '\n';
    strOfUserNamepass[++indexOfUserNamePass] = '\0';
    fputs(strOfUserNamepass, file);
    fputs(strOfUserlevel, file);
    fclose(file);

}
void timePrintOnScreen()//פונקציה הזמן 
{

    compileStrings(-47, 70, "your time:      sec");
    if (t2 - t1 <= 9)
    {
        timeprint[0] = 48 + (t2 - t1);
        timeprint[1] = '\0';
        glRasterPos2f(-38, 70);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, timeprint[0]);
    }
    if (t2 - t1 >= 10 && t2 - t1 <= 19)
    {
        timeprint[0] = '1';
        timeprint[1] = 48 + (t2 - t1) - 10;
        timeprint[2] = '\0';
        glRasterPos2f(-38, 70);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, timeprint[0]);
        glRasterPos2f(-37, 70);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, timeprint[1]);
    }
    if (t2 - t1 >= 20 && t2 - t1 <= 29)
    {
        timeprint[0] = '2';
        timeprint[1] = 48 + (t2 - t1) - 20;
        timeprint[2] = '\0';
        glRasterPos2f(-38, 70);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, timeprint[0]);
        glRasterPos2f(-37, 70);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, timeprint[1]);
    }
    if (t2 - t1 >= 30 && t2 - t1 <= 39)
    {
        timeprint[0] = '3';
        timeprint[1] = 48 + (t2 - t1) - 30;
        timeprint[2] = '\0';
        glRasterPos2f(-38, 70);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, timeprint[0]);
        glRasterPos2f(-37, 70);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, timeprint[1]);
    }
    if (t2 - t1 >= 40 && t2 - t1 <= 49)
    {
        timeprint[0] = '4';
        timeprint[1] = 48 + (t2 - t1) - 40;
        timeprint[2] = '\0';
        glRasterPos2f(-38, 70);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, timeprint[0]);
        glRasterPos2f(-37, 70);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, timeprint[1]);
    }
    if (t2 - t1 >= 50 && t2 - t1 <= 59)
    {
        timeprint[0] = '5';
        timeprint[1] = 48 + (t2 - t1) - 50;
        timeprint[2] = '\0';
        glRasterPos2f(-38, 70);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, timeprint[0]);
        glRasterPos2f(-37, 70);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, timeprint[1]);
    }
    glutPostRedisplay();
}
void home(float floors, float R, float G, float B, float x, float y, float z)//פונקציה ציור הבנינים  
{

    glBegin(GL_QUADS);
    // Front
    glColor3f(R, G, B);
    glVertex3f(-4 + x, 0 + y, 4 + z);
    glVertex3f(-4 + x, (floors * 2) + 1 + y, 4 + z);
    glVertex3f(4 + x, (floors * 2) + 1 + y, 4 + z);
    glVertex3f(4 + x, 0 + y, 4 + z);



    for (float m3ka = -3.8; m3ka < 4; m3ka += 0.6)
    {
        glColor3f(0.329412, 0.329412, 0.329412);
        glVertex3f(m3ka + x, (floors * 2) + 1 + y, 4 + z);
        glVertex3f(m3ka + x, (floors * 2) + 1.8 + y, 4 + z);
        glVertex3f(m3ka - 0.2 + x, (floors * 2) + 1.8 + y, 4 + z);
        glVertex3f(m3ka - 0.2 + x, (floors * 2) + 1 + y, 4 + z);
    }

    glColor3f(0.329412, 0.329412, 0.329412);
    glVertex3f(-4 + x, (floors * 2) + 1.8 + y, 4 + z);
    glVertex3f(-4 + x, (floors * 2) + 1.9 + y, 4 + z);
    glVertex3f(4 + x, (floors * 2) + 1.9 + y, 4 + z);
    glVertex3f(4 + x, (floors * 2) + 1.8 + y, 4 + z);


    /****************************/
    //door
    glColor3f(0.35, 0.16, 0.14);
    glVertex3f(-0.5 + x, 0 + y, 4.2f + z);
    glVertex3f(-0.5 + x, 1.5 + y, 4.2f + z);
    glVertex3f(0.5 + x, 1.5 + y, 4.2f + z);
    glVertex3f(0.5 + x, 0 + y, 4.2f + z);
    ////
    glColor3f(0.329412, 0.329412, 0.329412);
    glVertex3f(-0.5 + x, 0 + y, 4.2 + z);
    glVertex3f(-0.5 + x, 1.5 + y, 4.2 + z);
    glVertex3f(-0.7 + x, 1.7 + y, 4 + z);
    glVertex3f(-0.7 + x, 0 + y, 4 + z);

    glColor3f(0.329412, 0.329412, 0.329412);
    glVertex3f(0.5 + x, 0 + y, 4.2 + z);
    glVertex3f(0.5 + x, 1.5 + y, 4.2 + z);
    glVertex3f(0.7 + x, 1.7 + y, 4 + z);
    glVertex3f(0.7 + x, 0 + y, 4 + z);

    glColor3f(0.329412, 0.329412, 0.329412);
    glVertex3f(-0.5 + x, 1.5 + y, 4.2 + z);
    glVertex3f(0.5 + x, 1.5 + y, 4.2 + z);
    glVertex3f(0.7 + x, 1.7 + y, 4 + z);
    glVertex3f(-0.7 + x, 1.7 + y, 4 + z);

    //Window
    for (float i = 1, n = 0; i < (floors * 2); i += 2, n += 2)
    {     //Window left side
        glColor3f(1, 1, 1);
        glVertex3f(-1.5 + x, i + y, 4.2f + z);
        glVertex3f(-1.5 + x, i + 1 + y, 4.2f + z);
        glVertex3f(-3.0 + x, i + 1 + y, 4.2f + z);
        glVertex3f(-3.0 + x, i + y, 4.2f + z);
        ///
        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(-1.3 + x, n + 2.2 + y, 4.0f + z);
        glVertex3f(-1.5 + x, n + 2 + y, 4.2f + z);
        glVertex3f(-3.0 + x, n + 2 + y, 4.2f + z);
        glVertex3f(-3.2 + x, n + 2.2 + y, 4.0f + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(-1.3 + x, n + 0.8 + y, 4.0f + z);
        glVertex3f(-1.5 + x, n + 1 + y, 4.2f + z);
        glVertex3f(-3.0 + x, n + 1 + y, 4.2f + z);
        glVertex3f(-3.2 + x, n + 0.8 + y, 4.0f + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(-3.2 + x, n + 0.8 + y, 4.0f + z);
        glVertex3f(-3.2 + x, n + 2.2 + y, 4.0f + z);
        glVertex3f(-3.0 + x, n + 2 + y, 4.2f + z);
        glVertex3f(-3.0 + x, n + 1 + y, 4.2f + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(-1.3 + x, n + 0.8 + y, 4.0f + z);
        glVertex3f(-1.3 + x, n + 2.2 + y, 4.0f + z);
        glVertex3f(-1.5 + x, n + 2 + y, 4.2f + z);
        glVertex3f(-1.5 + x, n + 1 + y, 4.2f + z);
        //Window Right side
        glColor3f(1, 1, 1);
        glVertex3f(1.5 + x, i + y, 4.2f + z);
        glVertex3f(1.5 + x, i + 1 + y, 4.2f + z);
        glVertex3f(3.0 + x, i + 1 + y, 4.2f + z);
        glVertex3f(3.0 + x, i + y, 4.2f + z);
        ///
        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(1.3 + x, n + 2.2 + y, 4.0f + z);
        glVertex3f(1.5 + x, n + 2 + y, 4.2f + z);
        glVertex3f(3.0 + x, n + 2 + y, 4.2f + z);
        glVertex3f(3.2 + x, n + 2.2 + y, 4.0f + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(1.3 + x, n + 0.8 + y, 4.0f + z);
        glVertex3f(1.5 + x, n + 1 + y, 4.2f + z);
        glVertex3f(3.0 + x, n + 1 + y, 4.2f + z);
        glVertex3f(3.2 + x, n + 0.8 + y, 4.0f + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(3.2 + x, n + 0.8 + y, 4.0f + z);
        glVertex3f(3.2 + x, n + 2.2 + y, 4.0f + z);
        glVertex3f(3.0 + x, n + 2 + y, 4.2f + z);
        glVertex3f(3.0 + x, n + 1 + y, 4.2f + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(1.3 + x, n + 0.8 + y, 4.0f + z);
        glVertex3f(1.3 + x, n + 2.2 + y, 4.0f + z);
        glVertex3f(1.5 + x, n + 2 + y, 4.2f + z);
        glVertex3f(1.5 + x, n + 1 + y, 4.2f + z);
    }

    /***************************/
    // Back
    glColor3f(R, G, B);
    glVertex3f(-4 + x, 0 + y, -4 + z);
    glVertex3f(4 + x, 0 + y, -4 + z);
    glVertex3f(4 + x, (floors * 2) + 1 + y, -4 + z);
    glVertex3f(-4 + x, (floors * 2) + 1 + y, -4 + z);
    //????
    for (float m3ka = -3.8; m3ka < 4; m3ka += 0.6)
    {
        glColor3f(0.329412, 0.329412, 0.329412);
        glVertex3f(m3ka + x, (floors * 2) + 1 + y, -4 + z);
        glVertex3f(m3ka + x, (floors * 2) + 1.8 + y, -4 + z);
        glVertex3f(m3ka - 0.2 + x, (floors * 2) + 1.8 + y, -4 + z);
        glVertex3f(m3ka - 0.2 + x, (floors * 2) + 1 + y, -4 + z);
    }

    glColor3f(0.329412, 0.329412, 0.329412);
    glVertex3f(-4 + x, (floors * 2) + 1.8 + y, -4 + z);
    glVertex3f(-4 + x, (floors * 2) + 1.9 + y, -4 + z);
    glVertex3f(4 + x, (floors * 2) + 1.9 + y, -4 + z);
    glVertex3f(4 + x, (floors * 2) + 1.8 + y, -4 + z);

    //door
    glColor3f(0.35, 0.16, 0.14);
    glVertex3f(-0.5 + x, 0 + y, -4.2f + z);
    glVertex3f(-0.5 + x, 1.5 + y, -4.2f + z);
    glVertex3f(0.5 + x, 1.5 + y, -4.2f + z);
    glVertex3f(0.5 + x, 0 + y, -4.2f + z);
    ////
    glColor3f(0.329412, 0.329412, 0.329412);
    glVertex3f(-0.5 + x, 0 + y, -4.2 + z);
    glVertex3f(-0.5 + x, 1.5 + y, -4.2 + z);
    glVertex3f(-0.7 + x, 1.7 + y, -4 + z);
    glVertex3f(-0.7 + x, 0 + y, -4 + z);

    glColor3f(0.329412, 0.329412, 0.329412);
    glVertex3f(0.5 + x, 0 + y, -4.2 + z);
    glVertex3f(0.5 + x, 1.5 + y, -4.2 + z);
    glVertex3f(0.7 + x, 1.7 + y, -4 + z);
    glVertex3f(0.7 + x, 0 + y, -4 + z);

    glColor3f(0.329412, 0.329412, 0.329412);
    glVertex3f(-0.5 + x, 1.5 + y, -4.2 + z);
    glVertex3f(0.5 + x, 1.5 + y, -4.2 + z);
    glVertex3f(0.7 + x, 1.7 + y, -4 + z);
    glVertex3f(-0.7 + x, 1.7 + y, -4 + z);
    //////////////////////////////////////////
    for (float i = 1, n = 0; i < (floors * 2); i += 2, n += 2)
    {     //Window left side
        glColor3f(1, 1, 1);
        glVertex3f(-1.5 + x, i + y, -4.2f + z);
        glVertex3f(-1.5 + x, i + 1 + y, -4.2f + z);
        glVertex3f(-3.0 + x, i + 1 + y, -4.2f + z);
        glVertex3f(-3.0 + x, i + y, -4.2f + z);
        ///
        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(-1.3 + x, n + 2.2 + y, -4.0f + z);
        glVertex3f(-1.5 + x, n + 2 + y, -4.2f + z);
        glVertex3f(-3.0 + x, n + 2 + y, -4.2f + z);
        glVertex3f(-3.2 + x, n + 2.2 + y, -4.0f + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(-1.3 + x, n + 0.8 + y, -4.0f + z);
        glVertex3f(-1.5 + x, n + 1 + y, -4.2f + z);
        glVertex3f(-3.0 + x, n + 1 + y, -4.2f + z);
        glVertex3f(-3.2 + x, n + 0.8 + y, -4.0f + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(-3.2 + x, n + 0.8 + y, -4.0f + z);
        glVertex3f(-3.2 + x, n + 2.2 + y, -4.0f + z);
        glVertex3f(-3.0 + x, n + 2 + y, -4.2f + z);
        glVertex3f(-3.0 + x, n + 1 + y, -4.2f + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(-1.3 + x, n + 0.8 + y, -4.0f + z);
        glVertex3f(-1.3 + x, n + 2.2 + y, -4.0f + z);
        glVertex3f(-1.5 + x, n + 2 + y, -4.2f + z);
        glVertex3f(-1.5 + x, n + 1 + y, -4.2f + z);
        //Window Right side
        glColor3f(1, 1, 1);
        glVertex3f(1.5 + x, i + y, -4.2f + z);
        glVertex3f(1.5 + x, i + 1 + y, -4.2f + z);
        glVertex3f(3.0 + x, i + 1 + y, -4.2f + z);
        glVertex3f(3.0 + x, i + y, -4.2f + z);
        ///
        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(1.3 + x, n + 2.2 + y, -4.0f + z);
        glVertex3f(1.5 + x, n + 2 + y, -4.2f + z);
        glVertex3f(3.0 + x, n + 2 + y, -4.2f + z);
        glVertex3f(3.2 + x, n + 2.2 + y, -4.0f + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(1.3 + x, n + 0.8 + y, -4.0f + z);
        glVertex3f(1.5 + x, n + 1 + y, -4.2f + z);
        glVertex3f(3.0 + x, n + 1 + y, -4.2f + z);
        glVertex3f(3.2 + x, n + 0.8 + y, -4.0f + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(3.2 + x, n + 0.8 + y, -4.0f + z);
        glVertex3f(3.2 + x, n + 2.2 + y, -4.0f + z);
        glVertex3f(3.0 + x, n + 2 + y, -4.2f + z);
        glVertex3f(3.0 + x, n + 1 + y, -4.2f + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(1.3 + x, n + 0.8 + y, -4.0f + z);
        glVertex3f(1.3 + x, n + 2.2 + y, -4.0f + z);
        glVertex3f(1.5 + x, n + 2 + y, -4.2f + z);
        glVertex3f(1.5 + x, n + 1 + y, -4.2f + z);
    }

    // Left side
    glColor3f(R, G, B);
    glVertex3f(-4 + x, 0 + y, 4 + z);
    glVertex3f(-4 + x, 0 + y, -4 + z);
    glVertex3f(-4 + x, (floors * 2) + 1 + y, -4 + z);
    glVertex3f(-4 + x, (floors * 2) + 1 + y, 4 + z);
    //????
    for (float m3ka = -3.8; m3ka < 4; m3ka += 0.6)
    {
        glColor3f(0.329412, 0.329412, 0.329412);
        glVertex3f(-4 + x, (floors * 2) + 1 + y, m3ka + z);
        glVertex3f(-4 + x, (floors * 2) + 1.8 + y, m3ka + z);
        glVertex3f(-4 + x, (floors * 2) + 1.8 + y, m3ka - 0.2 + z);
        glVertex3f(-4 + x, (floors * 2) + 1 + y, m3ka - 0.2 + z);
    }

    glColor3f(0.329412, 0.329412, 0.329412);
    glVertex3f(-4 + x, (floors * 2) + 1.8 + y, -4 + z);
    glVertex3f(-4 + x, (floors * 2) + 1.9 + y, -4 + z);
    glVertex3f(-4 + x, (floors * 2) + 1.9 + y, 4 + z);
    glVertex3f(-4 + x, (floors * 2) + 1.8 + y, 4 + z);
    //////
    //door
    glColor3f(0.35, 0.16, 0.14);
    glVertex3f(-4.2f + x, 0 + y, -0.5 + z);
    glVertex3f(-4.2f + x, 1.5 + y, -0.5 + z);
    glVertex3f(-4.2f + x, 1.5 + y, 0.5 + z);
    glVertex3f(-4.2f + x, 0 + y, 0.5 + z);
    ////
    glColor3f(0.329412, 0.329412, 0.329412);
    glVertex3f(-4.2 + x, 0 + y, -0.5 + z);
    glVertex3f(-4.2 + x, 1.5 + y, -0.5 + z);
    glVertex3f(-4 + x, 1.7 + y, -0.7 + z);
    glVertex3f(-4 + x, 0 + y, -0.7 + z);

    glColor3f(0.329412, 0.329412, 0.329412);
    glVertex3f(-4.2 + x, 0 + y, 0.5 + z);
    glVertex3f(-4.2 + x, 1.5 + y, 0.5 + z);
    glVertex3f(-4 + x, 1.7 + y, 0.7 + z);
    glVertex3f(-4 + x, 0 + y, 0.7 + z);

    glColor3f(0.329412, 0.329412, 0.329412);
    glVertex3f(-4.2 + x, 1.5 + y, -0.5 + z);
    glVertex3f(-4.2 + x, 1.5 + y, 0.5 + z);
    glVertex3f(-4 + x, 1.7 + y, 0.7 + z);
    glVertex3f(-4 + x, 1.7 + y, -0.7 + z);
    ////////////////////////////////////
    for (float i = 1, n = 0; i < (floors * 2); i += 2, n += 2)
    {     //Window left side
        glColor3f(1, 1, 1);
        glVertex3f(-4.2f + x, i + y, -1.5 + z);
        glVertex3f(-4.2f + x, i + 1 + y, -1.5 + z);
        glVertex3f(-4.2f + x, i + 1 + y, -3.0 + z);
        glVertex3f(-4.2f + x, i + y, -3.0 + z);
        ///
        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(-4.0f + x, n + 2.2 + y, -1.3 + z);
        glVertex3f(-4.2f + x, n + 2 + y, -1.5 + z);
        glVertex3f(-4.2f + x, n + 2 + y, -3.0 + z);
        glVertex3f(-4.0f + x, n + 2.2 + y, -3.2 + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(-4.0f + x, n + 0.8 + y, -1.3 + z);
        glVertex3f(-4.2f + x, n + 1 + y, -1.5 + z);
        glVertex3f(-4.2f + x, n + 1 + y, -3.0 + z);
        glVertex3f(-4.0f + x, n + 0.8 + y, -3.2 + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(-4.0f + x, n + 0.8 + y, -3.2 + z);
        glVertex3f(-4.0f + x, n + 2.2 + y, -3.2 + z);
        glVertex3f(-4.2f + x, n + 2 + y, -3.0 + z);
        glVertex3f(-4.2f + x, n + 1 + y, -3.0 + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(-4.0f + x, n + 0.8 + y, -1.3 + z);
        glVertex3f(-4.0f + x, n + 2.2 + y, -1.3 + z);
        glVertex3f(-4.2f + x, n + 2 + y, -1.5 + z);
        glVertex3f(-4.2f + x, n + 1 + y, -1.5 + z);
        //Window Right side
        glColor3f(1, 1, 1);
        glVertex3f(-4.2f + x, i + y, 1.5 + z);
        glVertex3f(-4.2f + x, i + 1 + y, 1.5 + z);
        glVertex3f(-4.2f + x, i + 1 + y, 3.0 + z);
        glVertex3f(-4.2f + x, i + y, 3.0 + z);
        ///
        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(-4.0f + x, n + 2.2 + y, 1.3 + z);
        glVertex3f(-4.2f + x, n + 2 + y, 1.5 + z);
        glVertex3f(-4.2f + x, n + 2 + y, 3.0 + z);
        glVertex3f(-4.0f + x, n + 2.2 + y, 3.2 + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(-4.0f + x, n + 0.8 + y, 1.3 + z);
        glVertex3f(-4.2f + x, n + 1 + y, 1.5 + z);
        glVertex3f(-4.2f + x, n + 1 + y, 3.0 + z);
        glVertex3f(-4.0f + x, n + 0.8 + y, 3.2 + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(-4.0f + x, n + 0.8 + y, 3.2 + z);
        glVertex3f(-4.0f + x, n + 2.2 + y, 3.2 + z);
        glVertex3f(-4.2f + x, n + 2 + y, 3.0 + z);
        glVertex3f(-4.2f + x, n + 1 + y, 3.0 + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(-4.0f + x, n + 0.8 + y, 1.3 + z);
        glVertex3f(-4.0f + x, n + 2.2 + y, 1.3 + z);
        glVertex3f(-4.2f + x, n + 2 + y, 1.5 + z);
        glVertex3f(-4.2f + x, n + 1 + y, 1.5 + z);
    }

    /////// Right side
    glColor3f(R, G, B);
    glVertex3f(4 + x, 0 + y, 4 + z);
    glVertex3f(4 + x, 0 + y, -4 + z);
    glVertex3f(4 + x, (floors * 2) + 1 + y, -4 + z);
    glVertex3f(4 + x, (floors * 2) + 1 + y, 4 + z);
    //????
    for (float m3ka = -3.8; m3ka < 4; m3ka += 0.6)
    {
        glColor3f(0.329412, 0.329412, 0.329412);
        glVertex3f(4 + x, (floors * 2) + 1 + y, m3ka + z);
        glVertex3f(4 + x, (floors * 2) + 1.8 + y, m3ka + z);
        glVertex3f(4 + x, (floors * 2) + 1.8 + y, m3ka - 0.2 + z);
        glVertex3f(4 + x, (floors * 2) + 1 + y, m3ka - 0.2 + z);
    }

    glColor3f(0.329412, 0.329412, 0.329412);
    glVertex3f(4 + x, (floors * 2) + 1.8 + y, -4 + z);
    glVertex3f(4 + x, (floors * 2) + 1.9 + y, -4 + z);
    glVertex3f(4 + x, (floors * 2) + 1.9 + y, 4 + z);
    glVertex3f(4 + x, (floors * 2) + 1.8 + y, 4 + z);
    //////
    //door
    glColor3f(0.35, 0.16, 0.14);
    glVertex3f(4.2f + x, 0 + y, -0.5 + z);
    glVertex3f(4.2f + x, 1.5 + y, -0.5 + z);
    glVertex3f(4.2f + x, 1.5 + y, 0.5 + z);
    glVertex3f(4.2f + x, 0 + y, 0.5 + z);
    ////
    glColor3f(0.329412, 0.329412, 0.329412);
    glVertex3f(4.2 + x, 0 + y, -0.5 + z);
    glVertex3f(4.2 + x, 1.5 + y, -0.5 + z);
    glVertex3f(4 + x, 1.7 + y, -0.7 + z);
    glVertex3f(4 + x, 0 + y, -0.7 + z);

    glColor3f(0.329412, 0.329412, 0.329412);
    glVertex3f(4.2 + x, 0 + y, 0.5 + z);
    glVertex3f(4.2 + x, 1.5 + y, 0.5 + z);
    glVertex3f(4 + x, 1.7 + y, 0.7 + z);
    glVertex3f(4 + x, 0 + y, 0.7 + z);

    glColor3f(0.329412, 0.329412, 0.329412);
    glVertex3f(4.2 + x, 1.5 + y, -0.5 + z);
    glVertex3f(4.2 + x, 1.5 + y, 0.5 + z);
    glVertex3f(4 + x, 1.7 + y, 0.7 + z);
    glVertex3f(4 + x, 1.7 + y, -0.7 + z);
    ////////////////////////////////////
    for (float i = 1, n = 0; i < floors * 2; i += 2, n += 2)
    {     //Window left side
        glColor3f(1, 1, 1);
        glVertex3f(4.2f + x, i + y, -1.5 + z);
        glVertex3f(4.2f + x, i + 1 + y, -1.5 + z);
        glVertex3f(4.2f + x, i + 1 + y, -3.0 + z);
        glVertex3f(4.2f + x, i + y, -3.0 + z);
        ///
        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(4.0f + x, n + 2.2 + y, -1.3 + z);
        glVertex3f(4.2f + x, n + 2 + y, -1.5 + z);
        glVertex3f(4.2f + x, n + 2 + y, -3.0 + z);
        glVertex3f(4.0f + x, n + 2.2 + y, -3.2 + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(4.0f + x, n + 0.8 + y, -1.3 + z);
        glVertex3f(4.2f + x, n + 1 + y, -1.5 + z);
        glVertex3f(4.2f + x, n + 1 + y, -3.0 + z);
        glVertex3f(4.0f + x, n + 0.8 + y, -3.2 + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(4.0f + x, n + 0.8 + y, -3.2 + z);
        glVertex3f(4.0f + x, n + 2.2 + y, -3.2 + z);
        glVertex3f(4.2f + x, n + 2 + y, -3.0 + z);
        glVertex3f(4.2f + x, n + 1 + y, -3.0 + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(4.0f + x, n + 0.8 + y, -1.3 + z);
        glVertex3f(4.0f + x, n + 2.2 + y, -1.3 + z);
        glVertex3f(4.2f + x, n + 2 + y, -1.5 + z);
        glVertex3f(4.2f + x, n + 1 + y, -1.5 + z);
        //Window Right side
        glColor3f(1, 1, 1);
        glVertex3f(4.2f + x, i + y, 1.5 + z);
        glVertex3f(4.2f + x, i + 1 + y, 1.5 + z);
        glVertex3f(4.2f + x, i + 1 + y, 3.0 + z);
        glVertex3f(4.2f + x, i + y, 3.0 + z);
        ///
        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(4.0f + x, n + 2.2 + y, 1.3 + z);
        glVertex3f(4.2f + x, n + 2 + y, 1.5 + z);
        glVertex3f(4.2f + x, n + 2 + y, 3.0 + z);
        glVertex3f(4.0f + x, n + 2.2 + y, 3.2 + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(4.0f + x, n + 0.8 + y, 1.3 + z);
        glVertex3f(4.2f + x, n + 1 + y, 1.5 + z);
        glVertex3f(4.2f + x, n + 1 + y, 3.0 + z);
        glVertex3f(4.0f + x, n + 0.8 + y, 3.2 + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(4.0f + x, n + 0.8 + y, 3.2 + z);
        glVertex3f(4.0f + x, n + 2.2 + y, 3.2 + z);
        glVertex3f(4.2f + x, n + 2 + y, 3.0 + z);
        glVertex3f(4.2f + x, n + 1 + y, 3.0 + z);

        glColor3f(0.35, 0.16, 0.14);
        glVertex3f(4.0f + x, n + 0.8 + y, 1.3 + z);
        glVertex3f(4.0f + x, n + 2.2 + y, 1.3 + z);
        glVertex3f(4.2f + x, n + 2 + y, 1.5 + z);
        glVertex3f(4.2f + x, n + 1 + y, 1.5 + z);
    }
    glEnd();

    //up
    glBegin(GL_QUADS);
    glColor3f(0.329412, 0.329412, 0.329412);
    glVertex3f(-4 + x, (floors * 2) + 1 + y, -4 + z);
    glVertex3f(4 + x, (floors * 2) + 1 + y, -4 + z);
    glVertex3f(4 + x, (floors * 2) + 1 + y, 4 + z);
    glVertex3f(-4 + x, (floors * 2) + 1 + y, 4 + z);
    glEnd();

}
void lightstreet(float x, float y, float z) //פונקצית אורות השכונה בתוך המשחק 
{
    glBegin(GL_QUADS);
    //light_frontside
    glColor3f(0.50, 0.50, 0.50);
    //front
    glVertex3f(x - 0.1, y + 5, z + 0);
    glVertex3f(x + 0.1, y + 5, z + 0);
    glVertex3f(x + 0.1, y + 0.6, z + 0);
    glVertex3f(x - 0.1, y + 0.6, z + 0);
    //back
    glVertex3f(x - 0.1, y + 5, z + 0.3);
    glVertex3f(x + 0.1, y + 5, z + 0.3);
    glVertex3f(x + 0.1, y + 0.6, z + 0.3);
    glVertex3f(x - 0.1, y + 0.6, z + 0.3);


    glEnd();

}
void new_car(float x, float y, float z, int colorCarplayer)//פונקציה ציור המוכנית
{
    glBegin(GL_QUADS);
    // צד קדמי
    glColor3f(1.0f, 1.6f, 0.0f);
    colorCar
        glVertex3f(x - 2, y + 0, z - 3);
    glVertex3f(x - 2, y + 1, z - 3);
    glVertex3f(x + 2, y + 1, z - 3);
    glVertex3f(x + 2, y + 0, z - 3);
    //מס' רכב 
    //קדמי
    glColor3f(1.0f, 0.6f, 0.0f);
    glVertex3f(x - 0.7, y + 0.8, z - 3.1);
    glVertex3f(x - 0.7, y + 0.5, z - 3.1);
    glVertex3f(x + 0.7, y + 0.5, z - 3.1);
    glVertex3f(x + 0.7, y + 0.8, z - 3.1);
    //אחורי
    glColor3f(1.0f, 0.6f, 0.0f);
    glVertex3f(x - 0.7, y + 0.8, z + 3.1);
    glVertex3f(x - 0.7, y + 0.5, z + 3.1);
    glVertex3f(x + 0.7, y + 0.5, z + 3.1);
    glVertex3f(x + 0.7, y + 0.8, z + 3.1);
    //אורות הרכב
    //קדמי
    //שמאל
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(x - 1.8, y + 0.8, z - 3.1);
    glVertex3f(x - 1.8, y + 0.5, z - 3.1);
    glVertex3f(x - 1.4, y + 0.5, z - 3.1);
    glVertex3f(x - 1.4, y + 0.8, z - 3.1);
    //ימין
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(x + 1.8, y + 0.8, z - 3.1);
    glVertex3f(x + 1.8, y + 0.5, z - 3.1);
    glVertex3f(x + 1.4, y + 0.5, z - 3.1);
    glVertex3f(x + 1.4, y + 0.8, z - 3.1);
    //צד אחורי
    //שמאל
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(x - 1.8, y + 0.8, z + 3.1);
    glVertex3f(x - 1.8, y + 0.5, z + 3.1);
    glVertex3f(x - 1.4, y + 0.5, z + 3.1);
    glVertex3f(x - 1.4, y + 0.8, z + 3.1);
    //ימין
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(x + 1.8, y + 0.8, z + 3.1);
    glVertex3f(x + 1.8, y + 0.5, z + 3.1);
    glVertex3f(x + 1.4, y + 0.5, z + 3.1);
    glVertex3f(x + 1.4, y + 0.8, z + 3.1);
    ////////////////
    //צד שמאל של מוכנית
    glColor3f(1.0f, 1.6f, 0.0f);
    colorCar
        glVertex3f(x - 2, y + 0, z + 3);
    glVertex3f(x - 2, y + 0, z - 3);
    glVertex3f(x - 2, y + 1, z - 3);
    glVertex3f(x - 2, y + 1, z + 3);
    //חלון שמאלי 
    glColor3f(1.0f, 1.6f, 0.0f);
    colorCar
        glVertex3f(x - 2, y + 1, z + 2);
    glVertex3f(x - 2, y + 1, z + 0);
    glVertex3f(x - 2, y + 2, z + 0);
    glVertex3f(x - 2, y + 2, z + 1);

    glColor3f(1, 1, 1);
    glVertex3f(x - 2.01, y + 2, z + 1);
    glVertex3f(x - 2.01, y + 2, z - 0.5);
    glVertex3f(x - 2.01, y + 1, z - 2.01);
    glVertex3f(x - 2.01, y + 1, z + 0);

    //צד ימיני של מוכנית
    glColor3f(1.0f, 1.6f, 0.0f);
    colorCar
        glVertex3f(x + 2, y + 0, z - 3);
    glVertex3f(x + 2, y + 0, z + 3);
    glVertex3f(x + 2, y + 1, z + 3);
    glVertex3f(x + 2, y + 1, z - 3);
    //חלון
    glColor3f(1.0f, 1.6f, 0.0f);
    colorCar
        glVertex3f(x + 2, y + 1, z + 2);
    glVertex3f(x + 2, y + 1, z + 0);
    glVertex3f(x + 2, y + 2, z + 0);
    glVertex3f(x + 2, y + 2, z + 1);

    glColor3f(1, 1, 1);
    glVertex3f(x + 2.01, y + 2, z + 1);
    glVertex3f(x + 2.01, y + 2, z - 0.5);
    glVertex3f(x + 2.01, y + 1, z - 2.01);
    glVertex3f(x + 2.01, y + 1, z + 0);

    //טבון קדמי
    glColor3f(1.0f, 1.6f, 0.0f);
    colorCar
        glVertex3f(x - 2, y + 1, z - 2);
    glVertex3f(x + 2, y + 1, z - 2);
    glVertex3f(x + 2, y + 1, z - 3);
    glVertex3f(x - 2, y + 1, z - 3);
    //זכיכות קדמי
    glColor3f(1.0f, 1.6f, 0.0f);
    colorCar
        glVertex3f(x - 2, y + 1, z - 2);
    glVertex3f(x - 1.7, y + 1, z - 2);
    glVertex3f(x - 1.7, y + 2, z - 0.5);
    glVertex3f(x - 2, y + 2, z - 0.5);

    glColor3f(1, 1, 1);
    glVertex3f(x - 1.7, y + 1, z - 2);
    glVertex3f(x + 1.7, y + 1, z - 2);
    glVertex3f(x + 1.7, y + 2, z - 0.5);
    glVertex3f(x - 1.7, y + 2, z - 0.5);

    glColor3f(1.0f, 1.6f, 0.0f);
    colorCar
        glVertex3f(x + 2, y + 1, z - 2);
    glVertex3f(x + 1.7, y + 1, z - 2);
    glVertex3f(x + 1.7, y + 2, z - 0.5);
    glVertex3f(x + 2, y + 2, z - 0.5);

    //גג
    glColor3f(1.0f, 1.6f, 0.0f);
    colorCar
        glVertex3f(x - 2, y + 2, z + 1);
    glVertex3f(x + 2, y + 2, z + 1);
    glVertex3f(x + 2, y + 2, z - 0.5);
    glVertex3f(x - 2, y + 2, z - 0.5);

    //זכיכות אחורי
    glVertex3f(x - 2, y + 1, z + 2);
    glVertex3f(x - 1.7, y + 1, z + 2);
    glVertex3f(x - 1.7, y + 2, z + 1);
    glVertex3f(x - 2, y + 2, z + 1);

    glColor3f(1, 1, 1);
    glVertex3f(x - 1.7, y + 1, z + 2);
    glVertex3f(x + 1.7, y + 1, z + 2);
    glVertex3f(x + 1.7, y + 2, z + 1);
    glVertex3f(x - 1.7, y + 2, z + 1);

    glColor3f(1.0f, 1.6f, 0.0f);
    colorCar
        glVertex3f(x + 2, y + 1, z + 2);
    glVertex3f(x + 1.7, y + 1, z + 2);
    glVertex3f(x + 1.7, y + 2, z + 1);
    glVertex3f(x + 2, y + 2, z + 1);
    ////////////////////////////
    //צד אחורי
    glColor3f(1.0f, 1.6f, 0.0f);
    colorCar
        glVertex3f(x - 2, y + 0, z + 3);
    glVertex3f(x - 2, y + 1, z + 3);
    glVertex3f(x + 2, y + 1, z + 3);
    glVertex3f(x + 2, y + 0, z + 3);

    //טבון אחורי
    glColor3f(1.0f, 1.6f, 0.0f);
    colorCar
        glVertex3f(x - 2, y + 1, z + 2);
    glVertex3f(x + 2, y + 1, z + 2);
    glVertex3f(x + 2, y + 1, z + 3);
    glVertex3f(x - 2, y + 1, z + 3);

    glEnd();

}
void levelUpdate()//פונקציה המעדכנת השלבים בתוך הקובץ
{


    if (strOfUserlevel[0] == '1')
    {
        if (flag_level == false)
        {
            FILE* file;//מצביע לקובץ
            strOfUserlevel[0] = '2';
            strOfUserlevel[1] = '\0';
            file = fopen(strOfUserName, "a");
            remove("file");
            file = fopen(strOfUserName, "w+");
            strOfUserNamepass[indexOfUserNamePass] = '\n';
            strOfUserNamepass[++indexOfUserNamePass] = '\0';
            fputs(strOfUserNamepass, file);
            fputs(strOfUserlevel, file);
            fclose(file);
            flag_level = true;
        }
    }
    if (strOfUserlevel[0] == '2')
    {
        if (flag_level == false)
        {
            FILE* file; //מצביע לקובץ
            strOfUserlevel[0] = '3';
            strOfUserlevel[1] = '\0';
            file = fopen(strOfUserName, "a");
            remove("file");
            file = fopen(strOfUserName, "w+");
            strOfUserNamepass[indexOfUserNamePass] = '\n';
            strOfUserNamepass[++indexOfUserNamePass] = '\0';
            fputs(strOfUserNamepass, file);
            fputs(strOfUserlevel, file);
            fclose(file);
            flag_level = true;
        }
    }
    if (strOfUserlevel[0] == '3')
    {
        if (flag_level == false)
        {
            FILE* file; //מצביע לקובץ
            strOfUserlevel[0] = '4';
            strOfUserlevel[1] = '\0';
            file = fopen(strOfUserName, "a");
            remove("file");
            file = fopen(strOfUserName, "w+");
            strOfUserNamepass[indexOfUserNamePass] = '\n';
            strOfUserNamepass[++indexOfUserNamePass] = '\0';
            fputs(strOfUserNamepass, file);
            fputs(strOfUserlevel, file);
            fclose(file);
            flag_level = true;
        }
    }
}
void mdregh(int color, float x, float z, int direction)//פונקציה לציור מדרכות המקבלת קורדנתות ומיקום
{
    glBegin(GL_QUADS);
    if (direction == 1)
    {
        glColor3f(0, 1, 0);
        glVertex3f(0.3 + x, 0.31, z - 0.3);
        glVertex3f(-0.3 + x, 0.31, z - 0.3);
        glVertex3f(-0.3 + x, 0.31, z - 3);
        glVertex3f(0.3 + x, 0.31, z - 3);
    }
    if (direction == 2)
    {
        glColor3f(0, 1, 0);
        glVertex3f(0.3 + x, 0.31, z + 0.3);
        glVertex3f(-0.3 + x, 0.31, z + 0.3);
        glVertex3f(-0.3 + x, 0.31, z + 3);
        glVertex3f(0.3 + x, 0.31, z + 3);
    }
    if (direction == 3)
    {
        glColor3f(0, 1, 0);
        glVertex3f(0.3 + x, 0.31, z + 0.3);
        glVertex3f(0.3 + x, 0.31, z - 0.3);
        glVertex3f(x + 3, 0.31, -0.3 + z);
        glVertex3f(3 + x, 0.31, z + 0.3);
    }
    if (direction == 4)
    {
        glColor3f(0, 1, 0);
        glVertex3f(-0.3 + x, 0.31, z + 0.3);
        glVertex3f(-0.3 + x, 0.31, z - 0.3);
        glVertex3f(x - 3, 0.31, -0.3 + z);
        glVertex3f(-3 + x, 0.31, z + 0.3);
    }
    if (color == 1)
    {
        glColor3f(1, 0, 0);
    }
    if (color == 2)
    {
        glColor3f(1, 1, 1);
    }
    glVertex3f(0.3 + x, 0, z + 0.3);
    glVertex3f(-0.3 + x, 0, z + 0.3);
    glVertex3f(-0.3 + x, 0.3, z + 0.3);
    glVertex3f(0.3 + x, 0.3, z + 0.3);
    ///////
    glVertex3f(0.3 + x, 0, z - 0.3);
    glVertex3f(-0.3 + x, 0, z - 0.3);
    glVertex3f(-0.3 + x, 0.3, z - 0.3);
    glVertex3f(0.3 + x, 0.3, z - 0.3);
    ///////
    glVertex3f(+0.3 + x, 0, z + 0.3);
    glVertex3f(+0.3 + x, 0, z - 0.3);
    glVertex3f(+0.3 + x, 0.3, z - 0.3);
    glVertex3f(0.3 + x, 0.3, z + 0.3);
    ///////
    glVertex3f(-0.3 + x, 0, z + 0.3);
    glVertex3f(-0.3 + x, 0, z - 0.3);
    glVertex3f(-0.3 + x, 0.3, z - 0.3);
    glVertex3f(-0.3 + x, 0.3, z + 0.3);
    ///////
    glVertex3f(0.3 + x, 0.3, 0 + z + 0.3);
    glVertex3f(-0.3 + x, 0.3, 0 + z + 0.3);
    glVertex3f(-0.3 + x, 0.3, 0 + z - 0.3);
    glVertex3f(0.3 + x, 0.3, 0 + z - 0.3);

    glEnd();
}
void Floor()//פונקציה המגרש 
{
    glBegin(GL_QUADS);
    glColor3f(0.329412, 0.329412, 0.329412);
    glVertex3f(-48, 0, -48);
    glVertex3f(48, 0, -48);
    glVertex3f(48, 0, 48);
    glVertex3f(-48, 0, 48);
    glEnd();
}
void parking(int direction, int direction1, float x, float z) //פונקציה החניות בתוך המגרש מקבלת קורדנתןת ומיקום 
{
    glBegin(GL_QUADS);
    if (direction == 1)
    {
        glColor3f(1, 1, 1);
        glVertex3f(0.3 + x, 0.01, 3 + z);
        glVertex3f(-0.3 + x, 0.01, 3 + z);
        glVertex3f(-0.3 + x, 0.01, -3 + z);
        glVertex3f(0.3 + x, 0.01, -3 + z);
        if (direction1 == 1)
        {
            glVertex3f(1 + x, 0.01, 3 + z);
            glVertex3f(1 + x, 0.01, 3.6 + z);
            glVertex3f(-1 + x, 0.01, 3.6 + z);
            glVertex3f(-1 + x, 0.01, 3 + z);
        }
        else
        {
            glVertex3f(1 + x, 0.01, -3 + z);
            glVertex3f(1 + x, 0.01, -3.6 + z);
            glVertex3f(-1 + x, 0.01, -3.6 + z);
            glVertex3f(-1 + x, 0.01, -3 + z);
        }

        glEnd();
    }
    else
    {
        glColor3f(1, 1, 1);
        glVertex3f(3 + x, 0.01, 0.3 + z);
        glVertex3f(3 + x, 0.01, -0.3 + z);
        glVertex3f(-3 + x, 0.01, -0.3 + z);
        glVertex3f(-3 + x, 0.01, 0.3 + z);

        if (direction1 == 1)
        {
            glVertex3f(3 + x, 0.01, 1 + z);
            glVertex3f(3.6 + x, 0.01, 1 + z);
            glVertex3f(3.6 + x, 0.01, -1 + z);
            glVertex3f(3 + x, 0.01, -1 + z);
        }
        else
        {
            glVertex3f(-3 + x, 0.01, 1 + z);
            glVertex3f(-3.6 + x, 0.01, 1 + z);
            glVertex3f(-3.6 + x, 0.01, -1 + z);
            glVertex3f(-3 + x, 0.01, -1 + z);
        }
        glEnd();
    }
}
void correct_parking(int direction, float x, float z)//פונקציה של מיקום הרכב הנכון בתוך המגרש 
{

    glBegin(GL_QUADS);
    glColor3f(0, 1, 0);
    if (direction == 1)
    {
        glVertex3f(2.5 + x, 0.01, 3 + z);
        glVertex3f(-2.5 + x, 0.01, 3 + z);
        glVertex3f(-2.5 + x, 0.01, -3 + z);
        glVertex3f(2.5 + x, 0.01, -3 + z);
    }
    else
    {
        glVertex3f(3 + x, 0.01, 2.5 + z);
        glVertex3f(3 + x, 0.01, -2.5 + z);
        glVertex3f(-3 + x, 0.01, -2.5 + z);
        glVertex3f(-3 + x, 0.01, 2.5 + z);
    }

    glEnd();
}
void draw_correct_parking()//פונקציה המציירת החניון הירוק הנדרש 
{
    if (screen == 3 || screen == 16)
    {
        parking1.x = -32.5;
        parking1.z = -6;
        correct_parking(1, parking1.x, parking1.z);
    }
    if (screen == 11 || screen == 12)
    {
        parking1.x = 32.5;
        parking1.z = -6;
        correct_parking(1, parking1.x, parking1.z);
    }
}
void draw_mdregot()//פונקציה לציור מדרכות 
{
    v = 0;
    for (float i = 46; i > -11; i -= 1.2, v += 2)
    {
        arr[v].x = 37;
        arr[v + 1].x = 37;
        arr[v].color = 1;
        arr[v + 1].color = 2;
        arr[v].z = i;
        arr[v + 1].z = i - 0.6;
        mdregh(arr[v].color, arr[v].x, arr[v].z, 3);
        mdregh(arr[v + 1].color, arr[v + 1].x, arr[v + 1].z, 3);
    }
    for (float i = 46; i > -11; i -= 1.2, v += 2)
    {
        arr[v].x = -37;
        arr[v + 1].x = -37;
        arr[v].color = 1;
        arr[v + 1].color = 2;
        arr[v].z = i;
        arr[v + 1].z = i - 0.6;
        mdregh(arr[v].color, arr[v].x, arr[v].z, 4);
        mdregh(arr[v + 1].color, arr[v + 1].x, arr[v + 1].z, 4);
    }
    for (float i = 46; i >= -46; i -= 1.2, v += 4)
    {

        arr[v].x = i;
        arr[v + 1].x = i + 0.6;
        arr[v].color = 1;
        arr[v + 1].color = 2;
        arr[v].z = -10;
        arr[v + 1].z = -10;
        mdregh(arr[v].color, arr[v].x, arr[v].z, 1);
        mdregh(arr[v + 1].color, arr[v + 1].x, arr[v + 1].z, 1);
        arr[v + 2].x = i;
        arr[v + 3].x = i + 0.6;
        arr[v + 2].color = 1;
        arr[v + 3].color = 2;
        arr[v + 2].z = 46;
        arr[v + 3].z = 46;
        mdregh(arr[v + 2].color, arr[v + 2].x, arr[v + 2].z, 2);
        mdregh(arr[v + 3].color, arr[v + 3].x, arr[v + 3].z, 2);



    }
    /////////////////////////////////////////////
    for (float i = -46; i <= -10; i += 1.2, v += 4)
    {
        arr[v].z = 20;
        arr[v + 1].z = 20;
        arr[v].color = 1;
        arr[v + 1].color = 2;
        arr[v].x = -i;
        arr[v + 1].x = -i - 0.6;
        mdregh(arr[v].color, arr[v].x, arr[v].z, 2);
        mdregh(arr[v + 1].color, arr[v + 1].x, arr[v + 1].z, 2);
        arr[v + 2].z = 26;
        arr[v + 3].z = 26;
        arr[v + 2].color = 1;
        arr[v + 3].color = 2;
        arr[v + 2].x = -i;
        arr[v + 3].x = -i - 0.6;
        mdregh(arr[v + 2].color, arr[v + 2].x, arr[v + 2].z, 1);
        mdregh(arr[v + 3].color, arr[v + 3].x, arr[v + 3].z, 1);
    }
    for (float i = 20.6; i <= 26; i += 1.2, v += 2)
    {
        arr[v].z = i;
        arr[v + 1].z = i + 0.6;
        arr[v].color = 1;
        arr[v + 1].color = 2;
        arr[v].x = 10;
        arr[v + 1].x = 10;
        mdregh(arr[v].color, arr[v].x, arr[v].z, 0);
        mdregh(arr[v + 1].color, arr[v + 1].x, arr[v + 1].z, 0);
    }
    arr[v].z = 20;
    arr[v].color = 2;
    arr[v].x = 10;
    mdregh(arr[v].color, arr[v].x, arr[v].z, 0);
    //////////////////////////////////
    for (float i = -46; i <= -10; i += 1.2, v += 4)
    {
        arr[v].z = 20;
        arr[v + 1].z = 20;
        arr[v].color = 1;
        arr[v + 1].color = 2;
        arr[v].x = i;
        arr[v + 1].x = i - 0.6;
        mdregh(arr[v].color, arr[v].x, arr[v].z, 2);
        mdregh(arr[v + 1].color, arr[v + 1].x, arr[v + 1].z, 2);
        arr[v + 2].z = 26;
        arr[v + 3].z = 26;
        arr[v + 2].color = 1;
        arr[v + 3].color = 2;
        arr[v + 2].x = i;
        arr[v + 3].x = i - 0.6;
        mdregh(arr[v + 2].color, arr[v + 2].x, arr[v + 2].z, 1);
        mdregh(arr[v + 3].color, arr[v + 3].x, arr[v + 3].z, 1);
    }
    for (float i = 20.6; i <= 26; i += 1.2, v += 2)
    {
        arr[v].z = i;
        arr[v + 1].z = i + 0.6;
        arr[v].color = 1;
        arr[v + 1].color = 2;
        arr[v].x = -10.6;
        arr[v + 1].x = -10.6;
        mdregh(arr[v].color, arr[v].x, arr[v].z, 0);
        mdregh(arr[v + 1].color, arr[v + 1].x, arr[v + 1].z, 0);
    }
    arr[v].z = 20;
    arr[v].color = 2;
    arr[v].x = -10.6;
    mdregh(arr[v].color, arr[v].x, arr[v].z, 0);

}
void draw_cars() //פונקציה לציור המוכנית 
{
    for (int i = 13, colorC = 3, j = -22; i < 15; i++, j += 5)
    {
        cars[i].x = j - 0.5;
        cars[i].z = -7;
        cars[i].y = 0;
        new_car(cars[i].x, cars[i].y, cars[i].z, colorC++);
    }

    for (int i = 0, colorC = 3, j = -7; i < 8; i++, j += 5)
    {
        cars[i].x = j - 0.5;
        cars[i].z = -7;
        cars[i].y = 0;
        new_car(cars[i].x, cars[i].y, cars[i].z, colorC++);
        if (colorC == 5)colorC = 1;

    }
    for (int i = 8, colorC = 1, j = -22; i < 10; i++, j += 5)
    {

        cars[i].x = j - 1.3;
        cars[i].z = 16;
        cars[i].y = 0;
        new_car(cars[i].x, cars[i].y, cars[i].z, colorC++);
        if (colorC == 5)colorC = 1;

    }
    for (int i = 10, colorC = 4, j = 13; i < 12; i++, j += 5)
    {

        cars[i].x = j - 0.5;
        cars[i].z = 16;
        cars[i].y = 0;
        new_car(cars[i].x, cars[i].y, cars[i].z, colorC++);
        if (colorC == 5)colorC = 1;

    }
    cars[12].x = 28 - 0.5;
    cars[12].z = 16;
    cars[12].y = 0;
    new_car(cars[12].x, cars[12].y, cars[12].z, 5);


}
void draw_home() //פונקציה לציור הבניים 
{

    //1//
    home(5, 1.0, 0.4, 0.3, 36, 0.3, -16);
    home(7, 0.0, 0.7, 0.0, 28, 0.3, -16);
    home(9, 1.0, 0.1, 5.1, 20, 0.3, -16);
    home(5, 1.0, 0.4, 0.3, 12, 0.3, -16);
    home(7, 0.0, 0.7, 0.0, 4, 0.3, -16);
    home(9, 1.0, 0.1, 5.1, -4, 0.3, -16);
    home(5, 1.0, 0.4, 0.3, -12, 0.3, -16);
    home(7, 0.0, 0.7, 0.0, -20, 0.3, -16);
    home(9, 1.0, 0.1, 5.1, -28, 0.3, -16);
    home(5, 1.0, 0.4, 0.3, -36, 0.3, -16);
    //2//
    home(7, 0.0, 0.7, 0.0, -44, 0.3, 40);
    home(5, 1.0, 0.4, 0.3, -44, 0.3, 32);
    home(9, 1.0, 0.1, 5.1, -44, 0.3, 24);
    home(7, 0.0, 0.7, 0.0, -44, 0.3, 16);
    home(5, 1.0, 0.4, 0.3, -44, 0.3, 8);
    home(9, 1.0, 0.1, 5.1, -44, 0.3, 0);
    home(7, 0.0, 0.7, 0.0, -44, 0.3, -8);

    //3//
    home(7, 0.0, 0.7, 0.0, 44, 0.3, 40);
    home(5, 1.0, 0.4, 0.3, 44, 0.3, 32);
    home(9, 1.0, 0.1, 5.1, 44, 0.3, 24);
    home(7, 0.0, 0.7, 0.0, 44, 0.3, 16);
    home(5, 1.0, 0.4, 0.3, 44, 0.3, 8);
    home(9, 1.0, 0.1, 5.1, 44, 0.3, 0);
    home(7, 0.0, 0.7, 0.0, 44, 0.3, -8);
}
void draw_lightstreet()//פונקציה לציור הארות בשכונה 
{
    for (int i = 13; i <= 34; i += 3)
    {
        lightstreet(i, 0, 25);

    }
    for (int i = -13; i >= -34; i -= 3)
    {
        lightstreet(i, 0, 25);
    }


}
void draw_parking() //פונקציה לציור חניות
{
    for (int i = -35; i <= 35; i += 5)
    {
        parking(1, 1, i, -6.5);
        if (i > 5)
        {
            parking(1, 0, -i - 0.6, 16);
        }
        if (i < -5)
        {
            parking(1, 0, -i, 16);
        }

    }


}
void draw_car()//פונקציה לציור המוכנית של השחקן
{




    new_car(0, 0.2, 0, colorCarplayer);
    glColor3f(0.662, 0.662, 0.662);
    glRotatef(90, 0, 1, 0);

    glTranslatef(2, 0.2, -2);
    glutSolidTorus(0.1, 0.25, 4, 20);
    glTranslatef(-2, 0, 2);

    glTranslatef(-2, 0, -2);
    glutSolidTorus(0.1, 0.25, 10, 20);
    glTranslatef(2, 0, 2);

    glTranslatef(2, 0, 2);
    glutSolidTorus(0.1, 0.25, 4, 20);
    glTranslatef(-2, 0, -2);

    glTranslatef(-2, 0, 2);
    glutSolidTorus(0.1, 0.25, 10, 20);
    glTranslatef(2, -0.2, -2);
    glRotatef(-90, 0, 1, 0);

    glEnd();

}
void draw()//פונקציה לכל הפונקציות כדי לציר אותם
{
    glClear(GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, -25, -85);
    if (screen == 0)
    {

        glColor3f(0, 2, 0);
        compileStrings(-14, 70, "WELCOME TO PARKING CAR 3D");
        compileStrings(-12, 60, "  For Game Instructions Press 1");
        compileStrings(-10, 30, "{ Press ENTER To Start}");
        compileStrings(-40, 20, "{Click The Left Arrow}");
        compileStrings(20, 20, "{Click The Right Arrow}");
        compileStrings(-48.7, -15, "Copy Right to ASEM & MOHAMMAD Inc.");
        glTranslatef(0, 0, 70);
        glRotatef(root, 0, 1, 0);
        new_car(0, 20, 0, 2);
        glTranslatef(0, 0, -70);

        glRotatef(-root, 0, 1, 0);
    }
    if (screen == 1)
    {
        compileStrings(-14, 70, "Welcome To PARKING CAR 3D  !!");
        compileStrings(-30, 60, "Hi, playing a game must be registered as a new player.");
        compileStrings(-30, 52, "The game requires you to park your car in a green place, ");
        compileStrings(-30, 46, "you have to aim your car with four arrows to move to the next level, ");
        compileStrings(-30, 38, " there are 4 stages in the game. ");
        compileStrings(-30, 30, "Each level has a different level of difficulty. ");
        compileStrings(-30, 22, "Your score will be by taxes without your car hitting in any way ");
        compileStrings(-48, -5, "Press 'Escape' To Quit");
        compileStrings(35, -5, "To Return F1");
        compileStrings(-48.2, -15, "Copy Right to ASEM & MOHAMMAD Inc.");
    }
    if (screen == 3)
    {
        glTranslatef(0, 25, 90);

        glTranslatef(-car1.x, -25, -90 - car1.z);

        t2 = time(NULL);
        levelstage = 1;
        if (t2 - t1 == TimerEnd)
        {
            life[0]--;
            screen = 15;
        }
        /************************************************************/
        Floor();
        draw_mdregot();
        draw_home();
        draw_parking();
        draw_correct_parking();
        draw_cars();
        draw_lightstreet();
        glTranslatef(car1.x, 0, car1.z);

        timePrintOnScreen();
        compileStrings(39, 70, "SCORE: ");
        glRasterPos2f(46, 70);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, life[0]);
        glTranslatef(-car1.x, 0, -car1.z);
        car_parking();
        if (life[0] == '0')
        {

            screen = 10;
        }
    }
    if (screen == 4)
    {
        RADIUS = 0;
        LEFT = 0;
        speed = 0.005;
        RIGHT = -180;
        car1.x = 0;
        car1.z = 0;

        levelUpdate();
        compileStrings(-14, 70, "Welcome To PARKING CAR 3D  !!");
        compileStrings(-9, 60, "YOU WON !!");
        compileStrings(-8, 50, "Level UP !");

        if (life[0] == '3')
        {
            compileStrings(-10, 40, "YOUR SCORE IS '3'");
        }
        if (life[0] == '2') {
            compileStrings(-10, 40, "YOUR SCORE IS '2'");
        }
        if (life[0] == '1')
        {
            compileStrings(-10, 40, "YOUR SCORE IS '1'");
        }

        compileStrings(20, -5, "Press 'ENTER' To Next Level");
        compileStrings(-48, -5, "Press 'Escape' To Quit");
        compileStrings(-48.2, -10, "Copy Right to ASEM & MOHAMMAD Inc.");
    }
    if (screen == 5)
    {
        glTranslatef(0, 0, -5);

        glColor3f(0, 1, 0);
        compileStrings(-14, 70, "Welcome To PARKING CAR 3D  !!");
        compileStrings(-9, 65, "     NEW ACCOUNT ");
        compileStrings(-35, 60, "     Enter Your Name:");
        compileStrings(-35, 55, "     Enter Your Password:");
        compileStrings(-5, 20, "  START ");
        compileStrings(-48, -5, "Home - F1.");
        compileStrings(35, -5, "Return - F2.");
        compileStrings(-48.2, -15, "Copy Right to ASEM & MOHAMMAD Inc.");
        glColor3f(0, 1, 0);
        glRasterPos2f(-13, 55);
        int ind1 = 0;
        while (strOfUserNamepass[ind1]) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '*');
            ind1++;
        }
        /************************************************************/
        glColor3f(0, 1, 0);
        glRasterPos2f(-16, 60);
        int ind = 0;
        while (strOfUserName[ind]) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, strOfUserName[ind]); // print the color
            ind++;
        }
        if (name == true)
        {
            pass = false;
        }

        if (pass == true)
        {
            name = false;
        }

    }
    if (screen == 6)
    {
        name = false;
        pass = false;
        indexOfUserName = 0;
        indexOfUserNamePass = 0;
        compileStrings(-14, 70, "Welcome To PARKING CAR 3D  !!");
        compileStrings(-8, 60, "  Login Press 1");
        compileStrings(-10, 50, "  New Account Press 2");
        compileStrings(-40, 20, "{Click The Left Arrow}");
        compileStrings(20, 20, "{Click The Right Arrow}");


        compileStrings(-48, -5, "Home - F1.");
        compileStrings(-48.2, -15, "Copy Right to ASEM & MOHAMMAD Inc.");
        glTranslatef(0, 0, 70);
        glRotatef(root, 0, 1, 0);
        new_car(0, 20, 0, 2);
        glTranslatef(0, 0, -70);
        glRotatef(-root, 0, 1, 0);
    }
    if (screen == 7)
    {
        glTranslatef(0, 0, -5);

        glColor3f(0, 1, 0);
        compileStrings(-14, 70, "Welcome To PARKING CAR 3D  !!");
        compileStrings(-14, 60, "    LOGIN TO THE GAME ");
        compileStrings(-35, 55, "     Enter Your Name:");
        compileStrings(-35, 50, "     Enter Your Password:");
        compileStrings(-5, 20, "  START ");
        compileStrings(-48, -5, "Home - F1.");
        compileStrings(35, -5, "Return - F2.");
        compileStrings(-48.2, -15, "Copy Right to ASEM & MOHAMMAD Inc.");
        glColor3f(0, 1, 0);
        glRasterPos2f(-13, 50);
        int ind1 = 0;
        while (strOfUserNamepass[ind1]) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '*'); // print the color
            ind1++;
        }
        /************************************************************/
        glColor3f(0, 1, 0);
        glRasterPos2f(-16, 55);
        int ind = 0;
        while (strOfUserName[ind]) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, strOfUserName[ind]); // print the color
            ind++;
        }
        if (name == true)
        {
            pass = false;
        }

        if (pass == true)
        {
            name = false;
        }

    }
    if (screen == 8)
    {
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.6f, 0.0f);

        glVertex3f(2, -2, 2);
        glVertex3f(-2, -2, 2);
        glVertex3f(-2, 2, 2);
        glVertex3f(2, 2, 2);

        glColor3f(0.137255, 0.556863, 0.419608);
        glVertex3f(2 + 5, -2, 2);
        glVertex3f(-2 + 5, -2, 2);
        glVertex3f(-2 + 5, 2, 2);
        glVertex3f(2 + 5, 2, 2);

        glColor3f(1.00, 0.11, 0.68);
        glVertex3f(2 + 10, -2, 2);
        glVertex3f(-2 + 10, -2, 2);
        glVertex3f(-2 + 10, 2, 2);
        glVertex3f(2 + 10, 2, 2);

        glColor3f(0.30, 0.30, 1.00);
        glVertex3f(2 - 5, -2, 2);
        glVertex3f(-2 - 5, -2, 2);
        glVertex3f(-2 - 5, 2, 2);
        glVertex3f(2 - 5, 2, 2);

        glColor3f(0, 0, 0);
        glVertex3f(2 - 10, -2, 2);
        glVertex3f(-2 - 10, -2, 2);
        glVertex3f(-2 - 10, 2, 2);
        glVertex3f(2 - 10, 2, 2);
        glEnd();
        compileStrings(-14, 70, "Welcome To PARKING CAR 3D  !!");
        compileStrings(-10, 60, "  New Game Press '1'");
        compileStrings(-10, 55, "  Load Game Press '2'");
        compileStrings(35, -5, "  Exit Game Esc");
        compileStrings(-40, 20, "{Click The Left Arrow}");
        compileStrings(20, 20, "{Click The Right Arrow}");
        compileStrings(-48.2, -15, "Copy Right to ASEM & MOHAMMAD Inc.");
        glTranslatef(0, 0, 70);
        glRotatef(root, 0, 1, 0);
        new_car(0, 22, 0, colorCarplayer);
        glTranslatef(0, 0, -70);
        glRotatef(-root, 0, 1, 0);
    }
    if (screen == 9)
    {
        for (int i = 0; i < 20; i++)
        {
            strOfUserName[i] = NULL;
            strOfUserNamepass[i] = NULL;
        }
        indexOfUserName = 0;
        indexOfUserNamePass = 0;
        compileStrings(-10, 70, " PARKING CAR 3D  !!");
        compileStrings(-10, 50, "Password Incorrect !! ");
        compileStrings(-48, -5, "Home - F1.");
        compileStrings(35, -5, " Try Again F2.");
        compileStrings(-48.2, -15, "Copy Right to ASEM & MOHAMMAD Inc.");
    }
    if (screen == 10)
    {
        compileStrings(-10, 70, " PARKING CAR 3D  !!");
        compileStrings(-7, 50, "GAME OVER !!");
        compileStrings(-7, 40, "TIME IS OVER ");
        compileStrings(-10, 30, " OR YOUR LIFE IS OVER");
        compileStrings(-48, -5, " ENTER To Try Again");
        compileStrings(35, -5, "  Exit Game Esc");
        compileStrings(-48.2, -15, "Copy Right to ASEM & MOHAMMAD Inc.");
        life[0] = '3';
    }
    if (screen == 11)
    {
        glTranslatef(0, 25, 90);
        glTranslatef(-car1.x, -25, -90 - car1.z);
        levelstage = 2;
        t2 = time(NULL);
        if (t2 - t1 == TimerEnd)
        {
            screen = 15;
            life[0]--;

        }
        /************************************************************/
        Floor();
        draw_mdregot();
        draw_home();
        draw_parking();
        draw_correct_parking();
        draw_cars();
        draw_lightstreet();
        glTranslatef(car1.x, 0, car1.z);
        timePrintOnScreen();
        compileStrings(39, 70, "SCORE: ");
        glRasterPos2f(46, 70);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, life[0]);
        glTranslatef(-car1.x, 0, -car1.z);
        car_parking();
        if (life[0] == '0')
        {
            life[0]--;
            screen = 10;
        }
    }
    if (screen == 12)
    {
        glTranslatef(0, 25, 90);
        glTranslatef(-car1.x, -25, -90 - car1.z);
        levelstage = 3;
        new_car(car2.x, 0, car2.z, 4);
        t2 = time(NULL);
        if (t2 - t1 == TimerEnd)
        {
            screen = 15;
            life[0]--;
        }
        /************************************************************/
        Floor();
        draw_mdregot();
        draw_home();
        draw_parking();
        draw_correct_parking();
        draw_cars();
        draw_lightstreet();
        glTranslatef(car1.x, 0, car1.z);
        timePrintOnScreen();
        compileStrings(39, 70, "SCORE: ");
        glRasterPos2f(46, 70);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, life[0]);
        glTranslatef(-car1.x, 0, -car1.z);
        car_parking();
        if (life[0] == '0')
        {
            life[0]--;
            screen = 10;
        }

    }
    if (screen == 13)
    {
        flag_level = true;
        levelUpdate();
        compileStrings(-14, 70, "Welcome To PARKING CAR 3D  !!");
        compileStrings(-7, 60, "YOU WON !!");
        compileStrings(-20, 50, "YOU FINSHED ALL THE LEVELS EXCELLENT !! ");
        compileStrings(-13, 40, "STAY TUNED FOR MORE!! ");

        if (life[0] == '3')
        {
            compileStrings(-10, 30, "YOUR SCORE IS '3'");
        }
        if (life[0] == '2') {
            compileStrings(-10, 30, "YOUR SCORE IS '2'");
        }
        if (life[0] == '1')
        {
            compileStrings(-10, 30, "YOUR SCORE IS '1'");
        }
        compileStrings(-48, -5, "Press 'Escape' To Quit");
        compileStrings(-48.2, -10, "Copy Right to ASEM & MOHAMMAD Inc.");
    }
    if (screen == 15)
    {
        compileStrings(-10, 70, " PARKING CAR 3D  !!");
        RADIUS = 0;
        LEFT = 0;
        speed = 0.005;
        RIGHT = -180;
        car1.x = 0;
        car1.z = 0;
        if (levelstage == 3)
        {
            car2.x = 22.5;
            car2.z = 16;
        }
        if (levelstage == 4)
        {
            car2.x = -28.3;
            car2.z = 16;
            car3.x = -12.5;
            car3.z = -5;
        }
        if (life[0] == '2') {
            compileStrings(-10, 40, "TRY AGAIN YOUR LIFE IS '2'");
        }
        if (life[0] == '1')
        {
            compileStrings(-10, 40, "TRY AGAIN YOUR LIFE IS '2'");
        }
        compileStrings(-48, -5, " ENTER To Try Again");
        compileStrings(35, -5, "  Exit Game Esc");
        compileStrings(-48.2, -15, "Copy Right to ASEM & MOHAMMAD Inc.");
    }
    if (screen == 16)
    {
        glTranslatef(0, 25, 90);
        glTranslatef(-car1.x, -25, -90 - car1.z);
        levelstage = 4;
        new_car(car2.x, 0, car2.z, 3);
        new_car(car3.x, 0, car3.z, 5);
        t2 = time(NULL);
        if (t2 - t1 == TimerEnd)
        {
            life[0]--;
            screen = 15;
        }
        /************************************************************/
        Floor();
        draw_mdregot();
        draw_home();
        draw_parking();
        draw_correct_parking();
        draw_cars();
        draw_lightstreet();
        glTranslatef(car1.x, 0, car1.z);
        timePrintOnScreen();
        compileStrings(39, 70, "SCORE: ");
        glRasterPos2f(46, 70);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, life[0]);
        glTranslatef(-car1.x, 0, -car1.z);
        car_parking();
        if (life[0] == '0')
        {
            life[0]--;
            screen = 10;
        }
    }
    if (screen == 3 || screen == 11 || screen == 12 || screen == 16)
    {
        glTranslatef(0, 0, 35);
        glTranslatef(car1.x, 0.1, car1.z);
        glRotatef(RADIUS, 0, 1, 0);
        draw_car();
        glRotatef(-RADIUS, 0, 1, 0);
        glTranslatef(car1.x, 25, 90 + car1.z);
    }
    glutSwapBuffers();
}
void idle()
{

    if (flagCarUp && screen == 12)
    {

        if (car2.z <= 16 && car2.z >= 3) {
            car2.z -= 0.005;

        }
        else
        {
            flagCarUp = 0;
            flagCarDown = 1;
            car2.z += 0.005;
        }

    }
    if (flagCarDown && screen == 12)
    {

        if (car2.z <= 16 && car2.z >= 3) {
            car2.z += 0.005;
        }
        else
        {
            flagCarUp = 1;
            flagCarDown = 0;
            car2.z -= 0.005;
        }
    }
    if (car1.z < 10 && car1.x < -2)
    {
        if (flagCarUp && screen == 16)
        {
            if (car2.z <= 16 && car2.z >= 3) {
                car2.z -= 0.005;
            }
            else
            {
                flagCarUp = 0;
                flagCarDown = 1;
                car2.z += 0.005;
            }

        }
        if (flagCarDown && screen == 16)
        {
            if (car2.z <= 16 && car2.z >= 3) {
                car2.z += 0.005;
            }
            else
            {
                flagCarUp = 1;
                flagCarDown = 0;
                car2.z -= 0.005;
            }
        }
        if (flagCarUp2 && screen == 16)
        {
            if (car3.z <= 10 && car3.z >= -5) {
                car3.z -= 0.005;
            }
            else
            {
                flagCarUp2 = 0;
                flagCarDown2 = 1;
                car3.z += 0.005;
            }

        }
        if (flagCarDown2 && screen == 16)
        {
            if (car3.z <= 10 && car3.z >= -5) {
                car3.z += 0.005;
            }
            else
            {
                flagCarUp2 = 1;
                flagCarDown2 = 0;
                car3.z -= 0.005;
            }

        }
    }
    if (car_move_Accident() == 0)
    {
        life[0]--;
        if (life[0] >= '1')
        {
            screen = 15;

        }
    }
    draw();
}
void init()
{

    RADIUS = 0;
    LEFT = 0;
    RIGHT = -180;

    /**********************************************/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);

    // Lighting parameters

    GLfloat mat_ambdif[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular[] = { 0.0, 1.0, 0.0, 0.0 };
    GLfloat mat_shininess[] = { 80.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };


    glClearColor(0.74902, 0.847059, 0.847059, 0.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambdif); // set both amb and diff components
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);      // set specular
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);        // set shininess
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);      // set light "position", in this case direction
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);      // active material changes by glColor3f(..)


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
}
int main(int argc, char* argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);   // RGB display, double-str_compareed, with Z-str_compare
    glutInitWindowSize(1200, 800);                  // 500 x 500 pixels
    glutCreateWindow("3D");
    glutDisplayFunc(draw);                      // Set the display function
    glutSpecialFunc(specialKeyFunc);
    glutKeyboardFunc(keyboard);     // Set the keyboard function
    glutMouseFunc(mouse);
    glutIdleFunc(idle);// Set the keyboard function
    init();
    glutMainLoop();
    // Start the main event loop
}
