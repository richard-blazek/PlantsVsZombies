#pragma once

#include <iostream>
#include <iomanip>
#include "mylibraries/types.h"
#include "mylibraries/consol.h"
#include "mylibraries/dynarr.h"

using namespace std;
using containers::DynArr;

template<typename T>
using Table=DynArr<DynArr<T>>;

bool IsZombieChar(char ch)
{
	return ch>='A'&&ch<='Z';
}
bool IsPlantChar(char ch)
{
	return ch>='1'&&ch<='9';
}

void PrintField(const Table<char>& field, const Table<int16>& zombiesila)
{
    cout<<"  ";
    for(size_t vi=0;vi<field[0].size();++vi)
    {
        cout<<"   "<<vi+1<<"  ";
    }
    cout<<"\n  ";
    for(size_t vi=0;vi<field[0].size();++vi)
    {
        if(vi%9==0)
        {
            cout<<"_";
        }
        cout<<"______";
    }
    for(size_t y=0;y<field.size();++y)
    {
        cout.put('\n')<<"  |";
        for(size_t i=0;i<field[0].size();++i)
        {
            cout<<"     |";
        }
        cout.put('\n')<<y+1<<" |";
        for(size_t x=0;x<field[0].size();++x)
        {
            if(zombiesila[y][x]<=0&&IsZombieChar(field[y][x]))
            {
                cout<<"     |";
            }
            else
            {
                cout<<"  "<<field[y][x]<<"  |";
            }
        }
        cout.put('\n')<<"  |";
        for(size_t x=0;x<field[0].size();++x)
        {
            if(IsZombieChar(field[y][x])&&zombiesila[y][x]>0)
            {
                cout<<setw(4)<<zombiesila[y][x]<<" |";
            }
            else
            {
                cout<<"     |";
            }
        }
        cout.put('\n')<<"  |";
        for(size_t i=0;i<field[0].size();++i)
        {
            cout<<"_____|";
        }
    }
    cout<<endl;
}

void Menu(uint16 sun_count)
{
	cout<<"Mate "<<sun_count<<" slunicek"<<endl;
	cout<<"Co chcete koupit?"<<endl;
	cout<<"0-Konec nakupu"<<endl;
}

bool ZombieWin(const Table<char>& field)
{
	for(auto& line:field)
	{
		if(IsZombieChar(line[0]))
			return true;
	}
	return false;
}

void Init(Table<char>& field, Table<int16>& zombiesila, uint16 widht)
{
	for(uint16 oi=0;oi<field.size();++oi)
	{
		field[oi].resize(widht);
		zombiesila[oi].resize(widht);
		field[oi].fill(' ');
		zombiesila[oi].fill(0);
	}
}

void MoveZombie(Table<char>& field, Table<int16>& zombiesila, uint32 line, uint32 collumn, char znak, int8 step)
{
	if(zombiesila[line][collumn]>0)
	{
		field[line][collumn-step]=znak;
		zombiesila[line][collumn-step]=zombiesila[line][collumn];
		zombiesila[line][collumn]=0;
	}
	field[line][collumn]=' ';
}

void Shoot(Table<char>& field, Table<int16>& zombiesila, uint32 line, uint32 column, int8 attack, bool stop)
{
	for(;column<field[0].size();++column)//Zasahy
	{
		if(IsZombieChar(field[line][column])&&field[line][column]!='M')
		{
			zombiesila[line][column]-=attack;
			if(stop)
			{
				break;
			}
		}
	}
}
void ShootAll(Table<char>& field, Table<int16>& zombiesila, int8 attack, bool stop, char znak)
{
	for(uint16 line=0;line<field.size();++line)//Pukace
	{
		for(uint16 collumn=0;collumn<field[0].size();++collumn)
		{
			if(field[line][collumn]==znak)
			{
				Shoot(field, zombiesila, line, collumn, attack, stop);
			}
		}
	}
}
void FazoleShoot(Table<char>& field, Table<int16>& zombiesila, uint32 line, uint32 column, int8 attack, bool stop)
{
	for(;column<field[0].size();++column)//Zasahy
	{
		if(IsZombieChar(field[line][column]))
		{
			zombiesila[line][column]-=attack;
			if(stop)
			{
				break;
			}
		}
	}
}
void ShootAllFazole(Table<char>& field, Table<int16>& zombiesila, int8 attack, bool stop, char znak)
{
	for(uint16 line=0;line<field.size();++line)//Fazole
	{
		for(uint16 column=0;column<field[0].size();++column)
		{
			if(field[line][column]==znak)
			{
				FazoleShoot(field, zombiesila, line, column, attack, stop);
			}
		}
	}
}
void MoveAllZombies(Table<char>& field, Table<int16>& zombiesila, char znak, int8 step)
{
	for(uint16 line=0;line<field.size();++line)
	{
		for(uint16 collumn=0;collumn<field[0].size();++collumn)
		{
			if(field[line][collumn]==znak&&!IsZombieChar(field[line][collumn-1]))
			{
				MoveZombie(field, zombiesila, line, collumn, znak, step);
			}
		}
	}
}
bool CanPutPlant(Table<char>& field, uint32 line, uint32 collumn)
{
    return(line<field.size()&&collumn<field[line].size()&&field[line][collumn]==' ');
}
void PutZombie(Table<char>& field, Table<int16>& zombiesila, int16 line, char znak, int16 sila)
{
	field[line].back()=znak;
	zombiesila[line].back()=sila;
}

bool Buy(Table<char>& field, Table<int16>& zombiesila, uint16& sun_count, uint16 price, char znak)
{
	PrintField(field,zombiesila);
	if(sun_count<price)
	{
		cout<<"Mate nedostatek slunicek!"<<endl;
		return false;
	}
	uint16 line=0, column=0;
	cout<<"Zadejte radek"<<endl;
	cin>>line;
	--line;
	cout<<"Zadejte sloupec"<<endl;
	cin>>column;
	--column;
	if(CanPutPlant(field, line, column))
	{
		field[line][column]=znak;
		sun_count-=price;
		return true;
	}
	else
	{
		cout<<"Obsazeno"<<endl;
		return false;
	}
}