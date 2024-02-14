#pragma once

#include "PvZfunkce.h"

bool level1()
{
	//Velikost tabulky
    const uint16 widht=9, height=1;
    //Pocet slunci
    uint16 sun_count=50;
    Table<int16> zombiesila(height);
    Table<char> field(height);
    Init(field, zombiesila, widht);
    for(uint16 i=0;i<20;++i)
    {
        cout<<"Postup "<<i*5<<"%"<<endl;
        PrintField(field,zombiesila);
        cout<<"Z=Normalni zombik 30 zivotu"<<endl;
        for(;;)
        {
			uint16 action=0;
            Menu(sun_count);
            cout<<"1-Pukac: Cena:100 slunicek,utok:10,1 PUK/1 kolo"<<endl;
            cin>>action;
            console::Clear();
            if(action==0)
            {
                break;
            }
            if(action==1)
            {
                Buy(field, zombiesila, sun_count, 100, '1');
            }
        }
        sun_count+=25;
        MoveAllZombies(field, zombiesila, 'Z', 1);
		if(ZombieWin(field))
		{
			cout<<"Prohra!!!"<<endl;
			PrintField(field,zombiesila);
			cin.get();
			return false;
		}
		ShootAll(field, zombiesila, 10, true, '1');
        if((i&1)==0)
        {
        	PutZombie(field, zombiesila, 0, 'Z', 30);
        }
    }
    cout<<"Vyhral jsi!!!"<<endl;
    cin.get();
    cin.get();
    return true;
}
///_____________________________________________________________________________________________________________________________
bool level2()
{
    uint16 widht=9;
    uint16 height=3;
    uint16 sun_count=25;
    Table<int16> zombiesila(height);
    Table<char> field(height);
    Init(field, zombiesila, widht);
    for(uint32 i=0;i<30;++i)
    {
        cout<<"Postup "<<(i*100/30)<<"%"<<endl;
        PrintField(field,zombiesila);
        cout<<"Z=Normalni zombik 30 zivotu, rychlost:1"<<endl;
        cout<<"R=Rychly zombik 15 zivotu, rychlost:2"<<endl;
        for(;;)
        {
			uint16 action=0;
			uint16 line=0;
			uint16 collumn=0;
            Menu(sun_count);
            cout<<"1-Pukac: Cena:100,utok:10,1 PUK/1 kolo"<<endl;
            cout<<"2-Laser Pukac: Cena 175,utok:10,1 Trefa/1 kolo, Zasahne celou radu"<<endl;
            cout<<"3-Randap: Cena 0, Zlikviduje 1 rostlinu"<<endl;
            cin>>action;
            console::Clear();
            if(action==0)
            {
                break;
            }
            if(action==1)
            {
                Buy(field, zombiesila, sun_count, 100, '1');
            }
            if(action==2)
            {
                Buy(field, zombiesila, sun_count, 175, '2');
            }
            if(action==3)
            {
                PrintField(field,zombiesila);
                cout<<"Zadejte radek"<<endl;
                cin>>line;
                --line;
                cout<<"Zadejte sloupec"<<endl;
                cin>>collumn;
                --collumn;
                if(collumn<widht&&line<height&&(IsPlantChar(field[line][collumn])))
                {
                    field[line][collumn]=' ';
                }
            }
        }
        sun_count+=25;
        //Pukac
        ShootAll(field, zombiesila, 10, true, '1');
        //Laser pukac
        ShootAll(field, zombiesila, 10, false, '2');
        //Zombik
        MoveAllZombies(field, zombiesila, 'Z', 1);
        //Rychlý
        MoveAllZombies(field, zombiesila, 'R', 2);
		if(ZombieWin(field))
		{
			cout<<"Prohra!!!"<<endl;
			PrintField(field,zombiesila);
			cin.get();
			return false;
		}
        if(i%3==1)//Umistovani normalniho zombika
        {
        	PutZombie(field, zombiesila, 0, 'Z', 30);
        }
        if(i%3==3)//Umistovani normalniho zombika
        {
            PutZombie(field, zombiesila, 1, 'Z', 30);
        }
        if(i%3==6)//Umistovani normalniho zombika
        {
            PutZombie(field, zombiesila, 2, 'Z', 30);
        }
        if(i%15==1)//Umistovani rychleho zombika
        {
            PutZombie(field, zombiesila, 0, 'R', 15);
        }
        if(i%15==5)//Umistovani rychleho zombika
        {
            PutZombie(field, zombiesila, 1, 'R', 15);
        }
        if(i%15==10)//Umistovani rychleho zombika
        {
            PutZombie(field, zombiesila, 2, 'R', 15);
        }
    }
    cout<<"Vyhral jsi!!!"<<endl;
    cin.get();
    cin.get();
    return true;
}
///_____________________________________________________________________________________________________________________________
bool level3()
{
    uint16 slunecnice=0;
    uint16 widht=9;
    uint16 height=5;
    uint16 sun_count=50;
    Table<int16> zombiesila(height);
    Table<char> field(height);
    Init(field, zombiesila, widht);
    for(uint32 i=0;i<50;++i)
    {
        cout<<"Postup "<<i*2<<"%"<<endl;
        PrintField(field,zombiesila);
        cout<<"Z=Normalni zombik 30 zivotu, rychlost:1"<<endl;
        cout<<"R=Rychly zombik 15 zivotu, rychlost:2"<<endl;
        cout<<"T=Tezky zombik 75 zivotu, rychlost:0,5"<<endl;
        for(;;)
        {
			uint16 action=0;
			uint16 line=0;
			uint16 collumn=0;
            Menu(sun_count);
            cout<<"1-Pukac: Cena:100, utok:10, 1 PUK/1 kolo"<<endl;
            cout<<"2-Laser Pukac: Cena 175,utok:10, 1 Trefa/1 kolo, Zasahne celou radu"<<endl;
            cout<<"3-Randap: Cena 0, Zlikviduje 1 rostlinu"<<endl;
            cout<<"4-Bomba: Cena 100, Zlikviduje 1 zombika"<<endl;
            cout<<"5-Slunecnice: Cena 45, 10 slunicek/kolo"<<endl;
            cin>>action;
            console::Clear();
            if(action==0)
            {
                break;
            }
            if(action==1)
            {
                Buy(field, zombiesila, sun_count, 100, '1');
            }
            if(action==2)
            {
                Buy(field, zombiesila, sun_count, 175, '2');
            }
            if(action==3)
            {
                PrintField(field,zombiesila);
                cout<<"Zadejte radek"<<endl;
                cin>>line;
                --line;
                cout<<"Zadejte sloupec"<<endl;
                cin>>collumn;
                --collumn;
                if(field[line][collumn]=='5')
                {
                    --slunecnice;
                }
                if(collumn<widht&&line<height&&IsPlantChar(field[line][collumn]))
                {
                    field[line][collumn]=' ';
                }
            }
            if(action==4)
            {
                PrintField(field,zombiesila);
                if(sun_count<100)
                {
                    cout<<"Mate nedostatek slunicek!"<<endl;
                }
                else
                {
                    cout<<"Zadejte radek"<<endl;
                    cin>>line;
                    --line;
                    cout<<"Zadejte sloupec"<<endl;
                    cin>>collumn;
                    --collumn;
                    if(CanPutPlant(field, line, collumn))
                    {
                        field[line][collumn]=' ';
                        sun_count-=100;
                    }
                    else
					{
						cout<<"Obsazeno!"<<endl;
					}
                }
            }
            if(action==5)
            {
                if(Buy(field, zombiesila, sun_count, 45, '5'))
                {
                    ++slunecnice;
                }
            }
        }
        sun_count+=25+(slunecnice*10);
        //Pukac
        ShootAll(field, zombiesila, 10, true, '1');
        //Laser
        ShootAll(field, zombiesila, 10, false, '2');
        if((i&1)==0)
        {
            MoveAllZombies(field, zombiesila, 'T', 1);
        }
        MoveAllZombies(field, zombiesila, 'Z', 1);
        MoveAllZombies(field, zombiesila, 'Z', 2);
		if(ZombieWin(field))
		{
			cout<<"Prohra!!!"<<endl;
			PrintField(field,zombiesila);
			cin.get();
			return false;
		}
        if(i%8==0)
        {
            PutZombie(field, zombiesila, 0, 'Z', 30);
        }
        if(i%8==2)
        {
            PutZombie(field, zombiesila, 1, 'Z', 30);
        }
        if(i%8==4)
        {
            PutZombie(field, zombiesila, 2, 'Z', 30);
        }
        if(i%8==6)
        {
            PutZombie(field, zombiesila, 3, 'Z', 30);
        }
        if(i%8==7)
        {
        	PutZombie(field, zombiesila, 4, 'Z', 30);
        }
        if(i==30||i==40||i==39)//Umistovani rychleho zombika-Finalni vlna
        {
        	PutZombie(field, zombiesila, 0, 'R', 15);
        	PutZombie(field, zombiesila, 1, 'R', 15);
        	PutZombie(field, zombiesila, 2, 'R', 15);
        	PutZombie(field, zombiesila, 3, 'R', 15);
        	PutZombie(field, zombiesila, 4, 'R', 15);
        }
        if(i==31||i==51||i==53)//Umistovani tezkeho zombika-Finalni vlna
        {
        	PutZombie(field, zombiesila, 0, 'T', 75);
        	PutZombie(field, zombiesila, 1, 'T', 75);
        	PutZombie(field, zombiesila, 2, 'T', 75);
        	PutZombie(field, zombiesila, 3, 'T', 75);
        	PutZombie(field, zombiesila, 4, 'T', 75);
        }
    }
    cout<<"Vyhral jsi!!!"<<endl;
    cin.get();
    cin.get();
    return true;
}
///_____________________________________________________________________________________________________________________________
bool level4()
{
    uint16 slunecnice=0;
    uint16 widht=9;
    uint16 height=5;
    uint16 sun_count=50;
    Table<int16> zombiesila(height);
    Table<char> field(height);
    Init(field, zombiesila, widht);
    for(uint32 i=0;i<50;++i)
    {
        cout<<"Postup "<<i*2<<"%"<<endl;
        PrintField(field,zombiesila);
        cout<<"Z=Normalni zombik 30 zivotu, rychlost:1"<<endl;
        cout<<"R=Rychly zombik 15 zivotu, rychlost:2"<<endl;
        cout<<"T=Tezky zombik 75 zivotu, rychlost:0,5"<<endl;
        cout<<"M=Maly zombik 5 zivotu, rychlost:2, Trefi ho jen fazole"<<endl;
        cout<<"S=Sportovec 45 zivotu, rychlost:2"<<endl;
        for(;;)
        {
			uint16 action=0;
			uint16 line=0;
			uint16 collumn=0;
            Menu(sun_count);
            cout<<"1-Pukac: Cena:100, Utok:10, 1 PUK/1 kolo"<<endl;
            cout<<"2-Laser Pukac: Cena 175, Utok:10, 1 Bzzzt/1 kolo, Zasahne celou radu"<<endl;
            cout<<"3-Randap: Cena 0, Zlikviduje 1 rostlinu"<<endl;
            cout<<"4-Bomba: Cena 100, Zlikviduje 1 zombika"<<endl;
            cout<<"5-Slunecnice: Cena 45, 10 slunicek/1 kolo"<<endl;
            cout<<"6-Fazole: Cena 100, Utok:5, 1 LUP/1 kolo"<<endl;
            cout<<"7-Ohnivy pukac: Cena 150, Utok:15, 1 PUK/1 kolo"<<endl;
            cin>>action;
            console::Clear();
            if(action==0)
            {
                break;
            }
            if(action==1)
            {
                Buy(field, zombiesila, sun_count, 100, '1');
            }
            if(action==2)
            {
                Buy(field, zombiesila, sun_count, 175, '2');
            }
            if(action==3)
            {
                PrintField(field,zombiesila);
                cout<<"Zadejte radek"<<endl;
                cin>>line;
                --line;
                cout<<"Zadejte sloupec"<<endl;
                cin>>collumn;
                --collumn;
                if(collumn<widht&&line<height&&(IsPlantChar(field[line][collumn])))
                {
                    field[line][collumn]=' ';
                }
                if(field[line][collumn]=='5')
                {
                    --slunecnice;
                }
            }
            if(action==4)
            {
                PrintField(field,zombiesila);
                if(sun_count<100)
                {
                    cout<<"Mate nedostatek slunicek!"<<endl;
                }
                else
                {
                    cout<<"Zadejte radek"<<endl;
                    cin>>line;
                    --line;
                    cout<<"Zadejte sloupec"<<endl;
                    cin>>collumn;
                    --collumn;
                    if(CanPutPlant(field, line, collumn))
                    {
                        field[line][collumn]=' ';
                        sun_count-=100;
                    }
                    else
					{
						cout<<"Obsazeno!"<<endl;
					}
                }
            }
            if(action==5)
            {
                if(Buy(field, zombiesila, sun_count, 45, '5'))
                {
                    ++slunecnice;
                }
            }
            if(action==6)
            {
                Buy(field, zombiesila, sun_count, 100, '6');
            }
            if(action==7)
            {
                Buy(field, zombiesila, sun_count, 150, '7');
            }
        }
        sun_count+=25+(slunecnice*10);
        //Pukac
        ShootAll(field, zombiesila, 10, true, '1');
        //Laser
        ShootAll(field, zombiesila, 10, false, '2');
        //Fazole
        ShootAllFazole(field, zombiesila, 5, true, '6');
        //Ohnivy
        ShootAll(field, zombiesila, 15, true, '7');
        if(i%2==0)
        {
        	MoveAllZombies(field, zombiesila, 'T', 1);
        }
        MoveAllZombies(field, zombiesila, 'Z', 1);
        MoveAllZombies(field, zombiesila, 'S', 2);
        MoveAllZombies(field, zombiesila, 'R', 2);
        MoveAllZombies(field, zombiesila, 'M', 2);
		if(ZombieWin(field))
		{
			cout<<"Prohra!!!"<<endl;
			PrintField(field,zombiesila);
			cin.get();
			return false;
		}
        if(i==5)
        {
        	PutZombie(field, zombiesila, 0, 'M', 5);
        }
        if(i==6)
        {
        	PutZombie(field, zombiesila, 1, 'M', 5);
        }
        if(i==7)
        {
        	PutZombie(field, zombiesila, 2, 'M', 5);
        }
        if(i==8)
        {
        	PutZombie(field, zombiesila, 3, 'M', 5);
        }
        if(i==9)
        {
        	PutZombie(field, zombiesila, 4, 'M', 5);
        }
        if(i%5==0&&i>14&&i!=15)
        {
        	PutZombie(field, zombiesila, 0, 'S', 45);
        }
        if(i%5==1&&i>14&&i!=16)
        {
        	PutZombie(field, zombiesila, 1, 'S', 45);
        }
        if(i%5==2&&i>14&&i!=17)
        {
        	PutZombie(field, zombiesila, 2, 'S', 45);
        }
        if(i%5==3&&i>14&&i!=18)
        {
        	PutZombie(field, zombiesila, 3, 'S', 45);
        }
        if(i%5==4&&i>14&&i!=19)
        {
        	PutZombie(field, zombiesila, 4, 'S', 45);
        }
        if((i%15==0||i%15==2||i%15==4)&&i>5)
        {
        	PutZombie(field, zombiesila, 3, 'T', 75);
        }
        if(i%25<7&&i>17)
        {
        	PutZombie(field, zombiesila, 0, 'S', 45);
        	PutZombie(field, zombiesila, 1, 'R', 15);
        	PutZombie(field, zombiesila, 4, 'Z', 30);
        }
    }
    cout<<"Vyhral jsi!!!"<<endl;
    cin.get();
    cin.get();
    return true;
}
bool Level(uint16 level)
{
	switch(level)
	{
		case 1:
			return level1();
		case 2:
			return level2();
		case 3:
			return level3();
		case 4:
			return level4();
		default:
			throw "Tento level neexistuje!";
	}
}