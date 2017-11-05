#define ON 0
#define OFF 1

enum Mode
{
	timer, timing, show
};

enum TimerMode
{
	five, three
};

Mode mode;
Mode moded;
int showingNum;
int timerTime;

int buttomAed;
int buttomBed;

void setup()
{

	/* add setup code here */
	pinMode(1, OUTPUT);
	//LDP
	pinMode(2, OUTPUT);
	//4to10 1234
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);

	pinMode(8, INPUT_PULLUP);
	pinMode(9, INPUT_PULLUP);
	pinMode(10, INPUT_PULLUP);
	pinMode(11, INPUT_PULLUP);

	Serial.begin(9600);

	mode = show;
	showingNum = 0;

}

void ShowNum(int num, int num2)
{
	//0 ~ 9 = 0 to 9
	//10 ~ 11= LDP,null
	if (num2 == 10)
	{
		digitalWrite(2, LOW);
	}
	if (num2 == 11)
	{
		digitalWrite(2, HIGH);
	}
	switch (num)
	{
	case 1:
		//Serial.write(num);
		digitalWrite(3, LOW);
		digitalWrite(4, LOW);
		digitalWrite(5, LOW);
		digitalWrite(6, LOW);

		break;
	case 2:
		//Serial.write(num);
		digitalWrite(3, HIGH);
		digitalWrite(4, LOW);
		digitalWrite(5, LOW);
		digitalWrite(6, HIGH);
		break;
	case 3:
		//Serial.write(num);
		digitalWrite(3, LOW);
		digitalWrite(4, LOW);
		digitalWrite(5, LOW);
		digitalWrite(6, HIGH);
		break;
	case 4:
		//Serial.write(num);
		digitalWrite(3, HIGH);
		digitalWrite(4, HIGH);
		digitalWrite(5, HIGH);
		digitalWrite(6, LOW);
		break;
	case 5:
		//Serial.write(num);
		digitalWrite(3, LOW);
		digitalWrite(4, HIGH);
		digitalWrite(5, HIGH);
		digitalWrite(6, LOW);
		break;
	case 6:
		//Serial.write(num);
		digitalWrite(3, HIGH);
		digitalWrite(4, LOW);
		digitalWrite(5, HIGH);
		digitalWrite(6, LOW);
		break;
	case 7:
		//Serial.write(num);
		digitalWrite(3, LOW);
		digitalWrite(4, LOW);
		digitalWrite(5, HIGH);
		digitalWrite(6, LOW);
		break;
	case 8:
		//Serial.write(num);
		digitalWrite(3, HIGH);
		digitalWrite(4, HIGH);
		digitalWrite(5, LOW);
		digitalWrite(6, LOW);
		break;
	case 9:
		//Serial.write(num);
		digitalWrite(3, LOW);
		digitalWrite(4, HIGH);
		digitalWrite(5, LOW);
		digitalWrite(6, LOW);
		break;
	case 0:
		//Serial.write(num);
		digitalWrite(3, HIGH);
		digitalWrite(4, LOW);
		digitalWrite(5, LOW);
		digitalWrite(6, LOW);
		break;
	case 10://LDP
		//Serial.write(num);
		digitalWrite(2, LOW);
		digitalWrite(3, HIGH);
		digitalWrite(4, HIGH);
		digitalWrite(5, HIGH);
		digitalWrite(6, HIGH);
		break;
	default:
		//Serial.write(num);
		digitalWrite(3, HIGH);
		digitalWrite(4, HIGH);
		digitalWrite(5, HIGH);
		digitalWrite(6, HIGH);
		break;
	}

}

void set(int A, int B)
{
	buttomAed = A;
	buttomBed = B;
}

void loop()
{

	/* add main program code here */
	int buttomA = digitalRead(8);
	int buttomB = digitalRead(9);
	int switchFif = digitalRead(10);
	int switchThr = digitalRead(11);
	//if (buttomA == HIGH) Serial.write("HIGH");
	if (mode != moded)  Serial.write(mode == show ? "show\n\r" : mode == timer ? "timer\n\r" : "timering\n\r");
	moded = mode;
	if (mode == timing)
	{
		if (timerTime != 0)
		{

			timerTime--;
			int showNum = timerTime / 60 >= 1 ? timerTime / 60 : timerTime / 10 >= 1 ? timerTime / 10 : timerTime;
			ShowNum(showNum, 10);
			delay(248);
			ShowNum(showNum, 11);
			delay(750);
		}
		else
		{
			ShowNum(0, 10);
		}

		if (buttomB == ON)
		{
			mode = timer;
			delay(250);
			return;
		}
		return;
	}

	if (mode == show)
	{
		if (buttomA == ON && buttomB == ON)
		{
			mode = timer;
			delay(250);
			return;
		}

		if (buttomA == ON && buttomA != buttomBed)
		{
			if (showingNum == 11)
			{
				showingNum = -1;
			}
			showingNum++;
			ShowNum(showingNum, 11);
			//Serial.write("A\n\r");
			set(buttomA, buttomB);
			delay(250);
			return;
		}

		else if (buttomB == ON && buttomB != buttomBed)
		{
			if (showingNum == 0)
			{
				showingNum = 12;
			}
			showingNum--;
			ShowNum(showingNum, 11);
			set(buttomA, buttomB);
			//Serial.write("A\n\r");
			delay(250);
			return;
		}
		set(buttomA, buttomB);
		return;
	}
	if (mode == timer)
	{
		if (buttomA == ON && buttomB == ON)
		{
			mode = show;
			ShowNum(0, 11);
			delay(250);
			return;
		}
		if (buttomA == ON)
		{
			timerTime = switchFif == ON ? 300 : 180;
			mode = timing;
			delay(250);
			return;
		}
		if (switchFif == ON)
		{
			ShowNum(5, 11);
			return;
		}
		if (switchThr == ON)
		{
			ShowNum(3, 11);
			return;
		}
	}
}





