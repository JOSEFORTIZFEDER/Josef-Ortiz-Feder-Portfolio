using System;

public class Animal
{
	public Animal()
	{

	}
	public virtual void move()
	{
		Console.WriteLine("An animal is moving");
	}
    public virtual void sleep()
    {
        Console.WriteLine("An animal is sleeping");
    }
    public virtual void eat()
    {
        Console.WriteLine("An animal is eating");
    }
    
}
