#include<bits/stdc++.h>
#include <random>
using namespace std;

class Creature
{
protected:
    string m_name;
    char m_symbol {};
    int m_health {};
    int m_damage {};
    int m_gold {};

public:
    Creature(string name,char symbol,int health,int damage,int gold)
        : m_name{name}
        , m_symbol{symbol}
        , m_health{health}
        , m_damage{damage}
        , m_gold{gold}
        {
        }
        
    const string& getName() const{return m_name;}
    char getSymbol() const{return m_symbol;}
    int getHealth() const{return m_health;}
    int getDamage() const{return m_damage;}    
    int getGold() const{return m_gold;}

    void reduceHealth(int health){m_health-=health;}
    void addGold(int gold){m_gold+=gold;}
    bool isDead() const {return m_health<=0;}
};

class Player:public Creature
{
private:
    int m_level{1};

public:
    Player(string name)
        :Creature(name,'@',10,1,0)
    {
    }
    
    void levelUp(){
        m_level++;
        m_damage++;
    }

    int getLevel() const{return m_level;}
    bool hasWon() const{return m_level>=20;}

};

class Monster:public Creature
{
public:
    enum Type
    {
        dragon,
        orc,
        slime,
        max_types
    };

private:
    inline static Creature monsterData[] {
        Creature{"dragon",'D',20,4,100},
        Creature{"orc",'o',4,2,25},
        Creature{"slime",'s',1,1,10},
    };

    static_assert(size(monsterData)==max_types);


public:
     Monster(Type type)
        :Creature{monsterData[type]}
    {
    }

    static Monster getRandomMonster()
    {
        static random_device rd;     // seed
        static mt19937 gen(rd());    // engine
        uniform_int_distribution<int> dist(0, max_types - 1);

        int num = dist(gen); // random integer in [0, max_types-1]
        return Monster{static_cast<Type>(num)};
    }   
};

void attackMonster(Player &player, Monster &monster){
    if(player.isDead())return;

    cout<<"You hit the "<<monster.getName()<<" for "<<player.getDamage()<<" damage\n";

    monster.reduceHealth(player.getDamage());

    if(monster.isDead()){
        cout<<"You killed the "<<monster.getName()<<"\n";
        player.levelUp();
        cout<<"You are now level "<<player.getLevel()<<"\n";
        cout<<"You found "<<monster.getGold()<<" gold\n";
        player.addGold(monster.getGold());
    }
}

void attackPlayer(Monster &monster, Player &player){
    if(monster.isDead())return;
    player.reduceHealth(monster.getDamage());
    cout<<"The "<<monster.getName()<<" hit you for "<<monster.getDamage()<<" damage\n";
}



void fightMonster(Player &player){
    Monster monster{Monster::getRandomMonster()};
    cout<<"You have encountered a "<<monster.getName()<<" ("<<monster.getSymbol()<<")\n";

    while(!monster.isDead() && !player.isDead()){
        cout<<"(R)un or (F)ight: ";
        char input{};
        cin>>input;
        if(input=='R'||input=='r'){
            static random_device rd;     // seed
            static mt19937 gen(rd());    // engine
            uniform_int_distribution<int> dist(1, 2);
            int num = dist(gen); // random integer in [0, max_types-1]

            if(num==1){
                cout<<"You successfully fled\n";
                return;
            }
            else{
                cout<<"You failed to flee\n";
                attackPlayer(monster,player);
                continue;
            }
        }
        if(input=='F'||input=='f'){
            attackMonster(player,monster);
            attackPlayer(monster,player);
        }
    }
}





int main()
{
	cout<<"Enter your name: ";
    string playerName;
    cin>>playerName;

    Player player{playerName};
    cout<<"Welcome "<<player.getName()<<"\n";

    while(!player.isDead() && !player.hasWon()){
        fightMonster(player);
    }

    if(player.isDead()){
        cout<<"You died at level "<<player.getLevel()<<" and with "<<player.getGold()<<" gold\n";
    }
    else{
        cout<<"You won the game with "<<player.getGold()<<" gold\n";
    }

	return 0;
}

