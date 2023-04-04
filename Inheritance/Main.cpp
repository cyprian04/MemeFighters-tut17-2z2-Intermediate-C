#include <iostream>
#include <string>
#include <conio.h>
#include <random>

class Dice
{
public:
	int Roll( int nDice )
	{
		int total = 0;
		for( int n = 0; n < nDice; n++ )
		{
			total += d6( rng );
		}
		return total;
	}
private:
	std::uniform_int_distribution<int> d6 = std::uniform_int_distribution<int>( 1,6 );
	std::mt19937 rng = std::mt19937( std::random_device{}() );
};

class MemeFighter
{
public:
	const std::string& GetName() const
	{
		return name;
	}
	bool IsAlive() const
	{
		return hp > 0;
	}
	int GetInitiative()
	{
		return speed + d.Roll(2);
	}
	void Punch(MemeFighter& other) const
	{
		if (IsAlive() && other.IsAlive())
		{
			std::cout << name << " punches " << other.GetName()<<"!"<< std::endl;
			ApplyDamageTo(other, power + d.Roll(2));
		}
	}
	void Tick()
	{
		if (IsAlive())
		{
			const int recovery = Roll();
			std::cout <<name<<" recovers "<< recovery <<" hp" << std::endl;
			hp += recovery;
		}
	}
	virtual void SpecialMove(MemeFighter&)
	{
		std::cout << "You will never get this!" << std::endl;
	}
protected:
	MemeFighter(int hp, int speed, int power, std::string name)
		:
		hp(hp),
		speed(speed),
		power(power),
		name(name)
	{}
	void ApplyDamageTo(MemeFighter& target, int damage) const
	{
		target.hp -= damage;
		std::cout << target.name<<" takes"<< damage << "damage" << std::endl;
		if (!target.IsAlive())
		{
			std::cout<<"As the life leaves "<< target.name <<"'s body does the poop" << std::endl;
		}
	}
	int Roll(int nDice = 1)const
	{
		return d.Roll(nDice);
	}
protected:
	int hp;
	int speed;
	int power;
	std::string name;
private:
	mutable Dice d;
};

class MemeFrog : public MemeFighter
{
public:
	MemeFrog(const std::string& name)
		:
		MemeFighter(69, 7, 14, name)
	{}
	void SpecialMove(MemeFighter& other) const
	{
		if (IsAlive() && other.IsAlive())
		{
			if (Roll() > 4)
			{
				std::cout << GetName() << " attacks " << other.GetName() << "with a rainbow beam"<<std::endl;
				ApplyDamageTo(other, Roll(3) + 20);
			}
			else
			{
				std::cout << GetName() << " falls from his unicycle!" << std::endl;
			}
		}
	}
	void Tick()
	{
		if (IsAlive())
		{
			std::cout << GetName() << " is hurt by the bad AIDS" << std::endl;
			ApplyDamageTo(*this, Roll());
			MemeFighter::Tick();
		}
	}
};

class MemeStoner : public MemeFighter
{
public:
	MemeStoner(const std::string& name)
		:
		MemeFighter(80, 4, 10, name)
	{}
	void SpecialMove(MemeFighter&) override 
	{
		if (IsAlive())
		{
			if (Roll() > 3)
			{
				std::cout << GetName() << " smokes the dank sitcky inky, becoming" << " Super " << GetName() << std::endl;
				name = "Super" + name;
				speed += 3;
				power = (power * 69) / 42;
				hp += 10;
			}
			
			else
			{
				std::cout << GetName() << " spaces out " << std::endl;
			}
		}
	}

};

void Engage( MemeFighter& f1,MemeFighter& f2 )
{
	// pointers for sorting purposes
	auto* p1 = &f1;
	auto* p2 = &f2;
	// determine attack order
	if( p1->GetInitiative() < p2->GetInitiative() )
	{
		std::swap( p1,p2 );
	}
	// execute attacks
	p1->Punch( *p2 );
	p2->Punch( *p1 );
}

void DoSpecials(MemeFighter& f1, MemeFighter& f2)
{
	// pointers for sorting purposes
	auto* p1 = &f1;
	auto* p2 = &f2;
	// determine attack order
	if (p1->GetInitiative() < p2->GetInitiative())
	{
		std::swap(p1, p2);
	}
	// execute attacks
	p1->SpecialMove(*p2);
	p2->SpecialMove(*p1);
}

int main()
{
	MemeFrog f1( "Dat Boi" );
	MemeStoner f2( "Good Guy Greg" );

	while( f1.IsAlive() && f2.IsAlive() )
	{
		// trade blows
		Engage( f1,f2 );
		// special moves
		DoSpecials(f1, f2);
		// end of turn maintainence
		f1.Tick();
		f2.Tick();

		std::cout << "Press any key to continue...";
		while( !_kbhit() );
		_getch();
		std::cout << std::endl << std::endl;
	}

	if( f1.IsAlive() )
	{
		std::cout << f1.GetName() << " is victorious!";
	}
	else
	{
		std::cout << f2.GetName() << " is victorious!";
	}
	while( !_kbhit() );
	return 0;
}